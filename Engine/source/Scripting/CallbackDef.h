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
#ifndef CALLBACK_DEF_H
#define CALLBACK_DEF_H

#include "BaseType.h"

class CallbackDef {
public:
	typedef void (*FP_V)			(void);
	typedef void (*FP_U)			(u32);
	typedef void (*FP_IIII)			(s32, s32, s32, s32);
	typedef void (*FP_UII)			(u32, s32, s32);
	typedef void (*FP_UIII)			(u32, s32, s32, s32);
	typedef void (*FP_UIIII)		(u32, s32, s32, s32, s32);
	typedef void (*FP_US)			(u32, s32*);
	typedef void (*FP_USII)			(u32, s32*, s32, s32);
	typedef void (*FP_USU)			(u32, s32*, u32);
	typedef void (*FP_USS)			(u32, s32*, s32*);
	typedef void (*FP_UUS)			(u32, u32, s32*);
	typedef void (*FP_UUSS)			(u32, u32, s32*, s32*);
	typedef void (*FP_UU)			(u32, u32);
	typedef void (*FP_UUU)			(u32, u32, u32);
	typedef void (*FP_UUFF)			(u32, u32, float, float);
	typedef void (*FP_UUI)			(u32, u32, s32);
	typedef void (*FP_UUII)			(u32, u32, s32, s32);
	typedef void (*FP_UUIIII)		(u32, u32, s32, s32, s32, s32);
	typedef void (*FP_UUIIUU)		(u32, u32, s32, s32, u32, u32);
	typedef void (*FP_UUUII)		(u32, u32, u32, s32, s32);
	typedef void (*FP_UUUUII)		(u32, u32, u32, u32, s32, s32);
	typedef bool (*FP_UIIIP_retB)	(u32, s32, s32, s32, s32*);
	typedef void (*FP_UFS)			(u32, float, s32*);

	static FP_V				s_start					;
	static FP_U				s_destroyPtr			;
	static FP_IIII			s_worldCallBackPtr		;
	static FP_U				s_doCallBackPtrV		;
	static FP_UII			s_doCallBackPtrII		;
	static FP_UIII			s_doCallBackPtrIII		;
	static FP_UIIII			s_doCallBackPtrIIII		;
	static FP_US			s_doCallBackPtrS		;
	static FP_USII			s_doCallBackPtrSII		;
	static FP_USU			s_doCallBackPtrSU		;
	static FP_USS			s_doCallBackPtrSS		;
	static FP_UUS			s_doCallBackPtrUS		;
	static FP_UUSS			s_doCallBackPtrUSS		;
	static FP_UU			s_doCallBackPtrU		;
	static FP_UUU			s_doCallBackPtrUU		;
	static FP_UUFF			s_doCallBackPtrUFF		;
	static FP_UUI			s_doCallBackPtrUI		;
	static FP_UUII			s_doCallBackPtrUII		;
	static FP_UUIIII		s_doCallBackPtrUIIII	;
	static FP_UUIIUU		s_doCallBackPtrUIIUU	;
	static FP_UUUII			s_doCallBackPtrUUII		;
	static FP_UUUUII		s_doCallBackPtrUUUII	;
	static FP_UIIIP_retB	s_doCallBackPtrIIIP_retB;
	static FP_UFS			s_doCallBackPtrFS		;
};

void initCallbacks();
void registerWorldGC();

#endif //CALLBACK_DEF_H
