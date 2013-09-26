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
#include "CKLBLuaLibGL.h"
#include "CKLBDrawTask.h"
#include "TextureManagement.h"
#include "CKLBTouchPad.h"

static CKLBLuaLibGL libdef(0);

CKLBLuaLibGL::CKLBLuaLibGL(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibGL::~CKLBLuaLibGL() {}

// Lua関数の追加
void
CKLBLuaLibGL::addLibrary()
{
	addFunction("GL_SetResolution",			CKLBLuaLibGL::luaGLSetResolution		);
	addFunction("GL_GetHorizontalBorder",	CKLBLuaLibGL::luaGLGetHorizontalBorder	);
	addFunction("GL_GetVerticalBorder",		CKLBLuaLibGL::luaGLGetVerticalBorder	);
	addFunction("GL_ClearColor",			CKLBLuaLibGL::luaGLClearColor			);
	addFunction("GL_UseImageOffset",		CKLBLuaLibGL::luaGLUseImageOffset		);
	addFunction("GL_LoadAsQuarterTexture",	CKLBLuaLibGL::luaGLSetQuarter			);

	addFunction("GL_CreateScreenAsset",		CKLBLuaLibGL::luaGLCreateScreenAsset	);
	addFunction("GL_DoScreenShot",			CKLBLuaLibGL::luaGLDoScreenShot			);
	addFunction("GL_FreeScreenAsset",		CKLBLuaLibGL::luaGLFreeScreenShot		);
	
	addFunction("SG_GetGuardBand",			CKLBLuaLibGL::luaGetGuardBand			);
	addFunction("SG_SetGuardBand",			CKLBLuaLibGL::luaSetGuardBand			);

	addFunction("GL_Unloadtexture",			CKLBLuaLibGL::luaGLUnloadTexture		);
	addFunction("GL_Reloadtexture",			CKLBLuaLibGL::luaGLReloadTexture		);
	addFunction("GL_DoScreenShot",			CKLBLuaLibGL::luaGLDoScreenShot			);
}

/*static*/
int CKLBLuaLibGL::luaGLUnloadTexture (lua_State * L) {
	CLuaState lua(L);
	CKLBAssetManager::getInstance().unloadAsset();
	lua.retBoolean(true);
	return 1;
}

/*static*/
int CKLBLuaLibGL::luaGLReloadTexture (lua_State * L) {
	CLuaState lua(L);
	CKLBAssetManager::getInstance().restoreAsset();
	lua.retBoolean(true);
	return 1;
}

/*static*/
int CKLBLuaLibGL::luaGLGetHorizontalBorder	(lua_State * L) {
	CLuaState lua(L);
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	lua.retInt(draw.ox());
	return 1;
}

/*static*/
int CKLBLuaLibGL::luaGLGetVerticalBorder	(lua_State * L) {
	CLuaState lua(L);
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	lua.retInt(draw.oy());
	return 1;
}

int
CKLBLuaLibGL::luaGLUseImageOffset(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}
	bool b = lua.getBool(1);
	useOffsetForImages(b);
	lua.retBoolean(true);
	return 1;
}

int
CKLBLuaLibGL::luaGLClearColor(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc != 4) {
		lua.retBoolean(false);
		return 1;
	}
	float r = lua.getFloat(1);
	float g = lua.getFloat(2);
	float b = lua.getFloat(3);
	float a = lua.getFloat(4);

	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	bool bResult = draw.setClearColor(r, g, b, a);
	lua.retBoolean(bResult);
	return 1;
}

int
CKLBLuaLibGL::luaGLSetResolution(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBoolean(false);
		return 1;
	}
	int width	= lua.getInt(1);
	int height	= lua.getInt(2);
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	
	if (argc >= 3) {
		draw.setBorderless(lua.getBool(3));
	}
	
	if (argc == 4) {
		bool b = lua.getBool(4);
		CKLBTouchPadQueue::getInstance().setIgnoreOutside(b);
	} else {
		CKLBTouchPadQueue::getInstance().setIgnoreOutside(false);
	}


	// 論理解像度の指定を行う
	draw.setLogicalResolution(width, height);

	lua.retBoolean(true);
	return 1;
}

int CKLBLuaLibGL::luaGetGuardBand(lua_State * L) {
	CLuaState lua(L);
	
	lua.retFloat(CKLBNode::s_fLeftBorder);
	lua.retFloat(CKLBNode::s_fRightBorder);
	lua.retFloat(CKLBNode::s_fTopBorder);
	lua.retFloat(CKLBNode::s_fBottomBorder);

	return 4;
}

int CKLBLuaLibGL::luaSetGuardBand(lua_State * L) {
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc != 4) {
		lua.retBoolean(false);
		return 1;
	}

	CKLBNode::s_fLeftBorder		= lua.getFloat(1);
	CKLBNode::s_fRightBorder	= lua.getFloat(2);
	CKLBNode::s_fTopBorder		= lua.getFloat(3);
	CKLBNode::s_fBottomBorder	= lua.getFloat(4);

	lua.retBoolean(true);
	return 1;
}

/*static*/
bool
CKLBLuaLibGL::GLCreateScreenAsset(const char* name)
{
	IClientRequest& itf	= CPFInterface::getInstance().client();
	int width			= itf.getPhysicalScreenWidth();
	int height			= itf.getPhysicalScreenHeight();

	return createScreenAsset(name,width,height);
}

int
CKLBLuaLibGL::luaGLCreateScreenAsset(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if (argc != 1) {
		lua.retBoolean(false);
		return 1;
	}
	const char* name	= lua.getString(1);
	
	lua.retBoolean(GLCreateScreenAsset(name));
	return 1;
}

/*static*/
bool
CKLBLuaLibGL::GLDoScreenShot(const char* name)
{
	IClientRequest& itf	= CPFInterface::getInstance().client();
	int width			= itf.getPhysicalScreenWidth();
	int height			= itf.getPhysicalScreenHeight();

	return doScreenShot(name, 0, 0, width, height, 0, 0);
}

int
CKLBLuaLibGL::luaGLDoScreenShot(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc < 1) {
		lua.retBoolean(false);
		return 1;
	}

	const char* name	= lua.getString(1);
	
	lua.retBoolean(GLDoScreenShot(name));
	return 1;
}

/*static*/
void
CKLBLuaLibGL::GLFreeScreenAsset(const char* name)
{
	freeScreenAsset(name);
}

int
CKLBLuaLibGL::luaGLFreeScreenShot(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}

	const char* name	= lua.getString(1);
	freeScreenAsset(name);
	lua.retBoolean(true);
	return 1;
}

#include "CKLBAsset.h"

int
CKLBLuaLibGL::luaGLSetQuarter(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}

	bool val = lua.getBoolean(1);

	// Get 
	KLBTextureAssetPlugin* pTexPlug = (KLBTextureAssetPlugin*)CKLBAssetManager::getInstance().getPlugin('T');
	if (pTexPlug) {
		pTexPlug->setQuarterTexture(val);
	}

	lua.retBoolean(pTexPlug != NULL);
	return 1;
}

