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

Statement::Statement()
:m_bConstant			(false)
,m_statementType		(STM_UNDEFINED)
,lbl					(NULL)
,m_pNext				(NULL)
,m_pChild				(NULL)
,m_type					(NULL)
,m_expr					(NULL)
,m_vars					(NULL)
,m_counter				(-1)
{
	m_line = yylineno;
}

Statement::~Statement() 
{
	delete[] lbl;
	delete m_pChild;
	delete m_pNext;
	delete m_type;
	delete m_expr;
	delete m_vars;
}

Statement* Statement::setExpression(Expression* expr) {
	m_expr = expr;
	return this;
}

// LATER : Change to setLabel
Statement* Statement::addLabel(const char* label) {
	lbl = concat(label);
	return this;
}

// LATER : Change to setType most likely
Statement* Statement::addType(TypeObject* type) {
	this->m_type = type;
	return this;
}

Statement* Statement::addNext(Statement* next) {
	Statement* p = this;
	while (p->m_pNext) {
		p = p->m_pNext;
	}
	p->m_pNext = next;

	return this;
}

Statement* Statement::addChild(Statement* child) {
	Statement* p = this->m_pChild;
	if (p) {
		while (p->m_pNext) { p = p->m_pNext; }
		p->m_pNext = child;
	} else {
		m_pChild = child;
	}
	return this;
}

Statement* Statement::addChildNilWrap(Statement* child) {
	Statement* childW = new Statement();
	childW->m_statementType = STM_NILWRAPPER;
	childW->addChild(child);
	this->addChild(childW);
	return this;
}

Statement* Statement::setConstant() {
	this->m_bConstant = true;
	return this;
}

Statement* CreateStatement(EnumStatementType statementType, Statement* brother, Statement* child) {
	Statement* pN	= new Statement();
	pN->m_statementType		= statementType;
	pN->m_pNext				= brother;
	pN->m_pChild			= child;
	return pN;
}