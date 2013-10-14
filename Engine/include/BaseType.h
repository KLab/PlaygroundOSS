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
// === Common type, inside porting layer ===
//

#ifndef __KLB_BASE_TYPE__
#define __KLB_BASE_TYPE__

#ifdef _WIN32
#pragma warning(disable:4996)
#endif

//
// Base type definition.
//
typedef unsigned int	u32;
typedef int				s32;
typedef unsigned short	u16;
typedef short			s16;
typedef unsigned char	u8;
typedef char			s8;
typedef u16				unichar;
typedef long long int	s64;
typedef long long unsigned int u64;

#ifndef NULL
	#define	NULL			(0)
#endif

#define NULL_IDX			(0xFFFF)

// TODO RP : Move the lower definition to an internal .h file.
//
// Class ID.
//

// Special Array wrapper class
#define CLS_KLBARRAY			(0x80000000)
// Native array
#define CLS_ARRAYOF				(0x40000000)
#define CLS_PUBLIC				(0x20000000)
#define CLS_PRIVATEPROTECTED	(0x10000000)
#define CLS_READONLY			(0x08000000)

//
// Group bit.
//
#define CLS_BASETYPE			(0x00000000)
#define CLS_KLBENGINECLASS		(0x00010000)
#define CLS_KLBASSETCLASS		(0x00020000)
#define CLS_KLBUICORECLASS		(0x00040000)
#define CLS_KLBUSERTASK			(0x00080000)
#define CLS_USERCUSTOM			(0x00100000)
#define CLS_USERCUSTOMTASK		(CLS_USERCUSTOM | CLS_KLBUSERTASK)
#define CLS_NONVISUALTASK		(0x00200000)

// 4,8
#define CLS_UNIQUEID			(0x000FFFFF)

//
// Base Type
//
#define CLS_U32				(1 | CLS_BASETYPE)
#define CLS_S32				(2 | CLS_BASETYPE)
#define CLS_U16				(3 | CLS_BASETYPE)
#define CLS_S16				(4 | CLS_BASETYPE)
#define CLS_U8				(5 | CLS_BASETYPE)
#define CLS_S8				(6 | CLS_BASETYPE)
#define CLS_BOOL			(9 | CLS_BASETYPE)
#define CLS_FLOAT			(7 | CLS_BASETYPE)
#define CLS_PTR				(8 | CLS_BASETYPE)
#define CLS_CSTRING			(10| CLS_BASETYPE)
#define CLS_COLOR			(11| CLS_BASETYPE)

//
// Engine
//
#define CLS_KLBOBJECT		(1 | CLS_KLBENGINECLASS)
#define CLS_KLBNODE			(2 | CLS_KLBENGINECLASS)
// Node based

#define CLS_KLBUIELEMENT	(3 | CLS_KLBENGINECLASS | CLS_KLBUICORECLASS)
#define CLS_KLBUISELECTABLE	(4 | CLS_KLBENGINECLASS | CLS_KLBUICORECLASS)
#define CLS_KLBUICONTAINER	(5 | CLS_KLBENGINECLASS | CLS_KLBUICORECLASS)

#define CLS_GAMEUNIT		(6 | CLS_KLBENGINECLASS)
#define CLS_KLBSWFMOVIE		(7 | CLS_KLBENGINECLASS)
#define CLS_KLBSPLINENODE	(8 | CLS_KLBENGINECLASS)
#define CLS_KLBNODEMAP		(9 | CLS_KLBENGINECLASS)
#define CLS_KLBSCORENODE	(10| CLS_KLBENGINECLASS)

#define CLS_KLBTASKTOUCHPAD	(12| CLS_KLBENGINECLASS | CLS_NONVISUALTASK)
#define CLS_KLBTASKSCRIPT	(13| CLS_KLBENGINECLASS | CLS_NONVISUALTASK)
#define CLS_KLBTASKDRAW		(14| CLS_KLBENGINECLASS | CLS_NONVISUALTASK)
#define CLS_KLBTASKGENERIC	(15| CLS_KLBUSERTASK    | CLS_NONVISUALTASK)
#define CLS_KLBLUAPROPTASK  (16| CLS_KLBENGINECLASS)
#define CLS_KLBTASKUIEVENT	(17| CLS_KLBENGINECLASS)
#define CLS_KLBTASKOSCTRLEVENT (18|CLS_KLBENGINECLASS)

// UITasks based
#define CLS_KLBUIPROGRESS	(20| CLS_KLBUSERTASK)
#define CLS_KLBUISCORE		(21| CLS_KLBUSERTASK)
#define CLS_KLBUIVIRTUALDOC	(22| CLS_KLBUSERTASK)

#define CLS_KLBCELLANIMNODE	(23| CLS_KLBENGINECLASS)

// UITasks based
#define CLS_KLBUICELLANIM   (24| CLS_KLBUSERTASK)
#define CLS_KLBUISWFPLAYER  (25| CLS_KLBUSERTASK)
#define CLS_KLBUITOUCHPAD   (26| CLS_KLBUSERTASK)
#define CLS_KLBUIMAPTASK	(27| CLS_KLBUSERTASK)
#define CLS_KLBUIFORM		(28| CLS_KLBUSERTASK)

// Node based
#define CLS_KLBTEXTEDIT		(29| CLS_KLBENGINECLASS)
#define CLS_KLBWEBVIEW		(30| CLS_KLBENGINECLASS)
#define CLS_GAMEUNITBASE	(31| CLS_KLBENGINECLASS)
#define CLS_KLBLABEL		(32| CLS_KLBENGINECLASS)

// UITasks based
#define CLB_KLBUISCROLLBAR	(33| CLS_KLBUSERTASK)

#define CLS_KLBMOVIENODE		(34| CLS_KLBENGINECLASS)
#define CLS_KLBINTERVALTIMER	(35| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBUICANVAS			(36| CLS_KLBUSERTASK)
#define CLS_KLBUICONTROL		(37| CLS_KLBUSERTASK)
#define CLS_KLBUIDBGLABEL		(38| CLS_KLBUSERTASK)
#define CLS_KLBUIDRAGICON		(39| CLS_KLBUSERTASK)
#define CLS_KLBUIFREEVERTITEM	(40| CLS_KLBUSERTASK)
#define CLS_KLBUIGROUP			(41| CLS_KLBUSERTASK)
#define CLS_KLBUILABEL			(42| CLS_KLBUSERTASK)
#define CLS_KLBUILIST			(43| CLS_KLBUSERTASK)
#define CLS_KLBUIMOVIEPLAYER	(44| CLS_KLBUSERTASK)
#define CLS_KLBUIMULTIIMGITEM	(45| CLS_KLBUSERTASK)
#define CLS_KLBUIPIECHART		(46| CLS_KLBUSERTASK)
#define CLS_KLBUIPOLYLINE		(47| CLS_KLBUSERTASK)
#define CLS_KLBUIRUBBERBAND		(48| CLS_KLBUSERTASK)
#define CLS_KLBUISCALE9			(49| CLS_KLBUSERTASK)
#define CLS_KLBUISIMPLEITEM		(50| CLS_KLBUSERTASK)
#define CLS_KLBUITEXTINPUT		(51| CLS_KLBUSERTASK)

// export objects
#define CLS_KLBBINARRAY     (52| CLS_KLBENGINECLASS)
#define CLS_KLBLUADB        (53| CLS_KLBENGINECLASS)
#define CLS_KLBDATASET      (54| CLS_KLBENGINECLASS)
#define CLS_KLBNODEVIRTUALDOC	(55 | CLS_KLBENGINECLASS | CLS_KLBUICORECLASS)
#define CLS_KLBFONTOBJ		(56| CLS_KLBENGINECLASS)
#define CLS_KLBSOUNDOBJ		(57| CLS_KLBENGINECLASS)
#define CLS_KLBMATRIXOBJ	(58| CLS_KLBENGINECLASS)
#define CLS_KLBVECTOROBJ	(59| CLS_KLBENGINECLASS)

#define CLS_KLBUNITTASK		(60| CLS_KLBUSERTASK)
#define CLS_KLBMAPGROUP		(61| CLS_KLBUSERTASK)

#define CLS_KLBSTORESERVICE	(62| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBNETAPI		(63| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBPAUSECTRL	(64| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBLIFECTRL		(65| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBAIDRIVERTASK	(67| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBWORDLTASK	(68| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBUIWEBVIEW	(69| CLS_KLBUSERTASK)

#define CLS_KLBAPPPROP		(70| CLS_KLBENGINECLASS)

#define CLS_KLBACTIVITYINDICATORNODE    (71| CLS_KLBENGINECLASS)    // CKLBActivityIndicatorNode
#define CLS_KLBUIACTIVITYINDICATOR      (72| CLS_KLBUSERTASK)    // CKLBUIActivityIndicator

#define CLS_KLBUIVARIABLEITEM			(73| CLS_KLBUSERTASK)
#define CLS_KLBUICLIP					(74| CLS_KLBUSERTASK)
#define CLS_KLBAPPUPDATE				(75| CLS_KLBENGINECLASS)
#define CLS_KLBASYNCLOADER				(76| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBGCTASK					(77| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBAPPUPDATEZIP				(78| CLS_KLBUSERTASK | CLS_NONVISUALTASK)
#define CLS_KLBASYNCFILECOPY			(79| CLS_KLBUSERTASK | CLS_NONVISUALTASK)

#define CLS_KLBUIBUTTON		(80| CLS_KLBUSERTASK)
#define CLS_KLBPACKERCTRL	(81| CLS_KLBENGINECLASS)

//
// Engine Assets
//
#define CLS_ASSETBASE		(0 | CLS_KLBASSETCLASS)
#define CLS_ASSETTEXTURE	(1 | CLS_KLBASSETCLASS)
#define CLS_ASSETIMAGE		(2 | CLS_KLBASSETCLASS)
#define CLS_ASSETAUDIO		(3 | CLS_KLBASSETCLASS)
#define CLS_ASSETFLASH		(4 | CLS_KLBASSETCLASS)
#define CLS_ASSETANIMSPLINE	(5 | CLS_KLBASSETCLASS)
#define CLS_ASSETMAP		(6 | CLS_KLBASSETCLASS)
#define CLS_ASSETCELLANIM	(7 | CLS_KLBASSETCLASS)
#define CLS_ASSETCOMPOSITE	(8 | CLS_KLBASSETCLASS)
#define CLS_ASSETNODEANIM	(9 | CLS_KLBASSETCLASS)
#define CLS_ASSETAI			(10| CLS_KLBASSETCLASS)


#ifdef DEBUG_MEMORY

	// #define INTERNAL_MEMORY_STARVING

	#include "DebugAlloc.h"
	#include "DebugTracker.h"
	
	#define KLBNEW(a)				(a*)CTracker::logNew(new a(),sizeof(a),__LINE__,__FILE__)
	#define KLBNEWA(a,b)			(a*)CTracker::logNew(new a[(b)],sizeof(a)*(b),__LINE__,__FILE__)
	#define KLBNEWC(a,b)			(a*)CTracker::logNew(new a b,sizeof(a), __LINE__,__FILE__)
	#define KLBMALLOC(a)			CTracker::logNew(malloc(a),(a),__LINE__,__FILE__)

	#define KLBDELETE(a)			do { if( (a)!=NULL ){ CTracker::logDelete((void *)(a),__LINE__,__FILE__); delete a; } } while (0)
	#define KLBDELETEA(a)			do { if( (a)!=NULL ){ CTracker::logDelete((void *)(a),__LINE__, __FILE__); delete [] a; } } while (0)
	#define KLBFREE(a)				do { if( (a)!=NULL ){ CTracker::logDelete((void *)(a),__LINE__,__FILE__); free(a); a=NULL; } } while (0)
#else
    #define KLBNEW(a)				new a()
    #define KLBNEWA(a,b)			new a[(b)]
    #define KLBNEWC(a,b)			new a b
    #define KLBMALLOC(a)			malloc(a)

    #define KLBDELETE(a)			do { if( (a)!=NULL ){ delete a; } } while (0)
    #define KLBDELETEA(a)           do { if( (a)!=NULL ){ delete [] a; } } while (0)
    #define KLBFREE(a)				do { if( (a)!=NULL ){ free(a); a=NULL; } } while (0)
#endif

#include "assert_klb.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

#include <stdio.h>

// Heap checking (via crtdbg) is windows-only, so use it cautiously
#ifdef _WIN32
  #include <crtdbg.h>
  #define		CHECKMEM()			klb_assert(_CrtCheckMemory(),"Heap Corrupted")
#else
  #define		CHECKMEM()			;
#endif
#define TASKCLID(a)					{ CKLBTask* pTsk = CKLBTaskMgr::getInstance().getCurrentTask(); u32 clID = pTsk ? pTsk->getClassID() : 0; klb_assert(clID != (a),"Task Found"); }
#define ISCLID(a)					(CKLBTaskMgr::getInstance().getCurrentTask() ? ((CKLBTaskMgr::getInstance().getCurrentTask()->getClassID()) == a) : (0 == a)))

#ifdef DEBUG_TEXTURE_PACKER
	void checkVirtualDocState();
	void dumpVirtualDocState(void* lookupObj);
#endif

#endif
