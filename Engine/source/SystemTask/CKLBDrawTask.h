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
#ifndef CKLBDrawTask_h
#define CKLBDrawTask_h

#include "CKLBTask.h"
#include "CKLBRendering.h"
#include "CKLBNode.h"


class CKLBDrawResource
{
private:
	CKLBDrawResource();
	virtual ~CKLBDrawResource();

public:
	static CKLBDrawResource& getInstance();

	inline const int width      () const { return m_width;      }
	inline const int height     () const { return m_height;     }

	inline const int vp_width   () const { return m_vp_width;   }
	inline const int vp_height  () const { return m_vp_height;  }

	inline const int ox         () const { return m_ox;         }
	inline const int oy         () const { return m_oy;         }

	bool initResource(bool rotation, int width, int height);
	void freeResource();

	void setBorderless(bool hasNoBorder);

	inline
	bool hasBorder() { return m_hasBorder; }
	bool setLogicalResolution(int width, int height, float * other_matrix = 0);

	inline void convPointing(int x, int y, int& cx, int& cy) {
		cx = (int)((x - m_ox) / m_scale);
		cy = (int)((y - m_oy) / m_scale);
	}

	// 論理座標系上の長さを物理座標系上の長さに変換する
	inline float toPhisical(float logical) { return logical * m_scale; }

	// 物理座標系上の長さを論理座標系上の長さに変換する
	inline float toLogical(float phisical) { return phisical / m_scale; }

	// 論理座標を物理デバイス座標に変換する(OSコントロールの位置変換等に使用)
	inline void toPhisicalPosition(int lx, int ly, int& px, int& py) {
		px = (int)(lx * m_scale) + m_ox;
		py = (int)(ly * m_scale) + m_oy;
	}
	// 論理座標系上のサイズを物理デバイス座標系上のサイズに変換する
	inline void toPhisicalSize(int lw, int lh, int& pw, int& ph) {
		pw = (int)(lw * m_scale);
		ph = (int)(lh * m_scale);
	}

    void changeProjectionMatrix(float * matrix, int width, int height);
    
	inline CKLBNode * getRoot() { return m_gpRootNode; }
    
	inline void performAnimationUpdate(u32 deltaT) {
		CKLBSystem::performAnimationUpdate(deltaT); 
	}

	inline void recompute() {
		m_gpRootNode->recompute();
	}

	inline void draw() {
		CKLBRenderingManager::getInstance().draw();
	}

	bool setClearColor(float r, float g, float b, float a);

    // ビューポートの再設定(Android版でバックグラウンドから復帰した時に使用)
    void ResetViewport(void);
    
	bool allowLog	();
	void setLog		(bool activate);

	u32 incrementFrame();

private:
	bool		m_hasBorder;
	bool		m_allowLog;
	u32			m_frameCount;
	int			m_phisical_width;
	int			m_phisical_height;
	int			m_width;
	int			m_height;
	int			m_ox;
	int			m_oy;
	int			m_vp_width;
	int			m_vp_height;
	float		m_scale;	// 論理解像度に対する物理画面の倍率
	float		m_scaleX;
	float		m_scaleY;
	CKLBNode*	m_gpRootNode;
};


#ifdef DEBUG_PERFORMANCE
class CKLBDrawTask_recompute;
class CKLBDrawTask_draw;
#endif


/*!
* \class CKLBDrawTask
* \brief Draw Task class.
* 
* CKLBDrawTask is in charge of drawing the game resources each frame.
* It is instancied only once and draws all the resources in one and only one draw call.
* This task is instancied when the game starts and dies when it stops.
*/
class CKLBDrawTask : public CKLBTask
{
private:
	CKLBDrawTask();
	virtual ~CKLBDrawTask();

	bool onPause(bool bPause);

public:
	static CKLBDrawTask * create(bool rotate, int width, int height);

	void execute    (u32 deltaT);

	void die        ();

	u32 getClassID  ();

private:
	bool init(bool rotate, int width, int height);

#ifdef DEBUG_PERFORMANCE
	CKLBDrawTask_recompute	*	m_recompute;
	CKLBDrawTask_draw		*	m_draw;
#endif
};

#ifdef DEBUG_PERFORMANCE

class CKLBDrawTask_recompute : public CKLBTask
{
	friend class CKLBDrawTask;
private:
	CKLBDrawTask_recompute();
	virtual ~CKLBDrawTask_recompute();
	bool init(CKLBDrawTask * pParent);
public:
	void execute(u32 deltaT);
	void die    ();
};

class CKLBDrawTask_draw : public CKLBTask
{
	friend class CKLBDrawTask;
private:
	CKLBDrawTask_draw();
	virtual ~CKLBDrawTask_draw();
	bool init(CKLBDrawTask * pParent);
public:
	void execute(u32 deltaT);
	void die    ();
};


#endif // DEBUG_PERFORMANCE

#endif // CKLBDrawTask_h
