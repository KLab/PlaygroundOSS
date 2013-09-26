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
/*
	GameEngine が標準として持つべきタスクおよびLua関数モジュールが、
	「必ずリンク対象になる」ように、シンボルリファレンスを生じさせるための関数。
	同時に、標準タスクおよびLua関数モジュールが存在しているかのチェックにもなっている。

	標準のタスクやLua関数を追加した場合は、必ずメンテナンスが必要となる。
*/
#include "EngineStdReference.h"

// Utility Task
#include "CKLBGenericTask.h"
#include "CKLBIntervalTimer.h"
#include "CKLBLifeCtrlTask.h"
#include "CKLBPauseCtrl.h"

// Net Task
#include "CKLBStoreService.h"

// UI Task
#include "CKLBUIActivityIndicator.h"
#include "CKLBUICanvas.h"
#include "CKLBUIClip.h"
#include "CKLBUIControl.h"
#include "CKLBUIDebugItem.h"
#include "CKLBUIDragIcon.h"
#include "CKLBUIForm.h"
#include "CKLBUIFreeVertItem.h"
#include "CKLBUIGroup.h"
#include "CKLBUILabel.h"
#include "CKLBUIList.h"
#include "CKLBUIMoviePlayer.h"
#include "CKLBUIMultiImgItem.h"
#include "CKLBUIPieChart.h"
#include "CKLBUIPolyline.h"
#include "CKLBUIProgressBar.h"
#include "CKLBUIRubberBand.h"
#include "CKLBUIScale9.h"
#include "CKLBUIScore.h"
#include "CKLBUIScrollBar.h"
#include "CKLBUISimpleItem.h"
#include "CKLBUISWFPlayer.h"
#include "CKLBUITextInput.h"
#include "CKLBUIButton.h"
#include "CKLBUITouchPad.h"
#include "CKLBUIVariableItem.h"
#include "CKLBUIVirtualDoc.h"
#include "CKLBUIWebArea.h"
#include "CKLBUpdate.h"
#include "CKLBAsyncLoader.h"
#include "CKLBAsyncFilecopy.h"

bool EngineTaskReference()
{
	bool bResult = true;

	// Utility Task
	bResult = bResult && getFactoryFunc<CKLBGenericTask>();
	bResult = bResult && getFactoryFunc<CKLBIntervalTimer>();
	bResult = bResult && getFactoryFunc<CKLBLifeCtrlTask>();
	bResult = bResult && getFactoryFunc<CKLBPauseCtrl>();
	bResult = bResult && getFactoryFunc<CKLBAsyncLoader>();
	bResult = bResult && getFactoryFunc<CKLBAsyncFilecopy>();

	// Net Task
	bResult = bResult && getFactoryFunc<CKLBStoreService>();
	bResult = bResult && getFactoryFunc<CKLBUpdate>();
	bResult = bResult && getFactoryFunc<CKLBUpdateZip>();

	// UI Task
	bResult = bResult && getFactoryFunc<CKLBUIActivityIndicator>();
	bResult = bResult && getFactoryFunc<CKLBUICanvas>();
	bResult = bResult && getFactoryFunc<CKLBUIClip>();
	bResult = bResult && getFactoryFunc<CKLBUIControl>();
	bResult = bResult && getFactoryFunc<CKLBUIDebugItem>();
	bResult = bResult && getFactoryFunc<CKLBUIDragIcon>();
	bResult = bResult && getFactoryFunc<CKLBUIForm>();
	bResult = bResult && getFactoryFunc<CKLBUIFreeVertItem>();
	bResult = bResult && getFactoryFunc<CKLBUIGroup>();
	bResult = bResult && getFactoryFunc<CKLBUILabel>();
	bResult = bResult && getFactoryFunc<CKLBUIList>();
	bResult = bResult && getFactoryFunc<CKLBUIMoviePlayer>();
	bResult = bResult && getFactoryFunc<CKLBUIMultiImgItem>();
	bResult = bResult && getFactoryFunc<CKLBUIPieChart>();
	bResult = bResult && getFactoryFunc<CKLBUIPolyline>();
	bResult = bResult && getFactoryFunc<CKLBUIProgressBar>();
	bResult = bResult && getFactoryFunc<CKLBUIRubberBand>();
	bResult = bResult && getFactoryFunc<CKLBUIScale9>();
	bResult = bResult && getFactoryFunc<CKLBUIScore>();
	bResult = bResult && getFactoryFunc<CKLBUIScrollBar>();
	bResult = bResult && getFactoryFunc<CKLBUISimpleItem>();
	bResult = bResult && getFactoryFunc<CKLBUISWFPlayer>();
	bResult = bResult && getFactoryFunc<CKLBUITextInput>();
	bResult = bResult && getFactoryFunc<CKLBUIButton>();
	bResult = bResult && getFactoryFunc<CKLBUITouchPad>();
	bResult = bResult && getFactoryFunc<CKLBUIVariableItem>();
	bResult = bResult && getFactoryFunc<CKLBUIVirtualDoc>();
	bResult = bResult && getFactoryFunc<CKLBUIWebArea>();


	return bResult;
}

// LuaLib
#include "CKLBLuaLibAPP.h"
#include "CKLBLuaLibASSET.h"
#include "CKLBLuaLibBIN.h"
#include "CKLBLuaLibCONV.h"
#include "CKLBLuaLibDATA.h"
#include "CKLBLuaLibDB.h"
#include "CKLBLuaLibDEBUG.h"
#include "CKLBLuaLibENG.h"
#include "CKLBLuaLibFONT.h"
#include "CKLBLuaLibGL.h"
#include "CKLBLuaLibKEY.h"
#include "CKLBLuaLibLANG.h"
#include "CKLBLuaLibMatrix.h"
#include "CKLBLuaLibRES.h"
#include "CKLBLuaLibSOUND.h"
#include "CKLBLuaLibTASK.h"
#include "CKLBLuaLibUI.h"

#include "CKLBAppProperty.h"

#include "CKLBScrMgrDefault.h"
#include "CKLBScrMgrPage.h"
#include "CKLBScrMgrSolid.h"
#include "CKLBTexturePacker.h"

bool EngineLuaFuncReference()
{
	bool bResult = true;

	bResult = bResult && getFuncRegister<CKLBLuaLibAPP>();
	bResult = bResult && getFuncRegister<CKLBLuaLibASSET>();
	bResult = bResult && getFuncRegister<CKLBLuaLibBIN>();
	bResult = bResult && getFuncRegister<CKLBLuaLibCONV>();
	bResult = bResult && getFuncRegister<CKLBLuaLibDATA>();
	bResult = bResult && getFuncRegister<CKLBLuaLibDB>();
	bResult = bResult && getFuncRegister<CKLBLuaLibDEBUG>();
	bResult = bResult && getFuncRegister<CKLBLuaLibENG>();
	bResult = bResult && getFuncRegister<CKLBLuaLibFONT>();
	bResult = bResult && getFuncRegister<CKLBLuaLibGL>();
	bResult = bResult && getFuncRegister<CKLBLuaLibKEY>();
	bResult = bResult && getFuncRegister<CKLBLuaLibLANG>();
	bResult = bResult && getFuncRegister<CKLBLuaLibMatrix>();
	bResult = bResult && getFuncRegister<CKLBLuaLibRES>();
	bResult = bResult && getFuncRegister<CKLBLuaLibSOUND>();
	bResult = bResult && getFuncRegister<CKLBLuaLibTASK>();
	bResult = bResult && getFuncRegister<CKLBLuaLibUI>();
	bResult = bResult && getFuncRegister<CKLBLuaLibUPDATE>();
	bResult = bResult && getFuncRegister<CKLBLuaLibPackerControl>();
	bResult = bResult && (0 != CKLBAppScriptIF::setValue);

	return bResult;
}

bool EngineScrMgrReference()
{
	bool bResult = true;
	bResult = bResult && getFuncRegister<CKLBScrMgrDefaultFactory>();
	bResult = bResult && getFuncRegister<CKLBScrMgrPageFactory>();
	bResult = bResult && getFuncRegister<CKLBScrMgrSolidFactory>();

	return bResult;
}

bool EngineStdReference()
{
	bool bResult = true;
	bResult = bResult && EngineTaskReference();
	bResult = bResult && EngineLuaFuncReference();
	bResult = bResult && EngineScrMgrReference();
	return bResult;
}
