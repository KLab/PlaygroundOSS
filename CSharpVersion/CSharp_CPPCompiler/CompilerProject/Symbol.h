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
#ifndef SYMBOL_H
#define SYMBOL_H

#include "BaseType.h"


class NameSpace;

class Symbol {
public:
	Symbol();
	~Symbol();

	void	use					(Symbol* v);
	void	unuse				(Symbol* v);
	bool	stillUsing			(u32 mask = 0xFFFF);
	void	unuseAll			();
	void	markSetupDependancy	();

	virtual int			getGenre() { return EGENRE::_UNDEFGENRE; }
//	virtual TypeObject*	getSymbolType() = 0;
	virtual const char*	getName	();
	virtual const char* getFullName(NameSpace* ref = NULL)
	{
		compilerError(ERR_INTERNAL,"Internal Error : invalid getFullName");
		return NULL;
	}
	void		setName	(const char* name);

	u32			m_stdAttribute;
	const char*	m_name;
	Symbol*		m_pNext;
	Symbol*		m_pAlias;
	u32			m_uniqueId;
	u32			m_line;
protected:
	struct Dependancy {
		Dependancy*	m_pNext;
		Symbol*		m_uses;
	};
	Dependancy*	m_dependancyList;
};

Symbol* createNotFoundSymbol();

#endif	//SYMBOL_H
