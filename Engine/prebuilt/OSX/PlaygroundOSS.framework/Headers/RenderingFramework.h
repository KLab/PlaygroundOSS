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
#ifndef __GL_WRAPPER__
#define __GL_WRAPPER__

#include "BaseType.h"
#include "CPFInterface.h"
#include "glWrapper.h"

// #include "icontrollable.h"

#define null		(0)

#define S_UNIFORM	(0x0001)
#define S_ATTRIBUTE	(0x0002)
#define S_CONSTANT	(0x0003)

#define	S_INT		(0x0010)
#define S_FLOAT		(0x0020)
#define S_MATRIX	(0x0030)

#define S_SIZE1		(0x0100)
#define	S_SIZE2		(0x0200)
#define S_SIZE3		(0x0300)
#define S_SIZE4		(0x0400)

#include "assert_klb.h"

#define	klb_assertm(s)		klb_assertAlways(s)
#define klb_assertc(c,s)	klb_assert((int)(c),(s))

class CBuffer;

//
// Shader
//
struct SParam;
class CShader;
class CShaderInstance;
class CShaderSet;

//
// Texture
//
class CTextureBase;
class CTexture;
class CSubTexture;
class CTextureUsage;

//
// Main Manager
//
class CKLBOGLWrapper;

#define UNDEFINED_BOOL		(2)
#define TRUE_BOOL_U8		(1)
#define FALSE_BOOL_U8		(0)

enum DATA_TYPE {
	VEC1I		= 0,
	VEC1F		= 1,
	VEC2		= 2,
	VEC3		= 3,
	VEC4		= 4,
	MMAT2		= 5,
	MMAT3		= 6,
	MMAT4		= 7,
	TEX2D		= 8,
	VEC4BYTE	= 9,
	// --- 10,11,12,13,14,15 --- format are free.
	//
	// MSB 4 BIT IS BITMASK.
	//
	VERTEX		= 0x00,
	COLOR		= 0x10,
	TEXTURE		= 0x20,
	NORM		= 0x30,
	END_LIST	= 0xFF
};

enum QUALITY_TYPE {
	LOWP		= 1,
	MEDP		= 2,
	HIGHP		= 3
};

struct SVertexEntry {
public:
	s32				vertexInfoID;
	s32				offset;
	bool			isVBO;
	u8				type;
private:
	// TODO.
};

struct SParam {
public:
	const char*		name;
	bool			isUniform;
	s32				vertexORuniformID;
	u8				dType;
};

// Able to use loader directly from code.
s32 TGALoad( const char *fileName, char **buffer, s32 *width, s32 *height, bool load, bool swapXY);

// Shader : "name" + type (Uniform/vertex + Format) + vertexLocationID
class CIndexBuffer {
	friend class CKLBOGLWrapper;
public:
	void			overrideBuffer	(u32 indexCount, u16* buffer);
	void			load			(short* pIndex, s32 startIndex, s32 count);	
	short*			updateStart		(s32 startIndexIncluded);
	void			updateComplete	(s32 endIndexExcluded);
	void			setDrawOffset	(s32 index);
private:
	CIndexBuffer*	pNext;
	short*			ptrBuffer;		// Dynamic buffer.
	bool			fromOutside;

	GLuint			vboID;

	u16				offsetDraw;
	short			VBOModifyStart;
	short			VBOModifyEnd;
	bool			isVBO;
	bool			VBOModified;
	bool			VBOModifying;

	void			commitVBO		();

	CIndexBuffer();
	~CIndexBuffer();
};

class CBuffer {
	friend class CKLBOGLWrapper;
public:
	void			overrideBuffer	(u32 vertexCount, float* buffer); 
	void			load			(float* vertexArrayStart, s32 vertexSize, s32 vertexInfoID, s32 startVertex, s32 count);	
	float*			updateStart		(s32 vertexInfoID, s32 startVertexIncluded, u16* stride, void* internalPtr = NULL); 
	void			updateComplete	(s32 endVertexExcluded);
	void			setDrawOffset	(s32 index);
private:
	CBuffer*		pNext;
	float*			ptrBuffer;		// Dynamic buffer.
	float*			vboLocalCopy;	// Dynamic local buffer.
	GLuint			vboID;

	SVertexEntry*	structure;
	short			VBOModifyStart;
	short			VBOModifyEnd;
	s32				offsetDrawVBO;
	s32				offsetDrawDyn;
	u8				strideVBO;
	u8				strideDyn;
	u8				vboCount;
	u8				dynCount;
	bool			VBOModified;
	bool			VBOModifying;
	bool			fromOutside;
	void			commitVBO		();

	CBuffer();
	~CBuffer();
};

// #############################################################################
//
//   
//    SHADER MANAGEMENT
//
//
// #############################################################################

class CShader {
	friend class CKLBOGLWrapper;
	friend class CShaderInstance;
	friend class CShaderSet;
public:
	// Do nothing.
private:
	struct SInternalParam {
		SParam			param;
	//	s32				locationID;
	};

	CShader*		pNext;
	SInternalParam*	arrayParam;			// One Array, shared in two.
	GLuint			shaderObj;
	u8				countUniform;
	u8				countStreamInfo;
	u8				refCount;

	bool			enableTexture;
	bool			enableColor;

	// Invisible, only through factory.
	CShader();
	~CShader();
};

class CShaderInstance {
	friend class CShaderSet;
	friend class CShader;
	friend class CKLBOGLWrapper;
public:
	enum SHADER {
		VERTEX_SHADER = 0,
		PIXEL_SHADER  = 1
	};

	void			setUniformTexture		(SHADER type, s32 uniformID, CTextureUsage*	pTextureUsage);
	void			setUniformI				(SHADER type, s32 uniformID, GLint* values  );
	void			setUniformF				(SHADER type, s32 uniformID, GLfloat* values);
	void			setConstantifyVertex	(s32 vertexID, GLfloat* values);
	void			unConstantifyVertex		(s32 vertexID);

private:
	union Float_I32	{
		float	f;
		s32		i;
	};

	struct SInternalParam {
		CTextureUsage*	pTexture;		// Store pointer become ID change at runtime.
		Float_I32		values[16];		// Can store up to 4x4 matrices.	
		s32				vertexInfoID;
		u8				isConstantifiedOrUniform;
		u8				dType;
	};

	SInternalParam*	paramArrayUniformPixelShader;
	SInternalParam*	paramArrayUniformVertexShader;
	SInternalParam* paramArrayVertexVertexShader;
	CShaderSet*		m_pShaderSet;
	CShaderInstance*	pNext;

	bool			enableTexture;
	bool			enableColor;

	// Invisible, only through factory.
	CShaderInstance();
	~CShaderInstance();
};

class CShaderSet {
	friend class CKLBOGLWrapper;
	friend class CShaderInstance;
	friend class CShader;
public:
	CShader*			vertexShader;
	CShader*			pixelShader;

	CShaderInstance*	createInstance();
	void				releaseInstance(CShaderInstance* pInstance);
private:
	CShaderInstance*	pInstances;
	CShaderSet*			pNext;
	CKLBOGLWrapper*		pMgr;
	s32*				locationArray;
	GLuint				programObj;

	bool				enableTexture;
	bool				enableColor;

	void				releaseAllInstances();

	CShaderSet();
	~CShaderSet();
};

class CRenderState {
	// Z Buffer on / off / READ / WRITE / Z VALUE
	// Stencil
	// Blend operator setup
};

class CImageBuffer {
	friend class CKLBOGLWrapper;
	friend class CFrame;
public:
	// Publicly do nothing.
private:
	CImageBuffer();
	~CImageBuffer();
	
	void incrementRefCount();
	void decrementRefCount();

	CImageBuffer* next;	
	GLuint	buffer;
	s32		width;
	s32		height;
	GLenum	internalFormat;
	u8		refCounter;
};

class CFrame {
	friend class CKLBOGLWrapper;
public:
	bool setColorBuffer		(CImageBuffer*	pBuffer);
	bool setColorBuffer		(CTexture*		pTexture, u32 mipLevel);
	bool setDepthBuffer		(CImageBuffer*	pBuffer);
	bool setDepthBuffer		(CTexture*		pTexture, u32 mipLevel);
	bool setStencilBuffer	(CImageBuffer*	pBuffer);
	
	bool use(bool check);	// Allow user to verify that setup is correct, else return always true.
private:
	CFrame();
	~CFrame();

	CFrame*			next;
	CImageBuffer*	pColBufferBuf;
	CTexture*		pColBufferTex;
	CImageBuffer*	pDepthBufferBuf;
	CTexture*		pDepthBufferTex;
	CImageBuffer*	pStencilBufferBuf;

	GLuint	colorBuff;
	GLuint	depthBuff;
	GLuint	stencilBuff;

	GLuint	frameBuffID;
};

// #############################################################################
//
//   
//    TEXTURE MANAGEMENT
//
//
// #############################################################################

class CTextureUsage {
	friend class CTextureBase;
	friend class CTexture;
	friend class CKLBOGLWrapper;
public:
	enum SAMPLING {
		NEAREST = 0,
		LINEAR  = 1,
		BLEND_IFMIPMAP_BIT = 0x2 
	};

	enum WRAPPING {
		REPEAT			= 0,
		CLAMP_TO_EDGE	= 1
		// MIRRORED		= 2 Not available on OpenGL 2.0 AND 1.1
	};

	void			init				(CTextureBase* pTexture);

	void 			activate			(s32 sampler);
	
	// 
	void			setSampling			(SAMPLING minmode, SAMPLING magmode);
	void 			setWrapping			(WRAPPING U_mode, WRAPPING V_mode);

	// Lots of people need to find a texture based on usage ptr, put as public for now.
	CTextureBase*		pTexture;
private:
	GLenum	minSampling;
	GLenum	maxSampling;
	GLenum	uMode;
	GLenum	vMode;
	bool	samplingSetupDone;

	CKLBOGLWrapper*	pMgr;
	CTextureUsage*		pNext;

	CTextureUsage();
	~CTextureUsage();
};

class CTextureBase {
	friend class CKLBOGLWrapper;
	friend class CTextureUsage;
	friend class CTexture;
	friend class CSubTexture;
	friend class CFontTexture;
public:
	enum UVCOMPUTE_MODE {
		TOP_LEFT		= 0,
		CENTROID		= 1
	};

	u32	isAlpha	(float u,float v);

	inline
	s32 			getWidth				()									{ return width; 	}
	inline
	s32 			getHeight				()									{ return height;	}
	
	CTextureUsage*	createUsage				();
	void 			releaseUsage			(CTextureUsage* pUsage);

	CSubTexture*	setSubAtlas				(bool asFont, s32 x, s32 y, s32 width, s32 height);
	void			releaseSubTexture		(CSubTexture* pSubTex);
	bool			updateTexture			(s32 x, s32 y, s32 width, s32 height, void* data, s32 dataSize);
	void			updateTextureFromFrame	(u32 mipLevel, s32 dstX, s32 dstY, s32 srcX, s32 srcY, s32 srcW, s32 srcH);
	void			convertPixelToRenderUV	(s32 x, s32 y, UVCOMPUTE_MODE sampling, float* u, float* v);
	void			convertLocalUVToRenderUV(float lu, float lv, float* u, float *v);
	void			assignSWAlphaBuffer		(u8* buffer);
	u8*				getSWAlphaBuffer		()	{ return pSWAlphaMap ; }

	// To allow user to get main texture easily.
	CTexture*		pMaster;
private:
	// In absolute top parent coordinate system
	s32				x;
	s32				y;

	s32				width;
	s32				height;
	s32				usageCount;
	u8*				pSWAlphaMap;

	CKLBOGLWrapper*	pMgr;

	CTextureUsage	usageList;

	// Atlas feature.
	CTextureBase*	pParent;
	CTextureBase*	pChild;
	CTextureBase*	pBrother;

	CTextureBase();
	~CTextureBase();

	void 			releaseUsage		();
	void			releaseSubTextures	();
};

class CTexture : public CTextureBase {
	friend class CKLBOGLWrapper;
	friend class CTextureUsage;
	friend class CTextureBase;
	friend class CFontTexture;
	friend class CFrame;
public:
	void			makeEmptyShell			();
	GLuint			activeTexture;	
private:
	GLuint			getWorkingTexture() {
		if (pMaster->isDoubleBuffered) {
			return (pMaster->activeTexture == pMaster->texture) ? pMaster->textureDoubleBuff : pMaster->texture; 
		} else {
			return pMaster->texture;
		}
	}

	float			UPerPixel;
	float			VPerPixel;
	
	CTexture*		pNext;
	bool			isDoubleBuffered;
	bool			isMipmapped;
	bool			isCompressed;
	bool			is3D;
	s32				frame;

	// Open GL side
	GLenum			format;
	GLint			channels;

	GLuint			texture;
	GLuint			textureDoubleBuff;

	CTexture ();
	~CTexture();
};

class CFontTexture;

class CSubTexture : public CTextureBase {
	friend class CKLBOGLWrapper;
	friend class CTexture;
#ifndef __GNUC__
	friend class CSubTexture;
#endif
	friend class CTextureBase;
	friend class CFontTexture;
	// No member, no function for now.
private:
	CSubTexture();
	~CSubTexture();
};

class CFontTexture : public CSubTexture {
	friend class CTextureBase;
public:
	void setup			(s32 fixedSize);
	bool setupCharCount	(u16 charCount);

	void registerChar	(unichar c, s32 variableSize);
	void registerChar	(unichar c, u32 x, u32 y, u32 w, u32 h, bool rot = false, u8 marginTopLeft = 0, u8 marginBottomRight = 0);
	void getChar		(unichar c, float* u0, float* u1, float* v0, float* v1, float* w, float* h);
private:
	s32				fixedSize;
	s32				currX;
	s32				currY;
	float*			u0u1v0v1;
	u32*			wh;

	CFontTexture();
	~CFontTexture();
};

struct USampler {
	GLuint	texture;
};

// #############################################################################
//
//   
//    MAIN SYSTEM
//
//
// #############################################################################
struct SRenderState {
	friend class CKLBOGLWrapper;
public:
	SRenderState();

	enum RENDER_MODE {
		ONLY_COLOR,
		ONLY_TEXTURE,
		TEXTURE_MUL_COLOR,
		ES2_BRIGHTNESS,
		ES2_COLORIZE,
		ES2_SATURATE,
		ES2_RAMP,
		ES2_TONE,
		ES2_MOSAIC
	};

	enum BLEND_MODE {
		NO_ALPHA,
		ALPHA,
		ADDITIVE,
		ADDITIVE_ALPHA
	};

	enum BLEND_DST {
		D_ONE						= GL_ONE,
		D_SRC_COLOR					= GL_SRC_COLOR,
		D_ONE_MINUS_SRC_COLOR		= GL_ONE_MINUS_SRC_COLOR,
		D_SRC_ALPHA					= GL_SRC_ALPHA,
		D_ONE_MINUS_SRC_ALPHA		= GL_ONE_MINUS_SRC_ALPHA,
		D_DST_ALPHA					= GL_DST_ALPHA,
		D_ONE_MINUS_DST_ALPHA		= GL_ONE_MINUS_DST_ALPHA
	};

	enum BLEND_SRC {
		S_ZERO						= GL_ZERO,
		S_ONE						= GL_ONE,
		S_DST_COLOR					= GL_DST_COLOR,
		S_ONE_MINUS_DST_COLOR		= GL_ONE_MINUS_DST_COLOR,
		S_SRC_ALPHA_SATURATE		= GL_SRC_ALPHA_SATURATE,
		S_SRC_ALPHA					= GL_SRC_ALPHA,
		S_ONE_MINUS_SRC_ALPHA		= GL_ONE_MINUS_SRC_ALPHA,
		S_DST_ALPHA					= GL_DST_ALPHA,
		S_ONE_MINUS_DST_ALPHA		= GL_ONE_MINUS_DST_ALPHA
	};

	enum DEPTH_OP {
		LESS	= GL_LESS,
		GREATER	= GL_GREATER,
		LEQUAL	= GL_LEQUAL,
		GEQUAL	= GL_GEQUAL,
		EQUAL	= GL_EQUAL,
		NOTEQUAL= GL_NOTEQUAL,
		ALWAYS	= GL_ALWAYS,
		NEVER	= GL_NEVER
	};

	enum STENCIL_OP {
		KEEP	= GL_KEEP,
		ZERO	= GL_ZERO,
		REPLACE	= GL_REPLACE,
		INCR	= GL_INCR,
		DECR	= GL_DECR,
#ifdef OPENGL2
		INCR_WRAP = GL_INCR_WRAP,
		DECR_WRAP = GL_DECR_WRAP,
#endif
		INVERT	  = GL_INVERT
	};

	enum BLEND_OP {
		ADD		= 0,
#ifdef OPENGL2
		SUB		= 1,
		REVSUB	= 2
#endif
	};

	void setTextMode		(bool active);
	void setBlend			(BLEND_MODE mode);
	void setBlendAdvance	(BLEND_SRC src, BLEND_DST dst, BLEND_OP src_op_dst);
	void setDepthState		(bool write, bool test, DEPTH_OP op);

	void setStencilTestCW	(u32 readMask, u32 refValue, DEPTH_OP compare_op); 
	void setStencilTestCCW	(u32 readMask, u32 refValue, DEPTH_OP compare_op); 

	void setStencilWriteCW	(u32 writeMask, STENCIL_OP opFailStencil, STENCIL_OP opFailZ, STENCIL_OP opSucceed);
	void setStencilWriteCCW	(u32 writeMask, STENCIL_OP opFailStencil, STENCIL_OP opFailZ, STENCIL_OP opSucceed);

	void enableAlphaTest	(float value, DEPTH_OP compare_op);
	void disableAlphaTest	();

	void enableScissor		(s32 x, s32 y, s32 w, s32 h);
	void disableScissor		();

	void dump				();
public:
	bool		changed;

	// Scissor	(ability for external recomputation : public)
	GLint		scX;
	GLint		scY;
	GLsizei		scW;
	GLsizei		scH;
	u8			bEnableScissor;

private:
	// Blending
	u8			blendEnable;
	GLenum		blendSrcFactor;
	GLenum		blendDstFactor;
	u8			blendOp;

	// Depth
	u8			depthWriteEnable;
	u8			depthTestEnable;
	GLenum		depthFunction;
	
	// Custom text mode
	u8			textMode;

	// Alpha Test
	u8			alphaTestEnable;
	GLenum		alphaFunction;
	float		alphaValue;

	//
	// Stencil Read
	//
	u16			stReadMaskCW;
	u16			stReadMaskCCW;
	u16			stRefValueCW;
	u16			stRefValueCCW;
	DEPTH_OP	stRefOpCW;
	DEPTH_OP	stRefOpCCW;

	//
	// Stencil Write
	//
	u16			stWriteMaskCW;
	u16			stWriteMaskCCW;
	STENCIL_OP	stWriteFailS_StencilOP_CW;
	STENCIL_OP	stWriteFailZ_StencilOP_CW;
	STENCIL_OP	stWriteSuccZ_StencilOP_CW;
	STENCIL_OP	stWriteFailS_StencilOP_CCW;
	STENCIL_OP	stWriteFailZ_StencilOP_CCW;
	STENCIL_OP	stWriteSuccZ_StencilOP_CCW;
};

class CKLBOGLWrapper {
	friend class CTextureUsage;
public:
	inline
	static CKLBOGLWrapper& getInstance() {
		static CKLBOGLWrapper instance;
		return instance;
	}
	static void release() {
		getInstance()._release();
	}

	// Texture.
	enum TEX_OPTION {
		TEX_NONE					= 0,
		TEX_OPT_DOUBLEBUFFERED_BIT	= 0x1,
		TEX_OPT_MIPMAP_BIT			= 0x2,
		TEX_OPT_COMPRESSED_BIT		= 0x4,
		TEX_OPT_3D					= 0x8
	};

	enum TEX_CHANNEL {
		ALPHA			= 1,
		RGB				= 3,
		RGBA			= 4,
		LUMINANCE		= 0,
		LUMINANCE_ALPHA	= 2
	};

	enum SHADER_TYPE {
		VERTEX_SHADER	= 0,
		PIXEL_SHADER	= 1
	};

	bool			init(float displayMatrix[6]);

	// ------------------------------------------------------------------------
	// Buffers.
	//

	s32				getFrame()			{ return frame; }
	void			endFrame();

	// ------------------------------------------------------------------------
	// Rendering.
	//

	void			resetSampler		(s32 sampler);
	void			applyState(SRenderState* pState);
	void			draw(
								GLenum				mode,
								CShaderInstance*	instance,
								CBuffer**			pBuffer,
								u32					bufferCount,
								CIndexBuffer*		pIndexBuffer,
								CTextureUsage**		array_pTexture,
								s32*				uniformID,
								s32					indexCount);

	void			setRenderFrame(CFrame* pFrame = 0);
	
	
	// ------------------------------------------------------------------------
	// Object Allocation / Management
	//

	CTexture*		loadTGA				(const char* filename, u32 pixFormat, s32* rw = null, s32* rh = null, bool load = true, bool swapXY = false, CTexture* res = null, int x = 0, int y = 0, TEX_OPTION option = TEX_NONE);
	CTexture*		loadCompress		(const char* filename, u32 pixFormat, u32 w, u32 h, TEX_OPTION option = TEX_NONE);

	// 0 : Color
	// 1 : Depth
	// 2 : Stencil
	CImageBuffer*	createImageBuffer	(s32 width, s32 height, GLenum internalformat);
	void			releaseImageBuffer	(CImageBuffer* imageBuffer);

	bool			supportFrame		();
	bool			support3DTexture	();

	CFrame*			createFrame			();
	void			releaseFrame		(CFrame* pFrame);

	bool			copyScreenRGB888	(u32 srcx, u32 srcy, u32 width,u32 height,u8* buffer);

	CTexture*		createTexture		(s32 width, s32 height, GLenum pixelFormat, TEX_CHANNEL channelCount,void* data, s32 dataLength = 0, TEX_OPTION option = TEX_NONE, s32 depth = 0, CTexture* reload = NULL);
	void			releaseTexture		(CTexture* texture);
	
	// Shaders.
	CShader*		createShader		(SRenderState::RENDER_MODE, SHADER_TYPE type, const SParam* listParam);
	CShader*		createShader		(const char* source, SHADER_TYPE type, const SParam* listParam);
	void			releaseShader		(CShader* pShader);

	// Rendering Shader.
	CShaderSet*		createShaderSet		(CShader* pVertexShader, CShader* pPixelShader);
	void			releaseShaderSet	(CShaderSet* pFullShader);

	CBuffer*		createVertexBuffer	(s32 vertexCount, const SVertexEntry* listComponent, void* usingOutsideBuffer = NULL);
	void			releaseVertexBuffer	(CBuffer* pBuffer);

	CIndexBuffer*	createIndexBuffer	(s32 indexCount, bool asVBO, void* usingOutsideBuffer = NULL);
	void			releaseIndexBuffer	(CIndexBuffer* pBuffer);

	void			assignSampler		(CTextureUsage* pTextureInstance, s32 sampler);
private:
	CKLBOGLWrapper	();
	~CKLBOGLWrapper	();
	void _release	();

	CKLBOGLWrapper	(CKLBOGLWrapper const&);		// Dont implement.
	void operator=		(CKLBOGLWrapper const&);		// Dont implement.

	const char*		patch				(const char* shader, const char* glslTransform);

	GLuint			arrayBufferID;
	void			_glBindBuffer		(GLuint id);

	USampler		samplerUnit[4];
	s32				frame;

	GLfloat			displayMatrix2D[16];

	CTexture*		m_pTextureList;
	CShader*		shaderList;
	CShaderSet*		shaderSetList;
	CBuffer*		bufferList;
	CIndexBuffer*	indexBufferList;
	CImageBuffer*	imgBufferList;
	CFrame*			frameList;

	SRenderState	rState;
	SRenderState*	m_pLastState;
	CShaderInstance*
					m_lastShaderInstance;
	GLuint			lastElementArrayBuffer;
	u8				enableColor;
	u8				enableTexture;

#ifdef OPENGL2
	char shaderPatchArray[1000];
#endif
	void*			_glTexImage3DOES;
	void*			_glTexSubImage3DOES;
};

#endif
