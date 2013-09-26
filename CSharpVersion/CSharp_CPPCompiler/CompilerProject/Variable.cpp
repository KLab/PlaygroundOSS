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

Variable::Variable	() 
:m_pNextVariable	(NULL)
,m_expression		(NULL)
,m_attribute		(NULL)
,m_modifier			(0)
,m_type				(NULL)
,m_bEndless			(false)
,m_ignoreDelegate	(false)
,m_dependancyList	(NULL)
,m_ownerClass		(NULL)
{
	// Invalid for a constant.
	m_value.type = TYPE_UNRESOLVED;
}

Variable::~Variable() {
}

void Variable::markSetupDependancy() {
	bool analysis = g_analysis_static;
	g_analysis_static = true;

	if (m_expression) { m_expression->AnalysisAndTransform(); }

	g_analysis_static = analysis;
}

Variable* Variable::addVariable	(Variable* pNextVariable) {
	Variable* p = this;
	while (p->m_pNextVariable) {
		p = p->m_pNextVariable;
	}
	p->m_pNextVariable = pNextVariable;
	return this;
}

Variable* Variable::setInitializer(Expression* pExpr) {
	this->m_expression = pExpr;
	return this;
}

Variable* Variable::setAttribute	(Attribute* attrib) {
	this->m_attribute = attrib;
	return this;
}

Variable* Variable::setModifier	(u32 modifier) {
	this->m_modifier |= modifier;
	return this;
}

Variable* Variable::setType		(TypeObject* type) {
	this->m_type = type;
	return this;
}

Variable* Variable::setIsEndLessParam	() {
	this->m_bEndless = true;
	return this;
}

Variable* Variable::setValue		(SValue v) {
	m_value = v;
	return this;
}

bool Variable::hasImplicitConversion(TypeObject* type) {
	if(this->m_type->hasImplicitConversion(type)) {
		return true;
	}
	if((this->m_expression->m_expressionType == EXPR_CTE) && (this->m_value.v.i == 0) && (type->getGenre() == EGENRE::_ENUM)) {
		// 0 can be implicitly casted into any enum
		return true;
	}
	return false;
}

Statement*  CreateVarStatement	(EnumStatementType statementType, Statement* brother, Statement* child, Variable* vars, TypeObject* type) {
	Statement* pStatement = new Statement();
	pStatement->m_statementType = statementType;
	pStatement->addChild(child);
	pStatement->addNext(brother);
	pStatement->m_type = type;
	pStatement->m_vars = vars;
	
	// Assign type to all variables.
	Variable* pVar = vars;
	Variable* pPrevVar = NULL;
	while (pVar) {
		pVar->m_type = type;
		Statement* pSubStatement = new Statement();
		pSubStatement->m_statementType = STM_LOCAL_PERVAR;

		// var = ...
		if (pVar->m_expression) {
			Expression* assign = CreateDoubleExpr(EXPR_ASS_EQ, 
				CreateLeafExpr(EXPR_IDENT)->setIdentifier(pVar->getName()),
				pVar->m_expression
			);
			pSubStatement->setExpression(assign);
		}
		
		pStatement->addChild(pSubStatement);
		pSubStatement->m_vars = pVar;
		pSubStatement->m_bConstant;
		pPrevVar = pVar;
		pVar = pVar->m_pNextVariable;
	}
	return pStatement;
}

Variable*   CreateVarInstance	(const char* varName) {
	Variable* var = new Variable();
	var->setName(varName);
	return var;
}
