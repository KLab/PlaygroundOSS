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
#include <memory.h>
#include <stdio.h>
#include <varargs.h>

//------------------------------------------
//
// Helper Functions.
//
//------------------------------------------

void expand(int* count, void*** array_, void* newEntry) {
	// Get old information.
	void** oldArray = *array_;
	int oldCount	= *count;

	// Allocate new array and copy old array into new array.
	void** newArray = new void*[oldCount+1];
	if (oldArray) {
		memcpy(newArray,oldArray,oldCount * sizeof(void*));
	}

	// Add new element
	*count = (*count)+1;
	newArray[oldCount] = newEntry;

	// Delete old array
	if (oldArray) { delete[] oldArray; }
	*array_ = newArray;
}

extern int yylineno;
void compilerError(EnumError err, const char* format, int lineNumber) {
	int line = (lineNumber != -1) ? lineNumber : yylineno;
	const char* errorType;
	switch(err) {
	case ERR_NOT_SUPPORTED:
		errorType = "NOT SUPPORTED";
		break;
	case ERR_NOT_SUPPORTED_YET:
		errorType = "NOT SUPPORTED YET";
		break;
	case ERR_INTERNAL:
		errorType = "INTERNAL";
		break;
	case ERR_USER:
		errorType = "USER";
		break;
	default:
		errorType = "ERROR";
		break;
	}
	printf("[%s] Compiler Error",errorType);
	if(line != -1) {
		printf(" @line %i",line);
	}
	printf(" : %s%s\n",format,format[strlen(format) - 1] == '.' ? "" : ".");
}


SValue::SValue()
{
	pString = NULL;
	v.l = 0; // Fill memory with 0.
}

int SValue::operatorType(SValue &a, SValue &b)
{
	int default_ = 0;

	// In order !

	if ((a.type == TYPE_BOOL)  || (b.type == TYPE_BOOL ))	{ default_ = TYPE_BOOL;	}
	if ((a.type == TYPE_UINT)  || (b.type == TYPE_UINT ))	{ default_ = TYPE_UINT;	}
	if ((a.type == TYPE_INT )  || (b.type == TYPE_INT  ))	{ default_ = TYPE_INT;	}
	if ((a.type == TYPE_ULONG) || (b.type == TYPE_ULONG))	{ default_ = TYPE_ULONG;}
	if ((a.type == TYPE_LONG ) || (b.type == TYPE_LONG ))	{ default_ = TYPE_LONG; }
	if ((a.type == TYPE_FLOAT) || (b.type == TYPE_FLOAT))	{ default_ = TYPE_FLOAT;}
	if ((a.type == TYPE_DOUBLE)|| (b.type == TYPE_DOUBLE))	{ default_ = TYPE_DOUBLE;}

	return default_;
}

SValue SValue::ToType(int type) {
	SValue res;
	res.type = type;
	switch (type) {
	case TYPE_BOOL:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.i = this->v.i;
			break;
		case TYPE_INT:
			res.v.i = this->v.i ? 1 : 0;
			break;
		case TYPE_UINT:
			res.v.i = this->v.ui ? 1 : 0;
			break;
		case TYPE_LONG:
			res.v.i = this->v.l ? 1 : 0;
			break;
		case TYPE_ULONG:
			res.v.i = this->v.ul ? 1 : 0;
			break;
		case TYPE_FLOAT:
			res.v.i = (this->v.f != 0.0f) ? 1 : 0;
			break;
		case TYPE_DOUBLE:
			res.v.i = (this->v.d != 0.0f) ? 1 : 0;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_INT:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.i = this->v.i;
			break;
		case TYPE_INT:
			res.v.i = this->v.i;
			break;
		case TYPE_UINT:
			res.v.i = this->v.ui;
			break;
		case TYPE_LONG:
			res.v.i = (s32)this->v.l;
			break;
		case TYPE_ULONG:
			res.v.i = (s32)this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.i = (s32)this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.i = (s32)this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_UINT:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.ui = this->v.i;
			break;
		case TYPE_INT:
			res.v.ui = this->v.i;
			break;
		case TYPE_UINT:
			res.v.ui = this->v.ui;
			break;
		case TYPE_LONG:
			res.v.ui = (u32)this->v.l;
			break;
		case TYPE_ULONG:
			res.v.ui = (u32)this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.ui = (u32)this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.ui = (u32)this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_LONG:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.l = this->v.i;
			break;
		case TYPE_INT:
			res.v.l = this->v.i;
			break;
		case TYPE_UINT:
			res.v.l = this->v.ui;
			break;
		case TYPE_LONG:
			res.v.l = this->v.l;
			break;
		case TYPE_ULONG:
			res.v.l = this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.l = (s64)this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.l = (s64)this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_ULONG:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.ul = this->v.i;
			break;
		case TYPE_INT:
			res.v.ul = this->v.i;
			break;
		case TYPE_UINT:
			res.v.ul = this->v.ui;
			break;
		case TYPE_LONG:
			res.v.ul = this->v.l;
			break;
		case TYPE_ULONG:
			res.v.ul = this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.ul = (u64)this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.ul = (u64)this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_FLOAT:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.f = (float)this->v.i;
			break;
		case TYPE_INT:
			res.v.f = (float)this->v.i;
			break;
		case TYPE_UINT:
			res.v.f = (float)this->v.ui;
			break;
		case TYPE_LONG:
			res.v.f = (float)this->v.l;
			break;
		case TYPE_ULONG:
			res.v.f = (float)this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.f = this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.f = (float)this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	case TYPE_DOUBLE:
		switch (this->type) {
		case TYPE_BOOL:
			res.v.d = this->v.i;
			break;
		case TYPE_INT:
			res.v.d = this->v.i;
			break;
		case TYPE_UINT:
			res.v.d = this->v.ui;
			break;
		case TYPE_LONG:
			res.v.d = (double)this->v.l;
			break;
		case TYPE_ULONG:
			res.v.d = (double)this->v.ul;
			break;
		case TYPE_FLOAT:
			res.v.d = this->v.f;
			break;
		case TYPE_DOUBLE:
			res.v.d = this->v.d;
			break;
		default:
			compilerError(ERR_INTERNAL,"Internal type error conversion");
			break;
		}
		break;
	default:
		compilerError(ERR_INTERNAL,"Internal type error conversion");
		break;
	}
	return res;
}

Delegate::Delegate()
:Method()
,m_cppRepresentation	(NULL)
,m_csharpRepresentation	(NULL)
{
	m_type = new TypeObject();
	gGlobalClassID++;
}

/*virtual*/
int Delegate::getGenre() {
	return EGENRE::_DELEGATE;
}

/*virtual*/
const char* Delegate::getName() {
	if(m_cppRepresentation) {
		return m_cppRepresentation->m_name;
	}
	return m_name;
}

/*virtual*/
const char* Delegate::getFullName(NameSpace* ref) {
#ifdef __FULLNAMES__
	ref = gRootNameSpace;
#endif
	char buff[1000];
	const char* res = getOwner()->getFullName(ref);
	if (res[0] == 0) {
		sprintf(buff, "%s", this->getName());
	} else {
		sprintf(buff, "%s::_Delegate_Base_%s", res, this->getName());
	}
	return strdup(buff);
}

TypeObject* Delegate::getType() {
	if (m_type->m_typeID == TYPE_UNRESOLVED) {
		m_type->m_name					= m_name;
		m_type->m_definitionDelegate	= this;
		m_type->m_isGC_Able				= true;
		m_type->m_genreID				= EGENRE::_DELEGATE;
		m_type->m_name					= this->getName();
		m_type->m_typeID				= (EnumTypeObject)this->m_uniqueId;
		m_type->m_res.pSymbol			= this;
		m_type->m_res.pType				= m_type;
		m_type->m_res.symbolType		= EGENRE::_DELEGATE;
	}
	return m_type;
}

/*static*/ 
void DependancyMatrix::registerVariable(Variable* pVar, int domain) {
	// Insert at the end to have cleaner dump at the end.
	for (int n=0; n < 5; n++) {
		if (domain & (1<<n)) {
			Storage* p = new Storage();
			p->m_pSymbol	= pVar;
			p->m_next		= NULL;
			if (m_dependancyStorageEnd[n] == NULL) {
				m_dependancyStorage[n] = p;
			} else {
				m_dependancyStorageEnd[n]->m_next = p;
			}
			m_dependancyStorageEnd[n] = p;
		}
	}
}

void DependancyMatrix::registerAbstractContainer(AbstractContainer* pCnt, int domain) {
	// Insert at the end to have cleaner dump at the end.
	for (int n=0; n < 5; n++) {
		if (domain & (1<<n)) {
			Storage* p = new Storage();
			p->m_pSymbol	= pCnt;
			p->m_next		= NULL;
			if (m_dependancyStorageEnd[n] == NULL) {
				m_dependancyStorage[n] = p;
			} else {
				m_dependancyStorageEnd[n]->m_next = p;
			}
			m_dependancyStorageEnd[n] = p;
		}
	}
}

NameSpace* Delegate::getOwner() {
	if(m_cppRepresentation) {
		return m_cppRepresentation->m_pOwner;
	}
	return m_pOwner;
}

/*static*/ 
void DependancyMatrix::createDependancy(Variable* pVar, Variable* uses) {
	if (uses) {
		pVar->use(uses);
	} else {
		compilerError(ERR_INTERNAL, "Dependancy on null variable");
	}
}

/*static*/
void DependancyMatrix::createDependancy(AbstractContainer* pContainer, AbstractContainer* uses) {
	if(uses->m_noDump == false) {
		if (uses) {
			pContainer->use(uses);
		} else {
			compilerError(ERR_INTERNAL, "Dependancy on null abstract container");
		}
	}
	else {
		// Do not register the dependancy
	}
}

Variable* DependancyMatrix::popIndependantVariable(int domain) {
	return (Variable*)popIndependantSymbol(EGENRE::_VARIABLE, EGENRE::_VARIABLE, domain);
}

AbstractContainer* DependancyMatrix::popIndependantAbstractContainer(int domain) {
	return (AbstractContainer*)popIndependantSymbol(EGENRE::_ABSTRACTCONTAINER, EGENRE::_ABSTRACTCONTAINER, domain);
}

/*static*/ 
Symbol* DependancyMatrix::popIndependantSymbol(EGENRE genre, u32 mask, int domain) {
	for (int n=0; n < 5; n++) {
		if (domain & (1<<n)) {
			Storage* pStorage	= m_dependancyStorage[n];
			Storage* pPrev		= NULL;
			Symbol* result = NULL;

			// 1. Find independant variable if any.
			while (pStorage) {
				if (pStorage->m_pSymbol->getGenre() == genre) {
					if (!pStorage->m_pSymbol->stillUsing(mask)) {
						break;
					}
				}
				pPrev		= pStorage;
				pStorage	= pStorage->m_next; 
			}

			// 2. Remove from link list if found
			if (pStorage) {
				result = pStorage->m_pSymbol;
				if (pPrev) {
					pPrev->m_next = pStorage->m_next;
				} else {
					m_dependancyStorage[n] = pStorage->m_next;
				}

				delete pStorage;
			}

			// 3. Remove possible dependancy now that we export the variable.
			pStorage	= m_dependancyStorage[n];
			while (pStorage) {
				pStorage->m_pSymbol->unuse(result);
				pStorage	= pStorage->m_next; 
			}
			return result;
		}
	}
	return NULL;
}

/*static*/ 
void DependancyMatrix::clear() {
	for (int n=0; n < 5; n++) {
		Storage* pStore = m_dependancyStorage[n];
		while (pStore) {
			Storage* pNext = pStore->m_next;
			pStore->m_pSymbol->unuseAll();
			delete pStore;
			pStore = pNext;
		}
	}
}

Quals::Quals(u32 rank)
:m_pNext(NULL)
{
	this->rank = rank;
}

Quals* Quals::addQuals(u32 rank) {
	Quals* p		= this;
	while (p->m_pNext) {
		p	 = p->m_pNext;
	}

	p->m_pNext = new Quals(rank);
	return this;
}

Enum::Enum()
:m_list		(NULL)
,m_attribute(NULL)
,m_type		(NULL)
,m_parent	(NULL)
,m_modifier	(0)
{
	gGlobalClassID++;
}

/*virtual*/
int Enum::getGenre() {
	return EGENRE::_ENUM;
}

/*virtual*/
const char* Enum::getFullName(NameSpace* ref) {
#ifdef __FULLNAMES__
	ref = gRootNameSpace;
#endif
	char buff[1000];
	const char* res = (m_parent == ref) ? "" : m_parent->getFullName(ref);
	if (res[0] == 0) {
		sprintf(buff, "%s", this->getName());
	} else {
		sprintf(buff, "%s::%s", res, this->getName());
	}
	return strdup(buff);
}

Enum::EnumEntry::EnumEntry() 
:m_pNext		(NULL)
,m_pAttrib		(NULL)
,m_name			(NULL)
,m_expression	(NULL)
,m_parent		(NULL)
{
}

TypeObject* Enum::getType() {
	if (m_rtype.m_typeID == TYPE_UNRESOLVED) {
		if (m_type != NULL) {
			m_type->getResolvedType(this->m_parent);
		}
		m_rtype.m_definitionEnum	= this;
		m_rtype.m_isGC_Able			= false;
		m_rtype.m_genreID			= EGENRE::_ENUM;
		m_rtype.m_name				= this->getName();
		m_rtype.m_typeID			= (EnumTypeObject)this->m_uniqueId;
		m_rtype.m_res.pSymbol		= this;
		m_rtype.m_res.pType			= &m_rtype;
		m_rtype.m_res.symbolType	= EGENRE::_ENUM;
	}
	return &m_rtype;
}

void Enum::addEntry(Attribute* pAttri,const char* name, Expression* expr) {
	EnumEntry* pEntry = new EnumEntry();

	pEntry->m_name			= concat(name);
	if (expr) {
		if (expr->m_expressionType == EXPR_UNARYMINUS) {
			if (expr->m_expressions[0]->m_expressionType == EXPR_CTE) {
				expr->m_expressionType = EXPR_CTE;

				SValue v = expr->m_expressions[0]->m_value;

				switch (v.type) {
				case TYPE_INT:	v.v.i = -v.v.i; break;
				case TYPE_LONG:	v.v.l = -v.v.l; break;
				default:
					compilerError(ERR_INTERNAL,"Internal type error conversion");
					break;
				}

				expr->m_value = v;
			} else {
				compilerError(ERR_INTERNAL, "Wrong enum");
			}
		}

		if (expr->m_expressionType != EXPR_CTE) {
			compilerError(ERR_NOT_SUPPORTED_YET, "Does not support enum entries initialization different from CONSTANT INTEGER value.");
		}
	}

	pEntry->m_expression	= expr;
	pEntry->m_pAttrib		= pAttri;
	pEntry->m_parent		= this;

	if (m_list) {
		EnumEntry* p = m_list;
		while (p->m_pNext) {
			p = p->m_pNext;
		}
		p->m_pNext = pEntry;
	} else {
		m_list = pEntry;
	}
}

Enum::EnumEntry* Enum::findValue(const char* name)
{
	EnumEntry* pEnumEntry = m_list;
	while(pEnumEntry) {
		if (strcmp(pEnumEntry->m_name,name) == 0) {
			break;
		}
		pEnumEntry = pEnumEntry->m_pNext;
	}
	return pEnumEntry;
}

void		createAlias			(const char* alias, const char* originalName) {
	// 		
}

void		addUsingNameSpace	(const char* nameSpace) {
	gCurrentNameSpace->addUsing(nameSpace);
}

Accessor*	CreateAccessor		(Attribute* attribute, Statement* pStatement) {
	Accessor*	pAcc = new Accessor();
	pAcc->m_attribute = attribute;
	pAcc->m_statement = pStatement;
	return pAcc;
}

Accessor*	CreateAccessor		(Accessor* get_, Accessor* _set) {
	Accessor*	pAcc = new Accessor();
	pAcc->m_get = get_;
	pAcc->m_set = _set;
	return pAcc;
}

Enum*		CreateEnum			(Attribute* attribute, u32 modifier, const char* name, TypeObject* type) {
	return gCurrentNameSpace->addEnum(attribute, modifier, name, type);
}

Expression* CreateDelegateExpr(Variable* params, Statement* code) {
	char buff[200];
	sprintf(buff, "_anon_%i", gAnonymous++);
	Expression* pExpr = new Expression();

	// Create anon class and change name space, add it to the class
	AbstractContainer* anonClass = 	CreateClass(NULL, ATTRB_ANONDELEGATE, buff);
	// Pop back from anon name space.
	unuseNameSpace();

	pExpr->m_expressionType		= EXPR_DELEGATECREATE;
	pExpr->m_anonymousClass		= anonClass;
	pExpr->m_delegateSignature	= params;
	pExpr->m_delegateCode		= code;

	return pExpr;
}

Delegate*	CreateDelegate		(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Variable* params) {
	return gCurrentNameSpace->addDelegate(attribute, modifier, type, name, params);
}

SymbolDictionary::SymbolDictionary(SymbolDictionary* parent) : m_parent(parent), m_child(NULL) {
	m_list = new VariableList();
	m_list->content = NULL;
	m_list->pNext = NULL;
}

SymbolDictionary::~SymbolDictionary() {
	delete m_child;
	VariableList* toDestroy = m_list;
	VariableList* next;	
	while(toDestroy) {
		next = toDestroy->pNext;
		delete toDestroy;
		toDestroy = next;
	}
}

void SymbolDictionary::addVariable(Variable* var) {
	VariableList* pVarList = m_list;
	if(!pVarList->content) {
		pVarList->content = var;
	} else {
		while(pVarList->pNext) {
			pVarList = pVarList->pNext;
		}
		pVarList->pNext = new VariableList();
		pVarList->pNext->content = var;
	}
}

SymbolDictionary* SymbolDictionary::addDictionary() {
	SymbolDictionary* last= this;
	while(last->m_child) {
		last = last->m_child;
	}
	last->m_child = new SymbolDictionary(last);
	return last->m_child;
}

SymbolDictionary* SymbolDictionary::removeDictionary() {
	SymbolDictionary* last = this;
	SymbolDictionary* parent;
	while(last->m_child) {
		last = last->m_child;
	}
	parent = last->m_parent;
	delete last;
	if(parent) {
		parent->m_child = NULL;
	}
	return parent;
}

Variable* SymbolDictionary::findVariable(const char* name) {
	SymbolDictionary* pDictionary = this;
	while(pDictionary) {
		VariableList* pVarList = pDictionary->m_list;
		if(pVarList->content) {		//No need to check the list if it is empty
			while(pVarList){
				if(strcmp(pVarList->content->m_name, name)==0) {
					return pVarList->content;
				}
				pVarList = pVarList->pNext;
			}
		}
		pDictionary = pDictionary->m_parent;
	}
	return NULL;
}

ClassDictionary::ClassDictionary()
:count(0)
{
	classes	= new const char*[500];
	IDs		= new const char*[500];
}

void ClassDictionary::add(const char* name, const char* IDExpression) {
	if(count == 500) {
		compilerError(ERR_INTERNAL, "Maximum number of classes exceeded");
	}
	else {
		classes[count]	= concat(name);
		IDs[count]		= concat(IDExpression);
		count++;
	}
}

void useOrCreateNameSpace(Attribute* attribute, const char* nameSpace) {
	StringList* splitList = split(nameSpace);
	NameSpace* fNewWorkingSpace;
	NameSpace* pParentWorkSpace = gCurrentNameSpace;
	/*
	if(strcmp(splitList->content, "System") == 0) {
		g_noDump = true;
	}*/
	while(splitList) {
		fNewWorkingSpace = pParentWorkSpace->findNameSpace(splitList->content);
		if (!fNewWorkingSpace) {
			fNewWorkingSpace = new NameSpace();
			fNewWorkingSpace->setup(attribute, splitList->content);
			fNewWorkingSpace->m_noDump = g_noDump;
			pParentWorkSpace->addNameSpace(fNewWorkingSpace);
		}
		pParentWorkSpace = fNewWorkingSpace;
		splitList = splitList->pNext;
	}

	PushSpace(gCurrentNameSpace);
	gCurrentNameSpace = fNewWorkingSpace;
}

void unuseNameSpace		() {
	/*
	if(strcmp(gCurrentNameSpace->m_name, "System") == 0) {
		g_noDump = false;
	}*/
	gCurrentNameSpace = PopSpace();
	if (gCurrentNameSpace->m_bIsAbstract) {// Is abstract container
		gCurrentAC = (AbstractContainer*)gCurrentNameSpace;
		gCurrentAC->fixInheritance();
	}
}

const char* concat2(const char* a, const char* b) {
	char buff[1000];
	char* dst = buff;
	int strl = strlen(a);
	int strr = strlen(b);
	if (strl) { memcpy(buff, a, strl); dst += strl; }
	if (strr) { memcpy(dst, b, strr); dst += strr; }
	*dst = 0;
	return strdup(buff);
}

const char* concat3(const char* a, const char* b, const char* c) {
	char buff[1000];
	char* dst = buff;
	int strl = strlen(a);
	int strr = strlen(b);
	int str3 = strlen(c);
	if (strl) { memcpy(buff, a, strl); dst += strl; }
	if (strr) { memcpy(dst, b, strr); dst += strr; }
	if (str3) { memcpy(dst, c, str3); dst += str3; }
	*dst = 0;
	return strdup(buff);
}

const char* concat(const char* a) {
	return strdup(a);
}

void traceFunc(int line, int input, const char* token) {
	fprintf(stderr,"Rule Y@%i Input:%i Token:%s\n",line, input,token);
}

NameSpace*	nameSpaceStack[100];
int			nameSpaceStackIndex	= 0;
void		PushSpace(NameSpace* p) {	nameSpaceStack[nameSpaceStackIndex++] = p;		}
NameSpace*	PopSpace()				{	return nameSpaceStack[--nameSpaceStackIndex];	}

void display (const char* str)
{
	//printf("%s\n",str);
}

StringList*	split (const char* str)
{
	if(!str) {
		return NULL;
	}
	StringList* head = new StringList();
	StringList* current = head;
	char buf[100];
	buf[0] = 0;
	char* ptr = buf;
	for(int i = 0 ; str[i] ; i++) {
		if(str[i] == '.') {
			*ptr = 0;
			current->content = (char*)concat(buf);
			current = current->pNext = new StringList();
			ptr = buf;
		}
		else {
			*ptr++ = str[i];
		}
	}
	*ptr = 0;
	current->content = (char*)concat(buf);
	return head;
}

void resetLocalFileInfo() {
	// Reset Temp String Concat allocation.
	// Reset Using list.
	// Reset Alias list.
}

bool checkEntryPoint(u32 compilerOptions) {
	AbstractContainer* pProgram = (AbstractContainer*)(gRootNameSpace->findNameSpace("Program"));
	if(compilerOptions & COMPIL_USE_FRAMEWORK) {
		if(pProgram) {
			if(pProgram->m_accessorCount	!= 0
			|| pProgram->m_delegateCount	!= 0
			|| pProgram->m_enumCount		!= 0
			|| pProgram->m_memberCount		!= 0
			|| pProgram->m_methodCount		> 1) {
				compilerError(ERR_USER, "The Program class should only contain a static method named start", pProgram->m_line);
				return false;
			}
			Method* pStart = pProgram->findMethod("start", (Expression*)NULL, NULL);
			if(pStart) {
				if((pStart->m_modifier & ATT_STATIC) == 0) {
					compilerError(ERR_USER, "Program::start() should be static", pProgram->m_line);
					return false;
				}
				return true;
			}
			compilerError(ERR_USER, "start() entry point was not found in the Program class", pProgram->m_line);
			return false;
		}
		compilerError(ERR_USER, "Entry point was not found. There should be a class named Program, with a static start() method");
		return false;
	}
	if(pProgram) {
		compilerError(ERR_USER, "There should be a Program class only if the program is called by the game engine");
		return false;
	}
	return true;
}

void generateOutput(const char* outputPath, u32 compilerOptions) {
	bool isFramework	= (compilerOptions & COMPIL_IS_FRAMEWORK)	!= 0;
	bool useFramework	= (compilerOptions & COMPIL_USE_FRAMEWORK)	!= 0;

	if(checkEntryPoint(compilerOptions)) {

		if(outputPath) {
			freopen(isFramework ? concat2(outputPath, "framework.h") : outputPath, "w", stdout);
		}

		if(isFramework) {
			exportFrameworkHeader();
		}
		else if(useFramework) {
			printf("#include \"framework.cpp\"\n\n");
		}
		else {
			exportRuntimeIncludes();
			printf("\n");
		}

		// Parser complete, gCurrentNameSpace is current.
		gCurrentNameSpace = NULL;
		exportConstants();

		exportNameSpaceHeader(gRootNameSpace, false);
		exportPrototypes();

		if(isFramework) {
			exportFrameworkFooter();
			if(outputPath) {
				freopen(concat2(outputPath, "framework.cpp"), "w", stdout);
			}
			printf("#include \"framework.h\"\n\n");
		}
		
		exportNameSpaceImplementation(gRootNameSpace);
		registerGCWorld(gRootNameSpace, compilerOptions);

		if(outputPath && !isFramework) {
			exportInlineFiles(pathName(outputPath), gClassDictionary);
		}
	}
}


SValue registerString(SValue v) {
	static int gStringCounter = 0;

	// ==> We do constant pool factorization.

	// Find if string is already in the list or not.
	StringID* pList = gStrList;
	while (pList) {
		if (strcmp(pList->m_str, v.v.str) == 0) {
			v.pString = pList;
			return v;
		}
		pList = pList->m_next;
	}

	StringID* pID = new StringID();
	pID->m_id = gStringCounter++;
	pID->m_str = v.v.str;
	pID->m_next = gStrList;
	pID->m_isDumped = !g_noDump;
	gStrList = pID;
	v.pString = pID;
	return v;
}

// Fills out_namespace and out_method with the appropriate contexts for the symbol resolution.
void getContext(Symbol* symbol, NameSpace*& out_namespace, Method*& out_method) {
	switch(symbol->getGenre()) {
	case EGENRE::_ABSTRACTCONTAINER:
		out_namespace = (AbstractContainer*)symbol						; out_method = NULL;
		break;
	case EGENRE::_ACCESSOR:
		out_namespace = ((Accessor*)symbol)->m_ownerClass				; out_method = NULL;
		break;
	case EGENRE::_DELEGATE:
		out_namespace = ((Delegate*)symbol)->getOwner()					; out_method = NULL;
		break;
	case EGENRE::_ENUM:
		out_namespace = ((Enum*)symbol)->m_parent						; out_method = NULL;
		break;
	case EGENRE::_ENUMENTRY:
		out_namespace = ((Enum::EnumEntry*)symbol)->m_parent->m_parent	; out_method = NULL;
		break;
	case EGENRE::_METHOD:
		out_namespace = ((Method*)symbol)->m_pOwner						; out_method = (Method*)symbol;
		break;
	case EGENRE::_NAMESPACE:
		out_namespace = (NameSpace*)symbol								; out_method = NULL;
		break;
	case EGENRE::_VARIABLE:
	{
		AbstractContainer* pOwner = ((Variable*)symbol)->m_ownerClass;
		out_namespace = pOwner ? pOwner : gCurrentMethod->m_pOwner		; out_method = pOwner ? NULL : gCurrentMethod;
	}
		break;
	default:
		compilerError(ERR_INTERNAL, "Unknowm symbol type", symbol->m_line);
		out_namespace = NULL ; out_method = NULL;
		break;
	}
}

//Resolves a symbol which is not composed
SRSymbol resolveSimpleSymbol(SRSymbol baseContext, const char* name, u8 searchMask, Expression* methodSignature, Variable* delegateSignature, TypeGenericEntry* genParams) {
	Variable*					varRes		= NULL;
	Accessor*					accessorRes	= NULL;
	Method*						methodRes	= NULL;
	TypeGenericDefinitionEntry*	genericRes	= NULL;

	SRSymbol result;
	result.symbolType	= EGENRE::_UNDEFGENRE;
	result.pSymbol		= createNotFoundSymbol();

	if (baseContext.symbolType == EGENRE::_ABSTRACTCONTAINER) {
		//Search in the local variables
		AbstractContainer* contextAC = (AbstractContainer*)baseContext.pSymbol;

		// Search in the dictionaries
		if(searchMask & SEARCH_VARIABLE) {
			varRes = gCurrentSD->findVariable(name);
			if(varRes) {
				result.pSymbol		= varRes;
				result.symbolType	= EGENRE::_VARIABLE;
				return result; // Early return
			}
		}

		// Search in the local generic symbols
		if((searchMask & SEARCH_TYPE) && baseContext.symbolType == EGENRE::_METHOD) {
			Method* pMethod = (Method*)baseContext.pSymbol;
			genericRes = pMethod->findGenericSymbol(name);
			if(genericRes) {
				result.pSymbol		= genericRes;
				result.symbolType	= EGENRE::_GENDEFENTRY;
				return result;
			}
		}

		//Search in the class members
		if(searchMask & SEARCH_MEMBER) {
			varRes = contextAC->findMember(name);
			if(varRes) {
				result.pSymbol		= varRes;
				result.symbolType	= EGENRE::_MEMBER;
				return result;
			}
		}

		//Search in the properties
		if(searchMask & SEARCH_PROPERTY) {
			accessorRes = contextAC->findProperty(name);
			if(accessorRes) {
				result.pSymbol		= accessorRes;
				result.symbolType	= EGENRE::_ACCESSOR;
				return result;
			}
		}

		//Search in the methods
		if(searchMask & SEARCH_FUNCTION) {
			if(methodSignature) {
				methodRes = contextAC->findMethod(name, methodSignature, genParams);
			} else if(delegateSignature) {
				methodRes = contextAC->findMethod(name, delegateSignature, genParams);
			} else {
				methodRes = contextAC->findMethod(name, (Variable*)NULL, NULL);
			}
			if(methodRes) {
				result.pSymbol		= methodRes;
				result.symbolType	= (EGENRE)methodRes->getGenre();
				return result;
			}
		}

		// =================================================
		//   Inheritance method / member / field
		// =================================================

		//Search in the parent class / interfaces
		if(searchMask & SEARCH_INHERITANCE) {
			int n=0;
			while (n < contextAC->m_inheritancesCount) {
				TypeObject* pType = contextAC->m_inheritances[n];
				pType->getResolvedType(contextAC);
				SRSymbol input;
				input.symbolType	= EGENRE::_ABSTRACTCONTAINER;
				input.pSymbol		= pType->m_definitionAC;
				SRSymbol symbolRes  = resolveSimpleSymbol(input, name ,searchMask & ~SEARCH_HIERARCHY & ~SEARCH_TYPE, methodSignature, delegateSignature, genParams);
				if (symbolRes.symbolType != EGENRE::_UNDEFGENRE) {
					return symbolRes;
				}
				n++;
			}
		}

		//Search in the embedding class
		if((searchMask & SEARCH_HIERARCHY) && contextAC->m_pParent->getGenre() == EGENRE::_ABSTRACTCONTAINER) {	//Search in classes only
			SRSymbol input;
			input.symbolType	= EGENRE::_ABSTRACTCONTAINER;
			input.pSymbol		= (AbstractContainer*)contextAC->m_pParent;
			SRSymbol symbolRes = resolveSimpleSymbol(input, name, searchMask & ~SEARCH_TYPE, methodSignature, delegateSignature, genParams);
			if (symbolRes.symbolType != EGENRE::_UNDEFGENRE) {
				return symbolRes;
			}
		}
	}

	// =================================================
	//   End Inheritance method / member / field
	// =================================================

	// Look for a type (different search as it can come from a using)
	if ((searchMask & SEARCH_TYPE) && ((baseContext.symbolType == EGENRE::_ABSTRACTCONTAINER) || (baseContext.symbolType == EGENRE::_NAMESPACE))) {
		NameSpace* pSpace = (NameSpace*)baseContext.pSymbol;
		Symbol* symbolRes = pSpace->resolve(name);
		if (symbolRes) {
			SRSymbol result;
			result.symbolType	= (EGENRE)symbolRes->getGenre();
			result.pSymbol		= symbolRes;
			return result;
		}
	}

	//Look for a value in an enum type
	if (baseContext.symbolType == EGENRE::_ENUM) {
		Enum* contextEnum = (Enum*)baseContext.pSymbol;
		SRSymbol result;
		result.symbolType = EGENRE::_ENUMENTRY;
		result.pSymbol = contextEnum->findValue(name);
		return result;
	}

	return result;
}

// Returns true if argList1 is a better function member than argList2 for the signature
bool isBetterFunctionMember(Variable* argList1, Variable* argList2, Expression* signature) {
	if(signature->m_expressionType != EXPR_LIST) {
		compilerError(ERR_INTERNAL, "Signature is expected to be a list expression", signature->m_line);
		return false;
	}
	bool hasFoundBetter = false;
	Variable* pArg1		= argList1;
	Variable* pArg2		= argList2;
	for(int n = 0 ; n < signature->m_expressionCount ; n++, pArg1 = pArg1->m_pNextVariable, pArg2 = pArg2->m_pNextVariable) {
		if(!pArg1) {
			return false; 
		}
		// Handle default args (expr != NULL)
		if(pArg1->m_expression == NULL && pArg2->m_expression != NULL) {
			// Default arg
			return true;
		}
		if(pArg1->m_expression != NULL && pArg2->m_expression == NULL) {
			// Default arg
			return false;
		}
		Expression* pArg	= signature->m_expressions[n];	
		if(pArg->m_runtimeType->m_genreID == EGENRE::_ENUM) {
			// Special case : 0 passed as a parameter for an enum
			if(pArg1->m_type->m_genreID == EGENRE::_ENUM && 
			(pArg2->m_expression->m_expressionType == EXPR_CTE) && (pArg2->m_value.v.i == 0)) {
				hasFoundBetter = true;
			}
			if(pArg2->m_type->m_genreID == EGENRE::_ENUM && 
			(pArg1->m_expression->m_expressionType == EXPR_CTE) && (pArg1->m_value.v.i == 0)) {
				return false;
			}
		}
		ECOMPARISON comparison = compareConversions(pArg->m_runtimeType, pArg1->m_type, pArg2->m_type);
		if(comparison == ECOMPARISON::COMP_BETTER) {
			hasFoundBetter = true;
		}
		else if(comparison == ECOMPARISON::COMP_WORSE) {
			return false;
		}
	}
	return hasFoundBetter;
}

bool isBetterFunctionMember(Variable* argList1, Variable* argList2, Variable* signature) {
	bool hasFoundBetter = false;
	Variable* pArg1		= argList1;
	Variable* pArg2		= argList2;
	for(Variable* pSign = signature ; pSign ; pSign = pSign->m_pNextVariable, pArg1 = pArg1->m_pNextVariable, pArg2 = pArg2->m_pNextVariable) {
		// Handle default args (expr != NULL)
		if(pArg1->m_expression == NULL && pArg2->m_expression != NULL) {
			// Default arg
			return true;
		}
		if(pArg1->m_expression != NULL && pArg2->m_expression == NULL) {
			// Default arg
			return false;
		}
		if(pSign->m_type->m_genreID == EGENRE::_ENUM) {
			// Special case : 0 passed as a parameter for an enum
			if(pArg1->m_type->m_genreID == EGENRE::_ENUM && 
			(pArg2->m_expression->m_expressionType == EXPR_CTE) && (pArg2->m_value.v.i == 0)) {
				hasFoundBetter = true;
			}
			if(pArg2->m_type->m_genreID == EGENRE::_ENUM && 
			(pArg1->m_expression->m_expressionType == EXPR_CTE) && (pArg1->m_value.v.i == 0)) {
				return false;
			}
		}
		ECOMPARISON comparison = compareConversions(pSign->m_type, pArg1->m_type, pArg2->m_type);
		if(comparison == ECOMPARISON::COMP_BETTER) {
			hasFoundBetter = true;
		}
		else if(comparison == ECOMPARISON::COMP_WORSE) {
			return false;
		}
	}
	return hasFoundBetter;
}

EMATCH compareSignatures(Variable* argList, Expression* signature) {
	bool identical = true;
	if(signature == NULL) {
		if(!argList) {
			return EMATCH::M_IDENTICAL;
		}
		if(argList->m_expression) {
			return EMATCH::M_APPLICABLE;
		}
		return EMATCH::M_MISMATCH;
	}
	if(argList == NULL) {
		if(signature->m_expressionCount == 0) {
			return EMATCH::M_IDENTICAL;
		}
		return EMATCH::M_MISMATCH;
	}
	Variable* pMethodArg = argList;
	for(int n = 0 ; n < signature->m_expressionCount ; n++, pMethodArg = pMethodArg->m_pNextVariable)
	{
		if(!pMethodArg) { 
			return EMATCH::M_MISMATCH; 
		}
		Expression* pExpr = signature->m_expressions[n];
		TypeObject* argType = pMethodArg->m_type;
		TypeObject* signatureType = NULL;

		if(pMethodArg == NULL) {
			return EMATCH::M_MISMATCH;
		}
		if(((pMethodArg->m_modifier & ATT_REF) != 0) && pExpr->m_expressionType != EXPR_REF) {
			return EMATCH::M_MISMATCH;
		}
		if(argType->m_genreID == EGENRE::_ENUM) {
			// 0 can be implicitly converted to any enum.
			if(pExpr->m_expressionType == EXPR_CTE && pExpr->m_value.v.i == 0) {
				identical = false;
				signatureType = NULL;
				continue;
			}
			else if(pExpr->m_runtimeType->m_definitionEnum == argType->m_definitionEnum) {
				continue;
			}
			else {
				return EMATCH::M_MISMATCH;
			}
		}
		if(argType->isGC_Able() && pExpr->m_expressionType == EXPR_CTE && pExpr->m_value.v.i == 0) {
			// null pointer
			identical = false;
			signatureType = NULL;
		}
		else if(pExpr->m_expressionType == EXPR_REF) {
			if((pMethodArg->m_modifier & ATT_REF) == 0) {
				return EMATCH::M_MISMATCH;
			}
			signatureType = pExpr->m_expressions[0]->m_runtimeType;
		}
		else {
			signatureType = pExpr->m_runtimeType;
		}
		if(signatureType) {
			if(signatureType->m_typeID != argType->m_typeID) {
				if(signatureType->hasImplicitConversion(argType)) {
					identical = false;
				}
				else {
					return EMATCH::M_MISMATCH;
				}
			}
			else if(signatureType->m_typeID == TYPE_ARRAY) {
				if(signatureType->hasImplicitConversion(argType)) {
					continue;
				}
				else {
					return EMATCH::M_MISMATCH;	
				}
			}
			else if(signatureType->hasCompatibleGenerics(argType, &identical)) {
				continue;
			}
			else {
				return EMATCH::M_MISMATCH;
			}
		}
	}
	if(identical && pMethodArg == NULL) {
		return EMATCH::M_IDENTICAL;
	}
	return EMATCH::M_APPLICABLE;
}

EMATCH compareSignatures(Variable* argList, Variable* signature) {
	bool identical = true;
	if(signature == NULL || argList == NULL) {
		if(signature == NULL && argList == NULL) {
			return EMATCH::M_IDENTICAL;
		}
		return EMATCH::M_MISMATCH;
	}
	Variable* pMethodArg = argList;
	for(Variable* pSign = signature ;  pSign ;  pSign = pSign->m_pNextVariable, pMethodArg = pMethodArg->m_pNextVariable)
	{
		TypeObject* signatureType = pSign->m_type;
		TypeObject* argType = pMethodArg->m_type;
		if(pMethodArg == NULL) {
			return EMATCH::M_MISMATCH;
		}
		if((pMethodArg->m_modifier & ATT_REF) != (pSign->m_modifier & ATT_REF)) {
			return EMATCH::M_MISMATCH;
		}
		if(argType->m_genreID == EGENRE::_ENUM) {
			// 0 can be implicitly converted to any enum.
			if(pSign->m_expression && pSign->m_expression->m_expressionType == EXPR_CTE && pSign->m_expression->m_value.v.i == 0) {
				identical = false;
				signatureType = NULL;
				continue;
			}
			else if(signatureType->m_definitionEnum == argType->m_definitionEnum) {
				continue;
			}
			else {
				return EMATCH::M_MISMATCH;
			}
		}
		if(argType->isGC_Able() && pSign->m_expression && pSign->m_expression->m_expressionType == EXPR_CTE && pSign->m_expression->m_value.v.i == 0) {
			// null pointer
			identical = false;
			signatureType = NULL;
		}
		else if(signatureType->m_typeID != argType->m_typeID) {
			if(signatureType->hasImplicitConversion(argType)) {
				identical = false;
			}
			else {
				return EMATCH::M_MISMATCH;
			}
		}
		else if(signatureType->m_typeID == TYPE_ARRAY) {
			if(signatureType->hasImplicitConversion(argType)) {
				continue;
			}
			else {
				return EMATCH::M_MISMATCH;	
			}
		}
	}
	if(identical && pMethodArg == NULL) {
		return EMATCH::M_IDENTICAL;
	}
	return EMATCH::M_APPLICABLE;
}

//
// Replaces <<T>> by classList elements and <BODY> by the associated methodBody element.
//
// Sample :
// const char* templateList = "template<> struct __InternalUtilsGetTypeID<<T>> { ";
// const char* bodyCsteList = "static u32 getIt() { return <BODY>; }";
// const char* templateEndList = " };";
//
bool templateClassSpecializationDumpForOneGenericType(const char** templateList, const char** bodyCsteList, const char** templateEndList, u32 templateListLength, const char** classList, const char** classBody, u32 classListLenght) {
	for(u32 i_template = 0; i_template < templateListLength; ++i_template) {
		for(u32 i_class = 0; i_class < classListLenght; ++i_class) {
			const char* t = templateList[i_template];
			const char* c = classList[i_class];
			// template part (until open bracket).
			while(*t != '\0') {
				if(*t == '\\') {
					t++;
				} else {
					if(*t == '<') {
						t++;
						if(*t=='<') {
							// Replace <<T>> by <ClassName1, ClassName2, ClassName3>
							printf("<%s", c);
							t += 2;
							if(*t == '>' && *(t+1) == '>') {
								printf(">");
								t += 2;
							} else {
								return false;
							}
						} else if(*t == 'T' && *(t+1) == '>') {
							// replace <T> by ClassName
							printf("%s", c);
							t += 2;
						} else {
							printf("<%c", *t++);
						}
					} else {
						printf("%c", *t++);
					}
				}
			}

			// method body
			t = bodyCsteList[i_template];
			while(*t != '\0') {
				if(*t == '\\') {
					t++;
				} else {
					if(*t == '<' && *(t+1) == 'B' && *(t+2) == 'O' && *(t+3) == 'D' && *(t+4) == 'Y' && *(t+5) == '>') {
						// Replace <BODY> by methodBody
						printf("%s", classBody[i_class]);
						t+= 6;
					} else {
						printf("%c", *t++);
					}
				}
			}
			printf("%s\n", templateEndList[i_template]);
		}
	}

	return true;
}

// Returns the path without its file.
const char* pathName(const char* path)
{
	char buf[500];
	int i = strlen(path);
	for(; i >= 0 && path[i] != '\\' ; i--);
	if(path[i] == '\\')
	{
		memcpy(buf, path, (++i)*sizeof(char));
		buf[i] = 0;
		return strdup(buf);
	}
	return strdup(path);
}

// TODO force enum to have only direct constant expression --> More complex expression are forbidden for dependancy reason.
bool				g_forArgument		= false;
bool				g_noDump			= false;
bool				g_registerClasses	= false;
bool				g_unsafe			= false;
bool				g_unsafeEphemeral	= false;
bool				g_analysis_static	= false;
bool				gIsStaticFunc		= false;
bool				gTransformAsDelegate= false;

int					gGlobalClassID		= 0;
int					gSwitchCount		= 0;
int					gAnonymous			= 0;
Variable*			gCurrVar			= NULL;
Method*				gCurrentMethod		= NULL;
AbstractContainer*	gCurrentAC			= NULL;
Enum*				gCurrEnum			= NULL;
StringID*			gStrList			= NULL;
SymbolDictionary*	gCurrentSD			= NULL;
TypeObject*			gReturnType			= NULL;

NameSpace*			gRootNameSpace		= (new NameSpace())->setup(0,"");
NameSpace*			gCurrentNameSpace	= gRootNameSpace;
AbstractContainer*	gStaticContextAC	= NULL;
DependancyMatrix*	gStaticDepMatrix	= new DependancyMatrix();
ClassDictionary*	gClassDictionary	= new ClassDictionary();

DependancyMatrix::Storage* DependancyMatrix::m_dependancyStorage[]		= { NULL, NULL, NULL, NULL, NULL };
DependancyMatrix::Storage* DependancyMatrix::m_dependancyStorageEnd[]	= { NULL, NULL, NULL, NULL, NULL };

//
// DO NOT PUT CODE HERE, all global variable instance at the end of this file.
//
