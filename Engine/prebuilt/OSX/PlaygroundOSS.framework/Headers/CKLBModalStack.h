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
#ifndef CKLBModalStack_h
#define CKLBModalStack_h

class CKLBModalStack
{
public:
	CKLBModalStack(bool bModal = false, bool bUrgent = false);
	virtual ~CKLBModalStack();

	inline bool isUrgent() const { return m_bUrgent; }
	inline bool isModal () const { return m_bModal;  }
	inline bool isEnable() const { return m_bEnable; }

	inline bool setModal(bool bModal, bool bUrgent = false) {
		m_bModal  = bModal;
		m_bUrgent = bUrgent;
        if(m_bUrgent) { m_bModal = true; }
		return m_bModal;
	}
	 
	inline bool setEnable(bool bEnable) {
		m_bEnable = bEnable;
		return m_bEnable;
	}

	void push   ();
	void pop    ();
	void remove ();

private:
	
	bool						m_bEnable;

	bool						m_bModal;
	bool						m_bUrgent;

	CKLBModalStack			*	m_prev;
	CKLBModalStack			*	m_next;

	static CKLBModalStack	*	ms_begin;
	static CKLBModalStack	*	ms_end;
};


#endif // CKLBModalStack_h
