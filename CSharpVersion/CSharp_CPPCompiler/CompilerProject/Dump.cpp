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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UTF8Parse.h"

				
class GCSupport {
public:
	static void dumpMemberGC(Variable* var);
	static void memberReleaseGC(Variable* var);

	static void dumpStructGC(Variable* var, AbstractContainer* cnt);
	static void structReleaseGC(Variable* var, AbstractContainer* cnt);
};

void GCSupport::dumpMemberGC(Variable* var) 
{ printf("if (%s) { System::Memory::pushList(%s,0); }\n",var->getName(),var->getName()); }

void GCSupport::dumpStructGC(Variable* var, AbstractContainer* cnt) 
{ printf("%s._processGC();\n",var->getName()); }

void GCSupport::memberReleaseGC(Variable* var) 
{ printf("if (%s && !%s->isFreed()) { %s->_removeRef((System::__GCObject**)&%s); }\n",var->getName(),var->getName(),var->getName(),var->getName()); }

void GCSupport::structReleaseGC(Variable* var, AbstractContainer* cnt) 
{ printf("%s._releaseGC();\n",var->getName()); }

//
// Dump Code.
//

void dumpWrapper(Expression* expr, bool safe = false);
void dumpAccessorWrappers(const char* pName, const char* pStrType, bool isNonNum, const char* testDiv, bool isEnum, bool isStatic, bool isNativePtr);
void dumpGlobalInitializerPrototype();
void dumpGlobalInitializerImplementation();

int depth = 0;
void tab() { for (int n=0; n < depth; n++) { printf("    "); } }

void dumpUtf8ToUniChar(const char* str) {
	int len = strlen(str);
	u16 dst[5000];
	int count = toUtf16((const u8*)str, len, dst, 5000);

	bool first = true;
	int n=0;
	while (n < count) {
		if (!first) { printf(","); } else first = false;
		printf("%i", dst[n]);
		n++;
	}
}

void exportConstants() {
	StringID* p = gStrList;
	while (p) {
		if(p->m_isDumped) {
			tab(); printf("/* %s */\n",p->m_str);
			if(strcmp(p->m_str, "") != 0) {
				tab(); printf("static const uniChar _$_cteStr%i[] = {",p->m_id); dumpUtf8ToUniChar(p->m_str); printf("};\n");
			}
			else {
				// String is initialised with String::Empty
			}
			tab(); printf("static System::String* _$_cteStr%iObj;\n\n", p->m_id);
		}
		p = p->m_next;
	}

	dumpGlobalInitializerPrototype();
}

void exportInlineFiles(const char* outputPath, ClassDictionary* CD) {
	// Export class prototypes
	freopen(concat2(outputPath, "classPrototypes.inl"), "w", stdout);
	exportNameSpaceHeader(gRootNameSpace, true);

	// Export __InternalUtils::GetTypeID specializations
	freopen(concat2(outputPath, "__InternalUtilsGetTypeID_specializations.inl"), "w", stdout);
	const char* templateList = "template<> struct __InternalUtilsGetTypeID<<T>> { ";
	const char* bodyCsteList = "static u32 getIt() { return _TYPE_USEROBJECT | <BODY>; }";
	const char* templateEndList = " };";
	templateClassSpecializationDumpForOneGenericType(&templateList, &bodyCsteList, &templateEndList, 1,
		CD->classes, CD->IDs, CD->count);
}

void exportStatics(NameSpace* nSpace, const char* precNameSpace) {
	char prefix[1000];
	if (precNameSpace[0] != 0) {
		sprintf(prefix,"%s%s::",precNameSpace, nSpace->getName());
	} else {
		if (nSpace->getName()[0]) {
			sprintf(prefix,"%s::", nSpace->getName());
		} else {
			sprintf(prefix,"");
		}
	}

	NameSpace* pCurrSpace = nSpace;

	// Export all static
	AbstractContainer** pCnt = pCurrSpace->m_pInner;
	if (pCurrSpace->m_innerCount && (pCurrSpace->m_noDump == false)) {
		for (int n=0; n < pCurrSpace->m_innerCount; n++) {
			AbstractContainer* pAC = pCnt[n];
			gCurrentAC = pAC;
			for (int n=0; n < pAC->m_memberCount; n++) {
				Variable* pVar = pAC->m_members[n];
				if ((pVar->m_modifier & ATT_STATIC) != 0) {
					
					if (pVar->m_expression) {
						Expression::patchExpressionsForListExpressions(&pVar->m_expression, pVar->m_type);
						pVar->m_expression->AnalysisAndTransform();
					}

					if (prefix[0]) {
						printf("%s %s%s::%s;\n", pVar->m_type->dumpTypeForCode(NULL), prefix, pAC->getName(), pVar->getName());
					} else {
						printf("%s %s::%s;\n",pVar->m_type->dumpTypeForCode(NULL), pAC->getName(), pVar->getName());
					}
					// Analysis of expression for dependancy.
					gCurrVar = pVar;
					pVar->markSetupDependancy();
				}
			}
			gCurrentAC = NULL;
			exportStatics(pAC, prefix);
		}
	}

	// Export inner name space first
	NameSpace* p = pCurrSpace->m_pChildSpace;
	while (p)	{ exportStatics(p,prefix); p = p->m_pNextSpace; }
}

void initStaticVar(Variable* pVar) {
	printf(" = ");
	if (pVar->m_expression) {
		gStaticContextAC = pVar->m_ownerClass;
		// Expression::analysisTransformAndDump(&pVar->m_expression, pVar->m_type);
		pVar->m_expression->dumpExpression();
		gStaticContextAC = NULL;
	} else {
		if (pVar->m_type->isGC_Able()) {
			printf("NULL");
		} else {
			switch (pVar->m_type->m_typeID) {
			case TYPE_SBYTE		:	
			case TYPE_BYTE		:
			case TYPE_SHORT		:
			case TYPE_USHORT	:
			case TYPE_INT		:
			case TYPE_UINT		:
			case TYPE_LONG		:
			case TYPE_ULONG		:
				printf("0");
				break;
			case TYPE_CHAR		:
				printf("0");
				break;
			case TYPE_FLOAT		:
				printf("0.0f");
				break;
			case TYPE_DOUBLE	:
				printf("0.0");
				break;
			case TYPE_BOOL		:
				printf("false");
				break;
			case TYPE_INTPTR	:
				printf("NULL");
				break;
			default:
				if (pVar->m_type->m_genreID == EGENRE::_ENUM) {
					printf("(%s)0",pVar->m_type->getFullName(NULL));
				} else {
					compilerError(ERR_INTERNAL,"Error default GC type", pVar->m_line);
				}
			}
		}
	}
	printf(";\n");
}

Variable* structNest[50];	// More than enough.

void setStaticsVarRec(int nestCount, Variable* pVar) {
	AbstractContainer* pCls = pVar->m_ownerClass;

	//
	// Dump
	//
	SRSymbol v = pVar->m_type->getResolvedType(pCls);
	AbstractContainer* cnt = (AbstractContainer*)v.pSymbol;
	if (v.symbolType == EGENRE::_ABSTRACTCONTAINER && ((cnt)->m_modifier & ATT_STRUCT)) {
		for (int n=0; n < cnt->m_memberCount; n++) {
			Variable* pVarL = cnt->m_members[n];
			structNest[nestCount] = pVarL;
			setStaticsVarRec(nestCount+1, pVarL);
		}
	} else {
		const char* pSrc = structNest[0]->m_ownerClass->getFullName(NULL);	// From root
		tab(); printf("%s::%s", pSrc, structNest[0]->m_name);
		for (int m=1; m < nestCount; m++) {
			printf(".%s", structNest[m]->m_name);
		}
		initStaticVar(structNest[nestCount-1]);
	}
}

void setStatics() {
	Variable* pVar;
	//
	// This system allow to solve dependancy between static / const C# expression and dump them in correct other.
	//
	while (pVar = gStaticDepMatrix->popIndependantVariable()) {
		structNest[0] = pVar;
		setStaticsVarRec(1, pVar);
	}
}

void registerStaticsRec(int nestCount, char* prefix, AbstractContainer* pAC, Variable* v) {
	AbstractContainer* localContainer;
	if (v) {
		localContainer = v->m_type->m_definitionAC;
	} else {
		localContainer = pAC;
	}

	//
	// For nextCount >= 1 : Struct inheritance is not supported, just parse sub structures.
	//
	for (int n=0; n < localContainer->m_memberCount; n++) {
		Variable* pVar = localContainer->m_members[n];
		// First level variable are static,
		// But deeper level are inside a struct and do NOT depend on static flag !
		if ((((pVar->m_modifier & ATT_STATIC) != 0) && nestCount == 0) || (nestCount)) {
			if (pVar->m_type->isGC_Able()) {
				structNest[nestCount] = pVar;
				
				tab(); printf("System::Memory::registerGCRoot(&%s%s::",prefix, pAC->getName());
				
				for (int m=0; m <= nestCount; m++) {
					if (m != 0) {
						printf(".");
					}
					printf("%s", structNest[m]->m_name);
				}
				printf(");\n");
			} else if (pVar->m_type->m_definitionAC && pVar->m_type->m_definitionAC->m_modifier & ATT_STRUCT) {
				structNest[nestCount] = pVar;
				registerStaticsRec(nestCount + 1, prefix, pAC, pVar);
			}
		}
	}
}

void registerStatics(NameSpace* nSpace, const char* precNameSpace) {
	if(nSpace->m_noDump) {
		// Do not register the static members.
		return;
	}
	char prefix[1000];
	int strl = strlen(precNameSpace);
	if (strl) {
		sprintf(prefix,"%s%s::",precNameSpace,nSpace->getName());
	} else if(strlen(nSpace->getName())){
		sprintf(prefix,"%s::",nSpace->getName());
	}
	else {
		sprintf(prefix,"");
	}

	NameSpace* pCurrSpace = nSpace;

	// Export all static
	AbstractContainer** pCnt = pCurrSpace->m_pInner;
	if (pCurrSpace->m_innerCount) {
		for (int n=0; n < pCurrSpace->m_innerCount; n++) {
			AbstractContainer* pAC = pCnt[n];
			registerStaticsRec(0, prefix,pAC,NULL);
			registerStatics(pAC,prefix);
		}
	}

	// Export inner name space first
	NameSpace* p = pCurrSpace->m_pChildSpace;
	while (p)	{ registerStatics(p,prefix); p = p->m_pNextSpace; }
}

void registerGCWorld(NameSpace* root, u32 compilerOptions) {
	bool isFramework = (compilerOptions & COMPIL_IS_FRAMEWORK) != 0;

	// Declate all static variables.
	exportStatics(root,"");

	dumpGlobalInitializerImplementation();

	printf(isFramework ? "\n#include \"callbackDef.inl\"\n\nvoid initFrameworkStatic() {\n" : "\nvoid initAllStatic() {\n");

	depth++;
	setStatics();
	depth--;
	printf("}\n\n");

	printf(isFramework ? "void initFramework() {\n" : "void registerWorldGC() {\n");

	depth++;
	if(compilerOptions & COMPIL_USE_FRAMEWORK) {
		tab(); printf("initFramework();\n");
	}

	StringID* p = gStrList;
	bool first = true;
	while (p) {
		if(p->m_isDumped) {
			if (first) {
				first = false;
				tab(); printf("// Register Strings into the GC.\n");
			}
			if(strcmp(p->m_str, "") != 0) {
				tab(); printf("_$_cteStr%iObj = CS_NEW System::String(_$_cteStr%i,sizeof(_$_cteStr%i) / sizeof(uniChar));\n",p->m_id,p->m_id,p->m_id);
				tab(); printf("System::Memory::registerGCRoot(&_$_cteStr%iObj);\n\n",p->m_id);
			}
			else {
				tab(); printf("System::__GCObject::_RefSetValue((System::__GCObject**)&_$_cteStr%iObj, System::String::Empty);\n",p->m_id);
				// String::Empty is registered somewhere else
			}
		}
		p = p->m_next;
	}

	printf("\n");

	tab();
	if(isFramework) {
		printf("initFrameworkStatic();\n");
		tab(); printf("initCallbacks();\n");
	}
	else {
		printf("initAllStatic();\n");
	}

	printf("\n");
	registerStatics(root,"");
	printf("\n");

	depth--;
	printf("}\n");
}

const char* dotToColon(const char* str) {
	char buf[500];
	char* pStr = (char*)str;
	char* pBuf = buf;
	while(*pStr) {
		if(*pStr == '.') {
			for(int n = 0 ; n < 2 ; n++, pBuf++) {
				*pBuf = ':';
			}
			pStr++;
		}
		else {
			*(pBuf++) = *(pStr++);
		}
	}
	*pBuf = 0;
	return concat(buf);
}

void dumpUsings(NameSpace* nSpace) {
	for(int n=0; n < nSpace->m_usingCount ; n++) {
		if(strcmp(nSpace->m_usings[n], "System.Runtime") != 0 &&
		strcmp(nSpace->m_usings[n], "System.Runtime.InteropServices") != 0 &&
		strcmp(nSpace->m_usings[n], "System.Text") != 0) {
			bool isSupported = (nSpace->resolve(nSpace->m_usings[n]) != NULL);
			if(isSupported) {
				tab(); printf("using namespace %s;\n", dotToColon(nSpace->m_usings[n]));
			}
		}
		else {
			// Special case : those namespaces are used in C#, but must not be dumped in C++.
		}
	}
	printf("\n");
}

void dumpEnums(NameSpace* nSpace) {
	for (int n=0; n < nSpace->m_enumCount; n++) {
		Enum* pEnum = nSpace->m_enums[n];
		if(pEnum->getType()->m_typeID == TYPE_LONG || pEnum->getType()->m_typeID == TYPE_ULONG) {
			compilerError(ERR_NOT_SUPPORTED_YET, "Only byte, sbyte, short, ushort, int and uint types can be used for enums", pEnum->m_line);
			continue;
		}
		tab(); printf("enum %s {\n", pEnum->getName());
		Enum::EnumEntry* pEntry = pEnum->m_list;
		depth++;
		while (pEntry) {
			tab();printf(pEntry->m_name);
			if (pEntry->m_expression) {
				printf(" = ");
				Expression::analysisTransformAndDump(&pEntry->m_expression, pEnum->getType());
			}
			printf(",\n");
			pEntry = pEntry->m_pNext;
		}
		tab(); printf("_ForceWORD_%s = 0x7FFFFFFF\n", pEnum->m_name);
		depth--;
		tab(); printf("};\n\n");
	}
}

void dumpDelegatePrototypes(NameSpace* nSpace) {
	for(int n=0 ; n < nSpace->m_delegateCount ; n++) {
		Delegate* pDelegate = nSpace->m_delegates[n];
		gCurrentMethod = pDelegate;
		tab(); printf("class _Delegate_Base_%s;\n",pDelegate->getName());
		tab(); printf("template <class TClass> class _DelegateI_%s;\n",pDelegate->getName());
		tab(); printf("class _DelegateS_%s;\n",pDelegate->getName());
	}
	gCurrentMethod = NULL;
}

void dumpClassPrototypes(NameSpace* nSpace, bool forExport) {
	AbstractContainer** pCnt = nSpace->m_pInner;
	for (int n=0; n < nSpace->m_innerCount; n++) {
		AbstractContainer* currCnt = pCnt[n];
		if (currCnt->m_noDump == false || forExport) {
			tab(); currCnt->dumpTemplateLabel();
			if(currCnt->m_modifier & ATT_STRUCT) {
				printf("struct %s;\n", currCnt->getName());
			}
			else {
				printf("class %s;\n", currCnt->getName());
			}
		}
	}
	printf("\n");
}

void recursiveRegisterClassDependancy(NameSpace* pCurrSpace) {
	if (pCurrSpace->getGenre() == EGENRE::_NAMESPACE || pCurrSpace->getGenre() == EGENRE::_ABSTRACTCONTAINER) {
		if(pCurrSpace->m_noDump) {
			// No registration
			return;
		}
		NameSpace* p = pCurrSpace->m_pChildSpace;
		while (p)	{ recursiveRegisterClassDependancy(p); p = p->m_pNextSpace; }

		AbstractContainer** pCnt = pCurrSpace->m_pInner;
		for (int n=0; n < pCurrSpace->m_innerCount; n++) {
			AbstractContainer* currCnt = pCnt[n];
			if (pCurrSpace->getGenre() == EGENRE::_ABSTRACTCONTAINER) {
				gStaticDepMatrix->createDependancy(currCnt, (AbstractContainer*)pCurrSpace);
			}
			if (!currCnt->m_noDump) {
				gStaticDepMatrix->registerAbstractContainer(currCnt);
				for (int m=0; m < currCnt->m_inheritancesCount; m++) {
					TypeObject* type = currCnt->m_inheritances[m];
					type->getResolvedType(pCurrSpace);
					AbstractContainer* pDep = type->m_definitionAC;
					if(!pDep->isSubSystem()) {
						gStaticDepMatrix->createDependancy(currCnt, pDep);
					}
				}

				for (int m=0; m < currCnt->m_accessorCount; m++) {
					TypeObject* type = currCnt->m_accessors[m]->m_type;
					SRSymbol sr = type->getResolvedType(currCnt);
					switch (sr.symbolType) {
					case EGENRE::_ABSTRACTCONTAINER:
						{
							AbstractContainer* pCnt = (AbstractContainer*)sr.pSymbol;
							if (pCnt->m_modifier & ATT_STRUCT) {
								gStaticDepMatrix->createDependancy(currCnt, pCnt);
							}
						}
						break;
					}
				}

				for (int m=0; m < currCnt->m_memberCount; m++) {
					TypeObject* type = currCnt->m_members[m]->m_type;
					SRSymbol sr = type->getResolvedType(currCnt);
					switch (sr.symbolType) {
					case EGENRE::_ABSTRACTCONTAINER:
						{
							AbstractContainer* pCnt = (AbstractContainer*)sr.pSymbol;
							if (pCnt->m_modifier & ATT_STRUCT) {
								gStaticDepMatrix->createDependancy(currCnt, pCnt);
							}
						}
						break;
					}
				}

				// TODO Struct in func call.

				if(currCnt->m_innerCount) {
					recursiveRegisterClassDependancy(currCnt);
				}
			}
		}
	}
}

void exportPrototypes() {
	// 1. Register all classes with dependancies
	recursiveRegisterClassDependancy(gRootNameSpace);

	// 2. Dump each class based on dependancy
	AbstractContainer* pCnt;
	while (pCnt = gStaticDepMatrix->popIndependantAbstractContainer()) {
		pCnt->dumpPrototype(false);
	}
	if(gStaticDepMatrix->hasRemainingAC()) {
		compilerError(ERR_INTERNAL, "Dependant classes remaining");
	}
}

void dumpDelegates(const char* prefix, NameSpace* nSpace) {
	int count;
	for (count = 0; count < nSpace->m_delegateCount; count++) {
		gCurrentMethod = nSpace->m_delegates[count];
		nSpace->m_delegates[count]->dumpDefinition(prefix);
	}
	gCurrentMethod = NULL;
}

void exportRuntimeIncludes() {
	printf("#include \"RuntimeLibrary/CS_Array.h\"\n");
	printf("#include \"RuntimeLibrary/CS_Console.h\"\n");
	printf("#include \"RuntimeLibrary/CS_Marshal.h\"\n");
	printf("#include \"RuntimeLibrary/CS_Memory.h\"\n");
	printf("#include \"RuntimeLibrary/CS_Object.h\"\n");
	printf("#include \"RuntimeLibrary/CS_String.h\"\n");
	printf("#include \"RuntimeLibrary/CS_System.h\"\n");
	printf("#include \"RuntimeLibrary/Collections/Collections.h\"\n");
	printf("#include \"RuntimeLibrary/Collections/Generic/CS_Dictionary.h\"\n");
	printf("#include \"RuntimeLibrary/Collections/Generic/CS_List.h\"\n");
	printf("#include \"RuntimeLibrary/Collections/Generic/Generic.h\"\n");
	printf("#include \"RuntimeLibrary/InternalUtils.h\"\n");
	printf("#include \"RuntimeLibrary/MarshallingUtils.h\"\n");
}

void exportFrameworkHeader(){
	printf("#ifndef _FRAMEWORK_H\n");
	printf("#define _FRAMEWORK_H\n\n");
	exportRuntimeIncludes();
	printf("#include \"ExportListC_Likefunction.h\"\n");
	printf("\n");
}

void exportFrameworkFooter(){
	printf("\nvoid initFramework();\n\n");
	printf("class Program : public System::Object {\n");
	depth++;
	printf("public:\n");
	tab(); printf("void _ctor_Program();\n\n");
	tab(); printf("Program();\n");
	tab(); printf("static void start();\n");
	tab(); printf("virtual u32 _processGC();\n");
	tab(); printf("virtual void _releaseGC();\n");
	tab(); printf("virtual bool _isInstanceOf(u32 typeID);\n");
	tab(); printf("virtual inline void _moveAlert(u32 offset);\n");
	printf("private:\n");
	tab(); printf("static const u32 _TYPEID = 0xFFFFFFFF;\n");
	depth--;
	printf("};\n\n");
	printf("\n#endif // _FRAMEWORK_H\n\n");
}

void exportNameSpaceHeader(NameSpace* nSpace, bool forExport) {
	NameSpace* pCurrSpace = nSpace;
	bool hasNameSpace = strlen(pCurrSpace->getName()) != 0;
	bool isDumped = (pCurrSpace->m_noDump == false) || (forExport && !nSpace->isSubSystem());
	if (hasNameSpace && isDumped) { tab(); printf("namespace %s {\n", pCurrSpace->getName()); depth++; }

	if(isDumped) {
		//dumpUsings(nSpace);
		if(!forExport) {
			dumpEnums(nSpace);
		}
		dumpDelegatePrototypes(nSpace);
		dumpClassPrototypes(nSpace, forExport);
	}

	// Export inner name space first
	NameSpace* p = pCurrSpace->m_pChildSpace;
	while (p)	{ exportNameSpaceHeader(p, forExport); p = p->m_pNextSpace; }

	if (hasNameSpace && isDumped) { depth--; tab(); printf("}\n"); }
}

void exportNameSpaceImplementation(NameSpace* nSpace) {
#ifdef __FULLNAMES__
	bool dumpName = false;
#else
	bool dumpName = true;
#endif

	NameSpace* pCurrSpace = nSpace;
	bool hasNameSpace = strlen(pCurrSpace->getName()) != 0;
	bool isDumped = (pCurrSpace->m_noDump == false);
	if(isDumped) {
		if (hasNameSpace && dumpName) { tab(); printf("namespace %s {\n", pCurrSpace->getName()); depth++; }

		// Export inner name space first
		NameSpace* p = pCurrSpace->m_pChildSpace;
		while (p)	{ exportNameSpaceImplementation(p); p = p->m_pNextSpace; }

		//dumpUsings(nSpace);

		if (pCurrSpace->m_delegateCount) {
			tab(); printf("//\n");
			tab(); printf("// Delegate Implementation\n");
			tab(); printf("//\n\n");
			dumpDelegates(dumpName ? "" : nSpace->getFullName(gRootNameSpace), nSpace);
		}

		if (pCurrSpace->m_innerCount) {
			tab(); printf("//\n");
			tab(); printf("// Class/Struct Implementation\n");
			tab(); printf("//\n\n");
		}

		AbstractContainer** pCnt = pCurrSpace->m_pInner;
		for (int n=0; n < pCurrSpace->m_innerCount; n++) {
			if (!pCnt[n]->m_noDump) {
				tab(); printf("//=============================\n");
				tab(); printf("// Implementation of '%s'\n",pCnt[n]->getName());
				tab(); printf("//=============================\n\n");
				gCurrentAC = pCnt[n];
				pCnt[n]->dumpImplementation(dumpName ? "" : nSpace->getFullName(gRootNameSpace)); // Classes relative to current namespace.
				gCurrentAC = NULL;
				printf("\n");
			}
		}

		// Phase 2 : Dump implementation.

		if (hasNameSpace && dumpName) { depth--; tab(); printf("}\n"); }
	}
}

void processDelegateAssignment(Expression*& expression,TypeObject* typeOfDelegate, bool assignDelegate) {
loop:
	// Second resolve right side
	expression->AnalysisAndTransform();
	if(expression->m_expressionType == EXPR_CAST) {
		expression->m_item = expression->m_expressions[expression->m_expressionCount - 1]->m_item;
	}

	// Third check right side
	if (assignDelegate) {
		if (expression->m_item.symbolType == EGENRE::_DELEGATE) {
			// Do nothing, delegate operator created the delegate.
		} else if (expression->m_item.symbolType == EGENRE::_METHOD) {
			// Forbid for now to assign directly function to delegate
			// Later version of the compiler could generate the missing new automatically.
			switch(expression->m_expressionType) {
			case EXPR_IDENT :
			case EXPR_DOT:
				if(expression->m_expressionType == EXPR_DOT && expression->m_expressions[0]->m_runtimeType->isGC_Able() == false) {
					compilerError(ERR_USER, "Delegate assignments can use methods from pointer types only", expression->m_line);
					return;
				}
				// Modify expression tree and patch.
				// Generate the new.
				expression = CreateSingleExpr(EXPR_NEW, CreateMultipleExpr(expression))->setType(typeOfDelegate);
				goto loop;
			case EXPR_CAST:
				if(expression->m_expressions[expression->m_expressionCount - 1]->isMethodAsDelegate()) {
					processDelegateAssignment(expression->m_expressions[1], expression->m_runtimeType, assignDelegate);
					expression->m_expressions[expression->m_expressionCount - 1]->m_hasParenthesis = true;
					goto loop;
				}
				break;
			default:
				// Else call to a function returned a delegate.
				break;
			}
		} else if ((expression->m_item.symbolType == EGENRE::_VARIABLE) || (expression->m_item.symbolType == EGENRE::_MEMBER)) {
			// Do nothing
			// Delegate a = v; // v is a variable or member.
		} else if (expression->m_expressionType == EXPR_CTE) {
			// Do nothing
			// => Stick NULL.
		} else {
			if (expression->m_runtimeType->m_genreID == EGENRE::_DELEGATE) {
				// Do nothing, new operator created the delegate. 
			} else {
				compilerError(ERR_INTERNAL, "Delegate was not wrapped properly", expression->m_line);
			}
		}
	}
}

Statement* Statement::wrapCaseBody() {
	bool hasLocalVariable = false;
	Statement* pInstruction = this;
	while(pInstruction && !hasLocalVariable) {
		if(pInstruction->m_statementType == STM_LOCALVAR) {
			hasLocalVariable = true;
		}
		pInstruction = pInstruction->m_pNext;
	}
	if(hasLocalVariable) {
		return CreateStatement(STM_BLOCK, NULL, this);
	}
	return this;
}

void Statement::analysis(bool processBrother) {
	// Force to stop recursion, without test each
	if (this == NULL) { return; }

	Statement* p = m_pChild;

	switch (m_statementType) {
	case STM_UNDEFINED: 
		compilerError(ERR_INTERNAL, "Invalid Statement here", m_line);

		break;
	case STM_BLOCK: 
		gCurrentSD = gCurrentSD->addDictionary();
		depth++;
			p->analysis();
		depth--;
		gCurrentSD = gCurrentSD->removeDictionary();
		break;
	case STM_NILWRAPPER: 
		// Use by STM_FOR and act only as a "wrapper" to maintain order.
		p->analysis();

		break;
	case STM_NULL: 

		break;
	case STM_LABEL: 
		m_pChild->analysis();

		break;
	case STM_LOCAL_PERVAR:
		if (m_expr) {
			m_expr->AnalysisAndTransform();
		}
		break;
	case STM_LOCALVAR:
		{
			// Forbid variable usage as long as not assigned.
			Variable* pVar = this->m_vars;
			while (pVar) {
				gCurrentSD->addVariable(pVar);
				pVar->m_ignoreDelegate = true;
				pVar = pVar->m_pNextVariable;
			}

			Statement* pCaseCode = p->m_pChild; 
			while (p) {
				// Copy the flag here.
				p->m_bConstant = m_bConstant;
				p->analysis(false);
				p = p->m_pNext;
			}

			// Allow variable usage.
			pVar = this->m_vars;
			while (pVar) {
				pVar->m_ignoreDelegate = false;
				pVar = pVar->m_pNextVariable;
			}
		}
		break;

	case STM_WRAP_EXP:			m_expr->AnalysisAndTransform(); break;
	case STM_ASSIGN_EXPR:		m_expr->AnalysisAndTransform(); break;
	case STM_WRAPPER_POSTINCR:	m_expr->AnalysisAndTransform(); break;
	case STM_WRAPPER_POSTDECR:	m_expr->AnalysisAndTransform(); break;
	case STM_WRAPPER_PREINCR:	m_expr->AnalysisAndTransform(); break;
	case STM_WRAPPER_PREDECR:	m_expr->AnalysisAndTransform(); break;

	case STM_IF: 
		{
			m_expr->AnalysisAndTransform();
			// If code
			p->analysis(false);
			// else code
			p = p->m_pNext;
			if (p) {
				p->analysis(false);
			}
		}
		break;

	case STM_SWITCH:
		m_expr->AnalysisAndTransform();
		if(m_expr->m_runtimeType->m_typeID == TYPE_STRING) {
			compilerError(ERR_NOT_SUPPORTED_YET, "Switch statements with strings are not supported at the moment", m_line);
		}
		{
			int count = 0;
			Statement* pCaseCode = p->m_pChild; 
			while (p) {
				//
				// Dump Case inner code WHEN case list is completed.
				//
				if (pCaseCode != p->m_pChild) {
					pCaseCode->analysis(true);
					pCaseCode = p->m_pChild;
				}

				if (p->m_statementType == STM_CASE) {
					p->m_counter = count++;
					p->m_expr->AnalysisAndTransform();
				}

				p = p->m_pNext;
			}

			// Code for last case list block.
			depth++;
			pCaseCode->analysis(true);
			depth--;

			// Second loop to get the label number of the expressions referenced in the gotocases.
			p = m_pChild;	// Pointer roaming the cases of the switch
			while(p) {
				gCurrentSD = gCurrentSD->addDictionary();
				Statement* pInstruction = p->m_pChild;	// Pointer roaming the instructions of the case
				if(pInstruction && pInstruction->m_statementType != STM_BLOCK) {
					// Wrap case instruction into a block to be compatible with C++ if it contains local variables
					p->m_pChild = pInstruction->wrapCaseBody();
				}
				while(pInstruction) {
					if (pInstruction->m_statementType == STM_GOTOCASE) {
						pInstruction->m_expr->AnalysisAndTransform();

						// Fetch the corresponding case
						Statement* pCase = m_pChild;
						bool matched = false;
						while(pCase && !matched) {
							if(pInstruction->m_expr->m_expressionType == EXPR_CTE) { // Constant --> compare values
								matched = pCase->m_expr->compareValues(pInstruction->m_expr);
							}
							else {	// Enum --> compare texts
								matched = (strcmp(pCase->m_expr->m_text, pInstruction->m_expr->m_text) == 0);
							}
							if(!matched) {
								pCase = pCase->m_pNext;
							}
						}
						if(matched) {
							pInstruction->m_counter = pCase->m_counter;
						}
						else {
							compilerError(ERR_USER, "Case not found", pInstruction->m_line);
						}
					}
					pInstruction = pInstruction->m_pNext;
				}
				gCurrentSD = gCurrentSD->removeDictionary();
				p = p->m_pNext;
			}
		}
		break;
	case STM_GOTOCASE: 
		m_expr->AnalysisAndTransform();
		break;
	case STM_GOTODEFAULT:
		break;
	case STM_CASE: 
		// Nothing to do --> See Switch implementation.
		break;
	case STM_CASEDEFAULT: 
		// Nothing to do --> See Switch implementation.
		break;

	case STM_UNSAFE:
		{
			bool unsafe = g_unsafe;
			g_unsafe = true;
			m_pChild->analysis();
			g_unsafe = unsafe;
		}
		break;

	case STM_WHILE: 
		this->m_expr->AnalysisAndTransform();
		this->m_pChild->analysis();
		break;
	case STM_DOWHILE: 
		this->m_pChild->analysis();
		this->m_expr->AnalysisAndTransform();
		break;

	case STM_FOR: 
		// Expr : condition opt
		{
			gCurrentSD = gCurrentSD->addDictionary();
			Statement* p = m_pChild;
				p->analysis(false);
				this->m_expr->AnalysisAndTransform();
				p = p->m_pNext;
				p->analysis(false);
			p = p->m_pNext;
			p->analysis(false);
			gCurrentSD = gCurrentSD->removeDictionary();
		}
		break;
	case STM_FOREACH: 
		break;
	case STM_BREAK: 
		break;
	case STM_CONTINUE: 
		break;
	case STM_GOTO: 
		break;

	case STM_RETURN: 
		{
			TypeObject* typeOfDelegate = NULL;
			bool assignDelegate = false;

			if (m_expr) { 
				m_expr->AnalysisAndTransform(); 
				if ((m_expr->m_item.symbolType == EGENRE::_METHOD) && (m_expr->m_expressionType != EXPR_INVOKE)) {
					assignDelegate = true;
					typeOfDelegate = gReturnType;
					processDelegateAssignment(m_expr,typeOfDelegate, assignDelegate);
				}
			}
		}
		break;

	case STM_THROW: 
		if (m_expr) {
			m_expr->AnalysisAndTransform();
		}
		break;

	case STM_TRY: 
		// First child is code
		depth++;
			p->analysis();
		depth--;


		// Parse the list of CATCH / FINALLY
		{
			Statement* p2 = m_pNext;
			bool firstCatch = true;
			while (p2 && (p2->m_statementType == STM_CATCH || p2->m_statementType == STM_FINALLY)) {
				depth++;
				gCurrentSD = gCurrentSD->addDictionary();
				if(p2->lbl) {
					p2->m_type->getResolvedType(gCurrentAC);
					Variable* exception = CreateVarInstance(p2->lbl);
					exception->m_type = p2->m_type;
					gCurrentSD->addVariable(exception);
				}
				p2->m_pChild->analysis();
				gCurrentSD = gCurrentSD->removeDictionary();
				depth--;
				p2 = p2->m_pNext;
			}
		}
		break;
	case STM_CATCH: 
	case STM_FINALLY: 
		//
		// Do nothing, See STM_TRY
		//
		break;
	case STM_CHECKED: 
	case STM_UNCHECKED: 
		// Unsupported, generate compiler error in parser for CHECKED, jump dump sub expression in C++
		p->analysis();
		break;
	case STM_LOCK:
		// Unsupported, generate compiler error in parser for LOCK.
		break;
	case STM_USING: 
		// Unsupported, generate compiler error in parser for USING as statement.
		break;
	default:
		compilerError(ERR_INTERNAL, "Invalid Statement here", m_line);
		break;
	}

	// Dump all brother
	if (processBrother) {
		m_pNext->analysis();
	}
}

void Statement::dumpStatement(bool processBrother) {
	// Force to stop recursion, without test each
	if (this == NULL) { return; }

	Statement* p = m_pChild;

	switch (m_statementType) {
	case STM_UNDEFINED: 
		compilerError(ERR_INTERNAL, "Invalid Statement here", m_line);

		break;
	case STM_BLOCK: 
		tab(); printf("{\n");
		gCurrentSD = gCurrentSD->addDictionary();
		depth++;
			p->dumpStatement();
		depth--;
		gCurrentSD = gCurrentSD->removeDictionary();
		tab();printf("}\n");
		break;
	case STM_NILWRAPPER: 
		// Use by STM_FOR and act only as a "wrapper" to maintain order.
		p->dumpStatement();

		break;
	case STM_NULL: 
		if(!g_forArgument) {
			printf(";\n");
		}

		break;
	case STM_LABEL: 
		depth--;
		tab(); printf("%s:\n", this->lbl);
		depth++;
		m_pChild->dumpStatement();

		break;
	case STM_LOCAL_PERVAR:
		if(!g_forArgument) {
			tab();
		}
		gCurrentSD->addVariable(m_vars);
		if (this->m_bConstant) {
			// Const var in C# -> static const var in C++ ?
			printf("static const ");
		}
		printf(m_vars->m_type->dumpTypeForCode(gCurrentAC));
		// No need to dump "var_name = " anymore, now as expression.
		if (this->m_expr) {
			printf(" ");
			this->m_expr->dumpExpression();
		} else {
			printf(" %s",this->m_vars->getName());
		}

		if(!g_forArgument) {
			printf(";\n");
		}
		else if(this->m_pNext) {
			printf(", ");
		}
		break;
	case STM_LOCALVAR:
		{
			Statement* pCaseCode = p->m_pChild; 
			while (p) {
				p->dumpStatement(false);
				p = p->m_pNext;
			}
		}
		break;

	case STM_WRAP_EXP:			if(!g_forArgument) tab(); m_expr->dumpExpression(); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;
	case STM_ASSIGN_EXPR:		if(!g_forArgument) tab(); dumpWrapper(m_expr, !g_unsafe); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;
	case STM_WRAPPER_POSTINCR:	if(!g_forArgument) tab(); dumpWrapper(m_expr, !g_unsafe); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;
	case STM_WRAPPER_POSTDECR:	if(!g_forArgument) tab(); dumpWrapper(m_expr, !g_unsafe); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;
	case STM_WRAPPER_PREINCR:	if(!g_forArgument) tab(); dumpWrapper(m_expr, !g_unsafe); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;
	case STM_WRAPPER_PREDECR:	if(!g_forArgument) tab(); dumpWrapper(m_expr, !g_unsafe); if(!g_forArgument) printf(";\n"); else if(m_pNext) printf(", "); break;

	case STM_IF: 
		{
			tab(); printf("if ("); m_expr->dumpExpression(); printf(")\n");
			// If code
			p->dumpStatement(false);
			// else code
			p = p->m_pNext;
			if (p) {
				tab(); printf("else\n");
				p->dumpStatement(false);
			}
		}
		break;

	case STM_SWITCH:
		// TODO SWITCH : Check data type --> Switch in C++ are only using int.
		//	==> Perform a conversion of all cases ? -> If / elseIf tree ? => Better than generate an error and complain.
		// Note : If a class as a conversion operator to a int/string, then it become possible.
		// this->m_expr->solveExpressionType();
		gSwitchCount++;

		tab(); printf("switch ("); m_expr->dumpExpression(); printf(") {\n");
		{
			Statement* pCaseCode = p->m_pChild; 
			while (p) {
				//
				// Dump Case inner code WHEN case list is completed.
				//
				if (pCaseCode != p->m_pChild) {
					depth++;
					pCaseCode->dumpStatement(true);
					pCaseCode = p->m_pChild;
					depth--;
				}

				if (p->m_statementType == STM_CASE) {
					tab(); printf("case "); p->m_expr->dumpExpression(); printf(": sw_$lbl_%i_%i",gSwitchCount, p->m_counter); printf(":\n");
				} else
				if (p->m_statementType == STM_CASEDEFAULT) {
					tab(); printf("default : sw_$lbl_%i_default:\n",gSwitchCount);
				}

				p = p->m_pNext;
			}

			// Code for last case list block.
			depth++;
			pCaseCode->dumpStatement(true);
			depth--;
		}
		tab(); printf("}\n");
		break;
	case STM_GOTOCASE: 
		tab(); printf("goto sw_$lbl_%i_%i;\n",gSwitchCount,m_counter);
		break;
	case STM_GOTODEFAULT:
		tab(); printf("goto sw_$lbl_%i_default;\n",gSwitchCount);
		break;
	case STM_CASE: 
		// Nothing to do --> See Switch implementation.
		break;
	case STM_CASEDEFAULT: 
		// Nothing to do --> See Switch implementation.
		break;

	case STM_UNSAFE:
		{
			bool unsafe = g_unsafe;
			g_unsafe = true;
			m_pChild->dumpStatement();
			g_unsafe = unsafe;
		}
		break;

	case STM_WHILE: 
		tab(); printf("while (");
		this->m_expr->dumpExpression(); printf(")");
		if(this->m_pChild->m_statementType != STM_NULL) {
			printf("\n");
		}
		if(this->m_pChild->m_statementType != STM_BLOCK && this->m_pChild->m_statementType != STM_NULL) {
			depth--;
			tab();
			depth++;
		}
		this->m_pChild->dumpStatement();
		break;
	case STM_DOWHILE: 
		tab(); printf("do");
		if(this->m_pChild->m_statementType != STM_NULL) {
			printf("\n");
		}
		if(this->m_pChild->m_statementType != STM_BLOCK && this->m_pChild->m_statementType != STM_NULL) {
			depth--;
			tab();
			depth++;
		}
		this->m_pChild->dumpStatement();
		tab(); printf("while ("); this->m_expr->dumpExpression(); printf(");\n");
		break;

	case STM_FOR: 
		// Expr : condition opt
		{
			Statement* p = m_pChild;

			// Init section
			bool multipleInit = (p->m_pChild && p->m_pChild->m_pChild->m_pNext);
			if(multipleInit) {
				tab(); printf("{\n");
				depth++;
				p->dumpStatement(false);
				tab(); printf("for (;");
				g_forArgument = true;
			}
			else {
				g_forArgument = true;
				tab(); printf("for ("); 
				p->dumpStatement(false); printf(";");
			}
			// Condition section
			if(this->m_expr) {
				this->m_expr->dumpExpression();
			}
			printf(";"); 
			// Next Section
			p = p->m_pNext;
			p->dumpStatement(false);
			printf(")");
			if(p->m_pNext->m_pChild->m_statementType != STM_NULL) {
				printf("\n");
			}
			// Code inside the for.
			g_forArgument = false;
			p = p->m_pNext;
			if(p->m_pChild->m_statementType != STM_BLOCK && p->m_pChild->m_statementType != STM_NULL) {
				depth--;
				tab();
				depth++;
			}
			p->dumpStatement(false);
			if(multipleInit) {
				depth--;
				tab(); printf("}\n");
			}
		}
		break;
	case STM_FOREACH: 
		// TODO FOR EACH
		break;

	case STM_BREAK: 
		tab(); printf("break;\n"); // TO DO check. Is valid same as C++ ?
		break;
	case STM_CONTINUE: 
		tab(); printf("continue;\n"); // TO DO check.
		break;
	case STM_GOTO: 
		tab(); printf("goto %s;\n",this->lbl);
		break;

	case STM_RETURN: 
		tab(); printf("return "); if (m_expr) { 
			// printf("/*\n");
			// m_expr->dumpTree();
			// printf("*/\n");
			m_expr->dumpExpression(); 
		} printf(";\n");
		break;

	case STM_THROW: 
		if (m_expr) {
			tab(); printf("THROW("); m_expr->dumpExpression(); printf(");\n");
		} else {
			// throw; -> use hidden variable.
			tab(); printf("THROW(_$hiddenExcep);\n");
		}
		break;

	case STM_TRY: 
		tab(); printf("TRY\n");
		// First child is code
		p->dumpStatement();
		p = m_pNext;

		tab(); printf("CTRY\n");
		
		// "FIRSTCATCH(x)", "ELSECATCH(x)", "FINALLY"

		// Parse the list of CATCH / FINALLY
		{
			bool firstCatch = true;
			bool hasFinally = false;
			while (p && (p->m_statementType == STM_TRY || p->m_statementType == STM_CATCH || 
				         p->m_statementType == STM_FINALLY)) {
				if (p->m_statementType == STM_CATCH) {
					if (firstCatch) {
						firstCatch = false;
						tab(); printf("FIRSTCATCH(");
					} else {
						tab(); printf("ELSECATCH(");
					}

					if (p->m_type) {
						printf(p->m_type->getFullName(gCurrentAC)); printf(","); printf(p->lbl ? p->lbl : "_$hiddenExcep"); /*dumpTypeForCode(); // TODO : do not * the type*/
						printf(")\n");
					} else {
						printf("System::Exception,_$hiddenExcep)\n");
					}
				} else { // Finally
					hasFinally = true;
					if (!firstCatch) {
						// This line should not be executed for try-finally (no catches) pattern.
					    tab(); printf("FINALLY\n");
					}
				}
				p->m_pChild->dumpStatement();

				// Handle Type here to simplify structure and counting.
				p = p->m_pNext;
			}
			if(!hasFinally) {
				// Dump FINALLY anyway to close the CATCH statement.
				tab(); printf("FINALLY\n");
			}
		}

		tab(); printf("ETRY\n");

		break;
	case STM_CATCH: 
	case STM_FINALLY: 
		//
		// Do nothing, See STM_TRY
		//
		break;
	case STM_CHECKED: 
	case STM_UNCHECKED: 
		// Unsupported, generate compiler error in parser for CHECKED, jump dump sub expression in C++
		p->dumpStatement();
		break;
	case STM_LOCK:
		// Unsupported, generate compiler error in parser for LOCK.
		break;
	case STM_USING: 
		// Unsupported, generate compiler error in parser for USING as statement.
		break;
	default:
		compilerError(ERR_INTERNAL, "Invalid Statement here", m_line);
		break;
	}

	// Dump all brother
	if (processBrother) {
		m_pNext->dumpStatement();
	}
}

void SRSymbol::dump(bool assign) {
	switch (symbolType) {
	case EGENRE::_VARIABLE: 
		printf(pSymbol->getName());
		break;
	case EGENRE::_MEMBER:
		{
			//
			// If member is static or const, safe access.
			//

			Variable* pVar = (Variable*)this->pSymbol;
			if (g_unsafe || (pVar->m_modifier & ATT_STATIC)) {
				printf(pSymbol->getName());
			} else {
				// Convert into safe getter
				printf("_g$%s()",pSymbol->getName());
			}
		}
		break;
	case EGENRE::_METHOD: 
		break;
	case EGENRE::_ACCESSOR:
		{
			Accessor* pAcc = (Accessor*)this->pSymbol;
			printf("_acc_g%s",pSymbol->m_name);
			if (!(g_unsafe || (pAcc->m_modifier & ATT_STATIC))) { printf("$"); }
			printf("()");
		}
		break;
	case EGENRE::_DELEGATE:
		break;
	case EGENRE::_ENUM:
		break;
	case EGENRE::_ABSTRACTCONTAINER: 
		break;
	case EGENRE::_NAMESPACE:
		break;
	default: 
		printf("###UNRESOLVED###");
		break;
	}
}

const char* getExpressionString(EnumExpressionType e) {
	switch (e) {
	case EXPR_LIST: return "EXPR_LIST";
	case EXPR_THIS: return "EXPR_THIS";
	case EXPR_TYPEOF: return "EXPR_TYPEOF";	// + Type
	case EXPR_BASE: return "EXPR_BASE";
	case EXPR_CTE: return "EXPR_CTE";
	case EXPR_IDENT: return "EXPR_IDENT";
	case EXPR_REF: return "EXPR_REF";
	case EXPR_PLUSPLUS: return "EXPR_PLUSPLUS";
	case EXPR_MINUSMINUS: return "EXPR_MINUSMINUS";
	case EXPR_ARROW: return "EXPR_ARROW";		// + Id
	case EXPR_NOT: return "EXPR_NOT";		// !
	case EXPR_LNOT: return "EXPR_LNOT";		// ~
	case EXPR_ADRESSOF: return "EXPR_ADRESSOF";
	case EXPR_SIZEOF: return "EXPR_SIZEOF";	// + Type
	case EXPR_PREINCR: return "EXPR_PREINCR";
	case EXPR_PREDECR: return "EXPR_PREDECR";
	case EXPR_UNARYPLUS: return "EXPR_UNARYPLUS";
	case EXPR_UNARYMINUS: return "EXPR_UNARYMINUS";
	case EXPR_UNARYMULT: return "EXPR_MULT";
	case EXPR_IS: return "EXPR_IS";
	case EXPR_AS: return "EXPR_AS";
	case EXPR_UNCHECKED: return "EXPR_UNCHECKED";
	case EXPR_CHECKED: return "EXPR_CHECKED";
	case EXPR_ACCESS: return "EXPR_ACCESS";	// + Expr|Id
	case EXPR_NEW: return "EXPR_NEW";		// + Type
	case EXPR_DOT: return "EXPR_DOT";
	case EXPR_INVOKE: return "EXPR_INVOKE";
	case EXPR_CAST: return "EXPR_CAST";
	case EXPR_CAST_PTR: return "EXPR_CAST_PTR";
	case EXPR_MULT: return "EXPR_MULT";
	case EXPR_DIV: return "EXPR_DIV";
	case EXPR_MOD: return "EXPR_MOD";
	case EXPR_PLUS: return "EXPR_PLUS";
	case EXPR_MINUS: return "EXPR_MINUS";
	case EXPR_LSHFT: return "EXPR_LSHFT";
	case EXPR_RSHFT: return "EXPR_RSHFT";
	case EXPR_LESS: return "EXPR_LESS";
	case EXPR_MORE: return "EXPR_MORE";
	case EXPR_LESSEQ: return "EXPR_LESSEQ";
	case EXPR_MOREEQ: return "EXPR_MOREEQ";
	case EXPR_EQUTST: return "EXPR_EQUTST";
	case EXPR_DIFFTST: return "EXPR_DIFFTST";
	case EXPR_LAND: return "EXPR_LAND";
	case EXPR_LXOR: return "EXPR_LXOR";
	case EXPR_LOR: return "EXPR_LOR";
	case EXPR_AND: return "EXPR_AND";
	case EXPR_OR: return "EXPR_OR";
	case EXPR_XOR: return "EXPR_XOR";
	case EXPR_ASS_EQ: return "EXPR_ASS_EQ";
	case EXPR_ASS_PLUSEQ: return "EXPR_ASS_PLUSEQ";
	case EXPR_ASS_MINUSEQ: return "EXPR_ASS_MINUSEQ";
	case EXPR_ASS_STAREQ: return "EXPR_ASS_STAREQ";
	case EXPR_ASS_DIVEQ: return "EXPR_ASS_DIVEQ";
	case EXPR_ASS_MODEQ: return "EXPR_ASS_MODEQ";
	case EXPR_ASS_XOREQ: return "EXPR_ASS_XOREQ";
	case EXPR_ASS_ANDEQ: return "EXPR_ASS_ANDEQ";
	case EXPR_ASS_OREQ: return "EXPR_ASS_OREQ";
	case EXPR_ASS_RSHFTEQ: return "EXPR_ASS_RSHFTEQ";
	case EXPR_ASS_LSHFTEQ: return "EXPR_ASS_LSHFTEQ";
	case EXPR_COND: return "EXPR_COND";
	default: return "UNKOWN EXPRESSION";
	}
}

int dumpDepth = 0;
void Expression::dumpTree() {
	for (int m=0; m < dumpDepth; m++) { printf(" "); }	
	printf(getExpressionString(this->m_expressionType));
	if ((this->m_expressionType == EXPR_IDENT) || (this->m_expressionType == EXPR_INVOKE) || (this->m_expressionType == EXPR_DOT)) {
		printf(" %s ", this->m_text);
	}
	printf("\n");
	dumpDepth++;
	for (int n=0; n < m_expressionCount; n++) {
		if (m_expressions[n]) {
			m_expressions[n]->dumpTree();
		} else {
			for (int m=0; m < dumpDepth; m++) { printf(" "); }	
			printf("(null)\n");
		}
	}
	dumpDepth--;
}

SRSymbol Expression::resolveIteration(const char* text, SRSymbol input, TypeObject*& lastType, SRSymbol& item, u8 searchMask, Expression* methodSignature, Variable* delegateSignature, TypeGenericEntry* genParams) {
	SRSymbol res;
	/*
	if(searchFunction) {
		item = resolveSimpleSymbol(input,text,SEARCH_FUNCTION | SEARCH_INHERITANCE | SEARCH_HIERARCHY);
	}
	else {*/
	item = resolveSimpleSymbol(input, text, searchMask, methodSignature, delegateSignature, genParams);
	
	switch (item.symbolType) {
	case EGENRE::_MEMBER:
		{
			// Get Member
			Variable* pVar = (Variable*)item.pSymbol;

			// Get Type of Member & Resolve relative to member owner.
			res = pVar->m_type->getResolvedType(pVar->m_ownerClass);

			// Copy type here.
			lastType = pVar->m_type;
		}
		break;
	case EGENRE::_VARIABLE:
		{
			// Get Local Variable
			Variable* pVar = (Variable*)item.pSymbol;

			// Get Type of Member & Resolve relative to this class.
			// A method context is required as the type of the variable can be a local generic symbol.
			res = pVar->m_type->getResolvedType(gCurrentAC, gCurrentMethod);

			// Copy type here.
			lastType = pVar->m_type;
		}
		break;
	case EGENRE::_ACCESSOR:
		{
			Accessor* pAccessor = (Accessor*)item.pSymbol;
			res = pAccessor->m_type->getResolvedType(pAccessor->m_ownerClass);
			// Copy type
			lastType = pAccessor->m_type;
		}
		break;
	case EGENRE::_ABSTRACTCONTAINER:
		{
			AbstractContainer* pCnt = (AbstractContainer*)item.pSymbol;
			lastType = pCnt->getType();
			res = item;
		}
		break;
	case EGENRE::_NAMESPACE:
		{
			res = item;
			m_item = item;
			lastType = NULL;	// Expression should NEVER stop here.
		}
		break;
	case EGENRE::_ENUM:
		{
			Enum* pEnum = (Enum*)item.pSymbol;
			lastType = pEnum->getType();
			res = item;
		}
		break;
	case EGENRE::_ENUMENTRY:
		{
			Enum::EnumEntry* pEntry = (Enum::EnumEntry*)item.pSymbol;
			lastType = pEntry->m_parent->getType();
			res = item;
		}
		break;
    
	case EGENRE::_DELEGATE:
		{
			Delegate* pDelegate = (Delegate*)item.pSymbol;
			lastType = pDelegate->getType();
			res = item;
		}
		break;
    
	case EGENRE::_METHOD:
		{
			// Found a function.
			Method* pM = (Method*)item.pSymbol; // Workd for delegate.
			if(!pM->m_returnType) {
				if(pM->m_modifier & ATT_CTOR) {
					// Constructor
					res = pM->m_pOwner->getType()->m_res;
					pM->m_returnType = res.pType;
				}
				else {
					compilerError(ERR_INTERNAL, concat2("No return type for the method ", pM->getName()), m_line);
				}
			}
			else {
				// Resolve return type.
				res = pM->m_returnType->getResolvedType(pM->m_pOwner);
			}
			// Save type
			lastType = pM->m_returnType;
		}
		break;
	case EGENRE::_GENDEFENTRY:
		// Nothing to do
		break;
	case EGENRE::_METHODLIST:
		res = item;
		break;
	default:
		compilerError(ERR_INTERNAL,"Error EXPR_IDENT not solved.", m_line);
	}

	return res;
}

void transformIn_This(Expression* expr) {
	expr->m_expressionType = EXPR_DOT;

	Expression* sub = CreateLeafExpr(EXPR_UNDER_THIS);
	sub->m_runtimeType = gCurrentAC->getType();

	expr->addExpression(sub);
}

void Expression::AnalysisAndTransform() {
	if (this == NULL) { return; }

	if (this->m_expressionType == EXPR_DOT) {
		for(int n = 0 ; n < m_expressionCount ; n++) {
			m_expressions[n]->m_isDotRoot = false;
		}
	}

	if(this->m_expressionType != EXPR_INVOKE && this->m_delegateDef) {
		// Pass on delegate signature
		for(int n = 0 ; n < m_expressionCount ; n++) {
			m_expressions[n]->m_delegateDef = m_delegateDef;
		}
	}

	//
	// Those specifically need to control the recursion.
	//
	switch (this->m_expressionType) {
	case EXPR_INVOKE:
	case EXPR_PLUS:
	case EXPR_ASS_EQ:
	case EXPR_DELEGATECREATE:
	case EXPR_NEW:
	case EXPR_CAST:
		break;
	default:
		// Parse all sub expression
		for (int n=0; n < this->m_expressionCount; n++) {
			m_expressions[n]->AnalysisAndTransform();
		}
		break;
	}

	// . Transform indexer to get / set --> Really !? C++ not OK ?
	switch (this->m_expressionType) {
	// Multiple
	case EXPR_LIST:
	case EXPR_LIST_INIT:
		break;
	
	case EXPR_DELEGATECREATE:
		{
			if(this->m_item.symbolType == EGENRE::_DELEGATE) {
				// The expression has already been analysed.
				break;
			}
			Variable* pList = NULL;
			Variable* pListStart = NULL;

			if (!gIsStaticFunc) {
				Variable* pNew = new Variable();
				pNew->setType(gCurrentAC->getType());
				pNew->setName("_this__");
				this->m_anonymousClass->addMember(pNew);
				pList = pNew;
				pListStart = pList;
			}
		
			SymbolDictionary* pDic = gCurrentSD;
			while (pDic) {
				SymbolDictionary::VariableList* pVariable = pDic->m_list;
				while (pVariable) {
					if (pVariable->content) {
						if (pVariable->content->m_ignoreDelegate == false) {
							Variable* pNew = new Variable();

							if (pList) {
								pList->m_pNextVariable = pNew;
								pList = pNew;
							} else {
								pList = pNew;
								pListStart = pList;
							}
					
							pNew->setName(pVariable->content->getName());
							pNew->setType(pVariable->content->m_type);

							this->m_anonymousClass->addMember(pNew);
						}
					}
					pVariable = pVariable->pNext;
				}
				pDic = pDic->m_parent;
			}

			// Create Ctor with all member.
			Method* pMCtor = new Method();
			pMCtor->setName(this->m_anonymousClass->getName());
			pMCtor->m_modifier |= ATT_CTOR;
			pMCtor->m_parameters = pListStart;
			this->m_anonymousClass->addMethod(pMCtor);

			// Create calling method.
			Method* pM = new Method();
			pM->setName("_delegate");

			gTransformAsDelegate = true;
			pM->m_codeBlock		= this->m_delegateCode;
			pM->m_parameters	= this->m_delegateSignature;

			AbstractContainer* currClass = gCurrentAC;

			gCurrentAC = this->m_anonymousClass;
			// Create global dico + Add function parameters to dictionnary.
			if (gCurrentSD) {
				gCurrentSD = gCurrentSD->addDictionary();	// Inside a function.
			} else {
				gCurrentSD = new SymbolDictionary();		// Member init.
			}

			Variable* pParameter = pM->m_parameters;
			while(pParameter) {
				// Register variable as local symbols for code.
				gCurrentSD->addVariable(pParameter);
				pParameter = pParameter->m_pNextVariable;
			}

			pM->m_codeBlock->analysis();
			gCurrentAC = currClass;
			gTransformAsDelegate = false;

			// Destroy dico + Remove variable/parameters from dictionnary.
			gCurrentSD = gCurrentSD->removeDictionary();


			pM->m_parameters	= this->m_delegateSignature;
			// Get return type from recursion.
			pM->m_returnType	= this->m_delegateDef->m_returnType;

			this->m_anonymousClass->addMethod(pM);

			// Necessary for assignment operator test. (resolved like EXPR_DOT or EXPR_IDENT)
			this->m_item.symbolType = EGENRE::_DELEGATE;
		}

		break;
	// Leaf
	case EXPR_UNDER_THIS:
		// Do nothing.
		break;
	case EXPR_THIS:
		// Return type DONE
		this->m_runtimeType = gCurrentAC->getType();
		if (!gTransformAsDelegate) {
			// Do nothing.
		} else {
			//
			// Morphed itself into _this__ ! Yeah ! => Delegate
			//
			this->m_expressionType = EXPR_UNDER_THIS;
		}
		break;
	case EXPR_BASE: 
		{
			TypeObject* pParent = gCurrentAC->getAncestor(); 
			// Return type DONE
			this->m_runtimeType = pParent ? pParent : &t_OBJECT;
		}
		break;
	case EXPR_IDENT:
	case EXPR_DOT: 
		{
			if(m_delegateDef) {
				AnalysisMethodForDelegate(this->m_genericCall);
			}
			else {
				SRSymbol res;
				u8 searchMask;

				// Handle DOT or IDENT
				if (m_expressionCount == 0 || m_expressions[0] == NULL) {
					res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
					res.pSymbol		= gCurrentAC;
					searchMask		= SEARCH_ALL;
				} else {
					if(m_expressions[0]->m_runtimeType) {
						// Class / Enum / Namespace could be possible.
						res = m_expressions[0]->m_runtimeType->m_res;
					}
					else {
						// Namespaces don't have a runtime type
						res = m_expressions[0]->m_item;
					}
					searchMask = SEARCH_ALL & ~SEARCH_VARIABLE;
				}

				if(!m_isInvoked && !m_isDotRoot) {
					// Can't be a method
					searchMask &= ~SEARCH_FUNCTION;
				}

				res = resolveIteration(this->m_text, res, this->m_runtimeType,this->m_item, searchMask);
			}

			if (this->m_runtimeType && this->m_runtimeType->m_res.symbolType == EGENRE::_GENDEFENTRY && m_expressions[0]) {
				// Substitute generic type
				if(m_expressions[0]->m_runtimeType->m_res.symbolType == EGENRE::_ABSTRACTCONTAINER) {
					AbstractContainer* pAC = (AbstractContainer*)m_expressions[0]->m_runtimeType->m_res.pSymbol;
					TypeGenericDefinitionEntry* pGen = this->m_runtimeType->m_definitionGeneric;
					this->m_runtimeType = pAC->getGenericType(pGen, m_expressions[0]->m_runtimeType->m_generic);
				}
				else {
					compilerError(ERR_INTERNAL, "Template is not a class", m_expressions[0]->m_line);
				}
			}

			if (gTransformAsDelegate) { 
				// Insert a "_this + ." !, transform into EXPR_DOT.
				if (this->m_expressionType == EXPR_IDENT) {
					switch (this->m_item.symbolType) {
					case EGENRE::_MEMBER:
						{
							Variable* pVar = (Variable*)this->m_item.pSymbol;
							if ((pVar->m_modifier & ATT_STATIC) == 0) {
								transformIn_This(this);
							}
						}
						break;
					case EGENRE::_METHOD:
						{
							Method* pM = (Method*)this->m_item.pSymbol;
							if ((pM->m_modifier & ATT_STATIC) == 0) {
								transformIn_This(this);
							}
						}
						break;
					}
				}
			}

			if (g_analysis_static) {
				switch (this->m_item.symbolType) {
				case EGENRE::_MEMBER:
					{
						Variable* pVar = (Variable*)this->m_item.pSymbol;
						if (pVar->m_modifier & ATT_STATIC) {
							gStaticDepMatrix->createDependancy(gCurrVar, pVar);
						} else {
							compilerError(ERR_INTERNAL,"Non static member used in static assignement, WTF.", m_line);
						}
					}
					break;
				case EGENRE::_ACCESSOR:
				case EGENRE::_ABSTRACTCONTAINER:
				case EGENRE::_NAMESPACE:
				case EGENRE::_ENUM:
				case EGENRE::_DELEGATE:
				case EGENRE::_ENUMENTRY:
				case EGENRE::_METHOD:
					{
						// No dependancy.
					}
					break;
				default:
					compilerError(ERR_INTERNAL,"Unprocessed case", m_line);
				}
			}

			if(this->m_expressionCount > 0) {
					if(this->m_expressions[0]->m_item.symbolType == EGENRE::_ABSTRACTCONTAINER
					&& this->m_item.symbolType == EGENRE::_ABSTRACTCONTAINER) {
						// This inner class will be unnested, so its container should not be dumped.
						this->m_expressions[0]->m_bSkip = true;
				}
			}
		}
		break;
	case EXPR_INVOKE:
		{
			//Analyze generic symbols
			TypeGenericEntry* pGen = this->m_genericCall;
			while(pGen) {
				pGen->m_instanceType->getResolvedType(gCurrentAC, gCurrentMethod);
				pGen->m_genericName = pGen->m_instanceType->dumpTypeForCode(gCurrentAC, gCurrentMethod);
				pGen = pGen->m_pNext;
			}

			//
			// Descending and solving sub systems.
			//
			m_expressions[1]->AnalysisAndTransform();
			if(m_expressions[1]->isAmbiguous()) {
				// TODO : try every combinaison
				compilerError(ERR_NOT_SUPPORTED_YET, "Overloaded methods as method parameters are not supported yet", m_expressions[1]->m_line);
			}
			else {
				m_expressions[0]->AnalysisInvokeMethod(m_expressions[1], m_genericCall);
			}

			if (m_expressions[0]->m_runtimeType->m_res.symbolType == EGENRE::_GENDEFENTRY) {
				TypeGenericDefinitionEntry* pGen = m_expressions[0]->m_runtimeType->m_definitionGeneric;
				Method* pMethod = (Method*)m_expressions[0]->m_item.pSymbol;
				m_expressions[0]->m_runtimeType = pMethod->getGenericType(pGen, this->m_runtimeType->m_generic);
			}

			// Special case : method which returns a delegate
			if (m_expressions[0]->m_item.symbolType == EGENRE::_METHOD && m_expressions[0]->m_runtimeType->m_genreID == EGENRE::_DELEGATE) {
				switch(m_expressions[0]->m_expressionType)
				{
				case EXPR_IDENT :
				case EXPR_DOT :
					// Still a method at this level of the tree
					this->m_runtimeType = m_expressions[0]->m_runtimeType;
					this->m_item		= m_expressions[0]->m_item;
					break;
				case EXPR_INVOKE :	//getDelegate()() style
					{
						Delegate* pDelegate = m_expressions[0]->m_runtimeType->m_definitionDelegate;
						SRSymbol symbol;
						symbol.pSymbol = (Symbol*)pDelegate;
						symbol.pType = m_expressions[0]->m_runtimeType;
						symbol.symbolType = EGENRE::_DELEGATE;
						this->m_runtimeType = m_expressions[0]->m_runtimeType;
						this->m_item = symbol;
						break;
					}
				default:
					compilerError(ERR_INTERNAL,"The method is neither an identifier, an invoke nor a dot expression ?", m_expressions[0]->m_line);
					break;
				}
			}
			else if (m_expressions[0]->m_runtimeType == NULL) {
				compilerError(ERR_INTERNAL, "Unresolved invoke symbol", m_expressions[0]->m_line);
				SRSymbol notFound;
				notFound.symbolType	= EGENRE::_UNDEFGENRE;
				notFound.pSymbol	= createNotFoundSymbol();
				m_item = notFound;
				break;
			}
			else if (m_expressions[0]->m_runtimeType->m_genreID == EGENRE::_DELEGATE) {
				Delegate* pDelegate = m_expressions[0]->m_runtimeType->m_definitionDelegate;
				SRSymbol symbol;
				symbol.pSymbol = (Symbol*)pDelegate;
				symbol.pType = m_expressions[0]->m_runtimeType;
				symbol.symbolType = EGENRE::_DELEGATE;
				this->m_runtimeType = m_expressions[0]->m_runtimeType;
				this->m_item = symbol;
			} 
			else {
				//
				// Get the result of sub (EXPR_DOT) m_expressions[0].m_item.symbolType == EGENRE::_METHOD
				//
				if (m_expressions[0]->m_item.symbolType == EGENRE::_METHOD) {
					this->m_runtimeType = m_expressions[0]->m_runtimeType;
					this->m_item		= m_expressions[0]->m_item;
					Method* pMethod = (Method*)this->m_item.pSymbol;
					pMethod->resolveDefaultParams();
				} else {
					compilerError(ERR_INTERNAL, "Invoke not on a method, and it does not return a delegate", m_expressions[0]->m_line);
				}
			}

			if(m_expressions[1]) {
				// Transform the function parameters into delegates
				if(m_expressions[1]->m_expressionType == EXPR_LIST) {
					for(int n = 0 ; n < m_expressions[1]->m_expressionCount ; n++)
					{
						Expression*& pParam = m_expressions[1]->m_expressions[n];
						if(pParam->isMethodAsDelegate()) {
							transformMethodAsDelegate(pParam, n);
						}
						else if(pParam->m_expressionType == EXPR_COND) {
							for(int i = 1 ; i <= 2 ; i++) {
								Expression*& subExpr = pParam->m_expressions[i];
								if(subExpr->isMethodAsDelegate()) {
									if(subExpr->m_expressionType == EXPR_IDENT || subExpr->m_expressionType == EXPR_DOT) {
										compilerError(ERR_NOT_SUPPORTED_YET, "Please do not use the conditional operator with functions as a delegate-typed parameter", m_expressions[1]->m_line);
									}
									else {
										transformMethodAsDelegate(subExpr, n);
									}
								}
							}
						}
					}
				}
				else {
					compilerError(ERR_INTERNAL, "Method parameters are supposed to be a list", m_expressions[1]->m_line);
				}
			}

			//
			// Return type DONE EXPR_INVOKE.
			//
		}
		break;

	// Double
	case EXPR_ACCESS:
		{
			// Same as invoke.

			//
			// Descending and solving sub systems.
			//
			m_expressions[0]->AnalysisAndTransform();
			m_expressions[1]->AnalysisAndTransform();

			TypeObject* classType = m_expressions[0]->m_runtimeType;

			// Solve which accessor need to be called.
			Accessor* pAccessor = classType->m_definitionAC->findPropertyIndexer(m_expressions[1]);
			pAccessor->m_type->getResolvedType(classType->m_definitionAC);
			if(pAccessor->m_type->m_genreID == EGENRE::_GENDEFENTRY) {
				if(classType->m_originalType) {
					// Get the type of the array
					this->m_runtimeType = classType->m_originalType;
				}
				else if(classType->m_generic) {
					AbstractContainer* pAC = classType->m_definitionAC;
					TypeGenericDefinitionEntry *pGen = pAccessor->m_type->m_definitionGeneric;
					this->m_runtimeType = pAC->getGenericType(pGen, classType->m_generic);
				}
				else {
					compilerError(ERR_INTERNAL, "The class uses a generic variable, but its instance has no generic parameter", m_expressions[0]->m_line);
				}
			}
			else {
				// Get the output type of the accessor.
				this->m_runtimeType	= pAccessor->m_type;
			}

			if(classType->m_originalType) {
				// Local resolution context
				NameSpace*	contextNameSpace	= NULL;
				Method*		contextMethod		= NULL;
				getContext(this->m_expressions[0]->m_item.pSymbol, contextNameSpace, contextMethod);
				this->m_item = this->m_runtimeType->getResolvedType(contextNameSpace, contextMethod);
			}
			else {
				this->m_item = this->m_runtimeType->getResolvedType(pAccessor->m_ownerClass);
			}
		}
		break;

	case EXPR_CTE: 
		switch (this->m_value.type) {
		case TYPE_BOOL:
			this->m_runtimeType = &t_BOOL;
			break;
		case TYPE_STRING:
			this->m_runtimeType = &t_STRING;
			break;
		case TYPE_NULL: 
			this->m_runtimeType = &t_NULL;
			break;
		case TYPE_DOUBLE:
			this->m_runtimeType = &t_DOUBLE;
			break;
		case TYPE_FLOAT:
			this->m_runtimeType = &t_FLOAT;
			break;
		case TYPE_INT:
			this->m_runtimeType = &t_INT;
			break;
		case TYPE_UINT:
			this->m_runtimeType = &t_UINT;
			break;
		case TYPE_LONG:
			this->m_runtimeType = &t_LONG;
			break;
		case TYPE_ULONG:
			this->m_runtimeType = &t_ULONG;
			break;
		case TYPE_CHAR:
			this->m_runtimeType = &t_CHAR;
			break;
		default:
			compilerError(ERR_INTERNAL,"internal error dump expression CTE", m_line);
			break;
		}
		// Return type DONE (for each case)
		break;

	case EXPR_NOT: 
		// Return type DONE
		m_runtimeType = &t_BOOL;
		break;		// !
	case EXPR_PLUSPLUS: 
	case EXPR_MINUSMINUS: 
	case EXPR_PREINCR:
	case EXPR_PREDECR: 
		// Return type DONE (same type)
		m_runtimeType = m_expressions[0]->m_runtimeType;
		if(m_expressions[0]->m_expressionType != EXPR_ACCESS) {
			m_expressions[0]->m_isAssignmentSide = true;
		}
		m_item = m_expressions[0]->m_item;
		break;
	case EXPR_LNOT: 
	case EXPR_UNARYPLUS: 
	case EXPR_UNARYMINUS: 
		// Return type DONE (same type)
		m_runtimeType = m_expressions[0]->m_runtimeType;
		break;

	case EXPR_IS:
		// Return type DONE (Override Type by result of IS)
		this->m_typeParam->getResolvedType(gCurrentAC);
		this->m_runtimeType = &t_BOOL;
		break;
	case EXPR_AS: 
		// Return type DONE
		this->m_typeParam->getResolvedType(gCurrentAC);
		this->m_runtimeType = this->m_typeParam;
		break;

	case EXPR_NEW: 
		// The parameter type is actually stored in m_runtimeType
		this->m_typeParam = this->m_runtimeType;
		this->m_typeParam->getResolvedType(gCurrentAC);

		m_expressions[0]->AnalysisAndTransform();

		if (m_expressionCount == 2) {
			m_expressions[1]->AnalysisAndTransform();
			bool hasInitializer = (m_expressions[1] != NULL);

			if (hasInitializer) {
				// Already done. m_expressions[1]->AnalysisAndTransform();
				m_expressions[1]->m_initializerInfo->m_typeArray = this->m_typeParam;
			}
		} else {
			if (this->m_typeParam->isGC_Able()) {
				// Ok.
			} else {
				compilerError(ERR_NOT_SUPPORTED, "Impossible to use new with struct or basic type", m_line);
			}
		}
		break;		// + Type
	
	// Double
	case EXPR_CAST: 
		if (this->m_expressionCount == 2) {
			// Look for a type only
			SRSymbol context;
			Expression* castTypeExpr = this->m_expressions[0];
			if(castTypeExpr->m_expressionCount > 0) {
				Expression* dotPrefix = castTypeExpr->m_expressions[0];
				dotPrefix->AnalysisAndTransform();
				context = dotPrefix->m_runtimeType ? dotPrefix->m_runtimeType->m_res : dotPrefix->m_item;
			}
			else {
				context.pSymbol			= gCurrentAC;
				context.symbolType		= EGENRE::_ABSTRACTCONTAINER;
			}
			u8 searchMask = SEARCH_TYPE | SEARCH_INHERITANCE | SEARCH_HIERARCHY; // Look for a type only.

			castTypeExpr->m_item = resolveIteration(castTypeExpr->m_text, context, castTypeExpr->m_runtimeType, castTypeExpr->m_item, searchMask);
			this->m_expressions[1]->AnalysisAndTransform();
			this->m_expressions[0]->m_runtimeType->getResolvedType(gCurrentAC);
			this->m_runtimeType = this->m_expressions[0]->m_runtimeType;
			this->m_item = this->m_expressions[1]->m_item;
		}
		else {
			m_expressions[0]->AnalysisAndTransform();
			m_item = m_expressions[0]->m_item;
		}
		break;

	case EXPR_PLUS: 
		// Return type DONE
		{

			m_expressions[0]->AnalysisAndTransform();
			m_expressions[1]->AnalysisAndTransform();

			bool left_IsString = (m_expressions[0]->m_runtimeType->m_typeID == TYPE_STRING); 
			bool rightIsString = (m_expressions[1]->m_runtimeType->m_typeID == TYPE_STRING);
			bool left_IsAdd	   = (m_expressions[0]->m_expressionType == EXPR_PLUS);
			bool rightIsAdd	   = (m_expressions[1]->m_expressionType == EXPR_PLUS);
	
			if (left_IsString) {
				if (!left_IsAdd) {
					this->wrapStringStart = true;
				} else {
					if (rightIsString && rightIsAdd) {
						// TODO STRING Rebalance tree.
					}
				}
				if (m_expressions[1]->m_runtimeType->m_genreID == EGENRE::_ENUM) {
					compilerError(ERR_NOT_SUPPORTED_YET, "Impossible to use Enum with String concatenation in C++ version.", m_line);
				}
				this->m_runtimeType = m_expressions[0]->m_runtimeType;
			} else {
				this->m_runtimeType = m_expressions[0]->m_runtimeType->getResolvedBlend(m_expressions[1]->m_runtimeType);
			}
		}
		break;

	case EXPR_MULT: 
	case EXPR_DIV: 
	case EXPR_MOD: 
	case EXPR_MINUS: 

		// Return type DONE
		this->m_runtimeType = m_expressions[0]->m_runtimeType->getResolvedBlend(m_expressions[1]->m_runtimeType);
		break;

	case EXPR_LSHFT: 
	case EXPR_RSHFT: 
		// Just copy from left side
		// Return type DONE
		this->m_runtimeType = m_expressions[0]->m_runtimeType;
		break;

	case EXPR_LESS: 
	case EXPR_MORE: 
	case EXPR_LESSEQ: 
	case EXPR_MOREEQ: 
	case EXPR_EQUTST: 
	case EXPR_DIFFTST: 
		// Just copy from left side
		// Return type DONE
		this->m_runtimeType = &t_BOOL;
		break;

	case EXPR_LAND: 
	case EXPR_LXOR: 
	case EXPR_LOR: 
		// Operator
		// Return type DONE
		this->m_runtimeType = m_expressions[0]->m_runtimeType->getResolvedBlend(m_expressions[1]->m_runtimeType);
		break;

	case EXPR_AND: 
	case EXPR_OR: 
		// Return type DONE
		this->m_runtimeType = &t_BOOL;
		break;

	// Double (Assignment)
	case EXPR_ASS_EQ:
		{
			m_expressions[0]->m_isAssignmentSide = true;

			bool assignDelegate = false;

			m_expressions[0]->AnalysisAndTransform();

			// After resolution.
			m_item = m_expressions[0]->m_item;
			this->m_runtimeType = m_expressions[0]->m_runtimeType;

			if (m_expressions[0]->m_runtimeType->m_genreID == EGENRE::_DELEGATE) {
				// FIRST, Pass delegate signature to sub expression on left.
				m_expressions[1]->m_delegateDef = m_expressions[0]->m_runtimeType->m_definitionDelegate;
				assignDelegate = true;
			}

			processDelegateAssignment(m_expressions[1], m_expressions[0]->m_runtimeType, assignDelegate);

			Expression::patchExpressionsForListExpressions(&m_expressions[1],this->m_runtimeType);
			m_expressions[1]->AnalysisAndTransform();
		}
		break;
	case EXPR_ASS_PLUSEQ: 
	case EXPR_ASS_MINUSEQ:
	case EXPR_ASS_STAREQ: 
	case EXPR_ASS_DIVEQ: 
	case EXPR_ASS_MODEQ: 
	case EXPR_ASS_XOREQ: 
	case EXPR_ASS_ANDEQ: 
	case EXPR_ASS_OREQ: 
	case EXPR_ASS_RSHFTEQ: 
	case EXPR_ASS_LSHFTEQ: 
		// Just copy from left side
		// Return type DONE
		this->m_runtimeType = m_expressions[0]->m_runtimeType;
		if(m_expressions[0]->m_expressionType != EXPR_ACCESS) {
			m_expressions[0]->m_isAssignmentSide = true;
		}
		m_item = m_expressions[0]->m_item;
		break;
	case EXPR_REF:
		this->m_runtimeType = m_expressions[0]->m_runtimeType;
		m_item = m_expressions[0]->m_item;
		break;

	// Triple
	case EXPR_COND:
		// Return type DONE
		this->m_runtimeType = m_expressions[1]->m_runtimeType->getResolvedBlend(m_expressions[2]->m_runtimeType);
		break;
	case EXPR_UNARYMULT:
	case EXPR_CAST_PTR:
	case EXPR_UNCHECKED: 
	case EXPR_ADRESSOF:
	case EXPR_ARROW: 
	case EXPR_SIZEOF:
	case EXPR_TYPEOF:
	case EXPR_CHECKED: 
		// Not Supported, error handled at parser level.
		break;
	default:
		compilerError(ERR_INTERNAL, "Internal Error, unknown Expression Type", m_line);
	}

	if (this->m_expressionType != EXPR_PLUS) {
		for (int n=0; n < this->m_expressionCount; n++) {
			Expression* expr = m_expressions[n];
			if (expr) {
				if (expr->m_expressionType == EXPR_PLUS) {
					bool left_IsString = (expr->m_expressions[0]->m_runtimeType->m_typeID == TYPE_STRING);
					if (left_IsString) {
						expr->wrapStringEnd = true;
					}
				}
			}
		}
	}
}	

void Expression::AnalysisMethodForDelegate(TypeGenericEntry* genParams) {
	if(m_delegateDef) {
		// Analyse the delegate signature
		Variable* pParam = m_delegateDef->m_parameters;
		while(pParam) {
			pParam->m_type->getResolvedType(m_delegateDef->m_pOwner);
			pParam = pParam->m_pNextVariable;
		}

		// Resolve the method parameters
		if(this->m_expressionType == EXPR_LIST) {
			for(int n = 0 ; n < m_expressionCount ; n++) {
				m_expressions[n]->m_delegateDef = this->m_delegateDef;
				m_expressions[n]->AnalysisMethodForDelegate(genParams);
			}
		}
		else {
			SRSymbol context;
			if(this->m_expressionCount > 0) {
				m_expressions[0]->AnalysisAndTransform();
				context = m_expressions[0]->m_runtimeType->m_res;
			}
			else {
				context.pSymbol		= (AbstractContainer*)gCurrentAC;
				context.symbolType	= EGENRE::_ABSTRACTCONTAINER;
			}
			resolveIteration(this->m_text, context, this->m_runtimeType,this->m_item, SEARCH_ALL, NULL, m_delegateDef->m_parameters, genParams);
			if(this->m_item.symbolType == EGENRE::_UNDEFGENRE) {
				compilerError(ERR_INTERNAL, "Method not found", m_line);
			}
		}
	}
	else {
		compilerError(ERR_INTERNAL, "No delegate definition", m_line);
	}
}

void Expression::AnalysisInvokeMethod(Expression* signature, TypeGenericEntry* genParams) {
	if(this == NULL) {
		return;
	}
	if(!this->m_text) {
		AnalysisAndTransform();
		return;
	}
	SRSymbol context;
	if(this->m_expressionCount > 0) {
		m_expressions[0]->AnalysisAndTransform();
		context = m_expressions[0]->m_runtimeType->m_res;
	}
	else {
		context.pSymbol		= (AbstractContainer*)gCurrentAC;
		context.symbolType	= EGENRE::_ABSTRACTCONTAINER;
	}
	resolveIteration(this->m_text, context, this->m_runtimeType,this->m_item, SEARCH_ALL, signature, NULL, genParams);
	if(this->m_item.symbolType == EGENRE::_UNDEFGENRE) {
		compilerError(ERR_INTERNAL, "Method not found", m_line);
	}
}

// "this" needs to be the invocation expression.
void Expression::transformMethodAsDelegate(Expression*& methodParam, int paramRank) {
	Method* callingMethod = (Method*)m_expressions[0]->m_item.pSymbol;
	Variable* pMatchingParam = callingMethod->m_parameters;
	for(int i = 0 ; i < paramRank ; i++) {
		pMatchingParam = pMatchingParam->m_pNextVariable;
	}
	processDelegateAssignment(methodParam, pMatchingParam->m_type, true);
}

void dumpStringWrapper(Expression* expr) {
	if(expr->m_expressionType == EXPR_ASS_EQ) {
		// TODO : if str = a + b -> new else if str1 = str2 simple pointer copy => no CS_NEW
		expr->m_expressions[0]->dumpExpressionInternal(); printf(" = CS_NEW System::String()->appendStr("); expr->m_expressions[1]->dumpExpressionInternal(); printf(")->appendClose()");
		// TODO : Update reference counting
	}
	else if(expr->m_expressionType == EXPR_ASS_PLUSEQ) {
		const char* wrapperFunction;

		switch(expr->m_expressions[1]->m_runtimeType->m_typeID) {
		case TYPE_STRING :
			wrapperFunction = "_appendStr";
			break;
		case TYPE_CHAR :
			wrapperFunction = "_appendC";
			break;
		case TYPE_LONG :
			wrapperFunction = "_appendL";
			break;
		case TYPE_ULONG :
			wrapperFunction = "_appendUL";
			break;
		case TYPE_INT :
			wrapperFunction = "_appendI";
			break;
		case TYPE_UINT :
			wrapperFunction = "_appendU";
			break;
		case TYPE_SHORT :
			wrapperFunction = "_appendS";
			break;
		case TYPE_USHORT :
			wrapperFunction = "_appendUS";
			break;
		case TYPE_SBYTE :
			wrapperFunction = "_appendS8";
			break;
		case TYPE_BYTE :
			wrapperFunction = "_appendU8";
			break;
		case TYPE_FLOAT :
			wrapperFunction = "_appendF";
			break;
		case TYPE_DOUBLE :
			wrapperFunction = "_appendD";
			break;
		case TYPE_BOOL :
			wrapperFunction = "_appendB";
			break;
		default :
			compilerError(ERR_INTERNAL, "String concatenation with an unknown type", expr->m_expressions[1]->m_line);
			break;
		}

		expr->m_expressions[0]->m_isAssignmentSide = false;
		expr->m_expressions[0]->dumpExpressionInternal();
		printf(" = ");
		expr->m_expressions[0]->dumpExpressionInternal();
		Variable* pVar = (Variable*)expr->m_expressions[0];
		if(pVar->m_modifier & ATT_STATIC) {
			printf("::");
		}
		else {
			printf("->");
		}
		printf(wrapperFunction); printf("("); expr->m_expressions[1]->dumpExpressionInternal(); printf(")->_appendClose()");
	}
	else {
		compilerError(ERR_INTERNAL, "Only = and += operators should be wrapped for strings", expr->m_line);
	}
}

void dumpWrapper(Expression* expr, bool safe) {
	const char* preStd;		// Pre
	const char* postStd;	// Post
	const char* opt;
	const char* safeS = safe ? "$" : "";

	if(expr->m_runtimeType->m_typeID == TYPE_STRING && expr->m_expressionType == EXPR_ASS_PLUSEQ) {
		// Specific string wrapping
		compilerError(ERR_NOT_SUPPORTED_YET, "TODO : String wrapper", expr->m_line);
		dumpStringWrapper(expr);

		// Ignore the rest of the function
		return;
	}

	if(expr->m_expressionType == EXPR_ASS_EQ && expr->m_expressions[0]->m_expressionType == EXPR_ACCESS) {
		// Special wrapping for array[i] = value
		expr->m_expressions[0]->dumpExpressionInternal();
		expr->m_expressions[1]->dumpExpressionInternal();
		printf(")");

		// Early return
		return;
	}

	bool testDiv = ((expr->m_runtimeType->m_typeID & (ET_BASETYPE | ET_NUMBER))==ET_BASETYPE);

	bool forceWrapper = false;
	preStd="";
	switch (expr->m_expressionType) {
	case EXPR_PLUSPLUS:		opt = "postInc";	preStd="";		postStd="++";
		break;
	case EXPR_MINUSMINUS:	opt = "postDec";	preStd="";		postStd="--";
		break;
	case EXPR_PREINCR:		opt = "preInc";		preStd="++";	postStd="";
		break;
	case EXPR_PREDECR:		opt = "preDec";		preStd="--";	postStd="";
		break;
	case EXPR_ASS_EQ:		opt = "";							postStd=" = ";
		break;
	case EXPR_ASS_PLUSEQ:	opt = "AddEq";						postStd=" += ";
		break;
	case EXPR_ASS_MINUSEQ:	opt = "SubEq";						postStd=" -= ";
		break;
	case EXPR_ASS_STAREQ:	opt = "MulEq";						postStd=" *= ";
		break;
	case EXPR_ASS_DIVEQ:	opt = "DivEq";						postStd=" /= ";	forceWrapper = testDiv; // Div 0 except
		break;
	case EXPR_ASS_MODEQ:	opt = "ModEq";						postStd=" %%= "; forceWrapper = testDiv; // Div 0 except
		break;
	case EXPR_ASS_XOREQ:	opt = "XorEq";						postStd=" ^= ";
		break;
	case EXPR_ASS_ANDEQ:	opt = "AndEq";						postStd=" &= ";
		break;
	case EXPR_ASS_OREQ:		opt = "OrEq";						postStd=" |= ";
		break;
	case EXPR_ASS_RSHFTEQ:	opt = "RShiftEq";					postStd=" >>= ";
		break;
	case EXPR_ASS_LSHFTEQ:	opt = "LShiftEq";					postStd=" <<= ";
		break;
	default:
		compilerError(ERR_INTERNAL,"Unknown case", expr->m_line);
		break;
	}

	/*
		-> Accessor if safe		mode -> call safe
					if unsafe	mode -> call unsafe

		-> Member : if safe 	mode -> call safe
					if unsafe	mode -> generate C++ directly

		-> Static member : no safe operator do += directly

		-> Variable : always generate C++ directly
	 */
	const char* prefix = "";
	const char* name   = "";
	bool isStatic	= false;
	bool useWrapper = false;
	bool useRefWrapper = false;
	AbstractContainer* structDef = NULL;

	switch (expr->m_item.symbolType) {
	case EGENRE::_ACCESSOR:
		{
			prefix = "_acc";
			Accessor* pAcc = (Accessor*)expr->m_item.pSymbol;
			if (pAcc->m_modifier & ATT_STATIC) {
				isStatic = true;				
			}
			name = pAcc->getName();
			useWrapper = true;
		}
		break;
	case EGENRE::_MEMBER:
		{
			prefix = "";

			Variable* pVar = (Variable*)expr->m_item.pSymbol;

			bool isEnum					= (pVar->m_type->m_genreID == EGENRE::_ENUM);
			bool isNonNum				= ((pVar->m_type->m_typeID & (ET_BASETYPE | ET_NUMBER))==ET_BASETYPE);
			bool isPtr					= (pVar->m_type->isGC_Able());
			EnumExpressionType EType	= expr->m_expressionType;
			bool isEnumSpecialWrapper		= (isEnum && (EType == EXPR_PLUSPLUS || EType == EXPR_MINUSMINUS || EType == EXPR_PREINCR || EType == EXPR_PREDECR || EType == EXPR_ASS_PLUSEQ || EType == EXPR_ASS_MINUSEQ));
			bool isNumSpecialWrapper		= ((isNonNum == false && isPtr == false) && (EType == EXPR_ASS_MODEQ));
			bool isSpecialWrapper			= isEnumSpecialWrapper || isNumSpecialWrapper;

			bool isStruct				= (pVar->m_ownerClass->m_modifier & ATT_STRUCT) != 0;

			useRefWrapper = (isPtr || isStruct) && (expr->m_expressionType == EXPR_ASS_EQ);
			
			if (isStruct) {
				structDef = pVar->m_ownerClass;
			}

			if (pVar->m_modifier & ATT_STATIC) {
				isStatic = true;
				if(isSpecialWrapper) {
					// Wrap operators which only exist in C#
					useWrapper = true;
				}
			} else {
				useWrapper = (safe || isSpecialWrapper);
			}
			name = pVar->getName();
		}
		break;
	case EGENRE::_VARIABLE:
		// useWrapper = false
		{
			Variable* pVar = (Variable*)expr->m_item.pSymbol;
			name = pVar->getName();

			// If variable is int/long like -> Need to have a wrapper for divide and modulo for exception.
			if (testDiv && ((expr->m_expressionType == EXPR_ASS_DIVEQ) || (expr->m_expressionType == EXPR_ASS_MODEQ))) {
				if (expr->m_expressionType == EXPR_ASS_DIVEQ) {
					printf("UtilDiv::_divBy(");
				}

				if (expr->m_expressionType == EXPR_ASS_MODEQ) {
					printf("UtilDiv::_modBy(");
				}
				printf(name);
				printf(",");
				expr->m_expressions[1]->dumpExpressionInternal();
				printf(")");
			
				// Stop here.
				return;
			} else if (!testDiv && (expr->m_expressionType == EXPR_ASS_MODEQ)) {
				// Wrap %= operator for float types
				printf("UtilDiv::_modBy(");
				printf(name);
				printf(",");
				expr->m_expressions[1]->dumpExpressionInternal();
				printf(")");

				// Stop here.
				return;
			} else if ((pVar->m_type->m_genreID == EGENRE::_ENUM) &&
				(expr->m_expressionType == EXPR_PLUSPLUS || expr->m_expressionType == EXPR_MINUSMINUS || expr->m_expressionType == EXPR_PREINCR ||
				expr->m_expressionType == EXPR_PREDECR || expr->m_expressionType == EXPR_ASS_PLUSEQ || expr->m_expressionType == EXPR_ASS_MINUSEQ)) {
				// Wrap additive operator for enum type
				const char* pStrType = pVar->m_type->getFullName(pVar->m_ownerClass);
				switch(expr->m_expressionType) {
				case EXPR_PLUSPLUS :
					printf("(");printf(pStrType);printf(")(((s32&)");printf(name);printf(")++)");
					break;
				case EXPR_MINUSMINUS :
					printf("(");printf(pStrType);printf(")(((s32&)");printf(name);printf(")--)");
					break;
				case EXPR_PREINCR :
					printf("(");printf(pStrType);printf(")(++((s32&)");printf(name);printf("))");
					break;
				case EXPR_PREDECR :
					printf("(");printf(pStrType);printf(")(--((s32&)");printf(name);printf("))");
					break;
				case EXPR_ASS_PLUSEQ :
					printf(name);printf(" = (");printf(pStrType);printf(")((s32)");printf(name);printf(" + ");expr->m_expressions[1]->dumpExpressionInternal();printf(")");
					break;
				case EXPR_ASS_MINUSEQ :
					printf(name);printf(" = (");printf(pStrType);printf(")((s32)");printf(name);printf(" - ");expr->m_expressions[1]->dumpExpressionInternal();printf(")");
					break;
				default :
					compilerError(ERR_INTERNAL, "Only ++, --, += and -= operators should be wrapped for enum variables", expr->m_line);
					break;
				}

				// Stop here.
				return;
			}
		}
		break;
	case EGENRE::_METHOD:
		// Generate an L-Value, normal operation.
		// useWrapper = false
		break;
	case EGENRE::_ABSTRACTCONTAINER:
		if(expr->m_expressions[0]->m_expressionType == EXPR_ACCESS) {
			// identifier[index]++ syntax
			break;
		}
		else {
			compilerError(ERR_INTERNAL," Assignment operator on unknown type", expr->m_expressions[0]->m_line);
		}
		break;
	default:
		compilerError(ERR_INTERNAL," Assignment operator on unknown type", expr->m_line);
	}

	bool finalUseWrapper = useWrapper || forceWrapper || useRefWrapper;

	if (finalUseWrapper) {
		expr->m_expressions[0]->dumpExpressionInternal();
		printf(prefix);
		printf("_s");
		printf(name);
		if (useWrapper && !isStatic) { // use $ only when 
			printf(safeS);
		}
		printf(opt);
		printf("(");
		if (expr->m_expressionCount == 2) {
			expr->m_expressions[1]->dumpExpressionInternal();
		}
		printf(")");
	} else {
		printf(preStd);
		expr->m_expressions[0]->dumpExpressionInternal();
		printf(name);
		printf(postStd);
		if (expr->m_expressionCount == 2) {
			expr->m_expressions[1]->dumpExpressionInternal();
		}
	}
}

void writeMemberOrAccessor(u32 modifier, bool isAccessor, const char* name, bool hasPrevious, bool isAssign, bool isStruct) {
	const char* prefix = isAccessor ? "_acc" : "";
	bool isStatic			= (modifier & ATT_STATIC);
	if (hasPrevious) {
		if (isStatic) {
			printf("::");	
		} else {
			if (!isStruct) {
				printf("->");
			} else {
				printf(".");
			}
		}
	}

	if(!isAssign) {
		if (g_unsafe == true || isStatic == true) {
			if(isAccessor) {
				printf("_acc_g%s()", name);
			} else {
				printf(name);		// member name
			}
			if(g_unsafeEphemeral) { g_unsafe = false; g_unsafeEphemeral = false; }
		} else {
			printf(prefix);
			printf("_g%s$()", name);
		}
	} else {
		// We generate the last dump at the affectation level.
	}
}

void Expression::dumpTokens(SRSymbol res, const char* id, bool hasPrevious) {
	SRSymbol item = m_item;

	//res = resolveIteration(id, res, this->m_runtimeType, item);

	switch (item.symbolType) {
	case EGENRE::_METHOD:
		{
			Method* pM = (Method*)item.pSymbol;
			// EXPR_INVOKE
			if (this->m_expressionCount == 2) {
				if (hasPrevious) {
					pM->preFunc();						
				}
				pM->dumpCall(m_expressions[1], false, m_genericCall);
				compilerError(ERR_INTERNAL, "The compiler is not supposed to stop here.", m_line);
			} else {
				if(this->m_isInvoked) {
					if(!hasPrevious && pM->m_pOwner != gCurrentAC) {
						printf("%s::", pM->m_pOwner->getFullName(gCurrentAC));
					}
				}
				else {
					// Method as a delegate
					if(pM->m_pOwner == gCurrentAC) {
						printf("&%s", pM->getName());
					}
					else {
						printf("&%s::%s", pM->m_pOwner->getFullName(gCurrentAC), pM->getName());
					}
				}
			}
		}
		break;
	case EGENRE::_VARIABLE:
		{
			if (!m_isAssignmentSide) {
				// Local variable
				printf(id);
			}
		}
		break;
	case EGENRE::_MEMBER:
		{
			//
			// ::member			(CLASS Static)
			// member			(CLASS Instance / Class Static) Unsafe
			// ->member			(CLASS)							Unsafe
			// ->_g$member()	(CLASS)							Safe Read
			//   _s$member(val)	(CLASS)							Safe Write
			// .member			(STRUCT)
			// this->member		(STRUCT with this)
			//
			Variable* pVar = (Variable*)item.pSymbol;
			if(!hasPrevious) {
				// Dump prefix
				if(pVar->m_ownerClass != gCurrentAC) {
					printf("%s::", pVar->m_ownerClass->getFullName(gCurrentAC));
				}
			}
			writeMemberOrAccessor(pVar->m_modifier, false, id, hasPrevious, m_isAssignmentSide,((pVar->m_ownerClass->m_modifier & ATT_STRUCT) != 0));
		}
		break;
	case EGENRE::_ACCESSOR:
		{
			Accessor* pAcc = (Accessor*)item.pSymbol;
			if(!hasPrevious) {
				// Dump prefix
				if(pAcc->m_ownerClass != gCurrentAC) {
					printf("%s::", pAcc->m_ownerClass->getFullName(gCurrentAC));
				}
			}
			writeMemberOrAccessor(pAcc->m_modifier, true, id, hasPrevious, m_isAssignmentSide,((pAcc->m_ownerClass->m_modifier & ATT_STRUCT) != 0));
		}
		break;
	case EGENRE::_ABSTRACTCONTAINER:
	case EGENRE::_NAMESPACE:
		{
			if (hasPrevious) {
				printf("::");
			}
			bool arrayDump = false;
			if(item.symbolType == EGENRE::_ABSTRACTCONTAINER) {
				AbstractContainer* pSpace = (AbstractContainer*)item.pSymbol;
				if(pSpace->myType.m_typeID == TYPE_ARRAY) {
					arrayDump = true;
				}
			}
			NameSpace* pSpace = (NameSpace*)item.pSymbol;
			if(arrayDump) {
				printf("System::AbstractArray");
			}
			else {
				printf("%s", hasPrevious ? pSpace->getName() : pSpace->getFullName(gCurrentAC));
			}
		}
		break;
	case EGENRE::_ENUM:
		{
			// No dependancy.
			Enum* pEnum = (Enum*)item.pSymbol;
			if (hasPrevious) {
				printf("::");
			}
			else {
				// Dump prefix
				if(pEnum->m_parent != gCurrentAC) {
					printf("%s::", pEnum->m_parent->getFullName(gCurrentAC));
				}
			}
			printf("%s", pEnum->m_name);
		}
		break;
	case EGENRE::_ENUMENTRY:
		{
			// No dependancy.
			Enum::EnumEntry* pEnumEntry = (Enum::EnumEntry*)item.pSymbol;
			if (hasPrevious) {
				printf("::");
			}
			else {
				// Should not happen
				printf("%s::", pEnumEntry->m_parent->getFullName(gCurrentAC));
			}
			printf("%s", pEnumEntry->m_name);
		}
		break;
	case EGENRE::_DELEGATE:
		{
			Delegate* pDelegate = (Delegate*)item.pSymbol;
			if (hasPrevious) {
				printf("::");
			}
			else {
				// Dump prefix
				if(pDelegate->getOwner() != gCurrentAC) {
					printf("%s::", pDelegate->getOwner()->getFullName(gCurrentAC));
				}
			}
			printf("_Delegate_Base_%s", pDelegate->getName());
		}
		break;
	default:
		compilerError(ERR_INTERNAL,"Unprocessed case", m_line);
	}

	hasPrevious	= true;

}

const char* Method::getTemplateParams() {
	char buff[500];
	buff[0] = 0;
	char* ptr = buff;
	int delta;

	if(m_genericParam) {
		TypeGenericDefinitionEntry* genericSymbol = m_genericParam;
		sprintf(ptr++, "<");
		while(genericSymbol) {
			delta = sprintf(ptr, "%s", genericSymbol->m_genericName);
			ptr += delta;
			if(genericSymbol = genericSymbol->m_pNextGenericEntry) {
				sprintf(ptr, ", ");
				ptr += 2;
			}
		}
		sprintf(ptr, ">");
	}
	else {
		// The method is not a template.
	}
	return concat(buff);
}

void Method::dumpTemplateLabel() {
	if(m_genericParam) {
		TypeGenericDefinitionEntry* genericSymbol = m_genericParam;
		printf("template <");
		while(genericSymbol) {
			printf("typename %s", genericSymbol->m_genericName);
			if(genericSymbol = genericSymbol->m_pNextGenericEntry) {
				printf(", ");
			}
		}
		printf("> ");
	}
	else {
		// The class is not a template.
	}
}


void Method::preFunc() {
	if (this->m_modifier & ATT_STATIC) {
		printf("::");
	} else {
		if (this->m_pOwner->m_modifier & ATT_STRUCT) {
			printf(".");
		} else {
			printf("->");
		}
	}
}

void Method::dumpMarshalling() {
	tab(); printf("{\n");
	depth++;

	// Convention for ref/out parameters : use pointers on the C++ side

	// int, uint, float, double, bool, long, ...
	// struct
	// ref
	// IntPtr
	// []BaseType ou []IntPtr
	//
	bool isVoid = (this->m_returnType->m_typeID == TYPE_VOID);

	tab();
	if (!isVoid) {
		printf("return ");
	}

	printf(this->getName());
	printf("(");

	Variable* params = this->m_parameters;
	bool first = true;
	while (params) {
		TypeObject* pType = params->m_type;
		if (!first) {
			printf(",");
		} else {
			first = false;
		}

		if (pType->m_genreID == EGENRE::_ABSTRACTCONTAINER && pType->m_definitionAC->m_modifier & ATT_STRUCT) {
			// Poor struct marshalling (1/2)
			// TODO : struct marshalling method
			printf("(s32%s)", (params->m_modifier & ATT_REF) == 0 ? "" : "*");
		}

		if((params->m_modifier & ATT_REF) != 0) {
			printf("&");
		}

		if(pType->m_typeID & ET_BASETYPE) {
			printf(params->getName());
		}

		else if(pType->m_typeID == TYPE_STRING) {

			// For compatibility reason with Mono / .NET auto marshalling issue with string
			// Not supported
			// InternalUtils::NativeUTF8FromString
			// printf("%s ? %s->_getUTF8() : NULL", params->getName(), params->getName());
			compilerError(ERR_USER, "Please use IntPtr converted String instead of directly use String.", m_line);
		}

		else if (pType->m_genreID == EGENRE::_ENUM) {
			printf(params->getName());
		}

		else if (pType->isArray() && (pType->m_rankCount == 1) && (pType->m_ranks[0].m_dimensionCount == 1)){
			// Array of something.
			if (pType->m_originalType) {
				printf("%s ? (%s*)%s->_getPArray() : NULL", params->getName(), pType->m_originalType->dumpTypeForCode(gCurrentAC, gCurrentMethod), params->getName());
			} else {
				compilerError(ERR_INTERNAL, "Internal compiler error", m_line);
			}
		}
		
		else if (pType->m_genreID == EGENRE::_ABSTRACTCONTAINER) {
			AbstractContainer* pAC = pType->m_definitionAC;
			if (pAC->m_modifier & ATT_STRUCT) {
				pAC->dumpMarshalledStruct(params);
				// Poor struct marshalling (2/2)
				printf(" + 1");
			}
			else {
				compilerError(ERR_USER, "Class objects need to be marshalled into IntPtr for extern functions", m_line);
			}
		} else {
			compilerError(ERR_INTERNAL, "Should never arrive here.", m_line);
		}

		params = params->m_pNextVariable;
	}

	printf(");\n");

	depth--;
	tab(); printf("}\n");
}

void Method::dumpCall(Expression* expr, bool delegateCall, TypeGenericEntry* genericParams) {
	if (!delegateCall) {
		if (m_modifier & ATT_EXTERN) {
			printf("_ext_");
			// Ref extension added to ref only in case that the wrapper does NOT exist.
			if (m_referenceModifCount)	{ printf("_ref_"); }
		}
		printf(this->getName());

		if ((g_unsafe == false) && ((this->m_modifier & ATT_STATIC)==0)) {
			printf("$");
		}
		if(g_unsafeEphemeral) { g_unsafe = false; g_unsafeEphemeral = false; }
	}

	if(genericParams) {
		printf("<");
		TypeGenericEntry* pGen = genericParams;
		do {
			printf("%s", pGen->m_genericName);
			pGen = pGen->m_pNext;
			if(pGen) {
				printf(", ");
			}
		} while(pGen);
		printf(">");
	}

	// [->] func[$]  (CLASS)
	// [.]  func	 (STRUCT)
	// [::] func	 (CLASS static)
	printf("(");
	Variable* pVar = this->m_parameters;
	if(expr) {
		if (expr->m_expressionType == EXPR_LIST) {
			for (int n=0; n < expr->m_expressionCount; n++) {
				if (n != 0) { printf(","); }
				if(expr->m_expressions[n]->m_runtimeType->m_typeID == TYPE_NULL) {
					// Wrap NULL as it is always ambiguous between two class types in C++, but not necessarily in C#
					printf("(%s)", pVar->m_type->dumpTypeForCode(gCurrentAC));
				}
				expr->m_expressions[n]->dumpExpressionInternal();
				pVar = pVar->m_pNextVariable;
			}
		} else {
			compilerError(ERR_INTERNAL,"Internal Error", expr->m_line);
		}
	}
	// Default parameters dump : for loop has LESS parameter than function interface.
	bool isFirstTime = true;
	while (pVar) {
		if (pVar->m_expression) {
			if ((!expr && !isFirstTime) || (expr && expr->m_expressionCount != 0)) {
				printf(",");
			}
			isFirstTime = false;
			pVar->m_expression->dumpExpressionInternal();
		} else {
			compilerError(ERR_INTERNAL,"Internal Error", expr->m_line);
		}
		pVar = pVar->m_pNextVariable;
	}
	printf(")");
}

const char*	Delegate::generateTypeID() {
	char buffer[1000];
	sprintf(buffer, "ET_CLASS | %i", this->m_uniqueId);
	return concat(buffer);
}

void Delegate::dumpDefinition(const char* prefix) {
	char buffer[1000];
	char buffer2[1000];
	char buffer3[1000];

	buffer[0] = 0;
	buffer2[0] = 0;
	buffer3[0] = 0;

	const char* name			= getName();
	const char* retType			= this->m_returnType->dumpTypeForCode(getOwner());
	const char* signature		= buffer;  this->dumpParamsDef(buffer, false, true);
	const char* call			= buffer2; this->dumpParamsDef(buffer2, true, false);
	const char* signatureSimple	= buffer3; this->dumpParamsDef(buffer3, false, false);

	bool  isVoid = this->m_returnType->m_typeID == TYPE_VOID;

	if(strcmp(prefix, "") != 0) {
		prefix = concat2(prefix, "::");
	}

	tab(); printf("class %s_Delegate_Base_%s : public System::Delegate\n", prefix, name);
	tab(); printf("{\n");
	
	printf("private:\n");
	tab(); printf("static const u32 _TYPEID = _TYPE_USEROBJECT | %s;\n", generateTypeID());

	tab(); printf("public:\n");

	tab(); printf("    virtual bool _isInstanceOf(u32 typeID) {\n");
	tab(); printf("\t    _INSTANCEOF(_Delegate_Base_%s,%s);\n",name, "System::Delegate");
	tab(); printf("    }\n\n");

	if (isVoid) {
		tab(); printf("    inline void call$(%s) { CHCKTHIS; (*this)(%s); }\n",signature,call);
	} else {
		tab(); printf("    inline %s call$(%s) { CHCKTHIS; return (*this)(%s); }\n",retType,signature,call);
	}
	tab(); printf("    virtual %s operator() (%s)=0;\n", retType, signature);
	tab(); printf("    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }\n");
	tab(); printf("    virtual void _releaseGC() { }\n");
	tab(); printf("};\n");
	tab(); printf("\n");

	tab(); printf("template <class TClass> class %s_DelegateI_%s : public %s_Delegate_Base_%s\n",prefix,name,prefix,name);
	tab(); printf("{\n");
	tab(); printf("private:\n");
	tab(); printf("    %s (TClass::*fpt)(%s);\n",retType, signatureSimple);
	tab(); printf("    TClass* pt2Object;\n");
	tab(); printf("public:\n");
	tab(); printf("\n");
	tab(); printf("    _DelegateI_%s(TClass* _pt2Object, %s(TClass::*_fpt)(%s)) {\n",name,retType,signatureSimple);
	tab(); printf("        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }\n");
	tab(); printf("        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);\n");
	tab(); printf("        fpt=_fpt;\n");
	tab(); printf("    }\n");
	tab(); printf("\n");
	tab(); printf("    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }\n");
	tab(); printf("    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }\n");
	tab(); printf("    virtual void _moveAlert(u32 offset) { \n");
	tab(); printf("        _Delegate_Base_%s::_moveAlert(offset);\n", name);
	tab(); printf("        u8* oldPtr; u8* newPtr;\n");
	tab(); printf("        if(pt2Object) {\n");
	tab(); printf("            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;\n");
	tab(); printf("            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);\n");
	tab(); printf("        }\n");
	tab(); printf("    }\n");
	tab(); printf("\n");
	if (!isVoid) {
		tab(); printf("    virtual %s operator()(%s) { return (*pt2Object.*fpt)(%s);}\n", retType,signature,call);
	} else {
		tab(); printf("    virtual void operator()(%s) { (*pt2Object.*fpt)(%s);}\n", signature, call);
	}
	tab(); printf("};\n");
	tab(); printf("\n");
	tab(); printf("class %s_DelegateS_%s : public %s_Delegate_Base_%s", prefix, name, prefix, name);
	tab(); printf("{\n");
	tab(); printf("private:\n");
	tab(); printf("    %s (*fpt)(%s);\n",retType,signatureSimple);
	tab(); printf("public:\n");
	tab(); printf("\n");
	tab(); printf("    _DelegateS_%s(%s(*_fpt)(%s))",name,retType,signatureSimple);
	tab(); printf("    { fpt=_fpt; };\n");
	tab(); printf("\n");
	if (!isVoid) {
		tab(); printf("    virtual %s operator()(%s) { return (*fpt)(%s); };\n",retType,signature,call);
	} else {
		tab(); printf("    virtual void operator()(%s) { (*fpt)(%s); };\n",signature,call);
	}
	tab(); printf("};\n");
	tab(); printf("\n");
}

void dumpCopyVarDelegate(Variable* pVars) {
	bool first = true;
	while (pVars) {
		if (!first) { printf(","); } else { first = false; }
		if (strcmp("_this__", pVars->m_name) == 0) {
			printf("this");
		} else {
			printf(pVars->m_name);
		}
		pVars = pVars->m_pNextVariable;
	}
}

void Expression::dumpExpressionInternal() {
	if(this->m_item.symbolType == _UNDEFGENRE) {
		printf("[Symbol not found]");
		return;
	}
	if(this->m_hasParenthesis) { printf("("); }
	switch (this->m_expressionType) {
	// Multiple
	case EXPR_LIST:
		for (int n=0; n < this->m_expressionCount; n++) {
			if (n != 0) { printf(","); }
			m_expressions[n]->dumpExpressionInternal();
		}

		// Nothing to solve when going up the expression stack.
		// NO return type to do here. Function will take care.
		break;

	case EXPR_DELEGATECREATE:
		{
			// DelegateFct p2 = delegate(int a) { return B.myStr.Length; };
			const char * anonName		= this->m_anonymousClass->getName();
			const char * delegateName	= this->m_delegateDef->getName();

			const char* anonPrefix		= gStaticContextAC
											? concat2(gStaticContextAC->getFullName(gRootNameSpace), "::")
											: "";
			const char* delegatePrefix	= this->m_delegateDef->getOwner() == gCurrentAC
											? "" 
											: concat2(this->m_delegateDef->getOwner()->getFullName(gCurrentAC), "::");
			
			const char* prefixedAnonName = concat2(anonPrefix, anonName);
			Variable* signature			= this->m_delegateSignature;

			/*char prefix[1000];
			int strl = strlen(this->m_precNameSpace);
			if (strl) {
				sprintf(prefix,"%s::%s",precNameSpace,this->getName());
			} else {
				sprintf(prefix,"%s",this->getName());
			}*/

			Method* pM				= m_anonymousClass->findMethod(anonName, (Variable*)NULL, NULL);	// There will always be only one constructor, this is why no signature is required.
			Variable* pListStart	= pM->m_parameters;

			if (gIsStaticFunc) {
				printf("CS_NEW %s_DelegateS_%s(CS_NEW %s(",
					delegatePrefix,
					delegateName,
					prefixedAnonName
				);

				dumpCopyVarDelegate(pListStart);

				printf("), &%s_anon_%::_delegate);",
					anonPrefix,
					anonName
				);
			} else {
				printf("CS_NEW %s_DelegateI_%s<%s>(CS_NEW %s(",
					delegatePrefix,
					/*DelegateType*/delegateName,
					/*Template*/prefixedAnonName,
					/*new*/prefixedAnonName
				);

				dumpCopyVarDelegate(pListStart);

				printf("), &%s::_delegate)" ,
					/*fct*/prefixedAnonName);
			}
		}
		break;
	// Leaf
	case EXPR_UNDER_THIS:
		printf("_this__");
		break;
	case EXPR_THIS:
		printf("this");
		break;
	case EXPR_BASE: 
		// TODO : check if base can be used on a type different from "this" ?
		// base.funct
		// Constructor Class A(b):base(b)
			
		/* In C++, base will be replaced by the prefix of the following dot expression,
			so nothing needs to be done at this point */
		break;
	case EXPR_IDENT:
	case EXPR_DOT: 
		{
			NameSpace* pContext = gCurrentAC;
			SRSymbol res;

			bool hasPrevious;
			if (m_expressionType == EXPR_IDENT) {
				res.pSymbol		= pContext;
				res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
				hasPrevious = false;
			} else {
				m_expressions[0]->dumpExpressionInternal();
				if(m_expressions[0]->m_runtimeType) {
					res = m_expressions[0]->m_runtimeType->m_res;
				}
				else {
					// Namespaces don't have a runtime type
					res = m_expressions[0]->m_item;
				}
				if(m_expressions[0]->m_expressionType == EXPR_BASE) {
					hasPrevious = false;
					g_unsafe			= true;
					g_unsafeEphemeral	= true;
				} else {
					hasPrevious = true;
				}
			}

			if (!m_bSkip) {
				dumpTokens(res, this->m_text, hasPrevious);
			}
		}
		break;
	case EXPR_INVOKE:
		{
			//
			// Descending and solving sub systems.
			//
			Method* pM = (Method*)m_item.pSymbol;
			NameSpace* pContext = gCurrentAC;
			if (pM->getGenre() == EGENRE::_DELEGATE) { 
				printf("");
				m_expressions[0]->dumpExpressionInternal();
				printf("->call$");
				pM->dumpCall(m_expressions[1],true, m_genericCall);
			} else {
				m_expressions[0]->dumpExpressionInternal();
				if(m_expressions[0]->m_expressionType != EXPR_IDENT
					&& !(m_expressions[0]->m_expressionType == EXPR_DOT
						&& m_expressions[0]->m_expressions[0]->m_expressionType == EXPR_BASE)) {
					pM->preFunc();
				}
				pM->dumpCall(m_expressions[1],false, m_genericCall);
			}
		}
		break;

	// Double
	case EXPR_ACCESS: 
		m_expressions[0]->dumpExpressionInternal();

		if (!m_isAssignmentSide) {
			printf("->_idx_g$");
		} else {
			printf("->_idx_s$");
		}

		printf("(");
		if (m_expressions[1]) {
			m_expressions[1]->dumpExpressionInternal();
		}
		if(!m_isAssignmentSide) {
			printf(")");
		} else {
			printf(",");
			// The rest is dumped by EXPR_ASS_EQ
		}

		break;

	case EXPR_CTE: 
		switch (this->m_value.type) {
		case TYPE_BOOL:
			if (this->m_value.v.i) {
				printf("true");
			} else {
				printf("false");
			}
			break;
		case TYPE_STRING:
			// Generated String* from constant.
			printf("_$_cteStr%iObj",this->m_value.pString->m_id);
			break;
		case TYPE_NULL: 
			printf("NULL");
			this->m_runtimeType = &t_NULL;
			break;
		case TYPE_DOUBLE:
			printf("%f",this->m_value.v.d);
			break;
		case TYPE_FLOAT:
			printf("%ff",this->m_value.v.f);
			break;
		case TYPE_INT:
			printf("%i",this->m_value.v.i);
			break;
		case TYPE_UINT:
			printf("%uu",this->m_value.v.i);
			break;
		case TYPE_LONG:
			printf("%il",this->m_value.v.l);
			break;
		case TYPE_ULONG:
			printf("%uul",this->m_value.v.i);
			break;
		case TYPE_CHAR:
			if (this->m_value.v.i>=32 && this->m_value.v.i<127) {
				printf("'%c'",this->m_value.v.i);
			} else { 
				printf("0x%4X",this->m_value.v.i);
			}
			break;
		default:
			compilerError(ERR_INTERNAL,"internal error dump expression CTE", m_line);
			break;
		}
		break;

	case EXPR_PLUSPLUS: 
	case EXPR_MINUSMINUS: 
	case EXPR_PREINCR:
	case EXPR_PREDECR: 
	case EXPR_ASS_EQ:
	case EXPR_ASS_PLUSEQ: 
	case EXPR_ASS_MINUSEQ:
	case EXPR_ASS_STAREQ: 
	case EXPR_ASS_DIVEQ: 
	case EXPR_ASS_MODEQ: 
	case EXPR_ASS_XOREQ: 
	case EXPR_ASS_ANDEQ: 
	case EXPR_ASS_OREQ: 
	case EXPR_ASS_RSHFTEQ: 
	case EXPR_ASS_LSHFTEQ: 
		dumpWrapper(this);
		break;

	case EXPR_NOT: 
		printf("!");
		m_expressions[0]->dumpExpressionInternal();
		break;		// !

	case EXPR_LNOT: 
		printf("~");
		m_expressions[0]->dumpExpressionInternal();
		break;		// ~

	case EXPR_UNARYPLUS: 
		printf("+");
		m_expressions[0]->dumpExpressionInternal();
		break;

	case EXPR_UNARYMINUS: 
		printf("-");
		m_expressions[0]->dumpExpressionInternal();
		break;
	case EXPR_IS:
		if (this->m_typeParam->isGC_Able()) {
			m_expressions[0]->dumpExpressionInternal();
			printf("->_isInstanceOf$(%i)",this->m_typeParam->m_typeID);
		} else {
			compilerError(ERR_NOT_SUPPORTED_YET, "IS operator works only with pointer for now.", m_line);
		}
		break;
	case EXPR_AS:
		// TODO Warning for As using non object or struct. (Check how much C# allow)
		printf("(%s)_as_(", this->m_runtimeType->dumpTypeForCode(gCurrentAC));
		if (this->m_runtimeType->isGC_Able()) {
			m_expressions[0]->dumpExpressionInternal();
			printf(",%i)",this->m_runtimeType->m_typeID);
		} else {
			compilerError(ERR_NOT_SUPPORTED_YET, "AS operator works only with pointer for now.", m_line);
		}
		break;

	case EXPR_NEW: 
		if (this->m_runtimeType->m_genreID == EGENRE::_DELEGATE) {
			printf("CS_NEW ");
			if (m_expressionCount != 2) {
				Delegate* pDelegate = this->m_runtimeType->m_definitionDelegate;
				const char* nameDelegate = pDelegate->getName();
				const char* prefix = pDelegate->getOwner() == gCurrentAC ? "" : concat2(pDelegate->getOwner()->getFullName(gCurrentAC), "::");
				if ((m_expressions[0]->m_expressionType == EXPR_LIST) && (m_expressions[0]->m_expressionCount == 1)) {
					Expression* methodExpr = m_expressions[0]->m_expressions[0];
					if (methodExpr->m_item.symbolType == EGENRE::_METHOD) {
						Method* method = (Method*)methodExpr->m_item.pSymbol;
						const char* methodName = method->getName();
						bool isStatic = (method->m_modifier & ATT_STATIC) != 0;
						const char* className  = concat2(method->m_pOwner->getName(), m_runtimeType->getGenParams());

						if (isStatic) {
							// new _DelegateS_xxxx(&Class::Method);
							printf("%s_DelegateS_%s(&%s::%s)",prefix, nameDelegate,className,methodName);
						} else {
							if (methodExpr->m_expressionType == EXPR_DOT || methodExpr->m_expressionType == EXPR_IDENT) { 
								// new _DelegateI_xxxx<class>(ptr, &Class::Method);
								printf("%s_DelegateI_%s<%s>(",prefix, nameDelegate,className);
								if (methodExpr->m_expressionType == EXPR_IDENT) {
									printf("this");
								} else {
									// Do not print the method name !
									methodExpr->m_bSkip = true;
									methodExpr->dumpExpressionInternal();
								}
								printf(",&%s::%s)",className,methodName);
							} else {
								compilerError(ERR_INTERNAL, "Compiler internal error.", m_line);
							}
						}
					} else {
						compilerError(ERR_INTERNAL, "Compiler internal error.", m_line);
					}
				} else {
					compilerError(ERR_INTERNAL, "Compiler internal error.", m_line);
				}
			} else {
				compilerError(ERR_INTERNAL, "Delegate was not wrapped properly", m_line);;
			}
		} else {
			if (m_expressionCount == 2) {
				//
				// TODO : Support init depending on local variable and other
				// see dumpGlobalInitializerImplementation comment.
				//
				bool hasCountSize   = m_expressions[0] != NULL;
				bool hasInitializer = m_expressions[1] != NULL;
				bool hasChainInit	= false;
				SInitialization*	initor = NULL;
				bool isArray		= true;

				if (hasInitializer) {

					// Is it array ?
					isArray = this->m_typeParam->isArray();
					initor = m_expressions[1]->m_initializerInfo;
					
					// Patch initialization mode, can NOT do memcpy for non array.
					if (!isArray) {
						initor->m_mode = SInitialization::INIT_CHAINADD;
					}

					if (initor->m_mode == SInitialization::INIT_WRAP_FUNC || initor->m_mode == SInitialization::INIT_MEMCPY) {
						printf("(%s)_global_array_initializer_%i(",this->m_typeParam->dumpTypeForCode(gCurrentAC),initor->m_expressionCounter);
					}
					else if(initor->m_mode == SInitialization::INIT_CHAIN || initor->m_mode == SInitialization::INIT_CHAINADD) {
						hasChainInit = true;
					}
				}

				if(hasChainInit) {
					printf("(");
				}

				if (isArray) {
					printf("CS_NEW System::Array< ");
					printf(this->m_typeParam->m_originalType->dumpTypeForCode(gCurrentAC));
					printf(" >");
				} else {
					printf("CS_NEW ");
					printf(this->m_typeParam->dumpTypeForCode(gCurrentAC));
				}

				if (hasInitializer) {
					printf("(%i)",m_expressions[1]->m_expressionCount);
				} else {
					if(isArray) {
						printf("(");
						m_expressions[0]->dumpExpressionInternal();
						printf(")");
					}
					else {
						// Find the associated constructor
						Method* pM = this->m_runtimeType->m_definitionAC->findMethod(this->m_runtimeType->m_name, m_expressions[0], NULL);
						pM->dumpCall(m_expressions[0],true, m_genericCall);
					}
					
				}

				if (hasInitializer) {
					if (initor->m_mode == SInitialization::INIT_WRAP_FUNC || initor->m_mode == SInitialization::INIT_MEMCPY) {
						printf(")");
					}
					if (hasChainInit) {
						printf(")");
						Expression* pExprList = initor->m_expression;
						for (int n=0; n < pExprList->m_expressionCount; n++) {
							if (initor->m_mode == SInitialization::INIT_CHAIN) {
								printf("->_s(%i,",n);
							} else { // always INIT_CHAINADD here
								printf("->AddRT(");
							}
							pExprList->m_expressions[n]->dumpExpressionInternal();
							printf(")");
						}
					}
				}
			} 
			else {
				/* NEW type ( argument_list_opt ) */
				printf("CS_NEW ");
				printf(this->m_runtimeType->getFullName(gCurrentAC));
				printf(this->m_runtimeType->getGenParams());
				if (m_expressions[0] && this->m_typeParam->isArray()) {
					printf("(");
					m_expressions[0]->dumpExpressionInternal();
					printf(")");
				}
				else {
					// Dump parameters which fit the constructor (default parameters included)
					Method* pM = this->m_runtimeType->m_definitionAC->findMethod(this->m_runtimeType->m_name, m_expressions[0], NULL);
					if(pM) {
						pM->dumpCall(m_expressions[0],true, m_genericCall);
					}
					else {
						printf("()");
					}
				}
			}
		}
		break;		// + Type
	
	// Double
	case EXPR_CAST: 
		if (this->m_expressionCount == 1) {
			if (this->m_text) {
				//	$$.expr = CreateSingleExpr(EXPR_CAST, $6.expr)->setQuals($4.quals)->setIdentifier($2.text)->setRank($3.tmpValue);
				// TODO Cast
			} else {
				// $$.expr = CreateSingleExpr(EXPR_CAST, $5.expr)->setQuals($3.quals)->setType($2.type);
				// $$.expr = CreateSingleExpr(EXPR_CAST, $5.expr)->setQuals($3.quals)->setType($2.type);
				// $$.expr = CreateSingleExpr(EXPR_CAST, $5.expr)->setType(TypeObject::getTypeObject(TYPE_VOID)); */
				printf("(");
				printf(this->m_runtimeType->dumpTypeForCode(gCurrentAC));
				// TODO Quals for cast.
				printf(")");
				m_expressions[0]->dumpExpressionInternal();
			}
		} else {
			// $$.expr = CreateDoubleExpr(EXPR_CAST, $2.expr, $4.expr);
			printf("(");
			if(m_expressions[0]->m_runtimeType->m_typeID == TYPE_INTPTR) {
				printf("s32*");
			}
			else {
				m_expressions[0]->dumpExpressionInternal();
				if(this->m_runtimeType->isGC_Able()) {
					printf("*");
				}
			}
			printf(")");
			m_expressions[1]->dumpExpressionInternal();
		}
		break;

	case EXPR_PLUS: 
		if (wrapStringStart) {
			printf("(CS_NEW System::String())->_appendStr(");
			m_expressions[0]->dumpExpressionInternal();
			printf(")");
		} else {
			m_expressions[0]->dumpExpressionInternal();
		}

		//
		// Wrap expressions base on left / right type
		//
		if (m_expressions[0]->m_runtimeType->m_typeID == TYPE_STRING) {
			const char* suffix = "";
			bool skipNull = false;
			switch (m_expressions[1]->m_runtimeType->m_typeID) {
			case TYPE_SBYTE:	printf("->_appendS8("); break;
			case TYPE_BYTE:		printf("->_appendU8("); break;
			case TYPE_SHORT:	printf("->_appendS("); break;
			case TYPE_USHORT:	printf("->_appendUS("); break;
			case TYPE_INT:		printf("->_appendI("); break;
			case TYPE_UINT:		printf("->_appendU("); break;
			case TYPE_LONG:		printf("->_appendL("); break;
			case TYPE_ULONG:	printf("->_appendUL("); break;
			case TYPE_CHAR:		printf("->_appendC("); break;
			case TYPE_FLOAT:	printf("->_appendF("); break;
			case TYPE_DOUBLE:	printf("->_appendD("); break;
			case TYPE_BOOL:		printf("->_appendB("); break;
			case TYPE_OBJECT:	printf("->_appendStr("); suffix = "->ToString()"; break;
			case TYPE_STRING:	printf("->_appendStr("); break;
			case TYPE_INTPTR:	printf("->_appendUL((u64)"); break;
			case TYPE_NULL:		skipNull = true; break;
			default:
				printf("->_appendStr("); suffix = "->ToString()"; break;
			}

			if (!skipNull) {
				m_expressions[1]->dumpExpressionInternal();
				printf(suffix);
				printf(")");
			}
		} else {
			printf(" + ");
			m_expressions[1]->dumpExpressionInternal();
		}

		if (wrapStringEnd) {
			printf("->_appendClose()");
		}
		break;

	case EXPR_DIV: 
	case EXPR_MOD: 
		{
			bool wrapOp = ((ET_BASETYPE | ET_NUMBER) & m_expressions[0]->m_runtimeType->m_typeID & m_expressions[1]->m_runtimeType->m_typeID) == ET_BASETYPE;
			bool wrapFloatMod = (((m_expressions[0]->m_runtimeType->m_typeID & (ET_BASETYPE | ET_NUMBER))==(ET_BASETYPE | ET_NUMBER)) && this->m_expressionType == EXPR_MOD);

			// Both basic non floating point type or float modulo.
			if (wrapOp || wrapFloatMod) {
				if (this->m_expressionType == EXPR_DIV) {
					printf("UtilDiv::_divByWrp(");
				} else {
					printf("UtilDiv::_modByWrp(");
				}
				m_expressions[0]->dumpExpressionInternal();
				printf(",");
				m_expressions[1]->dumpExpressionInternal();
				printf(")");
			} else {
				m_expressions[0]->dumpExpressionInternal();
				printf(getOpDump());
				m_expressions[1]->dumpExpressionInternal();
			}
		}
		break;
	case EXPR_EQUTST:
		if(m_expressions[0]->m_runtimeType->isGC_Able() && (m_expressions[1]->m_runtimeType->m_typeID != TYPE_NULL)) {
			m_expressions[0]->dumpExpressionInternal();
			printf("->Equals(");
			m_expressions[1]->dumpExpressionInternal();
			printf(")");
			break;
		}
		else {
			// Do not break
		}
	case EXPR_MINUS: 
	case EXPR_MULT: 
	case EXPR_LSHFT: 
	case EXPR_RSHFT: 
	case EXPR_LESS: 
	case EXPR_MORE: 
	case EXPR_LESSEQ: 
	case EXPR_MOREEQ:  
	case EXPR_DIFFTST: 
	case EXPR_LAND: 
	case EXPR_LXOR: 
	case EXPR_LOR: 
	case EXPR_AND: 
	case EXPR_OR: 
		m_expressions[0]->dumpExpressionInternal();
		printf(getOpDump());
		m_expressions[1]->dumpExpressionInternal();
		break;
	case EXPR_REF:
		{
			bool wrap = false;

			// Pass a member as parameter.
			if (m_item.symbolType == EGENRE::_MEMBER) {
				if (m_runtimeType->isGC_Able()) {
					// 
					printf("(%s&)System::__GCObject::__registerByRef((System::__GCObject*&)",m_runtimeType->dumpTypeForCode(m_runtimeType->m_definitionAC));
					wrap = true;
				} else {
					if ((m_runtimeType->m_definitionAC != NULL) && (m_runtimeType->m_definitionAC->m_modifier & ATT_STRUCT)) {
						printf("%s::__registerByRef(",m_runtimeType->getFullName(gCurrentAC));
						wrap = true;
					}
				}
			}

			m_expressions[0]->dumpExpressionInternal();

			if (wrap) {
				printf(")");
			}
		}
		break;
	
	// Triple
	case EXPR_COND: 
		printf("(");
		m_expressions[0]->dumpExpressionInternal();
		printf(" ? ");
		m_expressions[1]->dumpExpressionInternal();
		printf(" : ");
		m_expressions[2]->dumpExpressionInternal();
		printf(")");
		break;
	case EXPR_UNARYMULT:
	case EXPR_CAST_PTR:
	case EXPR_UNCHECKED: 
	case EXPR_ADRESSOF:
	case EXPR_ARROW: 
	case EXPR_SIZEOF:
	case EXPR_TYPEOF:
	case EXPR_CHECKED: 
		// Not Supported, error handled at parser level.
		break;
	default:
		compilerError(ERR_INTERNAL, "Internal Error, unknown Expression Type", m_line);
	}
	if(this->m_hasParenthesis) { printf(")"); }
}

const char* Expression::getOpDump() {
	switch (this->m_expressionType) {
	case EXPR_DIV: 			return " / ";
	case EXPR_MOD: 			return " %% ";
	case EXPR_MINUS: 		return " - ";
	case EXPR_MULT: 		return " * ";
	case EXPR_LSHFT: 		return " << ";
	case EXPR_RSHFT: 		return " >> ";
	case EXPR_LESS: 		return " < ";
	case EXPR_MORE: 		return " > ";
	case EXPR_LESSEQ: 		return " <= ";
	case EXPR_MOREEQ:		return " >= ";
	case EXPR_EQUTST:		return " == ";
	case EXPR_DIFFTST:		return " != ";
	case EXPR_LAND:			return " & ";
	case EXPR_LXOR:			return " ^ ";
	case EXPR_LOR:			return " | ";
	case EXPR_AND:			return " && ";
	case EXPR_OR:			return " || ";
	default:
		compilerError(ERR_INTERNAL, "Internal error, should never reach that code", m_line);
		return NULL;
	}
}

const char* Expression::getAssEqOpDump() {
	switch (this->m_expressionType) {
	case EXPR_ASS_PLUSEQ:	return " += ";
	case EXPR_ASS_MINUSEQ:	return " -= ";
	case EXPR_ASS_STAREQ:	return " *= ";
	case EXPR_ASS_DIVEQ:	return " /= ";
	case EXPR_ASS_MODEQ:	return " %%= ";
	case EXPR_ASS_XOREQ:	return " ^= ";
	case EXPR_ASS_ANDEQ:	return " &= ";
	case EXPR_ASS_OREQ:		return " |= ";
	case EXPR_ASS_LSHFTEQ:  return " <<= ";
	case EXPR_ASS_RSHFTEQ:	return " >>= ";
	default:
		compilerError(ERR_INTERNAL, "Internal error, should never reach that code", m_line);
		return NULL;
	}
}

void Variable::dumpVariable	()
{
}

void Variable::dumpMember(NameSpace* nameSpaceContext) {
	//
	// === Line 1 ===
	//
	bool isConst	= false;
	bool isStatic	= false;
	tab();
	if (this->m_modifier & ATT_STATIC) {
		printf("static ");
		isStatic = true;
	}

	if (this->m_modifier & ATT_CONST) {
		isConst = true;
		printf("const ");
	}

	// TypeA varA;

	// LATER other modifier support ?
	// ATT_PUBLIC		= 0x00000002,
	// ATT_PRIVATE		= 0x00000004,
	// ATT_PROTECTED	= 0x00000008,
	// ATT_INTERNAL	= 0x00000010,
	// ATT_VOLATILE	= 0x00001000,
	// ATT_SEALED		= 0x00000080,	// Same as FINAL

	// Dump Type
	printf(this->m_type->dumpTypeForCode(nameSpaceContext)); printf(" ");

	// Dump Variable Name
	printf(this->getName());

	// Dump Assignment if any.
	// TODO if CONST and non object value -> put ATT_STATIC to the member.
	// --> All sub logic and search is going to optimize

	if (this->m_expression && isConst) {
		printf(" = ");
		Expression::analysisTransformAndDump(&this->m_expression, this->m_type);
	}

	printf(";\n");

	//
	// Line 2 : Dump equivalent inline safe getter
	//
	EnumTypeObject EType = this->m_type->m_typeID;
	const char* pStrType = this->m_type->dumpTypeForCode(nameSpaceContext);
	const char* name	 = this->m_name;
	bool		isNonNum = ((EType & (ET_BASETYPE | ET_NUMBER))==ET_BASETYPE);
	const char* testDiv	 = isNonNum ? "if (value == 0) { THROWDIVZERO; }; " : "";
	bool		isBool	 = (EType == ET_BOOL);
	bool		isPtr	 = this->m_type->isGC_Able();
	bool		isEnum	 = (this->m_type->m_genreID == EGENRE::_ENUM) && (isPtr == false);
	bool		isNativePtr	= (EType == TYPE_INTPTR);
	bool		isInteger = (EType == ET_INT8 || EType == ET_INT16 || EType == ET_INT32 || EType == ET_INT64 ||
							EType == ET_UINT8 || EType == ET_UINT16 || EType == ET_UINT32 || EType == ET_UINT64 ||
							EType == ET_CHAR) && (isPtr==false);

	bool		isStruct;
	
	if (this->m_type->m_definitionAC) {
		isStruct = (this->m_type->m_definitionAC->m_modifier & ATT_STRUCT) != 0;
	} else {
		isStruct = false;
	}

	// For GC-able members, inline function are dumped later to avoid dependancy issues.

	if (isStatic) {
		if(isEnum)
		{
			// Special case 1 : these operators need to be wrapped as they aren't staple overloaded operators for enums.
			tab(); printf("inline static %s _s%spostInc()				{ return (%s)(((s32&)%s)++); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline static %s _s%spostDec()				{ return (%s)(((s32&)%s)--); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline static %s _s%spreInc()				{ return (%s)(++(s32&)%s); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline static %s _s%spreDec()				{ return (%s)(--(s32&)%s); }\n", pStrType, name, pStrType, name);

			tab(); printf("inline static %s _s%sAddEq(s32 value)		{ return (%s)((s32&)%s += value); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline static %s _s%sSubEq(s32 value)		{ return (%s)((s32&)%s -= value); }\n", pStrType, name, pStrType, name);
		}
		else if((isNonNum == false) && (isPtr == false) && (isStruct == false))
		{
			// Special case  2 : %= exists in C# for doubles and floats, but not in C++.
			tab(); printf("inline static %s _s%sModEq(%s value)		{ s32 tmp = ((s32)(%s / value)); return %s = %s-(tmp*value); }\n", pStrType, name, pStrType, name, name, name);
		}
		else if(isInteger)
		{
			// Special case 3 : integer division needs to be wrapped to handle division by zero.
			tab(); printf("inline static %s _s%sDivEq(%s value)		{ %s; return %s /= value; }\n", pStrType, name, pStrType, testDiv, name);
			tab(); printf("inline static %s _s%sModEq(%s value)		{ %s; return %s %%= value; }\n", pStrType, name, pStrType, testDiv, name);
		}
		else if(isStruct) 
		{
			tab(); printf("inline static %s _s%s(%s _$value);\n",pStrType,name,pStrType);
		}
		else if(isPtr)
		{
			tab(); printf("inline static %s _s%s(%s _$value);\n",pStrType,name,pStrType);
		}
	}

	else if ((!isConst) && (!isStatic)) {

		//
		// Perform ref count analysis here at the same time : member is NOT static, member is NOT const
		// Work recursively as the struct are dumped in dependancy order.
		//
		if (isStruct) {
			u32 value = 0;
			if (isPtr)			{ value = 1; }
			else if (isStruct)	{ value = this->m_type->m_definitionAC->m_referenceModifCount; }
			this->m_ownerClass->m_referenceModifCount += value;
		}

		tab();
		printf("inline ");
		printf("%s& _g%s$() { CHCKTHIS; return %s; }\n",pStrType, name, name);
		
		//
		// Line 3 : Dump equivalent inline safe setter (Note : setter MUST return value because can do assignment in expression)
		//
		if (isPtr) {
			tab(); printf("inline %s _s%s(%s _$value);\n", pStrType, name, pStrType);
			tab(); printf("inline %s _s%s$(%s _$value);\n", pStrType, name, pStrType);
		} else {
			if (isStruct) {
				tab(); printf("inline %s _s%s(%s _$value);\n", pStrType,name,pStrType);
				tab(); printf("inline %s _s%s$(%s _$value);\n", pStrType, name, pStrType);
			} else {
				tab(); printf("inline ");
				printf("%s _s%s$(%s _$value) { CHCKTHIS; return %s = _$value; }\n", pStrType, name, pStrType, name);
			}
		}

		// Early return
		if (isBool || isPtr || isStruct) {
			return;
		}

		if(isEnum) {
			tab(); printf("inline %s _s%s$postInc()				{ CHCKTHIS; return (%s)(((s32&)%s)++); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%s$postDec()				{ CHCKTHIS; return (%s)(((s32&)%s)--); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%s$preInc()				{ CHCKTHIS; return (%s)(++(s32&)%s); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%s$preDec()				{ CHCKTHIS; return (%s)(--(s32&)%s); }\n", pStrType, name, pStrType, name);

			tab(); printf("inline %s _s%s$AddEq(s32 value)		{ CHCKTHIS; return (%s)((s32&)%s += value); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%s$SubEq(s32 value)		{ CHCKTHIS; return (%s)((s32&)%s -= value); }\n", pStrType, name, pStrType, name);

			tab(); printf("inline %s _s%spostInc()				{ return (%s)(((s32&)%s)++); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%spostDec()				{ return (%s)(((s32&)%s)--); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%spreInc()				{ return (%s)(++(s32&)%s); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%spreDec()				{ return (%s)(--(s32&)%s); }\n", pStrType, name, pStrType, name);

			tab(); printf("inline %s _s%sAddEq(s32 value)		{ return (%s)((s32&)%s += value); }\n", pStrType, name, pStrType, name);
			tab(); printf("inline %s _s%sSubEq(s32 value)		{ return (%s)((s32&)%s -= value); }\n", pStrType, name, pStrType, name);
		} else {
			if (!isNativePtr) {
				tab(); printf("inline %s _s%s$postInc()				{ CHCKTHIS; return %s++; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%s$postDec()				{ CHCKTHIS; return %s--; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%s$preInc()				{ CHCKTHIS; return ++%s; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%s$preDec()				{ CHCKTHIS; return --%s; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%s$AddEq(%s value)		{ CHCKTHIS; return %s += value; }\n", pStrType, name, pStrType, name);
				tab(); printf("inline %s _s%s$SubEq(%s value)		{ CHCKTHIS; return %s -= value; }\n", pStrType, name, pStrType, name);
			} else {
				tab(); printf("inline %s _s%s$AddEq(s32 value)		{ CHCKTHIS; return %s += value; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%s$SubEq(s32 value)		{ CHCKTHIS; return %s -= value; }\n", pStrType, name, name);
			}


			if (!isNativePtr) {
				tab(); printf("inline %s _s%s$MulEq(%s value)		{ CHCKTHIS; return %s *= value; }\n", pStrType, name, pStrType, name);
				tab(); printf("inline %s _s%s$DivEq(%s value)		{ CHCKTHIS; %s; return %s /= value; }\n", pStrType, name, pStrType, testDiv, name);
				if (isNonNum) {
					tab(); printf("inline %s _s%s$ModEq(%s value)		{ CHCKTHIS; %s; return %s %%= value; }\n", pStrType, name, pStrType, testDiv, name);
				} else {
					tab(); printf("inline %s _s%s$ModEq(%s value)		{ CHCKTHIS; s32 tmp = ((s32)(%s / value)); return %s = %s-(tmp*value); }\n", 
						pStrType, name, pStrType, name, name, name);
				}

				if (isNonNum) {
					tab(); printf("inline %s _s%s$XorEq(%s value)		{ CHCKTHIS; return %s ^= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%s$AndEq(%s value)		{ CHCKTHIS; return %s &= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%s$OrEq(%s value)		{ CHCKTHIS; return %s |= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%s$RShiftEq(%s value)	{ CHCKTHIS; return %s >>= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%s$LShiftEq(%s value)	{ CHCKTHIS; return %s <<= value; }\n", pStrType, name, pStrType, name);
				}

				tab(); printf("inline %s _s%spostInc()				{ return %s++; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%spostDec()				{ return %s--; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%spreInc()				{ return ++%s; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%spreDec()				{ return --%s; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%sAddEq(%s value)		{ return %s += value; }\n", pStrType, name, pStrType, name);
				tab(); printf("inline %s _s%sSubEq(%s value)		{ return %s -= value; }\n", pStrType, name, pStrType, name);
			} else {
				tab(); printf("inline %s _s%sAddEq(s32 value)		{ return %s += value; }\n", pStrType, name, name);
				tab(); printf("inline %s _s%sSubEq(s32 value)		{ return %s -= value; }\n", pStrType, name, name);
			}

			if (!isNativePtr) {
				tab(); printf("inline %s _s%sMulEq(%s value)		{ return %s *= value; }\n", pStrType, name, pStrType, name);
				tab(); printf("inline %s _s%sDivEq(%s value)		{ %s; return %s /= value; }\n", pStrType, name, pStrType, testDiv, name);
				if (isNonNum) {
					tab(); printf("inline %s _s%sModEq(%s value)		{ %s; return %s %%= value; }\n", pStrType, name, pStrType, testDiv, name);
				} else {
					tab(); printf("inline %s _s%sModEq(%s value)		{ s32 tmp = ((s32)(%s / value)); return %s = %s-(tmp*value); }\n", 
						pStrType, name, pStrType, name, name, name);
				}

				if (isNonNum) {
					tab(); printf("inline %s _s%sXorEq(%s value)		{ return %s ^= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%sAndEq(%s value)		{ return %s &= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%sOrEq(%s value)			{ return %s |= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%sRShiftEq(%s value)		{ return %s >>= value; }\n", pStrType, name, pStrType, name);
					tab(); printf("inline %s _s%sLShiftEq(%s value)		{ return %s <<= value; }\n", pStrType, name, pStrType, name);
				}
			}
		}
	}
}

void Method::dumpParamsDef(char* buffer, bool doCall, bool dumpDefault) {
	Variable* pVar = this->m_parameters;
	bool first = true;
	while (pVar) {
		if (first) {
			first = false;
		} else {
			buffer += sprintf(buffer,",");
		}

		if (!doCall) {
			buffer += sprintf(buffer, pVar->m_type->dumpTypeForCode(m_pOwner, this));
			if (pVar->m_modifier & ATT_REF) { buffer += sprintf(buffer, "&"); }
			buffer += sprintf(buffer, " ");
		}
		buffer += sprintf(buffer, pVar->getName());
		if (!doCall) {
			if (pVar->m_expression && dumpDefault) {
				buffer += sprintf(buffer, " = ");
				pVar->m_expression->dumpExpression();
			}
		}
		pVar = pVar->m_pNextVariable;
	}
}

void Method::dumpParamsDef() {
	Variable* pVar = this->m_parameters;
	bool first = true;
	while (pVar) {
		if (first) {
			first = false;
		} else {
			printf(",");
		}
		printf(pVar->m_type->dumpTypeForCode(m_pOwner, this));
		if (pVar->m_modifier & ATT_REF) { printf("&"); }
		printf(" ");
		printf(pVar->getName());
		/* DO NOT DUMP DEFAULT in C++, make the compiler perform full call instead.
		if (pVar->m_expression) {
			printf(" = ");
			pVar->m_expression->dumpExpression();
		}*/
		pVar = pVar->m_pNextVariable;
	}
}

void AbstractContainer::analyzeComplete() {
	if(isSubSystem()) {
		// No need to analyse
		return;
	}

	// Analyze Getter / Setter
	for (int n=0; n < this->m_accessorCount; n++) {
		Accessor* pA = this->m_accessors[n];

		// Create global dico + Add function parameters to dictionnary.
		if(!gCurrentSD) {	//gCurrentSD is supposed to be always NULL at this point
			gCurrentSD = new SymbolDictionary();
		}

		gIsStaticFunc = (pA->m_modifier & ATT_STATIC) != 0;
		pA->m_type->getResolvedType(this);
		gReturnType   = pA->m_type;
		
		// Register parameters in the dictionary
		Variable* pParam = pA->m_variable;
		while(pParam) {
			gCurrentSD->addVariable(pParam);
			pParam = pParam->m_pNextVariable;
		}

		if (pA->m_get) {
			if (pA->m_get->m_statement) {
				gCurrentSD = gCurrentSD->addDictionary();
				pA->m_get->m_statement->analysis();
				gCurrentSD = gCurrentSD->removeDictionary();
			}
		}
		if (pA->m_set) {
			if (pA->m_set->m_statement) {
				gCurrentSD = gCurrentSD->addDictionary();
				Variable* pParameter = CreateVarInstance("value");
				pParameter->setType(pA->m_type);
				gCurrentSD->addVariable(pParameter);
				pA->m_set->m_statement->analysis();
				gCurrentSD = gCurrentSD->removeDictionary();
			}
		}

		// Destroy dico + Remove variable/parameters from dictionnary.
		gCurrentSD = gCurrentSD->removeDictionary();	
	}

	// Analyze all member that may be delegate related.
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];

		if (pVar->m_expression) {
			SRSymbol res = pVar->m_type->getResolvedType(this);
			if (res.symbolType == EGENRE::_DELEGATE) {
				gIsStaticFunc = (pVar->m_modifier & ATT_STATIC) != 0;
				if (pVar->m_expression->m_expressionType == EXPR_DELEGATECREATE) {
					pVar->m_expression->m_delegateDef = (Delegate*)res.pSymbol;
					pVar->m_expression->AnalysisAndTransform();
				}
			}
		}
	}

	// Analyze functions
	for (int n=0; n < this->m_methodCount; n++) {
		Method* pM = this->m_methods[n];
		gCurrentMethod = pM;

		gIsStaticFunc = (pM->m_modifier & ATT_STATIC) != 0;
		if (pM->m_returnType) {	// NULL in case of CTOR & DTOR
			pM->m_returnType->getResolvedType(this, gCurrentMethod);
			gReturnType   = pM->m_returnType;
		}

		// Create global dico + Add function parameters to dictionnary.
		if(!gCurrentSD) {	//gCurrentSD is supposed to be always NULL at this point
			gCurrentSD = new SymbolDictionary();
		}

		Variable* pParameter = pM->m_parameters;
		while(pParameter) {
			// Register variables as local symbols for code.
			gCurrentSD->addVariable(pParameter);
			pParameter->m_type->m_res = pParameter->m_type->getResolvedType(this, pM);
			pParameter = pParameter->m_pNextVariable;
		}

		if(pM->m_initializerOpt) {
			// Analyse base constructor parameters
			pM->m_initializerOpt->AnalysisAndTransform();
		}

		pM->m_codeBlock->analysis();

		// Destroy dico + Remove variable/parameters from dictionnary.
		gCurrentSD = gCurrentSD->removeDictionary();

	}
	gCurrentMethod = NULL;
}

const char* AbstractContainer::getTemplateParams() {
	char buff[500];
	buff[0] = 0;
	char* ptr = buff;
	int delta;

	if(m_genericParam) {
		TypeGenericDefinitionEntry* genericSymbol = m_genericParam;
		sprintf(ptr++, "<");
		while(genericSymbol) {
			delta = sprintf(ptr, "%s", genericSymbol->m_genericName);
			ptr += delta;
			if(genericSymbol = genericSymbol->m_pNextGenericEntry) {
				sprintf(ptr, ", ");
				ptr += 2;
			}
		}
		sprintf(ptr, ">");
	}
	else {
		// The class is not a template.
	}
	return concat(buff);
}

void AbstractContainer::dumpTemplateLabel() {
	if(m_genericParam) {
		TypeGenericDefinitionEntry* genericSymbol = m_genericParam;
		printf("template <");
		while(genericSymbol) {
			printf("typename %s", genericSymbol->m_genericName);
			if(genericSymbol = genericSymbol->m_pNextGenericEntry) {
				printf(", ");
			}
		}
		printf("> ");
	}
	else {
		// The class is not a template.
	}
}

void AbstractContainer::dumpFriends() {
	for(int n = 0 ; n < m_innerCount ; n++) {
		AbstractContainer* pInner = m_pInner[n];
		if(pInner->m_cppRepresentation) {
			printf("friend %s %s;\n", ((pInner->m_modifier & ATT_STRUCT) == 0) ? "class" : "struct", pInner->m_cppRepresentation->m_name);
			pInner->dumpFriends();
		}
	}
	for(int n = 0 ; n < m_delegateCount ; n++) {
		if(m_delegates[n]->m_cppRepresentation)
		{
			printf("friend class %s;\n", m_delegates[n]->m_cppRepresentation->m_name);
		}
	}
}

// Dumps inner classes which are still nested (anonymous delegates).
void AbstractContainer::dumpNested() {
	for(int n = 0 ; n < m_innerCount ; n++) {
		if(!m_pInner[n]->m_cppRepresentation) {
			printf("class %s;\n", m_pInner[n]->m_name);
		}
	}
}

void AbstractContainer::dumpPrototype(bool isInnerClass) {
	// If no dump set, do nothing.
	if (m_noDump) { return ; }

	gCurrentAC = this;
	analyzeComplete();

	if((m_pParent == gRootNameSpace) && strcmp(m_name, "Program") == 0) {
		// Dumped in framework.h
		return;
	}

	char buff[1000];
	buff[0] = 0;
	char* pb = buff;
	int n = 0;
	AbstractContainer* list[50];
	list[n++] = this;
	AbstractContainer* p = this;
	while (p->m_name[0]) {
		list[n++] = p;
		p = (AbstractContainer*)p->m_pParent;		
	}
	for(n-- ; n > 1 ; n--) {
		pb += sprintf(pb, "%s::", list[n]->m_name);
	}
	pb += sprintf(pb, this->getName());
	const char* fullName = buff;

	if (this->m_csharpRepresentation) {
		// class NomMessedup { implement CSharp }
		this->m_csharpRepresentation->realDumpPrototype(isInnerClass, fullName);
	} else if (this->m_cppRepresentation) {
		// Skip.
		return;
	} else {
		// Normal, no change.
		realDumpPrototype(isInnerClass, fullName);
	}
}

void AbstractContainer::realDumpPrototype(bool isInnerClass, const char* fullName) {
	int		   nameSpaceCount = 0;	
	/*
	if (!isInnerClass) {
		// === List of name space to the root.
		NameSpace* nameSpace[50];
		NameSpace* current = this->m_pParent;
		while (current) {
			if (current->getGenre() == EGENRE::_NAMESPACE) {
				nameSpace[nameSpaceCount++] = current;
			}
			current = current->m_pParent;
		}

		// Dump root to class name space stack
		int n;
		n = nameSpaceCount-2; while (n >= 0) {
			printf("namespace %s { ", nameSpace[n]->m_name); 
			n--;
		}
		printf("\n");
		depth++;
	}*/


	bool isInterface = ((this->m_modifier & ATT_INTERFACE) != 0);
	bool isStruct	 = ((this->m_modifier & ATT_STRUCT) != 0);

	//
	// Header
	//
	tab(); 

	dumpTemplateLabel();

	int count = 0;
	if (this->m_modifier & ATT_CLASS) {
		count = 1;
		printf("class %s ", fullName);
		if (this->getAncestor())	{ 
			printf(": public %s ",this->getAncestor()->m_definitionAC->getFullName(this)); 
		} else {
			printf(": public System::Object ");
		}							// Force because we need GC and inheritance.
	} else {
		if (isInterface) {
			printf("class %s ", fullName); // Interface do NOT inherit from GC.
		} else {
			// Struct do not inherit from GCOBject either.
			// No real difference with C++ but use it as a convenience for debugging C++ output.
			printf("struct %s : public System::__GCStruct ", fullName);
		}
	}

	if (this->m_inheritancesCount) {
		for (int n=0; n < this->m_inheritancesCount; n++) {
			if (this->getAncestor() != m_inheritances[n]) {
				printf("%s", (count++ || isStruct) ? "," : ": ");
				printf("public %s ", this->m_inheritances[n]->getFullName(this)); // TODO : resolve
			}
		}
	}
	printf("{\n");

	dumpFriends();

	tab(); printf("\npublic:\n");

	dumpNested();

	// Inner guts
	depth++;

	dumpEnums(this);
	// Inner classes and delegates are unnested.
	// dumpDelegatePrototypes(this);
	// dumpClassPrototypes(this, false);

	if (!isInterface) {
		// Constructor / Destructor interface
		tab(); printf("void _ctor_%s();\n",this->getName());
	}

	bool hadDtor = false;
	bool hadEmptyCtor = false;

	// Dump Const & Static
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];

		pVar->dumpMember(this);

		if (pVar->m_modifier & ATT_STATIC) {
			gStaticDepMatrix->registerVariable(pVar);
		}
		printf("\n");
	}

	// Dump Getter / Setter
	for (int n=0; n < this->m_accessorCount; n++) {
		Accessor* pA = this->m_accessors[n];

		// Create global dico + Add function parameters to dictionnary.
		if(!gCurrentSD) {	//gCurrentSD is supposed to be always NULL at this point
			gCurrentSD = new SymbolDictionary();
		}

		bool isVirt		 = false;
		if ((this->m_modifier & ATT_INTERFACE)) {
			// Do nothing.
		} else {
			if (pA->m_modifier & ATT_STATIC) {
				isVirt = false;
			} else {
				isVirt = ((pA->m_modifier & ATT_VIRTUAL) != 0);
				// TODO : detect interface implementation -> generate virtual ? C++ consider even without rewriting virtual... should work as is.
			}
		}
		
		gIsStaticFunc = (pA->m_modifier & ATT_STATIC) != 0;

		const char* pStrType	= pA->m_type->dumpTypeForCode(this);
		const char* pName		= pA->m_name ? pA->m_name : "";
		const char* testDiv		= ((pA->m_type->m_typeID & (ET_BASETYPE | ET_NUMBER))==ET_BASETYPE) ? "if (value == 0) { THROWDIVZERO; }; " : "";
		const char* accType		= pA->m_variable == NULL ? "acc" : "idx";

		// getter/setter implementation is dumped later to avoid dependancy issues.

		if (pA->m_get) {
			if (!isInterface && ((pA->m_get->m_modifier & ATT_ABSTRACT)==0) && (pA->m_get->m_statement)) {
				tab();
				// Unsafe Getter
				if (pA->m_modifier & ATT_STATIC) { printf("static "); }
				printf("%s %s _%s_g%s(",isVirt ? "virtual" : "inline",pStrType, accType, pName); pA->dumpParams(false); printf(");\n");
				if ((pA->m_modifier & ATT_STATIC)==0) {
					tab(); printf("inline %s _%s_g%s$(",pStrType, accType, pName); pA->dumpParams(false); printf(");\n\n");
				}
			} else {
				tab();
				if (pA->m_modifier & ATT_STATIC) {
					printf("static %s _%s_g%s(",pStrType, accType, pName); pA->dumpParams(false); printf(") { THROWUNIMPLEMENTED; return (%s)NULL; }\n", pStrType);
					tab(); printf("static inline %s _%s_g%s$(",pStrType, accType, pName); pA->dumpParams(false); printf(");\n");
				} else {
					printf("virtual %s _%s_g%s(",pStrType, accType, pName); pA->dumpParams(false); printf(") = 0;\n");
					tab(); printf("virtual %s _%s_g%s$(",pStrType, accType, pName); pA->dumpParams(false); printf(") = 0;\n");
				}
			}
		}
		if (pA->m_set) {

			if (!isInterface && ((pA->m_set->m_modifier & ATT_ABSTRACT)==0) && (pA->m_set->m_statement)) {
				Variable* pParameter = CreateVarInstance("value");
				pParameter->setType(pA->m_type);
				gCurrentSD->addVariable(pParameter);

				bool		isNonNum	= ((pA->m_type->m_typeID & (ET_BASETYPE | ET_NUMBER))==ET_BASETYPE);
				bool		isBool		= (pA->m_type->m_typeID == ET_BOOL);
				bool		isEnum		= (pA->m_type->m_genreID == EGENRE::_ENUM);
				bool		isPtr		= pA->m_type->isGC_Able();
				bool		isReadable	= (pA->m_get != NULL);
				bool		isStatic	= (pA->m_modifier & ATT_STATIC);
				bool		isNativePtr	= (pA->m_type->m_typeID == TYPE_INTPTR);
				// Unsafe Setter
				tab(); 
				if (pA->m_modifier & ATT_STATIC) { printf("static "); }
				printf("%s %s _%s_s%s(",isVirt ? "virtual" : "inline",pStrType, accType, pName); pA->dumpParams(false, true); printf("%s value);\n", pStrType);
				if (!isStatic) {
					tab(); printf("inline %s _%s_s%s$(",
						pStrType, accType, pName);  pA->dumpParams(false, true); printf("%s value);\n", pStrType);
				}

				if (!isPtr && !isBool && isReadable) {
					dumpAccessorWrappers(pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
				}

			} else {
				tab();
				if (pA->m_modifier & ATT_STATIC) {
					printf("static %s _%s_s%s(",pStrType, accType, pName); pA->dumpParams(false, true); printf("%s value) { THROWUNIMPLEMENTED; }\n", pStrType);
					tab(); printf("static inline %s _%s_s%s$(",pStrType, accType, pName); pA->dumpParams(false, true); printf("%s value);\n");
				} else {
					printf("virtual %s _%s_s%s(",pStrType, accType, pName); pA->dumpParams(false, true); printf("%s value) = 0;\n", pStrType);
					tab(); printf("virtual %s _%s_s%s$(",pStrType, accType, pName); pA->dumpParams(false, true); printf("%s value) = 0;\n", pStrType);
				}
			}
		}

		// Destroy dico + Remove variable/parameters from dictionnary.
		gCurrentSD = gCurrentSD->removeDictionary();	
	}

	// TODO Dump Indexer

	// Dump function
	for (int n=0; n < this->m_methodCount; n++) {
		Method* pM = this->m_methods[n];
		gCurrentMethod = pM;
		if(pM->m_modifier & ATT_DTOR) {
			// The destructor body is dumped in _releaseGC().
			continue;
		}

		//
		// This is a bit complex so we need explaination here :
		// - We have dumped all struct in dependancy order.
		// - We have updated m_referenceModifCount during the dump of each member in dumpPrototype.
		//
		// --> m_referenceModifCount has been successfully evaluated, including recursive inclusion of struct inside struct.
		// --> "this" also works because we dump all members before dumping functions.
		//
		// ==> Thus analyzeRef can faithfully access to the type and read the m_referenceModifCount values and cumulate.
		//
		bool hasRef = pM->analyzeRef();

		tab(); pM->dumpTemplateLabel();
		if (isInterface || (pM->m_modifier & ATT_VIRTUAL) || (pM->m_modifier & ATT_ABSTRACT)) {
			printf("virtual ");
		}
		if (pM->m_modifier & ATT_STATIC) {
			printf("static ");
		}
		
		if (pM->m_modifier & (ATT_CTOR | ATT_DTOR)) {
			if (this->m_modifier & ATT_DTOR) {
				printf("~");
				hadDtor = true;
			} else if(!pM->m_parameters) {
				hadEmptyCtor = true;
			}
		} else {
			printf(pM->m_returnType->dumpTypeForCode(this)); printf(" ");
		}

		gIsStaticFunc = (pM->m_modifier & ATT_STATIC) != 0;

		const char* ext = "";
		if (pM->m_modifier & ATT_EXTERN)	{ printf("_ext_"); ext = "_ext_"; }
		if (pM->m_referenceModifCount)		{ printf("_ref_"); }
		printf(pM->getName());
		printf("(");
		
		pM->dumpParamsDef();

		printf(")");
		if (isInterface || (pM->m_modifier & ATT_ABSTRACT)) {
			printf(" = 0");
		}
		printf(";\n");

		if ((pM->m_modifier & ATT_STATIC) == 0) {
			if ((pM->m_modifier & (ATT_CTOR | ATT_DTOR)) == 0) {
				tab();
				pM->dumpTemplateLabel();
				printf("inline ");
				printf(pM->m_returnType->dumpTypeForCode(this)); printf(" "); printf(pM->getName()); printf("$(");				
				pM->dumpParamsDef();
				printf(");\n");
			}
		}

		//
		// Wrapper for corrected reference counting for the GC.
		//
		if (pM->m_referenceModifCount) {
			tab();
			printf("inline ");
			if (pM->m_modifier & ATT_STATIC) {
				printf("static ");
			}
			printf(pM->m_returnType->dumpTypeForCode(this)); printf(" "); printf(pM->getName()); printf("(");
			pM->dumpParamsDef();
			printf(");\n");
		}
	}
	gCurrentMethod = NULL;

	if ((!hadEmptyCtor) && (!isInterface)) {
		// Create default ctor
		tab(); printf("%s();\n",this->getName());
		this->m_bCreateDefaultCtor = true;
	}

	if (!isInterface && !isStruct) {
		tab(); printf("virtual u32 _processGC();\n");
		tab(); printf("virtual void _releaseGC();\n");
		tab(); printf("virtual bool _isInstanceOf(u32 typeID);\n");
		tab(); printf("virtual inline void _moveAlert(u32 offset);\n");
	}

	if (isStruct) {
		//
		// 1. Check for need
		//
		// The function bodies are declared later
		tab(); printf("inline u32 _processGC();\n");
		tab(); printf("inline void _releaseGC();\n");
		
		tab(); printf("inline void* _RefSetValue(void* newStruct);\n");
		tab(); printf("virtual inline void _moveAlert(u32 offset);\n");
		tab(); printf("inline static %s& __registerByRef(%s& m);\n",this->getName(), this->getName());
	}

	depth--; tab(); depth++; 
	printf("private:\n");

	tab(); printf("static const u32 _TYPEID = _TYPE_USEROBJECT | %s;\n", generateTypeID());

	depth--;
	//
	// Footer
	//
	tab(); printf("};\n");

	/*
	if (!isInnerClass) {
		// Dump root to class name space stack
		int n = nameSpaceCount-2; while (n >= 0) {
			printf("} ");
			n--;
		}
		printf("\n");
		depth--;
	}*/

	gCurrentAC = NULL;
}

void AbstractContainer::dumpInlineMethods(const char* prefix) {
	NameSpace* currSpace = this->m_pParent;
	const char* className = concat2(prefix, getTemplateParams());
	while(currSpace->getGenre() != EGENRE::_NAMESPACE) {
		currSpace = currSpace->m_pParent;
	}
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		const char* pStrType = pVar->m_type->dumpTypeForCode(currSpace);
		const char* name	 = pVar->m_name;
		bool isStatic	= pVar->m_modifier & ATT_STATIC;
		bool isPtr		= pVar->m_type->isGC_Able();
		bool isStruct;	
		if (pVar->m_type->m_definitionAC) {
			isStruct = (pVar->m_type->m_definitionAC->m_modifier & ATT_STRUCT) != 0;
		} else {
			isStruct = false;
		}

		if(isStatic) {
			if(isStruct) {
				tab(); dumpTemplateLabel(); printf("inline %s %s::_s%s(%s _$value)		{ return *(%s*)%s._RefSetValue(&_$value); }\n", pStrType, className , name, pStrType, pStrType, name);
			} else if(isPtr) {
				tab(); dumpTemplateLabel(); printf("inline %s %s::_s%s(%s _$value)		{ return (%s)System::__GCObject::_RefSetValue((System::__GCObject**)&%s,_$value); }\n",pStrType, className, name, pStrType, pStrType, name);
			}
		}
		else if (isPtr) {
			tab(); dumpTemplateLabel(); printf("inline ");
			printf("%s %s::_s%s(%s _$value)  { return (%s)System::__GCObject::_RefSetValue((System::__GCObject**)&%s,_$value); }\n", pStrType, className, name, pStrType, pStrType, name);
			tab(); dumpTemplateLabel(); printf("inline ");
			printf("%s %s::_s%s$(%s _$value) { CHCKTHIS; return _s%s(_$value); }\n", pStrType, className, name, pStrType, name);
		} else {
			if (isStruct) {
				tab(); dumpTemplateLabel(); printf("inline %s %s::_s%s(%s _$value)  { return *(%s*)%s._RefSetValue(&_$value); }\n", pStrType, className, name, pStrType, pStrType, name);
				tab(); dumpTemplateLabel(); printf("inline %s %s::_s%s$(%s _$value) { CHCKTHIS; return _s%s(_$value); }\n", pStrType, className , name, pStrType, name);
			} 
		}
	}

	printf("\n");

	if(this->m_modifier & ATT_STRUCT) {
		// GC Support for structures
		tab(); dumpTemplateLabel(); printf("inline u32 %s::_processGC() {\n", className);
		this->generateMemberProcessGCCode();
		tab(); printf("}\n");
		tab(); dumpTemplateLabel(); printf("inline void %s::_releaseGC() {\n", className);
		this->generateMemberReleaseGCCode();
		tab(); printf("}\n");
		
		tab(); dumpTemplateLabel(); printf("inline void* %s::_RefSetValue(void* newStruct) {\n", className);
		this->generateMemberAssignCode();
		depth++;
		tab(); (this->m_modifier & ATT_STRUCT) ? printf("return newStruct;\n") : printf("return newVal;\n");
		depth--;
		tab(); printf("}\n");

		// void  = 0;
		tab(); dumpTemplateLabel(); printf("inline void %s::_moveAlert(u32 offset) {\n", className);
		this->generateMemberMoveRefCode();
		tab(); printf("}\n");

		tab(); dumpTemplateLabel(); printf("inline %s& %s::__registerByRef(%s& m) {\n", className, className, className);
		this->generateMemberRefCode(this);
		depth++;
		tab(); printf("return m;\n");
		depth--;
		tab(); printf("}\n");
	}
}

void AbstractContainer::dumpAccessors(const char* prefix) {
	bool isInterface = ((this->m_modifier & ATT_INTERFACE) != 0);
	bool isStruct	 = ((this->m_modifier & ATT_STRUCT) != 0);

	for (int n=0; n < this->m_accessorCount; n++) {
		Accessor* pA = this->m_accessors[n];
		const char* pStrType	= pA->m_type->dumpTypeForCode(this->m_pParent);
		const char* pName		= pA->m_name ? pA->m_name : "";
		const char* accType		= pA->m_variable ? "idx" : "acc";

		// Create global dico + Add function parameters to dictionnary.
		if(!gCurrentSD) {	//gCurrentSD is supposed to be always NULL at this point
			gCurrentSD = new SymbolDictionary();
		}

		bool isVirt		 = false;
		if ((this->m_modifier & ATT_INTERFACE)) {
			// Do nothing.
		} else {
			if (pA->m_modifier & ATT_STATIC) {
				isVirt = false;
			} else {
				isVirt = ((pA->m_modifier & ATT_VIRTUAL) != 0);
				// TODO : detect interface implementation -> generate virtual ? C++ consider even without rewriting virtual... should work as is.
			}
		}

		if (pA->m_get) {
				if (!isInterface && ((pA->m_get->m_modifier & ATT_ABSTRACT)==0) && (pA->m_get->m_statement)) {
					tab();
					// Unsafe Getter
					printf("%s %s %s::_%s_g%s(",isVirt ? "" : "inline", pStrType, prefix, accType, pName); pA->dumpParams(false); printf(")");
					pA->m_get->m_statement->dumpStatement(); printf("\n");
					if ((pA->m_modifier & ATT_STATIC)==0) {
						tab(); printf("inline %s %s::_%s_g%s$(",pStrType, prefix, accType, pName); pA->dumpParams(false);
						printf(") { CHCKTHIS; return _%s_g%s(", accType, pName); pA->dumpParams(true); printf("); }\n\n");
					}
				}
			}
			if (pA->m_set) {
				if (!isInterface && ((pA->m_set->m_modifier & ATT_ABSTRACT)==0) && (pA->m_set->m_statement)) {
					Variable* pParameter = CreateVarInstance("value");
					pParameter->setType(pA->m_type);
					gCurrentSD->addVariable(pParameter);

					bool		isStatic	= (pA->m_modifier & ATT_STATIC);

					// Unsafe Setter
					tab(); 
					printf("%s %s %s::_%s_s%s(",isVirt ? "" : "inline",pStrType, prefix, accType, pName); pA->dumpParams(false, true); printf("%s value)", pStrType); tab(); printf("{\n");
					gCurrentSD = gCurrentSD->addDictionary();
					depth++;
					tab(); printf("%s _returnValue_ = value;\n", pStrType);
					pA->m_set->m_statement->m_pChild->dumpStatement();
					tab(); printf("return _returnValue_;\n");
					depth--;
					gCurrentSD = gCurrentSD->removeDictionary();
					tab(); printf("}\n");
					if (!isStatic) {
						tab(); printf("inline %s %s::_%s_s%s$(", pStrType, prefix, accType, pName);
						pA->dumpParams(false, true); printf("%s value)		{ CHCKTHIS; return _%s_s%s(", pStrType, accType, pName);
						pA->dumpParams(false, true); printf("value); }\n");		
					}
				}
			}
		// Destroy dico + Remove variable/parameters from dictionnary.
		gCurrentSD = gCurrentSD->removeDictionary();
	}
}

void AbstractContainer::dumpImplementation(const char* precNameSpace) {
	// If no dump set, do nothing.
	if (m_noDump) { return ; }

	if(m_csharpRepresentation) {
		m_csharpRepresentation->dumpImplementation(precNameSpace);
		return;
	}

	bool isInterface = ((this->m_modifier & ATT_INTERFACE) != 0);

	char prefix[1000];
	int strl = strlen(precNameSpace);
	if (strl) {
		sprintf(prefix,"%s::%s",precNameSpace,this->getName());
	} else {
		sprintf(prefix,"%s",this->getName());
	}

	const char* className = concat2(prefix, getTemplateParams());

	// Delegates are unnested.
	//dumpDelegates(prefix, this);

	//
	// Common initializer.
	//
	if(!isInterface) {
		gIsStaticFunc = false;
		tab(); dumpTemplateLabel(); printf("void %s::_ctor_%s() {\n",className, this->getName());
		depth++;
		for (int n=0; n < this->m_memberCount; n++) {
			Variable* pVar = this->m_members[n];
			if ((pVar->m_modifier & (ATT_CONST | ATT_STATIC)) == 0) {
				if (pVar->m_expression) {
					if(pVar->m_type->isGC_Able()) {
						tab(); printf("_s%s(", pVar->m_name);
						Expression::analysisTransformAndDump(&pVar->m_expression, pVar->m_type);
						printf(");\n");
					} else {
						tab(); printf("%s = ",pVar->m_name);
						Expression::analysisTransformAndDump(&pVar->m_expression, pVar->m_type);
						printf(";\n");
					}
				}
			}
		}
		depth--;
		tab(); printf("}\n\n");
	}

	//
	// Dump all functions.
	//
	gCurrentAC = this;

	for (int m=0; m < this->m_methodCount; m++) {
		Method* pMethod = this->m_methods[m];
		gCurrentMethod = pMethod;
		if ((pMethod->m_modifier & ATT_DTOR) != 0) {
			continue;
		}

		// Create global dico + Add function parameters to dictionnary.
		if(!gCurrentSD) {	//gCurrentSD is supposed to be always NULL at this point
			gCurrentSD = new SymbolDictionary();
		}

		g_unsafe = ((pMethod->m_modifier & ATT_UNSAFE) != 0);
		gIsStaticFunc = (pMethod->m_modifier & ATT_STATIC) != 0;

		if (pMethod->m_modifier & ATT_VIRTUAL)	{	tab(); printf("/*virtual*/\n");		}
		if (pMethod->m_modifier & ATT_STATIC)	{	tab(); printf("/*static*/\n");		}

		const char* extensionA = "";
		const char* extensionB = "";

		if (pMethod->m_modifier & ATT_EXTERN)	{ extensionA = "_ext_"; }
		if (pMethod->m_referenceModifCount)		{ extensionB = "_ref_"; }

		if ((pMethod->m_modifier & ATT_ABSTRACT) == 0 && !isInterface) {
			tab();
			dumpTemplateLabel();
			pMethod->dumpTemplateLabel();
			if (pMethod->m_modifier & ATT_CTOR) {
				// No return type.
			} else {
				printf(pMethod->m_returnType->dumpTypeForCode(this->m_pParent)); printf(" ");
			}

			printf("%s::%s%s%s(", className, extensionA, extensionB,pMethod->getName());

			Variable* pParameter = pMethod->m_parameters;
			bool first = true;
			while(pParameter) {
				// Register variable as local symbols for code.
				gCurrentSD->addVariable(pParameter);

				// Dump function parameters
				if (first) { first = false; } else { printf(","); }
				printf(pParameter->m_type->dumpTypeForCode(this));
				if (pParameter->m_modifier & ATT_REF) { printf("&"); }
				printf(" ");
				printf(pParameter->m_name);

				pParameter = pParameter->m_pNextVariable;
			}
			printf(")");

			gIsStaticFunc = false;
			if (pMethod->m_modifier & ATT_CTOR) {
				if (pMethod->m_initializerType >= 0) {	// -1 is none.
					// For now only accept BASE, and if pointer is not NULL -> Obvious call.
					const char* name = this->getAncestor()->getFullName(this);
					printf(" : %s(",name);
					if (pMethod->m_initializerOpt) {
						pMethod->m_initializerOpt->dumpExpression();
					}
					printf(")\n");
				} else {
					printf("\n");
				}

				tab(); printf("{\n");
				depth++;
				tab(); printf("_ctor_%s%s();\n", this->getName(), getTemplateParams());
			
				if (this->m_modifier & ATTRB_ANONDELEGATE) {
					// Constructor of anonymous delegate : copy parameter to member.
					Variable* pParameter = pMethod->m_parameters;
					while(pParameter) {
						if(pParameter->m_type->isGC_Able()) {
							tab(); printf("_s%s(%s);\n", pParameter->m_name, pParameter->m_name);
						} else {
							tab(); printf("%s = %s;\n", pParameter->m_name, pParameter->m_name);
						}
						pParameter = pParameter->m_pNextVariable;
					}
				}

				if(pMethod->m_codeBlock && pMethod->m_codeBlock->m_statementType == STM_BLOCK) {
					pMethod->m_codeBlock->m_pChild->dumpStatement();
					depth--;
				}
				else {
					depth--;
					pMethod->m_codeBlock->dumpStatement();
				}

				tab(); printf("}\n");
			} else {
				printf("\n");

				if (pMethod->m_codeBlock) {
					pMethod->m_codeBlock->dumpStatement();
				} else {
					if (pMethod->m_modifier & ATT_EXTERN) {
						pMethod->dumpMarshalling();
					}
				}
			}
			printf("\n");
		}

		// Dump Wrapper

		if ((pMethod->m_modifier & ATT_STATIC) == 0) {
			if ((pMethod->m_modifier & (ATT_CTOR | ATT_DTOR)) == 0) {
				tab();
				pMethod->dumpTemplateLabel();
				printf("inline ");
				printf(pMethod->m_returnType->dumpTypeForCode(this->m_pParent)); printf(" "); printf("%s::%s",className, pMethod->getName()); printf("$(");
				
				pMethod->dumpParamsDef();

				if (pMethod->m_returnType) {
					printf(") { CHCKTHIS; return %s%s(", pMethod->getName(), pMethod->getTemplateParams());
				} else {
					printf(") { CHCKTHIS; %s%s(", pMethod->getName(), pMethod->getTemplateParams());
				}

				Variable* pVar = pMethod->m_parameters;
				bool first = true;
				while (pVar) {
					if (first) { first = false; } else { printf(","); }
					printf(pVar->getName());
					pVar = pVar->m_pNextVariable;
				}

				printf("); }\n\n");
			}

		}

		//
		// Wrapper for corrected reference counting for the GC.
		//
		if (pMethod->m_referenceModifCount) {
			tab();
			printf("inline ");
			printf(pMethod->m_returnType->dumpTypeForCode(this)); printf(" "); printf("%s::%s",className, pMethod->getName()); printf("(");
				
			pMethod->dumpParamsDef();

			if (pMethod->m_returnType->m_typeID == TYPE_VOID) {
				printf(") { System::RefHolder _cs_refholder_loc_array[%i]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); %s_ref_%s(", pMethod->m_referenceModifCount, extensionA, pMethod->getName());
			} else {
				printf(") { System::RefHolder _cs_refholder_loc_array[%i]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); %s r = %s_ref_%s(", pMethod->m_referenceModifCount, pMethod->m_returnType->dumpTypeForCode(this), extensionA, pMethod->getName());
			}

			Variable* pVar = pMethod->m_parameters;
			bool first = true;
			while (pVar) {
				if (first) { first = false; } else { printf(","); }
				printf(pVar->getName());
				pVar = pVar->m_pNextVariable;
			}

			if (pMethod->m_returnType->m_typeID == TYPE_VOID) {
				printf("); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); }\n\n");
			} else {
				printf("); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }\n\n");
			}
		}

		// Destroy dico + Remove variable/parameters from dictionnary.
		gCurrentSD = gCurrentSD->removeDictionary();
	}
	gCurrentMethod = NULL;

	if(!isInterface) {
		if (this->m_bCreateDefaultCtor) {
			// No default constructor existed, so we implement one.
			tab();
			dumpTemplateLabel();
			printf("%s::%s() { _ctor_%s(); }\n\n",prefix,getName(),getName());
		}

		dumpInlineMethods(prefix);
		printf("\n");
		dumpAccessors(prefix);

		if (this->m_modifier & ATT_CLASS) {
			tab(); printf("/*virtual*/\n");
			tab(); dumpTemplateLabel(); printf("bool %s::_isInstanceOf(u32 typeID) {\n", className);
			tab(); printf("\t_INSTANCEOF(%s,%s);\n",getName(), this->getAncestor() ? this->getAncestor()->m_definitionAC->getFullName(this) : "System::Object");
			tab(); printf("}\n\n");

			//
			// GC Support
			//

			tab(); printf("/*virtual*/\n");
			tab(); dumpTemplateLabel(); printf("u32 %s::_processGC() {\n", className);
			this->generateMemberProcessGCCode();
			tab(); printf("}\n");


			tab(); printf("/*virtual*/\n");
			tab(); dumpTemplateLabel(); printf("void %s::_releaseGC() {\n", className);
			this->generateMemberReleaseGCCode();
			tab(); printf("}\n");

			tab(); printf("/*virtual*/\n");
			tab(); dumpTemplateLabel(); printf("void %s::_moveAlert(u32 offset) {\n", className);
			this->generateMemberMoveRefCode();
			tab(); printf("}\n");
		}
	}

	// Sub Classes which are still nested (anonymous delegates)
	for (int n=0; n < this->m_innerCount; n++) {
		if((m_pInner[n]->m_modifier & ATTRB_ANONDELEGATE) != 0) {
			this->m_pInner[n]->dumpImplementation(prefix);
		}
	}

	gCurrentAC = NULL;
}

void AbstractContainer::dumpMarshalledStruct(Variable* pVar) {
	if(!(m_modifier & ATT_STRUCT)) {
		compilerError(ERR_INTERNAL, "dumpMarshalledStruct() called on a class");
	}
	if(!(pVar->m_modifier & (ATT_REF | ATT_OUT))) {
		compilerError(ERR_USER, "Please pass structures to extern functions via references only", pVar->m_line);
	}
	Attribute* pAtt = m_attribute;
	if(!pAtt) {
		compilerError(ERR_USER, "Please use attributes for structure marshalling", m_line);
	}
	else {
		SMarshallingInfo info;
		pAtt->getMarshallingInfo(info);
		SStructInfo sInfo = info.m_structInfo;
		if(sInfo.m_layoutKind == 0 && sInfo.m_pack == 1) {
			// TODO : proper marshalling
			printf(pVar->m_name);
		}
		else {
			compilerError(ERR_NOT_SUPPORTED_YET, "Only StructLayout(LayoutKind.Sequential, Pack = 1) is supported for now", m_line);
		}
	}
}

void AbstractContainer::generateMemberProcessGCCode() {
	depth++;
	if (this->getAncestor()) {
		tab();printf("%s::_processGC();\n\n", this->getAncestor()->m_definitionAC->getFullName(this)); // TODO : verify if ancestor different package.
	}
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		if ((pVar->m_modifier & ATT_STATIC)==0) {
			SRSymbol sym = pVar->m_type->getResolvedType(this);
			switch (sym.symbolType) {
			case EGENRE::_ABSTRACTCONTAINER:
				{
					AbstractContainer* pCnt = (AbstractContainer*)sym.pSymbol;
					if (pCnt->m_modifier & ATT_STRUCT) {
						tab(); GCSupport::dumpStructGC(pVar, pCnt);
					} else {
						if (pVar->m_type->isGC_Able()) {
							tab(); GCSupport::dumpMemberGC(pVar);
						}
					}
				}
				break;
			case EGENRE::_ENUM:
				break;
			case EGENRE::_DELEGATE:
				tab(); GCSupport::dumpMemberGC(pVar);
				break;
			}
		}
	}
	tab(); printf("return System::__GCObject::COMPLETE;\n");
	depth--;
}

void AbstractContainer::generateMemberReleaseGCCode() {
	depth++;
	if (this->getAncestor()) {
		tab();printf("%s::_releaseGC();\n\n", this->getAncestor()->m_definitionAC->getFullName(this)); // TODO : verify if ancestor different package.
	}
	Method* pDtor = findDestructor();
	if(pDtor) {
		Statement* pCode = pDtor->m_codeBlock;
		if(pCode && pCode->m_statementType == STM_BLOCK) {
			pCode->m_pChild->dumpStatement();
		}
		else {
			pCode->dumpStatement();
		}
	}
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		if ((pVar->m_modifier & ATT_STATIC)==0) {
			SRSymbol sym = pVar->m_type->getResolvedType(this);
			switch (sym.symbolType) {
			case EGENRE::_ABSTRACTCONTAINER:
				{
					AbstractContainer* pCnt = (AbstractContainer*)sym.pSymbol;
					if (pCnt->m_modifier & ATT_STRUCT) {
						tab(); GCSupport::structReleaseGC(pVar, pCnt);
					} else {
						if (pVar->m_type->isGC_Able()) {
							tab(); GCSupport::memberReleaseGC(pVar);
						}
					}
				}
				break;
			case EGENRE::_ENUM:
				break;
			case EGENRE::_DELEGATE:
				tab(); GCSupport::memberReleaseGC(pVar);
				break;
			}
		}
	}
	depth--;
}


void AbstractContainer::generateMemberMoveRefCode() {
	depth++;
	if (this->getAncestor()) {
		tab();printf("%s::_moveAlert(offset);\n\n", this->getAncestor()->m_definitionAC->getFullName(this)); // TODO : verify if ancestor different package.
	}
	bool isFirstTime = true;
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		if ((pVar->m_modifier & ATT_STATIC)==0) {
			SRSymbol sym = pVar->m_type->getResolvedType(this);
			switch (sym.symbolType) {
			case EGENRE::_ABSTRACTCONTAINER:
				{
					AbstractContainer* pCnt = (AbstractContainer*)sym.pSymbol;
					if (pCnt->m_modifier & ATT_STRUCT) {
						// StructC::_RefSetValue(newVal.m_C);
						tab(); printf("%s._moveAlert(offset);\n",pVar->m_name);
					} else {
						if (pVar->m_type->isGC_Able()) {
							if(isFirstTime) {
								tab(); printf("u8* oldPtr; u8* newPtr;\n");
								isFirstTime = false;
							}
							tab(); printf("if (%s) {\n",pVar->m_name);
							tab(); printf("  newPtr = (u8*)(&%s); oldPtr = newPtr - offset;\n",pVar->m_name);
							tab(); printf("  %s->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);\n",pVar->m_name);
							tab(); printf("}\n");
						}
					}
				}
				break;
			case EGENRE::_ENUM:
				{
				}
				break;
			case EGENRE::_DELEGATE:
				if(isFirstTime) {
					tab(); printf("u8* oldPtr; u8* newPtr;\n");
					isFirstTime = false;
				}
				tab(); printf("if (%s) {\n",pVar->m_name);
				tab(); printf("  newPtr = (u8*)(&%s); oldPtr = newPtr - offset;\n",pVar->m_name);
				tab(); printf("  %s->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);\n",pVar->m_name);
				tab(); printf("}\n");
				break;
			}
		}
	}
	depth--;
}


void AbstractContainer::generateMemberAssignCode() {
	depth++;
	bool isStruct = (this->m_modifier & ATT_STRUCT) != 0;
	if(isStruct) {
		tab(); printf("%s* pStruct = (%s*)newStruct;\n", this->getName(), this->getName());
	}
	const char* newName = isStruct ? "pStruct->" : "newVal.";
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		if ((pVar->m_modifier & ATT_STATIC)==0) {
			SRSymbol sym = pVar->m_type->getResolvedType(this);
			switch (sym.symbolType) {
			case EGENRE::_ABSTRACTCONTAINER:
				{
					AbstractContainer* pCnt = (AbstractContainer*)sym.pSymbol;
					if (pCnt->m_modifier & ATT_STRUCT) {
						tab(); printf("this->%s._RefSetValue(&%s%s);\n",pVar->m_name, newName, pVar->m_name);
					} else {
						if (pVar->m_type->isGC_Able()) {
							// _RefSetValue(this->m_B, newVal.m_B);
							tab(); printf("System::__GCObject::_RefSetValue((System::__GCObject**)&this->%s,%s%s);\n",pVar->m_name, newName, pVar->m_name);
						} else {
							tab(); printf("this->%s = %s%s;\n",pVar->m_name, newName, pVar->m_name);
						}
					}
				}
				break;
			case EGENRE::_ENUM:
				{
					tab(); printf("this->%s = %s%s;\n",pVar->m_name, newName, pVar->m_name);
				}
				break;
			case EGENRE::_DELEGATE:
				tab(); printf("System::__GCObject::_RefSetValue((System::__GCObject**)&this->%s,%s%s);\n",pVar->m_name, newName, pVar->m_name);
				break;
			}
		}
	}
	depth--;
}

void AbstractContainer::generateMemberRefCode(AbstractContainer* pCtx) {
	depth++;
	for (int n=0; n < this->m_memberCount; n++) {
		Variable* pVar = this->m_members[n];
		if ((pVar->m_modifier & ATT_STATIC)==0) {
			SRSymbol sym = pVar->m_type->getResolvedType(this);
			switch (sym.symbolType) {
			case EGENRE::_ABSTRACTCONTAINER:
				{
					AbstractContainer* pCnt = (AbstractContainer*)sym.pSymbol;
					if (pCnt->m_modifier & ATT_STRUCT) {
						// StructC::_RefSetValue(newVal.m_C);
						tab(); printf("%s::__registerByRef(m.%s);\n",pCnt->getFullName(pCtx), pVar->m_name);
					} else {
						if (pVar->m_type->isGC_Able()) {
							// _RefSetValue(this->m_B, newVal.m_B);
							tab(); printf("System::__GCObject::__registerByRef((System::__GCObject*&)m.%s);\n",pVar->m_name);
						}
					}
				}
				break;
			case EGENRE::_ENUM:
				{
				}
				break;
			case EGENRE::_DELEGATE:
				tab(); printf("System::__GCObject::__registerByRef((System::__GCObject*&)m.%s);\n",pVar->m_name);
				break;
			}
		}
	}
	depth--;
}

const char* AbstractContainer::generateTypeID() {
	char buf[16];
	sprintf(buf, "%s | %i", ((m_modifier & ATT_STRUCT) == 0) ? "ET_CLASS" : "ET_STRUCT" , m_uniqueId);
	return concat(buf);
}

//Transforms a a::b::c string into a_b_c to be used as a label (deprecated)
/*
const char* labelize(const char* str)
{
	if(str)
	{
		char buf[100];
		int i = 0;
		int j = 0;
		while(str[i])
		{
			if(str[i]==':')
			{
				if(str[++i]==':')
				{
					buf[j] = '_';
				}
				else
				{
					compilerError(ERR_INTERNAL, "Invalid string : uses \":\" instead of \"::\"");
					return NULL;
				}
			}
			else
			{
				buf[j] = str[i];
			}
			i++;
			j++;
		}
		buf[j] = 0;
		return strdup(buf);
	}
	else
	{
		compilerError(ERR_INTERNAL, "Null string");
		return NULL;
	}
}
*/


void dumpSafeWrapper(const char* pName, const char* pStrType, const char* wrapperName, bool isStatic, bool isUnary, bool isEnum, bool isNativePtr)
{
	const char* typedParam;
	if(isUnary) {
		typedParam = "";
	} else if(isEnum || isNativePtr) {
		typedParam = "s32 value";
	} else {
		typedParam = concat2(pStrType, " value");
	}
	const char* param = isUnary ? "" : "value";
	if(!isStatic) {
		tab(); printf("inline %s _acc_s%s$%s(%s)			{ CHCKTHIS; return _acc_s%s%s(%s); }\n", 
						pStrType, pName, wrapperName, typedParam, pName, wrapperName, param);
	}
}

void dumpAccessorWrapper(EnumExpressionType type, const char* pName, const char* pStrType, bool isNonNum, const char* testDiv, bool isEnum, bool isStatic, bool isNativePtr)
{
	const char* modifier = isStatic ? "static inline" : "inline";

	switch(type) {
	case EXPR_ASS_EQ :
		compilerError(ERR_INTERNAL, "The dumpAccessorWrapper() function cannot be used to dump simple assignment wrappers");
		break;
	case EXPR_PLUSPLUS :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%spostInc()			{ %s tmp = _acc_g%s(); _acc_s%s((%s)((s32)tmp + 1)); return tmp; }\n", 
							modifier, pStrType, pName, pStrType, pName, pName, pStrType);
		} else {
			tab(); printf("%s %s _acc_s%spostInc()			{ %s tmp; _acc_s%s((tmp = _acc_g%s())+1); return tmp; }\n", 
							modifier, pStrType, pName, pStrType, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "postInc", isStatic, true, isEnum, isNativePtr);
		break;
	case EXPR_MINUSMINUS :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%spostDec()			{ %s tmp = _acc_g%s(); _acc_s%s((%s)((s32)tmp - 1)); return tmp; }\n", 
							modifier, pStrType, pName, pStrType, pName, pName, pStrType);
		} else {
			tab(); printf("%s %s _acc_s%spostDec()			{ %s tmp; _acc_s%s((tmp = _acc_g%s())-1); return tmp; }\n",
							modifier, pStrType, pName, pStrType, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "postDec", isStatic, true, isEnum, isNativePtr);
		break;
	case EXPR_PREINCR :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%spreInc()			{ return _acc_s%s((%s)((s32)_acc_g%s()+1)); }\n", 
						modifier, pStrType, pName, pName, pStrType, pName);
		} else {
			tab(); printf("%s %s _acc_s%spreInc()			{ return _acc_s%s(_acc_g%s()+1); }\n", 
							modifier, pStrType, pName, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "preInc", isStatic, true, isEnum, isNativePtr);
		break;
	case EXPR_PREDECR :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%spreDec()			{ return _acc_s%s((%s)((s32)_acc_g%s()-1)); }\n", 
						modifier, pStrType, pName, pName, pStrType, pName);
		} else {
			tab(); printf("%s %s _acc_s%spreDec()			{ return _acc_s%s(_acc_g%s()-1); }\n",
							modifier, pStrType, pName, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "preDec", isStatic, true, isEnum, isNativePtr);
		break;
	case EXPR_ASS_PLUSEQ :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%sAddEq(s32 value)	{ return _acc_s%s((%s)((s32)_acc_g%s() + value)); }\n", 
							modifier, pStrType, pName, pName, pStrType, pName);
		}
		else if(isNativePtr) {
			tab(); printf("%s %s _acc_s%sAddEq(s32 value)	{ return _acc_s%s(_acc_g%s() + value); }\n", 
							modifier, pStrType, pName, pName, pName);
		} else {
			tab(); printf("%s %s _acc_s%sAddEq(%s value)	{ return _acc_s%s(_acc_g%s() + value); }\n", 
							modifier, pStrType, pName, pStrType, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "AddEq", isStatic, false, isEnum, isNativePtr);
		break;
	case EXPR_ASS_MINUSEQ :
		if(isEnum) {
			tab(); printf("%s %s _acc_s%sSubEq(s32 value)	{ return _acc_s%s((%s)((s32)_acc_g%s() - value)); }\n", 
							modifier, pStrType, pName, pName, pStrType, pName);
		} else if(isNativePtr) {
			tab(); printf("%s %s _acc_s%sSubEq(s32 value)	{ return _acc_s%s(_acc_g%s() - value); }\n", 
							modifier, pStrType, pName, pName, pName);
		} else {
			tab(); printf("%s %s _acc_s%sSubEq(%s value)	{ return _acc_s%s(_acc_g%s() - value); }\n", 
							modifier, pStrType, pName, pStrType, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "SubEq", isStatic, false, isEnum, isNativePtr);
		break;
	case EXPR_ASS_STAREQ :
		tab(); printf("%s %s _acc_s%sMulEq(%s value)	{ return _acc_s%s(_acc_g%s() * value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "MulEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_DIVEQ :
		tab(); printf("%s %s _acc_s%sDivEq(%s value)	{ %sreturn _acc_s%s(_acc_g%s() / value); }\n", 
						modifier, pStrType, pName, pStrType, testDiv , pName, pName);
		dumpSafeWrapper(pName, pStrType, "DivEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_MODEQ :
		if (isNonNum) {
			tab(); printf("%s %s _acc_s%sModEq(%s value)	{ %sreturn _acc_s%s(_acc_g%s() %% value); }\n", 
							modifier, pStrType, pName, pStrType, testDiv , pName, pName);
		} else {
			tab(); printf("%s %s _acc_s%sModEq(%s value)	{ %s %s orig = _acc_g%s(); s32 tmp = (s32)(orig / value); return _acc_s%s(orig - (tmp * value)); }\n",
							modifier, pStrType, pName, pStrType, testDiv , pStrType, pName, pName);
		}
		dumpSafeWrapper(pName, pStrType, "ModEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_XOREQ :
		tab(); printf("%s %s _acc_s%sXorEq(%s value)	{ return _acc_s%s(_acc_g%s() ^ value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "XorEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_ANDEQ :
		tab(); printf("%s %s _acc_s%sAndEq(%s value)	{ return _acc_s%s(_acc_g%s() & value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "AndEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_OREQ :
		tab(); printf("%s %s _acc_s%sOrEq(%s value)		{ return _acc_s%s(_acc_g%s() | value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "OrEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_RSHFTEQ :
		tab(); printf("%s %s _acc_s%sRShiftEq(%s value)	{ return _acc_s%s(_acc_g%s() >> value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "RShiftEq", isStatic, false, false, isNativePtr);
		break;
	case EXPR_ASS_LSHFTEQ :
		tab(); printf("%s %s _acc_s%sLShiftEq(%s value)	{ return _acc_s%s(_acc_g%s() << value); }\n", 
						modifier, pStrType, pName, pStrType, pName, pName);
		dumpSafeWrapper(pName, pStrType, "LShiftEq", isStatic, false, false, isNativePtr);
		break;
	default :
		compilerError(ERR_INTERNAL, "Unknown assignment expression");
	}
}

void dumpAccessorWrappers(const char* pName, const char* pStrType, bool isNonNum, const char* testDiv, bool isEnum, bool isStatic, bool isNativePtr)
{
	if(!isNativePtr) {
		dumpAccessorWrapper(EXPR_PLUSPLUS, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		dumpAccessorWrapper(EXPR_MINUSMINUS, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		dumpAccessorWrapper(EXPR_PREINCR, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		dumpAccessorWrapper(EXPR_PREDECR, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
	}

	dumpAccessorWrapper(EXPR_ASS_PLUSEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
	dumpAccessorWrapper(EXPR_ASS_MINUSEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);

	if(!isEnum && !isNativePtr) {
		dumpAccessorWrapper(EXPR_ASS_STAREQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		dumpAccessorWrapper(EXPR_ASS_DIVEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		dumpAccessorWrapper(EXPR_ASS_MODEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		if(isNonNum) {
			dumpAccessorWrapper(EXPR_ASS_XOREQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
			dumpAccessorWrapper(EXPR_ASS_ANDEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
			dumpAccessorWrapper(EXPR_ASS_OREQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
			dumpAccessorWrapper(EXPR_ASS_RSHFTEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
			dumpAccessorWrapper(EXPR_ASS_LSHFTEQ, pName, pStrType, isNonNum, testDiv, isEnum, isStatic, isNativePtr);
		}
	}
}

void dumpGlobalInitializerPrototype() {
	SInitialization* p = gGlobalInitList;
	while (p) {
		if(p->m_isDumped) {
			if ((p->m_mode == SInitialization::INIT_WRAP_FUNC) || (p->m_mode == SInitialization::INIT_MEMCPY)) {
				tab(); printf("void* _global_array_initializer_%i(void* array_);\n",p->m_expressionCounter);
			}
		}
		p = p->m_next;
	}
	printf("\n");
}

// = MemCpy
// EXPR_CTE
// EXPR_NULL

// = Chaining for now.
// 
//

void dumpGlobalInitializerImplementation() {
	//
	// TODO support also : _array_->_setChain(idx, value)->_setChain(idx,value)->...
	// TODO optimize complete static array with memcpy.
	//
	SInitialization* p = gGlobalInitList;
	while (p) {
		if(p->m_isDumped) {
			if ((p->m_mode == SInitialization::INIT_WRAP_FUNC) || (p->m_mode == SInitialization::INIT_MEMCPY)) {
				tab(); printf("void* _global_array_initializer_%i(void* array_) {\n",p->m_expressionCounter);
				depth++;
				const char* type = p->m_typeArray->dumpTypeForCode(gRootNameSpace);
				tab(); printf("%s _array = (%s)array_;\n\n",type,type);

				if (p->m_mode == SInitialization::INIT_WRAP_FUNC) {
					for (int n=0; n < p->m_expression->m_expressionCount; n++) {
						tab();printf("_array->_idx_s(%i,",n);
						p->m_expression->m_expressions[n]->dumpExpressionInternal();
						printf(");\n");
					}
				}

				if (p->m_mode == SInitialization::INIT_MEMCPY) {
					tab();printf("static const %s _arrayCTE[] = {",p->m_typeArray->m_originalType->dumpTypeForCode(gRootNameSpace));
					for (int n=0; n < p->m_expression->m_expressionCount; n++) {
						if (n != 0) { printf(","); }
						p->m_expression->m_expressions[n]->dumpExpressionInternal();
					}
					printf("};\n");
					tab();printf("_array->_setMemCpy(_arrayCTE);\n");
				}

				tab(); printf("return array_;\n");
				depth--;
				tab(); printf("}\n",p->m_expressionCounter);
			}
		}

		p = p->m_next;
	}
}
