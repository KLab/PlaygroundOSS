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
#include "CallBackDef.h"

void initCallbacks() {
	CallbackDef::s_start                  = Program::start;
    CallbackDef::s_destroyPtr             = EnginePrototype::NativeManagement::destroyFromNative;
    CallbackDef::s_doCallBackPtrV         = EnginePrototype::NativeManagement::doCallBackV;
    CallbackDef::s_doCallBackPtrII        = EnginePrototype::NativeManagement::doCallBackII;
    CallbackDef::s_doCallBackPtrIII       = EnginePrototype::NativeManagement::doCallBackIII;
    CallbackDef::s_doCallBackPtrIIII      = EnginePrototype::NativeManagement::doCallBackIIII;
    CallbackDef::s_doCallBackPtrS         = EnginePrototype::NativeManagement::doCallBackS;
    CallbackDef::s_doCallBackPtrSII       = EnginePrototype::NativeManagement::doCallBackSII;
    CallbackDef::s_doCallBackPtrSU        = EnginePrototype::NativeManagement::doCallBackSU;
    CallbackDef::s_doCallBackPtrSS        = EnginePrototype::NativeManagement::doCallBackSS;
    CallbackDef::s_doCallBackPtrUS        = EnginePrototype::NativeManagement::doCallBackUS;
    CallbackDef::s_doCallBackPtrUSS       = EnginePrototype::NativeManagement::doCallBackUSS;
    CallbackDef::s_doCallBackPtrU         = EnginePrototype::NativeManagement::doCallBackU;
    CallbackDef::s_doCallBackPtrUU        = EnginePrototype::NativeManagement::doCallBackUU;
    CallbackDef::s_doCallBackPtrUFF       = EnginePrototype::NativeManagement::doCallBackUFF;
    CallbackDef::s_doCallBackPtrUI        = EnginePrototype::NativeManagement::doCallBackUI;
    CallbackDef::s_doCallBackPtrUII       = EnginePrototype::NativeManagement::doCallBackUII;
    CallbackDef::s_doCallBackPtrUIIII     = EnginePrototype::NativeManagement::doCallBackUIIII;
    CallbackDef::s_doCallBackPtrUIIUU     = EnginePrototype::NativeManagement::doCallBackUIIUU;
    CallbackDef::s_doCallBackPtrUUII      = EnginePrototype::NativeManagement::doCallBackUUII;
    CallbackDef::s_doCallBackPtrUUUII     = EnginePrototype::NativeManagement::doCallBackUUUII;
    CallbackDef::s_doCallBackPtrIIIP_retB = EnginePrototype::NativeManagement::doCallBackIIIP_retB;
    CallbackDef::s_doCallBackPtrFS        = EnginePrototype::NativeManagement::doCallBackFS;
}
