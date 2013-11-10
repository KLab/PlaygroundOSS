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
#ifndef KLBPlatformMetricsCommon_h
#define KLBPlatformMetricsCommon_h

// WARNING: this file should never included directly from Engine, nor from Porting layer.
// You should always include "KLBPlatformMetrics.h" instead.

// CPU usage measurement type constants
// bits layout: abbbbbbbcccccccc
//              a					: begin/end flag; 0=begin, 1=end
//               bbbbbbb			: task type flag
//                      cccccccc	: subtask type flag
#define TASKTYPE_BEGIN				(0x0000)
#define TASKTYPE_END				(0x8000)
#define TASKTYPE_LUA				(0x0100)
#define TASKTYPE_LUA_LOAD			((TASKTYPE_LUA) | 0x01)
#define TASKTYPE_LUA_EXEC			((TASKTYPE_LUA) | 0x02)
#define TASKTYPE_LUA_GC				((TASKTYPE_LUA) | 0x03)
#define TASKTYPE_TEX				(0x0200)
#define TASKTYPE_TEX_LOAD			((TASKTYPE_TEX) | 0x10)
#define TASKTYPE_TEX_LOAD_INFLATE	((TASKTYPE_TEX_LOAD) | 0x1)
#define TASKTYPE_TEX_LOAD_LOWCONV	((TASKTYPE_TEX_LOAD) | 0x2)
#define TASKTYPE_TEX_LOAD_OGL		((TASKTYPE_TEX_LOAD) | 0x3)
#define TASKTYPE_TEX_UPLOAD			((TASKTYPE_TEX) | 0x20)
#define TASKTYPE_SOUND				(0x0300)
#define TASKTYPE_SOUND_DECODE		((TASKTYPE_SOUND) | 0x01)
#define TASKTYPE_DRAW				(0x0400)
#define TASKTYPE_DRAW_ANIMATION		((TASKTYPE_DRAW) | 0x10)

// default (empty) macros. should be overridden using #undef inside platforms' "KLBPlatformMetrics.h".
#define REPORT_METRICS(msg) 
#define MEASURE_THREAD_CPU_BEGIN(type) 
#define MEASURE_THREAD_CPU_END(type) 

#endif
