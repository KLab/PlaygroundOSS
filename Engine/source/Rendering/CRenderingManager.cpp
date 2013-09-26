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
#include "RenderingFramework.h"
#include "mem.h"

static int _x_getVertexSize() {
	CHECKMEM();
	return 5;
}

CKLBOGLWrapper::CKLBOGLWrapper():
	frame				(0),

	m_pTextureList		(NULL),
	shaderList			(NULL),
	shaderSetList		(NULL),
	bufferList			(NULL),
	indexBufferList		(NULL),
	imgBufferList		(NULL),
	frameList			(NULL),
	m_pLastState		(NULL),
	m_lastShaderInstance(NULL),
	_glTexImage3DOES	(NULL),
	_glTexSubImage3DOES	(NULL),
	enableColor			(UNDEFINED_BOOL),
	enableTexture		(UNDEFINED_BOOL),
	lastElementArrayBuffer	((GLuint)-1),
	arrayBufferID			((GLuint)-1)
{
	//char shaderPatchArray[1000];

	// Vertex arrays is ALWAYS available
	// in our system.
#ifndef OPENGL2
	dglEnableClientState(GL_VERTEX_ARRAY);
#else
	// ### TODO ### Call Extensions _glTexImage3DOES, _glTexSubImage3DOES
#endif
}

CKLBOGLWrapper::~CKLBOGLWrapper() {
	_release();
}

void CKLBOGLWrapper::_release() {
	//
	// Release all textures / usages / sub textures.
	//
	while (m_pTextureList) {
		klb_assertAlways("Texture not freed yet");
		releaseTexture(m_pTextureList);
	}
	
	while (shaderSetList) {
		klb_assertAlways("Shader set not freed yet");
		releaseShaderSet(shaderSetList);
	}

	while (shaderList) {
		klb_assertAlways("Shader not freed yet");
		releaseShader(shaderList);
	}

	if (bufferList) {
	}

	if (indexBufferList) {
	}

	if (imgBufferList) {
	}

	if (frameList) {

	}
}

//
// Rendering Manager.
//
bool CKLBOGLWrapper::init(float displayMatrix[16]) {
	memcpy32(displayMatrix2D, displayMatrix, 16*sizeof(float));

	// Current GL state must be uninitialized.

#ifndef OPENGL2
	dglMatrixMode(GL_MODELVIEW);
	dglLoadMatrixf(displayMatrix2D);
#endif

	return true;
}

// s32		CKLBOGLWrapper::getFrame()	{ return frame; }

///
//  Macros
//
#define INVERTED_BIT            (1 << 5)

///
//  Types
//
#pragma pack(push,x1)                            // Byte alignment (8-bit)
#pragma pack(1)

typedef struct
{
   unsigned char  IdSize,
                  MapType,
                  ImageType;
   unsigned short PaletteStart,
                  PaletteSize;
   unsigned char  PaletteEntryDepth;
   unsigned short X,
                  Y,
                  Width,
                  Height;
   unsigned char  ColorDepth,
                  Descriptor;
         
} TGA_HEADER;

typedef struct {
	unsigned char rgbtRed, rgbtGreen, rgbtBlue;
} K_RGBTRIPLE;

typedef struct {
	unsigned char rgbtBlue, rgbtGreen, rgbtRed, rgbtAlpha;
} K_RGBQUAD;

#pragma pack(pop,x1)

////////////////////////////////////////////////////////////////////////////////////
//
//  Private Functions
//

////////////////////////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//


///
//  WinTGALoad()
//
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

s32 TGALoad( const char *fileName, char **buffer, s32 *width, s32 *height, bool load, bool swapXY)
{
	FILE        *fp;
	TGA_HEADER   Header;

	if ( ( fp = fopen ( fileName, "rb" ) ) == 0 )
	{
		return 0;
	}

	if ( fp == NULL )
	{
		return 0;
	}

	fread ( &Header, sizeof(TGA_HEADER), 1, fp );

	*width = Header.Width;
	*height = Header.Height;
   
	if (load) {
		if ( Header.ColorDepth == 24 )
		{
			K_RGBTRIPLE *Buffer24;

			Buffer24= (K_RGBTRIPLE*)KLBMALLOC(sizeof(K_RGBTRIPLE) * (*width) * (*height));

			if(Buffer24)
			{
				s32 i=0;
				s32 x,
				y;

				fread(Buffer24, sizeof(K_RGBTRIPLE), (*width) * (*height), fp);

				*buffer= (char*)KLBMALLOC(4 * (*width) * (*height));

				if (swapXY) {
					for ( y = 0; y < *width; y++ )
						for( x = 0; x < *height; x++ )
						{
							s32 Index= x * (*width) + y;

							if(!(Header.Descriptor & INVERTED_BIT)) {
								Index= ((*height) - 1 - x) * (*width) + y;
							}

							(*buffer)[(i * 4)]=      Buffer24[Index].rgbtRed;
							(*buffer)[(i * 4) + 1]=  Buffer24[Index].rgbtGreen;
							(*buffer)[(i * 4) + 2]=  Buffer24[Index].rgbtBlue;
							(*buffer)[(i * 4) + 3]=  (char)255;
        
							i++;
						}
				} else {
					for ( y = 0; y < *height; y++ )
						for( x = 0; x < *width; x++ )
						{
							s32 Index= y * (*width) + x;

							if(!(Header.Descriptor & INVERTED_BIT)) {
								Index= ((*height) - 1 - y) * (*width) + x;
							}

							(*buffer)[(i * 4)]=      Buffer24[Index].rgbtRed;
							(*buffer)[(i * 4) + 1]=  Buffer24[Index].rgbtGreen;
							(*buffer)[(i * 4) + 2]=  Buffer24[Index].rgbtBlue;
							(*buffer)[(i * 4) + 3]=  (char)255;
        
							i++;
						}
				}
				fclose(fp);
				KLBFREE(Buffer24);
				return 3;
			}
		}

		if ( Header.ColorDepth == 32 )
		{
			K_RGBQUAD *Buffer32;

			Buffer32= (K_RGBQUAD*)KLBMALLOC(sizeof(K_RGBQUAD) * (*width) * (*height));

			if(Buffer32)
			{
				s32 i=0;
				s32 x,
					y;

				fread(Buffer32, sizeof(K_RGBQUAD), (*width) * (*height), fp);

				*buffer= (char*)KLBMALLOC(4 * (*width) * (*height));

				if (swapXY) {
					for ( y = 0; y < *width; y++ )
						for( x = 0; x < *height; x++ )
						{
							s32 Index= x * (*width) + y;

							if(!(Header.Descriptor & INVERTED_BIT)) {
								Index= ((*height) - 1 - x) * (*width) + y;
							}

							(*buffer)[(i * 4)]=      Buffer32[Index].rgbtRed;
							(*buffer)[(i * 4) + 1]=  Buffer32[Index].rgbtGreen;
							(*buffer)[(i * 4) + 2]=  Buffer32[Index].rgbtBlue;
							(*buffer)[(i * 4) + 3]=  Buffer32[Index].rgbtAlpha;
        
							i++;
						}
				} else {
					for ( y = 0; y < *height; y++ )
						for( x = 0; x < *width; x++ )
						{
							s32 Index= y * (*width) + x;

							if(!(Header.Descriptor & INVERTED_BIT)) {
								Index= ((*height) - 1 - y) * (*width) + x;
							}

							(*buffer)[(i * 4)]=      Buffer32[Index].rgbtRed;
							(*buffer)[(i * 4) + 1]=  Buffer32[Index].rgbtGreen;
							(*buffer)[(i * 4) + 2]=  Buffer32[Index].rgbtBlue;
							(*buffer)[(i * 4) + 3]=  Buffer32[Index].rgbtAlpha;
        
							i++;
						}
				}
				KLBFREE(Buffer32);
			}
			fclose(fp);
			return 4;
		}		
	}
	   
	fclose(fp);
	return 0;
}

static void convertPixels(u8* pBuffer, s32 width, s32 height, u32 channel, GLenum pixFormat) {
	switch (channel) {
	case 1:		// GL_ALPHA, GL_LUMINANCE
		// Do nothing.
		return;
	case 2:		// GL_LUMINANCE_ALPHA
		// Do nothing.
		return;
	case 3:		// GL_RGB
	case 4:		// GL_RGBA
		if (pixFormat == GL_UNSIGNED_BYTE) {
			// DO NOTHING.
			return;
		} else if (pixFormat == 0x565) {
			// RGBA byte.
			for (s32 y=0; y < height; y++) {
				u8* pSrc	= &pBuffer[y * width * channel];
				u16* pDst	= (u16*)&pBuffer[y*width*2];
				for (s32 x=0; x < width; x++) {
					u16 col = ((pSrc[0] & 0xF8) << 8) | ((pSrc[1] & 0xFC)<<3) | ((pSrc[2] & 0xF8)>>3);
					*pDst++ = col;
					*pSrc  += channel;
				}
			}
		} else if (pixFormat == 0x4444) {
			// RGBA byte.
			if (channel == 3) {
				channel = 4;
				for (s32 y=0; y < height; y++) {
					u8* pSrc	= &pBuffer[y * width * channel];
					u16* pDst	= (u16*)&pBuffer[y*width*2];
					for (s32 x=0; x < width; x++) {
						u16 col = ((pSrc[0] & 0xF0) << 8) | ((pSrc[1] & 0xF0)<<4) | ((pSrc[2] & 0xF0) | 0xF);
						*pDst++ = col;
						*pSrc  += channel;
					}
				}
			} else {
				for (s32 y=0; y < height; y++) {
					u8* pSrc	= &pBuffer[y * width * channel];
					u16* pDst	= (u16*)&pBuffer[y*width*2];
					for (s32 x=0; x < width; x++) {
						u16 col = ((pSrc[0] & 0xF0) << 8) | ((pSrc[1] & 0xF0)<<4) | ((pSrc[2] & 0xF0) | (pSrc[3]>>4));
						*pDst++ = col;
						*pSrc  += channel;
					}
				}
			}
		} else if (pixFormat == 0x5551) {
			// RGBA byte.
			if (channel == 3) {
				channel = 4;
				for (s32 y=0; y < height; y++) {
					u8* pSrc	= &pBuffer[y * width * channel];
					u16* pDst	= (u16*)&pBuffer[y*width*2];
					for (s32 x=0; x < width; x++) {
						u16 col = ((pSrc[0] & 0xF8) << 8) | ((pSrc[1] & 0xF8)<<3) | (((pSrc[2] & 0xF8)>>2) | 0x1);
						*pDst++ = col;
						*pSrc  += channel;
					}
				}
			} else {
				for (s32 y=0; y < height; y++) {
					u8* pSrc	= &pBuffer[y * width * channel];
					u16* pDst	= (u16*)&pBuffer[y*width*2];
					for (s32 x=0; x < width; x++) {
						u16 col = ((pSrc[0] & 0xF8) << 8) | ((pSrc[1] & 0xF8)<<3) | (((pSrc[2] & 0xF8)>>2) | (pSrc[3]>>7));
						*pDst++ = col;
						*pSrc  += channel;
					}
				}
			}
		}
		break;
	}
}

CTexture*	CKLBOGLWrapper::loadCompress(const char* filename, GLenum pixFormat, u32 w, u32 h, TEX_OPTION option) {
	// open file and read data.
	u32 fileLength;
	u8* pBuffer;
	CKLBOGLWrapper::TEX_CHANNEL channel = CKLBOGLWrapper::RGBA;	// Value ignored anyway.
	FILE* fp;
	CTexture* pRes = null;

	if ((fp = fopen (filename, "rb")) == 0)	{	return null;	}
	if ( fp == NULL )						{	return null;	}

	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pBuffer = (u8*)KLBMALLOC(fileLength);

	if (pBuffer) {
		fread(pBuffer, sizeof(u8), fileLength, fp);
		pRes = createTexture(w,h, pixFormat, channel, pBuffer, fileLength, TEX_OPTION((int)option | TEX_OPT_COMPRESSED_BIT));
		KLBFREE(pBuffer);
	}
	fclose(fp);
	return pRes;
}

CTexture*	CKLBOGLWrapper::loadTGA(const char* filename, GLenum pixFormat, s32* rw, s32* rh, bool load, bool swapXY, CTexture* res, int x, int y, TEX_OPTION option) {
	s32 w	= 0;
	s32 h	= 0;
	char* pBuffer;
	TEX_CHANNEL channel = (TEX_CHANNEL)TGALoad(filename, &pBuffer, &w, &h, load, swapXY);
	if (rw) { *rw = w; }
	if (rh) { *rh = h; }
	if (channel && load) {
		if (swapXY) {
			int tmp;
			tmp = w;
			w = h;
			h = tmp;
		}

		convertPixels((u8*)pBuffer, w, h, channel, pixFormat);

		if (res == null) {
			res = createTexture(w,h, pixFormat, channel, pBuffer, w*h*channel, option);
		} else {
			res->updateTexture(x,y,w,h,pBuffer,w*h*channel);
		}
		KLBFREE(pBuffer);
		return res;
	} else {
		return null;
	}
}

int g_CountRl = 0;
void		CKLBOGLWrapper::releaseTexture	(CTexture* texture) {
	if (texture) {
		printf("Release Texture %p %i\n",texture, g_CountRl++);
		// Remove texture usage. (FIRST)
		texture->releaseUsage();

		// Remove Sub Textures. (SECOND)
		texture->releaseSubTextures();

		//
		// Remove master texture itself from the list.
		//
		if (texture == m_pTextureList) {
			m_pTextureList = texture->pNext;
		} else {
			CTexture* pPrev = m_pTextureList;
			while (pPrev->pNext != texture) {
				pPrev = pPrev->pNext;
			}

			pPrev->pNext = texture->pNext;
		}

		//
		// Free on GL side.
		//
		dglDeleteTextures(1, &texture->texture);
		texture->texture = 0;
		if (texture->textureDoubleBuff != 0) {
			dglDeleteTextures(1, &texture->textureDoubleBuff);
			texture->textureDoubleBuff = 0;
		}

		KLBDELETE(texture);
	}
}

CBuffer*	CKLBOGLWrapper::createVertexBuffer		(s32 vertexCount, const SVertexEntry* listComponent, void* asOutsideBuffer) {
	CBuffer* pNewBuffer = KLBNEW(CBuffer);
	if (pNewBuffer) {
		s32 sizeVBOVertex = 0;
		s32 sizeDynVertex = 0;
		s32 cntVBOVertex = 0;
		s32 cntDynVertex = 0;
		const SVertexEntry* pParse = listComponent;
		while (pParse->type != END_LIST) {
			s32 size;

			switch (pParse->type & 0x0F) {
			case VEC1F:
			case VEC1I:
			case VEC4BYTE:
				size = 1;
				break;
			case VEC2:
				size = 2;
				break;
			case VEC3:
				size = 3;
				break;
			case VEC4:
				size = 4;
				break;
			default:
				size = 0;
				klb_assertAlways("Invalid vertex type in vertex entry list (CRenderingBuffer::createVertexBuffer)");
				break;
			}

			if (pParse->isVBO) {
				sizeVBOVertex += size;
				cntVBOVertex++;
			} else {
				sizeDynVertex += size;
				cntDynVertex++;
			}
			pParse++;
		}
		
		pNewBuffer->fromOutside = (asOutsideBuffer != NULL);
		klb_assert(!(pNewBuffer->fromOutside == true && pParse->isVBO == true), "VBO can not be outside buffer"); 

		SVertexEntry* list = KLBNEWA(SVertexEntry,cntDynVertex + cntVBOVertex);
		if (list) {
			if (cntVBOVertex != 0) {
				dglGenBuffers(1, &pNewBuffer->vboID);
			}
			if ((pNewBuffer->vboID) || (cntVBOVertex == 0)) {
				float*	vboLocal;
				float*	ptrBuff;
				bool err;

				if (sizeDynVertex) {
					ptrBuff = KLBNEWA(float,vertexCount * sizeDynVertex);
					err		= (ptrBuff == null);
				} else {
					ptrBuff = null;
					err		= false;
				}

				if (cntVBOVertex != 0) {
					vboLocal = KLBNEWA(float,vertexCount * sizeVBOVertex);
					_glBindBuffer(pNewBuffer->vboID);
					dglBufferData(GL_ARRAY_BUFFER, vertexCount * sizeVBOVertex * sizeof(float), null, GL_STATIC_DRAW);
					err |= (vboLocal == null) || (glGetError() != GL_NO_ERROR);
				} else {
					vboLocal = null;
					err |= false;
				}

				if (!err) {
					pNewBuffer->dynCount		= cntDynVertex;
					pNewBuffer->vboCount		= cntVBOVertex;
					pNewBuffer->ptrBuffer		= ptrBuff;
					pNewBuffer->vboLocalCopy	= vboLocal;
					pNewBuffer->strideVBO		= sizeVBOVertex;
					pNewBuffer->strideDyn		= sizeDynVertex;
					pNewBuffer->VBOModified		= (cntVBOVertex != 0);
					pNewBuffer->VBOModifying	= false;
					pNewBuffer->VBOModifyStart	= 0;
					pNewBuffer->VBOModifyEnd	= vertexCount;
					pNewBuffer->offsetDrawDyn	= 0;
					pNewBuffer->offsetDrawVBO	= 0;

					pNewBuffer->structure		= list;

					pParse = listComponent;
					s32 sizeVBO = 0;
					s32 sizeDyn = 0;

					while (pParse->type != END_LIST) {
						s32 size;

						// Copy the struct first.
						*list = *pParse;
						
						switch (pParse->type & 0x0F) {
						case VEC1F:
						case VEC1I:
						case VEC4BYTE:
							size = 1;
							break;
						case VEC2:
							size = 2;
							break;
						case VEC3:
							size = 3;
							break;
						case VEC4:
							size = 4;
							break;
						default:
							//
							// Assert done already.
							//
							size = 0;
							break;
						}

						if (pParse->isVBO) {
							list->offset = sizeVBO;
							sizeVBO += size;
						} else {
							list->offset = sizeDyn;
							sizeDyn += size;
						}
						pParse++;
						list++;
					}

					pNewBuffer->pNext = this->bufferList;
					this->bufferList = pNewBuffer;
					return pNewBuffer;
				}
				
				if (vboLocal) {
					KLBDELETE(vboLocal);
				}

				if (ptrBuff && (!asOutsideBuffer)) {
					KLBDELETE(ptrBuff);
				}

				dglDeleteBuffers(1, &pNewBuffer->vboID);
			}
			KLBDELETE(list);
		}
		KLBDELETE(pNewBuffer);
		pNewBuffer = null;
	}
	return pNewBuffer;
}

CIndexBuffer* CKLBOGLWrapper::createIndexBuffer(s32 indexCount, bool asVBO, void* asOutsideBuffer) {
	CIndexBuffer* pNewBuffer = KLBNEW(CIndexBuffer);
	if (pNewBuffer) {
		GLushort*	ptrBuff		= KLBNEWA(GLushort,indexCount);
		pNewBuffer->vboID		= 0;
		pNewBuffer->fromOutside = (asOutsideBuffer != NULL);
		klb_assert(!(pNewBuffer->fromOutside == true && asVBO == true), "VBO can not be outside buffer"); 

		bool err = (ptrBuff == null);
		if (asVBO) {
			dglGenBuffers(1, &pNewBuffer->vboID);
			_glBindBuffer(pNewBuffer->vboID);
			dglBufferData(GL_ARRAY_BUFFER, indexCount * sizeof(GLushort), null, GL_STATIC_DRAW);
			err |= (dglGetError() != GL_NO_ERROR);
		}

		if (err == false) {
			pNewBuffer->ptrBuffer		= (short*)ptrBuff;
			pNewBuffer->VBOModified		= asVBO;
			pNewBuffer->VBOModifying	= false;
			pNewBuffer->VBOModifyStart	= 0;
			pNewBuffer->VBOModifyEnd	= indexCount;
			pNewBuffer->isVBO			= asVBO;
			pNewBuffer->pNext			= this->indexBufferList;
			pNewBuffer->offsetDraw		= 0;
			this->indexBufferList		= pNewBuffer;
			return pNewBuffer;
		}

		if (ptrBuff != null && (!asOutsideBuffer)) {
			KLBDELETE(ptrBuff);
		}

		if (pNewBuffer->vboID) {
			dglDeleteBuffers(1, &pNewBuffer->vboID);
		}

		KLBDELETE(pNewBuffer);
		pNewBuffer = null;
	}
	return pNewBuffer;
}

void CKLBOGLWrapper::_glBindBuffer(GLuint id) {
	if (id != arrayBufferID) {
		arrayBufferID = id;
		dglBindBuffer(GL_ARRAY_BUFFER, id);
	}
}

void CKLBOGLWrapper::releaseIndexBuffer(CIndexBuffer* pBuffer) {
	CIndexBuffer* p = this->indexBufferList;
	CIndexBuffer* prev = null;
	while (p != pBuffer) {
		prev = p;
		p = p->pNext;
	}

	if (prev == null) {
		this->indexBufferList = p->pNext;
	} else {
		prev->pNext = p->pNext;
	}

	dglDeleteBuffers(1, &pBuffer->vboID);

	if (!p->fromOutside) {
		KLBDELETE(p->ptrBuffer);
	}
	KLBDELETE(pBuffer);
}

void CKLBOGLWrapper::releaseVertexBuffer(CBuffer* pBuffer) {
	CBuffer* p = this->bufferList;
	CBuffer* prev = null;
	while (p != pBuffer) {
		prev = p;
		p = p->pNext;
	}

	if (prev == null) {
		this->bufferList = p->pNext;
	} else {
		prev->pNext = p->pNext;
	}

	dglDeleteBuffers(1, &pBuffer->vboID);

	KLBDELETE(p->structure);

	if (p->ptrBuffer && (!p->fromOutside)) {
		KLBDELETE(p->ptrBuffer);
	}

	if (p->vboLocalCopy) {
		KLBDELETE(p->vboLocalCopy);
	}
	
	KLBDELETE(pBuffer);
}

void CKLBOGLWrapper::endFrame() {
	frame++;
}

bool CKLBOGLWrapper::support3DTexture() {
	return (_glTexImage3DOES != NULL);
}

CTexture*	CKLBOGLWrapper::createTexture	(	s32 width, 
												s32 height, 
												GLenum pixelFormat, 
												TEX_CHANNEL channelCount,
												void* data, 
												s32 dataLength, 
												TEX_OPTION option, 
												s32 /*depth*/,
												CTexture* reload) {
	CTexture* pTexture = reload ? reload : KLBNEW(CTexture);

	if (pTexture) {
		// Init to nothing.
		pTexture->texture			= 0;
		pTexture->textureDoubleBuff = 0;
        
        GLenum err = glGetError();
		dglGenTextures(1, &pTexture->texture);
		
		pTexture->isDoubleBuffered	= ((option & TEX_OPT_DOUBLEBUFFERED_BIT	) != 0);
		pTexture->isCompressed		= ((option & TEX_OPT_COMPRESSED_BIT		) != 0);
		pTexture->isMipmapped		= ((option & TEX_OPT_MIPMAP_BIT			) != 0);
		pTexture->is3D				= ((option & TEX_OPT_3D					) != 0) && _glTexImage3DOES;

		klb_assert((!(((option & TEX_OPT_3D) != 0) && (_glTexImage3DOES==NULL))), "3D Texture not supported");

		if (pTexture->isDoubleBuffered) {
			dglGenTextures(1, &pTexture->textureDoubleBuff);
		}
        err = dglGetError();
		if (err == GL_NO_ERROR) {
			pTexture->x = 0;
			pTexture->y = 0;

			pTexture->width				= width;
			pTexture->height			= height;
			pTexture->UPerPixel			= (float)(1.0 / width);
			pTexture->VPerPixel			= (float)(1.0 / height);
			pTexture->usageCount		= 0;
			pTexture->pMaster			= pTexture;
			pTexture->pParent			= null;
			pTexture->pChild			= null;
			pTexture->pBrother			= null;
			pTexture->pMgr				= this;

			pTexture->activeTexture 	= pTexture->texture;

			pTexture->usageList.init(pTexture);
			pTexture->usageList.pMgr	= this;

			pTexture->format			= pixelFormat;

			//
			//
			//
			GLenum textureTarget = 
#ifdef OPENGL2
                GL_TEXTURE_2D
				// pTexture->is3D ? GL_TEXTURE_3D_OES : GL_TEXTURE_2D
#else
				GL_TEXTURE_2D
#endif
				;

			for (s32 n=0; n<2; n++) {
				if ( n == 0) {
					dglBindTexture(textureTarget, pTexture->texture);
				} else {
					if (!pTexture->isDoubleBuffered) {
						break;
					}
					dglBindTexture(textureTarget, pTexture->textureDoubleBuff);
				}

				if (pTexture->isCompressed) {
					klb_assert((!pTexture->is3D), "Do not support compressed 3D textures");
					dglCompressedTexImage2D(GL_TEXTURE_2D, 
							0,	// TODO MIPMAP Level
							pixelFormat,
							width,
							height,
							0,
							dataLength,
							data
					);
				} else {
					GLint internalFormat;
					switch (channelCount) {
						case ALPHA		:	internalFormat = GL_ALPHA;			break;
						case RGB		:	internalFormat = GL_RGB;			break;
						case LUMINANCE	:	internalFormat = GL_LUMINANCE;		break;
						case LUMINANCE_ALPHA
										:	internalFormat = GL_LUMINANCE_ALPHA;	break;

						default			:
						case RGBA		:	internalFormat = GL_RGBA;			break;
					}

					pTexture->channels			= internalFormat;

					if (pTexture->is3D) {
						// ### TODO TEXTURE UPDATE FUNCTION ###
						//PFNGLTEXSUBIMAGE3DOESPROC	_glTexSubImage3DOES;
#ifdef OPENGL2
                        /*
						((PFNGLTEXIMAGE3DOESPROC)_glTexImage3DOES)(GL_TEXTURE_3D_OES, 0, internalFormat, width, height, depth, 0, pixelFormat, internalFormat, data);
                        */
#else
						klb_assertAlways("OpenGL 1.1 does not use 3D Textures.");
#endif
					} else {
						dglTexImage2D(GL_TEXTURE_2D,
							0,	// TODO MIPMAP Level
							internalFormat,
							width,
							height,
							0,
							internalFormat,
							pixelFormat,
							data
						);
					}

					klb_assert(dglGetError()==GL_NO_ERROR,"Error creating OpenGL Texture.\n");
				}

				if (pTexture->isMipmapped) {
#ifdef OPENGL2
					dglGenerateMipmap (GL_TEXTURE_2D);
#else
					klb_assertAlways("Implement mipmap for OpenGL 1.x");
#endif
				}

				if (dglGetError() != GL_NO_ERROR) {
					goto error1;
				}
			}

			//
			// Finally everything is ok : add to the texture list.
			//
			if (!reload) {
				pTexture->pNext = m_pTextureList;
				m_pTextureList = pTexture;
			}
		} else {
			goto error1;
		}
	}
	return pTexture;
error1:
	if (pTexture->texture != 0) {	dglDeleteTextures(1, &pTexture->texture);	}

	if (pTexture->textureDoubleBuff != 0) {
									dglDeleteTextures(1, &pTexture->textureDoubleBuff); }

	KLBDELETE(pTexture);
	pTexture = null;
	return pTexture;
}

bool CKLBOGLWrapper::supportFrame() {
	klb_assertAlways("TODO");
	return false;
}

void CKLBOGLWrapper::setRenderFrame(CFrame* pFrame) {
	klb_assert(supportFrame(), "System does not support offscreen buffers");
#ifndef OPENGL2
    pFrame = pFrame;
	klb_assertAlways("TODO");
#else
	// Done
	if (pFrame) {
		dglBindFramebuffer(GL_FRAMEBUFFER, pFrame->frameBuffID);
	} else {
		// Screen direct.
		dglBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
#endif
}

CImageBuffer* CKLBOGLWrapper::createImageBuffer(s32 /*width*/, s32 /*height*/, GLenum /*internalformat*/) {
	CImageBuffer* pBuffer;
	klb_assert(supportFrame(), "System does not support offscreen buffers");
#ifndef OPENGL2
	klb_assertAlways("TODO");
	pBuffer = NULL;
#else
	// Done
	pBuffer = KLBNEW(CImageBuffer);
	if (pBuffer) {
		GLuint buf;
		dglGenRenderbuffers(1, &buf);
		if (buf) {
			pBuffer->buffer	= buf;
			pBuffer->next	= imgBufferList;
			imgBufferList	= pBuffer;
		}
		KLBDELETE(pBuffer);
	}
#endif
	return pBuffer;
}

void CKLBOGLWrapper::releaseImageBuffer(CImageBuffer* imageBuffer) {
	CImageBuffer* p = this->imgBufferList;
	CImageBuffer* prev = null;
	while (p != imageBuffer) {
		prev = p;
		p = p->next;
	}

	if (prev == null) {
		this->imgBufferList = p->next;
	} else {
		prev->next = p->next;
	}

#ifndef OPENGL2
	klb_assertAlways("TODO");
#else
	// Done
	dglDeleteRenderbuffers(1, &imageBuffer->buffer);
#endif
}

CFrame* CKLBOGLWrapper::createFrame() {
	CFrame* pFrame;
	klb_assert(supportFrame(), "System does not support offscreen buffers");
#ifndef OPENGL2
	klb_assertAlways("TODO");
	pFrame = NULL;
#else
	// Done
	pFrame = KLBNEW(CFrame);
	if (pFrame) {
		GLuint buf;
		dglGenFramebuffers(1, &buf);
		if (buf) {
			pFrame->frameBuffID	= buf;
			pFrame->next	= frameList;
			frameList		= pFrame;
		}
		KLBDELETE(pFrame);
	}
#endif
	return pFrame;
}

void CKLBOGLWrapper::releaseFrame(CFrame* pFrame) {
	CFrame* p = this->frameList;
	CFrame* prev = null;
	while (p != pFrame) {
		prev = p;
		p = p->next;
	}

	if (prev == null) {
		this->frameList = p->next;
	} else {
		prev->next = p->next;
	}

#ifndef OPENGL2
	klb_assertAlways("TODO");
#else
	// Done
	dglDeleteFramebuffers(1, &pFrame->frameBuffID);
#endif

	if (pFrame) {
		KLBDELETE(pFrame);
	}
}

bool CKLBOGLWrapper::copyScreenRGB888(u32 srcx, u32 srcy, u32 width,u32 height,u8* buffer) {
	dglReadPixels(srcx,srcy,width,height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	if (dglGetError()) {
		return false;
	}
	return true;
}


SRenderState::SRenderState()
:blendEnable			(UNDEFINED_BOOL)
,blendSrcFactor			(0)
,blendDstFactor			(0)
,blendOp				(0xFF)

,alphaTestEnable		(UNDEFINED_BOOL)

,depthWriteEnable		(UNDEFINED_BOOL)
,depthTestEnable		(UNDEFINED_BOOL)
,depthFunction			(0xFF)

,stRefOpCW				(ALWAYS)
,stRefOpCCW				(ALWAYS)
,stRefValueCW			(0)
,stRefValueCCW			(0)
,stReadMaskCCW			(0)
,stReadMaskCW			(0)

,textMode				(UNDEFINED_BOOL)

,changed				(true)
{
	scX					= 0;
	scY					= 0;
	scW					= 0;
	scH					= 0;
	bEnableScissor		= false;
	alphaFunction		= 0;
	alphaValue			= 0;

	stWriteMaskCW				= 0;
	stWriteMaskCCW				= 0;
	stWriteFailS_StencilOP_CW  = ZERO;
	stWriteFailZ_StencilOP_CW  = ZERO;
	stWriteSuccZ_StencilOP_CW  = ZERO;
	stWriteFailS_StencilOP_CCW = ZERO;
	stWriteFailZ_StencilOP_CCW = ZERO;
	stWriteSuccZ_StencilOP_CCW = ZERO;
}

void SRenderState::dump() {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	SRenderState* pState = this;
	if (pState->bEnableScissor == 0) {
		fprintf(pFile," Scissor None");
	} else if (pState->bEnableScissor == 1) {
		fprintf(pFile," Scissor ACTIVE");
	} else if (pState->bEnableScissor == 2) {
		fprintf(pFile," Ignore Scissor");
	} else {
		fprintf(pFile," -Invalid Scissor-");
	}

	if (pState->blendEnable == 0) {
		fprintf(pFile," Blend None");
	} else if (pState->blendEnable == 1) {
		fprintf(pFile," Blend ACTIVE");
	} else if (pState->blendEnable == 2) {
		fprintf(pFile," Ignore Blend");
	} else {
		fprintf(pFile," -Invalid Blend-");
	}

	if (pState->alphaTestEnable == 0) {
		fprintf(pFile," Alpha Test None");
	} else if (pState->alphaTestEnable == 1) {
		fprintf(pFile," Alpha Test ACTIVE");
	} else if (pState->alphaTestEnable == 2) {
		fprintf(pFile," Ignore Alpha Test");
	} else {
		fprintf(pFile," -Invalid Alpha Test-");
	}
			
	if (pState->alphaTestEnable == 0) {
		fprintf(pFile," Alpha Test None");
	} else if (pState->alphaTestEnable == 1) {
		fprintf(pFile," Alpha Test ACTIVE");
	} else if (pState->alphaTestEnable == 2) {
		fprintf(pFile," Ignore Alpha Test");
	} else {
		fprintf(pFile," -Invalid Alpha Test-");
	}
			
	if (pState->depthWriteEnable == 0) {
		fprintf(pFile," Depth Write None");
	} else if (pState->depthWriteEnable == 1) {
		fprintf(pFile," Depth Write ACTIVE");
	} else if (pState->depthWriteEnable == 2) {
		fprintf(pFile," Ignore Depth Write");
	} else {
		fprintf(pFile," -Invalid Depth Write-");
	}

	if (pState->depthTestEnable == 0) {
		fprintf(pFile," Depth Test None");
	} else if (pState->depthTestEnable == 1) {
		fprintf(pFile," Depth Test ACTIVE");
	} else if (pState->depthTestEnable == 2) {
		fprintf(pFile," Ignore Depth Test");
	} else {
		fprintf(pFile," -Invalid Depth Test-");
	}
}

void SRenderState::setTextMode(bool active) {
	textMode	= active ? TRUE_BOOL_U8 : FALSE_BOOL_U8;
	changed		= true;
}

void SRenderState::setBlend(BLEND_MODE mode) {
	switch (mode) {
	case NO_ALPHA:
		blendEnable		= false;
		break;
	case ALPHA:
		blendEnable		= true;
		blendSrcFactor	= GL_SRC_ALPHA;
		blendDstFactor	= GL_ONE_MINUS_SRC_ALPHA;
		blendOp			= ADD;
		break;
	case ADDITIVE:
		blendEnable		= true;
		blendSrcFactor	= GL_SRC_ALPHA;
		blendDstFactor	= GL_ONE;
		blendOp			= ADD;
		break;
    case ADDITIVE_ALPHA: 
		blendEnable		= true;
		blendSrcFactor	= GL_ONE;
		blendDstFactor	= GL_ONE_MINUS_SRC_ALPHA;
		break;
	}
	changed = true;
}

void SRenderState::setDepthState(bool write, bool test, DEPTH_OP op) {
	if (write) {
		depthWriteEnable = GL_TRUE;
	} else {
		depthWriteEnable = GL_FALSE;
	}

	depthTestEnable = test;
	depthFunction	= op;
	changed = true;
}

void SRenderState::setBlendAdvance(BLEND_SRC src, BLEND_DST dst, BLEND_OP src_op_dst) {
	blendEnable		= true;
	blendSrcFactor	= src;
	blendDstFactor	= dst;
	blendOp			= src_op_dst;
	changed = true;
}

void SRenderState::setStencilTestCW(u32 readMask, u32 refValue, DEPTH_OP compare_op) {
	stReadMaskCW	= readMask;
	stRefValueCW	= refValue;
	stRefOpCW		= compare_op;
	changed = true;
}

void SRenderState::setStencilTestCCW(u32 readMask, u32 refValue, DEPTH_OP compare_op) {
	stReadMaskCCW	= readMask;
	stRefValueCCW	= refValue;
	stRefOpCCW		= compare_op;
	changed = true;
}

void SRenderState::setStencilWriteCW(u32 writeMask, STENCIL_OP opFailStencil, STENCIL_OP opFailZ, STENCIL_OP opSucceed) {
	stWriteMaskCW				= writeMask;
	stWriteFailS_StencilOP_CW	= opFailStencil;
	stWriteFailZ_StencilOP_CW	= opFailZ;
	stWriteSuccZ_StencilOP_CW	= opSucceed;
	changed = true;
}

void SRenderState::setStencilWriteCCW(u32 writeMask, STENCIL_OP opFailStencil, STENCIL_OP opFailZ, STENCIL_OP opSucceed) {
	stWriteMaskCCW				= writeMask;
	stWriteFailS_StencilOP_CCW	= opFailStencil;
	stWriteFailZ_StencilOP_CCW	= opFailZ;
	stWriteSuccZ_StencilOP_CCW	= opSucceed;
	changed = true;
}

void SRenderState::enableAlphaTest	(float value, DEPTH_OP compare_op) {
	changed			= true;
	alphaTestEnable = TRUE_BOOL_U8;
	alphaFunction	= compare_op;
	alphaValue		= value;
}

void SRenderState::disableAlphaTest	() {
	changed			= true;
	alphaTestEnable	= FALSE_BOOL_U8;
}

void SRenderState::enableScissor(s32 x, s32 y, s32 w, s32 h) {
	bEnableScissor = TRUE_BOOL_U8;
	scX = x;
	scY = y;
	scW = w;
	scH = h;
	changed = true;
}

void SRenderState::disableScissor() {
	bEnableScissor = false;
	changed = true;
}

void CKLBOGLWrapper::applyState(SRenderState* pState) {
	/*
	//
	// Force render States each call.
	//
	if ((pState->blendEnable != 0) && (pState->blendEnable != UNDEFINED_BOOL)) {
		rState.blendEnable = pState->blendEnable;
		if (rState.blendEnable) {
			dglEnable(GL_BLEND);
			rState.blendSrcFactor = pState->blendSrcFactor;
			rState.blendDstFactor = pState->blendDstFactor;
			dglBlendFunc(rState.blendSrcFactor, rState.blendDstFactor);
		} else {
			dglDisable(GL_BLEND);
		}
	}

	if ((pState->bEnableScissor != 0) && (pState->bEnableScissor != UNDEFINED_BOOL)) {
		rState.bEnableScissor = pState->bEnableScissor;
		if (rState.bEnableScissor) {
			rState.scX = pState->scX;
			rState.scY = pState->scY;
			rState.scW = pState->scW;
			rState.scH = pState->scH;
			dglEnable(GL_SCISSOR_TEST);
			dglScissor(pState->scX, pState->scY, pState->scW, pState->scH);

			// For Testing.
			//dglClearColor(1.0f, 0.2039f, 0.7f, 0.0f);
			//dglClear(GL_COLOR_BUFFER_BIT);
			//
		} else {
			dglDisable(GL_SCISSOR_TEST);
		}
	}*/

	if ((m_pLastState != pState) || (pState->changed)) {
		m_pLastState	= pState;
		pState->changed = false;

#ifndef OPENGL2
		if ((pState->alphaTestEnable != rState.alphaTestEnable) && (pState->alphaTestEnable != UNDEFINED_BOOL)) {
			rState.alphaTestEnable = pState->alphaTestEnable;
			if (rState.alphaTestEnable) {
				dglEnable(GL_ALPHA_TEST);
#ifdef STD_OPENGL
				glAlphaFunc(pState->alphaFunction, pState->alphaValue);
#else
				dglAlphaFuncx(pState->alphaFunction, pState->alphaValue);
#endif
			} else {
				dglDisable(GL_ALPHA_TEST);
			}
		}
#endif

		if ((pState->blendEnable != rState.blendEnable) && (pState->blendEnable != UNDEFINED_BOOL)) {
			rState.blendEnable = pState->blendEnable;
			if (rState.blendEnable) {
				dglEnable(GL_BLEND);
			} else {
				dglDisable(GL_BLEND);
			}
		}

#ifndef OPENGL2
		if ((pState->textMode != rState.textMode) && (pState->textMode != UNDEFINED_BOOL)) {
			rState.textMode = pState->textMode;
			if (pState->textMode) {
				//
				// Activate
				//
				dglTexEnvi( GL_TEXTURE_ENV, GL_SRC0_RGB,  GL_TEXTURE);
				dglTexEnvi( GL_TEXTURE_ENV, GL_SRC1_RGB,  GL_PRIMARY_COLOR);
				dglTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB,  GL_SRC_ALPHA);
				dglTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB,  GL_SRC_COLOR);
				dglTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB,  GL_MODULATE);

				dglTexEnvi( GL_TEXTURE_ENV, GL_SRC0_ALPHA,  GL_TEXTURE);
				dglTexEnvi( GL_TEXTURE_ENV, GL_SRC1_ALPHA,  GL_PRIMARY_COLOR);
				dglTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_ALPHA,  GL_SRC_ALPHA);
				dglTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_ALPHA,  GL_SRC_COLOR);
				dglTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_ALPHA,  GL_MODULATE);

				dglBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				dglTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			} else {
				//
				// Desactivate
				//
				dglTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
		}
#endif

		// If enabled -> Check if we need to modify the blending function.
		if (rState.blendEnable && (pState->blendEnable != UNDEFINED_BOOL)) {
			if ((pState->blendSrcFactor != rState.blendSrcFactor) || (pState->blendDstFactor != rState.blendDstFactor)) {
				rState.blendSrcFactor = pState->blendSrcFactor;
				rState.blendDstFactor = pState->blendDstFactor;
				
				dglBlendFunc(rState.blendSrcFactor, rState.blendDstFactor);
			}

			// Other choice than ADD in OpenGLES 2.0
#ifdef OPENGL2
			if (pState->blendOp != rState.blendOp) {
				rState.blendOp = pState->blendOp;
				switch (rState.blendOp) {
				case SRenderState::ADD:		dglBlendEquation(GL_FUNC_ADD); break;
				case SRenderState::SUB:		dglBlendEquation(GL_FUNC_SUBTRACT); break;
				case SRenderState::REVSUB:	dglBlendEquation(GL_FUNC_REVERSE_SUBTRACT); break;
				}
			}
#endif				
		}
		

		if ((pState->depthWriteEnable != rState.depthWriteEnable) && (pState->depthWriteEnable != UNDEFINED_BOOL)) {
			rState.depthWriteEnable = pState->depthWriteEnable;
			dglDepthMask(rState.depthWriteEnable);
		}

		if ((pState->depthTestEnable != rState.depthTestEnable) && (pState->depthTestEnable != UNDEFINED_BOOL)) {
			rState.depthTestEnable = pState->depthTestEnable;
			if (rState.depthTestEnable) {

				dglEnable(GL_DEPTH_TEST);
			} else {
				dglDisable(GL_DEPTH_TEST);
			}
		}

		if (rState.depthFunction != pState->depthFunction) {
			rState.depthFunction = pState->depthFunction;
			if (rState.depthTestEnable) {
				dglDepthFunc(rState.depthFunction);
			}
		}

		// Stencil Test
		if (((pState->stReadMaskCW | pState->stReadMaskCCW) != (rState.stReadMaskCW | rState.stReadMaskCCW))
			||  (pState->stRefOpCW     != rState.stRefOpCW		)
			||  (pState->stRefOpCCW    != rState.stRefOpCCW		)
			||  (pState->stRefValueCW  != rState.stRefValueCW	)
			||  (pState->stRefValueCCW != rState.stRefValueCCW	)
		   ) {
			rState.stRefOpCW		= pState->stRefOpCW;
			rState.stRefOpCCW		= pState->stRefOpCCW;
			rState.stRefValueCW		= pState->stRefValueCW;
			rState.stRefValueCCW	= pState->stRefValueCCW;
			rState.stReadMaskCCW	= pState->stReadMaskCCW;
			rState.stReadMaskCW		= pState->stReadMaskCW;

			if (pState->stReadMaskCW | pState->stReadMaskCCW) {
				dglEnable(GL_STENCIL_TEST);
		#ifndef OPENGL2
				dglStencilFunc(rState.stRefOpCW, rState.stRefValueCW, rState.stReadMaskCW);
		#else
				dglStencilFuncSeparate(GL_CW, rState.stRefOpCW, rState.stRefValueCW, rState.stReadMaskCW);
				dglStencilFuncSeparate(GL_CCW, rState.stRefOpCCW, rState.stRefValueCCW, rState.stReadMaskCCW);
		#endif
			} else {
				dglDisable(GL_STENCIL_TEST);
			}
		}

		// Stencil write
		/* DISABLE : Non working for now --> Default value not set correctly in constructor.
		if (((pState->stWriteMaskCW | pState->stWriteMaskCCW) != (rState.stWriteMaskCW | rState.stWriteMaskCCW)) 
			|| (pState->stWriteFailS_StencilOP_CW  != rState.stWriteFailS_StencilOP_CW )
			|| (pState->stWriteFailS_StencilOP_CCW != rState.stWriteFailS_StencilOP_CCW)
			|| (pState->stWriteFailZ_StencilOP_CW  != rState.stWriteFailZ_StencilOP_CW )
			|| (pState->stWriteFailZ_StencilOP_CCW != rState.stWriteFailZ_StencilOP_CCW)
			|| (pState->stWriteSuccZ_StencilOP_CW  != rState.stWriteSuccZ_StencilOP_CW )
			|| (pState->stWriteSuccZ_StencilOP_CCW != rState.stWriteSuccZ_StencilOP_CCW)
			) {
			rState.stWriteMaskCCW	= pState->stWriteMaskCCW;
			rState.stWriteMaskCW	= pState->stWriteMaskCW;
			if (rState.stWriteMaskCW | rState.stWriteMaskCCW) {
		#ifndef OPENGL2
				dglStencilOp(rState.stWriteFailS_StencilOP_CW, rState.stWriteFailZ_StencilOP_CW, rState.stWriteSuccZ_StencilOP_CW);
				dglStencilMask(rState.stWriteMaskCW);
		#else
				dglStencilOpSeparate(GL_CW , rState.stWriteFailS_StencilOP_CW , rState.stWriteFailZ_StencilOP_CW , rState.stWriteSuccZ_StencilOP_CW );
				dglStencilOpSeparate(GL_CCW, rState.stWriteFailS_StencilOP_CCW, rState.stWriteFailZ_StencilOP_CCW, rState.stWriteSuccZ_StencilOP_CCW);
				dglStencilMaskSeparate(GL_CW, rState.stWriteMaskCW);
				dglStencilMaskSeparate(GL_CCW, rState.stWriteMaskCCW);
		#endif
			} else {
				dglStencilMask(0);	// No stencil write authorized.
			}
		}
		*/

		if ((pState->bEnableScissor != rState.bEnableScissor) && (pState->bEnableScissor != UNDEFINED_BOOL)) {
			rState.bEnableScissor = pState->bEnableScissor;
			if (rState.bEnableScissor) {
				rState.scX = pState->scX;
				rState.scY = pState->scY;
				rState.scW = pState->scW;
				rState.scH = pState->scH;
				dglEnable(GL_SCISSOR_TEST);
				dglScissor(pState->scX, pState->scY, pState->scW, pState->scH);

				// For Testing.
				//dglClearColor(1.0f, 0.2039f, 0.7f, 0.0f);
				//dglClear(GL_COLOR_BUFFER_BIT);
				//
			} else {
				dglDisable(GL_SCISSOR_TEST);
			}
		}
	}
}

void CKLBOGLWrapper::resetSampler(s32 sampler) {
	samplerUnit[sampler].texture = 0; // No texture assigned.
}

void CKLBOGLWrapper::assignSampler(CTextureUsage* pTextureInstance, s32 sampler) {
	GLuint textureID = pTextureInstance->pTexture->pMaster->activeTexture;
	// Main draw loop setup outside.
	// dglActiveTexture(GL_TEXTURE0 + sampler);

	
	if (samplerUnit[sampler].texture != textureID) {
		samplerUnit[sampler].texture = textureID;
		dglBindTexture(GL_TEXTURE_2D, textureID);
	}

	if (pTextureInstance->samplingSetupDone == false) {
		pTextureInstance->samplingSetupDone = true;
		dglTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pTextureInstance->minSampling);
		dglTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pTextureInstance->maxSampling);

		dglTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pTextureInstance->uMode);
		dglTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pTextureInstance->vMode);
	}
}

