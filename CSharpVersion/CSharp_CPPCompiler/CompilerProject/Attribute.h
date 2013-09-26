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
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "BaseType.h"

typedef struct SStructInfo {
public:
	s32 m_charSet;
	s32 m_pack;
	s32 m_layoutKind;

	SStructInfo();
} SStructInfo ;

typedef struct {
public:
	SStructInfo m_structInfo;
} SMarshallingInfo ;

class Attribute {
public:
	Attribute();
	~Attribute();

	Attribute*	addAttribute(TypeObject* type, Expression* expr);	// return this
	Attribute*	addChildAttribute(Attribute* attr);
	Attribute*	setSpecifier(u32 specifierAttrb);

	void		getMarshallingInfo(SMarshallingInfo& out_marshallingInfo);

	TypeObject*	m_type;
	Expression*	m_expression;
	Attribute*	m_next;
	Attribute*	m_child;
	u32			m_specifier;
};

Attribute*  CreateAttribute(TypeObject* type, Expression* expr);
Attribute*	CreateAttributeWithChild(Attribute* attr);

#endif	//ATTRIBUTE_H
