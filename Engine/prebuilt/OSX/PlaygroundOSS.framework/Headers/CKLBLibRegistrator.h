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
#ifndef CKLBLibRegistrator_h
#define CKLBLibRegistrator_h

#include "CKLBTask.h"
#include "CKLBUtility.h"
#include "CKLBScriptEnv.h"

#define		MAX_ELEM	(10)

class CKLBLibRegistrator
{
public:
	struct LIBREGISTSTRUCT {
		const char* name;
		u32 classID;
		LIBREGISTSTRUCT* next;
	};

	static 
	CKLBLibRegistrator*		getInstance		();
	LIBREGISTSTRUCT*		add				(const char* name, u32 classID);
	u32						getClassID		(const char* funcName);

private:
	int							m_count;
	LIBREGISTSTRUCT				m_list[MAX_ELEM];

	CKLBLibRegistrator ();
	~CKLBLibRegistrator();
};

#endif