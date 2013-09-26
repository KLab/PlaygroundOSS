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
#ifndef STATEMENT_H
#define STATEMENT_H

#include "BaseType.h"

//Constants for the search mask
const u8 SEARCH_VARIABLE		= 0x80;
const u8 SEARCH_MEMBER			= 0x40;
const u8 SEARCH_PROPERTY		= 0x20;
const u8 SEARCH_INSTANCE		= SEARCH_VARIABLE | SEARCH_MEMBER | SEARCH_PROPERTY;
const u8 SEARCH_INHERITANCE		= 0x10;
const u8 SEARCH_HIERARCHY		= 0x08;
const u8 SEARCH_FUNCTION		= 0x04;
const u8 SEARCH_TYPE			= 0x02;
const u8 SEARCH_ALL				= SEARCH_FUNCTION | SEARCH_INSTANCE | SEARCH_TYPE | SEARCH_INHERITANCE | SEARCH_HIERARCHY;

class Statement {
public:
	Statement();
	~Statement();

	Statement* setExpression(Expression* expr);
	Statement* addLabel(const char* label);
	Statement* addType(TypeObject* type);
	Statement* addNext(Statement* next);	// Return THIS, not NEXT !
	Statement* addChild(Statement* child);
	Statement* addChildNilWrap(Statement* child);	// If NULL, create a default NULL statement 
	Statement* setConstant();	// For variable create statement

	Statement* wrapCaseBody();
	void analysis(bool processBrother = true);
	void dumpStatement(bool processBrother = true);
public:
	bool				m_bConstant;
	EnumStatementType	m_statementType;
	const char*			lbl;
	Statement*			m_pNext;
	Statement*			m_pChild;
	TypeObject*			m_type;	// CATCH statement
	Expression*			m_expr;
	Variable*			m_vars;
	int					m_counter;
	u32					m_line;
};

Statement*  CreateStatement		(EnumStatementType statementType, Statement* brother, Statement* child);

#endif	//STATEMENT_H
