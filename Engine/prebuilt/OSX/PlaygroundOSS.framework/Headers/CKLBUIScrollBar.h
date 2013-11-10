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
#ifndef CKLBUIScrollBar_h
#define CKLBUIScrollBar_h
#include "CKLBUITask.h"
#include "CKLBModalStack.h"
#include "CKLBScrollBarIF.h"
#include "IMgrEntry.h"

/*!
* \class CKLBUIScrollBar
* \brief Scroll Bar Task Class
* 
* CKLBUIScrollBar allows to create and manage a Scroll Bar.
* The Scroll Bar action into the Game can be defined through a callback.
*/
class CKLBUIScrollBar : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIScrollBar>;
private:
	CKLBUIScrollBar();
	virtual ~CKLBUIScrollBar();
public:
	// プロパティのインデックス
	enum PROP_ID{
		P_WIDTH,
		P_HEIGHT,
		P_ORDER,
		P_VERT,

		P_IMAGE,
		P_MIN,
		P_MAX,
		P_POS,

		P_SLIDER_SIZE,
		P_SLIDER_MIN_SIZE,
	
		P_CALLBACK,
		P_TOUCH_ACTIVE,
		P_ALPHA_NORMAL,
		P_ALPHA_SELECT,
		P_COLOR_NORMAL,
		P_COLOR_SELECT,
	};

	static CKLBUIScrollBar * create(
		CKLBUITask * pParent, CKLBNode * pNode,
		u32 order, float x, float y, float width, float height,
		s32 minValue, s32 maxValue, s32 pos,
		const char * image,
		s32 slider_size, s32 min_slider_size, 
		const char * callback,
		u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hide_mode = false);

	bool initUI(CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI();
	
	u32 getClassID();

	inline s32	getMin          ()          { return m_min;             }
	inline s32	getMax          ()          { return m_max;             }
	inline s32	getPos          ()          { return m_pos;	            }
	inline s32	getSliderSize   ()          { return m_sliderSize;      }
	inline s32	getSliderSizeMin()          { return m_sliderSizeMin;   }
	inline bool getTouchActive  ()          { return m_bTouchActive;    }
	inline u32	getColorMode    (u32 mode)  { return m_scrBar.getColorMode(mode); }
	inline u32	getOrder        ()		    { return m_order;           }
	inline s32	getWidth        ()		    { return m_width;           }
	inline s32	getHeight       ()		    { return m_height;          }
	inline bool getVertical     ()		    { return m_vert;            }
	inline u32	getAlphaNormal  ()		    { return m_alphaNormal;     }
	inline u32	getAlphaSelect  ()		    { return m_alphaSelect;     }
	inline u32	getColorNormal  ()		    { return m_colorNormal;     }
	inline u32	getColorSelect  ()		    { return m_colorSelect;     }
	inline const char* getImage ()		    { return m_image;           }
	inline const char* getCallBack()	    { return m_callback;        }
	inline u32	getMode         ()		    { return m_mode;            }

	void setMin	(s32 value);
	void setMax	(s32 value);
	void setPos	(s32 value);

	inline void setSliderSize	(s32 value)				{ m_scrBar.setSliderSize(value);	m_sliderSize = m_scrBar.getSliderSize();		}
	inline void setSliderSizeMin(s32 value)				{ m_scrBar.setSliderSizeMin(value); m_sliderSizeMin = m_scrBar.getSliderSizeMin();	}
	inline void setTouchActive	(bool active)			{ m_active = active; m_scrBar.setTouchActive(active);	}
	inline void setMode			(u32 mode)				{ m_mode = mode;	 m_scrBar.setMode(mode);			}
	inline void setVertical		(bool vertical)			{ m_vert = vertical; m_scrBar.setVertical(vertical);	}
	inline void setAlphaNormal	(u32 alpha)				{ m_alphaNormal = (u8)alpha; m_scrBar.setColorMode(0,(m_alphaNormal<<24) | m_colorNormal);	}
	inline void setAlphaSelect	(u32 alpha)				{ m_alphaSelect = (u8)alpha; m_scrBar.setColorMode(1,(m_alphaSelect<<24) | m_colorSelect);	}
	inline void setColorNormal	(u32 colorRGB)			{ m_colorNormal = colorRGB;  m_scrBar.setColorMode(0,(m_alphaNormal<<24) | m_colorNormal);	}
	inline void setColorSelect	(u32 colorRGB)			{ m_colorSelect = colorRGB;  m_scrBar.setColorMode(1,(m_alphaSelect<<24) | m_colorSelect);	}
	inline void setWidth		(s32 width)				{ m_width  = width;	 m_scrBar.setWidth(width);		}
	inline void setHeight		(s32 height)			{ m_height = height; m_scrBar.setHeight(height);	}
	inline void setOrder		(u32 order)				{ m_order  = order;	 m_scrBar.setOrder(order);		}
	inline bool	selectScrMgr	(const char* name, int len, int* args) {
		CKLBScrollMgr * pMgr = IMgrEntry::getMgrByArray(name, len, args); 
		if(pMgr) m_scrBar.setScrollMgr(pMgr);
		return ((pMgr != NULL) ? true:false);
	}

	void setColorMode			(u32 mode, u32 color);
protected:

	s32		    m_min;
	s32		    m_max;
	s32		    m_pos;
	s32		    m_sliderSize;
	s32		    m_sliderSizeMin;
	bool	    m_bTouchActive;
	s32		    m_width;
	s32		    m_height;	
	u32		    m_order;
	bool	    m_vert;

	const char*	m_image;

	const char* m_callback;

	u32		    m_mode;
	u32		    m_colorNormal;
	u32		    m_colorSelect;
	bool	    m_active;
	u8		    m_alphaNormal;
	u8		    m_alphaSelect;

private:
	void recompute	();

	bool init(
		CKLBUITask * pParent, CKLBNode * pNode,
		u32 order, float x, float y, float width, float height,
		s32 minValue, s32 maxValue, s32 pos,
		const char * image,
		s32 slider_size, s32 min_slider_size, 
		const char * callback,
		u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hide_mode);

	bool initCore(
		u32 order, float x, float y, float width, float height,
		s32 minValue, s32 maxValue, s32 pos,
		const char * image,
		s32 slider_size, s32 min_slider_size, 
		const char * callback,
		u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hide_mode);


	int					m_minPos;
	CKLBModalStack		m_modalStack;	// モーダルスタック
	CKLBScrollBarIF		m_scrBar;		// ScrollBarインタフェース

	static	PROP_V2		ms_propItems[];
};


#endif // CKLBUIScrollBar_h
