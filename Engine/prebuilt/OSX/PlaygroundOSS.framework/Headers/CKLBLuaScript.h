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
//  CKLBLuaScript.h
//

#ifndef CKLBLuaScript_h
#define CKLBLuaScript_h

#include "CLuaState.h"
#include "CKLBLuaEnv.h"
#include "CKLBTask.h"


/*!
* \class CKLBLuaScript
* \brief Lua Script loading class.
* 
* CKLBLuaScript is used to load and execute some Lua script from an URL.
*/
class CKLBLuaScript : public CKLBTask
{
private:
    CKLBLuaScript ();
    ~CKLBLuaScript();

	bool onPause(bool bPause);

public:
    static CKLBLuaScript * create(const char * bootScriptURL);

    void execute(u32 deltaT);
    void die    ();

	u32 getClassID();
};


#endif
