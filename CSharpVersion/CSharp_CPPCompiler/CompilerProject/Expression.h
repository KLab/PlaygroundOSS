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
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "BaseType.h"

struct SInitialization {
	//
	// Used by m_mode
	//
	static const int	INIT_WRAP_FUNC			= 1;
	static const int	INIT_CHAIN				= 2;
	static const int	INIT_MEMCPY				= 3;
	static const int	INIT_CHAINADD			= 4;

	SInitialization*	m_next;
	TypeObject*			m_typeArray;
	Expression*			m_expression;
	int					m_expressionCounter;
	int					m_mode;
	bool				m_isDumped;
};

class Expression {
public:
	Expression();
	~Expression();
	Expression* addGenericType	(TypeGenericEntry* genericParam) { m_genericCall = genericParam; return this; }
	static void patchExpressionsForListExpressions(Expression** expr, TypeObject* type);
	Expression*	addExpression	(Expression*);		// return this
	Expression* setIdentifier	(const char* id);	// return this
	Expression* setType			(TypeObject* type);	// return this
	Expression* setType			(TypeObject* type, Quals* quals);	// return this
	Expression* addParenthesis	();					// return this
	Expression* setValue		(SValue v);
	Expression* setRank			(u32 rank);
	Expression* setArrayNew		(bool generateArrayType);
	Expression* setAsRef		()	{ m_asRef = true; return this; }
	Expression* patchSubInvoke	();

	SRSymbol	resolveIteration(const char* text, SRSymbol input, TypeObject*& lastType, SRSymbol& item, u8 searchMask, Expression* methodSignature = NULL, Variable* delegateSignature = NULL, TypeGenericEntry* genParams = NULL);
	void		dumpExpression		() {
		dumpExpressionInternal();
	}

	static void	analysisTransformAndDump(Expression** expr, TypeObject* type) {
		patchExpressionsForListExpressions(expr, type);
		(*expr)->AnalysisAndTransform();
		(*expr)->dumpExpressionInternal();
	}

	void		dumpExpressionInternal();
	void		AnalysisAndTransform();
	void		AnalysisMethodForDelegate(TypeGenericEntry* genParams);
	void		AnalysisInvokeMethod(Expression* signature, TypeGenericEntry* genParams);
	void		transformMethodAsDelegate(Expression*& methodParam, int paramRank);
	void		dumpTokens(SRSymbol res, const char* text, bool hasPrevious);

	void		dumpTree			();			// For debug purpose
	const char*	getOpDump			();
	const char*	getAssEqOpDump		();

	bool		isConstant			();
	SValue		getValue			();
	void		inverseValue		();
	bool		compareValues		(Expression* exp);

	bool		isAmbiguous			();
	bool		isMethodAsDelegate	();

	void		getStructInfo		(SStructInfo& out_structInfo);
public:
	TypeGenericEntry*	m_genericCall;
	int					m_expressionCount;
	Expression**		m_expressions;
	bool				m_hasParenthesis;
	Quals*				m_quals;
	TypeObject*			m_typeParam;
	TypeObject*			m_runtimeType;
	Variable*			m_delegateSignature;
	Statement*			m_delegateCode;
	AbstractContainer*	m_anonymousClass;
	const char*			m_text;
	EnumExpressionType	m_expressionType;
	bool				m_arrayNew;
	u32					m_rank;
	SValue				m_value;
	bool				m_isAssignmentSide;
	bool				wrapStringStart;
	bool				wrapStringEnd;
	bool				m_bSkip;	// Used to skip printing the method name when dumping expression for delegate creation in new, or the container class of a nested one.
	bool				m_asRef;
	bool				m_isInvoked;
	bool				m_isDotRoot;
	Delegate*			m_delegateDef;
	SInitialization*	m_initializerInfo;
	SRSymbol			m_item;
	u32					m_line;
};

Expression*	CreateMultipleExpr	(Expression* first);
Expression*	CreateLeafExpr		(EnumExpressionType type, const char* ident = NULL);
Expression*	CreateSingleExpr	(EnumExpressionType type, Expression* child);
Expression*	CreateDoubleExpr	(EnumExpressionType type, Expression* pre, Expression* post);
Expression*	CreateTripleExpr	(EnumExpressionType type, Expression* cond, Expression* tExpr, Expression* fExpr);

/*
Expression*	CreateNewObj		(EnumStatementType statementType);
Expression*	CreateNewObj		(EnumExpressionType expr_type);
*/

#endif	//EXPRESSION_H
