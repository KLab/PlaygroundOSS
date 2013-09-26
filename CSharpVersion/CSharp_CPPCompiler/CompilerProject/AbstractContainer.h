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
#ifndef ABSTRACTCONTAINER_H
#define ABSTRACTCONTAINER_H

#include "BaseType.h"
#include "NameSpace.h"
#include "TypeObject.h"

// Class and struct can have inner class/struct/interface
// They act as a kind of namespace.
// Support Interface inheritance mecanism
class AbstractContainer : public NameSpace {
public:
	AbstractContainer();
	~AbstractContainer();

	virtual int getGenre();
	virtual const char*	getName();

	TypeObject*			getType();
	AbstractContainer*	addInheritance(TypeObject* type);
	void				fixInheritance();
	Variable*			addVariable(Attribute* attribute, u32 modifier, TypeObject* type, Variable* variable);
	AbstractContainer*	addProperty(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Accessor* accessor);
	AbstractContainer*	addProperty(Attribute* attribute, u32 modifier, Accessor* indexer);
	Method*				addConstructor(Attribute* attribute, u32 modifier, const char* name, Variable* params, Statement* code, Expression* initializerOpt, s32 optType);
	Method*				addDestructor(Attribute* attribute, u32 modifier, const char* name, Statement* code);
	Method*				addMethod(Attribute* attribute, u32 modifier, const char* name, Variable* params, Statement* code, TypeObject* returnType);
	Variable*			findMember(const char* name);
	Method*				findMethod(const char* name, Expression* signature,	TypeGenericEntry* genParams);
	Method*				findMethod(const char* name, Variable* signature,	TypeGenericEntry* genParams);
	Method*				findDestructor();
	Accessor*			findProperty(const char* name);
	Accessor*			findPropertyIndexer(Expression* solvedSignatureList);

	void				setGenericParam();
	TypeObject*			getGenericType(TypeGenericDefinitionEntry* genericSymbol, TypeGenericEntry* genericParams);

	void		addMethod			(Method*		pMethod);
	void		addMember			(Variable*		pMember);
	void		addAccessor			(Accessor*		pAccess);
	TypeObject*	getAncestor			();
	
	const char*	getTemplateParams	();
	void		dumpTemplateLabel	();
	void		dumpFriends			();
	void		dumpNested			();
	void		dumpPrototype		(bool isInnerClass);
	void		realDumpPrototype	(bool isInnerClass, const char* fullName);
	void		analyzeComplete		();
	void		dumpInlineMethods	(const char* prefix);
	void		dumpAccessors		(const char* prefix);
	void		dumpImplementation	(const char* prevNameSpace);
	void		dumpMarshalledStruct(Variable* pVar);
	void		generateMemberProcessGCCode();
	void		generateMemberReleaseGCCode();
	void		generateMemberAssignCode();
	void		generateMemberMoveRefCode();
	void		generateMemberRefCode(AbstractContainer* pCtx);
	const char*	generateTypeID();

	TypeGenericDefinitionEntry*	m_genericParam;

	Method**			m_methods;
	int					m_methodCount;
	Variable**			m_members;
	int					m_memberCount;
	Accessor**			m_accessors;
	int					m_accessorCount;
	TypeObject**		m_inheritances;
	int					m_inheritancesCount;

	AbstractContainer*	m_ownerInner;
	AbstractContainer*	m_cppRepresentation;
	AbstractContainer*	m_csharpRepresentation;

	TypeObject*			m_ancestor;
	Attribute*			m_attribute;
	u32					m_modifier;
	u32					m_operator;
	
	u32					m_referenceModifCount;

	bool				m_bCreateDefaultCtor;
	bool				m_bAsGCAbleMember;

	const char*			m_cacheFullName;
	Variable*			m_pVariables;

	TypeObject			myType;
	void overrideType(TypeObject* pSolvedType);
};

/*
class Member {
public:
	bool				m_isConst;
	TypeObject*			m_type;
	u32					m_attribute;

};*/

AbstractContainer*	CreateClass	(Attribute* attribute, u32 modifier, const char* name);
AbstractContainer*	CreateStruct(Attribute* attribute, u32 modified, const char* name);
AbstractContainer*	CreateInterface(Attribute* attribute, u32 modified, const char* name);

#endif	ABSTRACT_CONTAINER_H
