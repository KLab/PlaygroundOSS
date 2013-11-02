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
#include "CKLBTexturePacker.h"
#include "ArrayAllocator.h"
#include "CKLBUtility.h"

//
// Flag to decide if we update the texture for each sub surface individually
// or check a change flag just before rendering. (Compile option for now but wanted to avoid #define)
// Some device on android did not react well to the fact of executing lots of texture change.
// Because we use a prebuffer software texture, we use now twice the amount of memory in exchange.
//
const bool g_useSWBuffer = true;

/*static*/ u8 TexturePacker::s_currentTextureMode = STARTUP_FORMAT;

// =====================================
//	Private Data Structure.
// =====================================
struct PackNode {
	PackNode(ArrayAllocator<PackNode>* pAlloc);
	~PackNode();
	
	static void* operator new		(size_t size, ArrayAllocator<PackNode>* pAlloc); 
	static void  operator delete	(void *p);
 
	PackNode*	clone();

	ArrayAllocator<PackNode>*	allocCtx;
	PackNode*	lft;
	PackNode*	rgt;
	u16 		x;
	u16 		y;
	u16 		w;
	u16 		h;
	bool		used;
};

typedef	ArrayAllocator<PackNode>	AllocNode;

/*static*/ void* PackNode::operator new		(size_t /*size*/, AllocNode* pAlloc)
{
	// Ignore size, we are fixed size type here.
	return pAlloc->allocEntry();
}

/*static*/ void  PackNode::operator delete	(void *p)
{
	((PackNode*)p)->allocCtx->freeEntry((PackNode*)p);
}

class Packer {
public:
	Packer ();
	~Packer();
	
	void setSize			(u16  width, u16  height);
	void getDimension		(u16& width, u16& height);
	bool findCoord			(u16 w, u16 h, u16& x, u16& y);
protected:
	u16 		usedWidth;
	u16 		usedHeight;
	PackNode*	root;
	ArrayAllocator<PackNode>	allocator;

	bool findCoordRec		(PackNode* node, u16 w, u16 h, u16& x, u16& y);
};

struct SPixel {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
};

struct SSurface {
	compact		cbCompactFunc;
	void*		ownerCtx;
	CKLBSprite*	m_sprite;
	u8*			swBuffer;
	u16			w;
	u16			h;
	u16			alloc_w;
	u16			alloc_h;

	u16			x;
	u16			y;
	// bool		flip;
	// bool		oldflip;
	bool		free;
};

// Maximum 2048 (12 bit on 16 bit index)
#define SURFACE_MAX	(1000)

// One instance per texture.
class TexturePackerOnce {
	friend class TexturePacker;
public:
	bool init				(u16 width,			u16 height, u16 mode);
	void reset				();
	void release			();
	void dump				(bool detail);
#ifdef DEBUG_TEXTURE_PACKER
	void scan				(void* ctx);
#endif

	void unloadSurfaces		();
	void reloadSurfaces		();
	u16  allocateSurface	(CKLBSprite* spr,	u16 w,		u16 h	,void* ptrOwner,compact cbCompaction, TexturePackerOnce** ppRealAlloc);
	u16	 reallocateSurface	(u16 surface,		u16 w,		u16 h	,TexturePackerOnce** ppRealAlloc);
	void releaseSurface		(u16 surface);
	void getSurfaceInfo		(u16 surface,		u32*& pixel, float& u0, float& v0, float& u1, float& v1, float& stepU, float& stepV);
	CTextureUsage*
		 getTextureUsage	()	{ return m_textureUsage;	}
	u16	 getSurfaceStride	()	{ return m_width;			}
	CKLBSprite* getSprite	(u16 surface)	{ return m_surface[surface].m_sprite;		}
	void*		getOwnerCtx	(u16 surface)	{ return m_surface[surface].ownerCtx;		}
	compact		getOwnerCB	(u16 surface)	{ return m_surface[surface].cbCompactFunc;	}
	void updateTexture		(u16 surface);
	u16				marker;
private:
	Packer			m_packer;
	u16				m_width;
	u16				m_height;
	CTexture*		m_texture;
	CTextureUsage*	m_textureUsage;
	u8*				m_swBuffer;
	u32				m_unit;
	u32				m_format;
	u32				m_totalSurface;
	u32				m_freeSurface;
	u16				m_startYChange;
	u16				m_endYChange;

	// Global
	SSurface	m_surface[SURFACE_MAX];
	u16			m_surfaceCount;
	u16			m_currFormat;

	bool simpleAllocInternal(CKLBSprite* spr, u16 x, u16 y, u16 w, u16 h, s16& found);
	void moveImage			(u16 id);
	void refreshTexture		();
};


// =====================================
//	PackNode
// =====================================

PackNode::PackNode(ArrayAllocator<PackNode>*	allocCtx)
: lft		(NULL)
, rgt		(NULL)
, allocCtx	(allocCtx)
, used		(false)
{
}

PackNode::~PackNode() {
	// Specific allocator, do NOT use KLBDELETE macro.
	delete lft;
	delete rgt;
}

PackNode* PackNode::clone() {
	// Specific allocator, do NOT use KLBNEW macro.
	PackNode* pNew = new(allocCtx) PackNode(allocCtx);
	if (pNew) {
		pNew->x = this->x;
		pNew->y = this->y;
		pNew->w = this->w;
		pNew->h = this->h;
	}
	return pNew;
}

// =====================================
//	Packer
// =====================================

Packer::Packer() {
	if (allocator.init(SURFACE_MAX * 2)) {
		root = new(&allocator) PackNode(&allocator);
		setSize	(0, 0);
	}
}

Packer::~Packer() {
	// Do NOT use KLBDELETE for PackNode
	delete root;
}

void Packer::setSize(u16 width, u16 height) {
	root->x	= 0;
	root->y	= 0;
	root->w	= width;
	root->h	= height;
	
	delete root->lft;
	delete root->rgt;
	
	root->lft	= NULL;
	root->rgt	= NULL;
	
	usedWidth	= 0;
	usedHeight	= 0;
}

void Packer::getDimension(u16& refWidth, u16& refHeight) {
	refWidth 	= usedWidth;
	refHeight	= usedHeight;
}

bool Packer::findCoord	(u16 w, u16 h, u16& x, u16& y) {
	if (findCoordRec(root, w, h, x, y)) {
		if (usedWidth  < (x + w)) 	{ usedWidth  = x + w; }
		if (usedHeight < (y + h))	{ usedHeight = y + h; }
		return true;
	} else {
		return false;
	}
}

bool Packer::findCoordRec(PackNode* node, u16 w, u16 h, u16& x, u16& y) {
	if (node->lft) {
		if (findCoordRec(node->lft,w,h,x,y)) {
			return true;
		} else {
			return findCoordRec(node->rgt,w,h,x,y);
		}
	} else {
		// if already used or it's too big then return
		if (node->used || (w > node->w) || (h > node->h)) {
			return false;
		}
		
		// if it fits perfectly then use this gap
		if ((w == node->w) && (h == node->h)) {
			node->used	= true;
			x 			= node->x;
			y 			= node->y;
			return true;
		}
		
		// initialize the left and right leafs by clonning the current one
		node->lft = node->clone();
		node->rgt = node->clone();
		
		// checks if we partition in vertical or horizontal
		if ((node->w - w) > (node->h - h)) {
			node->lft->w = w;
			node->rgt->x = node->x + w;
			node->rgt->w = node->w - w;	
		} else {
			node->lft->h = h;
			node->rgt->y = node->y + h;
			node->rgt->h = node->h - h;							
		}

		return findCoordRec(node->lft, w, h, x, y);
	}
}


// =====================================
//	TexturePackerOnce
// =====================================

bool TexturePackerOnce::init(u16 width, u16 height, u16 mode) {
	klb_assert((CKLBUtility::nearest2Pow(width ) == width ), "invalid power of two size");
	klb_assert((CKLBUtility::nearest2Pow(height) == height), "invalid power of two size");

	CKLBOGLWrapper::TEX_CHANNEL format;
	u32 unit;
	switch (mode) {
	case FORMAT_8888:
		format	= CKLBOGLWrapper::RGBA;
		unit	= GL_UNSIGNED_BYTE;
		break;
	case FORMAT_4444:
		format	= CKLBOGLWrapper::RGBA;
		unit	= GL_UNSIGNED_SHORT_4_4_4_4;
		break;
	case FORMAT_8:
		format	= CKLBOGLWrapper::LUMINANCE;
		unit	= GL_UNSIGNED_BYTE;
		break;
	default:
		format	= CKLBOGLWrapper::RGBA;	// Just for compiler warning.
		unit	= 0;
		klb_assertAlways("Invalid texture format for TexturePacker.");
	}

	m_currFormat = mode;

	if (g_useSWBuffer) {
		m_swBuffer	= KLBNEWA(u8, width * height * m_currFormat);
	}
	if ((m_swBuffer && g_useSWBuffer) || (g_useSWBuffer == false)) {
		CTexture* pTex	= CKLBOGLWrapper::getInstance().createTexture(width, height, unit, format, NULL, 0, CKLBOGLWrapper::TEX_NONE);
		if (pTex) {
			m_unit			= unit;
			m_format		= format;
			m_startYChange	= 0x4000;
			m_endYChange	= 0;
			m_texture		= pTex;
			m_textureUsage	= pTex->createUsage();
			m_surfaceCount	= 0;
			m_width			= width;
			m_height		= height;

			reset();

			return (m_textureUsage != NULL);
		}
		if (g_useSWBuffer) {
			KLBDELETEA(m_swBuffer);
			m_swBuffer = NULL;
		}
	}
	return false;
}

void TexturePackerOnce::reset() {
	m_surfaceCount	= 0;
	m_totalSurface	= m_width * m_height;
	m_freeSurface	= m_totalSurface;
	this->m_packer.setSize(m_width,m_height);
}

void TexturePackerOnce::release() {
	for (int n = 0 ; n < m_surfaceCount; n++) {
		KLBDELETEA(m_surface[n].swBuffer);
	}

	if (m_swBuffer && g_useSWBuffer) {
		KLBDELETEA(m_swBuffer);
		m_swBuffer = NULL;
	}

	if (m_textureUsage) {
		m_texture->releaseUsage(m_textureUsage);
		m_textureUsage = NULL;
	}

	if (m_texture) {
		CKLBOGLWrapper::getInstance().releaseTexture(m_texture);
		m_texture = NULL;
	}
}

void TexturePackerOnce::dump(bool detail) {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	fprintf(pFile, "==== Surface Alloc %8lX Size W:%i, H:%i Byte/Pix: %i ====\n", reinterpret_cast<uintptr_t>(this), m_width, m_height, m_currFormat);
	u32 totalSurface	= m_width * m_height;
	u32 usedSurface		= 0;
	u32 allocSurface	= 0;
	for (int n = 0; n < m_surfaceCount; n++) {
		if (m_surface[n].free) {
			if (detail) { printf("! "); }
		} else {
			if (detail) { printf("  "); }
			allocSurface += m_surface[n].alloc_w * m_surface[n].alloc_h; 
			usedSurface  += m_surface[n].w * m_surface[n].h; 
			if (detail) {
				// writeSurface(&m_surface[n], n, this);
			}
		}

		if (detail) {
			fprintf(pFile, "[%4i] AW:%4i(%4i) AH:%4i(%4i) X:%4i Y:%4i\n",	
															n,
															m_surface[n].alloc_w,
															m_surface[n].w,
															m_surface[n].alloc_h,
															m_surface[n].h,
															m_surface[n].x,
															m_surface[n].y);
		}
	}

	if (totalSurface) {
		fprintf(pFile, " Total : %i(100%%) Allocated : %i (%f) Used : %i (%f)\n",
			totalSurface,
			allocSurface,
			(allocSurface*100.0) / totalSurface,
			usedSurface,
			(usedSurface*100.0) / totalSurface
		);
	}

	fprintf(pFile, "==== Surface Alloc End =====\n");
}

#define INTERNAL_DUMP_TEXPACKER			/*dump(bool detail)*/;

void TexturePacker::unloadSurface() {
	for (int n=0; n<MAX_TEXTURES ; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (pCurr) {
			pCurr->unloadSurfaces();
		}
	}
}

void TexturePacker::reloadSurfaces() {
	for (int n=0; n<MAX_TEXTURES ; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (pCurr) {
			pCurr->reloadSurfaces();
		}
	}
}

void TexturePackerOnce::unloadSurfaces() {
	this->m_texture->makeEmptyShell();
}

void TexturePackerOnce::reloadSurfaces() {
	//
	// Allocate new texture
	//
	this->m_texture	= CKLBOGLWrapper::getInstance().createTexture(m_width, m_height, m_unit, (CKLBOGLWrapper::TEX_CHANNEL)m_format, NULL, 0, CKLBOGLWrapper::TEX_NONE,0,m_texture);

	//
	// Force SW -> texture
	//
	for (u16 n=0; n < this->m_surfaceCount; n++) {
		if (m_surface[n].free == false) {
			moveImage(n);
		}
	}
}

u16 TexturePackerOnce::allocateSurface(CKLBSprite* spr, u16 w, u16 h, void* ptrOwner,compact cbCompaction, TexturePackerOnce** ppRealAlloc) {
	u16 x = 0;
	u16 y = 0;
	*ppRealAlloc = this;
	s16 foundIdx;
	if (simpleAllocInternal(spr,x,y,w,h, foundIdx)) {

		// Item allocate succeed.
		bool res;
		if (foundIdx < 0) {
			res = m_packer.findCoord(w+2,h+2,x,y);
		} else {
			x = m_surface[foundIdx].x-1; // Because we add + 1
			y = m_surface[foundIdx].y-1;
			res = true;
		}

		if (res) {	// Add 1 pixel border around the buffer.
			u16 update = (foundIdx < 0) ? m_surfaceCount-1 : foundIdx;
			
			//	[.] Partial update of texture to GPU only for new item.
			/*  Caller to main allocator does it.
				*ptrOwner = update | this->marker;
			 */
			m_surface[update].x = x+1;	// X and Y point to the correct binding in texture including border (allow correct UV get)
			m_surface[update].y = y+1;
			m_surface[update].cbCompactFunc = cbCompaction;
			m_surface[update].ownerCtx = ptrOwner;
			m_freeSurface	-= (w+2) * (h+2);
			INTERNAL_DUMP_TEXPACKER;
			return update;
		} else {
			// Item allocate FAILED.
			u16 originalCount = m_surfaceCount - 1;
			
			// Get just allocated buffer.
			u8* buffer = m_surface[m_surfaceCount-1].swBuffer;
			m_surface[m_surfaceCount-1].free		= true; // Not necessary but cleaner.

			//	[.] Clear packer tree.
			m_packer.setSize(m_width,m_height);
		
			//	[.] For each already existing entry, register again
			u16 write = 0;

			TexturePacker& packer = TexturePacker::getInstance();
			packer.addIgnoreList(this);

			m_freeSurface	= m_totalSurface;
			bool hadFailure = false;
			for (u16 n = 0; n < originalCount; n++) {
				SSurface* pSurf = &m_surface[n];
				
				if (!pSurf->free) {
					bool success = m_packer.findCoord(	pSurf->w+2,
														pSurf->h+2,
														m_surface[n].x,
														m_surface[n].y);
					u16 newSurface;
					if (!success) {
						// CAN NOT RECOMPACT OLD ITEM --> Need to move to another texture.
						newSurface = packer.useOtherAlloc(pSurf->m_sprite, pSurf->w, pSurf->h, pSurf->ownerCtx,pSurf->cbCompactFunc);

						if (newSurface == NULL_IDX) {
							// Not enough memory : can not escape from total failure.
							// Avoid leak.
							KLBDELETEA(buffer);
							return NULL_IDX;
						} else {
							u16 localSurface = newSurface & 0xFFF;
							TexturePackerOnce* pOtherTextureAllocator = packer.m_allocatedPacker[(newSurface & 0xF000) >> 12];
							*ppRealAlloc = pOtherTextureAllocator;

							// Get New Surface Definition.
							SSurface* pNewSurf = &pOtherTextureAllocator->m_surface[localSurface];

							// -> Free new buffer allocated for nothing.
							KLBDELETEA(pNewSurf->swBuffer);
							// -> Switch to old buffer = Preserve data.
							pNewSurf->swBuffer = pSurf->swBuffer;

							// Update target Texture with old software buffer.
							pOtherTextureAllocator->moveImage(localSurface);
							pNewSurf->cbCompactFunc(pNewSurf->ownerCtx, n | this->marker, newSurface);

							// Free old surface entry.
							pSurf->free		= true;
							pSurf->swBuffer	= NULL;
							hadFailure = true;
						}
					} else {
						// Shift +1,+1 because our width and height is not W+2 and H+2
						m_surface[n].x++;
						m_surface[n].y++;

						// Perform compaction of freed items.
						m_surface[write] = m_surface[n];

						newSurface = write | this->marker;
						m_surface[write].cbCompactFunc(m_surface[write].ownerCtx, n | this->marker, newSurface);
						// If a displacement in texture occurs, texture must be updated.
						// if ((m_surface[write].x != oldX) || (m_surface[write].y != oldY)) {
							moveImage(write);
						// }
						write++;
					}
					INTERNAL_DUMP_TEXPACKER;

					m_freeSurface	-= (pSurf->alloc_w+2) * (pSurf->alloc_h+2);
				}
			}

			packer.removeIgnoreList(this);

			m_surfaceCount = write; // All reallocate complete -> Restore count.

			// Update texture post compaction all textures even if new item may not fit in.

			if (m_packer.findCoord(w + 2,h + 2,x,y)) {
				INTERNAL_DUMP_TEXPACKER;
				//	[.] Allocation succeed ? == Compaction succeeded.
			
				//	[.] Setup & Render New item
				//      simpleAllocInternal(spr,x,y,w,h); <-- Not done, reuse buffer from previous call.

				*ppRealAlloc	= this;
				SSurface* pSurf = &m_surface[m_surfaceCount++];
				pSurf->x		= x+1;
				pSurf->y		= y+1;
				pSurf->w		= w;
				pSurf->h		= h;
				pSurf->alloc_w	= w;
				pSurf->alloc_h	= h;
				pSurf->m_sprite	= spr;
				pSurf->free		= false;
				pSurf->swBuffer = buffer;
				pSurf->ownerCtx = ptrOwner;
				pSurf->cbCompactFunc = cbCompaction;
				m_freeSurface	-= (w+2) * (h+2);

				return m_surfaceCount - 1;
			} else {

				// klb_assert((_CrtCheckMemory() != 0), "Heap Error !");

				KLBDELETEA(buffer);
				//	[.] FAILED : this texture is full.
				dump(false);

				// klb_assert((_CrtCheckMemory() != 0), "Heap Error !");
				*ppRealAlloc = NULL;
			}
		}
	} else {
		if (foundIdx < 0) {
			m_surfaceCount--;
		} else {
			m_surface[foundIdx].free = true;
		}
	}

	return NULL_IDX;
}

u16 TexturePackerOnce::reallocateSurface(u16 surface, u16 w, u16 h, TexturePackerOnce** ppRealAlloc) {
	SSurface* pSurf = &m_surface[surface];
	if ((h <= pSurf->alloc_h) && (w <= pSurf->alloc_w)) {
		// Surface just got smaller or the same : no reallocation at all.

		// ### TODO Clean differential to avoid garbage ###

		pSurf->h     = h;
		pSurf->w     = w;
		*ppRealAlloc = this;

		return surface;
	} else {
		// Surface is bigger --> Need a new slot.
		u16 newSurface = allocateSurface(pSurf->m_sprite, w, h, pSurf->ownerCtx, pSurf->cbCompactFunc, ppRealAlloc);
		if (newSurface != NULL_IDX) {
			klb_assert(newSurface != surface,"Conflict : reallocation use same surface.");
			// And free the old slot.
			releaseSurface(surface);
		}
		return newSurface;
	}
}

#ifdef DEBUG_TEXTURE_PACKER
void* gGlobalDeleteCtx = NULL;

void TexturePacker::setCurrentDelete(void* ptr) {
	gGlobalDeleteCtx = ptr;
}
#endif

void TexturePackerOnce::releaseSurface(u16 surface) {
	if (surface != NULL_IDX) {
		klb_assert((surface < SURFACE_MAX), "Texture Packer no more surface available");
		SSurface* pSurf			= &m_surface[surface];
		pSurf->free				= true;
		m_freeSurface			+= (pSurf->alloc_w+2) * (pSurf->alloc_h+2);
		KLBDELETEA(pSurf->swBuffer);
		pSurf->swBuffer			= NULL;
		pSurf->cbCompactFunc	= NULL;
#ifdef DEBUG_TEXTURE_PACKER
		klb_assert(pSurf->ownerCtx == gGlobalDeleteCtx, "Different !");
#endif
		pSurf->ownerCtx			= NULL;
		pSurf->m_sprite			= NULL;
	}
}

bool TexturePackerOnce::simpleAllocInternal(CKLBSprite* spr, u16 x, u16 y, u16 w, u16 h, s16& found) {
	//	[.] Store Item
	klb_assert((m_surfaceCount < SURFACE_MAX), "Texture Packer no more surface available");

	found = -1;

	for (u32 n = 0; n < m_surfaceCount; n++) {
		SSurface* pSurf = &m_surface[n];
		// Could later modify to (surfaceW >= w) && (surfaceH >= h) && (w*h >= 80% of surface w*h)
		// 80%-100% reuse should be ok.
		if ((pSurf->free) && (pSurf->w == w) && (pSurf->h == h)) { 
			found = n;
			break;
		}
	}

	u16 idx;
	if (found < 0) {
		idx = m_surfaceCount++;
	} else {
		idx = found;
	}

	SSurface* pSurf = &m_surface[idx];
	if (found < 0) {
		pSurf->x		= x;
		pSurf->y		= y;
	}
	// pSurf->flip		= false;
	pSurf->w		= w;
	pSurf->h		= h;
	pSurf->alloc_w	= w;
	pSurf->alloc_h	= h;
	pSurf->m_sprite	= spr;
	pSurf->free		= false;
	pSurf->swBuffer = KLBNEWA(u8, w * h * m_currFormat);

	return (pSurf->swBuffer != NULL);
}

#include "CKLBTextTempBuffer.h"

void TexturePackerOnce::moveImage(u16 id) {
	// For now does not support any rotation.
	// - Update the sprite.
	SSurface* pSurf = &m_surface[id];

	int yt   = pSurf->y - 1;
	int wt   = pSurf->w + 1;
	int wtp1 = wt + 1;

	if (g_useSWBuffer) {
		//
		// Update software buffer
		//
		u8* pSrc = pSurf->swBuffer;
		u8* pDst = &m_swBuffer[(pSurf->x + ((pSurf->y)*m_texture->getWidth())) * m_currFormat];
		// Fill upper line
		memset(pDst - ((m_texture->getWidth()+1) * m_currFormat), 0, wtp1 * m_currFormat);
		for (int y = 0; y < pSurf->h; y++) {
			memcpy(pDst,pSrc,pSurf->w * m_currFormat);
			// Left Side
			if (m_currFormat == 4) {
				pDst[-4] = 0;
				pDst[-3] = 0;
			}
			pDst[-2] = 0;
			pDst[-1] = 0;
	
			// Right Side
			u8* tmp = &pDst[pSurf->w * m_currFormat];
			if (m_currFormat == 4) {
				*tmp++ = 0;
				*tmp++ = 0;
			}
			*tmp++ = 0;
			*tmp++ = 0;
	
			pSrc += pSurf->w * m_currFormat;
			pDst += m_texture->getWidth() * m_currFormat;
		}
		// Fill lower line
		memset(pDst - m_currFormat, 0, wtp1 * m_currFormat);
	
		if (yt < m_startYChange)	{	m_startYChange = yt;	}
		yt += pSurf->h + 2;
		if (yt > m_endYChange)		{	m_endYChange   = yt;	}
	} else {
		int xt = pSurf->x - 1;
		int ht = pSurf->h + 1;
		int htp1 = ht + 1;

		// Top left rect at x,y
		u32 sz = pSurf->w > pSurf->h ? wtp1 : htp1;
		u8* ptrNull = CKLBTextTempBuffer::reallocateBuffer(sz,1,4);
		memset(ptrNull, 0, sz * 4);

		// fill edges OUTSIDE the user texture.
		m_texture->updateTexture(xt, yt       , wtp1, 1, ptrNull, m_currFormat * htp1);
		m_texture->updateTexture(xt, yt + ht  , wtp1, 1, ptrNull, m_currFormat * htp1);
		m_texture->updateTexture(xt       , yt, 1, htp1, ptrNull, m_currFormat * wtp1);
		m_texture->updateTexture(xt + wt  , yt, 1, htp1, ptrNull, m_currFormat * wtp1);

		m_texture->updateTexture(
			pSurf->x,
			pSurf->y,
			pSurf->w,
			pSurf->h,
			pSurf->swBuffer,
			m_currFormat * pSurf->w * pSurf->h
		);
	}

}
/*
#include "CKLBTextTempBuffer.h"

void TexturePackerOnce::moveImage(u16 id) {
	// For now does not support any rotation.
	// - Update the sprite.
	SSurface* pSurf = &m_surface[id];

	u8* buff = CKLBTextTempBuffer::reallocateBuffer((pSurf->w + 2), (pSurf->h + 2), this->m_currFormat);

	memset(buff, 0, (pSurf->w + 2) * (pSurf->h + 2) * this->m_currFormat);

	if (buff) {
		//
		// Copy with border set to "0"
		//
		//
		//
		//				. is source buffer
		//				@ is border we create inside the texture.
		//
		//		@@@@@@@@@@@@@@
		//		@............@
		//		@............@
		//		@............@
		//		@............@
		//		@............@
		//		@@@@@@@@@@@@@@
		//

		u32 strideSrc  = pSurf->w * this->m_currFormat;
		u32 strideDest = strideSrc + (this->m_currFormat<<1);	// + Left and right border

		// Fill Rect
		if (this->m_currFormat == 2) {
			#ifdef INTERNAL_FILL_WITH_COLOR_TEXPACKER
				#define FILL_COLOR_4444		(0xF00F)
			#else
				#define FILL_COLOR_4444		(0x0)
			#endif
			// Top edge
			u16* buffFill	= (u16*)buff;
			u16* endBuffFill= &buffFill[(pSurf->w + 2)];
			while (buffFill != endBuffFill) {
				*buffFill++ = FILL_COLOR_4444;
			}

			// Bottom edge
			buffFill = (u16*)buff;
			buffFill = &buffFill[(strideDest >> 1)*(pSurf->h+1)];
			endBuffFill= &buffFill[(pSurf->w + 2)];
			while (buffFill != endBuffFill) {
				*buffFill++ = FILL_COLOR_4444;
			}

			// Left Edge
			// Right Edge
			buffFill = (u16*)buff;
			buffFill = &buffFill[(strideDest >> 1)];
			endBuffFill= &buffFill[(strideDest >> 1)*pSurf->h];
			u32 step = (strideDest >> 1);
			while (buffFill != endBuffFill) {
				buffFill[0]				= FILL_COLOR_4444;
				buffFill[pSurf->w+1]	= FILL_COLOR_4444;
				buffFill += step;
			}

			#undef FILL_COLOR_4444

		} else {
			klb_assert(this->m_currFormat == 4, "INVALID PIXEL FORMAT");

			#ifdef INTERNAL_FILL_WITH_COLOR_TEXPACKER
				#define FILL_COLOR_32		(0xFF0000FF)
			#else
				#define FILL_COLOR_32		(0)
			#endif

			// Top edge
			u32* buffFill	= (u32*)buff;
			u32* endBuffFill= &buffFill[(pSurf->w + 2)];
			while (buffFill != endBuffFill) {
				*buffFill++ = FILL_COLOR_32;
			}

			// Bottom edge
			u32 step = (strideDest >> 2);
			buffFill = (u32*)buff;
			buffFill = &buffFill[step*(pSurf->h+1)];
			endBuffFill= &buffFill[(pSurf->w + 2)];
			while (buffFill != endBuffFill) {
				*buffFill++ = FILL_COLOR_32;
			}

			// Left Edge
			// Right Edge
			buffFill = (u32*)buff;
			buffFill = &buffFill[step];
			endBuffFill= &buffFill[step*pSurf->h];
			while (buffFill != endBuffFill) {
				buffFill[0]				= FILL_COLOR_32;
				buffFill[pSurf->w+1]	= FILL_COLOR_32;
				buffFill += step;
			}

			#undef FILL_COLOR_32
		}

		// Copy inside
		u8* buffFill	= &buff[strideDest + this->m_currFormat];
		u8* buffSrc		= pSurf->swBuffer;

		for (int y=0; y < pSurf->h; y++) {
			memcpy(buffFill, buffSrc, this->m_currFormat * pSurf->w);
			buffFill += strideDest;
			buffSrc  += strideSrc;
		}

		// Setup the buffer to include
		m_texture->updateTexture(
			pSurf->x - 1,
			pSurf->y - 1,
			pSurf->w + 2,
			pSurf->h + 2,
			buff,
			m_currFormat * (pSurf->w+2) * (pSurf->h+2)
		);
	} else {
		klb_assertAlways("Allocation error");
	}
}
*/

void TexturePackerOnce::updateTexture(u16 surface) {
	moveImage(surface);
}

void TexturePackerOnce::getSurfaceInfo(u16 surface, u32*& pixel, float& u0, float& v0, float& u1, float& v1, float &stepU, float &stepV) {
	klb_assert((surface < m_surfaceCount), "Texture Packer no more surface available");
	klb_assert((m_surface[surface].free == false), "Error : Try to access freed object");
	float w = ((float)this->m_width );
	float h = ((float)this->m_height);

	pixel	= (u32*)m_surface[surface].swBuffer;
	u0		= m_surface[surface].x / w;
	v0		= m_surface[surface].y / h;
	u1		= (m_surface[surface].x + m_surface[surface].w) / w;
	v1		= (m_surface[surface].y + m_surface[surface].h) / h;
	stepU	= 1.0f / w;
	stepV	= 1.0f / h;
}

void TexturePackerOnce::refreshTexture() {
	int height = m_endYChange - m_startYChange;
	m_texture->updateTexture(
		0,
		m_startYChange,
		m_texture->getWidth(),
		height,
		&m_swBuffer[m_startYChange * m_texture->getWidth() * m_currFormat],
		m_texture->getWidth() * height * m_currFormat);

	m_startYChange	= 0x4000;
	m_endYChange	= 0;
}

void TexturePacker::refreshTextures() {
	if (g_useSWBuffer == false) { return; }

	for (int n = 0; n < MAX_TEXTURES ; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (pCurr && (pCurr->m_startYChange < pCurr->m_endYChange)) {
			pCurr->refreshTexture();
		}
	}
}

// =====================================
//	TexturePacker
// =====================================

bool TexturePacker::init(u16 width, u16 height, u16 defaultFormat) {
	klb_assert(CKLBUtility::nearest2Pow(width)  == width , "Not a power of 2.");
	klb_assert(CKLBUtility::nearest2Pow(height) == height, "Not a power of 2.");

	for (int n = 0; n < MAX_TEXTURES; n++) {
		m_allocatedPacker[n] = NULL;
	}

	m_currFormat	= defaultFormat;

	m_lastUsedPacker[FORMAT_8888] = NULL;
	m_lastUsedPacker[FORMAT_4444] = NULL;
	m_lastUsedPacker[FORMAT_8	] = NULL;

	m_width		= width;
	m_height	= height;
	m_update	= NULL_IDX;
	ignoreCount	= 0;

	m_allocatedPacker[0] = KLBNEW(TexturePackerOnce);
	if (m_allocatedPacker[0] && m_allocatedPacker[0]->init(width,height, m_currFormat)) {
		m_lastUsedPacker[m_currFormat]	= m_allocatedPacker[0];
		m_allocatedPacker[0]->marker = 0;
		return true;
	} else {
		return false;
	}
}

void TexturePacker::release() {
	for (int n = 0; n < MAX_TEXTURES; n++) {
		if (m_allocatedPacker[n]) {
			m_allocatedPacker[n]->release();
			KLBDELETE(m_allocatedPacker[n]);
			m_allocatedPacker[n] = NULL;
		}
	}

	m_lastUsedPacker[FORMAT_8888] = NULL;
	m_lastUsedPacker[FORMAT_4444] = NULL;
	m_lastUsedPacker[FORMAT_8	] = NULL;
}

void TexturePacker::dump(bool detail) {
	for (int n = 0; n < MAX_TEXTURES; n++) {
		if (m_allocatedPacker[n]) {
			m_allocatedPacker[n]->dump(detail);
		}
	}
}

TexturePackerOnce* TexturePacker::allocateAllocator(u16 w, u16 h) {
	for (int n = 0; n < MAX_TEXTURES; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (!pCurr) {
			// Create new surface.
			TexturePackerOnce* pNew = KLBNEW(TexturePackerOnce);
			if (pNew) {
				pNew->marker = (u16)(n << 12);

				u32 sw = m_width;
				u32 sh = m_height;

				if ((w > sw) || (h > sh)) {
					sw = CKLBUtility::nearest2Pow(w);
					sh = CKLBUtility::nearest2Pow(h);
				}

				if (pNew && pNew->init((u16)sw, (u16)sh, m_currFormat)) {
					m_allocatedPacker[n] = pNew; 
					return pNew;
				} else {
					KLBDELETE(pNew);
					break;
				}
			} else {
				break;
			}
		}
	}
	return NULL;
}

u32 globalCount = 0;

u16  TexturePacker::allocateSurface(CKLBSprite* spr, u16 w, u16 h, void* ptrOwner,compact cbCompaction) {
	klb_assert(w <= m_width , "Can never allocate surface wider than texture" );
	klb_assert(h <= m_height, "Can never allocate surface higher than texture");

	s64 startTime = CPFInterface::getInstance().platform().nanotime();

	if (m_lastUsedPacker[m_currFormat] == NULL) {
		m_lastUsedPacker[m_currFormat] = allocateAllocator(w,h);	// Allocate (no default mean none available)
		if (!m_lastUsedPacker[m_currFormat]) {
			return NULL_IDX;	// Critical Failure !!! : can not reallocate old items.
		}
	}

	TexturePackerOnce* pOnce = NULL;
	u16 surface = m_lastUsedPacker[m_currFormat]->allocateSurface(spr, w, h, ptrOwner, cbCompaction, &pOnce);
	if (surface != NULL_IDX) {
		klb_assert(pOnce, "null pointer");
		m_update = surface | pOnce->marker;
		klb_assert((m_update & 0xFFF) < pOnce->m_surfaceCount, "Error.");
	} else {
		addIgnoreList(m_lastUsedPacker[m_currFormat]);
		m_update = useOtherAlloc(spr, w, h, ptrOwner, cbCompaction);
		removeIgnoreList(m_lastUsedPacker[m_currFormat]);
		klb_assert(m_update != NULL_IDX, "Allocation did not work. Can not allocate");
	}

	s64 endTime = CPFInterface::getInstance().platform().nanotime();
	float time  = ((endTime - startTime) / 1000000.0f);
	if (time > 1.0f) {	// More than 1 ms.
		DEBUG_PRINT("2D Texture Packer : %5.2f ms",time);
	}

	return m_update;
}

bool TexturePacker::notInIgnoreList(TexturePackerOnce* pack) {
	for (int n = 0; n < ignoreCount; n++) {
		if (pack == ignore[n]) {
			return false;
		}
	}
	return true;
}

void TexturePacker::addIgnoreList(TexturePackerOnce* pack) {
	// Check if not in list already.
	for (int n = 0; n < ignoreCount; n++) {
		if (pack == ignore[n]) {
			return;
		}
	}

	// Add new item to the list.
	ignore[ignoreCount++] = pack;
}

void TexturePacker::removeIgnoreList(TexturePackerOnce* pack) {
	int n;
	for (n = 0; n < ignoreCount; n++) {
		if (pack == ignore[n]) {
			break;
		}
	}

	for (; n < ignoreCount-1; n++) {
		ignore[n] = ignore[n+1];
	}
	ignoreCount--;
}

u16 TexturePacker::useOtherAlloc(CKLBSprite* spr, u16 w, u16 h, void* ptrOwner,compact cbCompaction) {
	// 1. Try to find allocator supporting new allocated size.
	TexturePackerOnce* pRealAlloc = NULL;
	u16 surface;
	u32 max							= w*h;	// Search only bigger than this.
	for (int n = 0; n<MAX_TEXTURES ; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (pCurr && (notInIgnoreList(pCurr)) && (pCurr->m_currFormat == m_currFormat)) {
			if (pCurr->m_freeSurface > max) {
				surface = pCurr->allocateSurface(spr, w, h, ptrOwner, cbCompaction, &pRealAlloc);
				if (surface != NULL_IDX) {
					m_lastUsedPacker[m_currFormat] = pRealAlloc;
					return surface | pRealAlloc->marker;
				}
			}
		}
	}

	// 2. If fail, allocate new surface
	TexturePackerOnce* pOnce = allocateAllocator(w, h);
	if (pOnce) {
		surface = pOnce->allocateSurface(spr, w, h, ptrOwner, cbCompaction, &pRealAlloc);
		// If valid allocation switch to new allocator as default.
		if (surface != NULL_IDX) {
			m_lastUsedPacker[m_currFormat] = pRealAlloc;
			surface |= pRealAlloc->marker;
		}
		return surface;
	} else {
		return NULL_IDX;
	}
}

u16	 TexturePacker::reallocateSurface(u16 surface, u16 w, u16 h) {
	klb_assert(w <= m_width , "Can never allocate surface wider than texture" );
	klb_assert(h <= m_height, "Can never allocate surface higher than texture");

	TexturePackerOnce* pRealAlloc;
	u16 nsurface = m_allocatedPacker[surface>>12]->reallocateSurface(surface & 0xFFF, w,h,&pRealAlloc);
	if (nsurface != NULL_IDX) {
		klb_assert(pRealAlloc, "null pointer");
		m_update = nsurface | pRealAlloc->marker;
		klb_assert((m_update & 0xFFF) < pRealAlloc->m_surfaceCount, "Error.");
	} else {
		u16 surfID = surface & 0xFFF;
		CKLBSprite* pSpr	= m_allocatedPacker[surface>>12]->getSprite  (surfID);
		void*		pRef	= m_allocatedPacker[surface>>12]->getOwnerCtx(surfID);
		compact		cbCompaction = m_allocatedPacker[surface>>12]->getOwnerCB(surfID);
		nsurface = useOtherAlloc(pSpr, w, h, pRef, cbCompaction);
		if (nsurface != NULL_IDX) {
			klb_assert((nsurface & 0xFFF) < m_lastUsedPacker[nsurface>>12]->m_surfaceCount, "Error.");
			// Free old surface if successfull.
			m_allocatedPacker[surface>>12]->releaseSurface(surface);
		} else {
			klb_assertAlways("Allocation did not work. Can not allocate");
		}
		m_update = nsurface;
	}
	
	return m_update;
}

void TexturePacker::releaseSurface(u16 surface) {
	TexturePackerOnce* pPack = m_allocatedPacker[surface>>12];
	pPack->releaseSurface(surface & 0xFFF);

	// Free full surface when empty.
	if (pPack->m_freeSurface == pPack->m_totalSurface) {
		if ((surface>>12) != 0) {
			if (m_lastUsedPacker[pPack->m_currFormat] == m_allocatedPacker[surface>>12]) {
				u32 freeSurface = 0;
				TexturePackerOnce* result = NULL;
				// Search any texture allocator of same format around with maximal free surface
				for (int n = 0; n<MAX_TEXTURES ; n++) {
					TexturePackerOnce* pCurr	= m_allocatedPacker[n];
					if (pCurr && (pCurr != pPack) && (pCurr->m_currFormat == pPack->m_currFormat)) {
						if (pCurr->m_freeSurface > freeSurface) {
							freeSurface = pCurr->m_freeSurface;
							result = pCurr;
						}
					}
				}

				// If not found, none available.
				m_lastUsedPacker[pPack->m_currFormat] = result;
			}

			pPack->release();
			KLBDELETE(pPack);

			m_allocatedPacker[surface>>12] = NULL;
		} else {
			// Do not free texture 0, just clean list.
			pPack->reset();
		}
	}
}

void TexturePacker::getSurfaceInfo(u16 surface, u32*& pixel, float& u0, float& v0, float& u1, float& v1, float& stepU, float& stepV) {
	klb_assert(surface != NULL_IDX, "Error");
	m_allocatedPacker[surface>>12]->getSurfaceInfo(surface & 0xFFF, pixel, u0, v0, u1, v1, stepU, stepV);
}

CTextureUsage* TexturePacker::getTextureUsage(u16 surface) {
	return m_allocatedPacker[surface>>12]->getTextureUsage();
}

void TexturePacker::updateTexture(u16 texture) {
	if (texture != NULL_IDX) {
		m_allocatedPacker[texture>>12]->updateTexture(texture & 0xFFF);
	}
}

void TexturePacker::setFormat(u16 format) {
	m_currFormat = format;
}

#ifdef DEBUG_TEXTURE_PACKER

void TexturePackerOnce::scan(void* ctx) {
	for (int n = 0; n<m_surfaceCount; n++) {
		if (m_surface[n].free) {
			klb_assert(m_surface[n].ownerCtx == NULL, "Should be cleaned by current logic");
		} else {
			klb_assert(m_surface[n].ownerCtx != ctx , "Should not own ref anymore !");
		}
	}
}

void TexturePacker::scan(void* ctx) {
	for (int n = 0; n<MAX_TEXTURES ; n++) {
		TexturePackerOnce* pCurr	= m_allocatedPacker[n];
		if (pCurr) {
			pCurr->scan(ctx);
		}
	}
}

#endif

static CKLBLuaLibPackerControl libdef(0);

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibPackerControl::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibPackerControl", CLS_KLBPACKERCTRL);

CKLBLuaLibPackerControl::CKLBLuaLibPackerControl(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibPackerControl::~CKLBLuaLibPackerControl()
{
}

// Lua�֐��̒ǉ�
void
CKLBLuaLibPackerControl::addLibrary()
{
	addFunction("ENG_use8888texture", CKLBLuaLibPackerControl::use8888Texture);
}

int
CKLBLuaLibPackerControl::use8888Texture(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retNil();
		return 1;
	}
	
	bool active8888 = lua.getBool(1);

	if (active8888) {
		TexturePacker::s_currentTextureMode = FORMAT_8888;
	} else {
		TexturePacker::s_currentTextureMode = FORMAT_4444;
	}

	lua.retBool(true);
	return 1;
}
