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
//
// === Base System for object reflection mecanism, allocation ===
//
//

#ifndef __KLB_OBJECT_BASE__
#define __KLB_OBJECT_BASE__


#include "BaseType.h"

class CKLBStream;
class CKLBObject;

class CKLBContext {
	// Perform allocation.
	friend class CKLBObject;
public:
	CKLBContext		();
	~CKLBContext	();

	static			
	CKLBContext*	getContext		();
	
protected:
	void*			allocate		(unsigned int numByte);
	void			disallocate		(void* ptr);
};

class CKLBObject {
	friend class CKLBStream;
	friend class CKLBContext;
public:
	CKLBObject():
	  m_msgListener(NULL)	{ }

	virtual ~CKLBObject()	{ /* Do nothing by default */ }

	void* operator new( size_t num_bytes) {
		return CKLBContext::getContext()->allocate(num_bytes);
    }

	void operator delete(void* ptr) {
		if (ptr) {
			CKLBContext::getContext()->disallocate(ptr);
		}
    }

	virtual u32 getClassID() = 0;

	virtual void replaceAsset	(void* ptrAssetOld, void* ptr) {
		ptrAssetOld = ptrAssetOld;
		ptr = ptr;
		/* Do nothing */ 
	}

	virtual void receiveMsg		(CKLBObject* emitter, u32 msgID, u32 msgParam)	{ 
		/* Do nothing by default */ 
		emitter = emitter;
		msgID = msgID;
		msgParam = msgParam;
	}
protected:
	CKLBObject*		m_msgListener;

	inline
	void MsgRegister(CKLBObject* listener)	{
		klb_assert(!m_msgListener, "low level message listener already used by somebody else %8x", m_msgListener);
		m_msgListener = listener;
	}	
};

#ifndef _NULLHANDLER
#define _NULLHANDLER 0xFFFFFFFF
#endif

class CKLBObjectScriptable : public CKLBObject {
private:
	u32		m_handle;

public:
	CKLBObjectScriptable	(unsigned int handle = _NULLHANDLER);
	~CKLBObjectScriptable	();

	inline
	void setScriptHandle	(u32 handle)		{ m_handle = handle;	}
	inline
	u32  getScriptHandle	()					{ return m_handle;		}
};

#endif
