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
#ifndef CKLBUIDebugItem_h
#define CKLBUIDebugItem_h

#include "CKLBUITask.h"
#include "CKLBNodeVirtualDocument.h"

/*!
* \class CKLBUIDebugItem
* \brief Debug Item Task Class
* 
* CKLBUIDebugItem allows to display debug purpose items in the Game.
* A few properties (such as text, color, etc.) can be modified in runtime 
* and used for debugging.
*/
class CKLBUIDebugItem : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIDebugItem>;
private:
	CKLBUIDebugItem();
	virtual ~CKLBUIDebugItem();

	bool init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text, const char* callback,u32 id);
	bool initCore(u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text, const char* callback,u32 id);
public:
	static CKLBUIDebugItem* create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text, const char* callback,u32 id);
	u32 getClassID  ();
	bool initUI     (CLuaState& lua);
	void execute    (u32 deltaT);
	void dieUI      ();

	inline virtual void setOrder    (u32 order)		    { m_order = order; m_update = true; }
	inline virtual u32 getOrder     ()				    { return m_order;	}

	inline void         setAlpha    (u32 alpha)		    { m_alpha = alpha; m_update = true;	}
	inline u32          getAlpha    ()				    { return m_alpha;	}

	inline void         setU24Color (u32 color)	        { m_color = color; m_update = true;	}
	inline u32          getU24Color ()			        { return m_color;	}

	inline void         setColor    (u32 color)		    { m_alpha = color >> 24; m_color = color & 0xFFFFFF; m_update = true; }
	inline u32          getColor    ()				    { return (m_alpha << 24) | m_color; }

	inline void         setFont     (const char* font)	{ setStrC(m_font, font); m_update = true;	}
	inline const char*  getFont     ()			        { return m_font; }

	inline void         setSize     (u32 size)		    { m_size = size; m_update = true;	}
	inline u32          getSize     ()				    { return m_size; }

	inline void         setText     (const char* text)	{ setStrC(m_text, text); m_update = true;	}
	inline const char*  getText     ()			        { return m_text; }

private:
	u32							m_order;
	u8							m_format;
	u8							m_alpha;
	u32							m_color;
	const char*					m_font;
	const char*					m_text;
	u32							m_size;

	bool setup_node();
	// 現在は VDocで仮実装しておく。
	CKLBNodeVirtualDocument	*	m_pLabel;
	bool						m_update;

	STextInfo					m_txinfo;
	const char				*	m_callback;
	int							m_ID;

	int							m_padId;

	static	PROP_V2				ms_propItems[];
};

#endif // CKLBUIDebugItem_h
