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
#ifndef CKLBUIForm_h
#define CKLBUIForm_h

#include "CKLBUITask.h"
#include "CompositeManagement.h"
#include "CKLBUISystem.h"
#include "CKLBNodeAnimPack.h"
#include "CKLBFormIF.h"
#include "CKLBModalStack.h"
#include "CKLBFormGroup.h"

/*!
* \class CKLBUIForm
* \brief Form Task Class
* 
* CKLBUIForm is designed to manage forms in the Game.
* It allows to manage a whole form (composed of several sub elements) very easily.
*/
class CKLBUIForm : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIForm>;
private:
	CKLBUIForm();
	virtual ~CKLBUIForm();

	bool init(CKLBUITask* parent, CKLBNode* pNode, u32 order, float x, float y, bool bAssetFile, const char* asset, bool bExclusive, bool modal, bool urgent);
	bool initCore(u32 order, float x, float y, bool bAssetFile, const char* asset, u32 size, bool bExclusive, bool modal, bool urgent);

public:
	static CKLBUIForm* create(CKLBUITask* parent, CKLBNode* pNode, u32 order, float x, float y, bool bAssetFile, const char* asset, bool bExclusive, bool modal, bool urgent);
	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	u32 getClassID();

	// Read only
	inline const char*  getAsset    ()				    { return m_asset;			}

	// Read Only
	inline 
	virtual u32         getOrder    ()					{ return m_order;			}

	inline bool         getExclusive()					{ return m_bExclusive;		}
	inline void         setExclusive(bool exclusive)	{ m_bExclusive = exclusive; }
	
	// Read Only
	inline bool         getAssetFile()					{ return m_bAssetFile;		}

	/* Read only
	inline
	void setAssetFile(bool fileAsset)			{ m_bAssetFile = fileAsset; }
	*/

	inline void setEnable       (bool isEnable)		            {
		m_bEnable = isEnable;
		CKLBUISelectable * pItem;
		for(pItem = m_ctrlList.pBegin; pItem; pItem = pItem->getNextSelectable()) {
			pItem->setEnabled(isEnable);
		}
	}

	inline void inputEnable     (bool bEnable)					{ 
		m_bInputEnable = bEnable;
		m_ctrlList.bEnable = m_bEnable && m_bInputEnable;	// モーダル状態との複合になる。
	}

	inline bool setAnimCallback (const char* callback)		        { return m_animpack.setCallback(callback);		}

	inline bool animation       (const char* animname, bool blend)  { return m_animpack.kickAnim(getNode(), animname, blend);	}

	inline bool animEnter       ()									{ return m_animpack.kickEnter(getNode());		}

	inline bool animLeave       ()									{ return m_animpack.kickLeave(getNode());		}

	inline bool isAnim          (const char* name)					{
		int cnt = m_animpack.getAnimCounter(name);
		return (cnt > 0);
	}

	inline bool skipAnim        (const char* name)					{ return m_animpack.skipAnim(getNode(), name);	}

	inline bool setGroup        (const char* group_name)			{ return CKLBFormGroup::getInstance().addForm(&m_ctrlList, group_name);	}

	inline bool existNode       (const char* name)					{ return m_formIF.isExistNode(getNode(), name);	}

	void		setGlobalVolume (float volume);
protected:
	u32			m_order;
	const char* m_asset;
	bool		m_bAssetFile;
	bool		m_bExclusive;
private:
	void         setGlobalVolume_r  (CKLBNode* pNode, float volume);
	bool         setFormEnable      (bool bEnable);
	virtual void setVisible         (bool visible);

	CKLBNode		*	m_pFormNode;
	SFormCtrlList		m_ctrlList;
	u32					m_handle;

	CKLBNodeAnimPack	m_animpack;		// ポインタではないので注意

	CKLBFormIF			m_formIF;
	CKLBModalStack		m_modalStack;

	bool				m_bEnable;		// これまでのモーダルenable
	bool				m_bInputEnable;	// これまでの InputEnable

	static	PROP_V2		ms_propItems[];
};

#endif // CKLBUIForm_h
