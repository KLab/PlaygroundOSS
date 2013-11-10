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
#ifndef CKLBUIScale9_h
#define CKLBUIScale9_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIScale9
* \brief Scale 9 Task CLass
* 
* CKLBUIScale9 is designed to manage assets cut in 9 parts.
* 4 for corners, 4 for borders and 1 for the center.
*/
class CKLBUIScale9 : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIScale9>;
private:
	CKLBUIScale9();
	virtual ~CKLBUIScale9();
protected:
	enum PROP_ID{
		PR_ORDER /*= PRG_LAST_UITASK  <-- Support in FUTURE changes */,
		PR_WIDTH,
		PR_HEIGHT,
		PR_ASSET,
		PR_LAST_UISCALE9
	};
public:
	virtual u32 getClassID();
	static CKLBUIScale9 * create(CKLBUITask * pParent, CKLBNode * pNode, u32 order, float x, float y, s32 width, s32 height, const char* SCALE9Asset);
	
	bool init		(CKLBUITask * pParent, CKLBNode * pNode, u32 order, float x, float y, s32 width, s32 height, const char* SCALE9Asset);
	bool initCore	(u32 order, float x, float y, s32 width, s32 height, const char* SCALE9Asset);

	bool initUI		(CLuaState& lua);
	int commandUI	(CLuaState& lua, int argc, int cmd);

	void execute	(u32 deltaT);
	void dieUI		();

	inline void setWidth(s32 width) {
		if(m_width != width) {
			m_scale9->setWidth(width);
			m_width = width;
			getNode()->markUpMatrix();
		}
	}
	inline s32 getWidth() { return m_width; }

	inline void setHeight(s32 height) {
		if(m_height != height) {
			m_scale9->setHeight(height);
			m_height = height;
			getNode()->markUpMatrix();
		}
	}
	inline s32 getHeight() { return m_height; }

	inline void setOrder(u32 order) {
		if(order != m_order) {
			m_scale9->changeOrder(CKLBRenderingManager::getInstance(),order);
			m_order = order;
		}
	}
	inline u32 getOrder() { return m_order; }

	inline const char* getAsset() { return m_asset; }

	bool setAsset	(const char* asset);

private:
	u32					m_handle;
	CKLBTextureAsset*	m_texture;
	const char*			m_asset;
	CKLBSpriteScale9*	m_scale9;
	
	bool			    m_bInit;
	u32				    m_order;
	s32				    m_width;
	s32				    m_height;

	static PROP_V2			ms_propItems[];

	/* FUTURE property handling.
	static
	const char *	s_Scale9NameStatic		[PR_LAST_UISCALE9];
	VALUE			m_Scale9PropValue		[PR_LAST_UISCALE9];
	PROPTYPE		m_Scale9PropType		[PR_LAST_UISCALE9];
	bool			m_Scale9PropChecked		[PR_LAST_UISCALE9];
	*/
};

#endif // CKLBUIScale9_h
