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
#ifndef __COMPILER_FRAMEWORK_H
#define __COMPILER_FRAMEWORK_H

#define __NOTRACE__
#define	__FULLNAMES__

#include "BaseType.h"
#include "Variable.h"
#include "NameSpace.h"
#include "TypeObject.h"

void lex_in_generic();
void lex_out_generic();

// -----------------------------------------------------------------------
//  Definition of classes
// -----------------------------------------------------------------------

enum OPOVERRIDE {
	OPOVR_INDEXER			= 0x00000001,
	// +   -   !   ~   ++   --   true   false
	OPOVR_UNARYPLUS			= 0x00000002,
	OPOVR_UNARYMINUS		= 0x00000004,
	OPOVR_UNARYNOT			= 0x00000008,
	OPOVR_UNARYNEG			= 0x00000010,
	OPOVR_UNARYPLUSPLUS		= 0x00000020,
	OPOVR_UNARYMINUSMINUS	= 0x00000040,
	OPOVR_UNARYTRUE			= 0x00000080,
	OPOVR_UNARYFALSE		= 0x00000100,
	// +   -   *   /   %   &   |   ^   <<   >>   ==   !=   >   <   >=   <=
	OPOVR_BINARYPLUS		= 0x00001000,
	OPOVR_BINARYMINUS		= 0x00002000,
	OPOVR_BINARYMULT		= 0x00004000,
	OPOVR_BINARYDIV			= 0x00008000,
	OPOVR_BINARYMOD			= 0x00010000,
	OPOVR_BINARYAND			= 0x00020000,
	OPOVR_BINARYOR			= 0x00040000,
	OPOVR_BINARYXOR			= 0x00080000,
	OPOVR_BINARYLSHFT		= 0x00100000,
	OPOVR_BINARYRSHFT		= 0x00200000,
	OPOVR_BINARYEQU			= 0x00400000,
	OPOVR_BINARYDIFF		= 0x00800000,
	OPOVR_BINARYGREATER		= 0x01000000,
	OPOVR_BINARYLESSER		= 0x02000000,
	OPOVR_BINARYGREATEREQ	= 0x04000000,
	OPOVR_BINARYLESSEREQ	= 0x08000000,
};

class Uses {
public:
	Uses();
	~Uses();

	void		addNameSpace			(Symbol* nameSpace);

	Symbol**	m_uses;
	u32			m_useCount;
};

class Argument : public Variable {
public:
	u32					mode;	// By reference, in, out, ....
	TypeObject*			type;
	const char*			name;
};


class Accessor : public Symbol {
public:
	Accessor();
	~Accessor();
	virtual int getGenre();

	void setAsIndexer(TypeObject* type, Variable* signature) {
		m_type		= type;
		m_variable	= signature;
	}
	void dumpParams(bool call, bool addComma = false);

	Attribute*	m_attribute;
	TypeObject*	m_type;
	Accessor*	m_get;
	Accessor*	m_set;
	Indexer*	m_indexer;
	Statement*	m_statement;
	AbstractContainer* m_ownerClass;
	Variable*	m_variable;
	u32			m_modifier;
};

class Method : public Symbol {
public:
	Method();
	virtual int					getGenre();
	virtual const char*			getName();

	void						setupHasDefaultParams();
	void						resolveDefaultParams();
	void						setGenericParam();
	TypeObject*					getGenericType(TypeGenericDefinitionEntry* genericSymbol, TypeGenericEntry* genericParams);	
	const char*					getTemplateParams();
	void						dumpTemplateLabel();
	const char*					getGenCallParams();
	void						preFunc();
	void						dumpMarshalling();
	void						dumpParamsDef();
	void						dumpParamsDef(char* buffer, bool doCall, bool dumpDefault);
	void						dumpCall(Expression* expr, bool delegateCall, TypeGenericEntry* genericParams);

	bool						analyzeRef();
	inline Attribute*			getAttr() { return m_attribute; }

	TypeGenericDefinitionEntry*	findGenericSymbol(const char* name); 

	Attribute*					m_attribute;
	Variable*					m_parameters;
	TypeObject*					m_returnType;
	Statement*					m_codeBlock;
	u32							m_modifier;
	u32							m_referenceModifCount;
	AbstractContainer*			m_pOwner;
	Expression*					m_initializerOpt;
	s32							m_initializerType;
	TypeGenericDefinitionEntry*	m_genericParam;
	bool						m_bResolvedParam;
};

class MethodList : public Method {
public:
	Method*		m_method;
	MethodList*	m_nextMethod;
	int			m_count;

	MethodList(Method* head = NULL);
	virtual int getGenre();
	void add(Method* method);
};

// Delegate is just a disguised Method
class Delegate : public Method {
public:
	Delegate();
	virtual int getGenre();
	virtual const char*	getName();
	virtual const char* getFullName(NameSpace* ref);
	NameSpace*	getOwner();

	const char*	generateTypeID();
	void		dumpDefinition(const char* prefix);
	TypeObject*	getType();

	TypeObject* m_type;	
	Delegate*	m_cppRepresentation;
	Delegate*	m_csharpRepresentation;
};

class Enum : public NameSpace {
public:
	Enum();
	TypeObject*	getType();
	virtual int getGenre();
	virtual const char* getFullName(NameSpace* ref = NULL);
	static inline const char* substitute() { return "s32"; }

	class EnumEntry : public Symbol {
	public:
		EnumEntry();

		EnumEntry*	m_pNext;
		Attribute*	m_pAttrib;
		const char*	m_name;
		Expression*	m_expression;
		Enum*		m_parent;
	};

	void	addEntry(Attribute* pAttrib, const char* name, Expression* pExpr);
	EnumEntry* findValue(const char* name);

	EnumEntry*	m_list;
	Attribute*	m_attribute;
	u32			m_modifier;
	TypeObject*	m_type;
	TypeObject	m_rtype;
	NameSpace*	m_parent;
};

class StringList {
public:
	char* content;
	StringList* pNext;

	inline StringList() : content(NULL), pNext(NULL) {}
	inline ~StringList() {
		delete[] content;
		delete pNext;
	}
};

class Quals {
public:
	Quals(u32 rank);
	Quals* addQuals(u32 rank);

	u32 rank;
	Quals*	m_pNext;
};

//
// TODO : refactory the dependancy class into a template and instances for each use cases.
//
class DependancyMatrix {
public:
	static void clear						();
	static void registerVariable			(Variable* pVar, int domain = 1);
	static void createDependancy			(Variable* pVar, Variable* uses);
	static void createDependancy			(AbstractContainer* pContainer, AbstractContainer* uses);
	static Variable* popIndependantVariable	(int domain = 1);
	static AbstractContainer* popIndependantAbstractContainer	(int domain = 2);
	static void registerAbstractContainer	(AbstractContainer* pCnt, int domain = 2);
	static inline bool hasRemainingAC		() { return (m_dependancyStorage[1] != NULL); }
private:
	static Symbol* popIndependantSymbol		(EGENRE genre, u32 mask, int domain = 1);
	struct Storage {
		Storage*	m_next;
		Symbol*		m_pSymbol;
	};
	static Storage*		m_dependancyStorage[5];
	static Storage*		m_dependancyStorageEnd[5];
};

class SymbolDictionary {
public :
	typedef struct VariableList{
		Variable* content;
		VariableList* pNext;
	}VariableList;

	SymbolDictionary*	m_parent;
	SymbolDictionary*	m_child;
	VariableList*		m_list;

	SymbolDictionary(SymbolDictionary* parent = NULL);
	~SymbolDictionary();
	void addVariable(Variable* var);
	SymbolDictionary* addDictionary();		//returns the new dictionary
	SymbolDictionary* removeDictionary();	//returns the parent
	Variable* findVariable(const char*);
};

struct ClassDictionary {
public :
	const char**	classes;
	const char**	IDs;
	int				count;

	ClassDictionary();
	void add(const char* name, const char* IDExpression);
};

//
// Helper Functions.
//

Expression*	CreateDelegateExpr	(Variable* params, Statement* pStatement);
Delegate*	CreateDelegate		(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Variable* params);
Accessor*	CreateAccessor		(Attribute* attribute, Statement* pStatement);
Accessor*	CreateAccessor		(Accessor* get_, Accessor* _set);
Indexer*	CreateIndexer		(TypeObject* type, Variable* variable);
Enum*		CreateEnum			(Attribute* attribute, u32 modifier, const char* name, TypeObject* type);
void		useOrCreateNameSpace(Attribute* attribute, const char* nameSpace);
void		unuseNameSpace		();

void		createAlias			(const char* alias, const char* originalName);
void		addUsingNameSpace	(const char* nameSpace);
const char* concat(const char* a);
const char* concat2(const char* a, const char* b);
const char* concat3(const char* a, const char* b, const char* c);

void		traceFunc			(int line, int inputline, const char* token);
void		tab					();
NameSpace*	PopSpace			();
void		PushSpace			(NameSpace* newCurrentSpace);

void		display				(const char* str);	//used for debugging
StringList*	split				(const char* str);	//splits an "A.B.C" string into an A->B->C chain.

extern  NameSpace*			gRootNameSpace;
extern	AbstractContainer*	gStaticContextAC;
extern	AbstractContainer*	gCurrentAC;
extern  Method*				gCurrentMethod;
extern	Enum*				gCurrEnum;
extern	Variable*			gCurrVar;
extern  TypeObject*			gReturnType;
extern	int					depth;
extern  int					gGlobalClassID;
extern  int					gSwitchCount;
extern  int					gAnonymous;
extern  bool				g_unsafe;
extern  bool				g_unsafeEphemeral;
extern	StringID*			gStrList;
extern	SymbolDictionary*	gCurrentSD;
extern  DependancyMatrix*	gStaticDepMatrix;
extern	ClassDictionary*	gClassDictionary;
extern  bool				g_analysis_static;	// Set as parameter bitmaksk in expression dump.
extern  bool				g_noDump;
extern	bool				g_registerClasses;
extern  bool				gIsStaticFunc;
extern	bool				g_forArgument;
extern  bool				gTransformAsDelegate;
struct SInitialization;
extern  SInitialization*	gGlobalInitList;

extern  TypeObject			t_INT;
extern  TypeObject			t_BOOL;
extern  TypeObject			t_OBJECT;

extern  TypeObject			t_STRING;
extern  TypeObject			t_NULL;
extern  TypeObject			t_DOUBLE;
extern  TypeObject			t_FLOAT;
extern  TypeObject			t_UINT;
extern  TypeObject			t_LONG;
extern  TypeObject			t_ULONG;
extern  TypeObject			t_CHAR;
extern  int					yylineno;

void resetLocalFileInfo();
SValue registerString(SValue v);
bool checkEntryPoint(u32 compilerOptions);
void generateOutput(const char* outputPath, u32 compilerOptions);
void exportRuntimeIncludes();
void exportFrameworkHeader();
void exportFrameworkFooter();
void exportNameSpaceHeader(NameSpace* nSpace, bool forExport);
void exportNameSpaceImplementation(NameSpace* nSpace);
void exportPrototypes();
void exportConstants();
void exportInlineFiles(const char* outputPath, ClassDictionary* CD);
void initBaseType();
void registerGCWorld(NameSpace* root, u32 compilerOptions);
void GenerateInitList();
void PopInitList();
Expression* getInitList();

void addGenericName(const char* name);
TypeGenericDefinitionEntry* popGenericNameList();
TypeGenericEntry* PopGenericType();
void PushGenericType(TypeGenericEntry* data);

void		getContext(Symbol* symbol, NameSpace*& out_namespace, Method*& out_method);
SRSymbol	resolveSimpleSymbol(SRSymbol baseContext, const char*, u8 searchMask, Expression* methodSignature = NULL, Variable* delegateSignature = NULL, TypeGenericEntry* genParams = NULL);
bool		isBetterFunctionMember(Variable* argList1, Variable* argList2, Expression* signature);
bool		isBetterFunctionMember(Variable* argList1, Variable* argList2, Variable* signature);
EMATCH		compareSignatures(Variable* argList, Expression* signature);
EMATCH		compareSignatures(Variable* argList, Variable* signature);

bool templateClassSpecializationDumpForOneGenericType(const char** templateList, const char** bodyCsteList, const char** templateEndList, u32 templateListLength, const char** classList, const char** classBody, u32 classListLenght);
const char* pathName(const char* path);

// Trace parser state.
#ifndef __NOTRACE__
#define	R()					traceFunc(__LINE__, yylineno, NULL/*yytname[YYTRANSLATE(yychar)]*/);
#else
#define R()					;
#endif

// do nothing, no debug.
//#define R()						{}
#endif
