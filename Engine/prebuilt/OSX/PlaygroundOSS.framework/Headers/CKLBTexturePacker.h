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
#ifndef __TEXTURE_PACKER__
#define __TEXTURE_PACKER__

#include "BaseType.h"
#include "CKLBRendering.h"

// If defined, allocated buffer are filled with color for debugging.
// #define INTERNAL_FILL_WITH_COLOR_TEXPACKER

class TexturePackerOnce;

typedef void (*compact)(void* ctx, u16 surfaceID, u16 newSurfaceID);

#define FORMAT_8888		(4)
#define FORMAT_4444		(2)
#define FORMAT_8		(1)

#define STARTUP_FORMAT	(FORMAT_8888)

class CKLBLuaLibPackerControl;

class TexturePacker {
	friend class TexturePackerOnce;
	friend class CKLBLuaLibPackerControl;
public:
	inline
	static u8 getCurrentModeTexture() {
		return s_currentTextureMode;
	}

	inline
	static TexturePacker& getInstance() {
		static TexturePacker instance;
		return instance;
	}

	bool init				(u16 width,			u16 height, u16 format);
	void release			();
	void dump				(bool detail);
	void refreshTextures	();
	void unloadSurface		();
	void reloadSurfaces		();

	u16  allocateSurface	(CKLBSprite* spr,	u16 w,		u16 h	, void* ptrOwner, compact cbCompaction);
	u16	 reallocateSurface	(u16 surface,		u16 w,		u16 h	);
	void releaseSurface		(u16 surface);
	void getSurfaceInfo		(u16 surface,		u32*& pixel, float& u0, float& v0, float& u1, float& v1, float& stepU, float& stepV);
	CTextureUsage*
		 getTextureUsage	(u16 surface);
	u16	 getSurfaceStride	()	{ return m_width;			}
	void updateTexture		(u16 surface);
	void setFormat			(u16 format);

#ifdef DEBUG_TEXTURE_PACKER
	void scan				(void* ctx);
	void setCurrentDelete	(void* ptr);
#endif

private:
	u16	 useOtherAlloc		(CKLBSprite* spr,	u16 w,		u16 h	, void* ptrOwner,compact cbCompaction);
	TexturePackerOnce*
		 allocateAllocator	(u16 w, u16 h);
	bool notInIgnoreList	(TexturePackerOnce* pack);
	void removeIgnoreList	(TexturePackerOnce* pack);
	void addIgnoreList		(TexturePackerOnce* pack);

	// Maximum 4 bit on 16 bit index.
	#define MAX_TEXTURES	(16)
	u16					m_currFormat;
	u16					m_width;
	u16					m_height;
	u16					m_update;
	// Mode 8888, 4444, 8
	TexturePackerOnce*	m_lastUsedPacker	[5];
	TexturePackerOnce*	m_allocatedPacker	[MAX_TEXTURES];

	TexturePackerOnce*	ignore				[MAX_TEXTURES];
	u8					ignoreCount;

	static
	u8					s_currentTextureMode;
};

#include "ILuaFuncLib.h"
#include "CKLBLibRegistrator.h"

class CKLBLuaLibPackerControl : public ILuaFuncLib
{
private:
	CKLBLuaLibPackerControl();

	static int use8888Texture(lua_State * L);
	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;
public:
	CKLBLuaLibPackerControl(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibPackerControl();

	void addLibrary			();
};

#endif 	// ifndef __TEXTURE_PACKER__
