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
#ifndef CKLBUISimpleItem_h
#define CKLBUISimpleItem_h

#include "CKLBUITask.h"

/*!
* \class CKLBUISimpleItem
* \brief Simple Item task Class
* 
* CKLBUISimpleItem is a simple Image.
*/
class CKLBUISimpleItem : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUISimpleItem>;
private:
	CKLBUISimpleItem();
	virtual ~CKLBUISimpleItem();
	bool init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset);
	bool initCore(u32 order, float x, float y, const char* asset);
public:
	virtual u32 getClassID();
	static CKLBUISimpleItem* create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset);
	bool initUI (CLuaState& lua);
	void execute(u32 deltaT);
	void dieUI  ();

	inline virtual void setOrder(u32 order) {
		if (order != m_order) {
			m_order = order;
			m_pNode->setPriority(m_order);
		}
	}

	inline virtual u32  getOrder() { return m_order; }
	inline const char*	getAsset() { return m_asset; }

private:
	u32				m_order;
	const char*		m_asset;
	u32				m_handle;
	CKLBNode	*	m_pNode;

	static	PROP_V2		ms_propItems[];
};

#endif // CKLBUISimpleItem_h
