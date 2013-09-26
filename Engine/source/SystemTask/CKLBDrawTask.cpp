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
#include "CKLBDrawTask.h"
#include "CKLBObject.h"
#include "KLBPlatformMetrics.h"
;
CKLBDrawResource::CKLBDrawResource()
:m_allowLog		(false)
,m_frameCount	(0)
,m_hasBorder	(true)
{}

CKLBDrawResource::~CKLBDrawResource() {}

CKLBDrawResource&
CKLBDrawResource::getInstance() {
	static CKLBDrawResource instance;
	return instance;
}

void
CKLBDrawResource::setBorderless(bool hasNoBorder) {
	m_hasBorder = !hasNoBorder;
}

bool
CKLBDrawResource::setLogicalResolution(int width, int height, float * other_matrix)
{
	m_width = width;
	m_height = height;
	/*
	GLfloat matrix[16] = {
		(2.0f/m_width),	0.0f,					0.0f,	0.0f,
		0.0f,			(-2.0f/m_height),			0.0f,	0.0f,
		0.0f,			0.0f,					0.0f,	0.0f,
		-1.0f,			1.0f,					1.0f,	1.0f, };
	*/

	float scaleX = (float)m_phisical_width  / (float)m_width;
	float scaleY = (float)m_phisical_height / (float)m_height;
	m_scaleX = scaleX;
	m_scaleY = scaleY;

	m_scale = (scaleX < scaleY) ? scaleX : scaleY;

	m_vp_width	= m_width * m_scale;
	m_vp_height = m_height * m_scale;

	// 画面内の原点位置 m_ox, m_oy を計算
	m_ox = (m_phisical_width  - m_vp_width ) / 2;
	m_oy = (m_phisical_height - m_vp_height) / 2;

	// Select if 0,0 in coordinate is screen physical 0,0
	float glTX		= m_hasBorder ? -1.0f				: (-1.0f) + ((m_phisical_width  - (m_width  * m_scale)) / (float)m_phisical_width );
	float glTY		= m_hasBorder ? +1.0f				: (+1.0f) - ((m_phisical_height - (m_height * m_scale)) / (float)m_phisical_height);

	// Viewport pixel count width/height same as logical size ?
	// Yes : has border
	// No  : is borderless
	float glScaleX	= m_hasBorder ? (2.0/m_width)		: (( 2.0f/m_width )*m_scale) / scaleX;
	float glScaleY	= m_hasBorder ? (-2.0f/m_height)	: ((-2.0f/m_height)*m_scale) / scaleY;

	GLfloat matrix[16] = {
		glScaleX,	0.0f,		0.0f,	0.0f,
		0.0f,		glScaleY,	0.0f,	0.0f,
		0.0f,		0.0f,		1.0f,	0.0f,
		glTX,		glTY,		0.0f,	1.0f, 
	};
		
	float * proj_matrix = (other_matrix) ? other_matrix : matrix;
	bool bResult = CKLBOGLWrapper::getInstance().init(proj_matrix);
	if(!bResult) return bResult;

	// Perform centering and scaling at GL matrix level.
	if (m_hasBorder) {
		dglViewport(m_ox, m_oy, m_vp_width, m_vp_height);
	} else {
		dglViewport(0, 0, m_phisical_width, m_phisical_height);
	}

	dglClearColor(1.0f, 0.7f, 0.2039f, 1.0f);
	dglDisable( GL_CULL_FACE );

	return bResult;
}

bool
CKLBDrawResource::initResource(bool /*bLandscape*/, int width, int height)
{
	bool bResult = false;

	// 現時点では、物理解像度と論理解像度は同じ
	m_phisical_width = width;
	m_phisical_height = height;

	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
	if (pRdrMgr.setup(65000, 65000)) {

		// 物理解像度と同じ論理解像度でGLを初期化する。プロジェクションマトリクスはデフォルト
		if(setLogicalResolution(width, height)) {
			//
			// 3. Create Root Node
			//
			m_gpRootNode = KLBNEW(CKLBNode);
			if (m_gpRootNode) {
				m_gpRootNode->asRoot();
				m_gpRootNode->setScale(1.0f,1.0f);
				bResult = true;
			}
		}
	}

	return bResult;
}

bool
CKLBDrawResource::setClearColor(float r, float g, float b, float a)
{
	dglClearColor(r, g, b, a);
	return true;
}

void
CKLBDrawResource::freeResource()
{
	if (m_gpRootNode) {
		KLBDELETE(m_gpRootNode); m_gpRootNode = NULL;
	}
}

void
CKLBDrawResource::changeProjectionMatrix(float * matrix, int width, int height)
{
	setLogicalResolution(width, height, matrix);
}

void
CKLBDrawResource::ResetViewport(void)
{
	if (m_hasBorder) {
		dglViewport(m_ox, m_oy, m_vp_width, m_vp_height);
	} else {
		dglViewport(0, 0, m_phisical_width, m_phisical_height);
	}
}

bool
CKLBDrawResource::allowLog() {
	return m_allowLog;
}

void
CKLBDrawResource::setLog(bool activate) {
	m_allowLog = activate;
}

u32 CKLBDrawResource::incrementFrame() {
	return m_frameCount++;
}


CKLBDrawTask::CKLBDrawTask() : CKLBTask() {}
CKLBDrawTask::~CKLBDrawTask() {}

CKLBDrawTask *
CKLBDrawTask::create(bool rotate, int width, int height)
{
	CKLBDrawTask * pTask = KLBNEW(CKLBDrawTask);
	if(!pTask) return NULL;
	if(!pTask->init(rotate, width, height)) {
		KLBDELETE(pTask);
		return NULL;
	}
#ifdef DEBUG_PERFORMANCE
	pTask->m_recompute->init(pTask);
	pTask->m_draw->init(pTask);
#endif
	return pTask;
}

bool
CKLBDrawTask::onPause(bool /*bPause*/)
{
	// このタスクはpauseされてはならない
	return false;
}

#include "CKLBTexturePacker.h" 

void
CKLBDrawTask::execute(u32 deltaT)
{
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();

	// clear.
	dglDisable(GL_SCISSOR_TEST);
	// For TEST glClearColor(1.0f, 0.7f, 0.2039f, 0.0f);
	dglClear(GL_COLOR_BUFFER_BIT);

	s64 updateAnim		= 0;
	s64 updateTree		= 0;
	s64 renderTime		= 0;
	s64 endrenderTime	= 0;
	CKLBDrawResource& drawRes = CKLBDrawResource::getInstance();
	bool gLogFrameTime = drawRes.allowLog();
	int  gFrameCounter = CKLBDrawResource::getInstance().incrementFrame();

	if (gLogFrameTime) {
		updateAnim = CPFInterface::getInstance().platform().nanotime();
	}

	TexturePacker::getInstance().refreshTextures();

	// 5. Execution animation list (Spline, SWF movies)
	//
	if (!CKLBTaskMgr::getInstance().getFreeze()) {
		MEASURE_THREAD_CPU_BEGIN(TASKTYPE_DRAW_ANIMATION);
		draw.performAnimationUpdate(deltaT);
		MEASURE_THREAD_CPU_END(TASKTYPE_DRAW_ANIMATION);
	}

	if (gLogFrameTime) {
		updateTree = CPFInterface::getInstance().platform().nanotime();
	}
#ifndef DEBUG_PERFORMANCE
	// パフォーマンステストのため、処理を分割
	//
	// 6. Tree update
	//
	draw.recompute();

	if (gLogFrameTime) {
		renderTime = CPFInterface::getInstance().platform().nanotime();
	}
	//
	// 7. Render Draw
	//
	draw.draw();

	if (gLogFrameTime) {
		s64 startFrame = CKLBTaskMgr::getInstance().getStartTime();
		s64 scriptTime = CKLBTaskMgr::getInstance().getScriptTime();
		endrenderTime = CPFInterface::getInstance().platform().nanotime();
		DEBUG_PRINT("=== Frame[%8i] Anim : %4.2f mS, Tree : %4.2f mS, Render : %4.2f mS, Total : %4.2f ms, Script : %4.2f", 
			gFrameCounter,
			(((updateTree - updateAnim) / 1000) / 1000.0f),
			(((renderTime - updateTree) / 1000) / 1000.0f),
			(((endrenderTime - renderTime) / 1000) / 1000.0f),
			(((endrenderTime - startFrame) / 1000) / 1000.0f),
			((scriptTime / 1000) / 1000.0f)
		);
	}

	//
	// 9. Rendering close frame.
	//
	CKLBOGLWrapper&		pOGLMgr			= CKLBOGLWrapper::getInstance();
	pOGLMgr.endFrame();
#endif // DEBUG_PERFORMANCE
}

void
CKLBDrawTask::die()
{
	CKLBDrawResource::getInstance().freeResource();
}

u32
CKLBDrawTask::getClassID()
{
	return CLS_KLBTASKDRAW;
}


bool
CKLBDrawTask::init(bool rotate, int width, int height)
{
	bool bResult = CKLBDrawResource::getInstance().initResource(rotate, width, height);

    if(!bResult) return false;
#ifdef DEBUG_PERFORMANCE
	m_recompute = KLBNEW(CKLBDrawTask_recompute);
	m_draw      = KLBNEW(CKLBDrawTask_draw);
#endif
	return regist(NULL, P_DRAW);
}


#ifdef DEBUG_PERFORMANCE
CKLBDrawTask_recompute::CKLBDrawTask_recompute() : CKLBTask() { 
}
CKLBDrawTask_recompute::~CKLBDrawTask_recompute() {}

bool
CKLBDrawTask_recompute::init(CKLBDrawTask * pParent)
{
	return regist(pParent, P_DRAW);
}


void
CKLBDrawTask_recompute::execute(u32 deltaT)
{
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	//
	// 6. Tree update
	//
	CKLBNode::s_matrixRecomputeCount = 0;
	CKLBNode::s_vertexRecomputeCount = 0;
	CKLBNode::s_colorRecomputeCount  = 0;

	draw.recompute();
}

void
CKLBDrawTask_recompute::die()
{
}

CKLBDrawTask_draw::CKLBDrawTask_draw() : CKLBTask() {
}
CKLBDrawTask_draw::~CKLBDrawTask_draw() {}

bool
CKLBDrawTask_draw::init(CKLBDrawTask * pParent)
{
	return regist(pParent, P_DRAW);
}

void
CKLBDrawTask_draw::execute(u32 deltaT)
{
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	//
	// 7. Render Draw
	//
	draw.draw();

	//
	// 9. Rendering close frame.
	//
	CKLBOGLWrapper&		pOGLMgr			= CKLBOGLWrapper::getInstance();
	pOGLMgr.endFrame();
}

void
CKLBDrawTask_draw::die()
{
}

#endif // DEBUG_PERFORMANCE
