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
//
// === Rendering System ===
//
//

#ifndef __CKLB_RENDERING__
#define __CKLB_RENDERING__

#include "CKLBAsset.h"
#include "TextureManagement.h"
#include "RenderingFramework.h"

enum RENDERCOMMAND_TYPE {
	RENDERCOMMAND_SPRITE				= 0x001,
	RENDERCOMMAND_CHANGERENDERSTATE		= 0x002,
	RENDERCOMMAND_CHANGETARGET			= 0x004,
	RENDERCOMMAND_EXECUTECOMMAND		= 0x008,
	RENDERCOMMAND_SETSHADER				= 0x010,
	RENDERCOMMAND_CLEARCOLOR			= 0x020,
	RENDERCOMMAND_CLEARDEPTH			= 0x040,
	RENDERCOMMAND_CLEARSTENCIL			= 0x080,
	RENDERCOMMAND_3D					= 0x100,
	RENDERCOMMAND_UNSETSHADER			= 0x200,
	RENDERCOMMAND_DEPTHRANGE			= 0x400,
	RENDERCOMMAND_IGNORE				= 0x800,
};

// Buffer length have changed
#define FLAG_BUFFERSHIFT				(0x01)
#define FLAG_XYUPDATE					(0x02)
#define FLAG_COLORUPDATE				(0x04)
#define FLAG_UVUPDATE					(0x08)
#define FLAG_IGNORERENDER				(0x10)

#define VERTEX_SIZE						(4)
#define VERTEX_U_IDX					(VERTEX_SIZE - 2)
#define VERTEX_V_IDX					(VERTEX_SIZE - 1)

class CKLBRenderingManager;

class CKLBRenderCommand {
	friend class CKLBRenderingManager;
	friend class CKLBNode;
public:
	CKLBRenderCommand();
	virtual ~CKLBRenderCommand  ()	{ /* Do nothing */ }

	virtual	
    void applyNode		(CKLBNode* pNode)	{ /*Do nothing by default*/pNode = pNode; /*avoid warning*/ }
	
	void changeOrder	(CKLBRenderingManager& pRdr, u32 newOrder);

	inline	
    u32 getOrder        ()	        { return m_uiOrder; }

	bool setLocalColor  (u32 color)	{
				if (color != m_uiLocalColor) {
					m_uiLocalColor = color;
					return true;
				}
				return false;
			}

	inline 
    bool isInRenderList ()			{ return ((this->m_pNext != NULL) || (this->m_pPrev != NULL));	}
	inline 
    u32	getLocalColor   ()			{ return m_uiLocalColor; }

protected:
	inline
	void incrementCount()			{ m_uiRefCount++; }

	inline
	u8 decrementCount()				{ if (m_uiRefCount > 0) { return --m_uiRefCount; } else { return 0; } }

	virtual	void setColor		(const float* /*pVec*/)	{ /*Do nothing by default*/ }
	CKLBRenderCommand*	m_pAllocPrev;
	CKLBRenderCommand*	m_pAllocNext;
	CKLBRenderCommand*	m_pPrev;
	CKLBRenderCommand*	m_pNext;
	u32					m_uiOrder;
	s32					m_renderOffset;
	u32					m_uiLocalColor;
	u16					m_commandType;
	u8					m_uiStatus;
	u8					m_uiRefCount;
	bool				ignore;
};

class CKLBRenderState : public CKLBRenderCommand {
	friend class CKLBRenderingManager;
	friend class CKLBNode;
public:
	CKLBRenderState();
	virtual ~CKLBRenderState();
	
	virtual	void		applyNode		(CKLBNode* pNode);
	
	inline
	SRenderState*		getState		()									{ return &internalState;	}

	inline
	CShaderInstance*	getShader		()									{ return pShaderInstance;	}
										
	CKLBRenderCommand*	setJump			(CKLBRenderCommand*	jump)			{ this->jump = jump;		return this->jump;  }
	CKLBRenderCommand*	setReturn		(CKLBRenderCommand*	return_)		{ this->end	 = return_;		return this->end;   }
	void				executeCommand	();
	void				setUse			(bool useRenderState, bool useCommand, CShaderInstance* pShaderInstance);
	void				setClearColor	(bool active, float r, float g, float b, float alpha);
	void				setClearDepth	(bool active, float depth);
	void				setDepthRange	(float startRange, float endRange);
	void				setClearStencil	(bool active, u32 value);
	void				setScissor		(bool active, s32 x = 0, s32 y = 0, s32 w = 0, s32 h = 0);
    inline
	float*				getPostScissor	()	                                { return m_scissorPost;     }
protected:
	CKLBRenderCommand*	jump;
	CKLBRenderCommand*	end;
	CShaderInstance*	pShaderInstance;

	void				setupShaderParams	();

	float				m_scissor		[4];
	float				m_scissorPost	[4];

	GLint				m_stencilClear;
	float			    m_depthClear;
	float			    m_colorClearRed;
	float			    m_colorClearGreen;
	float			    m_colorClearBlue;
	float			    m_colorClearAlpha;
	float			    m_depthStart;
	float			    m_depthEnd;

	SRenderState internalState;
};

class CTextureUsage;
class CKLBRenderCommand;

class CKLBSprite : public CKLBRenderCommand {
	friend class CKLBRenderingManager;
public:
	CTextureUsage*			m_pTexture;
	CTextureUsage*			m_pMaskTexture;
	CKLBImageAsset*			m_pImageAsset;

	// Cached pointer from Image Asset
	float*				m_pVertex;
	float*				m_pVertexMaskUV;
	u16*				m_pIndex;
	u32*				m_pColors;

	/**
		Triangle count		= vertex count - 2.
		Index buffer count	= Triangle count * 3
	 */
	u16					m_uiVertexCount;
	u16					m_uiIndexCount;

	virtual		void	applyNode		(CKLBNode* pNode);

	bool		clicked		    (float u, float v);

	// Special version for 2D maps.
	void		applyNode	    (CKLBNode* pNode, float tx, float ty);

	void		switchImage	    (CKLBImageAsset* pImage);
	void		setMask		    (CKLBImageAsset* pMask);
	void		setRenderState	(SRenderState* pState) { m_pState = pState; }
	void		setClickID	    (u32 id);
protected:
	virtual	void setColor		(const float* vec4);

protected:
	SRenderState*		m_pState;
	u32					m_uiColor;
	u32					m_click;

	u16					m_uiMaxVertexCount;
	u16					m_uiMaxIndexCount;
	u8					m_bAllocated;
	//
	// Only CKLBRenderManager can construct sprites.
	//
protected:
	CKLBSprite();
	virtual ~CKLBSprite();
};

class CKLBSprite4_6 : public CKLBSprite {
	friend class CKLBRenderingManager;
public:
	CKLBSprite4_6();
	~CKLBSprite4_6();
private:
	float	m_pBuffer[(VERTEX_SIZE+1)*4];	// 4 vertex XYUV-Color
};

class CKLBDynSprite : public CKLBSprite {
public:
	static const int	MARK_CHANGE_XY	= FLAG_XYUPDATE;
	static const int	MARK_CHANGE_UV	= FLAG_UVUPDATE;

	CKLBDynSprite();
	~CKLBDynSprite();

	bool	setTriangleCount(u16 vertexCount, u16 indexCount);
	void	setVertexXY		(u32 index, float x, float y);
	void	setVertexUV		(u32 index, float u, float v);
	void	setVertexColor	(CKLBNode* owner, u32 index, u32 color);
	bool	importXYUV		(CKLBImageAsset* pImage);
	void	setTexture		(CKLBImageAsset* pImage);
	void	setTexture		(CTextureUsage*	pUsage);
	void	setVICount		(u32 vertexCount, u32 indexCount);

	virtual	void setColor		(const float* vec4);

	inline void		mark                (u32 mask)	{ m_uiStatus |= mask; }
	inline float*	getSrcUVBuffer      ()	        { return _internalImg.getUVBuffer();	}
	inline float*	getSrcXYBuffer      ()	        { return _internalImg.getXYBuffer();	}
	inline u16*		getSrcIndexBuffer   ()	        { return _internalImg.getIndexBuffer();	}
protected:
	CKLBImageAsset _internalImg;
	u32*	m_pLocalColors;
};

class CKLBSpriteScale9 : public CKLBDynSprite {
public:
	CKLBSpriteScale9();
	~CKLBSpriteScale9();
	void	setWidth		(s32 width);
	void	setHeight		(s32 height);

	void	useImage		(CKLBImageAsset* pImage);
protected:
	CKLBImageAsset* m_pOriginalImage;
	float			m_fRight;
	float			m_fBottom;
	s16				m_width;
	s16				m_height;
	s16				m_left;
	s16				m_right;
	s16				m_middleX;
	s16				m_top;
	s16				m_bottom;
	s16				m_middleY;


	void	recomputeVertex	(u32 mode);
};

class CKLBPolyline : public CKLBDynSprite {
public:
	CKLBPolyline();
	~CKLBPolyline();

	bool setMaxPointCount	(u32 ptsCount);
	void setPointCount		(u32 ptsCount);
	void setPoint			(u32 idx, float x, float y);
	void setColor			(u32 color);
protected:
	void recomputeSegment	(u32 idxSegment);

	u16		m_maxPts;
	float*	m_points;
private:
	void release();
};

class CKLBCanvasSprite;
class CIndexBuffer;
class CBuffer;

class CKLBRenderingManager {
public:
	inline
	static CKLBRenderingManager& getInstance() {
		static CKLBRenderingManager instance;
		return instance;
	}
	static void release() {	getInstance()._release();	}

	bool		setup(u16 maxVertexCount, u16 maxIndexCount);

	// Rendering Allocation.
	CKLBSprite*         allocateCommandSprite	    (CKLBImageAsset* pImage, u32 priority = 0);
	CKLBSprite*         allocateCommandSprite	    (u16 maxVertexCount, u16 maxIndexcount, u32 priority = 0);
	CKLBDynSprite*      allocateCommandDynSprite    (u16 vertexCount, u16 indexCount, u32 priority = 0);
	CKLBCanvasSprite*   allocateCommandCanvasSprite (u32 vertexCount, u32 indexCount, u32 priority = 0);
	CKLBRenderState*	allocateCommandState	    ();
	CKLBPolyline*       allocateCommandPolyline	    (u16 maxPointCount, u32 priority);

	void		releaseCommand			(CKLBRenderCommand* pCommand);

	void		removeFromRendering		(CKLBRenderCommand* pRender);
	void		addToRendering			(CKLBRenderCommand* pRender, u32 uiOrder);

	// Rendering.
	void		enableRange				(u32 start, u32 end, bool active);
	void		draw					();
	void		drawOverdraw			();

	CKLBRenderCommand*
				drawClick				(u32 x, u32 y);
	void		dump					(u32 mask);
	void		dumpMetrics				();
SRenderState*	getTextState			()	        { return &textState; }
	void		setRenderMode			(u32 mode);

	void		renderOverdraw			(u32 mode)	{ m_bRenderOverDraw = mode; }

	//======================================================================================
	//  Shader support
	//======================================================================================
private:
	u32			m_bRenderOverDraw;

	struct S_SHADERDEF {
		CShaderSet*			m_definition;
		CShader*			m_pixelShader;
		u8*					m_paramList;
	};

	struct S_SHADERINSTANCE {
		S_SHADERINSTANCE*	m_pNext;
		CShaderInstance*	m_pInstanceShader;
		u32					m_min;
		u32					m_max;
		u8*					m_paramList;
	};

	#define SHADER_DEF_MAX		(20)
	
	S_SHADERDEF			m_shaderDef[SHADER_DEF_MAX];
	u8					m_stackParam[1000];
	u8*					m_stackParamFiller;
	S_SHADERINSTANCE*	m_shaderInstanceList;	// TODO : set NULL at start, delete all when free rendering manager.

	CShaderInstance*	m_stackShader	[10];
	u32					m_stackShaderIdx;
	bool				m_coloring;

protected:
	void initShaderSystem		();
	void destroyShaderSystem	();
	void completeParameter		();
public:
	void stackParameter			(const char* name, u8 type, QUALITY_TYPE quality);
	u32  createShaderDefinition	(const char* shaderCode);
	void destroyShaderDefinition(u32 shaderDefinition);
	
	void* instanceShader		(u32 shaderDefinition, u32 startRange, u32 endRange);
	void removeShader			(void* instanceShader);
	
	void setShaderParamI		(void* instanceShader, const char* name, GLint* value);
	void setShaderParamF		(void* instanceShader, const char* name, GLfloat* value);
	void setShaderParamTexture	(void* instanceShader, const char* name, CTextureUsage* value);
	//======================================================================================
	//  /Shader support
	//======================================================================================

private:
	CKLBRenderingManager	();
	~CKLBRenderingManager	();
	void		_release	();

	CKLBRenderingManager	(CKLBRenderingManager const&);		// Dont implement.
	void operator=			(CKLBRenderingManager const&);		// Dont implement.


	void emitDrawCall		(u16*	pIndexCounter,
							 u16*	offsetIndex,
							 u16*	offsetVertex,
							 u16	offsetVertexHead,
							 CTextureUsage*	pTextureUsage,
							 CTextureUsage* pMask);
	CKLBRenderCommand		m_innerWatchDog;
	CKLBRenderCommand*		m_pListStart;
	CKLBRenderCommand*		m_pRenderWatchDog;
	CKLBRenderCommand*		m_pRenderLastModify;
	CKLBRenderCommand*		m_pAllocatedSpriteList;
	CIndexBuffer*			m_pIdxBuffer;
	CBuffer*				m_pVerBuffer;
	CBuffer*				m_pColBuffer;
	SRenderState			state;
	SRenderState			textState;
	SRenderState*			m_pCurrState;

	CShader*				m_pVShader;
	CShader*				m_pPShader;
	CShaderSet*				m_pShaderSet;
	CShaderInstance*		m_pShaderInstance;
	CShaderInstance*		m_pCurrShader;
	CTextureUsage*			m_pTextureUsage;

	u32		m_renderMode;
	u32		m_callMode;
	bool	m_useTextures;
	bool	m_useColor;

#ifdef DEBUG_PERFORMANCE
	u32 m_vertexCount;
	u32 m_indexCount;
	u32 m_spriteCount;
	u32 m_renderStateChange;
	u32 m_textureChange;
	u32 m_totalTransferSize;
	u32 m_memCopySize;
	u32 m_drawCall;
	s64 m_drawTime;
#endif

};

void useOffsetForImages(bool use);

#endif
