/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "include.h"

Expression::Expression()
:m_expressionCount	(0)
,m_expressions		(NULL)
,m_hasParenthesis	(false)
,m_typeParam		(NULL)
,m_runtimeType		(NULL)
,m_text				(NULL)
,m_arrayNew			(false)
,m_rank				(0)
,m_isAssignmentSide	(NULL)
,m_quals			(NULL)
,wrapStringStart	(false)
,wrapStringEnd		(false)
,m_bSkip			(false)
,m_delegateCode		(NULL)
,m_delegateSignature(NULL)
,m_anonymousClass	(NULL)
,m_delegateDef		(NULL)
,m_initializerInfo	(NULL)
,m_genericCall		(NULL)
,m_asRef			(false)
,m_isInvoked		(false)
,m_isDotRoot		(true)
{
	m_value.type	= TYPE_UNRESOLVED;
	m_line			= yylineno;
}

bool Expression::isConstant()
{
	if (this->m_expressionType == EXPR_CTE) {
		return true;
	}
	return false;
}

Expression* Expression::patchSubInvoke() {
	m_expressions[0]->m_isInvoked = true;
	return this;
}

SValue Expression::getValue()
{
	return this->m_value;
}

void Expression::inverseValue() {
	switch(m_value.type) {
		case TYPE_BOOL:
		case TYPE_STRING:
		case TYPE_NULL: 
		case TYPE_UINT:
		case TYPE_ULONG:
		case TYPE_CHAR:
			// Do nothing
			break;
			
		case TYPE_DOUBLE:
			m_value.v.d = -m_value.v.d;
			break;
		case TYPE_FLOAT:
			m_value.v.f = -m_value.v.f;
			break;
		case TYPE_INT:
			m_value.v.i = -m_value.v.i;
			break;
		case TYPE_LONG:
			m_value.v.l = -m_value.v.l;
			break;
		default:
			compilerError(ERR_INTERNAL,"Unknown constant type", m_line);
	}
}

bool Expression::compareValues(Expression* exp)
{
	if(!isConstant() || !exp->isConstant()) {
		compilerError(ERR_INTERNAL, "Can only compare values of constant expressions", exp->m_line);
		return false;
	}
	switch(m_value.type) {
		case TYPE_BOOL:
			return m_value.v.i == exp->m_value.v.i;
		case TYPE_STRING:
			return (strcmp(m_value.v.str,exp->m_value.v.str)==0);
		case TYPE_NULL: 
			return m_value.v.ptr == exp->m_value.v.ptr;
		case TYPE_DOUBLE:
			return m_value.v.d == exp->m_value.v.d;
		case TYPE_FLOAT:
			return m_value.v.f == exp->m_value.v.f;
		case TYPE_INT:
			return m_value.v.i == exp->m_value.v.i;
		case TYPE_UINT:
			return m_value.v.ui == exp->m_value.v.ui;
		case TYPE_LONG:
			return m_value.v.l == exp->m_value.v.l;
		case TYPE_ULONG:
			return m_value.v.ul == exp->m_value.v.ul;
		case TYPE_CHAR:
			return m_value.v.i == exp->m_value.v.i;
		default:
			compilerError(ERR_INTERNAL,"Unknown constant type", exp->m_line);
			return false;
	}
}

bool Expression::isAmbiguous() {
	if(this == NULL) {
		return false;
	}
	for(int n = 0 ; n < m_expressionCount ; n++) {
		if(!m_expressions[n]->m_runtimeType) {
			return false;
		}
		if(m_expressions[n]->m_runtimeType->m_res.symbolType == EGENRE::_METHODLIST) {
			return true;
		}
	}
	return false;
}

bool Expression::isMethodAsDelegate() {
	return (m_item.symbolType == EGENRE::_METHOD && m_expressionType != EXPR_INVOKE);
}

void Expression::getStructInfo(SStructInfo& out_structInfo) {
	if(m_expressionType != EXPR_LIST) {
		compilerError(ERR_INTERNAL, "Parameter list expected", m_line);
	}
	for(int n = 0; n < m_expressionCount ; n++) {
		Expression* pExpr = m_expressions[n];
		switch(pExpr->m_expressionType) {
		case EXPR_DOT :
			if(strcmp(pExpr->m_expressions[0]->m_text, "LayoutKind") != 0) {
				compilerError(ERR_USER, "Unknown parameter for StructLayout", pExpr->m_expressions[0]->m_line);
			}
			else {
				// Get the value of the enum entry
				pExpr->AnalysisAndTransform();
				if(pExpr->m_item.symbolType == EGENRE::_ENUMENTRY) {
					Enum::EnumEntry* pEntry = (Enum::EnumEntry*)pExpr->m_item.pSymbol;
					out_structInfo.m_layoutKind = pEntry->m_expression->m_value.v.i;
				}
				else {
					compilerError(ERR_INTERNAL, "Enum entry not found", pExpr->m_line);
				}
			}
			break;
		case EXPR_ASS_EQ :
		{
			s32* field = NULL;
			if(strcmp(pExpr->m_expressions[0]->m_text, "Pack") == 0) {
				field = &out_structInfo.m_pack;
			} else if(strcmp(pExpr->m_expressions[0]->m_text, "Charset") == 0) {
				field = &out_structInfo.m_charSet;
			} else {
				compilerError(ERR_USER, "Unknown parameter for StructLayout", pExpr->m_expressions[0]->m_line);
			}
			if(pExpr->m_expressions[1]->m_expressionType == EXPR_CTE) {
				if(field) {
					*field = pExpr->m_expressions[1]->m_value.v.i;
				}
			}
			else {
				compilerError(ERR_USER, "Attribute field value is not a constant", pExpr->m_expressions[1]->m_line);
			}
			break;
		}
		default :
			compilerError(ERR_USER, "Unknown attribute syntax", pExpr->m_line);
			break;
		}
	}
}

Expression::~Expression() {
	CLEAR(m_expressions,m_expressionCount);
}

Expression*	Expression::addExpression	(Expression* newExpr) {
	EXPAND(m_expressionCount, m_expressions, newExpr);
	return this;
}

Expression* Expression::setIdentifier	(const char* id) {
	this->m_text = concat(id);
	return this;
}

Expression* Expression::setType			(TypeObject* type) {
	this->m_runtimeType = type;
	return this;
}

Expression* Expression::setType			(TypeObject* type, Quals* quals) {
	if (quals == NULL) {
		return setType(type);
	} else {
		TypeObject* newType = type;
		Quals* pQuals = quals;
		while (pQuals) {
			newType = newType->addRank(pQuals->rank);
			pQuals = pQuals->m_pNext;
		}
		this->m_runtimeType = newType;
		return this;
	}
}

Expression* Expression::addParenthesis	() {
	this->m_hasParenthesis = true;
	return this;
}

Expression* Expression::setArrayNew(bool generateArrayType) {
	// Generate different TypeObject and wrap original one.
	this->m_arrayNew = true;
	if (generateArrayType) {
		m_runtimeType = m_runtimeType->createArrayType(1);
	}
	return this;
}

Expression* Expression::setRank(u32 rank) {
	this->m_rank = rank;
	return this;
}

Expression* Expression::setValue(SValue val) {
	this->m_value = val;
	return this;
}

/*static*/
void Expression::patchExpressionsForListExpressions(Expression** expr, TypeObject* type) {
	if ((*expr)->m_expressionType == EXPR_LIST_INIT) {
		//
		// Transform Var a = {....} into Var a = new type[count] { .... } 
		//
		SValue v;
		v.v.i = (*expr)->m_expressionCount;
		v.type	= TYPE_INT;

		Expression* sizeExpr	= CreateLeafExpr(EXPR_CTE)->setValue(v);
		Expression* initialized = *expr;
		Expression* exprNEW = CreateDoubleExpr(EXPR_NEW, sizeExpr, initialized)->setType(type);	// Set variable type.
		*expr = exprNEW;
	}
}

Expression*	CreateMultipleExpr	(Expression* first) {
	Expression* pexpr = new Expression();
	pexpr->m_expressionType = EXPR_LIST;
	pexpr->addExpression(first);
	return pexpr;
}

bool contains(const char* str, int char_) {
	while (*str) {
		if (*str++ == char_) {
			return true;
		}
	}
	return false;
}

Expression*	CreateLeafExpr		(EnumExpressionType type, const char* ident) {
	Expression* pLeafexpr = new Expression();
	pLeafexpr->m_expressionType = type;

	if (ident) {
		Expression* pExpr = pLeafexpr;
		if (contains(ident, '.') && (type == EXPR_IDENT)) {
			StringList* pList = split(ident);
			pLeafexpr->setIdentifier(pList->content);
			// start from next item.
			pList = pList->pNext;
			while (pList) {
				Expression* newExpr = CreateSingleExpr(EXPR_DOT, pExpr)->setIdentifier(pList->content);
				pExpr = newExpr;
				pList = pList->pNext;
			}
		} else {
			pLeafexpr->setIdentifier(ident);
		}

		return pExpr;
	}
	return pLeafexpr;
}

int gGlobalInitializeCount = 0;
SInitialization* gGlobalInitList = NULL;

Expression*	gInitializerStack[50];
int gInitializerCount = 0;

SInitialization* registerGlobalInitializer(Expression* expr) {
	SInitialization* init = new SInitialization();

	init->m_mode		= SInitialization::INIT_CHAIN;	// Default mode.
	init->m_expression	= expr;
	init->m_typeArray	= NULL;
	init->m_next		= gGlobalInitList;
	init->m_expressionCounter = gGlobalInitializeCount++;
	init->m_isDumped	= !g_noDump;

	gGlobalInitList = init;
	return init;
}

void GenerateInitList() {
	Expression* pExpr = CreateLeafExpr(EXPR_LIST_INIT,NULL);
	pExpr->m_initializerInfo = registerGlobalInitializer(pExpr);
	gInitializerStack[gInitializerCount++] = pExpr;
}

void PopInitList() {
	Expression* pExpr		= gInitializerStack[--gInitializerCount];
	bool allCte = true;
	for (int n=0; n < pExpr->m_expressionCount; n++) {
		Expression* pExp = pExpr->m_expressions[n];
		if ((!pExp->isConstant()) || (pExp->m_value.type == TYPE_STRING)) {
			allCte = false;
			break;
		}
	}
	SInitialization* pInit  = pExpr->m_initializerInfo;
	
	if (allCte) {
		pInit->m_mode = SInitialization::INIT_MEMCPY;
	}
}

Expression* getInitList() {
	return gInitializerStack[gInitializerCount-1];
}

Expression*	CreateSingleExpr	(EnumExpressionType type, Expression* child) {
	if (EXPR_UNARYMINUS==type) {
		if (child->m_expressionType == EXPR_CTE) {
			child->inverseValue();
			return child;
		}
	}
	Expression* pexpr = new Expression();
	pexpr->m_expressionType = type;
	pexpr->addExpression(child);
	return pexpr;
}

Expression*	CreateDoubleExpr	(EnumExpressionType type, Expression* pre, Expression* post) {
	Expression* pexpr = new Expression();
	pexpr->m_expressionType = type;
	pexpr->addExpression(pre);
	pexpr->addExpression(post);
	return pexpr;
}

Expression*	CreateTripleExpr	(EnumExpressionType type, Expression* cond, Expression* tExpr, Expression* fExpr) {
	Expression* pexpr = new Expression();
	pexpr->m_expressionType = type;
	pexpr->addExpression(cond);
	pexpr->addExpression(tExpr);
	pexpr->addExpression(fExpr);
	return pexpr;
}

/*
Expression*	CreateNewObj		(EnumStatementType statementType) {
	Expression* expr = new Expression();
	expr->
	return expr;
}

Expression*	CreateNewObj		(EnumExpressionType expr_type) {
	Expression* expr = new Expression();
	expr->m_expressionType = expr_type;
	return expr;
}
*/
