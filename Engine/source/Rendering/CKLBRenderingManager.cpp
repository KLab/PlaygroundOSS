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
#include "CKLBRendering.h"
#include "mem.h"
#include "CKLBDrawTask.h"
#include "CKLBSprite3D.h"

u32	gUseOffsetSystem = 1;

// Prototypes
u32  searchID(u8* stream, const char* name);
u32  getColor(u32 code);
bool crossLine(float x1, float y1, float x2, float y2, float px, float py, float cx, float cy);

void useOffsetForImages(bool use) {
	gUseOffsetSystem = use ? 1 : 0;
}

//
// #define USE_PREMULALPHA

CKLBRenderingManager::CKLBRenderingManager():
	m_pListStart			(NULL),
	m_pAllocatedSpriteList	(NULL),
	m_pIdxBuffer			(NULL),
	m_pVerBuffer			(NULL),
	m_pColBuffer			(NULL),
	m_pRenderWatchDog		(NULL),
	m_pRenderLastModify		(NULL),
	m_pVShader				(NULL),
	m_pPShader				(NULL),
	m_pShaderSet			(NULL),
	m_pShaderInstance		(NULL),
	m_pCurrShader			(NULL),
	m_renderMode			(0),
	m_bRenderOverDraw		(false),
	m_coloring				(false)
{
	setRenderMode(m_renderMode);
}

CKLBRenderingManager::~CKLBRenderingManager() {
	_release();
}

void CKLBRenderingManager::_release() {
	/* NEVER DESTROY THE RENDER QUEUE BUT
	   DESTROY THE LIST OF ALLOCATED RENDER ITEM !!!! */
	/*	### NO ###
	CKLBRenderCommand* pCommand = m_pAllocatedSpriteList;
	while (pCommand) {
		CKLBRenderCommand* pNext = pCommand->m_pNext;
		if (pNext != m_pRenderWatchDog) {
			// KLBDELETE(pCommand);
		}
		pCommand = pNext;
	}*/
	// ### YES ###
	CKLBRenderCommand* pRenderQueue = m_pListStart;
	while (pRenderQueue != m_pRenderWatchDog) {
		CKLBRenderCommand* pRenderQueueNext = pRenderQueue->m_pNext;
		KLBDELETE(pRenderQueue);
		pRenderQueue = pRenderQueueNext;
	}

	m_pListStart = m_pRenderWatchDog;

	CKLBOGLWrapper&		pOGLMgr			= CKLBOGLWrapper::getInstance();
	if (m_pIdxBuffer) {
		pOGLMgr.releaseIndexBuffer(m_pIdxBuffer);
		m_pIdxBuffer = NULL;
	}

	if (m_pVerBuffer) {
		pOGLMgr.releaseVertexBuffer(m_pVerBuffer);
		m_pVerBuffer = NULL;
	}

	if (m_pColBuffer) {
		pOGLMgr.releaseVertexBuffer(m_pColBuffer);
		m_pColBuffer = NULL;
	}

	if (m_pShaderInstance) {
		m_pShaderSet->releaseInstance(m_pShaderInstance);
		m_pShaderInstance = NULL;
	}

	if (m_pShaderSet) {
		pOGLMgr.releaseShaderSet(m_pShaderSet);
		m_pShaderSet = NULL;
	}

	destroyShaderSystem();

	/* Destroyed by ref counter from ShaderSet
	if (m_pVShader) {
		pOGLMgr.releaseShader(m_pVShader);
		m_pVShader = NULL;
	}

	if (m_pPShader) {
		pOGLMgr.releaseShader(m_pPShader);
		m_pPShader = NULL;
	}*/
}

static const SVertexEntry cteListVertex[3] = {
	//	StreamID	Offset	VBO?	Type
#if (VERTEX_SIZE == 4) 
	{		1,		0,		false,	VEC2	 | VERTEX},	// Coordinate.
#else
	{		1,		0,		false,	VEC3	 | VERTEX},	// Coordinate.
#endif
	{		2,		0,		false,	VEC2	 | TEXTURE},	// Texture UV.
	{ /*NA*/0,/*NA*/0,/*NA*/false,	END_LIST}	// Mark end of list.
};


static const SVertexEntry cteListColor[2] = {
	//	StreamID	Offset	VBO?	Type
	{		3,		0,		false,	VEC4BYTE | COLOR},
	{ /*NA*/0,/*NA*/0,/*NA*/false,	END_LIST}	// Mark end of list.
};

bool CKLBRenderingManager::setup(u16 maxVertexCount, u16 maxIndexCount) {
	// -------------------------------------------------------------------
	//   OpenGL Initialize.
	// -------------------------------------------------------------------

	//--------------------------------------------------------------------
	// Setup Blending between Tex0 and Tex1 in multi texture mode
	//

	// Disable Color0 * Tex0
	//dglActiveTexture(GL_TEXTURE0);
	//dglTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	dglActiveTexture(GL_TEXTURE1);
	dglTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//--------------------------------------------------------------------

	CKLBOGLWrapper&		pOGLMgr
					= CKLBOGLWrapper::getInstance();
	m_pIdxBuffer	= pOGLMgr.createIndexBuffer(maxIndexCount, false);
	m_pVerBuffer	= pOGLMgr.createVertexBuffer(maxVertexCount, &cteListVertex[0]);
	m_pColBuffer	= pOGLMgr.createVertexBuffer(maxVertexCount, &cteListColor[0]);

	// TODO RP : Hardcoded shader, vertex format.
	//   Render state,
	// -------------------------------------- SHADER
	const static SParam paramsVert[] = {
		// Name				Uniform?	StreamID	Data Type
		//								or
		//								UniformID
#if (VERTEX_SIZE == 4) 
		{	"pos_attr"		,false		,1			,VEC2	| VERTEX },	// Coordinate.
#else
		{	"pos_attr"		,false		,1			,VEC3	| VERTEX },	// Coordinate.
#endif
		{	"uv_attr"		,false		,2			,VEC2	| TEXTURE},	// UV.
		{   "col_attr"		,false		,3			,VEC4BYTE | COLOR},
		{	""				,false		,0			,END_LIST}	// Mark end of list.
	};

	const static SParam paramsShader[] = {
		// Name				Uniform?	StreamID	Data Type
		//								or
		//								UniformID
		{	"texture"		,true		,1			,TEX2D    | TEXTURE },
//		{	"power"			,true		,2			,VEC1F				},
//		{	"table"			,true		,1			,TEX2D    | TEXTURE },
		{	""				,false		,0			,END_LIST}		// Mark end of list.
	};

	// Create shader vertex & pixel
	SRenderState::RENDER_MODE mode = SRenderState::TEXTURE_MUL_COLOR;
	m_pVShader		= pOGLMgr.createShader(mode, CKLBOGLWrapper::VERTEX_SHADER, paramsVert);
	m_pPShader		= pOGLMgr.createShader(mode, CKLBOGLWrapper::PIXEL_SHADER, paramsShader);

	// Map the shader together.
	m_pShaderSet	= pOGLMgr.createShaderSet(m_pVShader, m_pPShader);
	// Create instance of shader for param
	m_pShaderInstance = m_pShaderSet->createInstance();
	// ----------------------------------------------

/*
	float val = 0.45f;
	m_pShaderInstance->setUniformF(CShaderInstance::PIXEL_SHADER, 2, &val);
*/
	// -------------------------------------------------------------------
	//   Manager Initialize.
	// -------------------------------------------------------------------

	m_pRenderWatchDog				= &m_innerWatchDog;
	m_pListStart					= m_pRenderWatchDog;
	m_pRenderWatchDog->m_uiOrder	= 0xFFFFFFFF;	// Always at the end.
	m_pRenderLastModify				= m_pRenderWatchDog;

#ifdef USE_PREMULALPHA
	state.setBlend(SRenderState::ADDITIVE_ALPHA);
#else
	state.setBlend(SRenderState::ALPHA);
#endif
	// state.setTextMode(false); UNDEFINED BY DEFAULT.

	// Dest
	/*
		D_ONE						= GL_ONE,
		D_SRC_COLOR					= GL_SRC_COLOR,
		D_ONE_MINUS_SRC_COLOR		= GL_ONE_MINUS_SRC_COLOR,
		D_SRC_ALPHA					= GL_SRC_ALPHA,
		D_ONE_MINUS_SRC_ALPHA		= GL_ONE_MINUS_SRC_ALPHA,
		D_DST_ALPHA					= GL_DST_ALPHA,
		D_ONE_MINUS_DST_ALPHA		= GL_ONE_MINUS_DST_ALPHA
	 */

	// Src
	/*enum BLEND_SRC {
		S_ZERO						= GL_ZERO,
		S_ONE						= GL_ONE,
		S_DST_COLOR					= GL_DST_COLOR,
		S_ONE_MINUS_DST_COLOR		= GL_ONE_MINUS_DST_COLOR,
		S_SRC_ALPHA_SATURATE		= GL_SRC_ALPHA_SATURATE,
		S_SRC_ALPHA					= GL_SRC_ALPHA,
		S_ONE_MINUS_SRC_ALPHA		= GL_ONE_MINUS_SRC_ALPHA,
		S_DST_ALPHA					= GL_DST_ALPHA,
		S_ONE_MINUS_DST_ALPHA		= GL_ONE_MINUS_DST_ALPHA
	*/
//	textState.setBlendAdvance(SRenderState::S_ONE, SRenderState::D_ONE_MINUS_SRC_ALPHA,SRenderState::ADD /*Add is mandatory in ES2.0*/);
	textState.setTextMode(true);
	//	setBlendAdvance(SRenderState::S_ONE, SRenderState::D_ONE_MINUS_SRC_COLOR,SRenderState::ADD /*Add is mandatory in ES2.0*/);

	initShaderSystem();

	// ===========================================================
	//
	// Test Code : Shader that modify the color strength (grey-scale <--> saturation)
	//
	/*
	// Create Parameter
	this->stackParameter("power", VEC1F, MEDP);
	u32 def = this->createShaderDefinition(
		"varying lowp vec4 col_var;\n"			// Cte
		"varying mediump vec2 uv_var;\n"		// Cte
		"uniform lowp sampler2D texture;\n"		// Cte
		"uniform mediump float power;\n"		// Param
		"const lowp vec3 coef = vec3(0.2125, 0.7154, 0.0721);"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture
		"	gl_FragColor        = mix(vec4(vec3(dot(color.rgb, coef)),color.a),color,power);\n"
//		"   gl_FragColor        = texture2D(texture,floor(uv_var*power)/power) * col_var;\n" // Mosaic
		"}"
	);

	// Create Shader Instance
	void* shaderI = this->instanceShader(def, 2000, 0x40000000);

	// Setup Shader Parameter
	float valuef = 300.0f;
	this->setShaderParamF(shaderI, "power", &valuef);
	// ===========================================================
	*/

	return (m_pIdxBuffer && m_pVerBuffer && m_pColBuffer && m_pVShader && m_pShaderSet && m_pShaderInstance);
}

void CKLBRenderingManager::setRenderMode(u32 mode) {
	m_renderMode = mode;
	switch (mode) {
	case 0:
		m_callMode		= GL_TRIANGLES;
		m_useTextures	= true;
		m_useColor		= true;
		break;
	case 1:
		m_callMode		= GL_LINE_STRIP;
		m_useTextures	= false;
		m_useColor		= false;
		break;
	}
}

CKLBSprite* CKLBRenderingManager::allocateCommandSprite(CKLBImageAsset* pImage, u32 priority) {
	klb_assert(m_pRenderWatchDog, "CKLBRenderingManager::setup not done first");
	klb_assert(pImage, "Null Image definition");
	bool isScale9	= (pImage->hasStandardAttribute(CKLBImageAsset::IS_SCALE9) != 0);
	bool isStdRect	= (pImage->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT) != 0);
	CKLBSprite* pSpr = isScale9 ? KLBNEW(CKLBSpriteScale9) : isStdRect ? KLBNEW(CKLBSprite4_6) : KLBNEW(CKLBSprite);
	if (pSpr) {
		if (isScale9) {
			if (((CKLBDynSprite*)pSpr)->setTriangleCount(16, 54)) {
				// SETUP BEFORE USE IMAGE !
				pSpr->m_renderOffset	= (pImage->m_renderOffset * gUseOffsetSystem);
				pSpr->m_uiOrder			= priority + pSpr->m_renderOffset;

				((CKLBSpriteScale9*)pSpr)->useImage(pImage);
				pSpr->m_pAllocNext			= m_pAllocatedSpriteList;
				if (m_pAllocatedSpriteList) {
					m_pAllocatedSpriteList->m_pAllocPrev = pSpr;
				}
				m_pAllocatedSpriteList		= pSpr;
				pSpr->m_uiStatus			= FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
				pSpr->m_pState				= &this->state;
				return pSpr;
			} else {
				KLBDELETE(pSpr);
				pSpr = NULL;
			}
		} else {
			u32 floatCount		= pImage->getVertexCount() * VERTEX_SIZE;	// X,Y,(Z),U,V
			float*  arr			= isStdRect ? ((CKLBSprite4_6*)pSpr)->m_pBuffer : KLBNEWA(float, floatCount + pImage->getVertexCount());
			u32* arrCol			= (u32*)&arr[floatCount];

			if (arr) {
				pSpr->m_pImageAsset		= pImage;
				pSpr->m_pVertex			= arr;
				pSpr->m_pColors			= arrCol;
				pSpr->m_pIndex			= pImage->getIndexBuffer();	// Cache
				pSpr->m_uiVertexCount	= (u16)pImage->getVertexCount();
				pSpr->m_uiIndexCount	= (u16)pImage->getIndexCount();
				pSpr->m_uiMaxVertexCount= (u16)pImage->getVertexCount();
				pSpr->m_uiMaxIndexCount = (u16)pImage->getIndexCount();
				pSpr->m_renderOffset	= (pImage->m_renderOffset * gUseOffsetSystem);

				pSpr->m_uiColor = 0xFFFFFFFF;	// Set default local color.
				memset32(arrCol, 0xFFFFFFFF, pSpr->m_uiVertexCount*sizeof(u32));

				if (VERTEX_SIZE > 4) {
					memset32(arr, 0, pSpr->m_uiVertexCount * VERTEX_SIZE * sizeof(float));
				}

				pSpr->m_pTexture			= pImage->getTexture()->m_pTextureUsage;
				pSpr->m_pAllocNext			= m_pAllocatedSpriteList;
				if (m_pAllocatedSpriteList) {
					m_pAllocatedSpriteList->m_pAllocPrev = pSpr;
				}
				pSpr->m_uiStatus			= FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
				pSpr->m_uiOrder				= priority + (pImage->m_renderOffset * gUseOffsetSystem);
				m_pAllocatedSpriteList		= pSpr;
				pSpr->m_pState				= &this->state;
			} else {
				if (arr)	{ KLBDELETEA(arr);		}

				KLBDELETE(pSpr);
				pSpr = NULL;
			}
		}
	}
	return pSpr;
}

CKLBDynSprite* CKLBRenderingManager::allocateCommandDynSprite(u16 vertexCount, u16 indexCount, u32 priority) {
	CKLBDynSprite* pSpr = KLBNEW(CKLBDynSprite);
	if (pSpr) {
		if (pSpr->setTriangleCount(vertexCount, indexCount)) {
			pSpr->m_pAllocNext			= m_pAllocatedSpriteList;
			if (m_pAllocatedSpriteList) {
				m_pAllocatedSpriteList->m_pAllocPrev = pSpr;
			}
			m_pAllocatedSpriteList		= pSpr;
			pSpr->m_uiOrder				= priority;
			pSpr->m_pState				= &this->state;
			return pSpr;
		}
		KLBDELETE(pSpr);
	}
	return NULL;
}

CKLBSprite* CKLBRenderingManager::allocateCommandSprite(u16 maxVertexCount, u16 maxIndexCount, u32 priority) {
	bool isPreAlloc = (maxVertexCount==4 && maxIndexCount==6);
	CKLBSprite* pSpr = isPreAlloc ? KLBNEW(CKLBSprite4_6) : KLBNEW(CKLBSprite);
	if (pSpr) {
		u32 floatCount		= maxVertexCount * VERTEX_SIZE;	// X,Y,U,V

		float*	arr			= isPreAlloc ? ((CKLBSprite4_6*)pSpr)->m_pBuffer : KLBNEWA(float,floatCount + maxIndexCount);
		u32* arrCol			= (u32*)&arr[floatCount];

		if (arr) {
			pSpr->m_pImageAsset		= NULL;
			pSpr->m_pVertex			= arr;
			if (VERTEX_SIZE > 4) { memset32(arr, 0, floatCount * sizeof(float)); }
			pSpr->m_pColors			= arrCol;
			pSpr->m_pIndex			= NULL;	// Cache
			pSpr->m_uiVertexCount	= 0;
			pSpr->m_uiIndexCount	= 0;
			pSpr->m_uiMaxVertexCount= maxVertexCount;
			pSpr->m_uiMaxIndexCount = maxIndexCount;

			pSpr->m_uiColor = 0xFFFFFFFF;	// Set default local color.
			pSpr->m_uiOrder				= priority;
			memset32(arrCol, 0xFFFFFFFF, maxVertexCount*sizeof(u32));
			pSpr->m_pState				= &this->state;

			pSpr->m_pTexture			= NULL;
			pSpr->m_pAllocNext			= m_pAllocatedSpriteList;
			if (m_pAllocatedSpriteList) {
				m_pAllocatedSpriteList->m_pAllocPrev = pSpr;
			}
			m_pAllocatedSpriteList		= pSpr;
		} else {
			if (arr)	{ KLBDELETEA(arr);		}

			KLBDELETE(pSpr);
			pSpr = NULL;
		}
	}
	return pSpr;
}

CKLBRenderState* CKLBRenderingManager::allocateCommandState() {
	CKLBRenderState* pComm = KLBNEW(CKLBRenderState);
	if (pComm) {
		pComm->jump					= NULL;
		pComm->end					= NULL;
		pComm->pShaderInstance		= NULL;

		pComm->m_scissor[0]			= 0.0f;
		pComm->m_scissor[1]			= 0.0f;
		pComm->m_scissor[2]			= 0.0f;
		pComm->m_scissor[3]			= 0.0f;

		pComm->m_scissorPost[0]		= 0.0f;
		pComm->m_scissorPost[1]		= 0.0f;
		pComm->m_scissorPost[2]		= 0.0f;
		pComm->m_scissorPost[3]		= 0.0f;

		pComm->m_stencilClear		= 0;
		pComm->m_depthClear			= 0.0f;
		pComm->m_colorClearRed		= 0.0f;
		pComm->m_colorClearGreen	= 0.0f;
		pComm->m_colorClearBlue		= 0.0f;
		pComm->m_colorClearAlpha	= 0.0f;
		pComm->m_depthStart			= 0.0f;
		pComm->m_depthEnd			= 0.0f;

		/*
		memset(&pComm->internalState,0,sizeof(SRenderState));
		*/
		pComm->m_pAllocNext			= m_pAllocatedSpriteList;
		if (m_pAllocatedSpriteList) {
			m_pAllocatedSpriteList->m_pAllocPrev = pComm;
		}
		m_pAllocatedSpriteList		= pComm;
		pComm->m_uiStatus = 0;
	}
	return pComm;
}

CKLBPolyline* CKLBRenderingManager::allocateCommandPolyline(u16 maxPointCount, u32 priority) {
	CKLBPolyline* pLine = KLBNEW(CKLBPolyline);
	if (pLine) {
		if (pLine->setMaxPointCount(maxPointCount)) {
			pLine->m_pState				= &this->state;

			pLine->m_uiOrder			= priority;
			pLine->m_pAllocNext			= m_pAllocatedSpriteList;
			if (m_pAllocatedSpriteList) {
				m_pAllocatedSpriteList->m_pAllocPrev = pLine;
			}
			m_pAllocatedSpriteList		= pLine;
		}
	}
	return pLine;
}

void CKLBRenderingManager::releaseCommand(CKLBRenderCommand* pCommand) {
	klb_assert(m_pRenderWatchDog, "CKLBRenderingManager::setup not done first");
	klb_assert(pCommand, "null pointer");

	//
	// Remove from rendering path.
	//
	if (pCommand->m_pNext || pCommand->m_pPrev) {
		removeFromRendering(pCommand);
	}

	if (pCommand->decrementCount() != 0) { return; }

	//
	// Remove from link list.
	//
	if (pCommand->m_pAllocPrev) {
		pCommand->m_pAllocPrev->m_pAllocNext = pCommand->m_pAllocNext;
	} else {
		m_pAllocatedSpriteList		= pCommand->m_pAllocNext;
	}

	if (pCommand->m_pAllocNext) {
		pCommand->m_pAllocNext->m_pAllocPrev	= pCommand->m_pAllocPrev;
	}

	KLBDELETE(pCommand);
}

void CKLBRenderingManager::removeFromRendering(CKLBRenderCommand* pRender) {
	klb_assert(m_pRenderWatchDog, "CKLBRenderingManager::setup not done first");
	klb_assert(pRender,"null pointer");
	klb_assert((pRender->m_pNext || pRender->m_pPrev),"Item already not in rendering list");

	pRender->m_pNext->m_pPrev	= pRender->m_pPrev;
	if (pRender->m_pPrev) {
		pRender->m_pPrev->m_pNext	= pRender->m_pNext;
	} else {
		m_pListStart				= pRender->m_pNext;
	}

	if (pRender == m_pRenderLastModify) {
		m_pRenderLastModify = m_pRenderLastModify->m_pNext;
	}

	// Update renderer that reuse of buffer is becoming useless from this point.
	pRender->m_pNext->m_uiStatus |= FLAG_BUFFERSHIFT;
	pRender->m_pNext = NULL;
	pRender->m_pPrev = NULL;
}

void CKLBRenderingManager::initShaderSystem() {
	for (int n=0; n < SHADER_DEF_MAX; n++) {
		m_shaderDef[n].m_definition		= NULL;
		m_shaderDef[n].m_paramList		= NULL;
		m_shaderDef[n].m_pixelShader	= NULL;
	}
	m_shaderInstanceList = NULL;
	m_stackParamFiller	 = m_stackParam;
}

void CKLBRenderingManager::destroyShaderSystem() {
	CKLBOGLWrapper&		pOGLMgr	= CKLBOGLWrapper::getInstance();
	S_SHADERINSTANCE* pShader = m_shaderInstanceList;
	while (pShader) {
		S_SHADERINSTANCE* pNext = pShader->m_pNext;
		// Do not : KLBDELETEA(pShader->m_paramList);  Simple cache here.
		KLBDELETE(pShader);
		// Shader Instance shader freed by Definition.
		pShader = pNext;
	}
	m_shaderInstanceList = NULL;

	for (int n=0; n < SHADER_DEF_MAX; n++) {
		if (m_shaderDef[n].m_definition) {
			pOGLMgr.releaseShaderSet(m_shaderDef[n].m_definition);
		}
		KLBDELETEA(m_shaderDef[n].m_paramList);
		m_shaderDef[n].m_definition		= NULL;
		m_shaderDef[n].m_paramList		= NULL;
		m_shaderDef[n].m_pixelShader	= NULL;
	}
}

void CKLBRenderingManager::stackParameter(const char* name, u8 type, QUALITY_TYPE quality) {
	u32 strLen = strlen(name) + 1;
	klb_assert(strLen < 256, "Shader Param less than 255 char");
	m_stackParamFiller[0] = type;		// Param Type
	m_stackParamFiller[1] = strLen;		// String Size
	m_stackParamFiller[2] = 0;			// Mapped Index
	m_stackParamFiller[3] = (u8)quality;
	m_stackParamFiller += 4;

	// Copy C String after size and param.
	memcpy(m_stackParamFiller, name, strLen);
	m_stackParamFiller += strLen;
}

void CKLBRenderingManager::completeParameter() {
	m_stackParamFiller[0] = 0;
	m_stackParamFiller[1] = 0;
	m_stackParamFiller[2] = 0;
	m_stackParamFiller[3] = 0;
	m_stackParamFiller += 4;
}

u32 CKLBRenderingManager::createShaderDefinition(const char* shaderCode) {

#ifdef OPENGL2
	CKLBOGLWrapper&		pOGLMgr	= CKLBOGLWrapper::getInstance();
	// 10 Param Max on stack.
	SParam paramsShader[10] = {
		// Name				Uniform?	StreamID	Data Type
		//								or
		//								UniformID
		{	"texture"		,true		,1			,TEX2D    | TEXTURE },	// Index 0
	};

	completeParameter();

	//
	// Copy Byte Stream Parameters.
	//
	int lenArray	= m_stackParamFiller - m_stackParam;
	// COPY FIRST.
	u8* pParam		= KLBNEWA(u8,lenArray);
	if (!pParam) {
		return NULL_IDX;
	}
	memcpy(pParam, m_stackParam, lenArray);

	//
	// Parse Byte Stream Parameter to build the shader.
	//
	SParam pTmpStruct;
	u8* pParamStream = pParam;
	int streamID = 1;	// "texture" is first.
	while (pParamStream[1]!=0) {								// Name Length
		pTmpStruct.name					= (const char*)&pParamStream[3];
		pTmpStruct.isUniform			= true;
		pTmpStruct.vertexORuniformID	= streamID + 1;
		pTmpStruct.dType				= pParamStream[0];
		pParamStream[2]					= streamID + 1;

		paramsShader[streamID++]		= pTmpStruct;
		pParamStream += pParamStream[1] + 3;						// Go to next item (3+String)
	}

	// Close List
	paramsShader[streamID].name					= "";
	paramsShader[streamID].isUniform			= false;
	paramsShader[streamID].vertexORuniformID	= 0;
	paramsShader[streamID].dType				= END_LIST;
	
	// Reset param stream buffer.
	m_stackParamFiller	 = m_stackParam;

	CShader*			pixelShader		= pOGLMgr.createShader(shaderCode, CKLBOGLWrapper::PIXEL_SHADER, paramsShader);
	CShaderSet*			shaderSet		= NULL;
	if (pixelShader) {
		// Map the shader together.
		shaderSet	= pOGLMgr.createShaderSet(m_pVShader, pixelShader);
		if (shaderSet) {
			for (int n=0; n < SHADER_DEF_MAX; n++) {
				if (!m_shaderDef[n].m_definition) {
					m_shaderDef[n].m_definition		= shaderSet;
					m_shaderDef[n].m_pixelShader	= pixelShader;
					m_shaderDef[n].m_paramList		= pParam;

					return n;
				}
			}
			pOGLMgr.releaseShaderSet(shaderSet);
		}
		pOGLMgr.releaseShader(pixelShader);
	}
#else
	klb_assertAlways("OpenGL 1.1 Profile does not support shader APIs");
#endif
	return NULL_IDX;
}

void CKLBRenderingManager::destroyShaderDefinition(u32 shaderDefinition) {
	if (!m_shaderDef[shaderDefinition].m_definition) {
		CKLBOGLWrapper&		pOGLMgr	= CKLBOGLWrapper::getInstance();

		KLBDELETEA(m_shaderDef[shaderDefinition].m_paramList);
		m_shaderDef[shaderDefinition].m_paramList = NULL;

		pOGLMgr.releaseShaderSet(m_shaderDef[shaderDefinition].m_definition);
		pOGLMgr.releaseShader(m_shaderDef[shaderDefinition].m_pixelShader);
		m_shaderDef[shaderDefinition].m_definition	= NULL;
		m_shaderDef[shaderDefinition].m_pixelShader = NULL;
	}
}

// Instance Slot
void* CKLBRenderingManager::instanceShader(u32 shaderDefinition, u32 startRange, u32 endRange) {
	//
	klb_assert(startRange < endRange,						"Invalid Range");
	klb_assert(shaderDefinition < SHADER_DEF_MAX,			"Invalid Shader Index");

	S_SHADERINSTANCE* pInst = m_shaderInstanceList;
	while (pInst) {
		if (!(((pInst->m_min > startRange) && (pInst->m_max < endRange)) ||
			  ((pInst->m_min < startRange) && (pInst->m_max > endRange)))) {
			klb_assertAlways("Invalid Ranges");
			return NULL;
		}
		pInst = pInst->m_pNext;
	}

	pInst = KLBNEW(S_SHADERINSTANCE);
	
	CKLBRenderState* pStartState = this->allocateCommandState();
	CKLBRenderState* pEndState   = this->allocateCommandState();


	if (pInst && pStartState && pEndState && m_shaderDef[shaderDefinition].m_definition) {
		pInst->m_pInstanceShader = m_shaderDef[shaderDefinition].m_definition->createInstance();
		if (pInst->m_pInstanceShader) {
			pStartState->setUse(false, false, pInst->m_pInstanceShader);
			pEndState->setUse(false,false,NULL);
			pEndState->m_commandType = RENDERCOMMAND_UNSETSHADER;

			// Shader Registered.
			pInst->m_paramList		= m_shaderDef[shaderDefinition].m_paramList;
			pInst->m_pNext			= m_shaderInstanceList;
			m_shaderInstanceList	= pInst;

			// Setup Start & End
			this->addToRendering(pStartState, startRange);
			this->addToRendering(pEndState, endRange);

			return pInst;
		}
	}

	// Handle Error.
	KLBDELETE(pInst);
	if (pStartState)	{ this->releaseCommand(pStartState);	}
	if (pEndState)		{ this->releaseCommand(pEndState);		}

	return NULL;
}

void CKLBRenderingManager::removeShader(void* /*instanceShader*/) {

	// TODO.	

}

u32 searchID(u8* stream, const char* name) {
	while (stream[1]!=0) {								// Name Length
		if (strcmp(name, (const char*)&stream[4])==0) {	// Name
			return stream[2];							// Index ID
		}
		stream += stream[1] + 4;						// Go to next item (3+String)
	}
	return NULL_IDX;
}

void CKLBRenderingManager::setShaderParamI(void* instanceShader, const char* name, GLint* value) {
	S_SHADERINSTANCE* pInst = (S_SHADERINSTANCE*)instanceShader;
	u32 uniformID = searchID(pInst->m_paramList, name);
	pInst->m_pInstanceShader->setUniformI(CShaderInstance::PIXEL_SHADER, uniformID, value);
}

void CKLBRenderingManager::setShaderParamF(void* instanceShader, const char* name, GLfloat* value) {
	S_SHADERINSTANCE* pInst = (S_SHADERINSTANCE*)instanceShader;
	u32 uniformID = searchID(pInst->m_paramList, name);
	pInst->m_pInstanceShader->setUniformF(CShaderInstance::PIXEL_SHADER, uniformID, value);
}

void CKLBRenderingManager::setShaderParamTexture(void* instanceShader, const char* name, CTextureUsage* value) {
	S_SHADERINSTANCE* pInst = (S_SHADERINSTANCE*)instanceShader;
	u32 uniformID = searchID(pInst->m_paramList, name);
	pInst->m_pInstanceShader->setUniformTexture(CShaderInstance::PIXEL_SHADER, uniformID, value);
}






void CKLBRenderingManager::addToRendering(CKLBRenderCommand* pRender, u32 index) {
	klb_assert(m_pRenderWatchDog, "CKLBRenderingManager::setup not done first");
	// Roll back when bug found.
	// klb_assert(index != 0xFFFFFFFF, " 0xFFFFFFFF Priority should not be used");
	klb_assert((pRender->m_pNext == NULL) && (pRender->m_pPrev == NULL), "Item already in list."); 

	//
	// Perform insertion.
	//
	CKLBRenderCommand* pInsertPoint = m_pRenderLastModify;
	if (index < m_pRenderLastModify->m_uiOrder) {
		// <
		CKLBRenderCommand* pPrevPoint = pInsertPoint; 
		while (pInsertPoint->m_uiOrder > index) {
			pPrevPoint   = pInsertPoint;
			pInsertPoint = pInsertPoint->m_pPrev;
			if (!pInsertPoint) { break; }
		}

		// Roll back to next item.
		pInsertPoint = pPrevPoint;
	} else {
		// loop until >=
		while (pInsertPoint->m_uiOrder < index) {
			pInsertPoint = pInsertPoint->m_pNext;
		}
	}

	//
	// Object inserted BEFORE insertPoint.
	//

	// Beginning of list
	if (pInsertPoint->m_pPrev == NULL) {
		pRender->m_pNext			= this->m_pListStart;
		pRender->m_pPrev			= NULL;
		this->m_pListStart->m_pPrev	= pRender;
		this->m_pListStart			= pRender;

	} else {
	// Middle of list
		pRender->m_pNext			= pInsertPoint;
		pRender->m_pPrev			= pInsertPoint->m_pPrev; 
		pInsertPoint->m_pPrev		= pRender;
		pRender->m_pPrev->m_pNext	= pRender;
	}

//	if (pRender->m_commandType == 1) {	// Buffer shift only with sprites.
		pRender->m_uiStatus |= FLAG_BUFFERSHIFT;
//	}
	pRender->m_uiOrder  = index;

	m_pRenderLastModify = pRender;

	if (index == 0xFFFFFFFF) {
		// Scene graph
		CKLBDrawResource& res = CKLBDrawResource::getInstance();
		res.getRoot()->dump(0, 0xFFFFFFFF);
		// Dump Rendering Queue
		dump(0xFFFFFFFF);

		// Put back at beginning once we did it.
		klb_assert(index != 0xFFFFFFFF, " 0xFFFFFFFF Priority should not be used");
	}
}

// Dirty Hack for now : 250 sprites with mask in ONE call max.
float	m_maskUVPtr[10000];

CTextureUsage* g_textureMask = NULL;
bool g_useTextureLast = false;
bool g_useColorLast = false;

void CKLBRenderingManager::emitDrawCall(	u16*			pIndexCounter,
											u16*			offsetIndex,
											u16*			offsetVertex,
											u16				offsetVertexHead,
											CTextureUsage*	pTextureUsage,
											CTextureUsage*	pTexture2
											) {
	u32 indexCount = *pIndexCounter;

	// OPTIMIZE : NOT VBO, could remove calls.
	m_pIdxBuffer->updateComplete(*offsetIndex + indexCount);
	m_pVerBuffer->updateComplete(offsetVertexHead);	// In vertex count
	m_pColBuffer->updateComplete(offsetVertexHead); // In vertex count

	CKLBOGLWrapper&		pOGLMgr	= CKLBOGLWrapper::getInstance();
	pOGLMgr.applyState(m_pCurrState);

	if (pTexture2 != g_textureMask) {

		dglActiveTexture(GL_TEXTURE1);
		dglClientActiveTexture(GL_TEXTURE1);

		if (pTexture2) {
			dglEnable(GL_TEXTURE_2D);
			dglBindTexture(GL_TEXTURE_2D, pTexture2->pTexture->pMaster->activeTexture);
			
			pOGLMgr.assignSampler(pTexture2, 1);

			dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
			dglTexCoordPointer(2, GL_FLOAT, 0, m_maskUVPtr);
		} else {
			dglDisable(GL_TEXTURE_2D);
			dglDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		dglActiveTexture(GL_TEXTURE0);
		dglClientActiveTexture(GL_TEXTURE0);
		g_textureMask = pTexture2;
	}

	if (indexCount) {

		m_pIdxBuffer->setDrawOffset(*offsetIndex);
		m_pVerBuffer->setDrawOffset(*offsetVertex);
		m_pColBuffer->setDrawOffset(*offsetVertex);

		// For now texture is only one texture.
		CTextureUsage* pArrTexture[2];
		s32 idUniform[2];
		pArrTexture			[0]		= pTextureUsage;
		idUniform			[0]		= 1;
		/*
		pArrTexture			[1]		= pTexture2;
		idUniform			[1]		= 2;
		*/

		//
		// Trick to support
		//
		if (pTextureUsage && m_useTextures) {
			if (g_useTextureLast == false) {
				dglEnable(GL_TEXTURE_2D);
				g_useTextureLast = true;
			}
		} else {
			if (g_useTextureLast == true) {
				dglDisable(GL_TEXTURE_2D);
				g_useTextureLast = false;
			}
		}

#ifndef OPENGL2
		if (!m_useColor) {
			if (g_useColorLast == true) {
				dglDisableClientState(GL_COLOR_ARRAY);
				g_useColorLast = false;
			}
		} else {
			if (g_useColorLast == false) {
				dglEnableClientState(GL_COLOR_ARRAY);
				g_useColorLast = true;
			}
		}
#endif

		m_pTextureUsage = pTextureUsage;

		CBuffer* arrBuff[2] = {
			m_pVerBuffer,
			m_pColBuffer,
		};

		pOGLMgr.draw(	m_callMode,
						m_pCurrShader,
						arrBuff,
						2,
						m_pIdxBuffer,
						pArrTexture,
						idUniform, 
						indexCount);

		*pIndexCounter = 0;
	#ifdef DEBUG_PERFORMANCE
		m_drawCall++;
		m_vertexCount	+= offsetVertexHead - (*offsetVertex); // Amount of vertex.
		m_indexCount	+= indexCount;
	#endif
	}

	*offsetVertex	 = offsetVertexHead;
	*offsetIndex	+= indexCount;  
}

void CKLBRenderingManager::dumpMetrics() {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
#ifdef DEBUG_PERFORMANCE
	fprintf(pFile,"\n==== Rendering Metrics ===\n");
	fprintf(pFile,"Total vertex Count : %i\n", m_vertexCount);
	fprintf(pFile,"Total index  Count : %i\n", m_indexCount);
	fprintf(pFile,"Total sprite Count : %i\n", m_spriteCount);
	fprintf(pFile,"Texture      Change: %i\n", m_textureChange);
	fprintf(pFile,"Render State Change: %i\n", m_renderStateChange);
	fprintf(pFile,"Total float transfer to GPU : %i\n", m_totalTransferSize);
	fprintf(pFile,"Total internal copy: %i\n", m_memCopySize);
	fprintf(pFile,"Total DrawCall     : %i\n", m_drawCall);
	fprintf(pFile,"Time %lli uSec\n", m_drawTime / 1000);
	fprintf(pFile,"==== Rendering Metrics End ===\n\n");
#else
	fprintf(pFile,"==== Not Available (Compile option DEBUG_PERFORMANCE not set\n\n");
#endif
}

void CKLBRenderingManager::dump(u32 /*mask*/) {
	int count = 0;
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	fprintf(pFile,"\n==== Rendering Queue Start ===\n");
	CKLBRenderCommand*	pCommand		= this->m_pListStart;
	while (pCommand != m_pRenderWatchDog) {
		fprintf(pFile,"@%p %c Priority:[%8i] Type : ",pCommand, pCommand->ignore ? '!' : ' ',pCommand->getOrder());
		u32 command = pCommand->m_commandType;
		if (command & RENDERCOMMAND_SPRITE) {
			CKLBSprite* pSpr = (CKLBSprite*)pCommand;
			fprintf(pFile,"[Sprite");

			if (pCommand->m_uiStatus & FLAG_BUFFERSHIFT) {
				fprintf(pFile," Shft");
			}
			if (pCommand->m_uiStatus & FLAG_XYUPDATE) {
				printf(" Geom");
			}
			if (pCommand->m_uiStatus & FLAG_COLORUPDATE) {
				fprintf(pFile," Col");
			}
			fprintf(pFile," Vertex:%i Index:%i] ", pSpr->m_uiVertexCount, pSpr->m_uiIndexCount);
		}

		if (command & RENDERCOMMAND_CHANGERENDERSTATE) {
			fprintf(pFile,"[Render State");
			CKLBRenderState* pRCom = (CKLBRenderState*)pCommand;
			SRenderState* pState = pRCom->getState();
			pState->dump();

			fprintf(pFile,"] ");
		}

		if (command & RENDERCOMMAND_SETSHADER) {
			fprintf(pFile,"[Shader] ");
		}

		if (command & RENDERCOMMAND_EXECUTECOMMAND) {
			if (command & RENDERCOMMAND_CLEARCOLOR)	{	
				fprintf(pFile,"[Clear Color] ");
			}
			if (command & RENDERCOMMAND_CLEARDEPTH)	{
				fprintf(pFile,"[Clear Depth] ");
			}
			if (command & RENDERCOMMAND_CLEARSTENCIL) {
				fprintf(pFile,"[Clear Stencil] ");
			}
		}
		
		fprintf(pFile,"\n");
		pCommand = pCommand->m_pNext;
		count++;
	}
	fprintf(pFile,"[WatchDog]\n==== Rendering Queue End : %i items ===\n", count);
}

u32 getColor(u32 code) {
	u8 col[4];
	col[0] = (code & 0x07) << 5;
	col[1] = (code & 0x38) << 2;
	col[2] = (code & 0x1C) >> 1;
	col[3] = 0xFF;

	return (*((u32*)col));
}

CKLBRenderCommand* CKLBRenderingManager::drawClick(u32 x, u32 y) {
	float fx = x;
	float fy = y;

	CKLBRenderCommand*	pCommand = m_pRenderWatchDog->m_pPrev;
	while (pCommand) {
		if (pCommand->m_commandType & RENDERCOMMAND_SPRITE) {
			CKLBSprite* pSpr = (CKLBSprite*)pCommand;
			if (pSpr->m_click) {
				if (pSpr->clicked(fx,fy)) {
					return pSpr;
				}
			}
		}
		pCommand = pCommand->m_pPrev;
	}

	return NULL;
}
/*
CKLBRenderCommand* CKLBRenderingManager::drawClick(u32 x, u32 y) {
	
	m_useTextures = false;
	m_coloring	  = true;

	// Clear
	dglClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	dglClear		(GL_COLOR_BUFFER_BIT);

	dglTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,	GL_COMBINE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB,		GL_REPLACE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA,		GL_REPLACE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB,			GL_TEXTURE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA,		GL_TEXTURE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB,		GL_SRC_COLOR);
	dglTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA,	GL_SRC_ALPHA);

	// Use vertex color but alpha from texture.
	//dglTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB,			GL_PRIMARY_COLOR);
	
	//
	// Test : to remove.
	//
	{
		int assignID = 1;
		CKLBRenderCommand*	pCommand = this->m_pListStart;
		CKLBRenderCommand*	found	 = NULL;
		while (pCommand != m_pRenderWatchDog) {
			if (pCommand->m_commandType & RENDERCOMMAND_SPRITE) {
				CKLBSprite* pSpr = (CKLBSprite*)pCommand;
				pSpr->m_clickID = assignID++;
			}
			pCommand = pCommand->m_pNext;
		}

		if (this->m_pListStart) {
			this->m_pListStart->m_uiStatus |= FLAG_BUFFERSHIFT;
		}
	}

	// TODO : Modify Scissor
	draw();

	// TODO : Restore Scissor

	// Get X,Y
	u8 col[8];
	dglReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&col);

	// Convert RGBA into Code
	// MSB 3 Bit of RGB -> BBBGGGRRR code;
	col[0] &= 0xE0;
	col[1] &= 0xE0;
	col[3] &= 0xE0;
	col[4]  = 0xFF;

	u32 id = (*((u32*)col));

	// Parse all rendering objects.
	CKLBRenderCommand*	pCommand = this->m_pListStart;
	CKLBRenderCommand*	found	 = NULL;
	if (id != 0) {
		while (pCommand != m_pRenderWatchDog) {
			if (pCommand->m_commandType & RENDERCOMMAND_SPRITE) {
				CKLBSprite* pSpr = (CKLBSprite*)pCommand;
				if (pSpr->m_clickColor == id) {
					found = pCommand;
					break;
				}
			}
			pCommand = pCommand->m_pNext;
		}
	}

	// Restore Initial value
	
	dglTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,	GL_MODULATE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB,		GL_MODULATE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB,			GL_TEXTURE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB,			GL_PRIMARY_COLOR);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA,		GL_TEXTURE);
	dglTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA,		GL_PRIMARY_COLOR);
	
	m_useTextures = true;
	m_coloring	  = false;

	// draw();

	return found;
}*/

void CKLBRenderingManager::enableRange(u32 start, u32 end, bool active) {
	if (end == 0xFFFFFFFF) {
		end--;
	}
	CKLBRenderCommand*	pCommand = m_pListStart;
	while (pCommand != m_pRenderWatchDog) {
		if (pCommand->m_uiOrder >= start && pCommand->m_uiOrder <= end) {
			pCommand->ignore = !active;
		}
		pCommand = pCommand->m_pNext;
	}
}

void CKLBRenderingManager::drawOverdraw() {
	CKLBRenderCommand*	renderStack[10];

	CKLBRenderCommand*	pCommand		= this->m_pListStart;
	CTextureUsage*		pLastTexture	= NULL;
	u16*				pDstIndexBuffer = (u16*)m_pIdxBuffer->updateStart(0);

	u8					bufferShift		= true;
	u16					strideVertex;
	float*				pDstVertexBuffer		= m_pVerBuffer->updateStart(1, 0, &strideVertex);
	u32*				pDstColBuffer			= (u32*)m_pColBuffer->updateStart(3, 0, null);
	u16		indexCount			= 0;
	u16		indexVCount			= 0;
	u16		offsetVertex		= 0;
	u16		offsetVertexHead	= 0;
	u16		offsetIndex			= 0;
	s32		stackDepth			= 0;
	CTextureUsage*		pLastTextureMask = NULL;

	renderStack[0]	= m_pRenderWatchDog;
	renderStack[1]	= pCommand;

	CKLBOGLWrapper& pOGLMgr	= CKLBOGLWrapper::getInstance();
	pOGLMgr.resetSampler(0);
	/*
	dump(0);
	dumpMetrics();
	*/

	m_pTextureUsage = pLastTexture;

	// Default
	m_pCurrState	= &state;
	// Default
	m_pCurrShader	= m_pShaderInstance;
	m_stackShaderIdx= 0;


#ifdef DEBUG_PERFORMANCE
	m_drawTime			= CPFInterface::getInstance().platform().nanotime();
	m_vertexCount		= 0;	// DONE
	m_indexCount		= 0;	// DONE
	m_spriteCount		= 0;	// DONE
	m_renderStateChange	= 0;	// DONE
	m_textureChange		= 0;	// DONE
	m_totalTransferSize	= 0;	// Total Transfer to GPU	
	m_memCopySize		= 0;	// Internal Move
	m_drawCall			= 0;	// DONE
#endif
	float* ptrUVMask	= m_maskUVPtr;

	dglActiveTexture(GL_TEXTURE1);
	dglClientActiveTexture(GL_TEXTURE1);
	dglDisable(GL_TEXTURE_2D);
	dglDisableClientState(GL_TEXTURE_COORD_ARRAY);

	dglActiveTexture(GL_TEXTURE0);
	dglClientActiveTexture(GL_TEXTURE0);
	g_textureMask = NULL;

	// force White fill.
	dglClearColor(1.0f,1.0f,1.0f,1.0f);
	dglClear(GL_COLOR_BUFFER_BIT);


	#define COLOR_COUNT			(7)
	static u8 g_colors[] = {
		// RGBA
		0xFF,0x00,0x00,0x40,	// Red			1
		0x00,0xFF,0x00,0x40,	// Green		2
		0x00,0x00,0xFF,0x40,	// Blue			3
		0xFF,0xFF,0x00,0x40,	// Yellow		4
		0x00,0xFF,0xFF,0x40,	// Cyan			5
		0xFF,0x00,0xFF,0x40,	// Magenta		6
		0x00,0x00,0x00,0x20,	// Black		7
	};

	u32 colorIndex = 0;

	// OPTIMIZE RP : have mecanism to remember FOR EACH draw call (render state change)
	//						avoid buffer shift in first draw call to impact further draw calls. (ie layers)
	//						and have different buffer to avoid crush by previous call.

	bool bTex = (m_bRenderOverDraw == 2);

	do {
		CKLBRenderCommand* pEnd = renderStack[stackDepth];
		pCommand				= renderStack[stackDepth+1];
		while (pCommand != pEnd) {
			if (pCommand->m_commandType & RENDERCOMMAND_SPRITE) {
				CKLBSprite* pSpr = (CKLBSprite*)pCommand;

				if ((pSpr->m_uiVertexCount != 0) && (!(pCommand->m_commandType & RENDERCOMMAND_IGNORE))) {	// TODO OPTIMIZE : Empty sprite could be optimized to be skipped once.
					if ((pSpr->m_pTexture != pLastTexture) /*|| (m_pCurrState != pSpr->m_pState)*/ || (pSpr->m_pMaskTexture != pLastTextureMask)) {
						emitDrawCall		(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, bTex ? pLastTexture : NULL ,pLastTextureMask);
						colorIndex++;
						ptrUVMask			= m_maskUVPtr;
						indexVCount  = 0; // Reset index counter.
						pLastTexture		= pSpr->m_pTexture;
						pLastTextureMask	= pSpr->m_pMaskTexture;
					}

					if (pCommand->m_commandType & RENDERCOMMAND_3D) {
						((CKLBSprite3D*)pCommand)->draw();
					} else {
						u16 sprIndexCount	= pSpr->m_uiIndexCount;
						u16 skipSize		= pSpr->m_uiVertexCount * strideVertex;

						bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);
						// Copy chunk of complete vertex. 
						// MemCopy UV
						// MemCopy XY
						if (bufferShift) {
							// Copy X,Y,U,V
							memcpy32(pDstVertexBuffer,	pSpr->m_pVertex,	skipSize              * sizeof(float));

							{
								u32 col = colorIndex % COLOR_COUNT;
								for (u32 n=0; n < pSpr->m_uiVertexCount; n++) {  pDstColBuffer[n] = *((u32*)&g_colors[col*4]); }
							}

							if (pLastTextureMask) {
								memcpy32(ptrUVMask, pSpr->m_pVertexMaskUV,	(skipSize *sizeof(float)) >> 1);
								ptrUVMask += skipSize >> 1;
							}

							// Index buffer recompute
							u16 lCount		= sprIndexCount;
							u16* pSprIdx	= pSpr->m_pIndex;

							//
							// Unroll loop by block of 8 indexes
							//
						loopSwitch:
							switch (lCount) {
							case 7: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 6: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 5: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 4: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 3: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 2: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 1: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
								break;
							default:
								if (lCount >= 8) {
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									lCount -= 8;
									goto loopSwitch;
								}
							}
						} else {
							// --- Geometry or color update : triangle do not change ---
							if (pCommand->m_uiStatus & (FLAG_XYUPDATE | FLAG_UVUPDATE)) {
								memcpy32(pDstVertexBuffer, pSpr->m_pVertex, skipSize * sizeof(float));
								if (pLastTextureMask) {
									memcpy32(ptrUVMask, pSpr->m_pVertexMaskUV,	(skipSize *sizeof(float)) >> 1);
									ptrUVMask += skipSize >> 1;
								}
							}

							{
								u32 col = colorIndex % COLOR_COUNT;
								for (u32 n=0; n < pSpr->m_uiVertexCount; n++) {  pDstColBuffer[n] = *((u32*)&g_colors[col*4]); }
							}

							// Index buffer untouched.
							pDstIndexBuffer		+= sprIndexCount;
						}

						pDstVertexBuffer	+= skipSize;
						pDstColBuffer		+= pSpr->m_uiVertexCount;
						indexCount			+= sprIndexCount;
						indexVCount			+= pSpr->m_uiVertexCount;
						offsetVertexHead	+= pSpr->m_uiVertexCount;
					}
				} else {
					// In case a sprite changed from n -> 0 vertex : global buffer is shifted.
					bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);
				}

				// Reset flag (processed)
				pCommand->m_uiStatus = 0;
				// Go next command.
				pCommand = pCommand->m_pNext;
			} else {
				emitDrawCall	(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, bTex ? pLastTexture : NULL, pLastTextureMask);
				colorIndex++;
				ptrUVMask	= m_maskUVPtr;
				indexVCount = 0;
				
				// Support render state change.
				CKLBRenderState* pRCom = (CKLBRenderState*)pCommand;

				int cmdType = pRCom->m_commandType;
				if (cmdType & RENDERCOMMAND_CHANGERENDERSTATE) {
					m_pCurrState	= pRCom->getState();
				}

				if (cmdType & RENDERCOMMAND_SETSHADER) {
					m_stackShader[m_stackShaderIdx++] = m_pCurrShader;
					m_pCurrShader	= pRCom->getShader();
				}

				if (cmdType & RENDERCOMMAND_EXECUTECOMMAND) {
					// case RENDERCOMMAND_CLEARCOLOR:
					// case RENDERCOMMAND_CLEARDEPTH:
					// case RENDERCOMMAND_CLEARSTENCIL:
					pRCom->executeCommand();
				}

				if (cmdType & RENDERCOMMAND_CHANGETARGET) {
				}

				if (cmdType & RENDERCOMMAND_UNSETSHADER) {
					m_pCurrShader	= m_stackShader[--m_stackShaderIdx];
				}

				bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);

				// Reset flag (processed)
				pCommand->m_uiStatus = 0;
				// Go next command.
				pCommand = pCommand->m_pNext;

				if (pRCom->jump) {
					renderStack[stackDepth  ] = pCommand;
					renderStack[stackDepth+1] = pEnd;

					stackDepth += 2;

					//
					// Switch to new rendering sub-queue
					//
					pCommand	= pRCom->jump;
					pEnd		= pRCom->end;
				}
			}
		}
		emitDrawCall		(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, bTex ? pLastTexture : NULL , pLastTextureMask);
		colorIndex++;
		ptrUVMask	= m_maskUVPtr;
	} while ((stackDepth -= 2) >= 0);
}

// Rendering.
void CKLBRenderingManager::draw() {
	if (m_bRenderOverDraw) {
		drawOverdraw();
		return;
	}

	klb_assert(m_pRenderWatchDog, "CKLBRenderingManager::setup not done first");

	CKLBRenderCommand*	renderStack[10];

	CKLBRenderCommand*	pCommand		= this->m_pListStart;
	CTextureUsage*		pLastTexture	= NULL;
	u16*				pDstIndexBuffer = (u16*)m_pIdxBuffer->updateStart(0);

	u8					bufferShift		= true;
	u16					strideVertex;
	float*				pDstVertexBuffer		= m_pVerBuffer->updateStart(1, 0, &strideVertex);
	u32*				pDstColBuffer			= (u32*)m_pColBuffer->updateStart(3, 0, null);
	u16		indexCount			= 0;
	u16		indexVCount			= 0;
	u16		offsetVertex		= 0;
	u16		offsetVertexHead	= 0;
	u16		offsetIndex			= 0;
	s32		stackDepth			= 0;
	CTextureUsage*		pLastTextureMask = NULL;

	renderStack[0]	= m_pRenderWatchDog;
	renderStack[1]	= pCommand;

	CKLBOGLWrapper& pOGLMgr	= CKLBOGLWrapper::getInstance();
	pOGLMgr.resetSampler(0);
	/*
	dump(0);
	dumpMetrics();
	*/

	m_pTextureUsage = pLastTexture;

	// Default
	m_pCurrState	= &state;
	// Default
	m_pCurrShader	= m_pShaderInstance;
	m_stackShaderIdx= 0;


#ifdef DEBUG_PERFORMANCE
	m_drawTime			= CPFInterface::getInstance().platform().nanotime();
	m_vertexCount		= 0;	// DONE
	m_indexCount		= 0;	// DONE
	m_spriteCount		= 0;	// DONE
	m_renderStateChange	= 0;	// DONE
	m_textureChange		= 0;	// DONE
	m_totalTransferSize	= 0;	// Total Transfer to GPU	
	m_memCopySize		= 0;	// Internal Move
	m_drawCall			= 0;	// DONE
#endif
	float* ptrUVMask	= m_maskUVPtr;

	dglActiveTexture(GL_TEXTURE1);
	dglClientActiveTexture(GL_TEXTURE1);
	dglDisable(GL_TEXTURE_2D);
	dglDisableClientState(GL_TEXTURE_COORD_ARRAY);

	dglActiveTexture(GL_TEXTURE0);
	dglClientActiveTexture(GL_TEXTURE0);
	g_textureMask = NULL;

	// OPTIMIZE RP : have mecanism to remember FOR EACH draw call (render state change)
	//						avoid buffer shift in first draw call to impact further draw calls. (ie layers)
	//						and have different buffer to avoid crush by previous call.

	do {
		CKLBRenderCommand* pEnd = renderStack[stackDepth];
		pCommand				= renderStack[stackDepth+1];
		while (pCommand != pEnd) {
			/* Comment out code concerning disabling of draw command.
			if (pCommand->ignore == true) {
				pCommand = pCommand->m_pNext;
				continue;
			}*/

			if (pCommand->m_commandType & RENDERCOMMAND_SPRITE) {
				CKLBSprite* pSpr = (CKLBSprite*)pCommand;

				if ((pSpr->m_uiVertexCount != 0) && (!(pCommand->m_commandType & RENDERCOMMAND_IGNORE))) {	// TODO OPTIMIZE : Empty sprite could be optimized to be skipped once.
				#ifdef DEBUG_PERFORMANCE
					m_spriteCount++;
				#endif
					if ((pSpr->m_pTexture != pLastTexture) /*|| (m_pCurrState != pSpr->m_pState)*/ || (pSpr->m_pMaskTexture != pLastTextureMask)) {
					#ifdef DEBUG_PERFORMANCE  
						m_textureChange++;
					#endif
						/* m_pState from sprite is garbage for now. (unused, not set in constructor)
						if (pSpr->m_pState) {
							m_pCurrState = pSpr->m_pState; // BEFORE draw call.
						}*/

						emitDrawCall		(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, pLastTexture,pLastTextureMask);
						ptrUVMask			= m_maskUVPtr;
						indexVCount  = 0; // Reset index counter.
						pLastTexture		= pSpr->m_pTexture;
						pLastTextureMask	= pSpr->m_pMaskTexture;
					}

					if (pCommand->m_commandType & RENDERCOMMAND_3D) {
						((CKLBSprite3D*)pCommand)->draw();
					} else {
						u16 sprIndexCount	= pSpr->m_uiIndexCount;
						u16 skipSize		= pSpr->m_uiVertexCount * strideVertex;

						bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);
						// Copy chunk of complete vertex. 
						// MemCopy UV
						// MemCopy XY
	#ifdef DEBUG_PERFORMANCE
						m_totalTransferSize	+= skipSize + pSpr->m_uiVertexCount;	// X,Y,U,V,Color
	#endif
						if (bufferShift) {
							// Copy X,Y,U,V
							memcpy32(pDstVertexBuffer,	pSpr->m_pVertex,	skipSize              * sizeof(float));
							// Modify color only on shift.
							memcpy32(pDstColBuffer,		pSpr->m_pColors,	pSpr->m_uiVertexCount * sizeof(u32  ));

							if (pLastTextureMask) {
								memcpy32(ptrUVMask, pSpr->m_pVertexMaskUV,	(skipSize *sizeof(float)) >> 1);
								ptrUVMask += skipSize >> 1;
							}
	#ifdef DEBUG_PERFORMANCE
							m_memCopySize	+= (skipSize + pSpr->m_uiVertexCount);	// X,Y,U,V,Color
	#endif

							// Index buffer recompute
							u16 lCount		= sprIndexCount;
							u16* pSprIdx	= pSpr->m_pIndex;

							//
							// Unroll loop by block of 8 indexes
							//
						loopSwitch:
							switch (lCount) {
							case 7: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 6: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 5: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 4: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 3: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 2: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
							case 1: *pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
								break;
							default:
								if (lCount >= 8) {
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									*pDstIndexBuffer++	= (*pSprIdx++) + indexVCount;
									lCount -= 8;
									goto loopSwitch;
								}
							}

		//					printf("cpy xyuv cpy col by shift");

						} else {
							// --- Geometry or color update : triangle do not change ---
							if (pCommand->m_uiStatus & (FLAG_XYUPDATE | FLAG_UVUPDATE)) {
								memcpy32(pDstVertexBuffer, pSpr->m_pVertex, skipSize * sizeof(float));
								if (pLastTextureMask) {
									memcpy32(ptrUVMask, pSpr->m_pVertexMaskUV,	(skipSize *sizeof(float)) >> 1);
									ptrUVMask += skipSize >> 1;
								}

	#ifdef DEBUG_PERFORMANCE
								m_memCopySize	+= skipSize;	// Number of float XYUV
	#endif
		//						printf("cpy xyuv ");
							} else {
								// else XYUV untouched
		//						printf("skp xyuv ");
							}

							if (pCommand->m_uiStatus & FLAG_COLORUPDATE) {
								memcpy32(pDstColBuffer, pSpr->m_pColors, pSpr->m_uiVertexCount * sizeof(u32));	// Modify color only on shift.
	#ifdef DEBUG_PERFORMANCE
								m_memCopySize	+= pSpr->m_uiVertexCount; // Number of color.
	#endif
		//						printf("cpy col");
							} else {
								// else Color untouched.
		//						printf("skp col");
							}

							// Index buffer untouched.
							pDstIndexBuffer		+= sprIndexCount;
						}

						pDstVertexBuffer	+= skipSize;
						pDstColBuffer		+= pSpr->m_uiVertexCount;
						indexCount			+= sprIndexCount;
						indexVCount			+= pSpr->m_uiVertexCount;
						offsetVertexHead	+= pSpr->m_uiVertexCount;
					}
				} else {
					// In case a sprite changed from n -> 0 vertex : global buffer is shifted.
					bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);
	//				printf("skip %i shift",bufferShift);
				}

				// Reset flag (processed)
				pCommand->m_uiStatus = 0;
				// Go next command.
				pCommand = pCommand->m_pNext;
			} else {
				#ifdef DEBUG_PERFORMANCE  
					m_renderStateChange++;
				#endif
				emitDrawCall	(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, pLastTexture, pLastTextureMask);
				ptrUVMask	= m_maskUVPtr;
				indexVCount = 0;
				
				// Support render state change.
				CKLBRenderState* pRCom = (CKLBRenderState*)pCommand;

				int cmdType = pRCom->m_commandType;
				if (cmdType & RENDERCOMMAND_CHANGERENDERSTATE) {
					m_pCurrState	= pRCom->getState();
				}

				if (cmdType & RENDERCOMMAND_SETSHADER) {
					m_stackShader[m_stackShaderIdx++] = m_pCurrShader;
					m_pCurrShader	= pRCom->getShader();
				}

				if (cmdType & RENDERCOMMAND_EXECUTECOMMAND) {
					// case RENDERCOMMAND_CLEARCOLOR:
					// case RENDERCOMMAND_CLEARDEPTH:
					// case RENDERCOMMAND_CLEARSTENCIL:
					pRCom->executeCommand();
				}

				if (cmdType & RENDERCOMMAND_CHANGETARGET) {
				}

				if (cmdType & RENDERCOMMAND_UNSETSHADER) {
					m_pCurrShader	= m_stackShader[--m_stackShaderIdx];
				}

				bufferShift |= (pCommand->m_uiStatus & FLAG_BUFFERSHIFT);

				// Reset flag (processed)
				pCommand->m_uiStatus = 0;
				// Go next command.
				pCommand = pCommand->m_pNext;

				if (pRCom->jump) {
					renderStack[stackDepth  ] = pCommand;
					renderStack[stackDepth+1] = pEnd;

					stackDepth += 2;

					//
					// Switch to new rendering sub-queue
					//
					pCommand	= pRCom->jump;
					pEnd		= pRCom->end;
				}
			}
		}
		emitDrawCall		(&indexCount, &offsetIndex, &offsetVertex, offsetVertexHead, pLastTexture, pLastTextureMask);
		ptrUVMask	= m_maskUVPtr;
	} while ((stackDepth -= 2) >= 0);
#ifdef DEBUG_PERFORMANCE
	m_drawTime			= CPFInterface::getInstance().platform().nanotime() - m_drawTime;
#endif
}

// ------------------------------------------
//   Render Command.
// ------------------------------------------

CKLBRenderCommand::CKLBRenderCommand():
	m_pNext				(NULL),
	m_pPrev				(NULL),
	m_pAllocPrev		(NULL),
	m_pAllocNext		(NULL),
	m_uiLocalColor		(0xFFFFFFFF),	// Most likely never used color to force refresh at first setup.
	m_uiOrder			(0),
	m_renderOffset		(0),
	m_uiRefCount		(0),
	ignore				(false)
{
	m_commandType	= 0;
	m_uiStatus		= 0;
}

void CKLBRenderCommand::changeOrder(CKLBRenderingManager& pRdr, u32 newOrder) {
	newOrder += m_renderOffset;

	// Can change the order ONLY if the object is already in the list
	if (this->m_uiOrder == newOrder) {
		return;
	}

//	if (this->m_pNext || this->m_pNext) {
	if (this->m_pPrev || this->m_pNext) {
		pRdr.removeFromRendering(this);
		pRdr.addToRendering(this, newOrder);
	} else {
		this->m_uiOrder = newOrder;
	}
}

// ------------------------------------------
//   Sprite.
// ------------------------------------------

CKLBSprite::CKLBSprite():
	CKLBRenderCommand	(),
	m_pTexture			(NULL),
	m_pMaskTexture		(NULL),
	m_pVertex			(NULL),
	m_pVertexMaskUV		(NULL),
	m_pIndex			(NULL),
	m_pColors			(NULL),
	m_uiVertexCount		(0),
	m_uiIndexCount		(0),
	m_pImageAsset		(NULL),
	m_pState			(NULL),
	m_uiColor			(0x03EF02F6),
	m_bAllocated		(1),
	m_click				(1)
{
	m_uiStatus			= 0;
	m_commandType		= RENDERCOMMAND_SPRITE;
}

CKLBSprite::~CKLBSprite() {
	if (m_pNext || m_pPrev) {
		CKLBRenderingManager::getInstance().removeFromRendering(this);
	}

	if (m_pVertex && m_bAllocated) {
		KLBDELETEA(m_pVertex);
		m_pVertex = NULL;
	}
}

bool crossLine( float x1 , float y1 , float x2 , float y2 , float px , float py , float cx , float cy )
{
	float check=0.0f;

	check = ((x1-x2)*(py-y1) + (y1-y2)*(x1-px)) * ((x1-x2)*(cy-y1) + (y1-y2)*(x1-cx));

	if( check<0 ) return true;

	return false;
}
bool CKLBSprite::clicked(float u, float v) {
	float inputX = u;
	float inputY = v;

	u16 tri_max = m_uiMaxVertexCount-2;
	u16 tri_count = 0;
	
	float p1[4];
	float p2[4];
	float p3[4];

	//
	// 1. Test by bounding box search.
	//
	bool inside = false;
	float* pVert = m_pVertex;
	float minX = 99999.0f,  minY = 99999.0f;
	float maxX = -99999.0f, maxY = -99999.0f;

	for( tri_count=0 ; tri_count<m_uiMaxVertexCount; tri_count++ ) {
		float v = *pVert++;		// X
		if (v < minX) {	minX = v;	}
		if (v > maxX) {	maxX = v;	}
		v = *pVert;	pVert +=3 ;	// Y, skip UV
		if (v < minY) {	minY = v;	}
		if (v > maxY) {	maxY = v;	}
	}

	// Outside of bounding box -> Early reject.
	if ((inputX < minX) || (inputX > maxX)) { return false; }
	if ((inputY < minY) || (inputY > maxY)) { return false; }

	//
	// 2. Test if inside triangle.
	//
	for( tri_count=0 ; tri_count<tri_max ; tri_count++ )
	{
		u16	idx[3];
		idx[0] = tri_count*3;
		idx[1] = tri_count*3+1;
		idx[2] = tri_count*3+2;

		u16 vertexID = m_pIndex[idx[0]]*VERTEX_SIZE;
		p1[0] = m_pVertex[vertexID++];		// x
		p1[1] = m_pVertex[vertexID];		// y

		vertexID = m_pIndex[idx[1]]*VERTEX_SIZE;
		p2[0] = m_pVertex[vertexID++];		// x
		p2[1] = m_pVertex[vertexID];		// y

		vertexID = m_pIndex[idx[2]]*VERTEX_SIZE;
		p3[0] = m_pVertex[vertexID++];		// x
		p3[1] = m_pVertex[vertexID];		// y

		float cx = (p1[0] + p2[0] + p3[0])/3.0f;
		float cy = (p1[1] + p2[1] + p3[1])/3.0f;

		if( crossLine( p1[0], p1[1], p2[0], p2[1], inputX, inputY, cx, cy ) ) continue;
		if( crossLine( p1[0], p1[1], p3[0], p3[1], inputX, inputY, cx, cy ) ) continue;
		if( crossLine( p2[0], p2[1], p3[0], p3[1], inputX, inputY, cx, cy ) ) continue;

		p1[2] = m_pVertex[m_pIndex[idx[0]]*VERTEX_SIZE+VERTEX_U_IDX];	// u
		p1[3] = m_pVertex[m_pIndex[idx[0]]*VERTEX_SIZE+VERTEX_V_IDX];	// v
		p2[2] = m_pVertex[m_pIndex[idx[1]]*VERTEX_SIZE+VERTEX_U_IDX];	// u
		p2[3] = m_pVertex[m_pIndex[idx[1]]*VERTEX_SIZE+VERTEX_V_IDX];	// v
		p3[2] = m_pVertex[m_pIndex[idx[2]]*VERTEX_SIZE+VERTEX_U_IDX];	// u
		p3[3] = m_pVertex[m_pIndex[idx[2]]*VERTEX_SIZE+VERTEX_V_IDX];	// v

		inside = true;
		break;
	}

	if( inside )
	{
		float testX = inputX - p1[0];
		float testY = inputY - p1[1];
		
		float TX[2],TY[2];
		/*
			p3
			|
			p1----p2

			T1 = p3-p1
			T2 = p2-p1
		*/
		TY[0] = p3[0]-p1[0];
		TY[1] = p3[1]-p1[1];

		TX[0] = p2[0]-p1[0];
		TX[1] = p2[1]-p1[1];

		float invDet = 1.0f / (TX[0]*TY[1]-TX[1]*TY[0]);
		float mat[4];
		/*
			mat[0] mat[1]
			mat[2] mat[3]
		*/
		mat[0] =  TY[1]*invDet;	mat[1] = -TY[0]*invDet;
		mat[2] = -TX[1]*invDet;	mat[3] =  TX[0]*invDet;

		float R[2];
		R[0] = testX*mat[0]+testY*mat[1];
		R[1] = testX*mat[2]+testY*mat[3];

		if ((R[0] < 0.0f) || (R[1] < 0.0f) || (R[0] + R[1] > 1.0f)) {
			// Early reject.
			return false;
		}

		float retU = p1[2]+R[0]*(p2[2]-p1[2])+R[1]*(p3[2]-p1[2]);
		float retV = p1[3]+R[0]*(p2[3]-p1[3])+R[1]*(p3[3]-p1[3]);

		return this->m_pTexture->pTexture->isAlpha(retU,retV) != 0;
	}

	return false;
}

CKLBSprite4_6::CKLBSprite4_6():CKLBSprite() {
	m_bAllocated = 0;
}

CKLBSprite4_6::~CKLBSprite4_6() {
	// Do nothing.
}

#include "CKLBNode.h"

/*virtual*/
void CKLBSprite::applyNode(CKLBNode* pNode, float stx, float sty) {
	const SMatrix2D* pMat = &pNode->m_composedMatrix;
	if (this->m_pImageAsset) {
		float* srcUV  = this->m_pImageAsset->getUVBuffer();
		float* srcXY  = this->m_pImageAsset->getXYBuffer();
		int    vCount = this->m_uiVertexCount;

	#ifdef DEBUG_PERFORMANCE
		CKLBNode::s_vertexRecomputeCount += vCount;
	#endif
	
		// We are ok here because we garantee to modify coordinate only when matrix changes.
		this->m_uiStatus |= FLAG_XYUPDATE;

		float* dstXY;
		if (this->m_uiStatus & FLAG_UVUPDATE) {
//			printf("update UV");

			// X,Y,U,V
			dstXY  =  this->m_pVertex + (VERTEX_SIZE - 2);

			for (int n=0; n < vCount; n++) {
				*dstXY++ = (*srcUV++);
				*dstXY = (*srcUV++);
				dstXY += (VERTEX_SIZE-1);
			}

		}

//		printf("\n");
		dstXY  =  this->m_pVertex;

		switch (pMat->m_type) {
		case MATRIX_ID:	// Identity
			for (int n=0; n < vCount; n++) {
				*dstXY++ = (*srcXY++) + stx;
				*dstXY   = (*srcXY++) + sty;
				dstXY   += (VERTEX_SIZE - 1);
			}
			break;
		case MATRIX_T:
			{
				float tx = pMat->m_matrix[MAT_TX] + stx;
				float ty = pMat->m_matrix[MAT_TY] + sty;

				for (int n=0; n < vCount; n++) {
					*dstXY++ = (*srcXY++) + tx;
					*dstXY   = (*srcXY++) + ty;
					dstXY   += (VERTEX_SIZE - 1);
				}
			}
			break;
		case MATRIX_TS:
			{
				float tx = pMat->m_matrix[MAT_TX];
				float ty = pMat->m_matrix[MAT_TY];
				float sx = pMat->m_matrix[MAT_A];
				float sy = pMat->m_matrix[MAT_D];

				for (int n=0; n < vCount; n++) {
					*dstXY++ = (((*srcXY++) + stx) * sx) + tx;
					*dstXY   = (((*srcXY++) + sty) * sy) + ty;
					dstXY   += (VERTEX_SIZE - 1);
				}
			}
			break;
		case MATRIX_TG:
			{
				float tx  = pMat->m_matrix[MAT_TX];
				float ty  = pMat->m_matrix[MAT_TY];
				float sx  = pMat->m_matrix[MAT_A];
				float nsx = pMat->m_matrix[MAT_B];
				float sy  = pMat->m_matrix[MAT_D];
				float nsy = pMat->m_matrix[MAT_C];

				for (int n=0; n < vCount; n++) {
					float lx = (*srcXY++) + stx;
					float ly = (*srcXY++) + sty;

					*dstXY++ = (lx * sx) + (ly * nsx) + tx;
					*dstXY   = (ly * sy) + (lx * nsy) + ty;
					dstXY   += (VERTEX_SIZE - 1);
				}
			}
			break;
		}
	}
}

void CKLBSprite::applyNode(CKLBNode* pNode) {
	applyNode(pNode, 0.0f, 0.0f);
}

/**
	WARNING : This function MUST be used with marking the NODE
	for recomputation.
 */
void CKLBSprite::switchImage(CKLBImageAsset* pImage) {
	if (m_pImageAsset != pImage) {
		u32 oldOrder = this->m_uiOrder - m_renderOffset; // Original order
		m_pImageAsset = pImage;

		if (pImage)	{
			u32 vCount = pImage->getVertexCount();
			m_uiStatus |= FLAG_UVUPDATE; // XY modified by node marking.
			if (m_uiVertexCount	!= vCount) {
				m_uiStatus |= FLAG_BUFFERSHIFT;
			}

			u32 color = m_pColors[0];	// Backup transformed color.

			if (vCount > m_uiMaxVertexCount) {
				//
				// Delete old buffers
				//
				if (m_bAllocated) {
					KLBDELETEA(m_pVertex);
				}
				
				//
				// Allocate new buffers
				//
				int add = ((pImage->m_attribMask & CKLBImageAsset::IS_3DMODEL) ? 2 : 0);
				float* pVertex		= KLBNEWA(float, vCount * (5 + add));	// Add Z&W for 3D object.
				u32*   pColors		= (u32*)&pVertex[vCount * 4 + add];
				if (pVertex) {
					m_bAllocated		= 1;
					m_pVertex			= pVertex;
					m_pColors			= pColors;
					m_uiMaxVertexCount	= m_uiVertexCount;
				} else {
					klb_assertAlways("Memory Allocation error");
				}
			}

			m_uiIndexCount		= (u16)pImage->getIndexCount();
			m_uiVertexCount		= (u16)vCount;
			m_pIndex			= pImage->getIndexBuffer();
			m_pTexture			= pImage->getTexture()->m_pTextureUsage;
			m_renderOffset		= pImage->m_renderOffset * gUseOffsetSystem;
			memset32(m_pColors, color, vCount*sizeof(u32));
		} else {
			m_uiStatus |= FLAG_BUFFERSHIFT;

			m_uiVertexCount		= 0;
			m_uiIndexCount		= 0;
			m_pIndex			= NULL;
			m_pTexture			= NULL;
			m_renderOffset		= 0;
		}
		
		this->changeOrder(CKLBRenderingManager::getInstance(), oldOrder); // Set original order.
	}
}

void CKLBSprite::setMask(CKLBImageAsset* pImage) {
	if (pImage) {
		if ((pImage->getVertexCount() != m_uiVertexCount) || (pImage->getIndexCount() != m_uiIndexCount)) {
			klb_assertAlways("Mask vertices does not match sprite image vertices");
		}
		this->m_pVertexMaskUV	= pImage->getUVBuffer();
		this->m_pMaskTexture	= pImage->getTexture()->m_pTextureUsage;
	} else {
		this->m_pVertexMaskUV	= NULL;
		this->m_pMaskTexture	= NULL; 
	}
}

// ------------------------------------------
//   Dynamic Sprites.
// ------------------------------------------


CKLBPolyline::CKLBPolyline()
:CKLBDynSprite	()
,m_points		(NULL)
,m_maxPts		(0)
{
}

CKLBPolyline::~CKLBPolyline() {
	release();
}

void CKLBPolyline::release() {
	KLBDELETEA(_internalImg.m_pXYCoord);
	_internalImg.m_pXYCoord = NULL;

	KLBDELETEA(m_pVertex);
	m_pVertex = NULL;
}

bool CKLBPolyline::setMaxPointCount	(u32 ptsCount) {
	release();
	u32 vertCount = (ptsCount-1) * 4;
	u32 idxCount  = (ptsCount-1) * 6;

	_internalImg.m_bAllocatedOutsideTexture = true;
	
	_internalImg.m_uiIndexCount		= 0;
	_internalImg.m_uiVertexCount	= 0;
	_internalImg.m_pTextureAsset	= NULL;

	float* buf	=	KLBNEWA(float, (vertCount*4) + ((idxCount + 2)>>1)); 
	
	// Use as one memory block.
	_internalImg.m_pXYCoord			= buf;
	_internalImg.m_pUVCoord			= &buf[vertCount*2];
	_internalImg.m_pIndex			= (u16*)&buf[vertCount*4];

	// Post Transform array.
	float*	arr			= KLBNEWA(float,(vertCount * (VERTEX_SIZE + 2)) + (ptsCount*2) );
	u32* arrCol			= (u32*)&arr[vertCount*VERTEX_SIZE];
	m_pLocalColors		= &arrCol[vertCount];
	m_points			= (float*)&m_pLocalColors[vertCount];
	
	bool res = _internalImg.m_pXYCoord && arr;
	if (res) {

		//
		// Fill arrays
		//
		for (u32 n=0; n < vertCount*2; n++) {
			_internalImg.m_pUVCoord[n] = 0.0f;
			_internalImg.m_pXYCoord[n] = 0.0f;
		}

		u16 m = 0;
		for (u32 n=0; n < idxCount; n+=6) {
			_internalImg.m_pIndex[n  ]	= 0 + m;
			_internalImg.m_pIndex[n+1]	= 1 + m;
			_internalImg.m_pIndex[n+2]	= 3 + m;
			_internalImg.m_pIndex[n+3]	= 1 + m;
			_internalImg.m_pIndex[n+4]	= 2 + m;
			_internalImg.m_pIndex[n+5]	= 3 + m;
			m += 4;
		}

		for (u32 n=0; n < vertCount; n++) {
			arrCol[n]					= 0xFFFFFFFF;
			m_pLocalColors[n]			= 0xFFFFFFFF;
		}

		for (u32 n=0; n < ptsCount*2; n++) {
			m_points[n] = 0.0f;
		}

		m_pImageAsset		= &_internalImg;
		m_pVertex			= arr;
		m_pColors			= arrCol;
		m_pIndex			= _internalImg.m_pIndex;	// Cache
		m_uiVertexCount		= 0;
		m_uiIndexCount		= 0;
		m_uiMaxVertexCount	= (u16)vertCount;
		m_uiMaxIndexCount	= (u16)idxCount;

		m_pTexture			= NULL;
		m_uiStatus			= FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;

		this->switchImage(&_internalImg);
	
		m_maxPts			= (u16)ptsCount;
	} else {
		KLBDELETEA(arr);
		// Other arrays destroyed when this object is destroyed.
	}
	return res;
}

void CKLBPolyline::setPointCount	(u32 ptsCount) {
	u32 vertCount = (ptsCount-1) * 4;
	u32 idxCount  = (ptsCount-1) * 6;

	klb_assert(vertCount <= m_uiMaxVertexCount, "setPointCount reached limit.");
	klb_assert(idxCount  <= m_uiMaxIndexCount , "setPointCount reached limit.");

	m_uiVertexCount					= (u16)vertCount;
	m_uiIndexCount					= (u16)idxCount;
	_internalImg.m_uiIndexCount		= (u16)idxCount;
	_internalImg.m_uiVertexCount	= (u16)vertCount;

	for (u32 n=0; n < ptsCount>>1; n++) {
		recomputeSegment(n);
	}
	m_uiStatus			|= FLAG_BUFFERSHIFT | FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
}

void CKLBPolyline::recomputeSegment(u32 idxSegment) {
	int id = idxSegment * 2;

	// Start
	float dx = m_points[id + 2] - m_points[id];
	float dy = m_points[id + 3] - m_points[id + 1];

	// Normalize Vector.
	float norm = sqrt((dx*dx) + (dy*dy));
	dx	= dx / norm;
	dy	= dy / norm;

	// Width for now
	dx *= 0.75f; 
	dy *= 0.75f; 

	float* arr = &_internalImg.m_pXYCoord[idxSegment * 8];

	//
	arr[0] = m_points[id  ] - dy;	// x0
	arr[1] = m_points[id+1] + dx;	// y0

	arr[2] = m_points[id+2] - dy;	// x1
	arr[3] = m_points[id+3] + dx;	// y1

	arr[4] = m_points[id+2] + dy;	// x2
	arr[5] = m_points[id+3] - dx;	// y2

	arr[6] = m_points[id  ] + dy;	// x3
	arr[7] = m_points[id+1] - dx;	// y3
}

void CKLBPolyline::setPoint			(u32 idx, float x, float y) {
	klb_assert(idx < m_maxPts, "setPointCount reached limit.");

	u32 id = idx * 2;
	m_points[id  ] = x;
	m_points[id+1] = y;

	if (idx == 0) {
		recomputeSegment(0);
	} else if (idx == (m_maxPts-1)) {
		idx++;
		idx >>= 1;
		recomputeSegment(idx  );
	} else {
		// Intermediate
		idx >>= 1;
		recomputeSegment(idx  );
		recomputeSegment(idx+1);
	}
	m_uiStatus			|= FLAG_XYUPDATE;
}

void CKLBPolyline::setColor			(u32 colorARGB) {
	// Conversion u32 ARGB platform dependant to RGBA byte order.
	u8 col[4];
	col[3] = colorARGB>>24;
	col[0] = colorARGB>>16;
	col[1] = colorARGB>>8 ;
	col[2] = colorARGB>>0 ;
	u32 color = *((u32*)col);

	for (u32 n=0; n < m_uiMaxVertexCount; n++) {
		m_pColors[n]				= color;
		m_pLocalColors[n]			= color;
	}
	m_uiStatus			|= FLAG_COLORUPDATE;
}

CKLBDynSprite::CKLBDynSprite()
:CKLBSprite()
,m_pLocalColors(NULL)
{
	_internalImg.m_pTextureAsset	= NULL;
	this->m_pTexture				= NULL;
}

CKLBDynSprite::~CKLBDynSprite() {
}

bool CKLBDynSprite::setTriangleCount(u16 vertexCount, u16 indexCount) {
	_internalImg.m_bAllocatedOutsideTexture = true;
	
	// Vertex & index count

	_internalImg.m_uiIndexCount		= indexCount;
	_internalImg.m_uiVertexCount	= vertexCount;
	_internalImg.m_pTextureAsset	= NULL;

	float* buf	=	KLBNEWA(float, (vertexCount*4) + ((indexCount + (indexCount&1))>>1));

	_internalImg.m_pXYCoord			= buf;
	_internalImg.m_pUVCoord			= &buf[vertexCount*2];
	_internalImg.m_pIndex			= (u16*)&buf[vertexCount*4];

	//
	float*	arr			= KLBNEWA(float,vertexCount * (VERTEX_SIZE + 2) );
	u32* arrCol			= (u32*)&arr[vertexCount * VERTEX_SIZE];
	m_pLocalColors		= &arrCol[vertexCount];

	bool res = (_internalImg.m_pXYCoord && arr);
	if (res) {

		//
		// Fill arrays
		//
		for (u32 n=0; n < (u32)(vertexCount<<1); n++) {
			_internalImg.m_pUVCoord[n] = 0.0f;
			_internalImg.m_pXYCoord[n] = 0.0f;
		}

		for (u32 n=0; n < vertexCount; n++) {
			_internalImg.m_pIndex[n]	= (u16)n;
			arrCol[n]					= 0xFFFFFFFF;
			m_pLocalColors[n]			= 0xFFFFFFFF;
		}

		if (VERTEX_SIZE > 4) {
			memset32(arr, 0, vertexCount * VERTEX_SIZE * sizeof(float));
		}

		m_pImageAsset		= &_internalImg;
		m_pVertex			= arr;
		m_pColors			= arrCol;
		m_pIndex			= _internalImg.m_pIndex;	// Cache
		m_uiVertexCount		= vertexCount;
		m_uiIndexCount		= indexCount;
		m_uiMaxVertexCount	= vertexCount;
		m_uiMaxIndexCount	= indexCount;

		m_pTexture			= NULL;
		m_uiStatus			= FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
	} else {
		if	(arr)				{ KLBDELETEA(arr);				}
		// Other arrays destroyed when this object is destroyed.
	}
	return res;
}

void CKLBDynSprite::setVertexXY		(u32 index, float x, float y) {
	if (index < m_uiVertexCount) {
		index *= 2;
		_internalImg.m_pXYCoord[index++] = x;
		_internalImg.m_pXYCoord[index  ] = y;
		m_uiStatus |= FLAG_XYUPDATE;
	}
}

void CKLBDynSprite::setVertexUV		(u32 index, float u, float v) {
	if (index < m_uiVertexCount) {
		index *= 2;
		_internalImg.m_pUVCoord[index++] = u;
		_internalImg.m_pUVCoord[index  ] = v;
		m_uiStatus |= FLAG_UVUPDATE;
	}
}

/*virtual*/
void CKLBSprite::setColor(const float* vec4) {
	u32 col = getLocalColor();
	u8* pLocalCol = (u8*)&col;

	//-----------------------------------
	// Combine with node color
	//-----------------------------------
	s32 alpha	 = (vec4[3] * pLocalCol[3]); // A
		if (alpha >= 256) {	alpha = 255;	}
		if (alpha <    0) { alpha = 0;		}
	pLocalCol[3] = alpha;
#ifdef USE_PREMULALPHA
	alpha += (alpha & 0x80)>>7; // 0..255 -> 0..256
#endif
	s32 v		 = (vec4[0] * pLocalCol[0]); // R
		if (v >= 256) {	v = 255;	}
		if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[0] = (v * alpha) >> 8;
#else
		pLocalCol[0] = v;
#endif
		v		 = (vec4[1] * pLocalCol[1]); // G
		if (v >= 256) {	v = 255;	}
		if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[1] = (v * alpha) >> 8;
#else
		pLocalCol[1] = v;
#endif
		v		 = (vec4[2] * pLocalCol[2]); // B
		if (v >= 256) {	v = 255;	}
		if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[2] = (v * alpha) >> 8;
#else
		pLocalCol[2] = v;
#endif

	#ifdef DEBUG_PERFORMANCE
	CKLBNode::s_colorRecomputeCount  += 1;
	#endif

	// Color changed ?
	if ((col != m_uiColor) || (this->m_uiStatus & FLAG_BUFFERSHIFT)) {
		m_uiColor = col;
		u32* pCol = this->m_pColors;
		this->m_uiStatus |= FLAG_COLORUPDATE;

		// Fill with RGBA 32 bit color.
		int    vCount = this->m_uiVertexCount;
		memset32(pCol, col, vCount * sizeof(u32));
	}
}

/*virtual*/
void CKLBDynSprite::setColor(const float* vec4) {

	#ifdef DEBUG_PERFORMANCE
	CKLBNode::s_colorRecomputeCount  += this->m_uiVertexCount;
	#endif

	for (u32 n=0; n<this->m_uiVertexCount; n++) {
		u32 col = m_pLocalColors[n];
		u8* pLocalCol = (u8*)&col;

		//-----------------------------------
		// Combine with node color
		//-----------------------------------
		s32 alpha	 = (vec4[3] * pLocalCol[3]); // A
			if (alpha >= 256) {	alpha = 255;	}
			if (alpha <    0) { alpha = 0;		}
		pLocalCol[3] = alpha;
#ifdef USE_PREMULALPHA
		alpha += (alpha & 0x80)>>7; // 0..255 -> 0..256
#endif

		s32  v		 = (vec4[0] * pLocalCol[0]); // R
			if (v >= 256) {	v = 255;	}
			if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[0] = (v * alpha) >> 8;
#else
		pLocalCol[0] = v;
#endif
			v		 = (vec4[1] * pLocalCol[1]); // G
			if (v >= 256) {	v = 255;	}
			if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[1] = (v * alpha) >> 8;
#else
		pLocalCol[1] = v;
#endif

			v		 = (vec4[2] * pLocalCol[2]); // B
			if (v >= 256) {	v = 255;	}
			if (v <    0) { v = 0;		}
#ifdef USE_PREMULALPHA
		pLocalCol[2] = (v * alpha) >> 8;
#else
		pLocalCol[2] = v;
#endif

		u32* pCol = this->m_pColors;
		if (pCol[n] != col) {
			pCol[n] = col;
			this->m_uiStatus |= FLAG_COLORUPDATE;
		}
	}
}

void CKLBDynSprite::setVertexColor(CKLBNode* owner, u32 index, u32 color) {
	// !!! WARNING !!!
	// color is 4x8 bit in memory with RGBA order.
	// IT IS NOT RGBA inside a U32 ! (ie endianess may change the u32)
	if (index < m_uiVertexCount) {
		u32 alpha = ((u8*)(&color))[3];
		alpha += (alpha & 0x80) >> 7;
		m_pLocalColors[index] = color;
		m_uiStatus |= FLAG_COLORUPDATE;
		owner->markUpColor();
	}
}

bool CKLBDynSprite::importXYUV		(CKLBImageAsset* pImage) {
	klb_assert(pImage,"Null ptr");
	klb_assert(pImage->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Not a standard rectangular image");
	//
	// Import only rectangular shape into 2 triangles.
	// 013 123 Source
	// 012 345 Dest
	//
	for (u32 n=0; n<12; n+=2) {
		u32 src;

		switch (n>>1) {
		case 0: src = 0; break;
		case 1: src = 2; break;
		case 2: src = 6; break;
		case 3: src = 2; break;
		case 4: src = 4; break;
		case 5: src = 6; break;
		default: src = 0;
		}

		// Copy XY
		_internalImg.m_pXYCoord[n  ]	= pImage->m_pXYCoord[src  ];
		_internalImg.m_pXYCoord[n+1]	= pImage->m_pXYCoord[src+1];

		// Copy UV
		_internalImg.m_pUVCoord[n  ]	= pImage->m_pUVCoord[src  ];
		_internalImg.m_pUVCoord[n+1]	= pImage->m_pUVCoord[src+1];

		// Index
		m_pIndex [n>>1] = (u16)(n>>1);
	}

	_internalImg.m_pTextureAsset	= pImage->getTexture();
	this->m_pTexture				= pImage->getTexture()->m_pTextureUsage;

	// May have change in vertex count.
	m_uiStatus |= FLAG_BUFFERSHIFT;

	return true;
}

void CKLBDynSprite::setTexture	(CKLBImageAsset* pImage) {
	if (pImage) {
		_internalImg.m_pTextureAsset	= pImage->getTexture();
		this->m_pTexture				= pImage->getTexture()->m_pTextureUsage;
	} else {
		_internalImg.m_pTextureAsset	= NULL;
		this->m_pTexture				= NULL;
	}
	
	// May have change in vertex count.
	m_uiStatus |= FLAG_BUFFERSHIFT;
}

void CKLBDynSprite::setTexture	(CTextureUsage* pUsage) {
		_internalImg.m_pTextureAsset	= NULL;
		this->m_pTexture				= pUsage;
}

void CKLBDynSprite::setVICount	(u32 vertexCount, u32 indexCount) {
	this->m_uiVertexCount = vertexCount;
	this->m_uiIndexCount  = indexCount;

	// May have change in vertex count.
	m_uiStatus |= FLAG_BUFFERSHIFT;
}

// ------------------------------------------
//   Slice 9 Sprite.
// ------------------------------------------

CKLBSpriteScale9::CKLBSpriteScale9()
:CKLBDynSprite		()
,m_width			(0)
,m_height			(0)
,m_pOriginalImage	(NULL)
{
}

CKLBSpriteScale9::~CKLBSpriteScale9() {
}

#define CHANGE_X	(1)
#define CHANGE_Y	(2)

void CKLBSpriteScale9::setWidth(s32 width) {
	if (width != m_width) {
		klb_assert((width >= 0) && (width < 32768), "Invalid Width (0..32767)"); 
		m_width		= (s16)width;
		recomputeVertex(CHANGE_X);
	}
}

void CKLBSpriteScale9::setHeight(s32 height) {
	if (height != m_height) {
		klb_assert((height >= 0) && (height < 32768), "Invalid Height (0..32767)"); 
		m_height	= (s16)height;
		recomputeVertex(CHANGE_Y);
	}
}

void CKLBSpriteScale9::useImage(CKLBImageAsset* pImage) {
	if (pImage->hasStandardAttribute(CKLBImageAsset::IS_SCALE9)) {
		u32 oldOrder = this->m_uiOrder - m_renderOffset; // Original order

		// Copy XY
		memcpy(_internalImg.m_pXYCoord, pImage->m_pXYCoord, 16*2*sizeof(float));
		// Copy UV
		memcpy(_internalImg.m_pUVCoord, pImage->m_pUVCoord, 16*2*sizeof(float));
		// Copy Index the first time.
		if (m_pOriginalImage == NULL) {
			memcpy(_internalImg.m_pIndex, pImage->m_pIndex, 54*sizeof(u16));
		}

		_internalImg.m_pTextureAsset	= pImage->getTexture();
		this->m_pTexture				= pImage->getTexture()->m_pTextureUsage;
		this->m_pOriginalImage			= pImage;
		this->m_renderOffset			= pImage->m_renderOffset * gUseOffsetSystem;
		
		s32 left,middleX,right;
		s32 top,middleY,bottom;

		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_LEFT,		left);
		m_left	 = (s16)left;
		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_MIDDLEX,	middleX);
		m_middleX= (s16)middleX;
		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_RIGHT,	right);
		m_right	 = (s16)right;
		m_fRight = (float)right;

		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_TOP,		top);
		m_top	 = (s16)top;
		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_MIDDLEY,	middleY);
		m_middleY= (s16)middleY;
		pImage->getAttribute(ASSET_ATTRIB::zK2_S9_BOTTOM,	bottom);
		m_bottom = (s16)bottom;
		m_fBottom = (float)bottom;

		// Adapt to new size.
		recomputeVertex(CHANGE_X | CHANGE_Y);

		changeOrder(CKLBRenderingManager::getInstance(), oldOrder);
	} else {
		klb_assertAlways("Image not usable in SCALE9");
	}
}

void CKLBSpriteScale9::recomputeVertex(u32 mode) {
	if (!m_pOriginalImage) {
		return;
	}

	//	0-1---2-3
	//  | |   | |
	//  4-5---6-7
	//  | |   | |
	//  | |   | |
	//  | |   | |
	//	8-9---A-B
	//  | |   | |
	//  C-D---E-F
	//  this->m_pOriginalImage : all info.
	//  -> Recompute sizes.

	// When width change :
	float space;

	if (mode & CHANGE_X) {
		// Computation compatible with centerX, centerY coordinate system.
		// Compute new width with low clipping
		// Compute new X
		// 26AE = 1 + NewMiddle
		space = (float)(m_width - (m_left + m_right));
		if (space < 0.0f) { space = 0.0f; }

		float* pVertex = &_internalImg.m_pXYCoord[4];
		for (int n=0; n<4; n++) {
			pVertex[0] = pVertex[-2] + space;
			pVertex += 8;	// Skip 4 vertex XY
		}

		// 37BF = 2 + Right
		pVertex = &_internalImg.m_pXYCoord[6];
		for (int n=0; n<4; n++) {
			pVertex[0] = pVertex[-2] + m_fRight;
			pVertex += 8;	// Skip 4 vertex XY
		}
	}

	// When height change :
	if (mode & CHANGE_Y) {
		// 89AB = 4 + New Middle
		// CDEF = 8 + Bottom
		space = (float)(m_height - (m_top + m_bottom));
		if (space < 0.0f) { space = 0.0f; }

		float* pVertex = &_internalImg.m_pXYCoord[(8*2)+1];	// Y Coord
		for (int n=0; n<4; n++) {
			pVertex[0] = pVertex[-8] + space;
			pVertex += 2;	// Next vertex XY
		}

		pVertex = &_internalImg.m_pXYCoord[(12*2)+1]; // Y Coord
		for (int n=0; n<4; n++) {
			pVertex[0] = pVertex[-8] + m_fBottom;
			pVertex += 2;	// Next vertex XY
		}
	}
}

// ------------------------------------------
//   Render State / Command
// ------------------------------------------

CKLBRenderState::CKLBRenderState()
:jump				(NULL)
,end				(NULL)
,pShaderInstance	(NULL)
,m_depthStart		(0.0f)
,m_depthEnd			(1.0f)
{
	m_commandType		= RENDERCOMMAND_CHANGERENDERSTATE;
}

CKLBRenderState::~CKLBRenderState()	{
}

void CKLBRenderState::executeCommand() {
	GLbitfield mask = 0;

	if (m_commandType & RENDERCOMMAND_CLEARCOLOR)	{	
		dglClearColor (m_colorClearRed, m_colorClearGreen, m_colorClearBlue, m_colorClearAlpha);
		mask |= GL_COLOR_BUFFER_BIT;	
	}
	if (m_commandType & RENDERCOMMAND_CLEARDEPTH)	{
#ifdef STD_OPENGL
		glClearDepth (m_depthClear);
#else
		dglClearDepthf (m_depthClear);
#endif
		dglDepthMask(GL_TRUE);
		mask |= GL_DEPTH_BUFFER_BIT;
	}
	if (m_commandType & RENDERCOMMAND_CLEARSTENCIL) {
		dglClearStencil (m_stencilClear);
		mask |= GL_STENCIL_BUFFER_BIT;
	}

	if (mask) {
		dglClear (mask);
	}

	if (m_commandType & RENDERCOMMAND_DEPTHRANGE) {
#ifdef STD_OPENGL
		glDepthRange(m_depthStart, m_depthEnd);
#else
		dglDepthRangef(m_depthStart, m_depthEnd);
#endif
	}
}

void CKLBRenderState::setDepthRange(float _near, float _far) {
	m_commandType |= RENDERCOMMAND_DEPTHRANGE;
	m_depthStart = _near;
	m_depthEnd	 = _far;
}

void CKLBRenderState::setClearColor(bool active, float r, float g, float b, float alpha) {
	if (active) {
		m_commandType |= RENDERCOMMAND_CLEARCOLOR;
	} else {
		m_commandType &= ~RENDERCOMMAND_CLEARCOLOR;
	}

	m_colorClearRed		= r;
	m_colorClearGreen	= g;
	m_colorClearBlue	= b;
	m_colorClearAlpha	= alpha;
}

void CKLBRenderState::setClearDepth(bool active, float depth) {
	if (active) {
		m_commandType |= RENDERCOMMAND_CLEARDEPTH;
	} else {
		m_commandType &= ~RENDERCOMMAND_CLEARDEPTH;
	}

	m_depthClear		= depth;
}

void CKLBRenderState::setClearStencil(bool active, u32 value) {
	if (active) {
		m_commandType |= RENDERCOMMAND_CLEARSTENCIL;
	} else {
		m_commandType &= ~RENDERCOMMAND_CLEARSTENCIL;
	}

	m_stencilClear = value;
}

void CKLBRenderState::setScissor(bool active, s32 x, s32 y, s32 w, s32 h) {

	internalState.changed		 = true;
	if (active) {
		internalState.bEnableScissor = TRUE_BOOL_U8;
		m_scissor[0] = x;
		m_scissor[1] = y;
		m_scissor[2] = x + w;
		m_scissor[3] = y + h;
	} else {
		internalState.bEnableScissor = FALSE_BOOL_U8;
	}
}

/*virtual*/
void CKLBRenderState::applyNode(CKLBNode* pNode) {
	if (internalState.bEnableScissor == TRUE_BOOL_U8) {
		const SMatrix2D* pMat = &pNode->m_composedMatrix;

		// Apply node transformation to Scissor.
		float tx = pMat->m_matrix[MAT_TX];
		float ty = pMat->m_matrix[MAT_TY];
		float sx = pMat->m_matrix[MAT_A];
		float sy = pMat->m_matrix[MAT_D];

		float* scissorSrc	= &m_scissor[0];
		float* scissorPost	= &m_scissorPost[0]; 

		for (int n=0; n < 2; n++) {
			*scissorPost++ = ((*scissorSrc++) * sx) + tx;
			*scissorPost++ = ((*scissorSrc++) * sy) + ty;
		}

		//
		// Logical Screen Space --> Physical
		//
		CKLBDrawResource& pDRsc = CKLBDrawResource::getInstance();
		int x0, y0, x1, y1, xo0, yo0,xo1, yo1;
		x0 = m_scissorPost[0];
		y0 = m_scissorPost[1];
		x1 = m_scissorPost[2];
		y1 = m_scissorPost[3];
		pDRsc.toPhisicalPosition(x0, y0, xo0, yo0);
		pDRsc.toPhisicalPosition(x1, y1, xo1, yo1);

		// phisical size. logical size keep.
		float localScissor[4]; 
		localScissor[0] = xo0;
		localScissor[1] = yo0;
		localScissor[2] = xo1;
		localScissor[3] = yo1;
	

		//
		// convert x,y,x,y into x,y,w,h
		//
		m_scissorPost[2] -= m_scissorPost[0];
		m_scissorPost[3] -= m_scissorPost[1];

		localScissor[2] -= localScissor[0];	// roll back to width
		localScissor[3] -= localScissor[1];	// roll back to height

//		localScissor[0] -= pDRsc.ox();
		localScissor[1] -= pDRsc.oy()*2;

		//
		// Float to int for GL (expensive float->int conv)
		//
		// Trick : GL Coordinate system is opposite on Bottom-Left, our system is Top-Left
		s32 h = (s32)localScissor[3];
		if (h < 0) { h = 0; }
		s32 w = (s32)localScissor[2];
		if (w < 0) { w = 0; }
		internalState.enableScissor	(	(s32)localScissor[0],
										(pDRsc.vp_height() - (s32)localScissor[1]-h ),
										w,
										h);
	} else {
		internalState.disableScissor();
	}
}

void CKLBRenderState::setUse(bool useRenderState, bool useCommand, CShaderInstance* pShaderInstance) {
	if (useRenderState) {
		m_commandType |= RENDERCOMMAND_CHANGERENDERSTATE;
	} else {
		m_commandType &= ~RENDERCOMMAND_CHANGERENDERSTATE;
	}

	if (useCommand) {
		m_commandType |= RENDERCOMMAND_EXECUTECOMMAND;
	} else {
		m_commandType &= ~RENDERCOMMAND_EXECUTECOMMAND;
	}

	if (pShaderInstance) {
		this->pShaderInstance = pShaderInstance;
		m_commandType |= RENDERCOMMAND_SETSHADER;
	} else {
		this->pShaderInstance = NULL;
		m_commandType &= ~RENDERCOMMAND_SETSHADER;
	}
}
