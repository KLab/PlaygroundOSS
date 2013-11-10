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
#ifndef CKLBAppProperty_h
#define CKLBAppProperty_h

#include "CKLBLuaTask.h"


class CKLBAppProperty
{
private:
	CKLBAppProperty();
	virtual ~CKLBAppProperty();
public:
	enum PIDX {
		SCRN_TYPE	= 0,	// Screen Type (LANDSCAPE or PORTRAIT or -1)

		PIDX_MAX
	};

	static CKLBAppProperty& getInstance();

	int  getValue(PIDX idx);
	bool setValue(PIDX idx, int value);

private:
	int		m_value[ PIDX_MAX ];
};

class CKLBAppScriptIF : public IFactory
{
public:
	CKLBAppScriptIF(const char * funcname, u32 classID, DEFCMD * arrCmdItem);
	virtual ~CKLBAppScriptIF();

	static int setValue(lua_State * L);
};

#endif // CKLBAppProperty_h
