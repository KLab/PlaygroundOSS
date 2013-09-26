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
#ifndef VARIABLE_H
#define VARIABLE_H

#include "BaseType.h"
#include "Symbol.h"

class Attribute;
class Expression;
class Statement;
class Symbol;
class TypeObject;

class Variable : public Symbol {
public:
	Variable();
	~Variable();

	virtual int getGenre() { return EGENRE::_VARIABLE; }

	Variable* addVariable	(Variable* pNextVariable);
	Variable* setInitializer(Expression* pExpr);

	Variable* setAttribute	(Attribute* attrib);
	Variable* setModifier	(u32 modified);
	Variable* setType		(TypeObject* type);
	Variable* setIsEndLessParam	();
	Variable* setValue		(SValue v);

	void	markSetupDependancy	();

	void		dumpVariable();
	void		dumpMember	(NameSpace* nameSpaceContext);

	bool	hasImplicitConversion(TypeObject* type);

	AbstractContainer*	m_ownerClass;
	Variable*	m_pNextVariable;
	Expression*	m_expression;
	Attribute*	m_attribute;
	u32			m_modifier;
	TypeObject*	m_type;
	bool		m_bEndless;
	bool		m_ignoreDelegate;
	SValue		m_value;
protected:
	struct VarDependancy {
		VarDependancy*	m_pNext;
		Variable*		m_uses;
	};
	VarDependancy*	m_dependancyList;
};

Statement*  CreateVarStatement	(EnumStatementType statementType, Statement* brother, Statement* child, Variable* vars, TypeObject* type);

Variable*   CreateVarInstance	(const char* varName);

#endif	//VARIABLE_H
