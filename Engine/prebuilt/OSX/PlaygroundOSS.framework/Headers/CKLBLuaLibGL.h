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
#ifndef CKLBLuaLibGL_h
#define CKLBLuaLibGL_h

#include "ILuaFuncLib.h"
#include "CKLBDrawTask.h"

class CKLBLuaLibGL : public ILuaFuncLib
{
private:
	CKLBLuaLibGL();
public:
	CKLBLuaLibGL(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibGL();

	void addLibrary();

private:
	static int luaGLSetResolution		(lua_State * L);
	static int luaGLClearColor			(lua_State * L);
	static int luaGLUseImageOffset		(lua_State * L);
	static int luaGetGuardBand			(lua_State * L);
	static int luaSetGuardBand			(lua_State * L);
	static int luaGLCreateScreenAsset	(lua_State * L);
	static int luaGLDoScreenShot		(lua_State * L);
	static int luaGLFreeScreenShot		(lua_State * L);
	static int luaGLGetHorizontalBorder	(lua_State * L);
	static int luaGLGetVerticalBorder	(lua_State * L);
	static int luaGLSetQuarter			(lua_State * L);
	static int luaGLReloadTexture		(lua_State * L);
	static int luaGLUnloadTexture		(lua_State * L);

	
		
public:
	inline static bool GLClearColor(float r, float g, float b, float a) {
		return CKLBDrawResource::getInstance().setClearColor(r, g, b, a);
	}

	inline static void GLSetResolution(int width, int height) {
		CKLBDrawResource::getInstance().setLogicalResolution(width, height);
	}

	inline static void SGGetGuardBand(float* leftBorder, float* rightBorder, float* topBorder, float* bottomBorder) {
		*leftBorder		= CKLBNode::s_fLeftBorder;
		*rightBorder	= CKLBNode::s_fRightBorder;
		*topBorder		= CKLBNode::s_fTopBorder;
		*bottomBorder	= CKLBNode::s_fBottomBorder;
	}
	inline static void SGSetGuardBand(float  leftBorder, float  rightBorder, float  topBorder, float  bottomBorder) {
		CKLBNode::s_fLeftBorder		= leftBorder;
		CKLBNode::s_fRightBorder	= rightBorder;
		CKLBNode::s_fTopBorder		= topBorder;
		CKLBNode::s_fBottomBorder	= bottomBorder;
	}

	static bool GLCreateScreenAsset	(const char* name);
	static bool GLDoScreenShot		(const char* name);
	static void GLFreeScreenAsset	(const char* name);
};


#endif // CKLBLuaLibGL_h
