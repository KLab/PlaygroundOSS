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
#ifndef CKLBUIClip_h
#define CKLBUIClip_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIClip
* \brief Clip Task Class
* 
* CKLBUIClip creates a Task clipping the screen for the required area.
* Sub tasks outside the clipping area will not be drawn.
*/
class CKLBUIClip : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIClip>;
private:
	CKLBUIClip();
	virtual ~CKLBUIClip();

public:
	virtual u32 getClassID();

	static CKLBUIClip * create(CKLBUITask * pParent, CKLBNode * pNode,
								u32 base_order, u32 max_order,
								float x, float y, float clip_width, float clip_height);
	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline u32  getOrder() { return m_uiOrder;	}
	inline void	setOrder(u32 order) {
		if (order != m_uiOrder) {
			m_uiOrder = order;
			REFRESH_A;
		}
	}

	inline float getWidth() { return m_fWidth; }
	inline void	 setWidth(float width) {
		if (width != m_fWidth) {
			m_fWidth = width;
			REFRESH_A;
		}
	}

	inline float getHeight() { return m_fHeight; }
	inline void	 setHeight(float height) {
		if (height != m_fHeight) {
			m_fHeight = height;
			REFRESH_A;
		}
	}

	inline u32  getMaxOdr() { return m_uiMaxOdr;	}
	inline void	setMaxOdr(u32 maxodr) {
		if (maxodr != m_uiMaxOdr) {
			m_uiMaxOdr = maxodr;
			REFRESH_A;
		}
	}

	inline void setPosition(float x, float y) {
		setX(x);
		setY(y);
		getNode()->setTranslate(x, y);
		REFRESH_A;
	}

	inline void setSize(float width, float height) {
		m_fWidth  = width;
		m_fHeight = height;
		REFRESH_A;
	}

private:
	bool init(CKLBUITask * pParent, CKLBNode * pNode,
              u32 base_order, u32 max_order,
              float x, float y, float clip_width, float clip_height);

	bool initCore(u32 base_order, u32 max_order,
				  float x, float y, float clip_width, float clip_height);

	bool setClip(u32 orderBegin, u32 orderEnd,
				 s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight);

	// clip情報
	int						m_basePriority;	// クリッピング基点プライオリティ
	int						m_endPriority;	// クリッピング終了プライオリティ

	u32						m_uiOrder;
	float					m_fWidth;
	float					m_fHeight;
	u32						m_uiMaxOdr;

	float					m_clipX;
	float					m_clipY;
	int						m_clipWidth;
	int						m_clipHeight;

	void				*	m_clipHandle;
	static PROP_V2			ms_propItems[];
};

#endif // CKLBUIClip_h
