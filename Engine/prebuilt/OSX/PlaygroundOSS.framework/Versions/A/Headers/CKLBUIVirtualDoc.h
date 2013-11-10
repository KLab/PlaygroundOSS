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
#ifndef CKLBUIVirtualDoc_h
#define CKLBUIVirtualDoc_h

#include "CKLBUITask.h"
#include "CKLBNodeVirtualDocument.h"
#include "CKLBModalStack.h"

/*!
* \class CKLBUIVirtualDoc
* \brief Virtual Document Task Class
* 
* CKLBUIVirtualDoc creates and allows to manage a Virtual Document.
* A Virtual Document allows to manage the rendering of an area of the screen.
* Several items can be associated to it, such as text, lines or images.
*/
class CKLBUIVirtualDoc : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIVirtualDoc>;
private:
	CKLBUIVirtualDoc();
	virtual ~CKLBUIVirtualDoc();
public:
	static CKLBUIVirtualDoc * create(CKLBUITask * pParent, CKLBNode * pNode,
									 u32 order, float x, float y,
									 u32 doc_width, u32 doc_height, 
									 u32 view_width, u32 view_height,
									 u32 max_command_nums, bool vertical,
									 const char * callback = NULL);
	bool initUI     (CLuaState& lua);
	u32  getClassID ();
	int  commandUI  (CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	void checkDocumentSize();

	inline void clear(u32 color) 
	{ m_pDocNode->clear(color); }

	inline void setFont(u32 idx, const char* fontName, u32 fontSize) 
	{ m_pDocNode->setFont(idx, fontName, fontSize); }

	inline void setViewPortPos(s32 x, s32 y) 
	{ m_viewPosX = x; m_viewPosY = y; m_pDocNode->setViewPortPos(x, y); }

	inline void drawLine(s32 x0, s32 y0, s32 x1, s32 y1, u32 color)
	{ m_pDocNode->drawLine(x0, y0, x1, y1, color); }

	inline void drawImage(s32 x0, s32 y0, const char* image, u32 alpha) 
	{	CKLBImageAsset * pImage = loadImage(image);
		m_pDocNode->drawImage(x0, y0, pImage, alpha);	}

	inline void fillRect(s32 x0, s32 y0, u32 width, u32 height, u32 color, bool fill)
	{	m_pDocNode->fillRect(x0, y0, width, height, color,fill); }

	inline void drawText(s32 x0, s32 y0, const char* str, u32 color, u32 fontidx)
	{	m_pDocNode->drawText(x0, y0, str, color, fontidx, (u8)m_align, (s16)m_align_width); REFRESH_B; }

	inline void startDocument()			{ m_pDocNode->emptyDocument(); m_pDocNode->lockDocument();	}
	inline void endDocument  ()			{ m_pDocNode->unlockDocument();	}

	inline u32  getCommandMax()			{ return m_commandMax; }
	inline void setCommandMax(u32 command) {
		if (command != m_commandMax) {
			m_commandMax = command;
			REFRESH_A;
		}
	}

	inline u32  getDocHeight()			{ return m_height; }
	inline void setDocHeight(u32 height) {
		if (height != m_height) {
			m_height = height;
			REFRESH_B;
		}
	}

	inline u32  getDocWidth()			{ return m_width;	}
	inline void setDocWidth(u32 width) {
		if (width != m_width) {
			m_width = width;
			REFRESH_B;
		}
	}

	inline bool getVertical()			{ return m_vertical; }
	inline void setVertical(bool vertical) {
		if (vertical != m_vertical) {
			m_vertical = vertical;
			REFRESH_B;
		}
	}

	inline s32  getViewHeight()				{ return m_viewHeight; }
	inline void setViewHeight(s32 height)	{
		if (height != m_viewHeight) {
			m_viewHeight = height;
			REFRESH_C;
		}
	}

	inline s32  getViewWidth()			{ return m_viewWidth; }
	inline void setViewWidth(s32 width) {
		if (width != m_viewWidth) {
			m_viewWidth = width;
			REFRESH_C;
		}
	}

	inline u32	getOrder	()			{	return m_order; }
	inline void setOrder	(u32 order)	{
		if (m_order != order) {
			m_order = order;
			m_pDocNode->setPriority(order);
		}
	}

	inline const char*  getCallBack()				        { return m_callBack;			}
	inline void         setCallBack(const char* callBack)	{ REFRESH_E; setStrC(m_callBack, callBack);}

	inline void         setAlign(u8 align, int alignWidth)  { m_align = align; m_align_width = alignWidth; }

private:
	void forceRefresh();

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
				u32 order, float x, float y,
				u32 doc_width, u32 doc_height, 
				u32 view_width, u32 view_height,
				u32 max_command_nums, bool vertical, const char * callback);

	bool initCore(
				u32 order, float x, float y,
				u32 doc_width, u32 doc_height, 
				u32 view_width, u32 view_height,
				u32 max_command_nums, bool vertical, const char * callback);

	CKLBImageAsset * loadImage(const char * image);
	void destroyImages();
	void touchPadEvent();

	u32		    m_order;
	u32		    m_commandMax;
	u32		    m_height;
	u32		    m_width;
	u32		    m_viewWidth;
	u32		    m_viewHeight;
	u32		    m_counter;
	const char*	m_callBack;
	s32         m_viewPosX;
	s32         m_viewPosY;
	u8			m_format;

	bool	    m_vertical;
	bool	    m_forceRefreshMode;

	struct VDIMG {

		VDIMG			*	prev;
		VDIMG			*	next;

		CKLBImageAsset	*	pImage;
		u32					handle;
	};
	VDIMG					*	m_imgBegin;
	VDIMG					*	m_imgEnd;

	int							m_dragID;
	int							m_dragX;
	int							m_dragY;

	u8							m_align;
	int							m_align_width;

	CKLBNodeVirtualDocument	*	m_pDocNode;
	CKLBModalStack				m_modalStack;	// モーダルスタックパッケージ

	static PROP_V2				ms_propItems[];

};


#endif // CKLBUIVirtualDoc_h
