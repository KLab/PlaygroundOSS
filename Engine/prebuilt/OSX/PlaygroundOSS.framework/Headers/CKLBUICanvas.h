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
#ifndef CKLBUICanvas_h
#define CKLBUICanvas_h

#include "CKLBUITask.h"
#include "CKLBCanvasSprite.h"

/*!
* \class CKLBUICanvas
* \brief Canvas Task Class
* 
* CKLBUICanvas regroups various images to draw Canvas
* The different assets must be in the same texture.
*/
class CKLBUICanvas : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUICanvas>;
private:
	CKLBUICanvas();
	virtual ~CKLBUICanvas();

public:
	u32 getClassID();

	static CKLBUICanvas * create(CKLBUITask * pParent, CKLBNode * pNode, u32 order, float x, float y, u32 vertexMax, u32 indexMax, const char * callback);
	
	bool init		    (CKLBUITask * pParent, CKLBNode * pNode, u32 order, float x, float y, u32 vertexMax, u32 indexMax, const char * callback);
	bool initCore	    (u32 order, float x, float y, u32 vertexMax, u32 indexMax, const char * callback);

	bool initUI		    (CLuaState& lua);
	int commandUI	    (CLuaState& lua, int argc, int cmd);

	bool addAsset		(const char* asset);
	void setTiledRect	(u32 width, u32 height, const char* asset, u32 alpha);
	void freeze			(bool freeze);
	void execute		(u32 deltaT);
	void dieUI			();

	
	inline virtual void setOrder    (u32 order) {
		if(order != m_order) {
			m_pCanvas->changeOrder(CKLBRenderingManager::getInstance(),order);
			m_order = order;
		}
	}

	inline virtual u32  getOrder    ()                      { return m_order;                   }

	inline u32          getIdxMax   ()						{ return m_maxAssetCount;           }

	inline void         setCallBack (const char* callback)	{ setStrC(m_callback, callback);	}
	inline const char*  getCallBack ()				        { return m_callback;		        }

	inline void         setFreeze   (bool val) {
		if (!val) {
			REFRESH_A;
		} else {
			RESET_A;
		}
		m_pCanvas->freeze(val);
	}

	inline void drawImage           (float x, float y, u32 idx, u32 color) {
		CKLBImageAsset* pAsset;
		if (idx >= m_assetCount) {
			pAsset = NULL;
		} else {
			pAsset = m_assets[idx];
		}

		m_pCanvas->drawImage(
			x,			// X 
			y,			// Y
			pAsset,		// Asset Index
			color
		);
		getNode()->markUpMatrix();
	}
	
	inline void drawImageScale      (float x, float y, float scale, u32 idx, u32 color) {
		CKLBImageAsset* pAsset;
		if (idx >= m_assetCount) {
			pAsset = NULL;
		} else {
			pAsset = m_assets[idx];
		}

		m_pCanvas->drawScale(
			x,y,scale,
			pAsset,		// Asset Index
			color
		);
		getNode()->markUpMatrix();
	}

	inline void fillRect            (float x, float y, float w, float h, u32 color) {
		m_pCanvas->fillRect(x,y,w,h,color);
		getNode()->markUpMatrix();
	}

	inline void startDynamicSection (u32 idx)	{	m_pCanvas->startDynamicSection(idx);	}
	inline void endDynamicSection   (u32 idx)	{	m_pCanvas->endDynamicSection(idx);		}
	
	inline void dynamicSectionTranslate(u32 idx, float deltaX, float deltaY) {
		m_pCanvas->dynamicSectionTranslate(idx, deltaX, deltaY);
		getNode()->markUpMatrix();
	}

	inline void dynamicSectionColor(u32 idx, u32 color) {
		m_pCanvas->dynamicSectionColor(idx, color);
		getNode()->markUpColor();
	}

private:
	CKLBCanvasSprite*	m_pCanvas;
	CKLBTextureAsset*	m_texture;
	CKLBImageAsset**	m_assets;
	u32					m_handle;
	u32					m_assetCount;
	u32					m_maxAssetCount;

	u32					m_order;
	const char*			m_callback;

	static	PROP_V2		ms_propItems[];

	void setTiledRect	(u32 width, u32 height, u32 idx, u32 alpha);
};

#endif // CKLBCanvas_h
