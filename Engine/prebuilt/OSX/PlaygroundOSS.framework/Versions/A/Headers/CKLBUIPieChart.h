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
#ifndef CKLBUIPieChart_h
#define CKLBUIPieChart_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIPieChart
* \brief Pie Chart Task Class
* 
* CKLBUIPieChart allows to create dynamic Pie Charts.
*/
class CKLBUIPieChart : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIPieChart>;
private:
	CKLBUIPieChart();
	virtual ~CKLBUIPieChart();

public:
	u32 getClassID();

	static CKLBUIPieChart * create(CKLBUITask * pParent, CKLBNode * pNode,
		                           u32 order, float x, float y, float width, float height,
								   const char * asset, float start, float end,
								   int anim = 0, float initial = 0.0f);

	bool initUI(CLuaState& lua);

	int commandUI(CLuaState& lua, int argc, int cmd);

	inline void  setStart(float start) {
		if (start != m_start) {
			m_start = start;
			REFRESH_A;
		}
	}
	inline float getStart() { return m_start; }

	inline void  setEnd(float end) {
		if (end != m_end) {
			m_end = end;
			REFRESH_A;
		}
	}
	inline float getEnd()   { return m_end; }

	inline void setValue(float value) {
		if (value != m_value) {
			m_value = value;
			REFRESH_A;
		}
	}
	inline float getValue()	{ return m_value;	}

	inline s32 getAnim()    { return m_anim;	}

	inline 
	virtual u32 getOrder()	{ return m_order;	}

	bool changeAsset(const char* asset);

	void execute(u32 deltaT);
	void dieUI  ();

private:

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
              u32 order, float x, float y, float width, float height,
			  const char * asset, float start, float end, int anim = 0, float initial = 0.0f);

	bool initCore(u32 order,
				  float x, float y, float width, float height, 
				  const char * asset, float start, float end, int anim = 0, float initial = 0.0f);


	void setVertices(float value);
	void getPoint   (int idx, float n, float& x, float &y, float& u, float& v);


	// テクスチャ情報
	u32					m_texHandle;
	CKLBImageAsset	*	m_pImgAsset;
	s32					m_texWidth;
	s32					m_texHeight;

	// ダイナミックスプライト
	CKLBDynSprite	*	m_pDynSprite;
	CKLBNode		*	m_pNode;

	// アニメーション情報
	bool				m_bAnim;
	int					m_iTimeCnt;
	float				m_nowRate;
	float				m_prevRate;

	float				m_start;
	float				m_end;
	float				m_value;
	s32					m_anim;
	u32					m_order;


	// 頂点情報
	struct VERTMAP {
		float x, y;
		float u, v;
	};
	
	
	VERTMAP				    m_vertices[ 17 ];

	static const VERTMAP 	ms_vertMaster[];
	static const int 		ms_idxMaster[8][3];
	static PROP_V2			ms_propItems[];
};

#endif // CKLBUIPieChart_h
