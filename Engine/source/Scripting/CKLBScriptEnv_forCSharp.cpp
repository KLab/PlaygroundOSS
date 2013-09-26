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
#include "CKLBScriptEnv.h"	

#ifdef __CSHARP_VERSION__

//#undef DEBUG_WITH_MD

#include "CKLBUtility.h"
#include "klb_vararg.h"
#include "CKLBScrollBarIF.h"

//Mono includes
#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <mono/utils/mono-logger.h>
#include <exception>

#ifdef _WIN32
#include <Windows.h>
#endif


class CKLBScriptEnvCSharp : public CKLBScriptEnv {
public:
	static MonoDomain* s_domain;

	static MonoMethod* s_destroyPtr;
	static MonoMethod* s_worldCallBackPtr;
	static MonoMethod* s_doCallBackPtrV;
	static MonoMethod* s_doCallBackPtrII;
	static MonoMethod* s_doCallBackPtrIII;
	static MonoMethod* s_doCallBackPtrIIII;
	static MonoMethod* s_doCallBackPtrS;
	static MonoMethod* s_doCallBackPtrSII;
	static MonoMethod* s_doCallBackPtrSU;
	static MonoMethod* s_doCallBackPtrSS;
	static MonoMethod* s_doCallBackPtrUS;
	static MonoMethod* s_doCallBackPtrUSS;
	static MonoMethod* s_doCallBackPtrU;
	static MonoMethod* s_doCallBackPtrUU;
	static MonoMethod* s_doCallBackPtrUFF;
	static MonoMethod* s_doCallBackPtrUI;
	static MonoMethod* s_doCallBackPtrUII;
	static MonoMethod* s_doCallBackPtrUIIII;
	static MonoMethod* s_doCallBackPtrUIIUU;
	static MonoMethod* s_doCallBackPtrUUII;
	static MonoMethod* s_doCallBackPtrUUUII;
	static MonoMethod* s_doCallBackPtrIIIP_retB;
	static MonoMethod* s_doCallBackPtrFS;

	CKLBScriptEnvCSharp()	{}

	~CKLBScriptEnvCSharp()	{}
};

MonoDomain* CKLBScriptEnvCSharp::s_domain					= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_destroyPtr				= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_worldCallBackPtr			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrV			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrII			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrIII			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrIIII		= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrS			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrSII			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrSU			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrSS			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUS			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUSS			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrU			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUU			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUFF			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUI			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUII			= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUIIII		= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUIIUU		= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUUII		= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrUUUII		= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrIIIP_retB	= NULL;
MonoMethod* CKLBScriptEnvCSharp::s_doCallBackPtrFS			= NULL;


CKLBScriptEnv&	CKLBScriptEnv::getInstance() {
	static CKLBScriptEnvCSharp env;
	return env;
}

CKLBScriptEnv::CKLBScriptEnv() {
}

CKLBScriptEnv::~CKLBScriptEnv() {
}

//
// CKLBScriptEnv_forCSharp.cpp
//	
u32 m_call				= 0;
u32 g_errorFlag			= 0;
const char* g_errorStr	= NULL;

u32* CKLBScriptEnv::getCallCounter()
{
	return &m_call;
}

u32* CKLBScriptEnv::getErrorReader() 
{
	return &g_errorFlag;
}

const char* CKLBScriptEnv::getErrorString()
{
	return g_errorStr;
}

void setError(const char* err) {
	g_errorFlag = 1;
	if (g_errorStr) {
		KLBDELETEA(g_errorStr);
		g_errorStr = NULL;
	}
	if (err) {
		g_errorStr = CKLBUtility::copyString(err);
	}
}

void CKLBScriptEnv::resetError()
{
	g_errorFlag = 0;
	KLBDELETEA(g_errorStr);
	g_errorStr = NULL;
}

void CKLBScriptEnv::errMsg(const char * str) {
	error(str);
}

void CKLBScriptEnv::error(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	char msg[1024];
	vsprintf(msg, fmt, ap);
	va_end(ap);

	setError(msg);
}

bool CKLBScriptEnv::boot(const char* bootScriptURL)
{
	CKLBScriptEnvCSharp* _this = reinterpret_cast<CKLBScriptEnvCSharp*>(this);

	//mono_set_dirs("../../libs/lib/","../../etc/");
	mono_set_dirs("C:\\Users\\Administrateur\\Desktop\\KLab\\KLABPROJ\\trunk\\Engine\\porting\\Win32\\Output\\Debug_CSharp\\libs\\lib","../../etc/");
	MonoAssembly* assembly;
	MonoMethodDesc* mdesc;
	MonoImage* image;
	MonoAssembly* bootAsm;
	MonoImage* bootImg;

//TODO : better platform support	
#ifndef _WIN32
#ifndef __MACH__
	mono_jit_set_aot_only(true);
#endif
#endif

#ifdef DEBUG_WITH_MD
	mono_debug_init(MONO_DEBUG_FORMAT_MONO);

	char* options[] = {
		"--soft-breakpoints", // makes mono embedded able to catch all C# exceptions.
		"--debugger-agent=transport=dt_socket,address=127.0.0.1:10000", // send debug messages to MonoDevelop listener
	};
	mono_jit_parse_options(sizeof(options)/sizeof(char*), (char**)options);
#endif

	//const char* frameworkPath = CPFInterface::getInstance().platform().getFullPath("asset://MyCSharpLibForWindows.dll");
	const char* frameworkPath = "C:\\KLabCSEG\\FrameworkTestSuite\\FrameworkTestSuite\\.publish\\iphone\\MyCSharpLibForWindows.dll";

	CKLBScriptEnvCSharp::s_domain = mono_jit_init_version(frameworkPath, "v4.0");
	if(!CKLBScriptEnvCSharp::s_domain)
	{
		klb_assertAlways("Mono JIT init failed (this is NOT a matter of JIT).");
		return false;
	}

#ifdef DEBUG_WITH_MD
	mono_debug_domain_create(CKLBScriptEnvCSharp::s_domain);
#endif

	try {
		assembly = mono_domain_assembly_open (CKLBScriptEnvCSharp::s_domain, frameworkPath);
	}
	catch(...) {
		delete[] frameworkPath;
	}
	if(!assembly) {
		klb_assertAlways("C# assembly loading failed.");
		return false;
	}
	image = mono_assembly_get_image(assembly);

	//const char* bootPath = CPFInterface::getInstance().platform().getFullPath(bootScriptURL);
	const char* bootPath = "C:\\KLabCSEG\\FrameworkTestSuite\\FrameworkTestSuite\\.publish\\iphone\\start.dll";
	try {
		bootAsm = mono_domain_assembly_open (CKLBScriptEnvCSharp::s_domain, bootPath);
	}
	catch(...) {
		delete[] bootPath;
	}
	if(!bootAsm) {
		klb_assertAlways("C# boot assembly loading failed.");
		return false;
	}
	bootImg = mono_assembly_get_image(bootAsm);

	//
	// Parameters for mono_method_desc_new() are optional if there is 1 and only 1 method with this name in C#.
	//
	mdesc = mono_method_desc_new("NativeManagement:destroyFromNative(uint)", false);
	CKLBScriptEnvCSharp::s_destroyPtr = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("CKLBWorld:callBackFunction", false);
	CKLBScriptEnvCSharp::s_worldCallBackPtr = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackV(uint)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrV = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackII(uint,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackIII(uint,int,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrIII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackIIII(uint,int,int,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrIIII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackS(uint,intptr)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrS = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackSII(uint,intptr,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrSII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackSU(uint,intptr,uint)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrSU = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackSS(uint,intptr,intptr)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrSS = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUS(uint,uint,intptr)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUS = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUSS(uint,uint,intptr,intptr)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUSS = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackU(uint,uint)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrU = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);
	
	mdesc = mono_method_desc_new("NativeManagement:doCallBackUU(uint,uint,uint)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUU = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUFF", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUFF = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);
	
	mdesc = mono_method_desc_new("NativeManagement:doCallBackUI(uint,uint,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUI = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUII(uint,uint,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUIIII(uint,uint,int,int,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUIIII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);
	
	mdesc = mono_method_desc_new("NativeManagement:doCallBackUIIUU(uint,uint,int,int,uint,uint)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUIIUU = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackUUII(uint,uint,uint,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUUII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);
	
	mdesc = mono_method_desc_new("NativeManagement:doCallBackUUUII(uint,uint,uint,uint,int,int)", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrUUUII = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackIIIP_retB", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrIIIP_retB = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("NativeManagement:doCallBackFS", false);
	CKLBScriptEnvCSharp::s_doCallBackPtrFS = mono_method_desc_search_in_image(mdesc,image);
	mono_method_desc_free(mdesc);

	mdesc = mono_method_desc_new("Program:start", false);
	MonoMethod *method = mono_method_desc_search_in_image(mdesc,bootImg);
	MonoObject* exception = 0;
	MonoObject* result = mono_runtime_invoke(method,NULL,NULL,&exception);
	if(exception)	//an exception has been caught
	{
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("CKLBScriptEnv::boot raised an exception : %s", mono_string_to_utf8(message));
	}

	mono_method_desc_free(mdesc);

	return true;
}

//Does nothing, function kept for compatibility with Lua.
bool CKLBScriptEnv::setupScriptEnv() {
	return true;
}

void CKLBScriptEnv::finishScriptEnv() {
	resetError();
	
	// TODO C# : determine how to do it the right way.
	/*
	mono_debug_cleanup();
	
	mono_jit_cleanup(CKLBScriptEnvCSharp::s_domain);
	if(!mono_domain_finalize(CKLBScriptEnvCSharp::s_domain, 0)) {
		klb_assertAlways("Mono domain did not finalized correctly.");
	}
	
	CKLBScriptEnvCSharp::s_domain = NULL;
	*/
}



void CKLBScriptEnv::destroy(u32 handle)
{
	void* args[2];
	args[0] = &handle;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_destroyPtr,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("CKLBScriptEnv::destroy raised an exception : %s", mono_string_to_utf8(message));
	}
}

void callbackV(u32 cbInfos)
{
	void* args[1];
	args[0] = &cbInfos;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrV,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackV raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackII(u32 cbInfos, s32 int_1, s32 int_2)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &int_1;
	args[2] = &int_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackIII(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3)
{
	void* args[4];
	args[0] = &cbInfos;
	args[1] = &int_1;
	args[2] = &int_2;
	args[3] = &int_3;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrIII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackIII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackIIII(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3, s32 int_4)
{
	void* args[5];
	args[0] = &cbInfos;
	args[1] = &int_1;
	args[2] = &int_2;
	args[3] = &int_3;
	args[4] = &int_4;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrIIII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackIIII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackS(u32 cbInfos, const char* string_1)
{
	void* args[2];
	args[0] = &cbInfos;
	args[1] = &string_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrS,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackS raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackSII(u32 cbInfos, const char* string_1, s32 int_1, s32 int_2)
{
	void* args[4];
	args[0] = &cbInfos;
	args[1] = &string_1;
	args[2] = &int_1;
	args[3] = &int_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrSII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackSII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackSU(u32 cbInfos, const char* string_1, u32 uint_1)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &string_1;
	args[2] = &uint_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrSU,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackSU raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackSS(u32 cbInfos, const char* string_1, const char* string_2)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &string_1;
	args[2] = &string_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrSS,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackSS raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUS(u32 cbInfos, u32 uint_1, const char* string_1)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &string_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUS,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUS raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUSS(u32 cbInfos, u32 uint_1, const char* string_1, const char* string_2)
{
	void* args[4];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &string_1;
	args[3] = &string_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUSS,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUSS raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackU(u32 cbInfos, u32 uint_1)
{
	void* args[2];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrU,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackU raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUU(u32 cbInfos, u32 uint_1, u32 uint_2)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &uint_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUU,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUU raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUFF(u32 cbInfos, u32 uint_1, float float_1, float float_2)
{
	void* args[4];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &float_1;
	args[3] = &float_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUFF,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUFF raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUI(u32 cbInfos, u32 uint_1, s32 int_1)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &int_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUI,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUI raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUII(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2)
{
	void* args[4];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &int_1;
	args[3] = &int_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUIIII(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2, s32 int_3, s32 int_4)
{
	void* args[6];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &int_1;
	args[3] = &int_2;
	args[4] = &int_3;
	args[5] = &int_4;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUIIII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUIIII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUIIUU(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2, u32 uint_2, u32 uint_3)
{
	void* args[6];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &int_1;
	args[3] = &int_2;
	args[4] = &uint_2;
	args[5] = &uint_3;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUIIUU,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUIIUU raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUUII(u32 cbInfos, u32 uint_1, u32 uint_2, s32 int_1, s32 int_2)
{
	void* args[5];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &uint_2;
	args[3] = &int_1;
	args[4] = &int_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUUII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUUII raised an exception : %s", mono_string_to_utf8(message));
	}
}
void callbackUUUII(u32 cbInfos, u32 uint_1, u32 uint_2, u32 uint_3, s32 int_1, s32 int_2)
{
	void* args[6];
	args[0] = &cbInfos;
	args[1] = &uint_1;
	args[2] = &uint_2;
	args[3] = &uint_3;
	args[4] = &int_1;
	args[5] = &int_2;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrUUUII,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackUUUII raised an exception : %s", mono_string_to_utf8(message));
	}
}
bool callbackIIIP_retB(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3, void* ptr_1)
{
	void* args[5];
	args[0] = &cbInfos;
	args[1] = &int_1;
	args[2] = &int_2;
	args[3] = &int_3;
	args[4] = &ptr_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrIIIP_retB,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackIIIP_retB raised an exception : %s", mono_string_to_utf8(message));
	}
	if(result) {
		return *(int*)mono_object_unbox(result);
	}
}
void callbackFS(u32 cbInfos, float float_1, const char* string_1)
{
	void* args[3];
	args[0] = &cbInfos;
	args[1] = &float_1;
	args[2] = &string_1;
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_doCallBackPtrFS,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
		DEBUG_PRINT("callbackFS raised an exception : %s", mono_string_to_utf8(message));
	}
}

void CKLBScriptEnv::call_onDie					(const char* funcNAme, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// This callback is stored for each C# Object with an index of 5 in the Delegate array.
	callbackV((5<<29) + objectHandle);
}

// Generic Task
void CKLBScriptEnv::call_genTaskExecute			(const char* funcName, CKLBObjectScriptable* obj, u32 deltaT, const char* arrayIndex)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackU(objectHandle, deltaT);
}

void CKLBScriptEnv::call_genTaskDie				(const char* funcName, CKLBObjectScriptable* obj, const char* arrayIndex)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	if(objectHandle != _NULLHANDLER) {
		callbackV((1<<29) + objectHandle);
	}
}

void CKLBScriptEnv::call_intervalTimerExecute	(const char* funcName, CKLBObjectScriptable* obj, u32 timerID)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// timerID is useless for C#
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_asyncLoader			(const char* funcName, CKLBObjectScriptable* obj, u32 loaded, u32 total)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUU(objectHandle, loaded, total);
}

void CKLBScriptEnv::call_asyncFileCopy			(const char* funcName, CKLBObjectScriptable* obj, u32 donePerc, u32 doneSize) 
{
    klb_assertAlways("TODO");
}

void CKLBScriptEnv::call_webTask				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* url)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUS(objectHandle, type, url);
}

void CKLBScriptEnv::call_pause					(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_resume					(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_storeEvent				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* itemID, const char* param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUSS(objectHandle, type, itemID, param);
}

void CKLBScriptEnv::call_fromSincVM				(const char* funcName, CKLBObjectScriptable* obj, u32 id, s32 param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI(objectHandle, id, param);
}

void CKLBScriptEnv::call_eventVirtualDoc		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 param1, s32 param2, s32 param3, s32 param4)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, param1, param2, param3, param4);
}

void CKLBScriptEnv::call_touchPad				(const char* funcName, CKLBObjectScriptable* obj)
{
	klb_assertAlways("Call back interface for C#");
}

void CKLBScriptEnv::call_touchPadCSharp			(CKLBObjectScriptable* obj, u32 execount, u32 type, u32 id, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUUUII(objectHandle, execount, type, id, x, y);
}

void CKLBScriptEnv::call_button                 (const char* funcName, CKLBObjectScriptable* obj)
{
    klb_assertAlways("TODO");
}

void CKLBScriptEnv::call_textInput				(const char* funcName, CKLBObjectScriptable* obj, const char* txt, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSU(objectHandle, txt, id);
}

void CKLBScriptEnv::call_eventSelectable		(const char* funcName, CKLBObjectScriptable* obj, const char* name, s32 type, s32 param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSII(objectHandle, name, type, param);
}

void CKLBScriptEnv::call_eventSwf				(const char* funcName, CKLBObjectScriptable* obj, const char* label)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackS(objectHandle, label);
}

// 2 call back for list

void CKLBScriptEnv::call_eventUIListDynamic		(const char* funcName, CKLBObjectScriptable* obj, u32 index, u32 id) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((2<<29) + objectHandle, index, id);
}

void CKLBScriptEnv::call_eventUIList			(const char* funcName, CKLBObjectScriptable* obj, u32 type, u32 itemCnt, s32 listLength, s32 pos)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUUII((1<<29) + objectHandle, type, itemCnt, listLength, pos);
}

void CKLBScriptEnv::call_eventUIListDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 param1, s32 param2)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, param1, param2);
}

void CKLBScriptEnv::call_eventDragIF			(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, deltaX, deltaY);
}

// UI Control
// 5 call back for UI Control
void CKLBScriptEnv::call_eventUIControlDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, deltaX, deltaY);
}

void CKLBScriptEnv::call_eventUIControlPinch	(const char* funcName, CKLBObjectScriptable* obj, u32 type, float pinch, float rot)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUFF((1<<29) + objectHandle, type, pinch, rot);
}

void CKLBScriptEnv::call_eventUIControlClick	(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((2<<29) + objectHandle, x, y);
}

void CKLBScriptEnv::call_eventUIControlDblClick	(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((3<<29) + objectHandle, x, y);
}

void CKLBScriptEnv::call_eventUIControlLongTap	(const char* funcName, CKLBObjectScriptable* obj, u32 time, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUII((4<<29) + objectHandle, time, x, y);
}

// UI Drag Icon
void CKLBScriptEnv::call_eventDragIcon		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 dragX, s32 dragY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUII(objectHandle, type, dragX, dragY);
}

// UI Movie
void CKLBScriptEnv::call_eventMovie			(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Cell Anim
void CKLBScriptEnv::call_eventCellAnim		(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Canvas
void CKLBScriptEnv::call_canvasOnDraw		(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Node Pack Anim
void CKLBScriptEnv::call_eventNodeAnimPack	(const char* funcName, CKLBObjectScriptable* obj, const char * name, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// Special Case : owned by different classes : use 4 to avoid conflict.
	callbackSU((4<<29) + objectHandle, name, id);
}

// UI Touch Event UI
void CKLBScriptEnv::call_eventUITouchEvent	(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 dx, s32 dy)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, dx, dy);
}

// CKLBDebugMenu
void CKLBScriptEnv::call_eventDebugItem		(const char* funcName, CKLBObjectScriptable* obj, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackU(objectHandle, id);
}

// UI Scroll Bar / UI List task
void CKLBScriptEnv::call_eventScrollBar		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 pos)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI((3<<29) + objectHandle, type, pos);
}

void CKLBScriptEnv::call_eventScrollBarStop	(const char* funcName, CKLBObjectScriptable* obj, s32 pos)
{
	if(!obj) { return; }

	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI((3<<29) + objectHandle, CKLBScrollBarIF::SCROLLBAR_STOPPED, pos);
}

// World Task
void CKLBScriptEnv::call_eventWorld			(const char* funcName, CKLBObjectScriptable* obj, s32 serial, s32 msg, s32 status)
{
	m_call++;
	void* args[4];
	args[0] = &serial;
	args[1] = &msg;
	args[2] = &status;
	args[3] = (int*)&funcName; // funcname is in fact an int* to the callback index.
	MonoObject* exception;
	MonoObject* result = mono_runtime_invoke(CKLBScriptEnvCSharp::s_worldCallBackPtr,NULL,args,&exception);
	if(exception) {
		MonoString* message = mono_object_to_string(exception,NULL);
	}
}

void CKLBScriptEnv::call_eventUpdateDownload	(const char* funcName, CKLBObjectScriptable* obj, double progress, const char* progressStr) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackFS(objectHandle,(float)progress,progressStr);
}

void CKLBScriptEnv::call_eventUpdateZIP		(const char* funcName, CKLBObjectScriptable* obj, s32 progress, s32 total) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII(objectHandle,progress,total);
}

void CKLBScriptEnv::call_eventUpdateComplete	(const char* funcName, CKLBObjectScriptable* obj) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_eventUpdateError(const char* funcName, CKLBObjectScriptable* obj) {
    klb_assertAlways("TODO");
}

bool CKLBScriptEnv::call_netAPI_callback(const char* funcName, CKLBObjectScriptable* obj, s32 uniq, s32 msg, s32 status, CKLBJsonItem * pRoot) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	return callbackIIIP_retB(objectHandle,uniq,msg,status,pRoot);
}

void CKLBScriptEnv::call_netAPI_versionUp		(const char* funcName, CKLBObjectScriptable* obj, const char* clientVer, const char* serverVer) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSS((1<<29) + objectHandle,clientVer,serverVer);
}

#endif
