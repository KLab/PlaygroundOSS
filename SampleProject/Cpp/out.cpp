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
#include "framework.cpp"

/* Stack Trace :  */
static const uniChar _$_cteStr118[] = {83,116,97,99,107,32,84,114,97,99,101,32,58,32};
static System::String* _$_cteStr118Obj;

/* Error Message :  */
static const uniChar _$_cteStr117[] = {69,114,114,111,114,32,77,101,115,115,97,103,101,32,58,32};
static System::String* _$_cteStr117Obj;

/* Exception Type :  */
static const uniChar _$_cteStr116[] = {69,120,99,101,112,116,105,111,110,32,84,121,112,101,32,58,32};
static System::String* _$_cteStr116Obj;

/* ####### Exception Handling ####### */
static const uniChar _$_cteStr115[] = {35,35,35,35,35,35,35,32,69,120,99,101,112,116,105,111,110,32,72,97,110,100,108,105,110,103,32,35,35,35,35,35,35,35};
static System::String* _$_cteStr115Obj;

/* Hello World from C#! */
static const uniChar _$_cteStr114[] = {72,101,108,108,111,32,87,111,114,108,100,32,102,114,111,109,32,67,35,33};
static System::String* _$_cteStr114Obj;

/* georgia */
static const uniChar _$_cteStr113[] = {103,101,111,114,103,105,97};
static System::String* _$_cteStr113Obj;

/* Hello from C# In Console. */
static const uniChar _$_cteStr112[] = {72,101,108,108,111,32,102,114,111,109,32,67,35,32,73,110,32,67,111,110,115,111,108,101,46};
static System::String* _$_cteStr112Obj;


class Program;

namespace SampleGame {
    class Program;

}
class SampleGame::Program : public System::Object {

public:
    void _ctor_Program();
    static void start();
    static void Main(System::Array<System::String*>* args);
    Program();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 272;
};
//
// Class/Struct Implementation
//

//=============================
// Implementation of 'Program'
//=============================

void SampleGame::Program::_ctor_Program() {
}

/*static*/
void SampleGame::Program::start()
{
    Main((System::Array<System::String*>*)NULL);
}

/*static*/
void SampleGame::Program::Main(System::Array<System::String*>* args)
{
    System::Console::WriteLine(_$_cteStr112Obj);
    TRY
    {
        EnginePrototype::CKLBUILabel* label = CS_NEW EnginePrototype::CKLBUILabel((EnginePrototype::CKLBUITask*)NULL,1000,300,100,0,_$_cteStr113Obj,16,_$_cteStr114Obj,EnginePrototype::CKLBUILabel::EALIGN::MID);
    }
    CTRY
    FIRSTCATCH(System::Exception,ex)
    {
        System::Console::WriteLine(_$_cteStr40Obj);
        System::Console::WriteLine(_$_cteStr115Obj);
        System::Console::WriteLine(_$_cteStr40Obj);
        System::Console::WriteLine();
        System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr116Obj)->_appendStr(ex->GetType$())->_appendClose());
        System::Console::WriteLine();
        System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr117Obj)->_appendStr(ex->_acc_gMessage$())->_appendClose());
        System::Console::WriteLine();
        System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr118Obj)->_appendStr(ex->_acc_gStackTrace$())->_appendClose());
    }
    FINALLY
    ETRY
}

SampleGame::Program::Program() { _ctor_Program(); }



/*virtual*/
bool SampleGame::Program::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Program,System::Object);
}

/*virtual*/
u32 SampleGame::Program::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void SampleGame::Program::_releaseGC() {
}
/*virtual*/
void SampleGame::Program::_moveAlert(u32 offset) {
}

//
// Class/Struct Implementation
//

//=============================
// Implementation of 'Program'
//=============================

void Program::_ctor_Program() {
}

/*static*/
void Program::start()
{
    SampleGame::Program::start();
}



/*virtual*/
bool Program::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Program,System::Object);
}

/*virtual*/
u32 Program::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void Program::_releaseGC() {
}
/*virtual*/
void Program::_moveAlert(u32 offset) {
}


void initAllStatic() {
}

void registerWorldGC() {
    initFramework();
    // Register Strings into the GC.
    _$_cteStr118Obj = CS_NEW System::String(_$_cteStr118,sizeof(_$_cteStr118) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr118Obj);

    _$_cteStr117Obj = CS_NEW System::String(_$_cteStr117,sizeof(_$_cteStr117) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr117Obj);

    _$_cteStr116Obj = CS_NEW System::String(_$_cteStr116,sizeof(_$_cteStr116) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr116Obj);

    _$_cteStr115Obj = CS_NEW System::String(_$_cteStr115,sizeof(_$_cteStr115) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr115Obj);

    _$_cteStr114Obj = CS_NEW System::String(_$_cteStr114,sizeof(_$_cteStr114) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr114Obj);

    _$_cteStr113Obj = CS_NEW System::String(_$_cteStr113,sizeof(_$_cteStr113) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr113Obj);

    _$_cteStr112Obj = CS_NEW System::String(_$_cteStr112,sizeof(_$_cteStr112) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr112Obj);


    initAllStatic();


}
