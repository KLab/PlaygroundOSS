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

SStructInfo::SStructInfo()
:m_charSet		(-1)
,m_pack			(-1)
,m_layoutKind	(-1)
{
}

Attribute::Attribute() 
:m_expression		(NULL)
,m_type				(NULL)
,m_next				(NULL)
,m_child			(NULL)
,m_specifier		(0)
{
}

Attribute::~Attribute() 
{
	delete m_expression;
	delete m_type;
	delete m_next;
	delete m_child;
}

Attribute* Attribute::addChildAttribute(Attribute* pChild) {
	Attribute* p = m_child;
	if (p) {
		while (p->m_next) { p = p->m_next; }
		p->m_next = pChild;
	} else {
		m_child = pChild;
	}
	return this;
}

Attribute* Attribute::addAttribute(TypeObject* type, Expression* expr)
{
	Attribute* pNewAttr = new Attribute();
	Attribute* p = this;
	while (p->m_next) { p = p->m_next; }
	p->m_next = pNewAttr;

	this->m_expression	= expr;
	this->m_type		= type;
	return this;
}

Attribute* Attribute::setSpecifier(u32 specifierAttrb) 
{
	this->m_specifier |= specifierAttrb;
	return this;
}

void Attribute::getMarshallingInfo(SMarshallingInfo& out_marshallingInfo) {
	//TODO : complete
	if(m_child) {
		m_child->getMarshallingInfo(out_marshallingInfo);
	}
	if(m_next) {
		m_next->getMarshallingInfo(out_marshallingInfo);
	}
	if(m_expression) {
		if(strcmp(m_type->m_name, "StructLayout") == 0) {
			m_expression->getStructInfo(out_marshallingInfo.m_structInfo);
		} else {
			//TODO
		}
	}
}

Attribute*  CreateAttribute(TypeObject* type, Expression* expr) {
	Attribute* attr		= new Attribute();
	attr->m_expression	= expr;
	attr->m_type		= type;
	if (type) {
		if (strcmp(type->getName(),"DllImport") == 0) {
			// Mark the attribute with an "external" tag as hint.
			attr->m_specifier |= ATT_EXTERN;
			bool callConv = false;
			if (expr) {
				if (expr->m_expressionType == EXPR_LIST) {
					int n = 0;
					while (n < expr->m_expressionCount) {
						Expression* p = expr->m_expressions[n];
						if (p->m_expressionType == EXPR_ASS_EQ) {
							if (p->m_expressionCount == 2) {
								if ((p->m_expressions[0]->m_expressionType == EXPR_IDENT) && (p->m_expressions[1]->m_expressionType == EXPR_DOT)) {
									if (strcmp(p->m_expressions[0]->m_text, "CallingConvention") == 0) {
										if (strcmp(p->m_expressions[1]->m_text, "Cdecl")!=0) {
											compilerError(ERR_NOT_SUPPORTED_YET, "Do NOT support other interface convention than Cdecl for now, please check your DllImport attribute");
										} else {
											callConv = true;							
										}
									}
								}
							}
						}
						n++;
					}
				}
			}

			if (callConv == false) {
				compilerError(ERR_USER, "Calling convention not defined at all, for now 'Cdecl' is the only supported convention.");
			}
		}
	}
	return attr;
}

Attribute*	CreateAttributeWithChild(Attribute* attr) {
	Attribute* newAttr		= new Attribute();
	newAttr->addChildAttribute(attr);
	return newAttr;
}