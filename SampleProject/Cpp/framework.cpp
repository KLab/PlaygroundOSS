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
#include "framework.h"

//
// Delegate Implementation
//

class EnginePrototype::_Delegate_Base_FunctionPointerV_inner0 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 59;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerV_inner0,System::Delegate);
    }

    inline void call$() { CHCKTHIS; (*this)(); }
    virtual void operator() ()=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerV_inner0 : public EnginePrototype::_Delegate_Base_FunctionPointerV_inner0
{
private:
    void (TClass::*fpt)();
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerV_inner0(TClass* _pt2Object, void(TClass::*_fpt)()) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerV_inner0::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()() { (*pt2Object.*fpt)();}
};

class EnginePrototype::_DelegateS_FunctionPointerV_inner0 : public EnginePrototype::_Delegate_Base_FunctionPointerV_inner0{
private:
    void (*fpt)();
public:

    _DelegateS_FunctionPointerV_inner0(void(*_fpt)())    { fpt=_fpt; };

    virtual void operator()() { (*fpt)(); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerII_inner1 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 61;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerII_inner1,System::Delegate);
    }

    inline void call$(s32 int_1,s32 int_2) { CHCKTHIS; (*this)(int_1,int_2); }
    virtual void operator() (s32 int_1,s32 int_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerII_inner1 : public EnginePrototype::_Delegate_Base_FunctionPointerII_inner1
{
private:
    void (TClass::*fpt)(s32 int_1,s32 int_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerII_inner1(TClass* _pt2Object, void(TClass::*_fpt)(s32 int_1,s32 int_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerII_inner1::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32 int_1,s32 int_2) { (*pt2Object.*fpt)(int_1,int_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerII_inner1 : public EnginePrototype::_Delegate_Base_FunctionPointerII_inner1{
private:
    void (*fpt)(s32 int_1,s32 int_2);
public:

    _DelegateS_FunctionPointerII_inner1(void(*_fpt)(s32 int_1,s32 int_2))    { fpt=_fpt; };

    virtual void operator()(s32 int_1,s32 int_2) { (*fpt)(int_1,int_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerIII_inner2 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 63;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerIII_inner2,System::Delegate);
    }

    inline void call$(s32 int_1,s32 int_2,s32 int_3) { CHCKTHIS; (*this)(int_1,int_2,int_3); }
    virtual void operator() (s32 int_1,s32 int_2,s32 int_3)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerIII_inner2 : public EnginePrototype::_Delegate_Base_FunctionPointerIII_inner2
{
private:
    void (TClass::*fpt)(s32 int_1,s32 int_2,s32 int_3);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerIII_inner2(TClass* _pt2Object, void(TClass::*_fpt)(s32 int_1,s32 int_2,s32 int_3)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerIII_inner2::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32 int_1,s32 int_2,s32 int_3) { (*pt2Object.*fpt)(int_1,int_2,int_3);}
};

class EnginePrototype::_DelegateS_FunctionPointerIII_inner2 : public EnginePrototype::_Delegate_Base_FunctionPointerIII_inner2{
private:
    void (*fpt)(s32 int_1,s32 int_2,s32 int_3);
public:

    _DelegateS_FunctionPointerIII_inner2(void(*_fpt)(s32 int_1,s32 int_2,s32 int_3))    { fpt=_fpt; };

    virtual void operator()(s32 int_1,s32 int_2,s32 int_3) { (*fpt)(int_1,int_2,int_3); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerIIII_inner3 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 65;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerIIII_inner3,System::Delegate);
    }

    inline void call$(s32 int_1,s32 int_2,s32 int_3,s32 int_4) { CHCKTHIS; (*this)(int_1,int_2,int_3,int_4); }
    virtual void operator() (s32 int_1,s32 int_2,s32 int_3,s32 int_4)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerIIII_inner3 : public EnginePrototype::_Delegate_Base_FunctionPointerIIII_inner3
{
private:
    void (TClass::*fpt)(s32 int_1,s32 int_2,s32 int_3,s32 int_4);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerIIII_inner3(TClass* _pt2Object, void(TClass::*_fpt)(s32 int_1,s32 int_2,s32 int_3,s32 int_4)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerIIII_inner3::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32 int_1,s32 int_2,s32 int_3,s32 int_4) { (*pt2Object.*fpt)(int_1,int_2,int_3,int_4);}
};

class EnginePrototype::_DelegateS_FunctionPointerIIII_inner3 : public EnginePrototype::_Delegate_Base_FunctionPointerIIII_inner3{
private:
    void (*fpt)(s32 int_1,s32 int_2,s32 int_3,s32 int_4);
public:

    _DelegateS_FunctionPointerIIII_inner3(void(*_fpt)(s32 int_1,s32 int_2,s32 int_3,s32 int_4))    { fpt=_fpt; };

    virtual void operator()(s32 int_1,s32 int_2,s32 int_3,s32 int_4) { (*fpt)(int_1,int_2,int_3,int_4); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerS_inner4 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 67;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerS_inner4,System::Delegate);
    }

    inline void call$(s32* intptr_1) { CHCKTHIS; (*this)(intptr_1); }
    virtual void operator() (s32* intptr_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerS_inner4 : public EnginePrototype::_Delegate_Base_FunctionPointerS_inner4
{
private:
    void (TClass::*fpt)(s32* intptr_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerS_inner4(TClass* _pt2Object, void(TClass::*_fpt)(s32* intptr_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerS_inner4::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32* intptr_1) { (*pt2Object.*fpt)(intptr_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerS_inner4 : public EnginePrototype::_Delegate_Base_FunctionPointerS_inner4{
private:
    void (*fpt)(s32* intptr_1);
public:

    _DelegateS_FunctionPointerS_inner4(void(*_fpt)(s32* intptr_1))    { fpt=_fpt; };

    virtual void operator()(s32* intptr_1) { (*fpt)(intptr_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerSII_inner5 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 69;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerSII_inner5,System::Delegate);
    }

    inline void call$(s32* intptr_1,s32 int_1,s32 int_2) { CHCKTHIS; (*this)(intptr_1,int_1,int_2); }
    virtual void operator() (s32* intptr_1,s32 int_1,s32 int_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerSII_inner5 : public EnginePrototype::_Delegate_Base_FunctionPointerSII_inner5
{
private:
    void (TClass::*fpt)(s32* intptr_1,s32 int_1,s32 int_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerSII_inner5(TClass* _pt2Object, void(TClass::*_fpt)(s32* intptr_1,s32 int_1,s32 int_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerSII_inner5::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32* intptr_1,s32 int_1,s32 int_2) { (*pt2Object.*fpt)(intptr_1,int_1,int_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerSII_inner5 : public EnginePrototype::_Delegate_Base_FunctionPointerSII_inner5{
private:
    void (*fpt)(s32* intptr_1,s32 int_1,s32 int_2);
public:

    _DelegateS_FunctionPointerSII_inner5(void(*_fpt)(s32* intptr_1,s32 int_1,s32 int_2))    { fpt=_fpt; };

    virtual void operator()(s32* intptr_1,s32 int_1,s32 int_2) { (*fpt)(intptr_1,int_1,int_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerSU_inner6 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 71;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerSU_inner6,System::Delegate);
    }

    inline void call$(s32* intptr_1,u32 uint_1) { CHCKTHIS; (*this)(intptr_1,uint_1); }
    virtual void operator() (s32* intptr_1,u32 uint_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerSU_inner6 : public EnginePrototype::_Delegate_Base_FunctionPointerSU_inner6
{
private:
    void (TClass::*fpt)(s32* intptr_1,u32 uint_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerSU_inner6(TClass* _pt2Object, void(TClass::*_fpt)(s32* intptr_1,u32 uint_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerSU_inner6::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32* intptr_1,u32 uint_1) { (*pt2Object.*fpt)(intptr_1,uint_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerSU_inner6 : public EnginePrototype::_Delegate_Base_FunctionPointerSU_inner6{
private:
    void (*fpt)(s32* intptr_1,u32 uint_1);
public:

    _DelegateS_FunctionPointerSU_inner6(void(*_fpt)(s32* intptr_1,u32 uint_1))    { fpt=_fpt; };

    virtual void operator()(s32* intptr_1,u32 uint_1) { (*fpt)(intptr_1,uint_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerSS_inner7 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 73;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerSS_inner7,System::Delegate);
    }

    inline void call$(s32* intptr_1,s32* intptr_2) { CHCKTHIS; (*this)(intptr_1,intptr_2); }
    virtual void operator() (s32* intptr_1,s32* intptr_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerSS_inner7 : public EnginePrototype::_Delegate_Base_FunctionPointerSS_inner7
{
private:
    void (TClass::*fpt)(s32* intptr_1,s32* intptr_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerSS_inner7(TClass* _pt2Object, void(TClass::*_fpt)(s32* intptr_1,s32* intptr_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerSS_inner7::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(s32* intptr_1,s32* intptr_2) { (*pt2Object.*fpt)(intptr_1,intptr_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerSS_inner7 : public EnginePrototype::_Delegate_Base_FunctionPointerSS_inner7{
private:
    void (*fpt)(s32* intptr_1,s32* intptr_2);
public:

    _DelegateS_FunctionPointerSS_inner7(void(*_fpt)(s32* intptr_1,s32* intptr_2))    { fpt=_fpt; };

    virtual void operator()(s32* intptr_1,s32* intptr_2) { (*fpt)(intptr_1,intptr_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUS_inner8 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 75;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUS_inner8,System::Delegate);
    }

    inline void call$(u32 uint_1,s32* intptr_1) { CHCKTHIS; (*this)(uint_1,intptr_1); }
    virtual void operator() (u32 uint_1,s32* intptr_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUS_inner8 : public EnginePrototype::_Delegate_Base_FunctionPointerUS_inner8
{
private:
    void (TClass::*fpt)(u32 uint_1,s32* intptr_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUS_inner8(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32* intptr_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUS_inner8::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32* intptr_1) { (*pt2Object.*fpt)(uint_1,intptr_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerUS_inner8 : public EnginePrototype::_Delegate_Base_FunctionPointerUS_inner8{
private:
    void (*fpt)(u32 uint_1,s32* intptr_1);
public:

    _DelegateS_FunctionPointerUS_inner8(void(*_fpt)(u32 uint_1,s32* intptr_1))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32* intptr_1) { (*fpt)(uint_1,intptr_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUSS_inner9 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 77;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUSS_inner9,System::Delegate);
    }

    inline void call$(u32 uint_1,s32* intptr_1,s32* intptr_2) { CHCKTHIS; (*this)(uint_1,intptr_1,intptr_2); }
    virtual void operator() (u32 uint_1,s32* intptr_1,s32* intptr_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUSS_inner9 : public EnginePrototype::_Delegate_Base_FunctionPointerUSS_inner9
{
private:
    void (TClass::*fpt)(u32 uint_1,s32* intptr_1,s32* intptr_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUSS_inner9(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32* intptr_1,s32* intptr_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUSS_inner9::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32* intptr_1,s32* intptr_2) { (*pt2Object.*fpt)(uint_1,intptr_1,intptr_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUSS_inner9 : public EnginePrototype::_Delegate_Base_FunctionPointerUSS_inner9{
private:
    void (*fpt)(u32 uint_1,s32* intptr_1,s32* intptr_2);
public:

    _DelegateS_FunctionPointerUSS_inner9(void(*_fpt)(u32 uint_1,s32* intptr_1,s32* intptr_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32* intptr_1,s32* intptr_2) { (*fpt)(uint_1,intptr_1,intptr_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerU_inner10 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 79;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerU_inner10,System::Delegate);
    }

    inline void call$(u32 uint_1) { CHCKTHIS; (*this)(uint_1); }
    virtual void operator() (u32 uint_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerU_inner10 : public EnginePrototype::_Delegate_Base_FunctionPointerU_inner10
{
private:
    void (TClass::*fpt)(u32 uint_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerU_inner10(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerU_inner10::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1) { (*pt2Object.*fpt)(uint_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerU_inner10 : public EnginePrototype::_Delegate_Base_FunctionPointerU_inner10{
private:
    void (*fpt)(u32 uint_1);
public:

    _DelegateS_FunctionPointerU_inner10(void(*_fpt)(u32 uint_1))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1) { (*fpt)(uint_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUU_inner11 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 81;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUU_inner11,System::Delegate);
    }

    inline void call$(u32 uint_1,u32 uint_2) { CHCKTHIS; (*this)(uint_1,uint_2); }
    virtual void operator() (u32 uint_1,u32 uint_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUU_inner11 : public EnginePrototype::_Delegate_Base_FunctionPointerUU_inner11
{
private:
    void (TClass::*fpt)(u32 uint_1,u32 uint_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUU_inner11(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,u32 uint_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUU_inner11::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,u32 uint_2) { (*pt2Object.*fpt)(uint_1,uint_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUU_inner11 : public EnginePrototype::_Delegate_Base_FunctionPointerUU_inner11{
private:
    void (*fpt)(u32 uint_1,u32 uint_2);
public:

    _DelegateS_FunctionPointerUU_inner11(void(*_fpt)(u32 uint_1,u32 uint_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,u32 uint_2) { (*fpt)(uint_1,uint_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUFF_inner12 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 83;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUFF_inner12,System::Delegate);
    }

    inline void call$(u32 uint_1,float float_1,float float_2) { CHCKTHIS; (*this)(uint_1,float_1,float_2); }
    virtual void operator() (u32 uint_1,float float_1,float float_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUFF_inner12 : public EnginePrototype::_Delegate_Base_FunctionPointerUFF_inner12
{
private:
    void (TClass::*fpt)(u32 uint_1,float float_1,float float_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUFF_inner12(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,float float_1,float float_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUFF_inner12::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,float float_1,float float_2) { (*pt2Object.*fpt)(uint_1,float_1,float_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUFF_inner12 : public EnginePrototype::_Delegate_Base_FunctionPointerUFF_inner12{
private:
    void (*fpt)(u32 uint_1,float float_1,float float_2);
public:

    _DelegateS_FunctionPointerUFF_inner12(void(*_fpt)(u32 uint_1,float float_1,float float_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,float float_1,float float_2) { (*fpt)(uint_1,float_1,float_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUI_inner13 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 85;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUI_inner13,System::Delegate);
    }

    inline void call$(u32 uint_1,s32 int_1) { CHCKTHIS; (*this)(uint_1,int_1); }
    virtual void operator() (u32 uint_1,s32 int_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUI_inner13 : public EnginePrototype::_Delegate_Base_FunctionPointerUI_inner13
{
private:
    void (TClass::*fpt)(u32 uint_1,s32 int_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUI_inner13(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32 int_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUI_inner13::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32 int_1) { (*pt2Object.*fpt)(uint_1,int_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerUI_inner13 : public EnginePrototype::_Delegate_Base_FunctionPointerUI_inner13{
private:
    void (*fpt)(u32 uint_1,s32 int_1);
public:

    _DelegateS_FunctionPointerUI_inner13(void(*_fpt)(u32 uint_1,s32 int_1))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32 int_1) { (*fpt)(uint_1,int_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUII_inner14 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 87;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUII_inner14,System::Delegate);
    }

    inline void call$(u32 uint_1,s32 int_1,s32 int_2) { CHCKTHIS; (*this)(uint_1,int_1,int_2); }
    virtual void operator() (u32 uint_1,s32 int_1,s32 int_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUII_inner14 : public EnginePrototype::_Delegate_Base_FunctionPointerUII_inner14
{
private:
    void (TClass::*fpt)(u32 uint_1,s32 int_1,s32 int_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUII_inner14(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32 int_1,s32 int_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUII_inner14::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2) { (*pt2Object.*fpt)(uint_1,int_1,int_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUII_inner14 : public EnginePrototype::_Delegate_Base_FunctionPointerUII_inner14{
private:
    void (*fpt)(u32 uint_1,s32 int_1,s32 int_2);
public:

    _DelegateS_FunctionPointerUII_inner14(void(*_fpt)(u32 uint_1,s32 int_1,s32 int_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2) { (*fpt)(uint_1,int_1,int_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUIIII_inner15 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 89;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUIIII_inner15,System::Delegate);
    }

    inline void call$(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4) { CHCKTHIS; (*this)(uint_1,int_1,int_2,int_3,int_4); }
    virtual void operator() (u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUIIII_inner15 : public EnginePrototype::_Delegate_Base_FunctionPointerUIIII_inner15
{
private:
    void (TClass::*fpt)(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUIIII_inner15(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUIIII_inner15::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4) { (*pt2Object.*fpt)(uint_1,int_1,int_2,int_3,int_4);}
};

class EnginePrototype::_DelegateS_FunctionPointerUIIII_inner15 : public EnginePrototype::_Delegate_Base_FunctionPointerUIIII_inner15{
private:
    void (*fpt)(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4);
public:

    _DelegateS_FunctionPointerUIIII_inner15(void(*_fpt)(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4) { (*fpt)(uint_1,int_1,int_2,int_3,int_4); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUIIUU_inner16 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 91;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUIIUU_inner16,System::Delegate);
    }

    inline void call$(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3) { CHCKTHIS; (*this)(uint_1,int_1,int_2,uint_2,uint_3); }
    virtual void operator() (u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUIIUU_inner16 : public EnginePrototype::_Delegate_Base_FunctionPointerUIIUU_inner16
{
private:
    void (TClass::*fpt)(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUIIUU_inner16(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUIIUU_inner16::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3) { (*pt2Object.*fpt)(uint_1,int_1,int_2,uint_2,uint_3);}
};

class EnginePrototype::_DelegateS_FunctionPointerUIIUU_inner16 : public EnginePrototype::_Delegate_Base_FunctionPointerUIIUU_inner16{
private:
    void (*fpt)(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3);
public:

    _DelegateS_FunctionPointerUIIUU_inner16(void(*_fpt)(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3) { (*fpt)(uint_1,int_1,int_2,uint_2,uint_3); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUUII_inner17 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 93;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUUII_inner17,System::Delegate);
    }

    inline void call$(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2) { CHCKTHIS; (*this)(uint_1,uint_2,int_1,int_2); }
    virtual void operator() (u32 uint_1,u32 uint_2,s32 int_1,s32 int_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUUII_inner17 : public EnginePrototype::_Delegate_Base_FunctionPointerUUII_inner17
{
private:
    void (TClass::*fpt)(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUUII_inner17(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUUII_inner17::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2) { (*pt2Object.*fpt)(uint_1,uint_2,int_1,int_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUUII_inner17 : public EnginePrototype::_Delegate_Base_FunctionPointerUUII_inner17{
private:
    void (*fpt)(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2);
public:

    _DelegateS_FunctionPointerUUII_inner17(void(*_fpt)(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,u32 uint_2,s32 int_1,s32 int_2) { (*fpt)(uint_1,uint_2,int_1,int_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerUUUII_inner18 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 95;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerUUUII_inner18,System::Delegate);
    }

    inline void call$(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2) { CHCKTHIS; (*this)(uint_1,uint_2,uint_3,int_1,int_2); }
    virtual void operator() (u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerUUUII_inner18 : public EnginePrototype::_Delegate_Base_FunctionPointerUUUII_inner18
{
private:
    void (TClass::*fpt)(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerUUUII_inner18(TClass* _pt2Object, void(TClass::*_fpt)(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerUUUII_inner18::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2) { (*pt2Object.*fpt)(uint_1,uint_2,uint_3,int_1,int_2);}
};

class EnginePrototype::_DelegateS_FunctionPointerUUUII_inner18 : public EnginePrototype::_Delegate_Base_FunctionPointerUUUII_inner18{
private:
    void (*fpt)(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2);
public:

    _DelegateS_FunctionPointerUUUII_inner18(void(*_fpt)(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2))    { fpt=_fpt; };

    virtual void operator()(u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2) { (*fpt)(uint_1,uint_2,uint_3,int_1,int_2); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerIIIP_retB_inner19 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 97;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerIIIP_retB_inner19,System::Delegate);
    }

    inline bool call$(s32 int_1,s32 int_2,s32 int_3,s32* obj_1) { CHCKTHIS; return (*this)(int_1,int_2,int_3,obj_1); }
    virtual bool operator() (s32 int_1,s32 int_2,s32 int_3,s32* obj_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerIIIP_retB_inner19 : public EnginePrototype::_Delegate_Base_FunctionPointerIIIP_retB_inner19
{
private:
    bool (TClass::*fpt)(s32 int_1,s32 int_2,s32 int_3,s32* obj_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerIIIP_retB_inner19(TClass* _pt2Object, bool(TClass::*_fpt)(s32 int_1,s32 int_2,s32 int_3,s32* obj_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerIIIP_retB_inner19::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual bool operator()(s32 int_1,s32 int_2,s32 int_3,s32* obj_1) { return (*pt2Object.*fpt)(int_1,int_2,int_3,obj_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerIIIP_retB_inner19 : public EnginePrototype::_Delegate_Base_FunctionPointerIIIP_retB_inner19{
private:
    bool (*fpt)(s32 int_1,s32 int_2,s32 int_3,s32* obj_1);
public:

    _DelegateS_FunctionPointerIIIP_retB_inner19(bool(*_fpt)(s32 int_1,s32 int_2,s32 int_3,s32* obj_1))    { fpt=_fpt; };

    virtual bool operator()(s32 int_1,s32 int_2,s32 int_3,s32* obj_1) { return (*fpt)(int_1,int_2,int_3,obj_1); };
};

class EnginePrototype::_Delegate_Base_FunctionPointerFS_inner20 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 99;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_FunctionPointerFS_inner20,System::Delegate);
    }

    inline void call$(float float_1,s32* intptr_1) { CHCKTHIS; (*this)(float_1,intptr_1); }
    virtual void operator() (float float_1,s32* intptr_1)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_FunctionPointerFS_inner20 : public EnginePrototype::_Delegate_Base_FunctionPointerFS_inner20
{
private:
    void (TClass::*fpt)(float float_1,s32* intptr_1);
    TClass* pt2Object;
public:

    _DelegateI_FunctionPointerFS_inner20(TClass* _pt2Object, void(TClass::*_fpt)(float float_1,s32* intptr_1)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_FunctionPointerFS_inner20::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(float float_1,s32* intptr_1) { (*pt2Object.*fpt)(float_1,intptr_1);}
};

class EnginePrototype::_DelegateS_FunctionPointerFS_inner20 : public EnginePrototype::_Delegate_Base_FunctionPointerFS_inner20{
private:
    void (*fpt)(float float_1,s32* intptr_1);
public:

    _DelegateS_FunctionPointerFS_inner20(void(*_fpt)(float float_1,s32* intptr_1))    { fpt=_fpt; };

    virtual void operator()(float float_1,s32* intptr_1) { (*fpt)(float_1,intptr_1); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner21 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 142;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner21,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total) { CHCKTHIS; (*this)(caller,loaded,total); }
    virtual void operator() (EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner21 : public EnginePrototype::_Delegate_Base_CallBack_inner21
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner21(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner21::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total) { (*pt2Object.*fpt)(caller,loaded,total);}
};

class EnginePrototype::_DelegateS_CallBack_inner21 : public EnginePrototype::_Delegate_Base_CallBack_inner21{
private:
    void (*fpt)(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total);
public:

    _DelegateS_CallBack_inner21(void(*_fpt)(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBAsyncLoader* caller,u32 loaded,u32 total) { (*fpt)(caller,loaded,total); };
};

class EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 145;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_ExecuteCallBack_inner22,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime) { CHCKTHIS; (*this)(caller,deltaTime); }
    virtual void operator() (EnginePrototype::CKLBGenericTask* caller,u32 deltaTime)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_ExecuteCallBack_inner22 : public EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime);
    TClass* pt2Object;
public:

    _DelegateI_ExecuteCallBack_inner22(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_ExecuteCallBack_inner22::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime) { (*pt2Object.*fpt)(caller,deltaTime);}
};

class EnginePrototype::_DelegateS_ExecuteCallBack_inner22 : public EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22{
private:
    void (*fpt)(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime);
public:

    _DelegateS_ExecuteCallBack_inner22(void(*_fpt)(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBGenericTask* caller,u32 deltaTime) { (*fpt)(caller,deltaTime); };
};

class EnginePrototype::_Delegate_Base_DieCallBack_inner23 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 147;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_DieCallBack_inner23,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBGenericTask* caller) { CHCKTHIS; (*this)(caller); }
    virtual void operator() (EnginePrototype::CKLBGenericTask* caller)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_DieCallBack_inner23 : public EnginePrototype::_Delegate_Base_DieCallBack_inner23
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBGenericTask* caller);
    TClass* pt2Object;
public:

    _DelegateI_DieCallBack_inner23(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBGenericTask* caller)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_DieCallBack_inner23::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBGenericTask* caller) { (*pt2Object.*fpt)(caller);}
};

class EnginePrototype::_DelegateS_DieCallBack_inner23 : public EnginePrototype::_Delegate_Base_DieCallBack_inner23{
private:
    void (*fpt)(EnginePrototype::CKLBGenericTask* caller);
public:

    _DelegateS_DieCallBack_inner23(void(*_fpt)(EnginePrototype::CKLBGenericTask* caller))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBGenericTask* caller) { (*fpt)(caller); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner24 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 150;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner24,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBIntervalTimer* caller) { CHCKTHIS; (*this)(caller); }
    virtual void operator() (EnginePrototype::CKLBIntervalTimer* caller)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner24 : public EnginePrototype::_Delegate_Base_CallBack_inner24
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBIntervalTimer* caller);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner24(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBIntervalTimer* caller)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner24::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBIntervalTimer* caller) { (*pt2Object.*fpt)(caller);}
};

class EnginePrototype::_DelegateS_CallBack_inner24 : public EnginePrototype::_Delegate_Base_CallBack_inner24{
private:
    void (*fpt)(EnginePrototype::CKLBIntervalTimer* caller);
public:

    _DelegateS_CallBack_inner24(void(*_fpt)(EnginePrototype::CKLBIntervalTimer* caller))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBIntervalTimer* caller) { (*fpt)(caller); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner25 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 154;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner25,System::Delegate);
    }

    inline bool call$(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot) { CHCKTHIS; return (*this)(caller,uniq,msg,status,pRoot); }
    virtual bool operator() (EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner25 : public EnginePrototype::_Delegate_Base_CallBack_inner25
{
private:
    bool (TClass::*fpt)(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner25(TClass* _pt2Object, bool(TClass::*_fpt)(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner25::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual bool operator()(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot) { return (*pt2Object.*fpt)(caller,uniq,msg,status,pRoot);}
};

class EnginePrototype::_DelegateS_CallBack_inner25 : public EnginePrototype::_Delegate_Base_CallBack_inner25{
private:
    bool (*fpt)(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot);
public:

    _DelegateS_CallBack_inner25(bool(*_fpt)(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot))    { fpt=_fpt; };

    virtual bool operator()(EnginePrototype::CKLBNetAPI* caller,s32 uniq,s32 msg,s32 status,s32* pRoot) { return (*fpt)(caller,uniq,msg,status,pRoot); };
};

class EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 156;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBackVersionUp_inner26,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer) { CHCKTHIS; (*this)(caller,clientVer,serverVer); }
    virtual void operator() (EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBackVersionUp_inner26 : public EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer);
    TClass* pt2Object;
public:

    _DelegateI_CallBackVersionUp_inner26(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBackVersionUp_inner26::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer) { (*pt2Object.*fpt)(caller,clientVer,serverVer);}
};

class EnginePrototype::_DelegateS_CallBackVersionUp_inner26 : public EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26{
private:
    void (*fpt)(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer);
public:

    _DelegateS_CallBackVersionUp_inner26(void(*_fpt)(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBNetAPI* caller,System::String* clientVer,System::String* serverVer) { (*fpt)(caller,clientVer,serverVer); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner27 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 160;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner27,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param) { CHCKTHIS; (*this)(caller,type,itemID,param); }
    virtual void operator() (EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner27 : public EnginePrototype::_Delegate_Base_CallBack_inner27
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner27(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner27::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param) { (*pt2Object.*fpt)(caller,type,itemID,param);}
};

class EnginePrototype::_DelegateS_CallBack_inner27 : public EnginePrototype::_Delegate_Base_CallBack_inner27{
private:
    void (*fpt)(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param);
public:

    _DelegateS_CallBack_inner27(void(*_fpt)(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBStoreService* caller,s32 type,System::String* itemID,System::String* param) { (*fpt)(caller,type,itemID,param); };
};

class EnginePrototype::_Delegate_Base_onDieCallBack_inner28 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 163;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_onDieCallBack_inner28,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBTask* caller) { CHCKTHIS; (*this)(caller); }
    virtual void operator() (EnginePrototype::CKLBTask* caller)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_onDieCallBack_inner28 : public EnginePrototype::_Delegate_Base_onDieCallBack_inner28
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBTask* caller);
    TClass* pt2Object;
public:

    _DelegateI_onDieCallBack_inner28(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBTask* caller)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_onDieCallBack_inner28::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBTask* caller) { (*pt2Object.*fpt)(caller);}
};

class EnginePrototype::_DelegateS_onDieCallBack_inner28 : public EnginePrototype::_Delegate_Base_onDieCallBack_inner28{
private:
    void (*fpt)(EnginePrototype::CKLBTask* caller);
public:

    _DelegateS_onDieCallBack_inner28(void(*_fpt)(EnginePrototype::CKLBTask* caller))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBTask* caller) { (*fpt)(caller); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner29 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 168;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner29,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUICanvas* caller) { CHCKTHIS; (*this)(caller); }
    virtual void operator() (EnginePrototype::CKLBUICanvas* caller)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner29 : public EnginePrototype::_Delegate_Base_CallBack_inner29
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUICanvas* caller);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner29(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUICanvas* caller)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner29::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUICanvas* caller) { (*pt2Object.*fpt)(caller);}
};

class EnginePrototype::_DelegateS_CallBack_inner29 : public EnginePrototype::_Delegate_Base_CallBack_inner29{
private:
    void (*fpt)(EnginePrototype::CKLBUICanvas* caller);
public:

    _DelegateS_CallBack_inner29(void(*_fpt)(EnginePrototype::CKLBUICanvas* caller))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUICanvas* caller) { (*fpt)(caller); };
};

class EnginePrototype::_Delegate_Base_OnClickCallBack_inner30 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 172;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_OnClickCallBack_inner30,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { CHCKTHIS; (*this)(caller,x,y); }
    virtual void operator() (EnginePrototype::CKLBUIControl* caller,s32 x,s32 y)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_OnClickCallBack_inner30 : public EnginePrototype::_Delegate_Base_OnClickCallBack_inner30
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y);
    TClass* pt2Object;
public:

    _DelegateI_OnClickCallBack_inner30(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_OnClickCallBack_inner30::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { (*pt2Object.*fpt)(caller,x,y);}
};

class EnginePrototype::_DelegateS_OnClickCallBack_inner30 : public EnginePrototype::_Delegate_Base_OnClickCallBack_inner30{
private:
    void (*fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y);
public:

    _DelegateS_OnClickCallBack_inner30(void(*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { (*fpt)(caller,x,y); };
};

class EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 174;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_OnDblClickCallBack_inner31,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { CHCKTHIS; (*this)(caller,x,y); }
    virtual void operator() (EnginePrototype::CKLBUIControl* caller,s32 x,s32 y)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_OnDblClickCallBack_inner31 : public EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y);
    TClass* pt2Object;
public:

    _DelegateI_OnDblClickCallBack_inner31(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_OnDblClickCallBack_inner31::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { (*pt2Object.*fpt)(caller,x,y);}
};

class EnginePrototype::_DelegateS_OnDblClickCallBack_inner31 : public EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31{
private:
    void (*fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y);
public:

    _DelegateS_OnDblClickCallBack_inner31(void(*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 x,s32 y) { (*fpt)(caller,x,y); };
};

class EnginePrototype::_Delegate_Base_OnDragCallBack_inner32 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 176;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_OnDragCallBack_inner32,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY) { CHCKTHIS; (*this)(caller,mode,x,y,mvX,mvY); }
    virtual void operator() (EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_OnDragCallBack_inner32 : public EnginePrototype::_Delegate_Base_OnDragCallBack_inner32
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY);
    TClass* pt2Object;
public:

    _DelegateI_OnDragCallBack_inner32(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_OnDragCallBack_inner32::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY) { (*pt2Object.*fpt)(caller,mode,x,y,mvX,mvY);}
};

class EnginePrototype::_DelegateS_OnDragCallBack_inner32 : public EnginePrototype::_Delegate_Base_OnDragCallBack_inner32{
private:
    void (*fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY);
public:

    _DelegateS_OnDragCallBack_inner32(void(*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 mode,s32 x,s32 y,s32 mvX,s32 mvY) { (*fpt)(caller,mode,x,y,mvX,mvY); };
};

class EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 178;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_OnPinchCallBack_inner33,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation) { CHCKTHIS; (*this)(caller,mode,pinch,rotation); }
    virtual void operator() (EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_OnPinchCallBack_inner33 : public EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation);
    TClass* pt2Object;
public:

    _DelegateI_OnPinchCallBack_inner33(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_OnPinchCallBack_inner33::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation) { (*pt2Object.*fpt)(caller,mode,pinch,rotation);}
};

class EnginePrototype::_DelegateS_OnPinchCallBack_inner33 : public EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33{
private:
    void (*fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation);
public:

    _DelegateS_OnPinchCallBack_inner33(void(*_fpt)(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,s32 mode,float pinch,float rotation) { (*fpt)(caller,mode,pinch,rotation); };
};

class EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 180;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_OnLongTapCallBack_inner34,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y) { CHCKTHIS; (*this)(caller,elapsedTime,x,y); }
    virtual void operator() (EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_OnLongTapCallBack_inner34 : public EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y);
    TClass* pt2Object;
public:

    _DelegateI_OnLongTapCallBack_inner34(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_OnLongTapCallBack_inner34::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y) { (*pt2Object.*fpt)(caller,elapsedTime,x,y);}
};

class EnginePrototype::_DelegateS_OnLongTapCallBack_inner34 : public EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34{
private:
    void (*fpt)(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y);
public:

    _DelegateS_OnLongTapCallBack_inner34(void(*_fpt)(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIControl* caller,u32 elapsedTime,s32 x,s32 y) { (*fpt)(caller,elapsedTime,x,y); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner35 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 185;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner35,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID) { CHCKTHIS; (*this)(caller,cmdID); }
    virtual void operator() (EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner35 : public EnginePrototype::_Delegate_Base_CallBack_inner35
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner35(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner35::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID) { (*pt2Object.*fpt)(caller,cmdID);}
};

class EnginePrototype::_DelegateS_CallBack_inner35 : public EnginePrototype::_Delegate_Base_CallBack_inner35{
private:
    void (*fpt)(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID);
public:

    _DelegateS_CallBack_inner35(void(*_fpt)(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIDebugItem* caller,u32 cmdID) { (*fpt)(caller,cmdID); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner36 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 188;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner36,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y) { CHCKTHIS; (*this)(caller,type,x,y); }
    virtual void operator() (EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner36 : public EnginePrototype::_Delegate_Base_CallBack_inner36
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner36(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner36::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y) { (*pt2Object.*fpt)(caller,type,x,y);}
};

class EnginePrototype::_DelegateS_CallBack_inner36 : public EnginePrototype::_Delegate_Base_CallBack_inner36{
private:
    void (*fpt)(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y);
public:

    _DelegateS_CallBack_inner36(void(*_fpt)(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIDragIcon* caller,u32 type,s32 x,s32 y) { (*fpt)(caller,type,x,y); };
};

class EnginePrototype::_Delegate_Base_SelectableCallBack_inner37 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 195;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_SelectableCallBack_inner37,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param) { CHCKTHIS; (*this)(caller,name,type,param); }
    virtual void operator() (EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_SelectableCallBack_inner37 : public EnginePrototype::_Delegate_Base_SelectableCallBack_inner37
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param);
    TClass* pt2Object;
public:

    _DelegateI_SelectableCallBack_inner37(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_SelectableCallBack_inner37::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param) { (*pt2Object.*fpt)(caller,name,type,param);}
};

class EnginePrototype::_DelegateS_SelectableCallBack_inner37 : public EnginePrototype::_Delegate_Base_SelectableCallBack_inner37{
private:
    void (*fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param);
public:

    _DelegateS_SelectableCallBack_inner37(void(*_fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIForm* caller,System::String* name,s32 type,s32 param) { (*fpt)(caller,name,type,param); };
};

class EnginePrototype::_Delegate_Base_AnimCallBack_inner38 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 197;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_AnimCallBack_inner38,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id) { CHCKTHIS; (*this)(caller,name,id); }
    virtual void operator() (EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_AnimCallBack_inner38 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner38
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id);
    TClass* pt2Object;
public:

    _DelegateI_AnimCallBack_inner38(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_AnimCallBack_inner38::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id) { (*pt2Object.*fpt)(caller,name,id);}
};

class EnginePrototype::_DelegateS_AnimCallBack_inner38 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner38{
private:
    void (*fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id);
public:

    _DelegateS_AnimCallBack_inner38(void(*_fpt)(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIForm* caller,System::String* name,u32 id) { (*fpt)(caller,name,id); };
};

class EnginePrototype::_Delegate_Base_AnimCallBack_inner39 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 201;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_AnimCallBack_inner39,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id) { CHCKTHIS; (*this)(caller,name,id); }
    virtual void operator() (EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_AnimCallBack_inner39 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner39
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id);
    TClass* pt2Object;
public:

    _DelegateI_AnimCallBack_inner39(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_AnimCallBack_inner39::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id) { (*pt2Object.*fpt)(caller,name,id);}
};

class EnginePrototype::_DelegateS_AnimCallBack_inner39 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner39{
private:
    void (*fpt)(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id);
public:

    _DelegateS_AnimCallBack_inner39(void(*_fpt)(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIGroup* caller,System::String* name,u32 id) { (*fpt)(caller,name,id); };
};

class EnginePrototype::_Delegate_Base_LimitCallBack_inner40 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 206;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_LimitCallBack_inner40,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos) { CHCKTHIS; (*this)(caller,type,itemCount,listLength,pos); }
    virtual void operator() (EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_LimitCallBack_inner40 : public EnginePrototype::_Delegate_Base_LimitCallBack_inner40
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos);
    TClass* pt2Object;
public:

    _DelegateI_LimitCallBack_inner40(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_LimitCallBack_inner40::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos) { (*pt2Object.*fpt)(caller,type,itemCount,listLength,pos);}
};

class EnginePrototype::_DelegateS_LimitCallBack_inner40 : public EnginePrototype::_Delegate_Base_LimitCallBack_inner40{
private:
    void (*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos);
public:

    _DelegateS_LimitCallBack_inner40(void(*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,u32 itemCount,s32 listLength,s32 pos) { (*fpt)(caller,type,itemCount,listLength,pos); };
};

class EnginePrototype::_Delegate_Base_DragCallBack_inner41 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 208;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_DragCallBack_inner41,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2) { CHCKTHIS; (*this)(caller,type,x,y,param1,param2); }
    virtual void operator() (EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_DragCallBack_inner41 : public EnginePrototype::_Delegate_Base_DragCallBack_inner41
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2);
    TClass* pt2Object;
public:

    _DelegateI_DragCallBack_inner41(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_DragCallBack_inner41::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2) { (*pt2Object.*fpt)(caller,type,x,y,param1,param2);}
};

class EnginePrototype::_DelegateS_DragCallBack_inner41 : public EnginePrototype::_Delegate_Base_DragCallBack_inner41{
private:
    void (*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2);
public:

    _DelegateS_DragCallBack_inner41(void(*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,s32 x,s32 y,s32 param1,s32 param2) { (*fpt)(caller,type,x,y,param1,param2); };
};

class EnginePrototype::_Delegate_Base_DynamicCallBack_inner42 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 210;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_DynamicCallBack_inner42,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIList* caller,s32 index,s32 id) { CHCKTHIS; (*this)(caller,index,id); }
    virtual void operator() (EnginePrototype::CKLBUIList* caller,s32 index,s32 id)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_DynamicCallBack_inner42 : public EnginePrototype::_Delegate_Base_DynamicCallBack_inner42
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIList* caller,s32 index,s32 id);
    TClass* pt2Object;
public:

    _DelegateI_DynamicCallBack_inner42(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIList* caller,s32 index,s32 id)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_DynamicCallBack_inner42::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIList* caller,s32 index,s32 id) { (*pt2Object.*fpt)(caller,index,id);}
};

class EnginePrototype::_DelegateS_DynamicCallBack_inner42 : public EnginePrototype::_Delegate_Base_DynamicCallBack_inner42{
private:
    void (*fpt)(EnginePrototype::CKLBUIList* caller,s32 index,s32 id);
public:

    _DelegateS_DynamicCallBack_inner42(void(*_fpt)(EnginePrototype::CKLBUIList* caller,s32 index,s32 id))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIList* caller,s32 index,s32 id) { (*fpt)(caller,index,id); };
};

class EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 212;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_ScrollBarCallBack_inner43,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos) { CHCKTHIS; (*this)(caller,type,pos); }
    virtual void operator() (EnginePrototype::CKLBUIList* caller,u32 type,s32 pos)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_ScrollBarCallBack_inner43 : public EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos);
    TClass* pt2Object;
public:

    _DelegateI_ScrollBarCallBack_inner43(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_ScrollBarCallBack_inner43::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos) { (*pt2Object.*fpt)(caller,type,pos);}
};

class EnginePrototype::_DelegateS_ScrollBarCallBack_inner43 : public EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43{
private:
    void (*fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos);
public:

    _DelegateS_ScrollBarCallBack_inner43(void(*_fpt)(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIList* caller,u32 type,s32 pos) { (*fpt)(caller,type,pos); };
};

class EnginePrototype::_Delegate_Base_AnimCallBack_inner44 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 214;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_AnimCallBack_inner44,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id) { CHCKTHIS; (*this)(caller,name,id); }
    virtual void operator() (EnginePrototype::CKLBUIList* caller,System::String* name,u32 id)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_AnimCallBack_inner44 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner44
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id);
    TClass* pt2Object;
public:

    _DelegateI_AnimCallBack_inner44(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_AnimCallBack_inner44::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id) { (*pt2Object.*fpt)(caller,name,id);}
};

class EnginePrototype::_DelegateS_AnimCallBack_inner44 : public EnginePrototype::_Delegate_Base_AnimCallBack_inner44{
private:
    void (*fpt)(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id);
public:

    _DelegateS_AnimCallBack_inner44(void(*_fpt)(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIList* caller,System::String* name,u32 id) { (*fpt)(caller,name,id); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner45 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 220;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner45,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIMoviePlayer* caller) { CHCKTHIS; (*this)(caller); }
    virtual void operator() (EnginePrototype::CKLBUIMoviePlayer* caller)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner45 : public EnginePrototype::_Delegate_Base_CallBack_inner45
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIMoviePlayer* caller);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner45(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIMoviePlayer* caller)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner45::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIMoviePlayer* caller) { (*pt2Object.*fpt)(caller);}
};

class EnginePrototype::_DelegateS_CallBack_inner45 : public EnginePrototype::_Delegate_Base_CallBack_inner45{
private:
    void (*fpt)(EnginePrototype::CKLBUIMoviePlayer* caller);
public:

    _DelegateS_CallBack_inner45(void(*_fpt)(EnginePrototype::CKLBUIMoviePlayer* caller))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIMoviePlayer* caller) { (*fpt)(caller); };
};

class EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 233;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_ScrollBarCallBack_inner46,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos) { CHCKTHIS; (*this)(caller,type,pos); }
    virtual void operator() (EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_ScrollBarCallBack_inner46 : public EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos);
    TClass* pt2Object;
public:

    _DelegateI_ScrollBarCallBack_inner46(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_ScrollBarCallBack_inner46::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos) { (*pt2Object.*fpt)(caller,type,pos);}
};

class EnginePrototype::_DelegateS_ScrollBarCallBack_inner46 : public EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46{
private:
    void (*fpt)(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos);
public:

    _DelegateS_ScrollBarCallBack_inner46(void(*_fpt)(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIScrollBar* caller,u32 type,s32 pos) { (*fpt)(caller,type,pos); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner47 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 238;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner47,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label) { CHCKTHIS; (*this)(caller,label); }
    virtual void operator() (EnginePrototype::CKLBUISWFPlayer* caller,System::String* label)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner47 : public EnginePrototype::_Delegate_Base_CallBack_inner47
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner47(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner47::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label) { (*pt2Object.*fpt)(caller,label);}
};

class EnginePrototype::_DelegateS_CallBack_inner47 : public EnginePrototype::_Delegate_Base_CallBack_inner47{
private:
    void (*fpt)(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label);
public:

    _DelegateS_CallBack_inner47(void(*_fpt)(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUISWFPlayer* caller,System::String* label) { (*fpt)(caller,label); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner48 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 256;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner48,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id) { CHCKTHIS; (*this)(caller,txt,id); }
    virtual void operator() (EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner48 : public EnginePrototype::_Delegate_Base_CallBack_inner48
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner48(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner48::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id) { (*pt2Object.*fpt)(caller,txt,id);}
};

class EnginePrototype::_DelegateS_CallBack_inner48 : public EnginePrototype::_Delegate_Base_CallBack_inner48{
private:
    void (*fpt)(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id);
public:

    _DelegateS_CallBack_inner48(void(*_fpt)(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUITextInput* caller,System::String* txt,u32 id) { (*fpt)(caller,txt,id); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner49 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 260;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner49,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y) { CHCKTHIS; (*this)(caller,execount,type,id,x,y); }
    virtual void operator() (EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner49 : public EnginePrototype::_Delegate_Base_CallBack_inner49
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner49(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner49::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y) { (*pt2Object.*fpt)(caller,execount,type,id,x,y);}
};

class EnginePrototype::_DelegateS_CallBack_inner49 : public EnginePrototype::_Delegate_Base_CallBack_inner49{
private:
    void (*fpt)(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y);
public:

    _DelegateS_CallBack_inner49(void(*_fpt)(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUITouchPad* caller,u32 execount,u32 type,u32 id,s32 x,s32 y) { (*fpt)(caller,execount,type,id,x,y); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner50 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 265;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner50,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY) { CHCKTHIS; (*this)(caller,type,x,y,moveX,moveY); }
    virtual void operator() (EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner50 : public EnginePrototype::_Delegate_Base_CallBack_inner50
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner50(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner50::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY) { (*pt2Object.*fpt)(caller,type,x,y,moveX,moveY);}
};

class EnginePrototype::_DelegateS_CallBack_inner50 : public EnginePrototype::_Delegate_Base_CallBack_inner50{
private:
    void (*fpt)(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY);
public:

    _DelegateS_CallBack_inner50(void(*_fpt)(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIVirtualDoc* caller,s32 type,s32 x,s32 y,u32 moveX,u32 moveY) { (*fpt)(caller,type,x,y,moveX,moveY); };
};

class EnginePrototype::_Delegate_Base_CallBack_inner51 : public System::Delegate
{
private:
static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 270;
public:
    virtual bool _isInstanceOf(u32 typeID) {
	    _INSTANCEOF(_Delegate_Base_CallBack_inner51,System::Delegate);
    }

    inline void call$(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url) { CHCKTHIS; (*this)(caller,uint1,url); }
    virtual void operator() (EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url)=0;
    virtual u32 _processGC() { return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { }
};

template <class TClass> class EnginePrototype::_DelegateI_CallBack_inner51 : public EnginePrototype::_Delegate_Base_CallBack_inner51
{
private:
    void (TClass::*fpt)(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url);
    TClass* pt2Object;
public:

    _DelegateI_CallBack_inner51(TClass* _pt2Object, void(TClass::*_fpt)(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url)) {
        if (!_pt2Object) { THROW(CS_NEW System::ArgumentException()); }
        System::__GCObject::_RefSetValue((System::__GCObject**)&pt2Object, _pt2Object);
        fpt=_fpt;
    }

    virtual u32 _processGC() { if (pt2Object) { System::Memory::pushList(pt2Object,0); } return System::__GCObject::COMPLETE; }
    virtual void _releaseGC() { if (pt2Object && !pt2Object->isFreed()) { pt2Object->_removeRef((System::__GCObject**)&pt2Object); } }
    virtual void _moveAlert(u32 offset) { 
        _Delegate_Base_CallBack_inner51::_moveAlert(offset);
        u8* oldPtr; u8* newPtr;
        if(pt2Object) {
            newPtr = (u8*)(&pt2Object); oldPtr = newPtr - offset;
            pt2Object->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
        }
    }

    virtual void operator()(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url) { (*pt2Object.*fpt)(caller,uint1,url);}
};

class EnginePrototype::_DelegateS_CallBack_inner51 : public EnginePrototype::_Delegate_Base_CallBack_inner51{
private:
    void (*fpt)(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url);
public:

    _DelegateS_CallBack_inner51(void(*_fpt)(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url))    { fpt=_fpt; };

    virtual void operator()(EnginePrototype::CKLBUIWebArea* caller,u32 uint1,System::String* url) { (*fpt)(caller,uint1,url); };
};

//
// Class/Struct Implementation
//

//=============================
// Implementation of 'CKLBException'
//=============================

void EnginePrototype::CKLBException::_ctor_CKLBException() {
}

EnginePrototype::CKLBException::CKLBException(System::String* msg) : System::Exception(msg)
{
    _ctor_CKLBException();
}

EnginePrototype::CKLBException::CKLBException() { _ctor_CKLBException(); }



/*virtual*/
bool EnginePrototype::CKLBException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBException,System::Exception);
}

/*virtual*/
u32 EnginePrototype::CKLBException::_processGC() {
    System::Exception::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBException::_releaseGC() {
    System::Exception::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBException::_moveAlert(u32 offset) {
    System::Exception::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBExceptionNotImplemented'
//=============================

void EnginePrototype::CKLBExceptionNotImplemented::_ctor_CKLBExceptionNotImplemented() {
}

EnginePrototype::CKLBExceptionNotImplemented::CKLBExceptionNotImplemented(System::String* msg) : EnginePrototype::CKLBException(msg)
{
    _ctor_CKLBExceptionNotImplemented();
}

EnginePrototype::CKLBExceptionNotImplemented::CKLBExceptionNotImplemented() { _ctor_CKLBExceptionNotImplemented(); }



/*virtual*/
bool EnginePrototype::CKLBExceptionNotImplemented::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBExceptionNotImplemented,EnginePrototype::CKLBException);
}

/*virtual*/
u32 EnginePrototype::CKLBExceptionNotImplemented::_processGC() {
    EnginePrototype::CKLBException::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBExceptionNotImplemented::_releaseGC() {
    EnginePrototype::CKLBException::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBExceptionNotImplemented::_moveAlert(u32 offset) {
    EnginePrototype::CKLBException::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBExceptionForbiddenMethod'
//=============================

void EnginePrototype::CKLBExceptionForbiddenMethod::_ctor_CKLBExceptionForbiddenMethod() {
}

EnginePrototype::CKLBExceptionForbiddenMethod::CKLBExceptionForbiddenMethod(System::String* msg) : EnginePrototype::CKLBException(msg)
{
    _ctor_CKLBExceptionForbiddenMethod();
}

EnginePrototype::CKLBExceptionForbiddenMethod::CKLBExceptionForbiddenMethod() { _ctor_CKLBExceptionForbiddenMethod(); }



/*virtual*/
bool EnginePrototype::CKLBExceptionForbiddenMethod::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBExceptionForbiddenMethod,EnginePrototype::CKLBException);
}

/*virtual*/
u32 EnginePrototype::CKLBExceptionForbiddenMethod::_processGC() {
    EnginePrototype::CKLBException::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBExceptionForbiddenMethod::_releaseGC() {
    EnginePrototype::CKLBException::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBExceptionForbiddenMethod::_moveAlert(u32 offset) {
    EnginePrototype::CKLBException::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBExceptionNullCppObject'
//=============================

void EnginePrototype::CKLBExceptionNullCppObject::_ctor_CKLBExceptionNullCppObject() {
}

EnginePrototype::CKLBExceptionNullCppObject::CKLBExceptionNullCppObject(System::String* msg) : EnginePrototype::CKLBException(msg)
{
    _ctor_CKLBExceptionNullCppObject();
}

EnginePrototype::CKLBExceptionNullCppObject::CKLBExceptionNullCppObject() { _ctor_CKLBExceptionNullCppObject(); }



/*virtual*/
bool EnginePrototype::CKLBExceptionNullCppObject::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBExceptionNullCppObject,EnginePrototype::CKLBException);
}

/*virtual*/
u32 EnginePrototype::CKLBExceptionNullCppObject::_processGC() {
    EnginePrototype::CKLBException::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBExceptionNullCppObject::_releaseGC() {
    EnginePrototype::CKLBException::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBExceptionNullCppObject::_moveAlert(u32 offset) {
    EnginePrototype::CKLBException::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBExceptionTooOld'
//=============================

void EnginePrototype::CKLBExceptionTooOld::_ctor_CKLBExceptionTooOld() {
}

EnginePrototype::CKLBExceptionTooOld::CKLBExceptionTooOld(System::String* msg) : EnginePrototype::CKLBException(msg)
{
    _ctor_CKLBExceptionTooOld();
}

EnginePrototype::CKLBExceptionTooOld::CKLBExceptionTooOld() { _ctor_CKLBExceptionTooOld(); }



/*virtual*/
bool EnginePrototype::CKLBExceptionTooOld::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBExceptionTooOld,EnginePrototype::CKLBException);
}

/*virtual*/
u32 EnginePrototype::CKLBExceptionTooOld::_processGC() {
    EnginePrototype::CKLBException::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBExceptionTooOld::_releaseGC() {
    EnginePrototype::CKLBException::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBExceptionTooOld::_moveAlert(u32 offset) {
    EnginePrototype::CKLBException::_moveAlert(offset);

}

//=============================
// Implementation of 'GameObject'
//=============================

void EnginePrototype::GameObject::_ctor_GameObject() {
    m_handle = NULLHANDLER;
    _sm_callbacksArray(CS_NEW System::Array< System::Delegate* >(NBCALLBACKS));
}

/*static*/
u32 EnginePrototype::GameObject::_ext_CKLBObjectScriptable_getScriptContext(s32* p)
{
    return CKLBObjectScriptable_getScriptContext(p);
}

/*static*/
void EnginePrototype::GameObject::_ext_CKLBObjectScriptable_setScriptContext(s32* p,u32 handle)
{
    CKLBObjectScriptable_setScriptContext(p,handle);
}

bool EnginePrototype::GameObject::isBoundToCpp()
{
    return _gm_cppObject$() != System::IntPtr::Zero;
}

inline bool EnginePrototype::GameObject::isBoundToCpp$() { CHCKTHIS; return isBoundToCpp(); }

EnginePrototype::GameObject::GameObject(u32 typeID)
{
    _ctor_GameObject();
    _sm_typeID$(typeID);
    EnginePrototype::WrapperReg::getInstance()->registerGameObject$(this);
    _sm_cppObject$(System::IntPtr::Zero);
}

void EnginePrototype::GameObject::bind(s32* cppObj)
{
    if (cppObj != System::IntPtr::Zero)
    {
        if (_gm_cppObject$() == System::IntPtr::Zero)
        {
            u32 nativeHandle = _ext_CKLBObjectScriptable_getScriptContext(cppObj);
            if (nativeHandle == NULLHANDLER)
            {
                EnginePrototype::NativeManagement::registerWrapper(cppObj,_gm_handle$());
                _sm_cppObject$(cppObj);
                doSetupCallbacks$();
            }
            else
            {
                THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr6Obj));
            }
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr7Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr8Obj));
    }
}

inline void EnginePrototype::GameObject::bind$(s32* cppObj) { CHCKTHIS; return bind(cppObj); }

void EnginePrototype::GameObject::bind(System::String* nodeName)
{
    if (nodeName == NULL)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr9Obj));
    }
    if (_gm_cppObject$() != System::IntPtr::Zero)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr7Obj));
    }
    EnginePrototype::NodeIterator* nodeIterator = CS_NEW EnginePrototype::NodeIterator(EnginePrototype::NativeManagement::getContextCounter(),EnginePrototype::NodeIterator::getRoot());
    if (nodeIterator->find$(nodeName,false))
    {
        s32* cppObj = nodeIterator->getAsUITask$()->_acc_gCppObject$();
        u32 nativeHandle = _ext_CKLBObjectScriptable_getScriptContext(cppObj);
        if (nativeHandle == NULLHANDLER)
        {
            EnginePrototype::NativeManagement::registerWrapper(cppObj,_gm_handle$());
            _sm_cppObject$(cppObj);
            doSetupCallbacks$();
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr6Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr10Obj));
    }
}

inline void EnginePrototype::GameObject::bind$(System::String* nodeName) { CHCKTHIS; return bind(nodeName); }

void EnginePrototype::GameObject::unbind()
{
    System::Console::WriteLine(_$_cteStr11Obj);
    if (_gm_cppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBObjectScriptable_setScriptContext(_gm_cppObject$(),NULLHANDLER);
        _sm_cppObject$(System::IntPtr::Zero);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    System::Console::WriteLine(_$_cteStr12Obj);
}

inline void EnginePrototype::GameObject::unbind$() { CHCKTHIS; return unbind(); }

/*virtual*/
void EnginePrototype::GameObject::doSetupCallbacks()
{
}

inline void EnginePrototype::GameObject::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::GameObject::clearInternals()
{
}

inline void EnginePrototype::GameObject::clearInternals$() { CHCKTHIS; return clearInternals(); }

/*virtual*/
void EnginePrototype::GameObject::Dispose()
{
    System::Console::WriteLine(_$_cteStr13Obj);
    clearInternals$();
    if (_gm_handle$() != NULLHANDLER)
    {
        EnginePrototype::WrapperReg::getInstance()->unregisterGameObject$(this);
    }
    if (_acc_gCppObject$() != System::IntPtr::Zero)
    {
        unbind$();
    }
    System::Console::WriteLine(_$_cteStr14Obj);
}

inline void EnginePrototype::GameObject::Dispose$() { CHCKTHIS; return Dispose(); }

/*virtual*/
void EnginePrototype::GameObject::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr15Obj));
}

inline void EnginePrototype::GameObject::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*static*/
void EnginePrototype::GameObject::staticSetDelegate(u32 handle,System::Delegate* delegatePtr,System::String* delegateName)
{
    EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle)->setDelegate$(delegatePtr,delegateName);
}

void EnginePrototype::GameObject::forceSetupCallBackWithVirtual(System::String* delegateName)
{
    setDelegate$((System::Delegate*)NULL,delegateName);
}

inline void EnginePrototype::GameObject::forceSetupCallBackWithVirtual$(System::String* delegateName) { CHCKTHIS; return forceSetupCallBackWithVirtual(delegateName); }

void EnginePrototype::GameObject::registerCallBack(System::Delegate* callback,u32 index)
{
    if (0 <= index && index < NBCALLBACKS)
    {
        if (callback != NULL)
        {
            _gm_callbacksArray$()->_idx_s$(index,callback);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr16Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

inline void EnginePrototype::GameObject::registerCallBack$(System::Delegate* callback,u32 index) { CHCKTHIS; return registerCallBack(callback,index); }

System::Delegate* EnginePrototype::GameObject::getCallBack(u32 index)
{
    if (0 <= index && index < NBCALLBACKS)
    {
        System::Delegate* d = _gm_callbacksArray$()->_idx_g$(index);
        return d;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

inline System::Delegate* EnginePrototype::GameObject::getCallBack$(u32 index) { CHCKTHIS; return getCallBack(index); }

EnginePrototype::GameObject::GameObject() { _ctor_GameObject(); }

inline System::Object* EnginePrototype::GameObject::_sm_tag(System::Object* _$value)  { return (System::Object*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_tag,_$value); }
inline System::Object* EnginePrototype::GameObject::_sm_tag$(System::Object* _$value) { CHCKTHIS; return _sm_tag(_$value); }
inline System::Array<System::Delegate*>* EnginePrototype::GameObject::_sm_callbacksArray(System::Array<System::Delegate*>* _$value)  { return (System::Array<System::Delegate*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callbacksArray,_$value); }
inline System::Array<System::Delegate*>* EnginePrototype::GameObject::_sm_callbacksArray$(System::Array<System::Delegate*>* _$value) { CHCKTHIS; return _sm_callbacksArray(_$value); }


inline System::Object* EnginePrototype::GameObject::_acc_gTag(){
    return _gm_tag$();
}

inline System::Object* EnginePrototype::GameObject::_acc_gTag$() { CHCKTHIS; return _acc_gTag(); }

inline System::Object* EnginePrototype::GameObject::_acc_sTag(System::Object* value){
    System::Object* _returnValue_ = value;
    _sm_tag$(value);
    return _returnValue_;
}
inline System::Object* EnginePrototype::GameObject::_acc_sTag$(System::Object* value)		{ CHCKTHIS; return _acc_sTag(value); }
inline u32 EnginePrototype::GameObject::_acc_gTypeID(){
    return _gm_typeID$();
}

inline u32 EnginePrototype::GameObject::_acc_gTypeID$() { CHCKTHIS; return _acc_gTypeID(); }

inline u32 EnginePrototype::GameObject::_acc_gHandle(){
    return _gm_handle$();
}

inline u32 EnginePrototype::GameObject::_acc_gHandle$() { CHCKTHIS; return _acc_gHandle(); }

inline u32 EnginePrototype::GameObject::_acc_sHandle(u32 value){
    u32 _returnValue_ = value;
    _sm_handle$(value);
    return _returnValue_;
}
inline u32 EnginePrototype::GameObject::_acc_sHandle$(u32 value)		{ CHCKTHIS; return _acc_sHandle(value); }
inline s32* EnginePrototype::GameObject::_acc_gCppObject(){
    return _gm_cppObject$();
}

inline s32* EnginePrototype::GameObject::_acc_gCppObject$() { CHCKTHIS; return _acc_gCppObject(); }

inline s32* EnginePrototype::GameObject::_acc_sCppObject(s32* value){
    s32* _returnValue_ = value;
    _sm_cppObject$(value);
    return _returnValue_;
}
inline s32* EnginePrototype::GameObject::_acc_sCppObject$(s32* value)		{ CHCKTHIS; return _acc_sCppObject(value); }
/*virtual*/
bool EnginePrototype::GameObject::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(GameObject,System::Object);
}

/*virtual*/
u32 EnginePrototype::GameObject::_processGC() {
    if (m_tag) { System::Memory::pushList(m_tag,0); }
    if (m_callbacksArray) { System::Memory::pushList(m_callbacksArray,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::GameObject::_releaseGC() {
    Dispose$();
    if (m_tag && !m_tag->isFreed()) { m_tag->_removeRef((System::__GCObject**)&m_tag); }
    if (m_callbacksArray && !m_callbacksArray->isFreed()) { m_callbacksArray->_removeRef((System::__GCObject**)&m_callbacksArray); }
}
/*virtual*/
void EnginePrototype::GameObject::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_tag) {
      newPtr = (u8*)(&m_tag); oldPtr = newPtr - offset;
      m_tag->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_callbacksArray) {
      newPtr = (u8*)(&m_callbacksArray); oldPtr = newPtr - offset;
      m_callbacksArray->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'GameObjectFactory'
//=============================

void EnginePrototype::GameObjectFactory::_ctor_GameObjectFactory() {
}

EnginePrototype::GameObjectFactory::GameObjectFactory() { _ctor_GameObjectFactory(); }



/*virtual*/
bool EnginePrototype::GameObjectFactory::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(GameObjectFactory,System::Object);
}

/*virtual*/
u32 EnginePrototype::GameObjectFactory::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::GameObjectFactory::_releaseGC() {
}
/*virtual*/
void EnginePrototype::GameObjectFactory::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'NativeManagement'
//=============================

void EnginePrototype::NativeManagement::_ctor_NativeManagement() {
}

/*static*/
u32 EnginePrototype::NativeManagement::_ext_CKLBObject_getTypeID(s32* p)
{
    return CKLBObject_getTypeID(p);
}

/*static*/
u32 EnginePrototype::NativeManagement::_ext_CKLBObjectScriptable_getScriptContext(s32* p)
{
    return CKLBObjectScriptable_getScriptContext(p);
}

/*static*/
void EnginePrototype::NativeManagement::_ext_CKLBObjectScriptable_setScriptContext(s32* p,u32 handle)
{
    CKLBObjectScriptable_setScriptContext(p,handle);
}

/*static*/
s32* EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_getCallBackCount()
{
    return CKLBScriptEnv_getCallBackCount();
}

/*static*/
s32* EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_getErrorPtr()
{
    return CKLBScriptEnv_getErrorPtr();
}

/*static*/
s32* EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_getErrorString()
{
    return CKLBScriptEnv_getErrorString();
}

/*static*/
void EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_resetError()
{
    CKLBScriptEnv_resetError();
}

/*static*/
void EnginePrototype::NativeManagement::resetCppError()
{
    _ext_CKLBScriptEnv_resetError();
}

/*static*/
void EnginePrototype::NativeManagement::intercepCppError()
{
    if (_acc_gCppErrorFlag() != 0)
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr19Obj)->_appendStr(_acc_gCppErrorString())->_appendClose()));
    }
}

/*static*/
u32 EnginePrototype::NativeManagement::getContextCounter()
{
    return (u32)System::Runtime::InteropServices::Marshal::ReadInt32(ms_counter);
}

/*static*/
u32 EnginePrototype::NativeManagement::getTypeID(s32* cppObj)
{
    return _ext_CKLBObject_getTypeID(cppObj);
}

/*static*/
void EnginePrototype::NativeManagement::registerWrapper(s32* cppObj,u32 handle)
{
    System::Console::WriteLine(_$_cteStr20Obj);
    EnginePrototype::GameObject* gameObject = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (cppObj != System::IntPtr::Zero)
    {
        if (EnginePrototype::NativeManagement::getTypeID(cppObj) == gameObject->_acc_gTypeID$())
        {
            _ext_CKLBObjectScriptable_setScriptContext(cppObj,handle);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr21Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    System::Console::WriteLine(_$_cteStr22Obj);
}

/*static*/
void EnginePrototype::NativeManagement::unregisterWrapper(s32* cppObj)
{
    if (cppObj != System::IntPtr::Zero)
    {
        System::Console::WriteLine(_$_cteStr23Obj);
        _ext_CKLBObjectScriptable_setScriptContext(cppObj,EnginePrototype::GameObject::NULLHANDLER);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

/*static*/
void EnginePrototype::NativeManagement::destroyFromNative(u32 handle)
{
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (obj != NULL)
    {
        EnginePrototype::WrapperReg::getInstance()->unregisterGameObject$(obj);
        obj->_acc_sCppObject$(System::IntPtr::Zero);
        obj->Dispose$();
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackV(u32 cbInfos)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerV_inner0* cb = (EnginePrototype::_Delegate_Base_FunctionPointerV_inner0*)obj->getCallBack$(callbackIndex);
        cb->call$();
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackII(u32 cbInfos,s32 int_1,s32 int_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerII_inner1* cb = (EnginePrototype::_Delegate_Base_FunctionPointerII_inner1*)obj->getCallBack$(callbackIndex);
        cb->call$(int_1,int_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackIII(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerIII_inner2* cb = (EnginePrototype::_Delegate_Base_FunctionPointerIII_inner2*)obj->getCallBack$(callbackIndex);
        cb->call$(int_1,int_2,int_3);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackIIII(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3,s32 int_4)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerIIII_inner3* cb = (EnginePrototype::_Delegate_Base_FunctionPointerIIII_inner3*)obj->getCallBack$(callbackIndex);
        cb->call$(int_1,int_2,int_3,int_4);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackS(u32 cbInfos,s32* intptr_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerS_inner4* cb = (EnginePrototype::_Delegate_Base_FunctionPointerS_inner4*)obj->getCallBack$(callbackIndex);
        cb->call$(intptr_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackSII(u32 cbInfos,s32* intptr_1,s32 int_1,s32 int_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerSII_inner5* cb = (EnginePrototype::_Delegate_Base_FunctionPointerSII_inner5*)obj->getCallBack$(callbackIndex);
        cb->call$(intptr_1,int_1,int_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackSU(u32 cbInfos,s32* intptr_1,u32 uint_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerSU_inner6* cb = (EnginePrototype::_Delegate_Base_FunctionPointerSU_inner6*)obj->getCallBack$(callbackIndex);
        cb->call$(intptr_1,uint_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackSS(u32 cbInfos,s32* intptr_1,s32* intptr_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerSS_inner7* cb = (EnginePrototype::_Delegate_Base_FunctionPointerSS_inner7*)obj->getCallBack$(callbackIndex);
        cb->call$(intptr_1,intptr_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUS(u32 cbInfos,u32 uint_1,s32* intptr_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUS_inner8* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUS_inner8*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,intptr_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUSS(u32 cbInfos,u32 uint_1,s32* intptr_1,s32* intptr_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUSS_inner9* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUSS_inner9*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,intptr_1,intptr_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackU(u32 cbInfos,u32 uint_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerU_inner10* cb = (EnginePrototype::_Delegate_Base_FunctionPointerU_inner10*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUU(u32 cbInfos,u32 uint_1,u32 uint_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUU_inner11* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUU_inner11*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,uint_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUFF(u32 cbInfos,u32 uint_1,float float_1,float float_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUFF_inner12* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUFF_inner12*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,float_1,float_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUI(u32 cbInfos,u32 uint_1,s32 int_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUI_inner13* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUI_inner13*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,int_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUII(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUII_inner14* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUII_inner14*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,int_1,int_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUIIII(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUIIII_inner15* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUIIII_inner15*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,int_1,int_2,int_3,int_4);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUIIUU(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUIIUU_inner16* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUIIUU_inner16*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,int_1,int_2,uint_2,uint_3);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUUII(u32 cbInfos,u32 uint_1,u32 uint_2,s32 int_1,s32 int_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUUII_inner17* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUUII_inner17*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,uint_2,int_1,int_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackUUUII(u32 cbInfos,u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerUUUII_inner18* cb = (EnginePrototype::_Delegate_Base_FunctionPointerUUUII_inner18*)obj->getCallBack$(callbackIndex);
        cb->call$(uint_1,uint_2,uint_3,int_1,int_2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
bool EnginePrototype::NativeManagement::doCallBackIIIP_retB(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3,s32* obj_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerIIIP_retB_inner19* cb = (EnginePrototype::_Delegate_Base_FunctionPointerIIIP_retB_inner19*)obj->getCallBack$(callbackIndex);
        return cb->call$(int_1,int_2,int_3,obj_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

/*static*/
void EnginePrototype::NativeManagement::doCallBackFS(u32 cbInfos,float float_1,s32* intptr_1)
{
    u32 callbackIndex = (cbInfos & -536870912) >> 29;
    u32 handle = cbInfos & 536870911;
    EnginePrototype::GameObject* obj = EnginePrototype::WrapperReg::getInstance()->getObjectFromHandle$(handle);
    if (0 <= callbackIndex && callbackIndex < EnginePrototype::GameObject::NBCALLBACKS)
    {
        EnginePrototype::_Delegate_Base_FunctionPointerFS_inner20* cb = (EnginePrototype::_Delegate_Base_FunctionPointerFS_inner20*)obj->getCallBack$(callbackIndex);
        cb->call$(float_1,intptr_1);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException((CS_NEW System::String())->_appendStr(_$_cteStr17Obj)->_appendI((EnginePrototype::GameObject::NBCALLBACKS - 1))->_appendStr(_$_cteStr18Obj)->_appendClose()));
    }
}

EnginePrototype::NativeManagement::NativeManagement() { _ctor_NativeManagement(); }



inline u32 EnginePrototype::NativeManagement::_acc_gCppErrorFlag(){
    return (u32)System::Runtime::InteropServices::Marshal::ReadInt32(ms_cppErrorFlag);
}

inline System::String* EnginePrototype::NativeManagement::_acc_gCppErrorString(){
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBScriptEnv_getErrorString());
}

/*virtual*/
bool EnginePrototype::NativeManagement::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(NativeManagement,System::Object);
}

/*virtual*/
u32 EnginePrototype::NativeManagement::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::NativeManagement::_releaseGC() {
}
/*virtual*/
void EnginePrototype::NativeManagement::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'NodeIterator'
//=============================

void EnginePrototype::NodeIterator::_ctor_NodeIterator() {
    _sm_navigation(CS_NEW System::Collections::Generic::List<s32*>());
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getRoot()
{
    return node_getRoot();
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getChild(s32* pNode)
{
    return node_getChild(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getParent(s32* pNode)
{
    return node_getParent(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getBrother(s32* pNode)
{
    return node_getBrother(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getNodeFromTask(s32* pTask)
{
    return node_getNodeFromTask(pTask);
}

/*static*/
float EnginePrototype::NodeIterator::_ext_node_getNodeScaleX(s32* pNode)
{
    return node_getNodeScaleX(pNode);
}

/*static*/
float EnginePrototype::NodeIterator::_ext_node_getNodeScaleY(s32* pNode)
{
    return node_getNodeScaleY(pNode);
}

/*static*/
float EnginePrototype::NodeIterator::_ext_node_getRotation(s32* pNode)
{
    return node_getRotation(pNode);
}

/*static*/
float EnginePrototype::NodeIterator::_ext_node_getNodeTranslateX(s32* pNode)
{
    return node_getNodeTranslateX(pNode);
}

/*static*/
float EnginePrototype::NodeIterator::_ext_node_getNodeTranslateY(s32* pNode)
{
    return node_getNodeTranslateY(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getName(s32* pNode)
{
    return node_getName(pNode);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setName(s32* pNode,s32* name)
{
    node_setName(pNode,name);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setTranslate(s32* pNode,float x,float y)
{
    node_setTranslate(pNode,x,y);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setRotation(s32* pNode,float deg)
{
    node_setRotation(pNode,deg);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setScale(s32* pNode,float scaleX,float scaleY)
{
    node_setScale(pNode,scaleX,scaleY);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_getColorMatrixVec(s32* pNode,System::Array<float>* dst)
{
    node_getColorMatrixVec(pNode,dst ? (float*)dst->_getPArray() : NULL);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setColorMatrixVec(s32* pNode,System::Array<float>* src)
{
    node_setColorMatrixVec(pNode,src ? (float*)src->_getPArray() : NULL);
}

/*static*/
u32 EnginePrototype::NodeIterator::_ext_node_getColorMatrixUInt(s32* pNode)
{
    return node_getColorMatrixUInt(pNode);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setColorMatrixUInt(s32* pNode,u32 val)
{
    node_setColorMatrixUInt(pNode,val);
}

/*static*/
void EnginePrototype::NodeIterator::_ext_node_setVisible(s32* pNode,bool visible)
{
    node_setVisible(pNode,visible);
}

/*static*/
bool EnginePrototype::NodeIterator::_ext_node_getVisible(s32* pNode)
{
    return node_getVisible(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_asElement(s32* pNode)
{
    return node_asElement(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_asContainer(s32* pNode)
{
    return node_asContainer(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_asSelectable(s32* pNode)
{
    return node_asSelectable(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_asAnimationNode(s32* pNode)
{
    return node_asAnimationNode(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_getUITask(s32* pNode)
{
    return node_getUITask(pNode);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_search(s32* pNode,s32* name)
{
    return node_search(pNode,name);
}

/*static*/
s32* EnginePrototype::NodeIterator::_ext_node_searchFirstByTypeID(s32* pNode,u32 typeID)
{
    return node_searchFirstByTypeID(pNode,typeID);
}

EnginePrototype::NodeIterator::NodeIterator()
{
    _ctor_NodeIterator();
}

EnginePrototype::NodeIterator::NodeIterator(u32 counter,s32* node)
{
    _ctor_NodeIterator();
    this->_sm_counter$(counter);
    this->_sm_nodeCpp$(node);
}

/*static*/
s32* EnginePrototype::NodeIterator::getRoot()
{
    return _ext_node_getRoot();
}

/*static*/
s32* EnginePrototype::NodeIterator::getNodeFromTask(EnginePrototype::CKLBUITask* task)
{
    return _ext_node_getNodeFromTask(task->_acc_gCppObject$());
}

EnginePrototype::Element* EnginePrototype::NodeIterator::getAsElement()
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_ext_node_asElement(_gm_nodeCpp$()) != System::IntPtr::Zero)
        {
            return CS_NEW EnginePrototype::Element(_gm_counter$(),_ext_node_asElement(_gm_nodeCpp$()));
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline EnginePrototype::Element* EnginePrototype::NodeIterator::getAsElement$() { CHCKTHIS; return getAsElement(); }

EnginePrototype::Container* EnginePrototype::NodeIterator::getAsContainer()
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_ext_node_asContainer(_gm_nodeCpp$()) != System::IntPtr::Zero)
        {
            return CS_NEW EnginePrototype::Container(_gm_counter$(),_ext_node_asElement(_gm_nodeCpp$()));
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline EnginePrototype::Container* EnginePrototype::NodeIterator::getAsContainer$() { CHCKTHIS; return getAsContainer(); }

EnginePrototype::Selectable* EnginePrototype::NodeIterator::getAsSelectable()
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_ext_node_asSelectable(_gm_nodeCpp$()) != System::IntPtr::Zero)
        {
            return CS_NEW EnginePrototype::Selectable(_gm_counter$(),_ext_node_asElement(_gm_nodeCpp$()));
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline EnginePrototype::Selectable* EnginePrototype::NodeIterator::getAsSelectable$() { CHCKTHIS; return getAsSelectable(); }

EnginePrototype::AnimationNode* EnginePrototype::NodeIterator::getAsAnimationNode()
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_ext_node_asAnimationNode(_gm_nodeCpp$()) != System::IntPtr::Zero)
        {
            return CS_NEW EnginePrototype::AnimationNode(_gm_counter$(),_ext_node_asElement(_gm_nodeCpp$()));
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline EnginePrototype::AnimationNode* EnginePrototype::NodeIterator::getAsAnimationNode$() { CHCKTHIS; return getAsAnimationNode(); }

bool EnginePrototype::NodeIterator::gotoChild(bool registerStack)
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        s32* nNode = _ext_node_getChild(_gm_nodeCpp$());
        if (nNode != System::IntPtr::Zero)
        {
            if (registerStack)
            {
                _gm_navigation$()->Add$(_gm_nodeCpp$());
            }
            _sm_nodeCpp$(nNode);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::gotoChild$(bool registerStack) { CHCKTHIS; return gotoChild(registerStack); }

bool EnginePrototype::NodeIterator::gotoBrother(bool registerStack)
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        s32* nNode = _ext_node_getBrother(_gm_nodeCpp$());
        if (nNode != System::IntPtr::Zero)
        {
            if (registerStack)
            {
                _gm_navigation$()->Add$(_gm_nodeCpp$());
            }
            _sm_nodeCpp$(nNode);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::gotoBrother$(bool registerStack) { CHCKTHIS; return gotoBrother(registerStack); }

bool EnginePrototype::NodeIterator::gotoParent(bool registerStack)
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        s32* nNode = _ext_node_getParent(_gm_nodeCpp$());
        if (nNode != System::IntPtr::Zero)
        {
            if (registerStack)
            {
                _gm_navigation$()->Add$(_gm_nodeCpp$());
            }
            _sm_nodeCpp$(nNode);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::gotoParent$(bool registerStack) { CHCKTHIS; return gotoParent(registerStack); }

bool EnginePrototype::NodeIterator::rollback()
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_navigation$()->_acc_gCount$() != 0)
        {
            _sm_nodeCpp$(_gm_navigation$()->_idx_g$(_gm_navigation$()->_acc_gCount$() - 1));
            _gm_navigation$()->RemoveAt$(_gm_navigation$()->_acc_gCount$() - 1);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::rollback$() { CHCKTHIS; return rollback(); }

bool EnginePrototype::NodeIterator::find(System::String* name,bool registerStack)
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            s32* ptr = _ext_node_search(_gm_nodeCpp$(),System::__MarshallingUtils::NativeUtf8FromString(name));
            if (ptr != System::IntPtr::Zero)
            {
                if (registerStack)
                {
                    _gm_navigation$()->Add$(_gm_nodeCpp$());
                }
                _sm_nodeCpp$(ptr);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::find$(System::String* name,bool registerStack) { CHCKTHIS; return find(name,registerStack); }

EnginePrototype::CKLBUITask* EnginePrototype::NodeIterator::getAsUITask()
{
    s32* ptr = _ext_node_getUITask(_gm_nodeCpp$());
    if (ptr != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        EnginePrototype::CKLBUITask* task = CS_NEW EnginePrototype::CKLBUITask(EnginePrototype::NativeManagement::getTypeID(ptr));
        EnginePrototype::NativeManagement::intercepCppError();
        task->bind$(ptr);
        return task;
    }
    else
    {
        return NULL;
    }
}

inline EnginePrototype::CKLBUITask* EnginePrototype::NodeIterator::getAsUITask$() { CHCKTHIS; return getAsUITask(); }

EnginePrototype::CKLBUITask* EnginePrototype::NodeIterator::bindTask(EnginePrototype::CKLBUITask* task,System::String* name)
{
    if (name != NULL)
    {
        if (find$(name,true))
        {
            task->bind$(_ext_node_getUITask(_gm_nodeCpp$()));
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr10Obj));
        }
    }
    else
    {
        s32* ptr = _ext_node_searchFirstByTypeID(_gm_nodeCpp$(),task->_acc_gTypeID$());
        if (ptr != System::IntPtr::Zero)
        {
            task->bind$(ptr);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr24Obj));
        }
    }
    return task;
}

inline EnginePrototype::CKLBUITask* EnginePrototype::NodeIterator::bindTask$(EnginePrototype::CKLBUITask* task,System::String* name) { CHCKTHIS; return bindTask(task,name); }

void EnginePrototype::NodeIterator::setXY(float x,float y)
{
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setTranslate(_gm_nodeCpp$(),x,y);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline void EnginePrototype::NodeIterator::setXY$(float x,float y) { CHCKTHIS; return setXY(x,y); }

inline System::Collections::Generic::List<s32*>* EnginePrototype::NodeIterator::_sm_navigation(System::Collections::Generic::List<s32*>* _$value)  { return (System::Collections::Generic::List<s32*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_navigation,_$value); }
inline System::Collections::Generic::List<s32*>* EnginePrototype::NodeIterator::_sm_navigation$(System::Collections::Generic::List<s32*>* _$value) { CHCKTHIS; return _sm_navigation(_$value); }


inline u32 EnginePrototype::NodeIterator::_acc_gRgba(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getColorMatrixUInt(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline u32 EnginePrototype::NodeIterator::_acc_gRgba$() { CHCKTHIS; return _acc_gRgba(); }

inline u32 EnginePrototype::NodeIterator::_acc_sRgba(u32 value){
    u32 _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setColorMatrixUInt(_gm_nodeCpp$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::NodeIterator::_acc_sRgba$(u32 value)		{ CHCKTHIS; return _acc_sRgba(value); }
inline float EnginePrototype::NodeIterator::_acc_gScaleX(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getNodeScaleX(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline float EnginePrototype::NodeIterator::_acc_gScaleX$() { CHCKTHIS; return _acc_gScaleX(); }

inline float EnginePrototype::NodeIterator::_acc_sScaleX(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setScale(_gm_nodeCpp$(),value,_ext_node_getNodeScaleY(_gm_nodeCpp$()));
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sScaleX$(float value)		{ CHCKTHIS; return _acc_sScaleX(value); }
inline float EnginePrototype::NodeIterator::_acc_gScaleY(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getNodeScaleY(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline float EnginePrototype::NodeIterator::_acc_gScaleY$() { CHCKTHIS; return _acc_gScaleY(); }

inline float EnginePrototype::NodeIterator::_acc_sScaleY(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setScale(_gm_nodeCpp$(),_ext_node_getNodeScaleX(_gm_nodeCpp$()),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sScaleY$(float value)		{ CHCKTHIS; return _acc_sScaleY(value); }
inline float EnginePrototype::NodeIterator::_acc_sScale(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setScale(_gm_nodeCpp$(),value,value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sScale$(float value)		{ CHCKTHIS; return _acc_sScale(value); }
inline float EnginePrototype::NodeIterator::_acc_gRotation(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getRotation(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline float EnginePrototype::NodeIterator::_acc_gRotation$() { CHCKTHIS; return _acc_gRotation(); }

inline float EnginePrototype::NodeIterator::_acc_sRotation(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setRotation(_gm_nodeCpp$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sRotation$(float value)		{ CHCKTHIS; return _acc_sRotation(value); }
inline float EnginePrototype::NodeIterator::_acc_gX(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getNodeTranslateX(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline float EnginePrototype::NodeIterator::_acc_gX$() { CHCKTHIS; return _acc_gX(); }

inline float EnginePrototype::NodeIterator::_acc_sX(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setTranslate(_gm_nodeCpp$(),value,_ext_node_getNodeTranslateY(_gm_nodeCpp$()));
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sX$(float value)		{ CHCKTHIS; return _acc_sX(value); }
inline float EnginePrototype::NodeIterator::_acc_gY(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getNodeTranslateY(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline float EnginePrototype::NodeIterator::_acc_gY$() { CHCKTHIS; return _acc_gY(); }

inline float EnginePrototype::NodeIterator::_acc_sY(float value){
    float _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setTranslate(_gm_nodeCpp$(),_ext_node_getNodeTranslateX(_gm_nodeCpp$()),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::NodeIterator::_acc_sY$(float value)		{ CHCKTHIS; return _acc_sY(value); }
inline bool EnginePrototype::NodeIterator::_acc_gVisible(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return _ext_node_getVisible(_gm_nodeCpp$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::NodeIterator::_acc_gVisible$() { CHCKTHIS; return _acc_gVisible(); }

inline bool EnginePrototype::NodeIterator::_acc_sVisible(bool value){
    bool _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setVisible(_gm_nodeCpp$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::NodeIterator::_acc_sVisible$(bool value)		{ CHCKTHIS; return _acc_sVisible(value); }
inline System::String* EnginePrototype::NodeIterator::_acc_gName(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            return System::__MarshallingUtils::StringFromNativeUtf8(_ext_node_getName(_gm_nodeCpp$()));
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline System::String* EnginePrototype::NodeIterator::_acc_gName$() { CHCKTHIS; return _acc_gName(); }

inline System::String* EnginePrototype::NodeIterator::_acc_sName(System::String* value){
    System::String* _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodeCpp$() != System::IntPtr::Zero)
        {
            _ext_node_setName(_gm_nodeCpp$(),System::__MarshallingUtils::NativeUtf8FromString(value));
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::NodeIterator::_acc_sName$(System::String* value)		{ CHCKTHIS; return _acc_sName(value); }
/*virtual*/
bool EnginePrototype::NodeIterator::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(NodeIterator,System::Object);
}

/*virtual*/
u32 EnginePrototype::NodeIterator::_processGC() {
    if (m_navigation) { System::Memory::pushList(m_navigation,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::NodeIterator::_releaseGC() {
    if (m_navigation && !m_navigation->isFreed()) { m_navigation->_removeRef((System::__GCObject**)&m_navigation); }
}
/*virtual*/
void EnginePrototype::NodeIterator::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_navigation) {
      newPtr = (u8*)(&m_navigation); oldPtr = newPtr - offset;
      m_navigation->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'Element'
//=============================

void EnginePrototype::Element::_ctor_Element() {
}

/*static*/
void EnginePrototype::Element::_ext_element_setEnabled(s32* pElem,bool isEnabled)
{
    element_setEnabled(pElem,isEnabled);
}

/*static*/
bool EnginePrototype::Element::_ext_element_isEnabled(s32* pElem)
{
    return element_isEnabled(pElem);
}

/*static*/
bool EnginePrototype::Element::_ext_element_setAsset(s32* pElem,u32 dest,s32* assetName)
{
    return element_setAsset(pElem,dest,assetName);
}

/*static*/
void EnginePrototype::Element::_ext_element_setPriority(s32* pElem,u32 renderPriority)
{
    element_setPriority(pElem,renderPriority);
}

/*static*/
u32 EnginePrototype::Element::_ext_element_getPriority(s32* pElem)
{
    return element_getPriority(pElem);
}

EnginePrototype::Element::Element(u32 m_counter,s32* nodePtr)
{
    _ctor_Element();
    this->_sm_counter$(m_counter);
    this->_sm_nodePtr$(nodePtr);
}

EnginePrototype::Element::Element() { _ctor_Element(); }



inline bool EnginePrototype::Element::_acc_gEnabled(){
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_element_isEnabled(_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::Element::_acc_gEnabled$() { CHCKTHIS; return _acc_gEnabled(); }

inline bool EnginePrototype::Element::_acc_sEnabled(bool value){
    bool _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_element_setEnabled(_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::Element::_acc_sEnabled$(bool value)		{ CHCKTHIS; return _acc_sEnabled(value); }
inline System::String* EnginePrototype::Element::_acc_snormalAsset(System::String* value){
    System::String* _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodePtr$() != System::IntPtr::Zero)
        {
            EnginePrototype::NativeManagement::resetCppError();
            if (!_ext_element_setAsset(_gm_nodePtr$(),(u32)ASSET_TYPE::NORMAL_ASSET,System::__MarshallingUtils::NativeUtf8FromString(value)))
            {
                EnginePrototype::NativeManagement::intercepCppError();
            }
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::Element::_acc_snormalAsset$(System::String* value)		{ CHCKTHIS; return _acc_snormalAsset(value); }
inline System::String* EnginePrototype::Element::_acc_sdisableAsset(System::String* value){
    System::String* _returnValue_ = value;
    if (_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (_gm_nodePtr$() != System::IntPtr::Zero)
        {
            EnginePrototype::NativeManagement::resetCppError();
            if (!_ext_element_setAsset(_gm_nodePtr$(),(u32)ASSET_TYPE::DISABLED_ASSET,System::__MarshallingUtils::NativeUtf8FromString(value)))
            {
                EnginePrototype::NativeManagement::intercepCppError();
            }
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::Element::_acc_sdisableAsset$(System::String* value)		{ CHCKTHIS; return _acc_sdisableAsset(value); }
/*virtual*/
bool EnginePrototype::Element::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Element,System::Object);
}

/*virtual*/
u32 EnginePrototype::Element::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::Element::_releaseGC() {
}
/*virtual*/
void EnginePrototype::Element::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'Container'
//=============================

void EnginePrototype::Container::_ctor_Container() {
}

/*static*/
s32 EnginePrototype::Container::_ext_container_getViewOffsetX(s32* pCont)
{
    return container_getViewOffsetX(pCont);
}

/*static*/
void EnginePrototype::Container::_ext_container_setViewOffsetX(s32* pCont,s32 scrollX)
{
    container_setViewOffsetX(pCont,scrollX);
}

/*static*/
s32 EnginePrototype::Container::_ext_container_getViewOffsetY(s32* pCont)
{
    return container_getViewOffsetY(pCont);
}

/*static*/
void EnginePrototype::Container::_ext_container_setViewOffsetY(s32* pCont,s32 scrollY)
{
    container_setViewOffsetY(pCont,scrollY);
}

/*static*/
u32 EnginePrototype::Container::_ext_container_getRadioValue(s32* pCont)
{
    return container_getRadioValue(pCont);
}

EnginePrototype::Container::Container(u32 m_counter,s32* nodePtr) : EnginePrototype::Element(m_counter,nodePtr)
{
    _ctor_Container();
}

EnginePrototype::Container::Container() { _ctor_Container(); }



inline s32 EnginePrototype::Container::_acc_gViewOffsetX(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_container_getViewOffsetX(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline s32 EnginePrototype::Container::_acc_gViewOffsetX$() { CHCKTHIS; return _acc_gViewOffsetX(); }

inline s32 EnginePrototype::Container::_acc_sViewOffsetX(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_container_setViewOffsetX(EnginePrototype::Element::_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::Container::_acc_sViewOffsetX$(s32 value)		{ CHCKTHIS; return _acc_sViewOffsetX(value); }
inline s32 EnginePrototype::Container::_acc_gViewOffsetY(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_container_getViewOffsetY(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline s32 EnginePrototype::Container::_acc_gViewOffsetY$() { CHCKTHIS; return _acc_gViewOffsetY(); }

inline s32 EnginePrototype::Container::_acc_sViewOffsetY(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_container_setViewOffsetY(EnginePrototype::Element::_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::Container::_acc_sViewOffsetY$(s32 value)		{ CHCKTHIS; return _acc_sViewOffsetY(value); }
inline u32 EnginePrototype::Container::_acc_gRadioValue(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_container_getRadioValue(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline u32 EnginePrototype::Container::_acc_gRadioValue$() { CHCKTHIS; return _acc_gRadioValue(); }

/*virtual*/
bool EnginePrototype::Container::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Container,EnginePrototype::Element);
}

/*virtual*/
u32 EnginePrototype::Container::_processGC() {
    EnginePrototype::Element::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::Container::_releaseGC() {
    EnginePrototype::Element::_releaseGC();

}
/*virtual*/
void EnginePrototype::Container::_moveAlert(u32 offset) {
    EnginePrototype::Element::_moveAlert(offset);

}

//=============================
// Implementation of 'Selectable'
//=============================

void EnginePrototype::Selectable::_ctor_Selectable() {
}

/*static*/
void EnginePrototype::Selectable::_ext_selectable_setClick(s32* pSelect,s32 coordinateX,s32 coordinateY,s32 width,s32 height)
{
    selectable_setClick(pSelect,coordinateX,coordinateY,width,height);
}

/*static*/
bool EnginePrototype::Selectable::_ext_selectable_setAudio(s32* pSelect,s32* assetAudio,u32 mode,float volume)
{
    return selectable_setAudio(pSelect,assetAudio,mode,volume);
}

/*static*/
void EnginePrototype::Selectable::_ext_selectable_setStick(s32* pSelect,bool isStickable)
{
    selectable_setStick(pSelect,isStickable);
}

/*static*/
bool EnginePrototype::Selectable::_ext_selectable_isStickable(s32* pSelect)
{
    return selectable_isStickable(pSelect);
}

/*static*/
void EnginePrototype::Selectable::_ext_selectable_setSticked(s32* pSelect,bool isSticked)
{
    selectable_setSticked(pSelect,isSticked);
}

/*static*/
bool EnginePrototype::Selectable::_ext_selectable_isSticked(s32* pSelect)
{
    return selectable_isSticked(pSelect);
}

/*static*/
void EnginePrototype::Selectable::_ext_selectable_setRadio(s32* pSelect,u32 radioID)
{
    selectable_setRadio(pSelect,radioID);
}

/*static*/
u32 EnginePrototype::Selectable::_ext_selectable_getRadioID(s32* pSelect)
{
    return selectable_getRadioID(pSelect);
}

EnginePrototype::Selectable::Selectable(u32 m_counter,s32* nodePtr) : EnginePrototype::Element(m_counter,nodePtr)
{
    _ctor_Selectable();
}

bool EnginePrototype::Selectable::setAudio(System::String* assetName,u32 mode,float volume)
{
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_selectable_setAudio(EnginePrototype::Element::_gm_nodePtr$(),System::__MarshallingUtils::NativeUtf8FromString(assetName),mode,volume);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::Selectable::setAudio$(System::String* assetName,u32 mode,float volume) { CHCKTHIS; return setAudio(assetName,mode,volume); }

void EnginePrototype::Selectable::setClickArea(s32 x,s32 y,s32 width,s32 height)
{
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_selectable_setClick(EnginePrototype::Element::_gm_nodePtr$(),x,y,width,height);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline void EnginePrototype::Selectable::setClickArea$(s32 x,s32 y,s32 width,s32 height) { CHCKTHIS; return setClickArea(x,y,width,height); }

EnginePrototype::Selectable::Selectable() { _ctor_Selectable(); }



inline System::String* EnginePrototype::Selectable::_acc_spushedAsset(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            EnginePrototype::NativeManagement::resetCppError();
            if (!EnginePrototype::Element::_ext_element_setAsset(EnginePrototype::Element::_gm_nodePtr$(),(u32)EnginePrototype::Element::ASSET_TYPE::PUSHED_ASSET,System::__MarshallingUtils::NativeUtf8FromString(value)))
            {
                EnginePrototype::NativeManagement::intercepCppError();
            }
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::Selectable::_acc_spushedAsset$(System::String* value)		{ CHCKTHIS; return _acc_spushedAsset(value); }
inline bool EnginePrototype::Selectable::_acc_gisDown(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_selectable_isSticked(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::Selectable::_acc_gisDown$() { CHCKTHIS; return _acc_gisDown(); }

inline bool EnginePrototype::Selectable::_acc_sisDown(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_selectable_setStick(EnginePrototype::Element::_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::Selectable::_acc_sisDown$(bool value)		{ CHCKTHIS; return _acc_sisDown(value); }
inline bool EnginePrototype::Selectable::_acc_gcheckBoxMode(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_selectable_isStickable(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline bool EnginePrototype::Selectable::_acc_gcheckBoxMode$() { CHCKTHIS; return _acc_gcheckBoxMode(); }

inline bool EnginePrototype::Selectable::_acc_scheckBoxMode(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_selectable_setSticked(EnginePrototype::Element::_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::Selectable::_acc_scheckBoxMode$(bool value)		{ CHCKTHIS; return _acc_scheckBoxMode(value); }
inline u32 EnginePrototype::Selectable::_acc_gRadioID(){
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            return _ext_selectable_getRadioID(EnginePrototype::Element::_gm_nodePtr$());
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
}

inline u32 EnginePrototype::Selectable::_acc_gRadioID$() { CHCKTHIS; return _acc_gRadioID(); }

inline u32 EnginePrototype::Selectable::_acc_sRadioID(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::Element::_gm_counter$() == EnginePrototype::NativeManagement::getContextCounter())
    {
        if (EnginePrototype::Element::_gm_nodePtr$() != System::IntPtr::Zero)
        {
            _ext_selectable_setRadio(EnginePrototype::Element::_gm_nodePtr$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionTooOld(_$_cteStr4Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::Selectable::_acc_sRadioID$(u32 value)		{ CHCKTHIS; return _acc_sRadioID(value); }
/*virtual*/
bool EnginePrototype::Selectable::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Selectable,EnginePrototype::Element);
}

/*virtual*/
u32 EnginePrototype::Selectable::_processGC() {
    EnginePrototype::Element::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::Selectable::_releaseGC() {
    EnginePrototype::Element::_releaseGC();

}
/*virtual*/
void EnginePrototype::Selectable::_moveAlert(u32 offset) {
    EnginePrototype::Element::_moveAlert(offset);

}

//=============================
// Implementation of 'AnimationNode'
//=============================

void EnginePrototype::AnimationNode::_ctor_AnimationNode() {
}

EnginePrototype::AnimationNode::AnimationNode(u32 m_counter,s32* nodePtr)
{
    _ctor_AnimationNode();
    this->_sm_counter$(m_counter);
    this->_snodePtr$(nodePtr);
}

void EnginePrototype::AnimationNode::setAnimation(EnginePrototype::AnimationInfo* animationInfo)
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionNotImplemented(_$_cteStr1Obj));
}

inline void EnginePrototype::AnimationNode::setAnimation$(EnginePrototype::AnimationInfo* animationInfo) { CHCKTHIS; return setAnimation(animationInfo); }

EnginePrototype::AnimationNode::AnimationNode() { _ctor_AnimationNode(); }



/*virtual*/
bool EnginePrototype::AnimationNode::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(AnimationNode,System::Object);
}

/*virtual*/
u32 EnginePrototype::AnimationNode::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::AnimationNode::_releaseGC() {
}
/*virtual*/
void EnginePrototype::AnimationNode::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'Size'
//=============================

void EnginePrototype::Size::_ctor_Size() {
}

EnginePrototype::Size::Size() { _ctor_Size(); }


inline u32 EnginePrototype::Size::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::Size::_releaseGC() {
}
inline void* EnginePrototype::Size::_RefSetValue(void* newStruct) {
    Size* pStruct = (Size*)newStruct;
    this->width = pStruct->width;
    this->height = pStruct->height;
    return newStruct;
}
inline void EnginePrototype::Size::_moveAlert(u32 offset) {
}
inline EnginePrototype::Size& EnginePrototype::Size::__registerByRef(EnginePrototype::Size& m) {
    return m;
}


//=============================
// Implementation of 'USize'
//=============================

void EnginePrototype::USize::_ctor_USize() {
}

EnginePrototype::USize::USize() { _ctor_USize(); }


inline u32 EnginePrototype::USize::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::USize::_releaseGC() {
}
inline void* EnginePrototype::USize::_RefSetValue(void* newStruct) {
    USize* pStruct = (USize*)newStruct;
    this->width = pStruct->width;
    this->height = pStruct->height;
    return newStruct;
}
inline void EnginePrototype::USize::_moveAlert(u32 offset) {
}
inline EnginePrototype::USize& EnginePrototype::USize::__registerByRef(EnginePrototype::USize& m) {
    return m;
}


//=============================
// Implementation of 'FSize'
//=============================

void EnginePrototype::FSize::_ctor_FSize() {
}

EnginePrototype::FSize::FSize() { _ctor_FSize(); }


inline u32 EnginePrototype::FSize::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::FSize::_releaseGC() {
}
inline void* EnginePrototype::FSize::_RefSetValue(void* newStruct) {
    FSize* pStruct = (FSize*)newStruct;
    this->width = pStruct->width;
    this->height = pStruct->height;
    return newStruct;
}
inline void EnginePrototype::FSize::_moveAlert(u32 offset) {
}
inline EnginePrototype::FSize& EnginePrototype::FSize::__registerByRef(EnginePrototype::FSize& m) {
    return m;
}


//=============================
// Implementation of 'IClientRequest'
//=============================

void EnginePrototype::IClientRequest::_ctor_IClientRequest() {
}

EnginePrototype::IClientRequest::IClientRequest() { _ctor_IClientRequest(); }



/*virtual*/
bool EnginePrototype::IClientRequest::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(IClientRequest,System::Object);
}

/*virtual*/
u32 EnginePrototype::IClientRequest::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::IClientRequest::_releaseGC() {
}
/*virtual*/
void EnginePrototype::IClientRequest::_moveAlert(u32 offset) {
}

//=============================
// Implementation of '__FrameworkUtils'
//=============================

void EnginePrototype::__FrameworkUtils::_ctor___FrameworkUtils() {
}

/*static*/
u32 EnginePrototype::__FrameworkUtils::_ext_Cpp_getClassIDByName(s32* name)
{
    return Cpp_getClassIDByName(name);
}

/*static*/
u32 EnginePrototype::__FrameworkUtils::GetClassIDByName(System::String* className)
{
    System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr25Obj)->_appendStr(className)->_appendStr(_$_cteStr26Obj)->_appendU(_ext_Cpp_getClassIDByName(System::__MarshallingUtils::NativeUtf8FromString(className)))->_appendClose());
    return _ext_Cpp_getClassIDByName(System::__MarshallingUtils::NativeUtf8FromString(className));
}

/*static*/
u32 EnginePrototype::__FrameworkUtils::RegisterClass(System::String* className)
{
    return GetClassIDByName(className);
}

EnginePrototype::__FrameworkUtils::__FrameworkUtils() { _ctor___FrameworkUtils(); }



/*virtual*/
bool EnginePrototype::__FrameworkUtils::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(__FrameworkUtils,System::Object);
}

/*virtual*/
u32 EnginePrototype::__FrameworkUtils::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::__FrameworkUtils::_releaseGC() {
}
/*virtual*/
void EnginePrototype::__FrameworkUtils::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'WrapperReg'
//=============================

void EnginePrototype::WrapperReg::_ctor_WrapperReg() {
}

EnginePrototype::WrapperReg::WrapperReg()
{
    _ctor_WrapperReg();
    System::Console::WriteLine(_$_cteStr27Obj);
    _sm_listSize$(10);
    _sm_list$(CS_NEW System::Array< EnginePrototype::GameObject* >(_gm_listSize$()));
    _sm_freeHandlesList$(CS_NEW System::Collections::Generic::List<u32>());
    _sm_objectCounter$(0);
    System::Console::WriteLine(_$_cteStr28Obj);
}

/*static*/
EnginePrototype::WrapperReg* EnginePrototype::WrapperReg::getInstance()
{
    return reg;
}

u32 EnginePrototype::WrapperReg::registerGameObject(EnginePrototype::GameObject* pObj)
{
    System::Console::WriteLine(_$_cteStr29Obj);
    if (pObj->_acc_gHandle$() == EnginePrototype::GameObject::NULLHANDLER)
    {
        System::Console::WriteLine(_$_cteStr30Obj);
        if (_gm_freeHandlesList$()->_acc_gCount$() == 0)
        {
            _gm_list$()->_idx_s$(_gm_objectCounter$(),pObj);
            pObj->_acc_sHandle$(_gm_objectCounter$());
            if (++m_objectCounter == _gm_listSize$())
            {
                System::Console::WriteLine(_$_cteStr31Obj);
                System::AbstractArray::Resize((System::Array<EnginePrototype::GameObject*>*&)System::__GCObject::__registerByRef((System::__GCObject*&)_gm_list$()),m_listSize += 10);
            }
            System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr32Obj)->_appendI((_gm_objectCounter$() - 1))->_appendClose());
            return _gm_objectCounter$() - 1;
        }
        else
        {
            u32 idx = _gm_freeHandlesList$()->_idx_g$(0);
            _gm_freeHandlesList$()->RemoveAt$(0);
            _gm_list$()->_idx_s$(idx,pObj);
            pObj->_acc_sHandle$(idx);
            System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr33Obj)->_appendU(idx)->_appendClose());
            return idx;
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr34Obj));
    }
}

inline u32 EnginePrototype::WrapperReg::registerGameObject$(EnginePrototype::GameObject* pObj) { CHCKTHIS; return registerGameObject(pObj); }

void EnginePrototype::WrapperReg::unregisterGameObject(EnginePrototype::GameObject* pObj)
{
    System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr35Obj)->_appendStr(pObj->ToString())->_appendStr(_$_cteStr36Obj)->_appendClose());
    if (pObj->_acc_gHandle$() != EnginePrototype::GameObject::NULLHANDLER)
    {
        _gm_freeHandlesList$()->Add$(pObj->_acc_gHandle$());
        _gm_list$()->_idx_s$(pObj->_acc_gHandle$(),NULL);
        pObj->_acc_sHandle$(EnginePrototype::GameObject::NULLHANDLER);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr37Obj));
    }
    System::Console::WriteLine(_$_cteStr38Obj);
}

inline void EnginePrototype::WrapperReg::unregisterGameObject$(EnginePrototype::GameObject* pObj) { CHCKTHIS; return unregisterGameObject(pObj); }

EnginePrototype::GameObject* EnginePrototype::WrapperReg::getObjectFromHandle(u32 handle)
{
    if (handle < _gm_listSize$())
    {
        return _gm_list$()->_idx_g$(handle);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr39Obj));
    }
}

inline EnginePrototype::GameObject* EnginePrototype::WrapperReg::getObjectFromHandle$(u32 handle) { CHCKTHIS; return getObjectFromHandle(handle); }

void EnginePrototype::WrapperReg::display()
{
    System::Console::WriteLine();
    System::Console::WriteLine(_$_cteStr40Obj);
    System::Console::WriteLine(_$_cteStr41Obj);
    System::Console::WriteLine(_$_cteStr40Obj);
    for (s32 i = 0;_gm_list$()->_idx_g$(i) != NULL && i < _gm_listSize$();++i)
    System::Console::WriteLine((CS_NEW System::String())->_appendStr(_$_cteStr42Obj)->_appendI(i)->_appendStr(_$_cteStr43Obj)->_appendStr(_gm_list$()->_idx_g$(i)->ToString())->_appendClose());
}

inline void EnginePrototype::WrapperReg::display$() { CHCKTHIS; return display(); }

inline System::Array<EnginePrototype::GameObject*>* EnginePrototype::WrapperReg::_sm_list(System::Array<EnginePrototype::GameObject*>* _$value)  { return (System::Array<EnginePrototype::GameObject*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_list,_$value); }
inline System::Array<EnginePrototype::GameObject*>* EnginePrototype::WrapperReg::_sm_list$(System::Array<EnginePrototype::GameObject*>* _$value) { CHCKTHIS; return _sm_list(_$value); }
inline System::Collections::Generic::List<u32>* EnginePrototype::WrapperReg::_sm_freeHandlesList(System::Collections::Generic::List<u32>* _$value)  { return (System::Collections::Generic::List<u32>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_freeHandlesList,_$value); }
inline System::Collections::Generic::List<u32>* EnginePrototype::WrapperReg::_sm_freeHandlesList$(System::Collections::Generic::List<u32>* _$value) { CHCKTHIS; return _sm_freeHandlesList(_$value); }
inline EnginePrototype::WrapperReg* EnginePrototype::WrapperReg::_sreg(EnginePrototype::WrapperReg* _$value)		{ return (EnginePrototype::WrapperReg*)System::__GCObject::_RefSetValue((System::__GCObject**)&reg,_$value); }


/*virtual*/
bool EnginePrototype::WrapperReg::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(WrapperReg,System::Object);
}

/*virtual*/
u32 EnginePrototype::WrapperReg::_processGC() {
    if (m_list) { System::Memory::pushList(m_list,0); }
    if (m_freeHandlesList) { System::Memory::pushList(m_freeHandlesList,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::WrapperReg::_releaseGC() {
    if (m_list && !m_list->isFreed()) { m_list->_removeRef((System::__GCObject**)&m_list); }
    if (m_freeHandlesList && !m_freeHandlesList->isFreed()) { m_freeHandlesList->_removeRef((System::__GCObject**)&m_freeHandlesList); }
}
/*virtual*/
void EnginePrototype::WrapperReg::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_list) {
      newPtr = (u8*)(&m_list); oldPtr = newPtr - offset;
      m_list->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_freeHandlesList) {
      newPtr = (u8*)(&m_freeHandlesList); oldPtr = newPtr - offset;
      m_freeHandlesList->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CSAPP'
//=============================

void EnginePrototype::CSAPP::_ctor_CSAPP() {
}

/*static*/
bool EnginePrototype::CSAPP::_ext_CKLBLuaLibAPP_callApplication(s32 type,s32* addr,s32* subject,s32* body)
{
    return CKLBLuaLibAPP_callApplication(type,addr,subject,body);
}

/*static*/
bool EnginePrototype::CSAPP::callApplication(s32 type,System::String* addr,System::String* subject,System::String* body)
{
    return _ext_CKLBLuaLibAPP_callApplication(type,System::__MarshallingUtils::NativeUtf8FromString(addr),System::__MarshallingUtils::NativeUtf8FromString(subject),System::__MarshallingUtils::NativeUtf8FromString(body));
}

EnginePrototype::CSAPP::CSAPP() { _ctor_CSAPP(); }



/*virtual*/
bool EnginePrototype::CSAPP::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSAPP,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSAPP::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSAPP::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSAPP::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSAsset'
//=============================

void EnginePrototype::CSAsset::_ctor_CSAsset() {
}

/*static*/
void EnginePrototype::CSAsset::_ext_CKLBLuaLibASSET_getImageSize(s32* assetName,s32& returnWidth,s32& returnHeight)
{
    CKLBLuaLibASSET_getImageSize(assetName,&returnWidth,&returnHeight);
}

/*static*/
void EnginePrototype::CSAsset::_ext_CKLBLuaLibASSET_getBoundSize(s32* assetName,float& returnWidth,float& returnHeight)
{
    CKLBLuaLibASSET_getBoundSize(assetName,&returnWidth,&returnHeight);
}

/*static*/
void EnginePrototype::CSAsset::_ext_CKLBLuaLibASSET_getAssetInfo(s32* assetName,s32& returnImgWidth,s32& returnImgHeight,float& returnBoundWidth,float& returnBoundHeight)
{
    CKLBLuaLibASSET_getAssetInfo(assetName,&returnImgWidth,&returnImgHeight,&returnBoundWidth,&returnBoundHeight);
}

/*static*/
void EnginePrototype::CSAsset::getImageSize(System::String* assetPath,s32& width,s32& height)
{
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getImageSize(System::__MarshallingUtils::NativeUtf8FromString(assetPath),width,height);
    EnginePrototype::NativeManagement::intercepCppError();
}

/*static*/
void EnginePrototype::CSAsset::getImageSize(System::String* assetPath,EnginePrototype::Size& size)
{
    s32 width = 0;
    s32 height = 0;
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getImageSize(System::__MarshallingUtils::NativeUtf8FromString(assetPath),width,height);
    EnginePrototype::NativeManagement::resetCppError();
    size._swidth$(width);
    size._sheight$(height);
}

/*static*/
void EnginePrototype::CSAsset::getBoundSize(System::String* assetPath,float& width,float& height)
{
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getBoundSize(System::__MarshallingUtils::NativeUtf8FromString(assetPath),width,height);
    EnginePrototype::NativeManagement::intercepCppError();
}

/*static*/
void EnginePrototype::CSAsset::getBoundSize(System::String* assetPath,EnginePrototype::FSize& size)
{
    float width = 0;
    float height = 0;
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getBoundSize(System::__MarshallingUtils::NativeUtf8FromString(assetPath),width,height);
    EnginePrototype::NativeManagement::intercepCppError();
    size._swidth$(width);
    size._sheight$(height);
}

/*static*/
void EnginePrototype::CSAsset::getAssetInfo(System::String* assetPath,s32& imgWidth,s32& imgHeight,float& boundWidth,float& boundHeight)
{
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getAssetInfo(System::__MarshallingUtils::NativeUtf8FromString(assetPath),imgWidth,imgHeight,boundWidth,boundHeight);
    EnginePrototype::NativeManagement::intercepCppError();
}

/*static*/
void EnginePrototype::CSAsset::getAssetInfo(System::String* assetPath,EnginePrototype::Size& imgSize,EnginePrototype::FSize& boundSize)
{
    s32 imgWidth = 0;
    s32 imgHeight = 0;
    float boundWidth = 0;
    float boundHeight = 0;
    EnginePrototype::NativeManagement::resetCppError();
    _ext_CKLBLuaLibASSET_getAssetInfo(System::__MarshallingUtils::NativeUtf8FromString(assetPath),imgWidth,imgHeight,boundWidth,boundHeight);
    EnginePrototype::NativeManagement::intercepCppError();
    imgSize._swidth$(imgWidth);
    imgSize._sheight$(imgHeight);
    boundSize._swidth$(boundWidth);
    boundSize._sheight$(boundHeight);
}

EnginePrototype::CSAsset::CSAsset() { _ctor_CSAsset(); }



/*virtual*/
bool EnginePrototype::CSAsset::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSAsset,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSAsset::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSAsset::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSAsset::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSBin'
//=============================

void EnginePrototype::CSBin::_ctor_CSBin() {
}

/*static*/
s32* EnginePrototype::CSBin::_ext_CKLBLuaLibBIN_open(s32* bin_asset)
{
    return CKLBLuaLibBIN_open(bin_asset);
}

/*static*/
void EnginePrototype::CSBin::_ext_CKLBLuaLibBIN_close(s32* pBIN)
{
    CKLBLuaLibBIN_close(pBIN);
}

/*static*/
bool EnginePrototype::CSBin::_ext_CKLBLuaLibBIN_peek(s32* pBIN,s32 offset,s32& value)
{
    return CKLBLuaLibBIN_peek(pBIN,offset,&value);
}

/*static*/
bool EnginePrototype::CSBin::_ext_CKLBLuaLibBIN_peek_u16(s32* pBIN,s32 offset,u32& value,bool f_bigendian)
{
    return CKLBLuaLibBIN_peek_u16(pBIN,offset,&value,f_bigendian);
}

/*static*/
bool EnginePrototype::CSBin::_ext_CKLBLuaLibBIN_peek_u32(s32* pBIN,s32 offset,u32& value,bool f_bigendian)
{
    return CKLBLuaLibBIN_peek_u32(pBIN,offset,&value,f_bigendian);
}

EnginePrototype::CSBin::CSBin(System::String* bin_asset) : EnginePrototype::GameObject(s_classID)
{
    _ctor_CSBin();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBLuaLibBIN_open(System::__MarshallingUtils::NativeUtf8FromString(bin_asset));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

/*virtual*/
void EnginePrototype::CSBin::clearInternals()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibBIN_close(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CSBin::clearInternals$() { CHCKTHIS; return clearInternals(); }

bool EnginePrototype::CSBin::peek(s32 offset,s32& value)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibBIN_peek(EnginePrototype::GameObject::_acc_gCppObject$(),offset,value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CSBin::peek$(s32 offset,s32& value) { CHCKTHIS; return peek(offset,value); }

bool EnginePrototype::CSBin::peek_u16(s32 offset,u32& value,bool f_bigendian)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibBIN_peek_u16(EnginePrototype::GameObject::_acc_gCppObject$(),offset,value,f_bigendian);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CSBin::peek_u16$(s32 offset,u32& value,bool f_bigendian) { CHCKTHIS; return peek_u16(offset,value,f_bigendian); }

bool EnginePrototype::CSBin::peek_u32(s32 offset,u32& value,bool f_bigendian)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibBIN_peek_u32(EnginePrototype::GameObject::_acc_gCppObject$(),offset,value,f_bigendian);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CSBin::peek_u32$(s32 offset,u32& value,bool f_bigendian) { CHCKTHIS; return peek_u32(offset,value,f_bigendian); }

EnginePrototype::CSBin::CSBin() { _ctor_CSBin(); }



/*virtual*/
bool EnginePrototype::CSBin::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSBin,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CSBin::_processGC() {
    EnginePrototype::GameObject::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSBin::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

}
/*virtual*/
void EnginePrototype::CSBin::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

}

//=============================
// Implementation of 'CSData'
//=============================

void EnginePrototype::CSData::_ctor_CSData() {
}

/*static*/
s32* EnginePrototype::CSData::_ext_CKLBLuaLibDATA_cmdCreateData(u32 dataSetID)
{
    return CKLBLuaLibDATA_cmdCreateData(dataSetID);
}

/*static*/
bool EnginePrototype::CSData::_ext_CKLBLuaLibDATA_cmdRegistData(s32* pDataSet,s32* nameAsset,u32& pReturnHandle)
{
    return CKLBLuaLibDATA_cmdRegistData(pDataSet,nameAsset,&pReturnHandle);
}

/*static*/
void EnginePrototype::CSData::_ext_CKLBLuaLibDATA_cmdDelete(s32* pDataSet)
{
    CKLBLuaLibDATA_cmdDelete(pDataSet);
}

EnginePrototype::CSData::CSData(u32 ID) : EnginePrototype::GameObject(s_classID)
{
    _ctor_CSData();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBLuaLibDATA_cmdCreateData(ID);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

bool EnginePrototype::CSData::registerData(System::String* nameAsset,u32& pReturnHandle)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibDATA_cmdRegistData(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(nameAsset),pReturnHandle);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CSData::registerData$(System::String* nameAsset,u32& pReturnHandle) { CHCKTHIS; return registerData(nameAsset,pReturnHandle); }

/*virtual*/
void EnginePrototype::CSData::clearInternals()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibDATA_cmdDelete(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CSData::clearInternals$() { CHCKTHIS; return clearInternals(); }

EnginePrototype::CSData::CSData() { _ctor_CSData(); }



/*virtual*/
bool EnginePrototype::CSData::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSData,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CSData::_processGC() {
    EnginePrototype::GameObject::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSData::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

}
/*virtual*/
void EnginePrototype::CSData::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

}

//=============================
// Implementation of 'CSDB'
//=============================

void EnginePrototype::CSDB::_ctor_CSDB() {
}

/*static*/
s32* EnginePrototype::CSDB::_ext_CKLBLuaLibDB_dbopen(s32* db_asset,bool b_write,bool b_create)
{
    return CKLBLuaLibDB_dbopen(db_asset,b_write,b_create);
}

/*static*/
void EnginePrototype::CSDB::_ext_CKLBLuaLibDB_dbclose(s32* pDB)
{
    CKLBLuaLibDB_dbclose(pDB);
}

/*static*/
void EnginePrototype::CSDB::_ext_CKLBLuaLibDB_closeAll()
{
    CKLBLuaLibDB_closeAll();
}

/*static*/
s32* EnginePrototype::CSDB::_ext_CKLBLuaLibDB_query(s32* pDB,s32* sqlQuery,s32& nbEntries)
{
    return CKLBLuaLibDB_query(pDB,sqlQuery,&nbEntries);
}

EnginePrototype::CSDB::CSDB(System::String* db_asset,bool b_write,bool b_create) : EnginePrototype::GameObject(s_classID)
{
    _ctor_CSDB();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBLuaLibDB_dbopen(System::__MarshallingUtils::NativeUtf8FromString(db_asset),b_write,b_create);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_isWritable$(b_write);
    _sm_isCreatable$(b_create);
}

/*virtual*/
void EnginePrototype::CSDB::clearInternals()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibDB_dbclose(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CSDB::clearInternals$() { CHCKTHIS; return clearInternals(); }

/*static*/
void EnginePrototype::CSDB::closeAll()
{
    _ext_CKLBLuaLibDB_closeAll();
}

void EnginePrototype::CSDB::_ref_query(System::String* sqlQuery,System::Array<System::String*>*& results)
{
    s32 nbEntries = 0;
    s32* p = _ext_CKLBLuaLibDB_query(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(sqlQuery),nbEntries);
    results = System::__MarshallingUtils::StringArrayFromNativeUtf8IntPtr(p,nbEntries * 2);
}

inline void EnginePrototype::CSDB::query$(System::String* sqlQuery,System::Array<System::String*>*& results) { CHCKTHIS; return query(sqlQuery,results); }

inline void EnginePrototype::CSDB::query(System::String* sqlQuery,System::Array<System::String*>*& results) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); _ref_query(sqlQuery,results); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); }

EnginePrototype::CSDB::CSDB() { _ctor_CSDB(); }



inline bool EnginePrototype::CSDB::_acc_gIsWritable(){
    return _gm_isWritable$();
}

inline bool EnginePrototype::CSDB::_acc_gIsWritable$() { CHCKTHIS; return _acc_gIsWritable(); }

inline bool EnginePrototype::CSDB::_acc_gIsCreatable(){
    return _gm_isCreatable$();
}

inline bool EnginePrototype::CSDB::_acc_gIsCreatable$() { CHCKTHIS; return _acc_gIsCreatable(); }

/*virtual*/
bool EnginePrototype::CSDB::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSDB,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CSDB::_processGC() {
    EnginePrototype::GameObject::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSDB::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

}
/*virtual*/
void EnginePrototype::CSDB::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

}

//=============================
// Implementation of 'CSDebug'
//=============================

void EnginePrototype::CSDebug::_ctor_CSDebug() {
}

/*static*/
void EnginePrototype::CSDebug::_ext_CKLBLuaLibDEBUG_startMenu(u32 maxCount,s32* caption,s32* key)
{
    CKLBLuaLibDEBUG_startMenu(maxCount,caption,key);
}

/*static*/
void EnginePrototype::CSDebug::_ext_CKLBLuaLibDEBUG_addItem(u32 mode,s32* caption,s32* key,s32 min,s32 max,s32 value,System::Array<s32*>* items,u32 itemsCount)
{
    CKLBLuaLibDEBUG_addItem(mode,caption,key,min,max,value,items ? (s32**)items->_getPArray() : NULL,itemsCount);
}

/*static*/
void EnginePrototype::CSDebug::_ext_CKLBLuaLibDEBUG_endMenu()
{
    CKLBLuaLibDEBUG_endMenu();
}

/*static*/
void EnginePrototype::CSDebug::_ext_CKLBLuaLibDEBUG_removeMenu(s32* key)
{
    CKLBLuaLibDEBUG_removeMenu(key);
}

/*static*/
void EnginePrototype::CSDebug::setCallback()
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionNotImplemented(_$_cteStr1Obj));
}

/*static*/
void EnginePrototype::CSDebug::startMenu(u32 maxCount,System::String* caption,System::String* key)
{
    if (s_isBuildingMenu)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr47Obj));
    }
    s_isBuildingMenu = true;
    _ext_CKLBLuaLibDEBUG_startMenu(maxCount,System::__MarshallingUtils::NativeUtf8FromString(caption),System::__MarshallingUtils::NativeUtf8FromString(key));
}

/*static*/
void EnginePrototype::CSDebug::addItemSwitch(System::String* itemName,System::String* itemKey,bool defaultValue)
{
    if (!s_isBuildingMenu)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr48Obj));
    }
    _ext_CKLBLuaLibDEBUG_addItem((u32)ESECTION_TYPE::M_SWITCH,System::__MarshallingUtils::NativeUtf8FromString(itemName),System::__MarshallingUtils::NativeUtf8FromString(itemKey),0,0,((defaultValue) ? 1 : 0),(System::Array<s32*>*)NULL,0);
}

/*static*/
void EnginePrototype::CSDebug::addItemSelect(System::String* itemName,System::String* itemKey,System::String* defaultValue,System::Array<System::String*>* items)
{
    if (!s_isBuildingMenu)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr48Obj));
    }
    _ext_CKLBLuaLibDEBUG_addItem((u32)ESECTION_TYPE::M_SELECT,System::__MarshallingUtils::NativeUtf8FromString(itemName),System::__MarshallingUtils::NativeUtf8FromString(itemKey),0,0,System::AbstractArray::IndexOf(items,defaultValue),System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(items,items->_acc_gLength$()),(u32)items->_acc_gLength$());
}

/*static*/
void EnginePrototype::CSDebug::addItemNumber(System::String* itemName,System::String* itemKey,s32 lowerLimit,s32 upperLimit,s32 defaultValue)
{
    if (!s_isBuildingMenu)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr48Obj));
    }
    _ext_CKLBLuaLibDEBUG_addItem((u32)ESECTION_TYPE::M_NUMBER,System::__MarshallingUtils::NativeUtf8FromString(itemName),System::__MarshallingUtils::NativeUtf8FromString(itemKey),lowerLimit,upperLimit,defaultValue,(System::Array<s32*>*)NULL,0);
}

/*static*/
void EnginePrototype::CSDebug::endMenu()
{
    if (!s_isBuildingMenu)
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr48Obj));
    }
    _ext_CKLBLuaLibDEBUG_endMenu();
    s_isBuildingMenu = false;
}

/*static*/
void EnginePrototype::CSDebug::removeMenu(System::String* key)
{
    _ext_CKLBLuaLibDEBUG_removeMenu(System::__MarshallingUtils::NativeUtf8FromString(key));
}

EnginePrototype::CSDebug::CSDebug() { _ctor_CSDebug(); }



/*virtual*/
bool EnginePrototype::CSDebug::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSDebug,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSDebug::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSDebug::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSDebug::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSEng'
//=============================

void EnginePrototype::CSEng::_ctor_CSEng() {
}

/*static*/
bool EnginePrototype::CSEng::_ext_CKLBLuaLibENG_isRelease()
{
    return CKLBLuaLibENG_isRelease();
}

/*static*/
s32* EnginePrototype::CSEng::_ext_CKLBLuaLibENG_getPlatform()
{
    return CKLBLuaLibENG_getPlatform();
}

/*static*/
void EnginePrototype::CSEng::_ext_CKLBLuaLibENG_getNanoTime(s32& milli,s32& nano)
{
    CKLBLuaLibENG_getNanoTime(&milli,&nano);
}

/*static*/
void EnginePrototype::CSEng::_ext_CKLBLuaLibENG_startNanoTime(s32 idx)
{
    CKLBLuaLibENG_startNanoTime(idx);
}

/*static*/
void EnginePrototype::CSEng::_ext_CKLBLuaLibENG_endNanoTime(s32 idx,s32& milli,s32& nano)
{
    CKLBLuaLibENG_endNanoTime(idx,&milli,&nano);
}

/*static*/
u32 EnginePrototype::CSEng::_ext_CKLBLuaLibENG_getFrameID()
{
    return CKLBLuaLibENG_getFrameID();
}

/*static*/
void EnginePrototype::CSEng::getNanoTime(s32& milli,s32& nano)
{
    _ext_CKLBLuaLibENG_getNanoTime(milli,nano);
}

/*static*/
void EnginePrototype::CSEng::startNanoTime(s32 idx)
{
    _ext_CKLBLuaLibENG_startNanoTime(idx);
}

/*static*/
void EnginePrototype::CSEng::endNanoTime(s32 idx,s32& milli,s32& nano)
{
    _ext_CKLBLuaLibENG_endNanoTime(idx,milli,nano);
}

EnginePrototype::CSEng::CSEng() { _ctor_CSEng(); }



inline bool EnginePrototype::CSEng::_acc_gIsRelease(){
    return _ext_CKLBLuaLibENG_isRelease();
}

inline System::String* EnginePrototype::CSEng::_acc_gPlatform(){
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBLuaLibENG_getPlatform());
}

inline u32 EnginePrototype::CSEng::_acc_gFrameId(){
    return _ext_CKLBLuaLibENG_getFrameID();
}

/*virtual*/
bool EnginePrototype::CSEng::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSEng,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSEng::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSEng::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSEng::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSFont'
//=============================

void EnginePrototype::CSFont::_ctor_CSFont() {
}

/*static*/
s32* EnginePrototype::CSFont::_ext_CKLBLuaLibFONT_createFont(s32 size,s32* fontName)
{
    return CKLBLuaLibFONT_createFont(size,fontName);
}

/*static*/
void EnginePrototype::CSFont::_ext_CKLBLuaLibFONT_removeFont(s32* font)
{
    CKLBLuaLibFONT_removeFont(font);
}

/*static*/
void EnginePrototype::CSFont::_ext_CKLBLuaLibFONT_cmdGetTextInfo(s32* str,s32* font,EnginePrototype::STextInfo_inner0& outInfo)
{
    CKLBLuaLibFONT_cmdGetTextInfo(str,font,(s32*)&outInfo + 1);
}

EnginePrototype::CSFont::CSFont(u32 size,System::String* name) : EnginePrototype::GameObject(s_classID)
{
    _ctor_CSFont();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBLuaLibFONT_createFont((s32)size,System::__MarshallingUtils::NativeUtf8FromString(name));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_size$(size);
    _sm_name$(name);
}

/*virtual*/
void EnginePrototype::CSFont::clearInternals()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibFONT_removeFont(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CSFont::clearInternals$() { CHCKTHIS; return clearInternals(); }

void EnginePrototype::CSFont::getTextInfo(System::String* text,EnginePrototype::STextInfo_inner0& info)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibFONT_cmdGetTextInfo(System::__MarshallingUtils::NativeUtf8FromString(text),EnginePrototype::GameObject::_acc_gCppObject$(),info);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSFont::getTextInfo$(System::String* text,EnginePrototype::STextInfo_inner0& info) { CHCKTHIS; return getTextInfo(text,info); }

EnginePrototype::CSFont::CSFont() { _ctor_CSFont(); }

inline System::String* EnginePrototype::CSFont::_sm_name(System::String* _$value)  { return (System::String*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_name,_$value); }
inline System::String* EnginePrototype::CSFont::_sm_name$(System::String* _$value) { CHCKTHIS; return _sm_name(_$value); }


inline u32 EnginePrototype::CSFont::_acc_gSize(){
    return _gm_size$();
}

inline u32 EnginePrototype::CSFont::_acc_gSize$() { CHCKTHIS; return _acc_gSize(); }

inline u32 EnginePrototype::CSFont::_acc_sSize(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_size$(value);
        _ext_CKLBLuaLibFONT_removeFont(EnginePrototype::GameObject::_acc_gCppObject$());
        EnginePrototype::NativeManagement::resetCppError();
        s32* ptr = _ext_CKLBLuaLibFONT_createFont((s32)value,System::__MarshallingUtils::NativeUtf8FromString(_gm_name$()));
        EnginePrototype::NativeManagement::intercepCppError();
        EnginePrototype::WrapperReg::getInstance()->registerGameObject$(this);
        EnginePrototype::GameObject::bind$(ptr);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CSFont::_acc_sSize$(u32 value)		{ CHCKTHIS; return _acc_sSize(value); }
inline System::String* EnginePrototype::CSFont::_acc_gName(){
    return _gm_name$();
}

inline System::String* EnginePrototype::CSFont::_acc_gName$() { CHCKTHIS; return _acc_gName(); }

inline System::String* EnginePrototype::CSFont::_acc_sName(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_name$(value);
        _ext_CKLBLuaLibFONT_removeFont(EnginePrototype::GameObject::_acc_gCppObject$());
        EnginePrototype::NativeManagement::resetCppError();
        s32* ptr = _ext_CKLBLuaLibFONT_createFont((s32)_gm_size$(),System::__MarshallingUtils::NativeUtf8FromString(value));
        EnginePrototype::NativeManagement::intercepCppError();
        EnginePrototype::WrapperReg::getInstance()->registerGameObject$(this);
        EnginePrototype::GameObject::bind$(ptr);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CSFont::_acc_sName$(System::String* value)		{ CHCKTHIS; return _acc_sName(value); }
/*virtual*/
bool EnginePrototype::CSFont::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSFont,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CSFont::_processGC() {
    EnginePrototype::GameObject::_processGC();

    if (m_name) { System::Memory::pushList(m_name,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSFont::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

    if (m_name && !m_name->isFreed()) { m_name->_removeRef((System::__GCObject**)&m_name); }
}
/*virtual*/
void EnginePrototype::CSFont::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_name) {
      newPtr = (u8*)(&m_name); oldPtr = newPtr - offset;
      m_name->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'STextInfo_inner0'
//=============================

void EnginePrototype::STextInfo_inner0::_ctor_STextInfo_inner0() {
}

EnginePrototype::STextInfo_inner0::STextInfo_inner0() { _ctor_STextInfo_inner0(); }


inline u32 EnginePrototype::STextInfo_inner0::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::STextInfo_inner0::_releaseGC() {
}
inline void* EnginePrototype::STextInfo_inner0::_RefSetValue(void* newStruct) {
    STextInfo_inner0* pStruct = (STextInfo_inner0*)newStruct;
    this->width = pStruct->width;
    this->height = pStruct->height;
    this->ascent = pStruct->ascent;
    this->descent = pStruct->descent;
    this->top = pStruct->top;
    this->bottom = pStruct->bottom;
    return newStruct;
}
inline void EnginePrototype::STextInfo_inner0::_moveAlert(u32 offset) {
}
inline EnginePrototype::STextInfo_inner0& EnginePrototype::STextInfo_inner0::__registerByRef(EnginePrototype::STextInfo_inner0& m) {
    return m;
}


//=============================
// Implementation of 'CSGL'
//=============================

void EnginePrototype::CSGL::_ctor_CSGL() {
}

/*static*/
void EnginePrototype::CSGL::_ext_CKLBLuaLibGL_GLClearColor(float r,float g,float b,float a)
{
    CKLBLuaLibGL_GLClearColor(r,g,b,a);
}

/*static*/
void EnginePrototype::CSGL::_ext_CKLBLuaLibGL_GLSetResolution(s32 width,s32 height)
{
    CKLBLuaLibGL_GLSetResolution(width,height);
}

/*static*/
bool EnginePrototype::CSGL::_ext_CKLBLuaLibGL_GLCreateScreenAsset(s32* name)
{
    return CKLBLuaLibGL_GLCreateScreenAsset(name);
}

/*static*/
bool EnginePrototype::CSGL::_ext_CKLBLuaLibGL_GLDoScreenShot(s32* name)
{
    return CKLBLuaLibGL_GLDoScreenShot(name);
}

/*static*/
void EnginePrototype::CSGL::_ext_CKLBLuaLibGL_GLFreeScreenAsset(s32* name)
{
    CKLBLuaLibGL_GLFreeScreenAsset(name);
}

/*static*/
void EnginePrototype::CSGL::_ext_CKLBLuaLibGL_SGGetGuardBand(float& leftBorder,float& rightBorder,float& topBorder,float& bottomBorder)
{
    CKLBLuaLibGL_SGGetGuardBand(&leftBorder,&rightBorder,&topBorder,&bottomBorder);
}

/*static*/
void EnginePrototype::CSGL::_ext_CKLBLuaLibGL_SGSetGuardBand(float leftBorder,float rightBorder,float topBorder,float bottomBorder)
{
    CKLBLuaLibGL_SGSetGuardBand(leftBorder,rightBorder,topBorder,bottomBorder);
}

/*static*/
void EnginePrototype::CSGL::clearColor(float r,float g,float b,float a)
{
    _ext_CKLBLuaLibGL_GLClearColor(r,g,b,a);
}

/*static*/
void EnginePrototype::CSGL::setResolution(s32 width,s32 height)
{
    _ext_CKLBLuaLibGL_GLSetResolution(width,height);
}

/*static*/
bool EnginePrototype::CSGL::createScreenAsset(System::String* name)
{
    return _ext_CKLBLuaLibGL_GLCreateScreenAsset(System::__MarshallingUtils::NativeUtf8FromString(name));
}

/*static*/
bool EnginePrototype::CSGL::doScreenShot(System::String* name)
{
    return _ext_CKLBLuaLibGL_GLDoScreenShot(System::__MarshallingUtils::NativeUtf8FromString(name));
}

/*static*/
void EnginePrototype::CSGL::freeScreenAsset(System::String* name)
{
    _ext_CKLBLuaLibGL_GLFreeScreenAsset(System::__MarshallingUtils::NativeUtf8FromString(name));
}

/*static*/
void EnginePrototype::CSGL::getGuardBand(float& leftBorder,float& rightBorder,float& topBorder,float& bottomBorder)
{
    _ext_CKLBLuaLibGL_SGGetGuardBand(leftBorder,rightBorder,topBorder,bottomBorder);
}

/*static*/
void EnginePrototype::CSGL::setGuardBand(float leftBorder,float rightBorder,float topBorder,float bottomBorder)
{
    _ext_CKLBLuaLibGL_SGSetGuardBand(leftBorder,rightBorder,topBorder,bottomBorder);
}

EnginePrototype::CSGL::CSGL() { _ctor_CSGL(); }



/*virtual*/
bool EnginePrototype::CSGL::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSGL,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSGL::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSGL::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSGL::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSKey'
//=============================

void EnginePrototype::CSKey::_ctor_CSKey() {
}

/*static*/
s32 EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_genUserID(s32* userId,u32 bufSize)
{
    return CKLBLuaLibKEY_genUserID(userId,bufSize);
}

/*static*/
s32 EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_genUserPW(s32* userId,s32* buf,u32 bufSize)
{
    return CKLBLuaLibKEY_genUserPW(userId,buf,bufSize);
}

/*static*/
bool EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_setSecureID(s32* serviceName,s32* userId)
{
    return CKLBLuaLibKEY_setSecureID(serviceName,userId);
}

/*static*/
bool EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_setSecurePW(s32* serviceName,s32* passwd)
{
    return CKLBLuaLibKEY_setSecurePW(serviceName,passwd);
}

/*static*/
s32 EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_getSecureID(s32* serviceName,s32* buf,u32 bufSize)
{
    return CKLBLuaLibKEY_getSecureID(serviceName,buf,bufSize);
}

/*static*/
s32 EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_getSecurePW(s32* serviceName,s32* buf,u32 bufSize)
{
    return CKLBLuaLibKEY_getSecurePW(serviceName,buf,bufSize);
}

/*static*/
bool EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_delSecureID(s32* serviceName)
{
    return CKLBLuaLibKEY_delSecureID(serviceName);
}

/*static*/
bool EnginePrototype::CSKey::_ext_CKLBLuaLibKEY_delSecurePW(s32* serviceName)
{
    return CKLBLuaLibKEY_delSecurePW(serviceName);
}

/*static*/
s32 EnginePrototype::CSKey::_ref_genUserID(System::String*& userId,u32 bufSize)
{
    s32* intPtr = System::__MarshallingUtils::NativeUtf8FromString(CS_NEW System::String('0',(s32)bufSize));
    s32 len = _ext_CKLBLuaLibKEY_genUserID(intPtr,bufSize);
    userId = System::__MarshallingUtils::StringFromNativeUtf8(intPtr);
    return len;
}

inline s32 EnginePrototype::CSKey::genUserID(System::String*& userId,u32 bufSize) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); s32 r = _ref_genUserID(userId,bufSize); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

/*static*/
s32 EnginePrototype::CSKey::_ref_genUserPW(System::String* userId,System::String*& passwd,u32 bufSize)
{
    s32* intPtr = System::__MarshallingUtils::NativeUtf8FromString(CS_NEW System::String('0',(s32)bufSize));
    s32 len = _ext_CKLBLuaLibKEY_genUserPW(System::__MarshallingUtils::NativeUtf8FromString(userId),intPtr,bufSize);
    passwd = System::__MarshallingUtils::StringFromNativeUtf8(intPtr);
    return len;
}

inline s32 EnginePrototype::CSKey::genUserPW(System::String* userId,System::String*& passwd,u32 bufSize) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); s32 r = _ref_genUserPW(userId,passwd,bufSize); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

/*static*/
bool EnginePrototype::CSKey::setSecureID(System::String* serviceName,System::String* userId)
{
    return _ext_CKLBLuaLibKEY_setSecureID(System::__MarshallingUtils::NativeUtf8FromString(serviceName),System::__MarshallingUtils::NativeUtf8FromString(userId));
}

/*static*/
bool EnginePrototype::CSKey::setSecurePW(System::String* serviceName,System::String* passwd)
{
    return _ext_CKLBLuaLibKEY_setSecurePW(System::__MarshallingUtils::NativeUtf8FromString(serviceName),System::__MarshallingUtils::NativeUtf8FromString(passwd));
}

/*static*/
s32 EnginePrototype::CSKey::_ref_getSecureID(System::String* serviceName,System::String*& secureID,u32 bufSize)
{
    s32* intPtr = System::__MarshallingUtils::NativeUtf8FromString(CS_NEW System::String('0',(s32)bufSize));
    s32 len = _ext_CKLBLuaLibKEY_getSecureID(System::__MarshallingUtils::NativeUtf8FromString(serviceName),intPtr,bufSize);
    secureID = System::__MarshallingUtils::StringFromNativeUtf8(intPtr);
    return len;
}

inline s32 EnginePrototype::CSKey::getSecureID(System::String* serviceName,System::String*& secureID,u32 bufSize) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); s32 r = _ref_getSecureID(serviceName,secureID,bufSize); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

/*static*/
s32 EnginePrototype::CSKey::_ref_getSecurePW(System::String* serviceName,System::String*& securePW,u32 bufSize)
{
    s32* intPtr = System::__MarshallingUtils::NativeUtf8FromString(CS_NEW System::String('0',(s32)bufSize));
    s32 len = _ext_CKLBLuaLibKEY_getSecurePW(System::__MarshallingUtils::NativeUtf8FromString(serviceName),intPtr,bufSize);
    securePW = System::__MarshallingUtils::StringFromNativeUtf8(intPtr);
    return len;
}

inline s32 EnginePrototype::CSKey::getSecurePW(System::String* serviceName,System::String*& securePW,u32 bufSize) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); s32 r = _ref_getSecurePW(serviceName,securePW,bufSize); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

/*static*/
bool EnginePrototype::CSKey::delSecureID(System::String* serviceName)
{
    return _ext_CKLBLuaLibKEY_delSecureID(System::__MarshallingUtils::NativeUtf8FromString(serviceName));
}

/*static*/
bool EnginePrototype::CSKey::delSecurePW(System::String* serviceName)
{
    return _ext_CKLBLuaLibKEY_delSecurePW(System::__MarshallingUtils::NativeUtf8FromString(serviceName));
}

EnginePrototype::CSKey::CSKey() { _ctor_CSKey(); }



/*virtual*/
bool EnginePrototype::CSKey::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSKey,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSKey::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSKey::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSKey::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSLang'
//=============================

void EnginePrototype::CSLang::_ctor_CSLang() {
}

/*static*/
bool EnginePrototype::CSLang::_ext_CKLBLuaLibLANG_addString(s32* id,s32* str)
{
    return CKLBLuaLibLANG_addString(id,str);
}

/*static*/
s32* EnginePrototype::CSLang::_ext_CKLBLuaLibLANG_getString(s32* id)
{
    return CKLBLuaLibLANG_getString(id);
}

/*static*/
void EnginePrototype::CSLang::_ext_CKLBLuaLibLANG_removeString(s32* id)
{
    CKLBLuaLibLANG_removeString(id);
}

/*static*/
bool EnginePrototype::CSLang::_ext_CKLBLuaLibLANG_useDB(s32* dbFile,s32* table,s32* keyF,s32* valueF,s32* groupF)
{
    return CKLBLuaLibLANG_useDB(dbFile,table,keyF,valueF,groupF);
}

/*static*/
bool EnginePrototype::CSLang::_ext_CKLBLuaLibLANG_loadGroup(s32* groupId)
{
    return CKLBLuaLibLANG_loadGroup(groupId);
}

/*static*/
bool EnginePrototype::CSLang::addString(System::String* id,System::String* str)
{
    return _ext_CKLBLuaLibLANG_addString(System::__MarshallingUtils::NativeUtf8FromString(id),System::__MarshallingUtils::NativeUtf8FromString(str));
}

/*static*/
System::String* EnginePrototype::CSLang::getString(System::String* id)
{
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBLuaLibLANG_getString(System::__MarshallingUtils::NativeUtf8FromString(id)));
}

/*static*/
void EnginePrototype::CSLang::removeString(System::String* id)
{
    _ext_CKLBLuaLibLANG_removeString(System::__MarshallingUtils::NativeUtf8FromString(id));
}

/*static*/
bool EnginePrototype::CSLang::useDB(System::String* dbFile,System::String* table,System::String* keyF,System::String* valueF,System::String* groupF)
{
    return _ext_CKLBLuaLibLANG_useDB(System::__MarshallingUtils::NativeUtf8FromString(dbFile),System::__MarshallingUtils::NativeUtf8FromString(table),System::__MarshallingUtils::NativeUtf8FromString(keyF),System::__MarshallingUtils::NativeUtf8FromString(valueF),System::__MarshallingUtils::NativeUtf8FromString(groupF));
}

/*static*/
bool EnginePrototype::CSLang::loadGroup(System::String* groupId)
{
    return _ext_CKLBLuaLibLANG_loadGroup(System::__MarshallingUtils::NativeUtf8FromString(groupId));
}

EnginePrototype::CSLang::CSLang() { _ctor_CSLang(); }



/*virtual*/
bool EnginePrototype::CSLang::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSLang,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSLang::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSLang::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSLang::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSMatrix'
//=============================

void EnginePrototype::CSMatrix::_ctor_CSMatrix() {
}

EnginePrototype::CSMatrix::CSMatrix(System::Array<float>* matrix)
{
    _ctor_CSMatrix();
    if (matrix != NULL)
    {
        if (matrix->_acc_gLength$() == 16)
        {
            _sm_matrix$(matrix);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr50Obj));
        }
    }
    else
    {
        _sm_matrix$((System::Array<float>*)_global_array_initializer_0(CS_NEW System::Array< float >(16)));
    }
}

System::Object* EnginePrototype::CSMatrix::Clone()
{
    return CS_NEW EnginePrototype::CSMatrix((System::Array<float>*)_gm_matrix$()->Clone$());
}

inline System::Object* EnginePrototype::CSMatrix::Clone$() { CHCKTHIS; return Clone(); }

EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Copy()
{
    return (EnginePrototype::CSMatrix*)this->Clone$();
}

inline EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Copy$() { CHCKTHIS; return Copy(); }

EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Transposed()
{
    System::Array<float>* res = (System::Array<float>*)_global_array_initializer_1(CS_NEW System::Array< float >(16));
    for (s32 i = 0;i < 4;++i)
    {
        for (s32 j = 0;j < 4;++j)
        {
            res->_idx_s$(4 * i + j,_gm_matrix$()->_idx_g$(4 * j + i));
        }
    }
    return CS_NEW EnginePrototype::CSMatrix(res);
}

inline EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Transposed$() { CHCKTHIS; return Transposed(); }

EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Mul(EnginePrototype::CSMatrix* mat)
{
    System::Array<float>* res = (System::Array<float>*)_global_array_initializer_2(CS_NEW System::Array< float >(16));
    for (s32 i = 0;i < 4;++i)
    {
        for (s32 j = 0;j < 4;++j)
        {
            for (s32 k = 0;k < 4;++k)
            {
                res->_idx_g$(4 * j + i) += this->_idx_g$(i,k) * mat->_idx_g$(k,j);
            }
        }
    }
    return CS_NEW EnginePrototype::CSMatrix(res);
}

inline EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Mul$(EnginePrototype::CSMatrix* mat) { CHCKTHIS; return Mul(mat); }

EnginePrototype::CSVector_inner1* EnginePrototype::CSMatrix::Mul(EnginePrototype::CSVector_inner1* vect)
{
    System::Array<float>* res = (System::Array<float>*)_global_array_initializer_3(CS_NEW System::Array< float >(4));
    for (s32 i = 0;i < 4;++i)
    {
        for (s32 k = 0;k < 4;++k)
        {
            res->_idx_g$(i) += this->_idx_g$(i,k) * vect->_idx_g$(k);
        }
    }
    return CS_NEW EnginePrototype::CSVector_inner1(res);
}

inline EnginePrototype::CSVector_inner1* EnginePrototype::CSMatrix::Mul$(EnginePrototype::CSVector_inner1* vect) { CHCKTHIS; return Mul(vect); }

/*static*/
float EnginePrototype::CSMatrix::fabs(float f)
{
    return (f >= 0 ? f : f * (-1));
}

EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Inverse()
{
    System::Array<float>* A = _gm_matrix$();
    System::Array<float>* B = (System::Array<float>*)_global_array_initializer_4(CS_NEW System::Array< float >(16));
    for (s32 y = 0;y < 4;++y)
    {
        float n = A->_idx_g$(4 * y + y);
        if (fabs(n) < EPSILON)
        return NULL;
        for (s32 x = 0;x < 4;++x)
        {
            A->_idx_g$(4 * y + x) /= n;
            B->_idx_g$(4 * y + x) /= n;
        }
        for (s32 x = 0;x < 4;++x)
        {
            if (x == y)
            {
                continue;
            }
            n = A->_idx_g$(4 * x + y);
            for (s32 z = 0;z < 4;++z)
            {
                A->_idx_g$(4 * x + z) -= A->_idx_g$(4 * y + z) * n;
                B->_idx_g$(4 * x + z) -= B->_idx_g$(4 * y + z) * n;
            }
        }
    }
    return CS_NEW EnginePrototype::CSMatrix(B);
}

inline EnginePrototype::CSMatrix* EnginePrototype::CSMatrix::Inverse$() { CHCKTHIS; return Inverse(); }

EnginePrototype::CSMatrix::CSMatrix() { _ctor_CSMatrix(); }

inline System::Array<float>* EnginePrototype::CSMatrix::_sm_matrix(System::Array<float>* _$value)  { return (System::Array<float>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_matrix,_$value); }
inline System::Array<float>* EnginePrototype::CSMatrix::_sm_matrix$(System::Array<float>* _$value) { CHCKTHIS; return _sm_matrix(_$value); }


inline float EnginePrototype::CSMatrix::_idx_g(s32 i, s32 j){
    return _gm_matrix$()->_idx_g$(4 * i + j);
}

inline float EnginePrototype::CSMatrix::_idx_g$(s32 i, s32 j) { CHCKTHIS; return _idx_g(i, j); }

/*virtual*/
bool EnginePrototype::CSMatrix::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSMatrix,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSMatrix::_processGC() {
    if (m_matrix) { System::Memory::pushList(m_matrix,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSMatrix::_releaseGC() {
    if (m_matrix && !m_matrix->isFreed()) { m_matrix->_removeRef((System::__GCObject**)&m_matrix); }
}
/*virtual*/
void EnginePrototype::CSMatrix::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_matrix) {
      newPtr = (u8*)(&m_matrix); oldPtr = newPtr - offset;
      m_matrix->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CSVector_inner1'
//=============================

void EnginePrototype::CSVector_inner1::_ctor_CSVector_inner1() {
}

EnginePrototype::CSVector_inner1::CSVector_inner1(System::Array<float>* vector)
{
    _ctor_CSVector_inner1();
    _sm_vector$(vector);
}

System::Object* EnginePrototype::CSVector_inner1::Clone()
{
    return CS_NEW EnginePrototype::CSVector_inner1((System::Array<float>*)_gm_vector$()->Clone$());
}

inline System::Object* EnginePrototype::CSVector_inner1::Clone$() { CHCKTHIS; return Clone(); }

EnginePrototype::CSVector_inner1::CSVector_inner1() { _ctor_CSVector_inner1(); }

inline System::Array<float>* EnginePrototype::CSVector_inner1::_sm_vector(System::Array<float>* _$value)  { return (System::Array<float>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_vector,_$value); }
inline System::Array<float>* EnginePrototype::CSVector_inner1::_sm_vector$(System::Array<float>* _$value) { CHCKTHIS; return _sm_vector(_$value); }


inline float EnginePrototype::CSVector_inner1::_idx_g(s32 i){
    return _gm_vector$()->_idx_g$(i);
}

inline float EnginePrototype::CSVector_inner1::_idx_g$(s32 i) { CHCKTHIS; return _idx_g(i); }

/*virtual*/
bool EnginePrototype::CSVector_inner1::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSVector_inner1,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSVector_inner1::_processGC() {
    if (m_vector) { System::Memory::pushList(m_vector,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSVector_inner1::_releaseGC() {
    if (m_vector && !m_vector->isFreed()) { m_vector->_removeRef((System::__GCObject**)&m_vector); }
}
/*virtual*/
void EnginePrototype::CSVector_inner1::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_vector) {
      newPtr = (u8*)(&m_vector); oldPtr = newPtr - offset;
      m_vector->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CSRES'
//=============================

void EnginePrototype::CSRES::_ctor_CSRES() {
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpSceneGraph(s32* task)
{
    CKLBLuaLibRES_dumpSceneGraph(task);
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpRendering(bool detailed)
{
    CKLBLuaLibRES_dumpRendering(detailed);
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpAssets()
{
    CKLBLuaLibRES_dumpAssets();
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpDataSet()
{
    CKLBLuaLibRES_dumpDataSet();
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpTexturePacker(bool detailed)
{
    CKLBLuaLibRES_dumpTexturePacker(detailed);
}

/*static*/
void EnginePrototype::CSRES::_ext_CKLBLuaLibRES_dumpGeometryCost(bool detailed)
{
    CKLBLuaLibRES_dumpGeometryCost(detailed);
}

/*static*/
void EnginePrototype::CSRES::dumpSceneGraph(EnginePrototype::CKLBUITask* task)
{
    if (task != NULL)
    {
        _ext_CKLBLuaLibRES_dumpSceneGraph(task->_acc_gCppObject$());
    }
    else
    {
        _ext_CKLBLuaLibRES_dumpSceneGraph(System::IntPtr::Zero);
    }
}

/*static*/
void EnginePrototype::CSRES::dumpRendering(bool detailed)
{
    _ext_CKLBLuaLibRES_dumpRendering(detailed);
}

/*static*/
void EnginePrototype::CSRES::dumpAssets()
{
    _ext_CKLBLuaLibRES_dumpAssets();
}

/*static*/
void EnginePrototype::CSRES::dumpDataSet()
{
    _ext_CKLBLuaLibRES_dumpDataSet();
}

/*static*/
void EnginePrototype::CSRES::dumpTexturePacker(bool detailed)
{
    _ext_CKLBLuaLibRES_dumpTexturePacker(detailed);
}

/*static*/
void EnginePrototype::CSRES::dumpGeometryCost(bool detailed)
{
    _ext_CKLBLuaLibRES_dumpGeometryCost(detailed);
}

EnginePrototype::CSRES::CSRES() { _ctor_CSRES(); }



/*virtual*/
bool EnginePrototype::CSRES::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSRES,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSRES::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSRES::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSRES::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CSSound'
//=============================

void EnginePrototype::CSSound::_ctor_CSSound() {
}

/*static*/
s32* EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundOpen(s32* sndAsset,bool fBgm)
{
    return CKLBLuaLibSOUND_cmdSoundOpen(sndAsset,fBgm);
}

/*static*/
bool EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundSetBufSize(s32* pSnd,s32 level)
{
    return CKLBLuaLibSOUND_cmdSoundSetBufSize(pSnd,level);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundClose(s32* pSnd)
{
    CKLBLuaLibSOUND_cmdSoundClose(pSnd);
}

/*static*/
s32 EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_removeSoundAll()
{
    return CKLBLuaLibSOUND_removeSoundAll();
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundPlay(s32* pSnd,u32 fade_msec,float tgtVol,float globalVol)
{
    CKLBLuaLibSOUND_cmdSoundPlay(pSnd,fade_msec,tgtVol,globalVol);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundStop(s32* pSnd,u32 fade_msec,float tgtVol)
{
    CKLBLuaLibSOUND_cmdSoundStop(pSnd,fade_msec,tgtVol);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundVolume(s32* pSnd,float volume)
{
    CKLBLuaLibSOUND_cmdSoundVolume(pSnd,volume);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundPan(s32* pSnd,float pan)
{
    CKLBLuaLibSOUND_cmdSoundPan(pSnd,pan);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundPause(s32* pSnd)
{
    CKLBLuaLibSOUND_cmdSoundPause(pSnd);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundResume(s32* pSnd)
{
    CKLBLuaLibSOUND_cmdSoundResume(pSnd);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundSeek(s32* pSnd,s32 millisec)
{
    CKLBLuaLibSOUND_cmdSoundSeek(pSnd,millisec);
}

/*static*/
s32 EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundTell(s32* pSnd)
{
    return CKLBLuaLibSOUND_cmdSoundTell(pSnd);
}

/*static*/
s32 EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSoundState(s32* pSnd)
{
    return CKLBLuaLibSOUND_cmdSoundState(pSnd);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdVolumeBGM(float volume)
{
    CKLBLuaLibSOUND_cmdVolumeBGM(volume);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdVolumeSE(float volume)
{
    CKLBLuaLibSOUND_cmdVolumeSE(volume);
}

/*static*/
s32 EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdGetLength(s32* pSnd)
{
    return CKLBLuaLibSOUND_cmdGetLength(pSnd);
}

/*static*/
void EnginePrototype::CSSound::_ext_CKLBLuaLibSOUND_cmdSetFade(s32* pSnd,s32 millisec,float tgtVol)
{
    CKLBLuaLibSOUND_cmdSetFade(pSnd,millisec,tgtVol);
}

EnginePrototype::CSSound::CSSound(System::String* sound_asset,bool bgmMode) : EnginePrototype::GameObject(s_classID)
{
    _ctor_CSSound();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBLuaLibSOUND_cmdSoundOpen(System::__MarshallingUtils::NativeUtf8FromString(sound_asset),bgmMode);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

bool EnginePrototype::CSSound::setBufSize(s32 size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_bufSize$(size);
        return _ext_CKLBLuaLibSOUND_cmdSoundSetBufSize(EnginePrototype::GameObject::_acc_gCppObject$(),(s32)size);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CSSound::setBufSize$(s32 size) { CHCKTHIS; return setBufSize(size); }

/*virtual*/
void EnginePrototype::CSSound::clearInternals()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundClose(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CSSound::clearInternals$() { CHCKTHIS; return clearInternals(); }

/*static*/
void EnginePrototype::CSSound::closeAll()
{
    _ext_CKLBLuaLibSOUND_removeSoundAll();
}

void EnginePrototype::CSSound::play(u32 fade_msec,float tgtVol,float globalVol)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundPlay(EnginePrototype::GameObject::_acc_gCppObject$(),fade_msec,tgtVol,globalVol);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::play$(u32 fade_msec,float tgtVol,float globalVol) { CHCKTHIS; return play(fade_msec,tgtVol,globalVol); }

void EnginePrototype::CSSound::stop(u32 fade_msec,float tgtVol)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundStop(EnginePrototype::GameObject::_acc_gCppObject$(),fade_msec,tgtVol);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::stop$(u32 fade_msec,float tgtVol) { CHCKTHIS; return stop(fade_msec,tgtVol); }

void EnginePrototype::CSSound::pause()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundPause(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::pause$() { CHCKTHIS; return pause(); }

void EnginePrototype::CSSound::resume()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundResume(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::resume$() { CHCKTHIS; return resume(); }

void EnginePrototype::CSSound::seek(s32 milliseconds)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSoundSeek(EnginePrototype::GameObject::_acc_gCppObject$(),milliseconds);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::seek$(s32 milliseconds) { CHCKTHIS; return seek(milliseconds); }

s32 EnginePrototype::CSSound::tell()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibSOUND_cmdSoundTell(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CSSound::tell$() { CHCKTHIS; return tell(); }

s32 EnginePrototype::CSSound::state()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibSOUND_cmdSoundState(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CSSound::state$() { CHCKTHIS; return state(); }

void EnginePrototype::CSSound::setFade(s32 millisec,float tgtVol)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBLuaLibSOUND_cmdSetFade(EnginePrototype::GameObject::_acc_gCppObject$(),millisec,tgtVol);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CSSound::setFade$(s32 millisec,float tgtVol) { CHCKTHIS; return setFade(millisec,tgtVol); }

/*static*/
void EnginePrototype::CSSound::volumeBGM(float volume)
{
    _ext_CKLBLuaLibSOUND_cmdVolumeBGM(volume);
}

/*static*/
void EnginePrototype::CSSound::volumeSE(float volume)
{
    _ext_CKLBLuaLibSOUND_cmdVolumeSE(volume);
}

EnginePrototype::CSSound::CSSound() { _ctor_CSSound(); }



inline s32 EnginePrototype::CSSound::_acc_gBufSize(){
    return _gm_bufSize$();
}

inline s32 EnginePrototype::CSSound::_acc_gBufSize$() { CHCKTHIS; return _acc_gBufSize(); }

inline float EnginePrototype::CSSound::_acc_gVolume(){
    return _gm_volume$();
}

inline float EnginePrototype::CSSound::_acc_gVolume$() { CHCKTHIS; return _acc_gVolume(); }

inline float EnginePrototype::CSSound::_acc_sVolume(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_volume$(value);
        _ext_CKLBLuaLibSOUND_cmdSoundVolume(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CSSound::_acc_sVolume$(float value)		{ CHCKTHIS; return _acc_sVolume(value); }
inline float EnginePrototype::CSSound::_acc_gPan(){
    return _gm_pan$();
}

inline float EnginePrototype::CSSound::_acc_gPan$() { CHCKTHIS; return _acc_gPan(); }

inline float EnginePrototype::CSSound::_acc_sPan(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_pan$(value);
        _ext_CKLBLuaLibSOUND_cmdSoundPan(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CSSound::_acc_sPan$(float value)		{ CHCKTHIS; return _acc_sPan(value); }
inline s32 EnginePrototype::CSSound::_acc_gLength(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBLuaLibSOUND_cmdGetLength(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CSSound::_acc_gLength$() { CHCKTHIS; return _acc_gLength(); }

/*virtual*/
bool EnginePrototype::CSSound::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSSound,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CSSound::_processGC() {
    EnginePrototype::GameObject::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSSound::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

}
/*virtual*/
void EnginePrototype::CSSound::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

}

//=============================
// Implementation of 'CSSystem'
//=============================

void EnginePrototype::CSSystem::_ctor_CSSystem() {
}

/*static*/
void EnginePrototype::CSSystem::_ext_CKLBLuaEnv_cmdLogging(s32* msg)
{
    CKLBLuaEnv_cmdLogging(msg);
}

/*static*/
void EnginePrototype::CSSystem::_ext_CKLBLuaEnv_cmdExit()
{
    CKLBLuaEnv_cmdExit();
}

/*static*/
void EnginePrototype::CSSystem::_ext_CKLBLuaEnv_cmdSystemInfo(s32& width,s32& height)
{
    CKLBLuaEnv_cmdSystemInfo(&width,&height);
}

/*static*/
void EnginePrototype::CSSystem::_ext_CKLBLuaEnv_cmdSystemReboot()
{
    CKLBLuaEnv_cmdSystemReboot();
}

/*static*/
void EnginePrototype::CSSystem::logging(System::String* msg)
{
    _ext_CKLBLuaEnv_cmdLogging(System::__MarshallingUtils::NativeUtf8FromString(msg));
}

/*static*/
void EnginePrototype::CSSystem::exitGame()
{
    _ext_CKLBLuaEnv_cmdExit();
}

/*static*/
void EnginePrototype::CSSystem::getInfo(EnginePrototype::SystemInfo_inner2& sysInfos)
{
    s32 width = 0;
    s32 height = 0;
    _ext_CKLBLuaEnv_cmdSystemInfo(width,height);
    sysInfos._swidth$(width);
    sysInfos._sheight$(height);
}

/*static*/
void EnginePrototype::CSSystem::reboot()
{
    _ext_CKLBLuaEnv_cmdSystemReboot();
}

EnginePrototype::CSSystem::CSSystem() { _ctor_CSSystem(); }



/*virtual*/
bool EnginePrototype::CSSystem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSSystem,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSSystem::_processGC() {
    System::Object::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSSystem::_releaseGC() {
    System::Object::_releaseGC();

}
/*virtual*/
void EnginePrototype::CSSystem::_moveAlert(u32 offset) {
    System::Object::_moveAlert(offset);

}

//=============================
// Implementation of 'SystemInfo_inner2'
//=============================

void EnginePrototype::SystemInfo_inner2::_ctor_SystemInfo_inner2() {
}

EnginePrototype::SystemInfo_inner2::SystemInfo_inner2() { _ctor_SystemInfo_inner2(); }


inline u32 EnginePrototype::SystemInfo_inner2::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::SystemInfo_inner2::_releaseGC() {
}
inline void* EnginePrototype::SystemInfo_inner2::_RefSetValue(void* newStruct) {
    SystemInfo_inner2* pStruct = (SystemInfo_inner2*)newStruct;
    this->width = pStruct->width;
    this->height = pStruct->height;
    return newStruct;
}
inline void EnginePrototype::SystemInfo_inner2::_moveAlert(u32 offset) {
}
inline EnginePrototype::SystemInfo_inner2& EnginePrototype::SystemInfo_inner2::__registerByRef(EnginePrototype::SystemInfo_inner2& m) {
    return m;
}


//=============================
// Implementation of 'CSUI'
//=============================

void EnginePrototype::CSUI::_ctor_CSUI() {
}

/*static*/
void EnginePrototype::CSUI::_ext_CKLBLuaLibUI_calcPosition(float x,float y,float w,float h,u32 mask,float& out_rx,float& out_ry)
{
    CKLBLuaLibUI_calcPosition(x,y,w,h,mask,&out_rx,&out_ry);
}

/*static*/
void EnginePrototype::CSUI::calcPosition(float x,float y,float w,float h,s32 mask,float& out_rx,float& out_ry)
{
    _ext_CKLBLuaLibUI_calcPosition(x,y,w,h,(u32)mask,out_rx,out_ry);
}

EnginePrototype::CSUI::CSUI() { _ctor_CSUI(); }



/*virtual*/
bool EnginePrototype::CSUI::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CSUI,System::Object);
}

/*virtual*/
u32 EnginePrototype::CSUI::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CSUI::_releaseGC() {
}
/*virtual*/
void EnginePrototype::CSUI::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'CKLBAsyncLoader'
//=============================

void EnginePrototype::CKLBAsyncLoader::_ctor_CKLBAsyncLoader() {
}

/*static*/
s32* EnginePrototype::CKLBAsyncLoader::_ext_CKLBAsyncLoader_create(s32* pParentTask,System::Array<s32*>* assets,u32 count,u32 datasetID)
{
    return CKLBAsyncLoader_create(pParentTask,assets ? (s32**)assets->_getPArray() : NULL,count,datasetID);
}

/*static*/
u32 EnginePrototype::CKLBAsyncLoader::_ext_CKLBAsyncLoader_getProcessCount(s32* p)
{
    return CKLBAsyncLoader_getProcessCount(p);
}

/*static*/
u32 EnginePrototype::CKLBAsyncLoader::_ext_CKLBAsyncLoader_getTotalCount(s32* p)
{
    return CKLBAsyncLoader_getTotalCount(p);
}

EnginePrototype::CKLBAsyncLoader::CKLBAsyncLoader(EnginePrototype::CKLBTask* pParent,System::Array<System::String*>* assets,u32 datasetID,EnginePrototype::_Delegate_Base_CallBack_inner21* callback) : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBAsyncLoader();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBAsyncLoader_create(((pParent != NULL) ? pParent->_acc_gCppObject$() : System::IntPtr::Zero),System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(assets,assets->_acc_gLength$()),(u32)assets->_acc_gLength$(),datasetID);
    EnginePrototype::NativeManagement::intercepCppError();
    _sm_callback$(callback);
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBAsyncLoader::CKLBAsyncLoader() : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBAsyncLoader();
}

/*virtual*/
void EnginePrototype::CKLBAsyncLoader::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUU_inner11<CKLBAsyncLoader>(this,&CKLBAsyncLoader::callBackFunction),0);
}

inline void EnginePrototype::CKLBAsyncLoader::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBAsyncLoader::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner21*)anyDelegate);
}

inline void EnginePrototype::CKLBAsyncLoader::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBAsyncLoader::callBackFunction(u32 loaded,u32 total)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,loaded,total);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBAsyncLoader::callBackFunction$(u32 loaded,u32 total) { CHCKTHIS; return callBackFunction(loaded,total); }

inline EnginePrototype::_Delegate_Base_CallBack_inner21* EnginePrototype::CKLBAsyncLoader::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner21* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner21*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner21* EnginePrototype::CKLBAsyncLoader::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner21* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBAsyncLoader::_acc_gProcessCount(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBAsyncLoader_getProcessCount(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBAsyncLoader::_acc_gProcessCount$() { CHCKTHIS; return _acc_gProcessCount(); }

inline u32 EnginePrototype::CKLBAsyncLoader::_acc_gTotalCount(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBAsyncLoader_getTotalCount(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBAsyncLoader::_acc_gTotalCount$() { CHCKTHIS; return _acc_gTotalCount(); }

/*virtual*/
bool EnginePrototype::CKLBAsyncLoader::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBAsyncLoader,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBAsyncLoader::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBAsyncLoader::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBAsyncLoader::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBGenericTask'
//=============================

void EnginePrototype::CKLBGenericTask::_ctor_CKLBGenericTask() {
}

/*static*/
s32* EnginePrototype::CKLBGenericTask::_ext_CKLBGenericTask_create(s32* pParent,u32 phase)
{
    return CKLBGenericTask_create(pParent,phase);
}

EnginePrototype::CKLBGenericTask::CKLBGenericTask(EnginePrototype::CKLBTask* parent,s32 phase,EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* executeCallBack,EnginePrototype::_Delegate_Base_DieCallBack_inner23* dieCallBack) : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBGenericTask();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBGenericTask_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),(u32)phase);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_executeCallBack$(executeCallBack);
    _sm_dieCallBack$(dieCallBack);
}

EnginePrototype::CKLBGenericTask::CKLBGenericTask() : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBGenericTask();
}

/*virtual*/
void EnginePrototype::CKLBGenericTask::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerU_inner10<CKLBGenericTask>(this,&CKLBGenericTask::executeCallBackFunction),0);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerV_inner0<CKLBGenericTask>(this,&CKLBGenericTask::dieCallBackFunction),1);
}

inline void EnginePrototype::CKLBGenericTask::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBGenericTask::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr55Obj))
    {
        _sm_executeCallBack$((EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr56Obj))
    {
        _sm_dieCallBack$((EnginePrototype::_Delegate_Base_DieCallBack_inner23*)anyDelegate);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr57Obj));
    }
}

inline void EnginePrototype::CKLBGenericTask::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBGenericTask::executeCallBackFunction(u32 deltaTime)
{
    if (_gm_executeCallBack$() != NULL)
    {
        _gm_executeCallBack$()->call$(this,deltaTime);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBGenericTask::executeCallBackFunction$(u32 deltaTime) { CHCKTHIS; return executeCallBackFunction(deltaTime); }

/*virtual*/
void EnginePrototype::CKLBGenericTask::dieCallBackFunction()
{
    if (_gm_dieCallBack$() != NULL)
    {
        _gm_dieCallBack$()->call$(this);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBGenericTask::dieCallBackFunction$() { CHCKTHIS; return dieCallBackFunction(); }

inline EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* EnginePrototype::CKLBGenericTask::_sm_executeCallBack(EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _$value)  { return (EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_executeCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* EnginePrototype::CKLBGenericTask::_sm_executeCallBack$(EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _$value) { CHCKTHIS; return _sm_executeCallBack(_$value); }
inline EnginePrototype::_Delegate_Base_DieCallBack_inner23* EnginePrototype::CKLBGenericTask::_sm_dieCallBack(EnginePrototype::_Delegate_Base_DieCallBack_inner23* _$value)  { return (EnginePrototype::_Delegate_Base_DieCallBack_inner23*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_dieCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_DieCallBack_inner23* EnginePrototype::CKLBGenericTask::_sm_dieCallBack$(EnginePrototype::_Delegate_Base_DieCallBack_inner23* _$value) { CHCKTHIS; return _sm_dieCallBack(_$value); }


/*virtual*/
bool EnginePrototype::CKLBGenericTask::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBGenericTask,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBGenericTask::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    if (m_executeCallBack) { System::Memory::pushList(m_executeCallBack,0); }
    if (m_dieCallBack) { System::Memory::pushList(m_dieCallBack,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBGenericTask::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

    if (m_executeCallBack && !m_executeCallBack->isFreed()) { m_executeCallBack->_removeRef((System::__GCObject**)&m_executeCallBack); }
    if (m_dieCallBack && !m_dieCallBack->isFreed()) { m_dieCallBack->_removeRef((System::__GCObject**)&m_dieCallBack); }
}
/*virtual*/
void EnginePrototype::CKLBGenericTask::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_executeCallBack) {
      newPtr = (u8*)(&m_executeCallBack); oldPtr = newPtr - offset;
      m_executeCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_dieCallBack) {
      newPtr = (u8*)(&m_dieCallBack); oldPtr = newPtr - offset;
      m_dieCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBIntervalTimer'
//=============================

void EnginePrototype::CKLBIntervalTimer::_ctor_CKLBIntervalTimer() {
}

/*static*/
s32* EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_create(s32* pParent,u32 interval,bool repeat,u8 mode)
{
    return CKLBIntervalTimer_create(pParent,interval,repeat,mode);
}

/*static*/
u32 EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_getTimerID(s32* p)
{
    return CKLBIntervalTimer_getTimerID(p);
}

/*static*/
void EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_setTimerID(s32* p,u32 ID)
{
    CKLBIntervalTimer_setTimerID(p,ID);
}

/*static*/
bool EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_getRepeat(s32* p)
{
    return CKLBIntervalTimer_getRepeat(p);
}

/*static*/
void EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_setRepeat(s32* p,bool boolean)
{
    CKLBIntervalTimer_setRepeat(p,boolean);
}

/*static*/
u32 EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_getInterval(s32* p)
{
    return CKLBIntervalTimer_getInterval(p);
}

/*static*/
void EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_setInterval(s32* p,u32 interval)
{
    CKLBIntervalTimer_setInterval(p,interval);
}

/*static*/
u8 EnginePrototype::CKLBIntervalTimer::_ext_CKLBIntervalTimer_getMode(s32* p)
{
    return CKLBIntervalTimer_getMode(p);
}

EnginePrototype::CKLBIntervalTimer::CKLBIntervalTimer(EnginePrototype::CKLBTask* parent,u32 interval,EnginePrototype::_Delegate_Base_CallBack_inner24* callback,bool repeat,s32 mode) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBIntervalTimer();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBIntervalTimer_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),interval,repeat,(u8)mode);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBIntervalTimer::CKLBIntervalTimer() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBIntervalTimer();
}

/*virtual*/
void EnginePrototype::CKLBIntervalTimer::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerV_inner0<CKLBIntervalTimer>(this,&CKLBIntervalTimer::callBackFunction),0);
}

inline void EnginePrototype::CKLBIntervalTimer::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBIntervalTimer::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner24*)anyDelegate);
}

inline void EnginePrototype::CKLBIntervalTimer::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBIntervalTimer::callBackFunction()
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBIntervalTimer::callBackFunction$() { CHCKTHIS; return callBackFunction(); }

inline EnginePrototype::_Delegate_Base_CallBack_inner24* EnginePrototype::CKLBIntervalTimer::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner24* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner24*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner24* EnginePrototype::CKLBIntervalTimer::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner24* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline s32 EnginePrototype::CKLBIntervalTimer::_acc_gMode(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return (ETIMERMODE)_ext_CKLBIntervalTimer_getMode(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBIntervalTimer::_acc_gMode$() { CHCKTHIS; return _acc_gMode(); }

inline u32 EnginePrototype::CKLBIntervalTimer::_acc_gInterval(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBIntervalTimer_getInterval(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBIntervalTimer::_acc_gInterval$() { CHCKTHIS; return _acc_gInterval(); }

inline u32 EnginePrototype::CKLBIntervalTimer::_acc_sInterval(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBIntervalTimer_setInterval(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBIntervalTimer::_acc_sInterval$(u32 value)		{ CHCKTHIS; return _acc_sInterval(value); }
inline bool EnginePrototype::CKLBIntervalTimer::_acc_gRepeat(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBIntervalTimer_getRepeat(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBIntervalTimer::_acc_gRepeat$() { CHCKTHIS; return _acc_gRepeat(); }

inline bool EnginePrototype::CKLBIntervalTimer::_acc_sRepeat(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBIntervalTimer_setRepeat(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBIntervalTimer::_acc_sRepeat$(bool value)		{ CHCKTHIS; return _acc_sRepeat(value); }
/*virtual*/
bool EnginePrototype::CKLBIntervalTimer::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBIntervalTimer,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBIntervalTimer::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBIntervalTimer::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBIntervalTimer::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBNetAPI'
//=============================

void EnginePrototype::CKLBNetAPI::_ctor_CKLBNetAPI() {
}

/*static*/
s32* EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_create(s32* pParent,s32* apiurl,s32* client_version,s32* consumerKey,s32* applicationId,u32 sessionMax,s32* region)
{
    return CKLBNetAPI_create(pParent,apiurl,client_version,consumerKey,applicationId,sessionMax,region);
}

/*static*/
bool EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_startUp(s32* p,s32* loginID,s32* password,s32* invite,u32 timeout,u32& session)
{
    return CKLBNetAPI_startUp(p,loginID,password,invite,timeout,&session);
}

/*static*/
bool EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_login(s32* p,s32* loginID,s32* password,u32 timeout,u32& session)
{
    return CKLBNetAPI_login(p,loginID,password,timeout,&session);
}

/*static*/
bool EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_cancel(s32* p,u32 uniq)
{
    return CKLBNetAPI_cancel(p,uniq);
}

/*static*/
void EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_cancelAll(s32* p)
{
    CKLBNetAPI_cancelAll(p);
}

/*static*/
bool EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_watchMaintenance(s32* p,u32 timeout,u32& session)
{
    return CKLBNetAPI_watchMaintenance(p,timeout,&session);
}

/*static*/
void EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_debugHdr(s32* p,bool debugflag)
{
    CKLBNetAPI_debugHdr(p,debugflag);
}

/*static*/
void EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_genCmdNumID(s32* p,s32* body,s32 serial,s32* buf)
{
    CKLBNetAPI_genCmdNumID(p,body,serial,buf);
}

/*static*/
bool EnginePrototype::CKLBNetAPI::_ext_CKLBNetAPI_sendHTTP(s32* p,s32* apiURL,s32* json,u32 timeout,bool passVersionCheck,u32& session)
{
    return CKLBNetAPI_sendHTTP(p,apiURL,json,timeout,passVersionCheck,&session);
}

EnginePrototype::CKLBNetAPI::CKLBNetAPI(EnginePrototype::CKLBTask* parent,System::String* apiUrl,System::String* clientVersion,System::String* consumerKey,System::String* applicationID,u32 sessionMax,System::String* region,EnginePrototype::_Delegate_Base_CallBack_inner25* callback,EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* versionUpCallback) : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBNetAPI();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBNetAPI_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),System::__MarshallingUtils::NativeUtf8FromString(apiUrl),System::__MarshallingUtils::NativeUtf8FromString(clientVersion),System::__MarshallingUtils::NativeUtf8FromString(consumerKey),System::__MarshallingUtils::NativeUtf8FromString(applicationID),sessionMax,System::__MarshallingUtils::NativeUtf8FromString(region));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
    _sm_callbackVersionUp$(versionUpCallback);
}

EnginePrototype::CKLBNetAPI::CKLBNetAPI() : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBNetAPI();
}

/*virtual*/
void EnginePrototype::CKLBNetAPI::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerIIIP_retB_inner19<CKLBNetAPI>(this,&CKLBNetAPI::callBackFunction),0);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSS_inner7<CKLBNetAPI>(this,&CKLBNetAPI::callBackVersionUpFunction),1);
}

inline void EnginePrototype::CKLBNetAPI::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBNetAPI::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr61Obj))
    {
        _sm_callbackVersionUp$((EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26*)anyDelegate);
    }
    else
    {
        _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner25*)anyDelegate);
    }
}

inline void EnginePrototype::CKLBNetAPI::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
bool EnginePrototype::CKLBNetAPI::callBackFunction(s32 uniq,s32 msg,s32 status,s32* pRoot)
{
    if (_gm_callback$() != NULL)
    {
        return _gm_callback$()->call$(this,uniq,(ESTATUS)msg,status,pRoot);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::callBackFunction$(s32 uniq,s32 msg,s32 status,s32* pRoot) { CHCKTHIS; return callBackFunction(uniq,msg,status,pRoot); }

/*virtual*/
void EnginePrototype::CKLBNetAPI::callBackVersionUpFunction(s32* clientVer,s32* serverVer)
{
    if (_gm_callbackVersionUp$() != NULL)
    {
        _gm_callbackVersionUp$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(clientVer),System::__MarshallingUtils::StringFromNativeUtf8(serverVer));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBNetAPI::callBackVersionUpFunction$(s32* clientVer,s32* serverVer) { CHCKTHIS; return callBackVersionUpFunction(clientVer,serverVer); }

bool EnginePrototype::CKLBNetAPI::startUp(u32& session,System::String* loginID,System::String* password,System::String* invite,u32 timeout)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        bool res = _ext_CKLBNetAPI_startUp(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(loginID),System::__MarshallingUtils::NativeUtf8FromString(password),System::__MarshallingUtils::NativeUtf8FromString(invite),timeout,session);
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::startUp$(u32& session,System::String* loginID,System::String* password,System::String* invite,u32 timeout) { CHCKTHIS; return startUp(session,loginID,password,invite,timeout); }

bool EnginePrototype::CKLBNetAPI::login(u32& session,System::String* loginID,System::String* password,u32 timeout)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        bool res = _ext_CKLBNetAPI_login(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(loginID),System::__MarshallingUtils::NativeUtf8FromString(password),timeout,session);
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::login$(u32& session,System::String* loginID,System::String* password,u32 timeout) { CHCKTHIS; return login(session,loginID,password,timeout); }

bool EnginePrototype::CKLBNetAPI::cancel(u32 session)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBNetAPI_cancel(EnginePrototype::GameObject::_acc_gCppObject$(),session);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::cancel$(u32 session) { CHCKTHIS; return cancel(session); }

bool EnginePrototype::CKLBNetAPI::send(u32& session,System::String* json,System::String* apiURL,u32 timeout,bool pass_version_check)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBNetAPI_sendHTTP(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(apiURL),System::__MarshallingUtils::NativeUtf8FromString(json),timeout,pass_version_check,session);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::send$(u32& session,System::String* json,System::String* apiURL,u32 timeout,bool pass_version_check) { CHCKTHIS; return send(session,json,apiURL,timeout,pass_version_check); }

void EnginePrototype::CKLBNetAPI::cancelAll()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBNetAPI_cancelAll(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBNetAPI::cancelAll$() { CHCKTHIS; return cancelAll(); }

bool EnginePrototype::CKLBNetAPI::watchMaintenance(u32& session,u32 timeout)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBNetAPI_watchMaintenance(EnginePrototype::GameObject::_acc_gCppObject$(),timeout,session);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBNetAPI::watchMaintenance$(u32& session,u32 timeout) { CHCKTHIS; return watchMaintenance(session,timeout); }

void EnginePrototype::CKLBNetAPI::debugHdr(bool debugflag)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBNetAPI_debugHdr(EnginePrototype::GameObject::_acc_gCppObject$(),debugflag);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBNetAPI::debugHdr$(bool debugflag) { CHCKTHIS; return debugHdr(debugflag); }

void EnginePrototype::CKLBNetAPI::_ref_genCmdNumID(System::String*& numID,System::String* body,s32 serial)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        s32* intPtr = System::__MarshallingUtils::NativeUtf8FromString(CS_NEW System::String('0',512));
        _ext_CKLBNetAPI_genCmdNumID(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(body),serial,intPtr);
        numID = System::__MarshallingUtils::StringFromNativeUtf8(intPtr);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBNetAPI::genCmdNumID$(System::String*& numID,System::String* body,s32 serial) { CHCKTHIS; return genCmdNumID(numID,body,serial); }

inline void EnginePrototype::CKLBNetAPI::genCmdNumID(System::String*& numID,System::String* body,s32 serial) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); _ref_genCmdNumID(numID,body,serial); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); }

inline EnginePrototype::_Delegate_Base_CallBack_inner25* EnginePrototype::CKLBNetAPI::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner25* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner25*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner25* EnginePrototype::CKLBNetAPI::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner25* _$value) { CHCKTHIS; return _sm_callback(_$value); }
inline EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* EnginePrototype::CKLBNetAPI::_sm_callbackVersionUp(EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _$value)  { return (EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callbackVersionUp,_$value); }
inline EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* EnginePrototype::CKLBNetAPI::_sm_callbackVersionUp$(EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _$value) { CHCKTHIS; return _sm_callbackVersionUp(_$value); }


/*virtual*/
bool EnginePrototype::CKLBNetAPI::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBNetAPI,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBNetAPI::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    if (m_callbackVersionUp) { System::Memory::pushList(m_callbackVersionUp,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBNetAPI::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
    if (m_callbackVersionUp && !m_callbackVersionUp->isFreed()) { m_callbackVersionUp->_removeRef((System::__GCObject**)&m_callbackVersionUp); }
}
/*virtual*/
void EnginePrototype::CKLBNetAPI::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_callbackVersionUp) {
      newPtr = (u8*)(&m_callbackVersionUp); oldPtr = newPtr - offset;
      m_callbackVersionUp->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBStoreService'
//=============================

void EnginePrototype::CKLBStoreService::_ctor_CKLBStoreService() {
}

/*static*/
s32* EnginePrototype::CKLBStoreService::_ext_CKLBStoreService_create()
{
    return CKLBStoreService_create();
}

/*static*/
void EnginePrototype::CKLBStoreService::_ext_CKLBStoreService_buyItems(s32* p,s32* item)
{
    CKLBStoreService_buyItems(p,item);
}

/*static*/
void EnginePrototype::CKLBStoreService::_ext_CKLBStoreService_getProducts(s32* p,s32* json,bool currency)
{
    CKLBStoreService_getProducts(p,json,currency);
}

EnginePrototype::CKLBStoreService::CKLBStoreService(EnginePrototype::_Delegate_Base_CallBack_inner27* callback) : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBStoreService();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBStoreService_create();
    EnginePrototype::NativeManagement::intercepCppError();
    _sm_callback$(callback);
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBStoreService::CKLBStoreService() : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBStoreService();
}

/*virtual*/
void EnginePrototype::CKLBStoreService::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUSS_inner9<CKLBStoreService>(this,&CKLBStoreService::callBackFunction),0);
}

inline void EnginePrototype::CKLBStoreService::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBStoreService::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner27*)anyDelegate);
}

inline void EnginePrototype::CKLBStoreService::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBStoreService::callBackFunction(u32 type,s32* itemID,s32* param)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,(EnginePrototype::IClientRequest::EVENT_TYPE)type,System::__MarshallingUtils::StringFromNativeUtf8(itemID),System::__MarshallingUtils::StringFromNativeUtf8(param));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBStoreService::callBackFunction$(u32 type,s32* itemID,s32* param) { CHCKTHIS; return callBackFunction(type,itemID,param); }

void EnginePrototype::CKLBStoreService::buyItems(System::String* item)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBStoreService_buyItems(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(item));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBStoreService::buyItems$(System::String* item) { CHCKTHIS; return buyItems(item); }

void EnginePrototype::CKLBStoreService::getProducts(System::String* json,bool currency)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBStoreService_getProducts(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(json),currency);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBStoreService::getProducts$(System::String* json,bool currency) { CHCKTHIS; return getProducts(json,currency); }

inline EnginePrototype::_Delegate_Base_CallBack_inner27* EnginePrototype::CKLBStoreService::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner27* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner27*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner27* EnginePrototype::CKLBStoreService::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner27* _$value) { CHCKTHIS; return _sm_callback(_$value); }


/*virtual*/
bool EnginePrototype::CKLBStoreService::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBStoreService,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBStoreService::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBStoreService::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBStoreService::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBTask'
//=============================

void EnginePrototype::CKLBTask::_ctor_CKLBTask() {
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_kill(s32* task)
{
    Task_kill(task);
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_setStageTask(s32* task)
{
    Task_setStageTask(task);
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_clearStageTask()
{
    Task_clearStageTask();
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_setPause(s32* task,bool bPause,bool bRecursive)
{
    Task_setPause(task,bPause,bRecursive);
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_setManagerPause(bool bPause)
{
    Task_setManagerPause(bPause);
}

/*static*/
void EnginePrototype::CKLBTask::_ext_Task_interposeTimer(s32* pTask,s32* pTimer)
{
    Task_interposeTimer(pTask,pTimer);
}

/*static*/
bool EnginePrototype::CKLBTask::_ext_Task_isKill(s32* task)
{
    return Task_isKill(task);
}

EnginePrototype::CKLBTask::CKLBTask(u32 classID) : EnginePrototype::GameObject(classID)
{
    _ctor_CKLBTask();
    _sm_timer$(NULL);
}

/*virtual*/
void EnginePrototype::CKLBTask::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerV_inner0<CKLBTask>(this,&CKLBTask::onDieCallBackFunction),5);
}

inline void EnginePrototype::CKLBTask::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

void EnginePrototype::CKLBTask::setOnDieCallBack(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* anyDelegate)
{
    _sm_callback$(anyDelegate);
}

inline void EnginePrototype::CKLBTask::setOnDieCallBack$(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* anyDelegate) { CHCKTHIS; return setOnDieCallBack(anyDelegate); }

/*virtual*/
void EnginePrototype::CKLBTask::onDieCallBackFunction()
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this);
    }
}

inline void EnginePrototype::CKLBTask::onDieCallBackFunction$() { CHCKTHIS; return onDieCallBackFunction(); }

void EnginePrototype::CKLBTask::kill()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        onDieCallBackFunction$();
        s32* cppObject = EnginePrototype::GameObject::_acc_gCppObject$();
        EnginePrototype::GameObject::unbind$();
        _ext_Task_kill(cppObject);
    }
}

inline void EnginePrototype::CKLBTask::kill$() { CHCKTHIS; return kill(); }

bool EnginePrototype::CKLBTask::isKill()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_Task_isKill(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    return true;
}

inline bool EnginePrototype::CKLBTask::isKill$() { CHCKTHIS; return isKill(); }

/*virtual*/
void EnginePrototype::CKLBTask::Dispose()
{
    kill$();
    EnginePrototype::GameObject::Dispose();
}

inline void EnginePrototype::CKLBTask::Dispose$() { CHCKTHIS; return Dispose(); }

void EnginePrototype::CKLBTask::setPause(bool bPause,bool bRecursive)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_Task_setPause(EnginePrototype::GameObject::_acc_gCppObject$(),bPause,bRecursive);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBTask::setPause$(bool bPause,bool bRecursive) { CHCKTHIS; return setPause(bPause,bRecursive); }

void EnginePrototype::CKLBTask::setLifeTime(s32 mode,u32 time)
{
    if (_gm_timer$() == NULL)
    {
        EnginePrototype::_Delegate_Base_CallBack_inner24* cb = CS_NEW EnginePrototype::_DelegateI_CallBack_inner24<_anon_0>(CS_NEW _anon_0(this,mode,time), &_anon_0::_delegate);
        _sm_timer$(CS_NEW EnginePrototype::CKLBIntervalTimer((EnginePrototype::CKLBTask*)NULL,time,cb,false,mode));
        _ext_Task_interposeTimer(EnginePrototype::GameObject::_acc_gCppObject$(),_gm_timer$()->_acc_gCppObject$());
    }
    else
    {
        _gm_timer$()->_acc_sInterval$(time);
    }
}

inline void EnginePrototype::CKLBTask::setLifeTime$(s32 mode,u32 time) { CHCKTHIS; return setLifeTime(mode,time); }

void EnginePrototype::CKLBTask::stageOnly()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_Task_setStageTask(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBTask::stageOnly$() { CHCKTHIS; return stageOnly(); }

/*static*/
void EnginePrototype::CKLBTask::clearStage()
{
    _ext_Task_clearStageTask();
}

/*static*/
void EnginePrototype::CKLBTask::setManagerPause(bool bPause)
{
    _ext_Task_setManagerPause(bPause);
}

EnginePrototype::CKLBTask::CKLBTask() { _ctor_CKLBTask(); }

inline EnginePrototype::_Delegate_Base_onDieCallBack_inner28* EnginePrototype::CKLBTask::_sm_callback(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _$value)  { return (EnginePrototype::_Delegate_Base_onDieCallBack_inner28*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_onDieCallBack_inner28* EnginePrototype::CKLBTask::_sm_callback$(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _$value) { CHCKTHIS; return _sm_callback(_$value); }
inline EnginePrototype::CKLBIntervalTimer* EnginePrototype::CKLBTask::_sm_timer(EnginePrototype::CKLBIntervalTimer* _$value)  { return (EnginePrototype::CKLBIntervalTimer*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_timer,_$value); }
inline EnginePrototype::CKLBIntervalTimer* EnginePrototype::CKLBTask::_sm_timer$(EnginePrototype::CKLBIntervalTimer* _$value) { CHCKTHIS; return _sm_timer(_$value); }


/*virtual*/
bool EnginePrototype::CKLBTask::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBTask,EnginePrototype::GameObject);
}

/*virtual*/
u32 EnginePrototype::CKLBTask::_processGC() {
    EnginePrototype::GameObject::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    if (m_timer) { System::Memory::pushList(m_timer,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBTask::_releaseGC() {
    EnginePrototype::GameObject::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
    if (m_timer && !m_timer->isFreed()) { m_timer->_removeRef((System::__GCObject**)&m_timer); }
}
/*virtual*/
void EnginePrototype::CKLBTask::_moveAlert(u32 offset) {
    EnginePrototype::GameObject::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_timer) {
      newPtr = (u8*)(&m_timer); oldPtr = newPtr - offset;
      m_timer->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}
void EnginePrototype::CKLBTask::_anon_0::_ctor__anon_0() {
}

EnginePrototype::CKLBTask::_anon_0::_anon_0(EnginePrototype::CKLBTask* _this__,s32 mode,u32 time)
{
    _ctor__anon_0();
    _s_this__(_this__);
    mode = mode;
    time = time;
}

void EnginePrototype::CKLBTask::_anon_0::_delegate(EnginePrototype::CKLBIntervalTimer* caller)
{
}

inline void EnginePrototype::CKLBTask::_anon_0::_delegate$(EnginePrototype::CKLBIntervalTimer* caller) { CHCKTHIS; return _delegate(caller); }

EnginePrototype::CKLBTask::_anon_0::_anon_0() { _ctor__anon_0(); }

inline EnginePrototype::CKLBTask* EnginePrototype::CKLBTask::_anon_0::_s_this__(EnginePrototype::CKLBTask* _$value)  { return (EnginePrototype::CKLBTask*)System::__GCObject::_RefSetValue((System::__GCObject**)&_this__,_$value); }
inline EnginePrototype::CKLBTask* EnginePrototype::CKLBTask::_anon_0::_s_this__$(EnginePrototype::CKLBTask* _$value) { CHCKTHIS; return _s_this__(_$value); }


/*virtual*/
bool EnginePrototype::CKLBTask::_anon_0::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(_anon_0,System::Object);
}

/*virtual*/
u32 EnginePrototype::CKLBTask::_anon_0::_processGC() {
    if (_this__) { System::Memory::pushList(_this__,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBTask::_anon_0::_releaseGC() {
    if (_this__ && !_this__->isFreed()) { _this__->_removeRef((System::__GCObject**)&_this__); }
}
/*virtual*/
void EnginePrototype::CKLBTask::_anon_0::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (_this__) {
      newPtr = (u8*)(&_this__); oldPtr = newPtr - offset;
      _this__->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUICanvas'
//=============================

void EnginePrototype::CKLBUICanvas::_ctor_CKLBUICanvas() {
}

/*static*/
s32* EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_create(s32* pParent,u32 order,float x,float y,u32 vertexMax,u32 indexMax)
{
    return CKLBUICanvas_create(pParent,order,x,y,vertexMax,indexMax);
}

/*static*/
u32 EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_getOrder(s32* p)
{
    return CKLBUICanvas_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_setOrder(s32* p,u32 order)
{
    CKLBUICanvas_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_getIdxMax(s32* p)
{
    return CKLBUICanvas_getIdxMax(p);
}

/*static*/
bool EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_addResource(s32* p,s32* asset)
{
    return CKLBUICanvas_addResource(p,asset);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_setFreeze(s32* p,bool freeze)
{
    CKLBUICanvas_setFreeze(p,freeze);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_drawImage(s32* p,float x,float y,u32 idx,u32 color)
{
    CKLBUICanvas_drawImage(p,x,y,idx,color);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_drawImageScale(s32* p,float x,float y,float scale,u32 idx,u32 color)
{
    CKLBUICanvas_drawImageScale(p,x,y,scale,idx,color);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_fillRect(s32* p,float x,float y,float w,float h,u32 color)
{
    CKLBUICanvas_fillRect(p,x,y,w,h,color);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_startDynamicSection(s32* p,u32 idx)
{
    CKLBUICanvas_startDynamicSection(p,idx);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_endDynamicSection(s32* p,u32 idx)
{
    CKLBUICanvas_endDynamicSection(p,idx);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_dynamicSectionTranslate(s32* p,u32 idx,float deltaX,float deltaY)
{
    CKLBUICanvas_dynamicSectionTranslate(p,idx,deltaX,deltaY);
}

/*static*/
void EnginePrototype::CKLBUICanvas::_ext_CKLBUICanvas_dynamicSectionColor(s32* p,u32 idx,u32 color)
{
    CKLBUICanvas_dynamicSectionColor(p,idx,color);
}

EnginePrototype::CKLBUICanvas::CKLBUICanvas(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 vertexMax,u32 indexMax,EnginePrototype::_Delegate_Base_CallBack_inner29* onDrawCallBack) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUICanvas();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUICanvas_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,vertexMax,indexMax);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(onDrawCallBack);
}

EnginePrototype::CKLBUICanvas::CKLBUICanvas() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUICanvas();
}

/*virtual*/
void EnginePrototype::CKLBUICanvas::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerV_inner0<CKLBUICanvas>(this,&CKLBUICanvas::callBackFunction),0);
}

inline void EnginePrototype::CKLBUICanvas::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUICanvas::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner29*)anyDelegate);
}

inline void EnginePrototype::CKLBUICanvas::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUICanvas::callBackFunction()
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::callBackFunction$() { CHCKTHIS; return callBackFunction(); }

bool EnginePrototype::CKLBUICanvas::addResource(System::String* asset)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        bool res = _ext_CKLBUICanvas_addResource(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(asset));
        EnginePrototype::NativeManagement::intercepCppError();
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUICanvas::addResource$(System::String* asset) { CHCKTHIS; return addResource(asset); }

void EnginePrototype::CKLBUICanvas::drawImage(float x,float y,u32 idx,u32 color)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_drawImage(EnginePrototype::GameObject::_acc_gCppObject$(),x,y,idx,color);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::drawImage$(float x,float y,u32 idx,u32 color) { CHCKTHIS; return drawImage(x,y,idx,color); }

void EnginePrototype::CKLBUICanvas::drawImageScale(float x,float y,float scale,u32 idx,u32 color)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_drawImageScale(EnginePrototype::GameObject::_acc_gCppObject$(),x,y,scale,idx,color);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::drawImageScale$(float x,float y,float scale,u32 idx,u32 color) { CHCKTHIS; return drawImageScale(x,y,scale,idx,color); }

void EnginePrototype::CKLBUICanvas::fillRect(float x,float y,float w,float h,u32 color)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_fillRect(EnginePrototype::GameObject::_acc_gCppObject$(),x,y,w,h,color);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::fillRect$(float x,float y,float w,float h,u32 color) { CHCKTHIS; return fillRect(x,y,w,h,color); }

void EnginePrototype::CKLBUICanvas::startDynamicSection(u32 idx)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_startDynamicSection(EnginePrototype::GameObject::_acc_gCppObject$(),idx);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::startDynamicSection$(u32 idx) { CHCKTHIS; return startDynamicSection(idx); }

void EnginePrototype::CKLBUICanvas::endDynamicSection(u32 idx)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_endDynamicSection(EnginePrototype::GameObject::_acc_gCppObject$(),idx);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::endDynamicSection$(u32 idx) { CHCKTHIS; return endDynamicSection(idx); }

void EnginePrototype::CKLBUICanvas::dynamicSectionTranslate(u32 idx,float deltaX,float deltaY)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_dynamicSectionTranslate(EnginePrototype::GameObject::_acc_gCppObject$(),idx,deltaX,deltaY);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::dynamicSectionTranslate$(u32 idx,float deltaX,float deltaY) { CHCKTHIS; return dynamicSectionTranslate(idx,deltaX,deltaY); }

void EnginePrototype::CKLBUICanvas::dynamicSectionColor(u32 idx,u32 color)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_dynamicSectionColor(EnginePrototype::GameObject::_acc_gCppObject$(),idx,color);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUICanvas::dynamicSectionColor$(u32 idx,u32 color) { CHCKTHIS; return dynamicSectionColor(idx,color); }

inline EnginePrototype::_Delegate_Base_CallBack_inner29* EnginePrototype::CKLBUICanvas::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner29* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner29*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner29* EnginePrototype::CKLBUICanvas::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner29* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUICanvas::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUICanvas_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUICanvas::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUICanvas::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUICanvas::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUICanvas::_acc_gIdxMax(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUICanvas_getIdxMax(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUICanvas::_acc_gIdxMax$() { CHCKTHIS; return _acc_gIdxMax(); }

inline bool EnginePrototype::CKLBUICanvas::_acc_sFreeze(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUICanvas_setFreeze(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUICanvas::_acc_sFreeze$(bool value)		{ CHCKTHIS; return _acc_sFreeze(value); }
/*virtual*/
bool EnginePrototype::CKLBUICanvas::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUICanvas,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUICanvas::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUICanvas::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUICanvas::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIClip'
//=============================

void EnginePrototype::CKLBUIClip::_ctor_CKLBUIClip() {
}

/*static*/
s32* EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_create(s32* pParent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight)
{
    return CKLBUIClip_create(pParent,baseOrder,maxOrder,x,y,clipWidth,clipHeight);
}

/*static*/
u32 EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_getOrder(s32* p)
{
    return CKLBUIClip_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setOrder(s32* p,u32 order)
{
    CKLBUIClip_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_getMaxOdr(s32* p)
{
    return CKLBUIClip_getMaxOdr(p);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setMaxOdr(s32* p,u32 maxodr)
{
    CKLBUIClip_setMaxOdr(p,maxodr);
}

/*static*/
float EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_getWidth(s32* p)
{
    return CKLBUIClip_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setWidth(s32* p,float width)
{
    CKLBUIClip_setWidth(p,width);
}

/*static*/
float EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_getHeight(s32* p)
{
    return CKLBUIClip_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setHeight(s32* p,float height)
{
    CKLBUIClip_setHeight(p,height);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setPosition(s32* p,float x,float y)
{
    CKLBUIClip_setPosition(p,x,y);
}

/*static*/
void EnginePrototype::CKLBUIClip::_ext_CKLBUIClip_setSize(s32* p,float width,float height)
{
    CKLBUIClip_setSize(p,width,height);
}

EnginePrototype::CKLBUIClip::CKLBUIClip(EnginePrototype::CKLBUITask* parent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIClip();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIClip_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),baseOrder,maxOrder,x,y,clipWidth,clipHeight);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIClip::CKLBUIClip() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIClip();
}

void EnginePrototype::CKLBUIClip::getSize(EnginePrototype::FSize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIClip_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIClip_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIClip::getSize$(EnginePrototype::FSize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIClip::setSize(EnginePrototype::FSize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setSize(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIClip::setSize$(EnginePrototype::FSize size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIClip::setSize(float width,float height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setSize(EnginePrototype::GameObject::_acc_gCppObject$(),width,height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIClip::setSize$(float width,float height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIClip::setPosition(float x,float y)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setPosition(EnginePrototype::GameObject::_acc_gCppObject$(),x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIClip::setPosition$(float x,float y) { CHCKTHIS; return setPosition(x,y); }



inline u32 EnginePrototype::CKLBUIClip::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIClip_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIClip::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIClip::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIClip::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUIClip::_acc_gMaxOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIClip_getMaxOdr(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIClip::_acc_gMaxOrder$() { CHCKTHIS; return _acc_gMaxOrder(); }

inline u32 EnginePrototype::CKLBUIClip::_acc_sMaxOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setMaxOdr(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIClip::_acc_sMaxOrder$(u32 value)		{ CHCKTHIS; return _acc_sMaxOrder(value); }
inline float EnginePrototype::CKLBUIClip::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIClip_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIClip::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline float EnginePrototype::CKLBUIClip::_acc_sWidth(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIClip::_acc_sWidth$(float value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline float EnginePrototype::CKLBUIClip::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIClip_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIClip::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline float EnginePrototype::CKLBUIClip::_acc_sHeight(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIClip_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIClip::_acc_sHeight$(float value)		{ CHCKTHIS; return _acc_sHeight(value); }
/*virtual*/
bool EnginePrototype::CKLBUIClip::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIClip,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIClip::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIClip::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIClip::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIControl'
//=============================

void EnginePrototype::CKLBUIControl::_ctor_CKLBUIControl() {
}

/*static*/
s32* EnginePrototype::CKLBUIControl::_ext_CKLBUIControl_create(s32* pParent)
{
    return CKLBUIControl_create(pParent);
}

/*static*/
bool EnginePrototype::CKLBUIControl::_ext_CKLBUIControl_setGroup(s32* p,s32* groupName)
{
    return CKLBUIControl_setGroup(p,groupName);
}

/*static*/
void EnginePrototype::CKLBUIControl::_ext_CKLBUIControl_setMask(s32* p,u16 mask)
{
    CKLBUIControl_setMask(p,mask);
}

/*static*/
void EnginePrototype::CKLBUIControl::_ext_CKLBUIControl_lock(s32* p,bool lockMode)
{
    CKLBUIControl_lock(p,lockMode);
}

EnginePrototype::CKLBUIControl::CKLBUIControl(EnginePrototype::CKLBTask* parent,EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* onClickCallBack,EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* onDragCallBack) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIControl();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIControl_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_onDragCallBack$(onDragCallBack);
    _sm_onClickCallBack$(onClickCallBack);
}

EnginePrototype::CKLBUIControl::CKLBUIControl() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIControl();
}

/*virtual*/
void EnginePrototype::CKLBUIControl::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUIIII_inner15<CKLBUIControl>(this,&CKLBUIControl::onDragCallBackFunction),0);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUFF_inner12<CKLBUIControl>(this,&CKLBUIControl::onPinchCallBackFunction),1);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerII_inner1<CKLBUIControl>(this,&CKLBUIControl::onClickCallBackFunction),2);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerII_inner1<CKLBUIControl>(this,&CKLBUIControl::onDblClickCallBackFunction),3);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUII_inner14<CKLBUIControl>(this,&CKLBUIControl::onLongTapCallBackFunction),4);
}

inline void EnginePrototype::CKLBUIControl::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIControl::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr67Obj))
    {
        _sm_onDragCallBack$((EnginePrototype::_Delegate_Base_OnDragCallBack_inner32*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr68Obj))
    {
        _sm_onPinchCallBack$((EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr69Obj))
    {
        _sm_onClickCallBack$((EnginePrototype::_Delegate_Base_OnClickCallBack_inner30*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr70Obj))
    {
        _sm_onDblClickCallBack$((EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr71Obj))
    {
        _sm_onLongTapCallBack$((EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34*)anyDelegate);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr57Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIControl::onClickCallBackFunction(s32 x,s32 y)
{
    if (_gm_onClickCallBack$() != NULL)
    {
        _gm_onClickCallBack$()->call$(this,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::onClickCallBackFunction$(s32 x,s32 y) { CHCKTHIS; return onClickCallBackFunction(x,y); }

/*virtual*/
void EnginePrototype::CKLBUIControl::onDragCallBackFunction(u32 mode,s32 x,s32 y,s32 mvX,s32 mvY)
{
    if (_gm_onDragCallBack$() != NULL)
    {
        _gm_onDragCallBack$()->call$(this,(EMODE)mode,x,y,mvX,mvY);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::onDragCallBackFunction$(u32 mode,s32 x,s32 y,s32 mvX,s32 mvY) { CHCKTHIS; return onDragCallBackFunction(mode,x,y,mvX,mvY); }

/*virtual*/
void EnginePrototype::CKLBUIControl::onPinchCallBackFunction(u32 mode,float pinch,float rotation)
{
    if (_gm_onPinchCallBack$() != NULL)
    {
        _gm_onPinchCallBack$()->call$(this,(EMODE)mode,pinch,rotation);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::onPinchCallBackFunction$(u32 mode,float pinch,float rotation) { CHCKTHIS; return onPinchCallBackFunction(mode,pinch,rotation); }

/*virtual*/
void EnginePrototype::CKLBUIControl::onDblClickCallBackFunction(s32 x,s32 y)
{
    if (_gm_onDblClickCallBack$() != NULL)
    {
        _gm_onDblClickCallBack$()->call$(this,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::onDblClickCallBackFunction$(s32 x,s32 y) { CHCKTHIS; return onDblClickCallBackFunction(x,y); }

/*virtual*/
void EnginePrototype::CKLBUIControl::onLongTapCallBackFunction(u32 elapsedTime,s32 x,s32 y)
{
    if (_gm_onLongTapCallBack$() != NULL)
    {
        _gm_onLongTapCallBack$()->call$(this,elapsedTime,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::onLongTapCallBackFunction$(u32 elapsedTime,s32 x,s32 y) { CHCKTHIS; return onLongTapCallBackFunction(elapsedTime,x,y); }

bool EnginePrototype::CKLBUIControl::setGroup(System::String* groupName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIControl_setGroup(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(groupName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIControl::setGroup$(System::String* groupName) { CHCKTHIS; return setGroup(groupName); }

void EnginePrototype::CKLBUIControl::setMask(s32 mask)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIControl_setMask(EnginePrototype::GameObject::_acc_gCppObject$(),(u16)mask);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::setMask$(s32 mask) { CHCKTHIS; return setMask(mask); }

void EnginePrototype::CKLBUIControl::setLock(bool lockBool)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIControl_lock(EnginePrototype::GameObject::_acc_gCppObject$(),lockBool);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIControl::setLock$(bool lockBool) { CHCKTHIS; return setLock(lockBool); }

inline EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* EnginePrototype::CKLBUIControl::_sm_onDragCallBack(EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _$value)  { return (EnginePrototype::_Delegate_Base_OnDragCallBack_inner32*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_onDragCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* EnginePrototype::CKLBUIControl::_sm_onDragCallBack$(EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _$value) { CHCKTHIS; return _sm_onDragCallBack(_$value); }
inline EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* EnginePrototype::CKLBUIControl::_sm_onPinchCallBack(EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _$value)  { return (EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_onPinchCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* EnginePrototype::CKLBUIControl::_sm_onPinchCallBack$(EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _$value) { CHCKTHIS; return _sm_onPinchCallBack(_$value); }
inline EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* EnginePrototype::CKLBUIControl::_sm_onClickCallBack(EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _$value)  { return (EnginePrototype::_Delegate_Base_OnClickCallBack_inner30*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_onClickCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* EnginePrototype::CKLBUIControl::_sm_onClickCallBack$(EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _$value) { CHCKTHIS; return _sm_onClickCallBack(_$value); }
inline EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* EnginePrototype::CKLBUIControl::_sm_onDblClickCallBack(EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _$value)  { return (EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_onDblClickCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* EnginePrototype::CKLBUIControl::_sm_onDblClickCallBack$(EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _$value) { CHCKTHIS; return _sm_onDblClickCallBack(_$value); }
inline EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* EnginePrototype::CKLBUIControl::_sm_onLongTapCallBack(EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _$value)  { return (EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_onLongTapCallBack,_$value); }
inline EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* EnginePrototype::CKLBUIControl::_sm_onLongTapCallBack$(EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _$value) { CHCKTHIS; return _sm_onLongTapCallBack(_$value); }


/*virtual*/
bool EnginePrototype::CKLBUIControl::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIControl,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIControl::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_onDragCallBack) { System::Memory::pushList(m_onDragCallBack,0); }
    if (m_onPinchCallBack) { System::Memory::pushList(m_onPinchCallBack,0); }
    if (m_onClickCallBack) { System::Memory::pushList(m_onClickCallBack,0); }
    if (m_onDblClickCallBack) { System::Memory::pushList(m_onDblClickCallBack,0); }
    if (m_onLongTapCallBack) { System::Memory::pushList(m_onLongTapCallBack,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIControl::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_onDragCallBack && !m_onDragCallBack->isFreed()) { m_onDragCallBack->_removeRef((System::__GCObject**)&m_onDragCallBack); }
    if (m_onPinchCallBack && !m_onPinchCallBack->isFreed()) { m_onPinchCallBack->_removeRef((System::__GCObject**)&m_onPinchCallBack); }
    if (m_onClickCallBack && !m_onClickCallBack->isFreed()) { m_onClickCallBack->_removeRef((System::__GCObject**)&m_onClickCallBack); }
    if (m_onDblClickCallBack && !m_onDblClickCallBack->isFreed()) { m_onDblClickCallBack->_removeRef((System::__GCObject**)&m_onDblClickCallBack); }
    if (m_onLongTapCallBack && !m_onLongTapCallBack->isFreed()) { m_onLongTapCallBack->_removeRef((System::__GCObject**)&m_onLongTapCallBack); }
}
/*virtual*/
void EnginePrototype::CKLBUIControl::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_onDragCallBack) {
      newPtr = (u8*)(&m_onDragCallBack); oldPtr = newPtr - offset;
      m_onDragCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_onPinchCallBack) {
      newPtr = (u8*)(&m_onPinchCallBack); oldPtr = newPtr - offset;
      m_onPinchCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_onClickCallBack) {
      newPtr = (u8*)(&m_onClickCallBack); oldPtr = newPtr - offset;
      m_onClickCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_onDblClickCallBack) {
      newPtr = (u8*)(&m_onDblClickCallBack); oldPtr = newPtr - offset;
      m_onDblClickCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_onLongTapCallBack) {
      newPtr = (u8*)(&m_onLongTapCallBack); oldPtr = newPtr - offset;
      m_onLongTapCallBack->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIDebugItem'
//=============================

void EnginePrototype::CKLBUIDebugItem::_ctor_CKLBUIDebugItem() {
}

/*static*/
s32* EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_create(s32* pParent,u32 order,float x,float y,u32 argb,s32* font,u32 size,s32* text,u32 id)
{
    return CKLBUIDebugItem_create(pParent,order,x,y,argb,font,size,text,id);
}

/*static*/
u32 EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_getOrder(s32* p)
{
    return CKLBUIDebugItem_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_setOrder(s32* p,u32 order)
{
    CKLBUIDebugItem_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_getColor(s32* p)
{
    return CKLBUIDebugItem_getColor(p);
}

/*static*/
void EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_setColor(s32* p,u32 order)
{
    CKLBUIDebugItem_setColor(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_getFont(s32* p)
{
    return CKLBUIDebugItem_getFont(p);
}

/*static*/
void EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_setFont(s32* p,s32* font)
{
    CKLBUIDebugItem_setFont(p,font);
}

/*static*/
u32 EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_getSize(s32* p)
{
    return CKLBUIDebugItem_getSize(p);
}

/*static*/
void EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_setSize(s32* p,u32 order)
{
    CKLBUIDebugItem_setSize(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_getText(s32* p)
{
    return CKLBUIDebugItem_getText(p);
}

/*static*/
void EnginePrototype::CKLBUIDebugItem::_ext_CKLBUIDebugItem_setText(s32* p,s32* text)
{
    CKLBUIDebugItem_setText(p,text);
}

EnginePrototype::CKLBUIDebugItem::CKLBUIDebugItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 argb,System::String* font_name,u32 font_size,System::String* text,u32 cmdID,EnginePrototype::_Delegate_Base_CallBack_inner35* callback) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIDebugItem();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIDebugItem_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,argb,System::__MarshallingUtils::NativeUtf8FromString(font_name),font_size,System::__MarshallingUtils::NativeUtf8FromString(text),cmdID);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUIDebugItem::CKLBUIDebugItem() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIDebugItem();
}

/*virtual*/
void EnginePrototype::CKLBUIDebugItem::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerU_inner10<CKLBUIDebugItem>(this,&CKLBUIDebugItem::callBackFunction),0);
}

inline void EnginePrototype::CKLBUIDebugItem::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIDebugItem::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner35*)anyDelegate);
}

inline void EnginePrototype::CKLBUIDebugItem::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIDebugItem::callBackFunction(u32 cmdID)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,cmdID);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIDebugItem::callBackFunction$(u32 cmdID) { CHCKTHIS; return callBackFunction(cmdID); }

inline EnginePrototype::_Delegate_Base_CallBack_inner35* EnginePrototype::CKLBUIDebugItem::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner35* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner35*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner35* EnginePrototype::CKLBUIDebugItem::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner35* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDebugItem_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDebugItem_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_gFont(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIDebugItem_getFont(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_gFont$() { CHCKTHIS; return _acc_gFont(); }

inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_sFont(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDebugItem_setFont(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_sFont$(System::String* value)		{ CHCKTHIS; return _acc_sFont(value); }
inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gSize(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDebugItem_getSize(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gSize$() { CHCKTHIS; return _acc_gSize(); }

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sSize(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDebugItem_setSize(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sSize$(u32 value)		{ CHCKTHIS; return _acc_sSize(value); }
inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gTextArgb(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDebugItem_getColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_gTextArgb$() { CHCKTHIS; return _acc_gTextArgb(); }

inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sTextArgb(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDebugItem_setColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIDebugItem::_acc_sTextArgb$(u32 value)		{ CHCKTHIS; return _acc_sTextArgb(value); }
inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_gText(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIDebugItem_getText(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_gText$() { CHCKTHIS; return _acc_gText(); }

inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_sText(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDebugItem_setText(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIDebugItem::_acc_sText$(System::String* value)		{ CHCKTHIS; return _acc_sText(value); }
/*virtual*/
bool EnginePrototype::CKLBUIDebugItem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIDebugItem,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIDebugItem::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIDebugItem::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIDebugItem::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIDragIcon'
//=============================

void EnginePrototype::CKLBUIDragIcon::_ctor_CKLBUIDragIcon() {
}

/*static*/
s32* EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_create(s32* pParent,u32 order,float x,float y,EnginePrototype::Area_inner3& tap_area,s32* asset,s32* drag_asset,s32 drag_order_offset,float drag_alpha,float center_x,float center_y,u32 flags)
{
    return CKLBUIDragIcon_create(pParent,order,x,y,(s32*)&tap_area + 1,asset,drag_asset,drag_order_offset,drag_alpha,center_x,center_y,flags);
}

/*static*/
u32 EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getOrder(s32* p)
{
    return CKLBUIDragIcon_getOrder(p);
}

/*static*/
s32* EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getAsset(s32* p)
{
    return CKLBUIDragIcon_getAsset(p);
}

/*static*/
s32* EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getDrag(s32* p)
{
    return CKLBUIDragIcon_getDrag(p);
}

/*static*/
u32 EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getFlags(s32* p)
{
    return CKLBUIDragIcon_getFlags(p);
}

/*static*/
void EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_setFlags(s32* p,u32 flag)
{
    CKLBUIDragIcon_setFlags(p,flag);
}

/*static*/
bool EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getEnable(s32* p)
{
    return CKLBUIDragIcon_getEnable(p);
}

/*static*/
void EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_setEnable(s32* p,bool enable)
{
    CKLBUIDragIcon_setEnable(p,enable);
}

/*static*/
float EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getDragScaleX(s32* p)
{
    return CKLBUIDragIcon_getDragScaleX(p);
}

/*static*/
void EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_setDragScaleX(s32* p,float x)
{
    CKLBUIDragIcon_setDragScaleX(p,x);
}

/*static*/
float EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_getDragScaleY(s32* p)
{
    return CKLBUIDragIcon_getDragScaleY(p);
}

/*static*/
void EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_setDragScaleY(s32* p,float y)
{
    CKLBUIDragIcon_setDragScaleY(p,y);
}

/*static*/
void EnginePrototype::CKLBUIDragIcon::_ext_CKLBUIDragIcon_dragArea(s32* p,EnginePrototype::Area_inner3& area)
{
    CKLBUIDragIcon_dragArea(p,(s32*)&area + 1);
}

EnginePrototype::CKLBUIDragIcon::CKLBUIDragIcon(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,EnginePrototype::Area_inner3& tap_area,System::String* asset,System::String* drag_asset,s32 drag_order_offset,float drag_alpha,float center_x,float center_y,EnginePrototype::_Delegate_Base_CallBack_inner36* callback,u32 flags) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIDragIcon();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIDragIcon_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,tap_area,System::__MarshallingUtils::NativeUtf8FromString(asset),System::__MarshallingUtils::NativeUtf8FromString(drag_asset),drag_order_offset,drag_alpha,center_x,center_y,flags);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUIDragIcon::CKLBUIDragIcon() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIDragIcon();
}

/*virtual*/
void EnginePrototype::CKLBUIDragIcon::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUII_inner14<CKLBUIDragIcon>(this,&CKLBUIDragIcon::callBackFunction),0);
}

inline void EnginePrototype::CKLBUIDragIcon::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIDragIcon::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner36*)anyDelegate);
}

inline void EnginePrototype::CKLBUIDragIcon::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIDragIcon::callBackFunction(u32 type,s32 x,s32 y)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,type,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIDragIcon::callBackFunction$(u32 type,s32 x,s32 y) { CHCKTHIS; return callBackFunction(type,x,y); }

void EnginePrototype::CKLBUIDragIcon::dragArea(EnginePrototype::Area_inner3 area)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDragIcon_dragArea(EnginePrototype::GameObject::_acc_gCppObject$(),area);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIDragIcon::dragArea$(EnginePrototype::Area_inner3 area) { CHCKTHIS; return dragArea(area); }

inline EnginePrototype::_Delegate_Base_CallBack_inner36* EnginePrototype::CKLBUIDragIcon::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner36* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner36*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner36* EnginePrototype::CKLBUIDragIcon::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner36* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUIDragIcon::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIDragIcon_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIDragIcon::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline System::String* EnginePrototype::CKLBUIDragIcon::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIDragIcon_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIDragIcon::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

inline System::String* EnginePrototype::CKLBUIDragIcon::_acc_gDragAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIDragIcon_getDrag(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIDragIcon::_acc_gDragAsset$() { CHCKTHIS; return _acc_gDragAsset(); }

inline s32 EnginePrototype::CKLBUIDragIcon::_acc_gFlags(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return (EFLAGS)_ext_CKLBUIDragIcon_getFlags(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIDragIcon::_acc_gFlags$() { CHCKTHIS; return _acc_gFlags(); }

inline s32 EnginePrototype::CKLBUIDragIcon::_acc_sFlags(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDragIcon_setFlags(EnginePrototype::GameObject::_acc_gCppObject$(),(u32)value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIDragIcon::_acc_sFlags$(s32 value)		{ CHCKTHIS; return _acc_sFlags(value); }
inline float EnginePrototype::CKLBUIDragIcon::_acc_gDragScaleX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDragIcon_getDragScaleX(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIDragIcon::_acc_gDragScaleX$() { CHCKTHIS; return _acc_gDragScaleX(); }

inline float EnginePrototype::CKLBUIDragIcon::_acc_sDragScaleX(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDragIcon_setDragScaleX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIDragIcon::_acc_sDragScaleX$(float value)		{ CHCKTHIS; return _acc_sDragScaleX(value); }
inline float EnginePrototype::CKLBUIDragIcon::_acc_gDragScaleY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDragIcon_getDragScaleY(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIDragIcon::_acc_gDragScaleY$() { CHCKTHIS; return _acc_gDragScaleY(); }

inline float EnginePrototype::CKLBUIDragIcon::_acc_sDragScaleY(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDragIcon_setDragScaleY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIDragIcon::_acc_sDragScaleY$(float value)		{ CHCKTHIS; return _acc_sDragScaleY(value); }
inline bool EnginePrototype::CKLBUIDragIcon::_acc_gEnable(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIDragIcon_getEnable(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIDragIcon::_acc_gEnable$() { CHCKTHIS; return _acc_gEnable(); }

inline bool EnginePrototype::CKLBUIDragIcon::_acc_sEnable(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIDragIcon_setEnable(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIDragIcon::_acc_sEnable$(bool value)		{ CHCKTHIS; return _acc_sEnable(value); }
/*virtual*/
bool EnginePrototype::CKLBUIDragIcon::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIDragIcon,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIDragIcon::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIDragIcon::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIDragIcon::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'Area_inner3'
//=============================

void EnginePrototype::Area_inner3::_ctor_Area_inner3() {
}

EnginePrototype::Area_inner3::Area_inner3(s32 _x,s32 _y,s32 _width,s32 _height)
{
    _ctor_Area_inner3();
    _sx$(_x);
    _sy$(_y);
    _swidth$(_width);
    _sheight$(_height);
}

void EnginePrototype::Area_inner3::setValues(s32 _x,s32 _y,s32 _width,s32 _height)
{
    _sx$(_x);
    _sy$(_y);
    _swidth$(_width);
    _sheight$(_height);
}

inline void EnginePrototype::Area_inner3::setValues$(s32 _x,s32 _y,s32 _width,s32 _height) { CHCKTHIS; return setValues(_x,_y,_width,_height); }

EnginePrototype::Area_inner3::Area_inner3() { _ctor_Area_inner3(); }


inline u32 EnginePrototype::Area_inner3::_processGC() {
    return System::__GCObject::COMPLETE;
}
inline void EnginePrototype::Area_inner3::_releaseGC() {
}
inline void* EnginePrototype::Area_inner3::_RefSetValue(void* newStruct) {
    Area_inner3* pStruct = (Area_inner3*)newStruct;
    this->x = pStruct->x;
    this->y = pStruct->y;
    this->width = pStruct->width;
    this->height = pStruct->height;
    return newStruct;
}
inline void EnginePrototype::Area_inner3::_moveAlert(u32 offset) {
}
inline EnginePrototype::Area_inner3& EnginePrototype::Area_inner3::__registerByRef(EnginePrototype::Area_inner3& m) {
    return m;
}


//=============================
// Implementation of 'CKLBUIForm'
//=============================

void EnginePrototype::CKLBUIForm::_ctor_CKLBUIForm() {
}

/*static*/
s32* EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_create(s32* pParent,u32 order,float x,float y,bool bAssetFile,s32* asset,bool bExclusive,bool modal,bool urgent)
{
    return CKLBUIForm_create(pParent,order,x,y,bAssetFile,asset,bExclusive,modal,urgent);
}

/*static*/
s32* EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_getAsset(s32* p)
{
    return CKLBUIForm_getAsset(p);
}

/*static*/
u32 EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_getOrder(s32* p)
{
    return CKLBUIForm_getOrder(p);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_getExclusive(s32* p)
{
    return CKLBUIForm_getExclusive(p);
}

/*static*/
void EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_setExclusive(s32* p,bool exclusive)
{
    CKLBUIForm_setExclusive(p,exclusive);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_getIsFile(s32* p)
{
    return CKLBUIForm_getIsFile(p);
}

/*static*/
void EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_setEnable(s32* p,bool isEnabled)
{
    CKLBUIForm_setEnable(p,isEnabled);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_existNode(s32* p,s32* name)
{
    return CKLBUIForm_existNode(p,name);
}

/*static*/
void EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_inputEnable(s32* p,bool bEnable)
{
    CKLBUIForm_inputEnable(p,bEnable);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_animation(s32* p,s32* animname,bool blend)
{
    return CKLBUIForm_animation(p,animname,blend);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_animEnter(s32* p)
{
    return CKLBUIForm_animEnter(p);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_animLeave(s32* p)
{
    return CKLBUIForm_animLeave(p);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_isAnim(s32* p,s32* name)
{
    return CKLBUIForm_isAnim(p,name);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_skipAnim(s32* p,s32* name)
{
    return CKLBUIForm_skipAnim(p,name);
}

/*static*/
bool EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_setGroup(s32* p,s32* groupName)
{
    return CKLBUIForm_setGroup(p,groupName);
}

/*static*/
void EnginePrototype::CKLBUIForm::_ext_CKLBUIForm_setGlobalVolume(s32* p,float volume)
{
    CKLBUIForm_setGlobalVolume(p,volume);
}

EnginePrototype::CKLBUIForm::CKLBUIForm(EnginePrototype::CKLBUITask* parent,u32 order,s32 x,s32 y,bool assetFile,System::String* asset_name,bool bExclusive,bool modal,bool urgent) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIForm();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIForm_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,assetFile,System::__MarshallingUtils::NativeUtf8FromString(asset_name),bExclusive,modal,urgent);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIForm::CKLBUIForm() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIForm();
}

/*virtual*/
void EnginePrototype::CKLBUIForm::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSII_inner5<CKLBUIForm>(this,&CKLBUIForm::selectableCallbackFunction),0);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSU_inner6<CKLBUIForm>(this,&CKLBUIForm::animCallBackFunction),4);
}

inline void EnginePrototype::CKLBUIForm::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIForm::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr75Obj))
    {
        _sm_selectableCallback$((EnginePrototype::_Delegate_Base_SelectableCallBack_inner37*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr76Obj))
    {
        _sm_animCallback$((EnginePrototype::_Delegate_Base_AnimCallBack_inner38*)anyDelegate);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr57Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIForm::animCallBackFunction(s32* name,u32 id)
{
    if (_gm_animCallback$() != NULL)
    {
        _gm_animCallback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(name),id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::animCallBackFunction$(s32* name,u32 id) { CHCKTHIS; return animCallBackFunction(name,id); }

/*virtual*/
void EnginePrototype::CKLBUIForm::selectableCallbackFunction(s32* name,s32 type,s32 param)
{
    if (_gm_selectableCallback$() != NULL)
    {
        _gm_selectableCallback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(name),type,param);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::selectableCallbackFunction$(s32* name,s32 type,s32 param) { CHCKTHIS; return selectableCallbackFunction(name,type,param); }

void EnginePrototype::CKLBUIForm::setEnabled(bool isEnabled)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIForm_setEnable(EnginePrototype::GameObject::_acc_gCppObject$(),isEnabled);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::setEnabled$(bool isEnabled) { CHCKTHIS; return setEnabled(isEnabled); }

bool EnginePrototype::CKLBUIForm::existNode(System::String* name)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_existNode(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(name));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::existNode$(System::String* name) { CHCKTHIS; return existNode(name); }

void EnginePrototype::CKLBUIForm::inputEnable(bool bEnable)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIForm_inputEnable(EnginePrototype::GameObject::_acc_gCppObject$(),bEnable);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::inputEnable$(bool bEnable) { CHCKTHIS; return inputEnable(bEnable); }

bool EnginePrototype::CKLBUIForm::animation(System::String* animationName,bool blend)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_animation(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName),blend);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::animation$(System::String* animationName,bool blend) { CHCKTHIS; return animation(animationName,blend); }

bool EnginePrototype::CKLBUIForm::isRunningAnimation(System::String* animationName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_isAnim(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::isRunningAnimation$(System::String* animationName) { CHCKTHIS; return isRunningAnimation(animationName); }

bool EnginePrototype::CKLBUIForm::skipAnim(System::String* animationName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_skipAnim(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::skipAnim$(System::String* animationName) { CHCKTHIS; return skipAnim(animationName); }

bool EnginePrototype::CKLBUIForm::animEnter()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_animEnter(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::animEnter$() { CHCKTHIS; return animEnter(); }

bool EnginePrototype::CKLBUIForm::animLeave()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_animLeave(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::animLeave$() { CHCKTHIS; return animLeave(); }

bool EnginePrototype::CKLBUIForm::setGroup(System::String* groupName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_setGroup(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(groupName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::setGroup$(System::String* groupName) { CHCKTHIS; return setGroup(groupName); }

void EnginePrototype::CKLBUIForm::setGlobalVolume(float volume)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIForm_setGlobalVolume(EnginePrototype::GameObject::_acc_gCppObject$(),volume);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIForm::setGlobalVolume$(float volume) { CHCKTHIS; return setGlobalVolume(volume); }

inline EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* EnginePrototype::CKLBUIForm::_sm_selectableCallback(EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _$value)  { return (EnginePrototype::_Delegate_Base_SelectableCallBack_inner37*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_selectableCallback,_$value); }
inline EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* EnginePrototype::CKLBUIForm::_sm_selectableCallback$(EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _$value) { CHCKTHIS; return _sm_selectableCallback(_$value); }
inline EnginePrototype::_Delegate_Base_AnimCallBack_inner38* EnginePrototype::CKLBUIForm::_sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _$value)  { return (EnginePrototype::_Delegate_Base_AnimCallBack_inner38*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_animCallback,_$value); }
inline EnginePrototype::_Delegate_Base_AnimCallBack_inner38* EnginePrototype::CKLBUIForm::_sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _$value) { CHCKTHIS; return _sm_animCallback(_$value); }


inline u32 EnginePrototype::CKLBUIForm::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIForm::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline System::String* EnginePrototype::CKLBUIForm::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIForm_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIForm::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

inline bool EnginePrototype::CKLBUIForm::_acc_gIsFile(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_getIsFile(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::_acc_gIsFile$() { CHCKTHIS; return _acc_gIsFile(); }

inline bool EnginePrototype::CKLBUIForm::_acc_gExclusive(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIForm_getExclusive(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIForm::_acc_gExclusive$() { CHCKTHIS; return _acc_gExclusive(); }

inline bool EnginePrototype::CKLBUIForm::_acc_sExclusive(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIForm_setExclusive(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIForm::_acc_sExclusive$(bool value)		{ CHCKTHIS; return _acc_sExclusive(value); }
/*virtual*/
bool EnginePrototype::CKLBUIForm::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIForm,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIForm::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_selectableCallback) { System::Memory::pushList(m_selectableCallback,0); }
    if (m_animCallback) { System::Memory::pushList(m_animCallback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIForm::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_selectableCallback && !m_selectableCallback->isFreed()) { m_selectableCallback->_removeRef((System::__GCObject**)&m_selectableCallback); }
    if (m_animCallback && !m_animCallback->isFreed()) { m_animCallback->_removeRef((System::__GCObject**)&m_animCallback); }
}
/*virtual*/
void EnginePrototype::CKLBUIForm::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_selectableCallback) {
      newPtr = (u8*)(&m_selectableCallback); oldPtr = newPtr - offset;
      m_selectableCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_animCallback) {
      newPtr = (u8*)(&m_animCallback); oldPtr = newPtr - offset;
      m_animCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIFreeVertItem'
//=============================

void EnginePrototype::CKLBUIFreeVertItem::_ctor_CKLBUIFreeVertItem() {
}

/*static*/
s32* EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_create(s32* parent,u32 order,float x,float y,s32* asset,System::Array<float>* verticesArray)
{
    return CKLBUIFreeVertItem_create(parent,order,x,y,asset,verticesArray ? (float*)verticesArray->_getPArray() : NULL);
}

/*static*/
u32 EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_getOrder(s32* p)
{
    return CKLBUIFreeVertItem_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_setOrder(s32* p,u32 order)
{
    CKLBUIFreeVertItem_setOrder(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_getAsset(s32* p)
{
    return CKLBUIFreeVertItem_getAsset(p);
}

/*static*/
void EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_setVertices(s32* p,System::Array<float>* coord)
{
    CKLBUIFreeVertItem_setVertices(p,coord ? (float*)coord->_getPArray() : NULL);
}

/*static*/
void EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_setColors(s32* p,System::Array<u32>* colors)
{
    CKLBUIFreeVertItem_setColors(p,colors ? (u32*)colors->_getPArray() : NULL);
}

/*static*/
void EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_setVertCol(s32* p,s32 idx,u32 argb)
{
    CKLBUIFreeVertItem_setVertCol(p,idx,argb);
}

/*static*/
void EnginePrototype::CKLBUIFreeVertItem::_ext_CKLBUIFreeVertItem_setUV(s32* p,System::Array<float>* uv)
{
    CKLBUIFreeVertItem_setUV(p,uv ? (float*)uv->_getPArray() : NULL);
}

EnginePrototype::CKLBUIFreeVertItem::CKLBUIFreeVertItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset,System::Array<float>* verticesArray) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIFreeVertItem();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIFreeVertItem_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,System::__MarshallingUtils::NativeUtf8FromString(asset),verticesArray);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIFreeVertItem::CKLBUIFreeVertItem() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIFreeVertItem();
}

void EnginePrototype::CKLBUIFreeVertItem::setVertices(System::Array<float>* coords)
{
    if (coords->_acc_gLength$() != 8)
    THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr78Obj));
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIFreeVertItem_setVertices(EnginePrototype::GameObject::_acc_gCppObject$(),coords);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIFreeVertItem::setVertices$(System::Array<float>* coords) { CHCKTHIS; return setVertices(coords); }

void EnginePrototype::CKLBUIFreeVertItem::setColors(System::Array<u32>* colors)
{
    if (colors->_acc_gLength$() != 4)
    THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr79Obj));
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIFreeVertItem_setColors(EnginePrototype::GameObject::_acc_gCppObject$(),colors);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIFreeVertItem::setColors$(System::Array<u32>* colors) { CHCKTHIS; return setColors(colors); }

void EnginePrototype::CKLBUIFreeVertItem::setVertCol(s32 idx,u32 argb)
{
    if (idx > 7)
    THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr80Obj));
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIFreeVertItem_setVertCol(EnginePrototype::GameObject::_acc_gCppObject$(),idx,argb);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIFreeVertItem::setVertCol$(s32 idx,u32 argb) { CHCKTHIS; return setVertCol(idx,argb); }

void EnginePrototype::CKLBUIFreeVertItem::setUv(System::Array<float>* uv)
{
    if (uv->_acc_gLength$() != 8)
    THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr81Obj));
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIFreeVertItem_setUV(EnginePrototype::GameObject::_acc_gCppObject$(),uv);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIFreeVertItem::setUv$(System::Array<float>* uv) { CHCKTHIS; return setUv(uv); }



inline u32 EnginePrototype::CKLBUIFreeVertItem::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIFreeVertItem_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIFreeVertItem::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIFreeVertItem::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIFreeVertItem_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIFreeVertItem::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUIFreeVertItem::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIFreeVertItem_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIFreeVertItem::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

/*virtual*/
bool EnginePrototype::CKLBUIFreeVertItem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIFreeVertItem,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIFreeVertItem::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIFreeVertItem::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIFreeVertItem::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIGroup'
//=============================

void EnginePrototype::CKLBUIGroup::_ctor_CKLBUIGroup() {
}

/*static*/
s32* EnginePrototype::CKLBUIGroup::_ext_CKLBUIGroup_create(s32* parent,float x,float y)
{
    return CKLBUIGroup_create(parent,x,y);
}

/*static*/
bool EnginePrototype::CKLBUIGroup::_ext_CKLBUIGroup_setAnimCallback(s32* p,s32* callback)
{
    return CKLBUIGroup_setAnimCallback(p,callback);
}

/*static*/
bool EnginePrototype::CKLBUIGroup::_ext_CKLBUIGroup_setAnimation(s32* p,s32* anim_name,bool blend)
{
    return CKLBUIGroup_setAnimation(p,anim_name,blend);
}

/*static*/
bool EnginePrototype::CKLBUIGroup::_ext_CKLBUIGroup_isAnim(s32* p,s32* anim_name)
{
    return CKLBUIGroup_isAnim(p,anim_name);
}

/*static*/
bool EnginePrototype::CKLBUIGroup::_ext_CKLBUIGroup_skipAnim(s32* p,s32* anim_name)
{
    return CKLBUIGroup_skipAnim(p,anim_name);
}

EnginePrototype::CKLBUIGroup::CKLBUIGroup(EnginePrototype::CKLBUITask* parent,float x,float y) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIGroup();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIGroup_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),x,y);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIGroup::CKLBUIGroup() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIGroup();
}

/*virtual*/
void EnginePrototype::CKLBUIGroup::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSU_inner6<CKLBUIGroup>(this,&CKLBUIGroup::animCallBackFunction),0);
}

inline void EnginePrototype::CKLBUIGroup::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIGroup::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr76Obj))
    {
        _sm_animCallback$((EnginePrototype::_Delegate_Base_AnimCallBack_inner39*)anyDelegate);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr57Obj));
    }
}

inline void EnginePrototype::CKLBUIGroup::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIGroup::animCallBackFunction(s32* name,u32 id)
{
    if (_gm_animCallback$() != NULL)
    {
        _gm_animCallback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(name),id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIGroup::animCallBackFunction$(s32* name,u32 id) { CHCKTHIS; return animCallBackFunction(name,id); }

bool EnginePrototype::CKLBUIGroup::setAnimation(System::String* animationName,bool blendFlag)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIGroup_setAnimation(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName),blendFlag);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline bool EnginePrototype::CKLBUIGroup::setAnimation$(System::String* animationName,bool blendFlag) { CHCKTHIS; return setAnimation(animationName,blendFlag); }

bool EnginePrototype::CKLBUIGroup::isRunningAnimation(System::String* animationName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIGroup_isAnim(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline bool EnginePrototype::CKLBUIGroup::isRunningAnimation$(System::String* animationName) { CHCKTHIS; return isRunningAnimation(animationName); }

bool EnginePrototype::CKLBUIGroup::skipAnim(System::String* animationName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIGroup_skipAnim(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline bool EnginePrototype::CKLBUIGroup::skipAnim$(System::String* animationName) { CHCKTHIS; return skipAnim(animationName); }

inline EnginePrototype::_Delegate_Base_AnimCallBack_inner39* EnginePrototype::CKLBUIGroup::_sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _$value)  { return (EnginePrototype::_Delegate_Base_AnimCallBack_inner39*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_animCallback,_$value); }
inline EnginePrototype::_Delegate_Base_AnimCallBack_inner39* EnginePrototype::CKLBUIGroup::_sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _$value) { CHCKTHIS; return _sm_animCallback(_$value); }


/*virtual*/
bool EnginePrototype::CKLBUIGroup::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIGroup,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIGroup::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_animCallback) { System::Memory::pushList(m_animCallback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIGroup::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_animCallback && !m_animCallback->isFreed()) { m_animCallback->_removeRef((System::__GCObject**)&m_animCallback); }
}
/*virtual*/
void EnginePrototype::CKLBUIGroup::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_animCallback) {
      newPtr = (u8*)(&m_animCallback); oldPtr = newPtr - offset;
      m_animCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUILabel'
//=============================

void EnginePrototype::CKLBUILabel::_ctor_CKLBUILabel() {
}

/*static*/
s32* EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_create(s32* pParent,u32 order,float x,float y,u32 argb,s32* font,u32 size,s32* text,u32 align)
{
    return CKLBUILabel_create(pParent,order,x,y,argb,font,size,text,align);
}

/*static*/
u32 EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getOrder(s32* p)
{
    return CKLBUILabel_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setOrder(s32* p,u32 order)
{
    CKLBUILabel_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getAlign(s32* p)
{
    return CKLBUILabel_getAlign(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setAlign(s32* p,u32 align)
{
    CKLBUILabel_setAlign(p,align);
}

/*static*/
s32* EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getText(s32* p)
{
    return CKLBUILabel_getText(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setText(s32* p,s32* text)
{
    CKLBUILabel_setText(p,text);
}

/*static*/
u32 EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getColor(s32* p)
{
    return CKLBUILabel_getColor(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setColor(s32* p,u32 color)
{
    CKLBUILabel_setColor(p,color);
}

/*static*/
s32* EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getFont(s32* p)
{
    return CKLBUILabel_getFont(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setFont(s32* p,s32* font)
{
    CKLBUILabel_setFont(p,font);
}

/*static*/
u32 EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_getFontSize(s32* p)
{
    return CKLBUILabel_getFontSize(p);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setFontSize(s32* p,u32 size)
{
    CKLBUILabel_setFontSize(p,size);
}

/*static*/
void EnginePrototype::CKLBUILabel::_ext_CKLBUILabel_setPosition(s32* p,float x,float y)
{
    CKLBUILabel_setPosition(p,x,y);
}

EnginePrototype::CKLBUILabel::CKLBUILabel(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 argb,System::String* font_name,u32 font_size,System::String* text,s32 align) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUILabel();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUILabel_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,argb,System::__MarshallingUtils::NativeUtf8FromString(font_name),font_size,System::__MarshallingUtils::NativeUtf8FromString(text),(u32)align);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUILabel::CKLBUILabel() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUILabel();
    System::Console::WriteLine(_$_cteStr84Obj);
}

void EnginePrototype::CKLBUILabel::setFont(System::String* name,u32 size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setFont(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(name));
        _ext_CKLBUILabel_setFontSize(EnginePrototype::GameObject::_acc_gCppObject$(),size);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUILabel::setFont$(System::String* name,u32 size) { CHCKTHIS; return setFont(name,size); }

void EnginePrototype::CKLBUILabel::setPosition(float x,float y)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setPosition(EnginePrototype::GameObject::_acc_gCppObject$(),x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUILabel::setPosition$(float x,float y) { CHCKTHIS; return setPosition(x,y); }



inline u32 EnginePrototype::CKLBUILabel::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUILabel_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUILabel::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUILabel::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUILabel::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUILabel::_acc_gFontName(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUILabel_getFont(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUILabel::_acc_gFontName$() { CHCKTHIS; return _acc_gFontName(); }

inline System::String* EnginePrototype::CKLBUILabel::_acc_sFontName(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setFont(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUILabel::_acc_sFontName$(System::String* value)		{ CHCKTHIS; return _acc_sFontName(value); }
inline u32 EnginePrototype::CKLBUILabel::_acc_gFontSize(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUILabel_getFontSize(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUILabel::_acc_gFontSize$() { CHCKTHIS; return _acc_gFontSize(); }

inline u32 EnginePrototype::CKLBUILabel::_acc_sFontSize(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setFontSize(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUILabel::_acc_sFontSize$(u32 value)		{ CHCKTHIS; return _acc_sFontSize(value); }
inline u32 EnginePrototype::CKLBUILabel::_acc_gTxtArgb(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUILabel_getColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUILabel::_acc_gTxtArgb$() { CHCKTHIS; return _acc_gTxtArgb(); }

inline u32 EnginePrototype::CKLBUILabel::_acc_sTxtArgb(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUILabel::_acc_sTxtArgb$(u32 value)		{ CHCKTHIS; return _acc_sTxtArgb(value); }
inline System::String* EnginePrototype::CKLBUILabel::_acc_gText(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUILabel_getText(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUILabel::_acc_gText$() { CHCKTHIS; return _acc_gText(); }

inline System::String* EnginePrototype::CKLBUILabel::_acc_sText(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setText(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUILabel::_acc_sText$(System::String* value)		{ CHCKTHIS; return _acc_sText(value); }
inline s32 EnginePrototype::CKLBUILabel::_acc_gAlign(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return (EALIGN)_ext_CKLBUILabel_getAlign(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUILabel::_acc_gAlign$() { CHCKTHIS; return _acc_gAlign(); }

inline s32 EnginePrototype::CKLBUILabel::_acc_sAlign(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUILabel_setAlign(EnginePrototype::GameObject::_acc_gCppObject$(),(u32)value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUILabel::_acc_sAlign$(s32 value)		{ CHCKTHIS; return _acc_sAlign(value); }
/*virtual*/
bool EnginePrototype::CKLBUILabel::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUILabel,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUILabel::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUILabel::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUILabel::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIList'
//=============================

void EnginePrototype::CKLBUIList::_ctor_CKLBUIList() {
}

/*static*/
s32* EnginePrototype::CKLBUIList::_ext_CKLBUIList_create(s32* pParent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight,s32 defaultLineStep,bool vertical,u32 optionalFlags)
{
    return CKLBUIList_create(pParent,baseOrder,maxOrder,x,y,clipWidth,clipHeight,defaultLineStep,vertical,optionalFlags);
}

/*static*/
u32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getWidth(s32* p)
{
    return CKLBUIList_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setWidth(s32* p,u32 width)
{
    CKLBUIList_setWidth(p,width);
}

/*static*/
u32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getHeight(s32* p)
{
    return CKLBUIList_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setHeight(s32* p,u32 height)
{
    CKLBUIList_setHeight(p,height);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getStepX(s32* p)
{
    return CKLBUIList_getStepX(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setStepX(s32* p,s32 x)
{
    CKLBUIList_setStepX(p,x);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getStepY(s32* p)
{
    return CKLBUIList_getStepY(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setStepY(s32* p,s32 y)
{
    CKLBUIList_setStepY(p,y);
}

/*static*/
u32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getOrder(s32* p)
{
    return CKLBUIList_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setOrder(s32* p,u32 order)
{
    CKLBUIList_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getMaxOrder(s32* p)
{
    return CKLBUIList_getMaxOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setMaxOrder(s32* p,u32 order)
{
    CKLBUIList_setMaxOrder(p,order);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_getVertical(s32* p)
{
    return CKLBUIList_getVertical(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setVertical(s32* p,bool vertical)
{
    CKLBUIList_setVertical(p,vertical);
}

/*static*/
u32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getItems(s32* p)
{
    return CKLBUIList_getItems(p);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getMarginTop(s32* p)
{
    return CKLBUIList_getMarginTop(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setMarginTop(s32* p,s32 top)
{
    CKLBUIList_setMarginTop(p,top);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_getMarginBottom(s32* p)
{
    return CKLBUIList_getMarginBottom(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setMarginBottom(s32* p,s32 bottom)
{
    CKLBUIList_setMarginBottom(p,bottom);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_getDefaultScroll(s32* p)
{
    return CKLBUIList_getDefaultScroll(p);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setDefaultScroll(s32* p,bool scroll)
{
    CKLBUIList_setDefaultScroll(p,scroll);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdItemRemove(s32* p,s32 idx)
{
    return CKLBUIList_cmdItemRemove(p,idx);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdItemMove(s32* p,s32 src,s32 dst)
{
    CKLBUIList_cmdItemMove(p,src,dst);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetMargin(s32* p,s32 top,s32 bottom)
{
    CKLBUIList_cmdSetMargin(p,top,bottom);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdGetPosition(s32* p)
{
    return CKLBUIList_cmdGetPosition(p);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetPosition(s32* p,s32 pos,s32 dir)
{
    return CKLBUIList_cmdSetPosition(p,pos,dir);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetItemID(s32* p,s32 index,s32 id)
{
    CKLBUIList_cmdSetItemID(p,index,id);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSearchID(s32* p,s32 id)
{
    return CKLBUIList_cmdSearchID(p,id);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetItemPos(s32* p,s32 mode,s32 idx,s32 offset)
{
    CKLBUIList_cmdSetItemPos(p,mode,idx,offset);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetLimitClip(s32* p,bool chklimit)
{
    CKLBUIList_cmdSetLimitClip(p,chklimit);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdGetLimit(s32* p)
{
    return CKLBUIList_cmdGetLimit(p);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetLimitArea(s32* p,s32 limitArea)
{
    return CKLBUIList_cmdSetLimitArea(p,limitArea);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdChangeStep(s32* p,s32 index,s32 step)
{
    CKLBUIList_cmdChangeStep(p,index,step);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdInputEnable(s32* p,bool enable)
{
    CKLBUIList_cmdInputEnable(p,enable);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdExistNode(s32* p,s32 index,s32* name)
{
    return CKLBUIList_cmdExistNode(p,index,name);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdAnimationItem(s32* p,s32 index,s32* name,bool blend)
{
    return CKLBUIList_cmdAnimationItem(p,index,name,blend);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdAnimationAll(s32* p,s32* name,bool blend)
{
    return CKLBUIList_cmdAnimationAll(p,name,blend);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdItemAnimSkip(s32* p,s32 idx,s32* name)
{
    return CKLBUIList_cmdItemAnimSkip(p,idx,name);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdAllAnimSkip(s32* p,s32* name)
{
    return CKLBUIList_cmdAllAnimSkip(p,name);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetGroup(s32* p,s32* group_name)
{
    CKLBUIList_cmdSetGroup(p,group_name);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setLoop(s32* p,bool mode)
{
    CKLBUIList_setLoop(p,mode);
}

/*static*/
s32 EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetInitial(s32* p,s32 pos)
{
    return CKLBUIList_cmdSetInitial(p,pos);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_useScrollBar(s32* p,u32 order,bool side,s32 lineWeight,s32* image,s32 minSlenderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide)
{
    return CKLBUIList_useScrollBar(p,order,side,lineWeight,image,minSlenderSize,colorNormal,colorSelect,active,hideMode,shortHide);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdFWModeConfig(s32* p,s32 itemStep,s32 maxItems)
{
    CKLBUIList_cmdFWModeConfig(p,itemStep,maxItems);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetItemMode(s32* p,s32 itemMode)
{
    return CKLBUIList_cmdSetItemMode(p,itemMode);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdAddRecords(s32* p,s32 insIdx,s32* tpForm,s32* dbRecords,s32 step)
{
    return CKLBUIList_cmdAddRecords(p,insIdx,tpForm,dbRecords,step);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSelectScrMgr(s32* p,s32* name,System::Array<s32>* optParams,u32 nb)
{
    return CKLBUIList_cmdSelectScrMgr(p,name,optParams ? (s32*)optParams->_getPArray() : NULL,nb);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdSetClip(s32* p,u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight)
{
    CKLBUIList_cmdSetClip(p,orderBegin,orderEnd,clipX,clipY,clipWidth,clipHeight);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdItemAdd(s32* p,s32* name)
{
    return CKLBUIList_cmdItemAdd(p,name);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdItemAdd2(s32* p,s32* name,s32 step,s32 id)
{
    return CKLBUIList_cmdItemAdd2(p,name,step,id);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdInsertItem(s32* p,s32* name,s32 idx)
{
    return CKLBUIList_cmdInsertItem(p,name,idx);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdInsertItem2(s32* p,s32* name,s32 idx,s32 step,s32 id)
{
    return CKLBUIList_cmdInsertItem2(p,name,idx,step,id);
}

/*static*/
bool EnginePrototype::CKLBUIList::_ext_CKLBUIList_cmdRemoveSelection(s32* p,System::Array<s32>* indexes,u32 nb)
{
    return CKLBUIList_cmdRemoveSelection(p,indexes ? (s32*)indexes->_getPArray() : NULL,nb);
}

/*static*/
void EnginePrototype::CKLBUIList::_ext_CKLBUIList_setDragRect(s32* p,s32 left,s32 top,s32 right,s32 bottom)
{
    CKLBUIList_setDragRect(p,left,top,right,bottom);
}

EnginePrototype::CKLBUIList::CKLBUIList(EnginePrototype::CKLBUITask* parent,u32 base_priority,u32 max_order,float x,float y,float clip_width,float clip_height,s32 default_line_step,EnginePrototype::_Delegate_Base_DragCallBack_inner41* callback,bool vertical,u32 option_flags) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIList();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIList_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),base_priority,max_order,x,y,clip_width,clip_height,default_line_step,vertical,option_flags);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_dragCallback$(callback);
}

EnginePrototype::CKLBUIList::CKLBUIList() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIList();
}

/*virtual*/
void EnginePrototype::CKLBUIList::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUIIII_inner15<CKLBUIList>(this,&CKLBUIList::dragCallBackFunction),0);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUUII_inner17<CKLBUIList>(this,&CKLBUIList::limitCallBackFunction),1);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerII_inner1<CKLBUIList>(this,&CKLBUIList::dynamicCallBackFunction),2);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUI_inner13<CKLBUIList>(this,&CKLBUIList::scrollbarCallBackFunction),3);
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSU_inner6<CKLBUIList>(this,&CKLBUIList::animCallBackFunction),4);
}

inline void EnginePrototype::CKLBUIList::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIList::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    if (delegateName->Equals(_$_cteStr86Obj))
    {
        _sm_limitCallback$((EnginePrototype::_Delegate_Base_LimitCallBack_inner40*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr87Obj))
    {
        _sm_dragCallback$((EnginePrototype::_Delegate_Base_DragCallBack_inner41*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr88Obj))
    {
        _sm_dynamicCallback$((EnginePrototype::_Delegate_Base_DynamicCallBack_inner42*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr76Obj))
    {
        _sm_animCallback$((EnginePrototype::_Delegate_Base_AnimCallBack_inner44*)anyDelegate);
    }
    else
    if (delegateName->Equals(_$_cteStr89Obj))
    {
        _sm_scrollbarCallback$((EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43*)anyDelegate);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr57Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIList::dragCallBackFunction(u32 type,s32 x,s32 y,s32 param1,s32 param2)
{
    if (_gm_dragCallback$() != NULL)
    {
        _gm_dragCallback$()->call$(this,type,x,y,param1,param2);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIList::dragCallBackFunction$(u32 type,s32 x,s32 y,s32 param1,s32 param2) { CHCKTHIS; return dragCallBackFunction(type,x,y,param1,param2); }

/*virtual*/
void EnginePrototype::CKLBUIList::limitCallBackFunction(u32 type,u32 itemCount,s32 listLength,s32 pos)
{
    if (_gm_limitCallback$() != NULL)
    {
        _gm_limitCallback$()->call$(this,type,itemCount,listLength,pos);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIList::limitCallBackFunction$(u32 type,u32 itemCount,s32 listLength,s32 pos) { CHCKTHIS; return limitCallBackFunction(type,itemCount,listLength,pos); }

/*virtual*/
void EnginePrototype::CKLBUIList::dynamicCallBackFunction(s32 index,s32 id)
{
    if (_gm_dynamicCallback$() != NULL)
    {
        _gm_dynamicCallback$()->call$(this,index,id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIList::dynamicCallBackFunction$(s32 index,s32 id) { CHCKTHIS; return dynamicCallBackFunction(index,id); }

/*virtual*/
void EnginePrototype::CKLBUIList::scrollbarCallBackFunction(u32 type,s32 pos)
{
    if (_gm_scrollbarCallback$() != NULL)
    {
        _gm_scrollbarCallback$()->call$(this,type,pos);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIList::scrollbarCallBackFunction$(u32 type,s32 pos) { CHCKTHIS; return scrollbarCallBackFunction(type,pos); }

/*virtual*/
void EnginePrototype::CKLBUIList::animCallBackFunction(s32* name,u32 id)
{
    if (_gm_animCallback$() != NULL)
    {
        _gm_animCallback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(name),id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIList::animCallBackFunction$(s32* name,u32 id) { CHCKTHIS; return animCallBackFunction(name,id); }

void EnginePrototype::CKLBUIList::getSize(EnginePrototype::USize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIList_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIList_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::getSize$(EnginePrototype::USize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIList::setSize(EnginePrototype::USize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIList_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setSize$(EnginePrototype::USize size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIList::setSize(u32 width,u32 height)
{
    _ext_CKLBUIList_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
    _ext_CKLBUIList_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
}

inline void EnginePrototype::CKLBUIList::setSize$(u32 width,u32 height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIList::itemAdd(System::String* asset)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdItemAdd(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(asset));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemAdd$(System::String* asset) { CHCKTHIS; return itemAdd(asset); }

void EnginePrototype::CKLBUIList::itemAdd(System::String* asset,s32 step,s32 id)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdItemAdd2(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(asset),step,id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemAdd$(System::String* asset,s32 step,s32 id) { CHCKTHIS; return itemAdd(asset,step,id); }

void EnginePrototype::CKLBUIList::itemInsert(System::String* asset,s32 index)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdInsertItem(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(asset),index);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemInsert$(System::String* asset,s32 index) { CHCKTHIS; return itemInsert(asset,index); }

void EnginePrototype::CKLBUIList::itemInsert(System::String* asset,s32 index,s32 step,s32 id)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdInsertItem2(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(asset),index,step,id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemInsert$(System::String* asset,s32 index,s32 step,s32 id) { CHCKTHIS; return itemInsert(asset,index,step,id); }

bool EnginePrototype::CKLBUIList::itemRemove(s32 index)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdItemRemove(EnginePrototype::GameObject::_acc_gCppObject$(),index);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::itemRemove$(s32 index) { CHCKTHIS; return itemRemove(index); }

void EnginePrototype::CKLBUIList::itemMove(s32 src,s32 dst)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdItemMove(EnginePrototype::GameObject::_acc_gCppObject$(),src,dst);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemMove$(s32 src,s32 dst) { CHCKTHIS; return itemMove(src,dst); }

void EnginePrototype::CKLBUIList::itemRemoveSelection(System::Array<s32>* indexes)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdRemoveSelection(EnginePrototype::GameObject::_acc_gCppObject$(),indexes,(u32)indexes->_acc_gLength$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::itemRemoveSelection$(System::Array<s32>* indexes) { CHCKTHIS; return itemRemoveSelection(indexes); }

void EnginePrototype::CKLBUIList::setMargin(s32 margin_top,s32 margin_bottom)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetMargin(EnginePrototype::GameObject::_acc_gCppObject$(),margin_top,margin_bottom);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setMargin$(s32 margin_top,s32 margin_bottom) { CHCKTHIS; return setMargin(margin_top,margin_bottom); }

void EnginePrototype::CKLBUIList::setItemPosition(s32 positionMode,s32 index,s32 offset)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetItemPos(EnginePrototype::GameObject::_acc_gCppObject$(),(s32)positionMode,index,offset);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setItemPosition$(s32 positionMode,s32 index,s32 offset) { CHCKTHIS; return setItemPosition(positionMode,index,offset); }

void EnginePrototype::CKLBUIList::changeStep(s32 index,s32 newStep)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdChangeStep(EnginePrototype::GameObject::_acc_gCppObject$(),index,newStep);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::changeStep$(s32 index,s32 newStep) { CHCKTHIS; return changeStep(index,newStep); }

void EnginePrototype::CKLBUIList::setLimitClip(bool limitClipEnable)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetLimitClip(EnginePrototype::GameObject::_acc_gCppObject$(),limitClipEnable);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setLimitClip$(bool limitClipEnable) { CHCKTHIS; return setLimitClip(limitClipEnable); }

void EnginePrototype::CKLBUIList::setLimitClip(bool limitClipEnable,EnginePrototype::_Delegate_Base_LimitCallBack_inner40* limitCallback)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_limitCallback$(limitCallback);
        _ext_CKLBUIList_cmdSetLimitClip(EnginePrototype::GameObject::_acc_gCppObject$(),limitClipEnable);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setLimitClip$(bool limitClipEnable,EnginePrototype::_Delegate_Base_LimitCallBack_inner40* limitCallback) { CHCKTHIS; return setLimitClip(limitClipEnable,limitCallback); }

bool EnginePrototype::CKLBUIList::setLimitArea(s32 size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdSetLimitArea(EnginePrototype::GameObject::_acc_gCppObject$(),size);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::setLimitArea$(s32 size) { CHCKTHIS; return setLimitArea(size); }

void EnginePrototype::CKLBUIList::setInputEnable(bool enableFlag)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdInputEnable(EnginePrototype::GameObject::_acc_gCppObject$(),enableFlag);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setInputEnable$(bool enableFlag) { CHCKTHIS; return setInputEnable(enableFlag); }

bool EnginePrototype::CKLBUIList::existNode(s32 index,System::String* name)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        bool res = _ext_CKLBUIList_cmdExistNode(EnginePrototype::GameObject::_acc_gCppObject$(),index,System::__MarshallingUtils::NativeUtf8FromString(name));
        EnginePrototype::NativeManagement::intercepCppError();
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::existNode$(s32 index,System::String* name) { CHCKTHIS; return existNode(index,name); }

bool EnginePrototype::CKLBUIList::animationItem(s32 index,System::String* animationName,bool blendFlag)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdAnimationItem(EnginePrototype::GameObject::_acc_gCppObject$(),index,System::__MarshallingUtils::NativeUtf8FromString(animationName),blendFlag);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::animationItem$(s32 index,System::String* animationName,bool blendFlag) { CHCKTHIS; return animationItem(index,animationName,blendFlag); }

bool EnginePrototype::CKLBUIList::animationAll(System::String* animationName,bool blendFlag)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdAnimationAll(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(animationName),blendFlag);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::animationAll$(System::String* animationName,bool blendFlag) { CHCKTHIS; return animationAll(animationName,blendFlag); }

bool EnginePrototype::CKLBUIList::useScrollbar(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_useScrollBar(EnginePrototype::GameObject::_acc_gCppObject$(),order,side,lineWeight,System::__MarshallingUtils::NativeUtf8FromString(image),minSliderSize,colorNormal,colorSelect,active,hideMode,shortHide);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::useScrollbar$(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide) { CHCKTHIS; return useScrollbar(order,side,lineWeight,image,minSliderSize,colorNormal,colorSelect,active,hideMode,shortHide); }

bool EnginePrototype::CKLBUIList::useScrollbar(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* callback,bool hideMode,bool shortHide)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_scrollbarCallback$(callback);
        return _ext_CKLBUIList_useScrollBar(EnginePrototype::GameObject::_acc_gCppObject$(),order,side,lineWeight,System::__MarshallingUtils::NativeUtf8FromString(image),minSliderSize,colorNormal,colorSelect,active,hideMode,shortHide);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::useScrollbar$(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* callback,bool hideMode,bool shortHide) { CHCKTHIS; return useScrollbar(order,side,lineWeight,image,minSliderSize,colorNormal,colorSelect,active,callback,hideMode,shortHide); }

void EnginePrototype::CKLBUIList::setItemID(s32 index,s32 id)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetItemID(EnginePrototype::GameObject::_acc_gCppObject$(),index,id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setItemID$(s32 index,s32 id) { CHCKTHIS; return setItemID(index,id); }

s32 EnginePrototype::CKLBUIList::searchID(s32 index)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdSearchID(EnginePrototype::GameObject::_acc_gCppObject$(),index);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::searchID$(s32 index) { CHCKTHIS; return searchID(index); }

bool EnginePrototype::CKLBUIList::selectScrMgr(System::String* managerName,System::Array<s32>* optParams)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        if (optParams != NULL)
        {
            return _ext_CKLBUIList_cmdSelectScrMgr(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(managerName),optParams,(u32)optParams->_acc_gLength$());
        }
        else
        {
            return _ext_CKLBUIList_cmdSelectScrMgr(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(managerName),(System::Array<s32>*)NULL,0);
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::selectScrMgr$(System::String* managerName,System::Array<s32>* optParams) { CHCKTHIS; return selectScrMgr(managerName,optParams); }

bool EnginePrototype::CKLBUIList::itemAnimSkip(s32 idx,System::String* name)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdItemAnimSkip(EnginePrototype::GameObject::_acc_gCppObject$(),idx,System::__MarshallingUtils::NativeUtf8FromString(name));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::itemAnimSkip$(s32 idx,System::String* name) { CHCKTHIS; return itemAnimSkip(idx,name); }

bool EnginePrototype::CKLBUIList::allAnimSkip(System::String* groupName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdAllAnimSkip(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(groupName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::allAnimSkip$(System::String* groupName) { CHCKTHIS; return allAnimSkip(groupName); }

bool EnginePrototype::CKLBUIList::addRecords(s32 insIdx,System::String* tpForm,System::String* dbRecords,s32 step)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdAddRecords(EnginePrototype::GameObject::_acc_gCppObject$(),insIdx,System::__MarshallingUtils::NativeUtf8FromString(tpForm),System::__MarshallingUtils::NativeUtf8FromString(dbRecords),step);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::addRecords$(s32 insIdx,System::String* tpForm,System::String* dbRecords,s32 step) { CHCKTHIS; return addRecords(insIdx,tpForm,dbRecords,step); }

s32 EnginePrototype::CKLBUIList::setInitial(s32 pos)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdSetInitial(EnginePrototype::GameObject::_acc_gCppObject$(),pos);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::setInitial$(s32 pos) { CHCKTHIS; return setInitial(pos); }

void EnginePrototype::CKLBUIList::fwModeConfig(s32 itemStep,s32 maxItems)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdFWModeConfig(EnginePrototype::GameObject::_acc_gCppObject$(),itemStep,maxItems);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::fwModeConfig$(s32 itemStep,s32 maxItems) { CHCKTHIS; return fwModeConfig(itemStep,maxItems); }

void EnginePrototype::CKLBUIList::fwItemAdd()
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionNotImplemented(_$_cteStr90Obj));
}

inline void EnginePrototype::CKLBUIList::fwItemAdd$() { CHCKTHIS; return fwItemAdd(); }

void EnginePrototype::CKLBUIList::fwItemInsertTop()
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionNotImplemented(_$_cteStr90Obj));
}

inline void EnginePrototype::CKLBUIList::fwItemInsertTop$() { CHCKTHIS; return fwItemInsertTop(); }

bool EnginePrototype::CKLBUIList::setItemMode(s32 mode)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdSetItemMode(EnginePrototype::GameObject::_acc_gCppObject$(),(s32)mode);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::setItemMode$(s32 mode) { CHCKTHIS; return setItemMode(mode); }

bool EnginePrototype::CKLBUIList::setItemMode(s32 mode,EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* dynamicCallback)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _sm_dynamicCallback$(dynamicCallback);
        return _ext_CKLBUIList_cmdSetItemMode(EnginePrototype::GameObject::_acc_gCppObject$(),(s32)mode);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::setItemMode$(s32 mode,EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* dynamicCallback) { CHCKTHIS; return setItemMode(mode,dynamicCallback); }

s32 EnginePrototype::CKLBUIList::setPosition(s32 pos,s32 dir)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdSetPosition(EnginePrototype::GameObject::_acc_gCppObject$(),pos,dir);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::setPosition$(s32 pos,s32 dir) { CHCKTHIS; return setPosition(pos,dir); }

void EnginePrototype::CKLBUIList::setGroup(System::String* groupName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetGroup(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(groupName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setGroup$(System::String* groupName) { CHCKTHIS; return setGroup(groupName); }

void EnginePrototype::CKLBUIList::setClip(u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_cmdSetClip(EnginePrototype::GameObject::_acc_gCppObject$(),orderBegin,orderEnd,clipX,clipY,clipWidth,clipHeight);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setClip$(u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight) { CHCKTHIS; return setClip(orderBegin,orderEnd,clipX,clipY,clipWidth,clipHeight); }

void EnginePrototype::CKLBUIList::setDragRect(s32 left,s32 top,s32 right,s32 bottom)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setDragRect(EnginePrototype::GameObject::_acc_gCppObject$(),left,top,right,bottom);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIList::setDragRect$(s32 left,s32 top,s32 right,s32 bottom) { CHCKTHIS; return setDragRect(left,top,right,bottom); }

inline EnginePrototype::_Delegate_Base_LimitCallBack_inner40* EnginePrototype::CKLBUIList::_sm_limitCallback(EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _$value)  { return (EnginePrototype::_Delegate_Base_LimitCallBack_inner40*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_limitCallback,_$value); }
inline EnginePrototype::_Delegate_Base_LimitCallBack_inner40* EnginePrototype::CKLBUIList::_sm_limitCallback$(EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _$value) { CHCKTHIS; return _sm_limitCallback(_$value); }
inline EnginePrototype::_Delegate_Base_DragCallBack_inner41* EnginePrototype::CKLBUIList::_sm_dragCallback(EnginePrototype::_Delegate_Base_DragCallBack_inner41* _$value)  { return (EnginePrototype::_Delegate_Base_DragCallBack_inner41*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_dragCallback,_$value); }
inline EnginePrototype::_Delegate_Base_DragCallBack_inner41* EnginePrototype::CKLBUIList::_sm_dragCallback$(EnginePrototype::_Delegate_Base_DragCallBack_inner41* _$value) { CHCKTHIS; return _sm_dragCallback(_$value); }
inline EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* EnginePrototype::CKLBUIList::_sm_dynamicCallback(EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _$value)  { return (EnginePrototype::_Delegate_Base_DynamicCallBack_inner42*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_dynamicCallback,_$value); }
inline EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* EnginePrototype::CKLBUIList::_sm_dynamicCallback$(EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _$value) { CHCKTHIS; return _sm_dynamicCallback(_$value); }
inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* EnginePrototype::CKLBUIList::_sm_scrollbarCallback(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _$value)  { return (EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_scrollbarCallback,_$value); }
inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* EnginePrototype::CKLBUIList::_sm_scrollbarCallback$(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _$value) { CHCKTHIS; return _sm_scrollbarCallback(_$value); }
inline EnginePrototype::_Delegate_Base_AnimCallBack_inner44* EnginePrototype::CKLBUIList::_sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _$value)  { return (EnginePrototype::_Delegate_Base_AnimCallBack_inner44*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_animCallback,_$value); }
inline EnginePrototype::_Delegate_Base_AnimCallBack_inner44* EnginePrototype::CKLBUIList::_sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _$value) { CHCKTHIS; return _sm_animCallback(_$value); }


inline u32 EnginePrototype::CKLBUIList::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIList::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline u32 EnginePrototype::CKLBUIList::_acc_sWidth(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIList::_acc_sWidth$(u32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline u32 EnginePrototype::CKLBUIList::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIList::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline u32 EnginePrototype::CKLBUIList::_acc_sHeight(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIList::_acc_sHeight$(u32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline s32 EnginePrototype::CKLBUIList::_acc_gStepX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getStepX(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gStepX$() { CHCKTHIS; return _acc_gStepX(); }

inline s32 EnginePrototype::CKLBUIList::_acc_sStepX(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setStepX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIList::_acc_sStepX$(s32 value)		{ CHCKTHIS; return _acc_sStepX(value); }
inline s32 EnginePrototype::CKLBUIList::_acc_gStepY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getStepY(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gStepY$() { CHCKTHIS; return _acc_gStepY(); }

inline s32 EnginePrototype::CKLBUIList::_acc_sStepY(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setStepY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIList::_acc_sStepY$(s32 value)		{ CHCKTHIS; return _acc_sStepY(value); }
inline u32 EnginePrototype::CKLBUIList::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIList::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIList::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIList::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUIList::_acc_gMaxodr(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getMaxOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIList::_acc_gMaxodr$() { CHCKTHIS; return _acc_gMaxodr(); }

inline u32 EnginePrototype::CKLBUIList::_acc_sMaxodr(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setMaxOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIList::_acc_sMaxodr$(u32 value)		{ CHCKTHIS; return _acc_sMaxodr(value); }
inline bool EnginePrototype::CKLBUIList::_acc_gIsVertical(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getVertical(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::_acc_gIsVertical$() { CHCKTHIS; return _acc_gIsVertical(); }

inline bool EnginePrototype::CKLBUIList::_acc_sIsVertical(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setVertical(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIList::_acc_sIsVertical$(bool value)		{ CHCKTHIS; return _acc_sIsVertical(value); }
inline u32 EnginePrototype::CKLBUIList::_acc_gItems(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getItems(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIList::_acc_gItems$() { CHCKTHIS; return _acc_gItems(); }

inline s32 EnginePrototype::CKLBUIList::_acc_gMarginTop(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getMarginTop(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gMarginTop$() { CHCKTHIS; return _acc_gMarginTop(); }

inline s32 EnginePrototype::CKLBUIList::_acc_sMarginTop(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setMarginTop(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIList::_acc_sMarginTop$(s32 value)		{ CHCKTHIS; return _acc_sMarginTop(value); }
inline s32 EnginePrototype::CKLBUIList::_acc_gMarginBottom(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getMarginBottom(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gMarginBottom$() { CHCKTHIS; return _acc_gMarginBottom(); }

inline s32 EnginePrototype::CKLBUIList::_acc_sMarginBottom(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setMarginBottom(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIList::_acc_sMarginBottom$(s32 value)		{ CHCKTHIS; return _acc_sMarginBottom(value); }
inline bool EnginePrototype::CKLBUIList::_acc_gDefaultScroll(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_getDefaultScroll(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIList::_acc_gDefaultScroll$() { CHCKTHIS; return _acc_gDefaultScroll(); }

inline bool EnginePrototype::CKLBUIList::_acc_sDefaultScroll(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setDefaultScroll(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIList::_acc_sDefaultScroll$(bool value)		{ CHCKTHIS; return _acc_sDefaultScroll(value); }
inline s32 EnginePrototype::CKLBUIList::_acc_gPosition(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdGetPosition(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gPosition$() { CHCKTHIS; return _acc_gPosition(); }

inline s32 EnginePrototype::CKLBUIList::_acc_gLimit(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIList_cmdGetLimit(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIList::_acc_gLimit$() { CHCKTHIS; return _acc_gLimit(); }

inline bool EnginePrototype::CKLBUIList::_acc_gLoopMode(){
    THROW(CS_NEW EnginePrototype::CKLBExceptionNotImplemented(_$_cteStr1Obj));
}

inline bool EnginePrototype::CKLBUIList::_acc_gLoopMode$() { CHCKTHIS; return _acc_gLoopMode(); }

inline bool EnginePrototype::CKLBUIList::_acc_sLoopMode(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIList_setLoop(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIList::_acc_sLoopMode$(bool value)		{ CHCKTHIS; return _acc_sLoopMode(value); }
/*virtual*/
bool EnginePrototype::CKLBUIList::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIList,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIList::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_limitCallback) { System::Memory::pushList(m_limitCallback,0); }
    if (m_dragCallback) { System::Memory::pushList(m_dragCallback,0); }
    if (m_dynamicCallback) { System::Memory::pushList(m_dynamicCallback,0); }
    if (m_scrollbarCallback) { System::Memory::pushList(m_scrollbarCallback,0); }
    if (m_animCallback) { System::Memory::pushList(m_animCallback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIList::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_limitCallback && !m_limitCallback->isFreed()) { m_limitCallback->_removeRef((System::__GCObject**)&m_limitCallback); }
    if (m_dragCallback && !m_dragCallback->isFreed()) { m_dragCallback->_removeRef((System::__GCObject**)&m_dragCallback); }
    if (m_dynamicCallback && !m_dynamicCallback->isFreed()) { m_dynamicCallback->_removeRef((System::__GCObject**)&m_dynamicCallback); }
    if (m_scrollbarCallback && !m_scrollbarCallback->isFreed()) { m_scrollbarCallback->_removeRef((System::__GCObject**)&m_scrollbarCallback); }
    if (m_animCallback && !m_animCallback->isFreed()) { m_animCallback->_removeRef((System::__GCObject**)&m_animCallback); }
}
/*virtual*/
void EnginePrototype::CKLBUIList::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_limitCallback) {
      newPtr = (u8*)(&m_limitCallback); oldPtr = newPtr - offset;
      m_limitCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_dragCallback) {
      newPtr = (u8*)(&m_dragCallback); oldPtr = newPtr - offset;
      m_dragCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_dynamicCallback) {
      newPtr = (u8*)(&m_dynamicCallback); oldPtr = newPtr - offset;
      m_dynamicCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_scrollbarCallback) {
      newPtr = (u8*)(&m_scrollbarCallback); oldPtr = newPtr - offset;
      m_scrollbarCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
    if (m_animCallback) {
      newPtr = (u8*)(&m_animCallback); oldPtr = newPtr - offset;
      m_animCallback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIMoviePlayer'
//=============================

void EnginePrototype::CKLBUIMoviePlayer::_ctor_CKLBUIMoviePlayer() {
}

/*static*/
s32* EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_create(s32* pParent,bool mode,float x,float y,float width,float height,s32* url)
{
    return CKLBUIMoviePlayer_create(pParent,mode,x,y,width,height,url);
}

/*static*/
u32 EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_getWidth(s32* p)
{
    return CKLBUIMoviePlayer_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_setWidth(s32* p,u32 width)
{
    CKLBUIMoviePlayer_setWidth(p,width);
}

/*static*/
u32 EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_getHeight(s32* p)
{
    return CKLBUIMoviePlayer_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_setHeight(s32* p,u32 height)
{
    CKLBUIMoviePlayer_setHeight(p,height);
}

/*static*/
s32* EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_getText(s32* p)
{
    return CKLBUIMoviePlayer_getText(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_setText(s32* p,s32* text)
{
    CKLBUIMoviePlayer_setText(p,text);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_moviePlay(s32* p)
{
    CKLBUIMoviePlayer_moviePlay(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_movieStop(s32* p)
{
    CKLBUIMoviePlayer_movieStop(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_moviePause(s32* p)
{
    CKLBUIMoviePlayer_moviePause(p);
}

/*static*/
void EnginePrototype::CKLBUIMoviePlayer::_ext_CKLBUIMoviePlayer_movieResume(s32* p)
{
    CKLBUIMoviePlayer_movieResume(p);
}

EnginePrototype::CKLBUIMoviePlayer::CKLBUIMoviePlayer(EnginePrototype::CKLBUITask* parent,bool background_mode,float x,float y,float width,float height,EnginePrototype::_Delegate_Base_CallBack_inner45* callback,System::String* url) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIMoviePlayer();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIMoviePlayer_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),background_mode,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(url));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUIMoviePlayer::CKLBUIMoviePlayer() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIMoviePlayer();
}

/*virtual*/
void EnginePrototype::CKLBUIMoviePlayer::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerV_inner0<CKLBUIMoviePlayer>(this,&CKLBUIMoviePlayer::callBackFunction),0);
}

inline void EnginePrototype::CKLBUIMoviePlayer::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIMoviePlayer::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner45*)anyDelegate);
}

inline void EnginePrototype::CKLBUIMoviePlayer::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIMoviePlayer::callBackFunction()
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIMoviePlayer::callBackFunction$() { CHCKTHIS; return callBackFunction(); }

void EnginePrototype::CKLBUIMoviePlayer::getSize(EnginePrototype::USize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIMoviePlayer_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIMoviePlayer_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::getSize$(EnginePrototype::USize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIMoviePlayer::setSize(EnginePrototype::USize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIMoviePlayer_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIMoviePlayer_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::setSize$(EnginePrototype::USize size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIMoviePlayer::setSize(u32 width,u32 height)
{
    _ext_CKLBUIMoviePlayer_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
    _ext_CKLBUIMoviePlayer_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
}

inline void EnginePrototype::CKLBUIMoviePlayer::setSize$(u32 width,u32 height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIMoviePlayer::play()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_moviePlay(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::play$() { CHCKTHIS; return play(); }

void EnginePrototype::CKLBUIMoviePlayer::pause()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_moviePause(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::pause$() { CHCKTHIS; return pause(); }

void EnginePrototype::CKLBUIMoviePlayer::stop()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_movieStop(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::stop$() { CHCKTHIS; return stop(); }

void EnginePrototype::CKLBUIMoviePlayer::resume()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_movieResume(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIMoviePlayer::resume$() { CHCKTHIS; return resume(); }

inline EnginePrototype::_Delegate_Base_CallBack_inner45* EnginePrototype::CKLBUIMoviePlayer::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner45* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner45*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner45* EnginePrototype::CKLBUIMoviePlayer::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner45* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIMoviePlayer_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_sWidth(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_sWidth$(u32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIMoviePlayer_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_sHeight(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIMoviePlayer::_acc_sHeight$(u32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline System::String* EnginePrototype::CKLBUIMoviePlayer::_acc_gPath(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIMoviePlayer_getText(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIMoviePlayer::_acc_gPath$() { CHCKTHIS; return _acc_gPath(); }

inline System::String* EnginePrototype::CKLBUIMoviePlayer::_acc_sPath(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIMoviePlayer_setText(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIMoviePlayer::_acc_sPath$(System::String* value)		{ CHCKTHIS; return _acc_sPath(value); }
/*virtual*/
bool EnginePrototype::CKLBUIMoviePlayer::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIMoviePlayer,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIMoviePlayer::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIMoviePlayer::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIMoviePlayer::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIMultiImgItem'
//=============================

void EnginePrototype::CKLBUIMultiImgItem::_ctor_CKLBUIMultiImgItem() {
}

/*static*/
s32* EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_create(s32* pParent,u32 order,float x,float y,u32 idx,System::Array<s32*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 assetCount)
{
    return CKLBUIMultiImgItem_create(pParent,order,x,y,idx,pArrayAsset ? (s32**)pArrayAsset->_getPArray() : NULL,pArrayIndexes ? (u32*)pArrayIndexes->_getPArray() : NULL,assetCount);
}

/*static*/
u32 EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_getIndexMax(s32* p)
{
    return CKLBUIMultiImgItem_getIndexMax(p);
}

/*static*/
void EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_setIndexMax(s32* p,u32 index)
{
    CKLBUIMultiImgItem_setIndexMax(p,index);
}

/*static*/
u32 EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_getOrder(s32* p)
{
    return CKLBUIMultiImgItem_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_setOrder(s32* p,u32 order)
{
    CKLBUIMultiImgItem_setOrder(p,order);
}

/*static*/
u32 EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_getIndex(s32* p)
{
    return CKLBUIMultiImgItem_getIndex(p);
}

/*static*/
void EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_setIndex(s32* p,u32 index)
{
    CKLBUIMultiImgItem_setIndex(p,index);
}

/*static*/
bool EnginePrototype::CKLBUIMultiImgItem::_ext_CKLBUIMultiImgItem_changeAssets(s32* p,System::Array<s32*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 assetCount)
{
    return CKLBUIMultiImgItem_changeAssets(p,pArrayAsset ? (s32**)pArrayAsset->_getPArray() : NULL,pArrayIndexes ? (u32*)pArrayIndexes->_getPArray() : NULL,assetCount);
}

EnginePrototype::CKLBUIMultiImgItem::CKLBUIMultiImgItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 index) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIMultiImgItem();
    if (pArrayAsset->_acc_gLength$() != pArrayAsset->_acc_gLength$())
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr93Obj));
    }
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIMultiImgItem_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,index,System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(pArrayAsset,pArrayAsset->_acc_gLength$()),pArrayIndexes,(u32)pArrayAsset->_acc_gLength$());
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIMultiImgItem::CKLBUIMultiImgItem() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIMultiImgItem();
}

bool EnginePrototype::CKLBUIMultiImgItem::changeAssets(System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes)
{
    if (pArrayAsset->_acc_gLength$() != pArrayIndexes->_acc_gLength$())
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr94Obj));
    }
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        bool res = _ext_CKLBUIMultiImgItem_changeAssets(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(pArrayAsset,pArrayAsset->_acc_gLength$()),pArrayIndexes,(u32)pArrayAsset->_acc_gLength$());
        EnginePrototype::NativeManagement::intercepCppError();
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIMultiImgItem::changeAssets$(System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes) { CHCKTHIS; return changeAssets(pArrayAsset,pArrayIndexes); }



inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIMultiImgItem_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIMultiImgItem_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gIndex(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIMultiImgItem_getIndex(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gIndex$() { CHCKTHIS; return _acc_gIndex(); }

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sIndex(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIMultiImgItem_setIndex(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sIndex$(u32 value)		{ CHCKTHIS; return _acc_sIndex(value); }
inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gIdMax(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIMultiImgItem_getIndexMax(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_gIdMax$() { CHCKTHIS; return _acc_gIdMax(); }

inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sIdMax(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIMultiImgItem_setIndexMax(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIMultiImgItem::_acc_sIdMax$(u32 value)		{ CHCKTHIS; return _acc_sIdMax(value); }
/*virtual*/
bool EnginePrototype::CKLBUIMultiImgItem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIMultiImgItem,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIMultiImgItem::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIMultiImgItem::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIMultiImgItem::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIPieChart'
//=============================

void EnginePrototype::CKLBUIPieChart::_ctor_CKLBUIPieChart() {
}

/*static*/
s32* EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* asset,float start,float end,s32 anim,float initial)
{
    return CKLBUIPieChart_create(pParent,order,x,y,width,height,asset,start,end,anim,initial);
}

/*static*/
float EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_getStart(s32* p)
{
    return CKLBUIPieChart_getStart(p);
}

/*static*/
void EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_setStart(s32* p,float start)
{
    CKLBUIPieChart_setStart(p,start);
}

/*static*/
float EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_getEnd(s32* p)
{
    return CKLBUIPieChart_getEnd(p);
}

/*static*/
void EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_setEnd(s32* p,float end)
{
    CKLBUIPieChart_setEnd(p,end);
}

/*static*/
float EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_getValue(s32* p)
{
    return CKLBUIPieChart_getValue(p);
}

/*static*/
void EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_setValue(s32* p,float value)
{
    CKLBUIPieChart_setValue(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_getAnim(s32* p)
{
    return CKLBUIPieChart_getAnim(p);
}

/*static*/
u32 EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_getOrder(s32* p)
{
    return CKLBUIPieChart_getOrder(p);
}

/*static*/
bool EnginePrototype::CKLBUIPieChart::_ext_CKLBUIPieChart_changeAsset(s32* p,s32* assetName)
{
    return CKLBUIPieChart_changeAsset(p,assetName);
}

EnginePrototype::CKLBUIPieChart::CKLBUIPieChart(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* image_asset,float start_angle,float end_angle,s32 anim_time,float initial_value) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIPieChart();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIPieChart_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(image_asset),start_angle,end_angle,anim_time,initial_value);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIPieChart::CKLBUIPieChart() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIPieChart();
}

bool EnginePrototype::CKLBUIPieChart::changeAsset(System::String* assetName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        bool res = _ext_CKLBUIPieChart_changeAsset(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(assetName));
        EnginePrototype::NativeManagement::intercepCppError();
        return res;
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIPieChart::changeAsset$(System::String* assetName) { CHCKTHIS; return changeAsset(assetName); }



inline u32 EnginePrototype::CKLBUIPieChart::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPieChart_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIPieChart::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline float EnginePrototype::CKLBUIPieChart::_acc_gStart(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPieChart_getStart(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIPieChart::_acc_gStart$() { CHCKTHIS; return _acc_gStart(); }

inline float EnginePrototype::CKLBUIPieChart::_acc_sStart(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPieChart_setStart(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIPieChart::_acc_sStart$(float value)		{ CHCKTHIS; return _acc_sStart(value); }
inline float EnginePrototype::CKLBUIPieChart::_acc_gEnd(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPieChart_getEnd(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIPieChart::_acc_gEnd$() { CHCKTHIS; return _acc_gEnd(); }

inline float EnginePrototype::CKLBUIPieChart::_acc_sEnd(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPieChart_setEnd(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIPieChart::_acc_sEnd$(float value)		{ CHCKTHIS; return _acc_sEnd(value); }
inline float EnginePrototype::CKLBUIPieChart::_acc_gValue(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPieChart_getValue(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIPieChart::_acc_gValue$() { CHCKTHIS; return _acc_gValue(); }

inline float EnginePrototype::CKLBUIPieChart::_acc_sValue(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPieChart_setValue(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIPieChart::_acc_sValue$(float value)		{ CHCKTHIS; return _acc_sValue(value); }
inline s32 EnginePrototype::CKLBUIPieChart::_acc_gAnim(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPieChart_getAnim(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIPieChart::_acc_gAnim$() { CHCKTHIS; return _acc_gAnim(); }

/*virtual*/
bool EnginePrototype::CKLBUIPieChart::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIPieChart,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIPieChart::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIPieChart::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIPieChart::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIPolyline'
//=============================

void EnginePrototype::CKLBUIPolyline::_ctor_CKLBUIPolyline() {
}

/*static*/
s32* EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_create(s32* parent,u32 order,u32 maxPoint)
{
    return CKLBUIPolyline_create(parent,order,maxPoint);
}

/*static*/
u32 EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_getMaxPoint(s32* p)
{
    return CKLBUIPolyline_getMaxPoint(p);
}

/*static*/
void EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_setMaxPoint(s32* p,u32 maxpointcount)
{
    CKLBUIPolyline_setMaxPoint(p,maxpointcount);
}

/*static*/
u32 EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_getOrder(s32* p)
{
    return CKLBUIPolyline_getOrder(p);
}

/*static*/
u32 EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_getPointCount(s32* p)
{
    return CKLBUIPolyline_getPointCount(p);
}

/*static*/
void EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_setPointCount(s32* p,u32 pointcount)
{
    CKLBUIPolyline_setPointCount(p,pointcount);
}

/*static*/
void EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_setPoint(s32* p,u32 idx,float x,float y)
{
    CKLBUIPolyline_setPoint(p,idx,x,y);
}

/*static*/
u32 EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_getColor(s32* p)
{
    return CKLBUIPolyline_getColor(p);
}

/*static*/
void EnginePrototype::CKLBUIPolyline::_ext_CKLBUIPolyline_setColor(s32* p,u32 color)
{
    CKLBUIPolyline_setColor(p,color);
}

EnginePrototype::CKLBUIPolyline::CKLBUIPolyline(EnginePrototype::CKLBUITask* parent,u32 order,u32 maxPoint) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIPolyline();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIPolyline_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,maxPoint);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIPolyline::CKLBUIPolyline() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIPolyline();
}

void EnginePrototype::CKLBUIPolyline::setPoint(u32 point_index,float x,float y)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPolyline_setPoint(EnginePrototype::GameObject::_acc_gCppObject$(),point_index,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIPolyline::setPoint$(u32 point_index,float x,float y) { CHCKTHIS; return setPoint(point_index,x,y); }



inline u32 EnginePrototype::CKLBUIPolyline::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPolyline_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIPolyline::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIPolyline::_acc_gMaxPointCount(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPolyline_getMaxPoint(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIPolyline::_acc_gMaxPointCount$() { CHCKTHIS; return _acc_gMaxPointCount(); }

inline u32 EnginePrototype::CKLBUIPolyline::_acc_sMaxPointCount(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPolyline_setMaxPoint(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIPolyline::_acc_sMaxPointCount$(u32 value)		{ CHCKTHIS; return _acc_sMaxPointCount(value); }
inline u32 EnginePrototype::CKLBUIPolyline::_acc_gPointCount(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPolyline_getPointCount(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIPolyline::_acc_gPointCount$() { CHCKTHIS; return _acc_gPointCount(); }

inline u32 EnginePrototype::CKLBUIPolyline::_acc_sPointCount(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        if (value > 0)
        {
            _ext_CKLBUIPolyline_setPointCount(EnginePrototype::GameObject::_acc_gCppObject$(),value);
        }
        else
        {
            THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr97Obj));
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIPolyline::_acc_sPointCount$(u32 value)		{ CHCKTHIS; return _acc_sPointCount(value); }
inline u32 EnginePrototype::CKLBUIPolyline::_acc_gColor(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIPolyline_getColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIPolyline::_acc_gColor$() { CHCKTHIS; return _acc_gColor(); }

inline u32 EnginePrototype::CKLBUIPolyline::_acc_sColor(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIPolyline_setColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIPolyline::_acc_sColor$(u32 value)		{ CHCKTHIS; return _acc_sColor(value); }
/*virtual*/
bool EnginePrototype::CKLBUIPolyline::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIPolyline,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIPolyline::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIPolyline::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIPolyline::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIProgressBar'
//=============================

void EnginePrototype::CKLBUIProgressBar::_ctor_CKLBUIProgressBar() {
}

/*static*/
s32* EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* fullImage,s32* emptyImage,s32 startPix,s32 endPix,s32 anim,bool vert,s32* barfilterImage)
{
    return CKLBUIProgressBar_create(pParent,order,x,y,width,height,fullImage,emptyImage,startPix,endPix,anim,vert,barfilterImage);
}

/*static*/
u32 EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getOrder(s32* p)
{
    return CKLBUIProgressBar_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setOrder(s32* p,u32 order)
{
    CKLBUIProgressBar_setOrder(p,order);
}

/*static*/
float EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getWidth(s32* p)
{
    return CKLBUIProgressBar_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setWidth(s32* p,float width)
{
    CKLBUIProgressBar_setWidth(p,width);
}

/*static*/
float EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getHeight(s32* p)
{
    return CKLBUIProgressBar_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setHeight(s32* p,float height)
{
    CKLBUIProgressBar_setHeight(p,height);
}

/*static*/
bool EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getVertical(s32* p)
{
    return CKLBUIProgressBar_getVertical(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setVertical(s32* p,bool vertical)
{
    CKLBUIProgressBar_setVertical(p,vertical);
}

/*static*/
u32 EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getAnimTime(s32* p)
{
    return CKLBUIProgressBar_getAnimTime(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setAnimTime(s32* p,u32 time)
{
    CKLBUIProgressBar_setAnimTime(p,time);
}

/*static*/
float EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getStart(s32* p)
{
    return CKLBUIProgressBar_getStart(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setStart(s32* p,float start)
{
    CKLBUIProgressBar_setStart(p,start);
}

/*static*/
float EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getEnd(s32* p)
{
    return CKLBUIProgressBar_getEnd(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setEnd(s32* p,float end)
{
    CKLBUIProgressBar_setEnd(p,end);
}

/*static*/
float EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getValue(s32* p)
{
    return CKLBUIProgressBar_getValue(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setValue(s32* p,float value)
{
    CKLBUIProgressBar_setValue(p,value);
}

/*static*/
s32* EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getImgEmpty(s32* p)
{
    return CKLBUIProgressBar_getImgEmpty(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setImgEmpty(s32* p,s32* imageEmpty)
{
    CKLBUIProgressBar_setImgEmpty(p,imageEmpty);
}

/*static*/
s32* EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getImgFull(s32* p)
{
    return CKLBUIProgressBar_getImgFull(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setImgFull(s32* p,s32* imageFull)
{
    CKLBUIProgressBar_setImgFull(p,imageFull);
}

/*static*/
s32* EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getImgFilter(s32* p)
{
    return CKLBUIProgressBar_getImgFilter(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setImgFilter(s32* p,s32* imageFilter)
{
    CKLBUIProgressBar_setImgFilter(p,imageFilter);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_reset(s32* p)
{
    CKLBUIProgressBar_reset(p);
}

/*static*/
bool EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getFilterVisible(s32* p)
{
    return CKLBUIProgressBar_getFilterVisible(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setFilterVisible(s32* p,bool value)
{
    CKLBUIProgressBar_setFilterVisible(p,value);
}

/*static*/
u32 EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_getFilterColor(s32* p)
{
    return CKLBUIProgressBar_getFilterColor(p);
}

/*static*/
void EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setFilterColor(s32* p,u32 value)
{
    CKLBUIProgressBar_setFilterColor(p,value);
}

/*static*/
bool EnginePrototype::CKLBUIProgressBar::_ext_CKLBUIProgressBar_setFilterAnim(s32* p,bool bColAnim,u32 argb1,u32 argb2,u32 freq)
{
    return CKLBUIProgressBar_setFilterAnim(p,bColAnim,argb1,argb2,freq);
}

EnginePrototype::CKLBUIProgressBar::CKLBUIProgressBar(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* imageFull,System::String* imageEmpty,s32 startPix,s32 endPix,s32 animTime,bool verticalFlag,System::String* barfilterImage) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIProgressBar();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIProgressBar_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(imageFull),System::__MarshallingUtils::NativeUtf8FromString(imageEmpty),startPix,endPix,animTime,verticalFlag,System::__MarshallingUtils::NativeUtf8FromString(barfilterImage));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIProgressBar::CKLBUIProgressBar() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIProgressBar();
}

void EnginePrototype::CKLBUIProgressBar::getSize(EnginePrototype::FSize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIProgressBar_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIProgressBar_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIProgressBar::getSize$(EnginePrototype::FSize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIProgressBar::setSize(EnginePrototype::FSize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIProgressBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIProgressBar::setSize$(EnginePrototype::FSize size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIProgressBar::setSize(float width,float height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
        _ext_CKLBUIProgressBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIProgressBar::setSize$(float width,float height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIProgressBar::reset()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_reset(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIProgressBar::reset$() { CHCKTHIS; return reset(); }

void EnginePrototype::CKLBUIProgressBar::complete()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setValue(EnginePrototype::GameObject::_acc_gCppObject$(),_ext_CKLBUIProgressBar_getEnd(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIProgressBar::complete$() { CHCKTHIS; return complete(); }

bool EnginePrototype::CKLBUIProgressBar::setFilterAnim(bool bColAnim,u32 argb1,u32 argb2,u32 freq)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_setFilterAnim(EnginePrototype::GameObject::_acc_gCppObject$(),bColAnim,argb1,argb2,freq);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIProgressBar::setFilterAnim$(bool bColAnim,u32 argb1,u32 argb2,u32 freq) { CHCKTHIS; return setFilterAnim(bColAnim,argb1,argb2,freq); }



inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline float EnginePrototype::CKLBUIProgressBar::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIProgressBar::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline float EnginePrototype::CKLBUIProgressBar::_acc_sWidth(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIProgressBar::_acc_sWidth$(float value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline float EnginePrototype::CKLBUIProgressBar::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIProgressBar::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline float EnginePrototype::CKLBUIProgressBar::_acc_sHeight(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIProgressBar::_acc_sHeight$(float value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline bool EnginePrototype::CKLBUIProgressBar::_acc_gIsVertical(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getVertical(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIProgressBar::_acc_gIsVertical$() { CHCKTHIS; return _acc_gIsVertical(); }

inline bool EnginePrototype::CKLBUIProgressBar::_acc_sIsVertical(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setVertical(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIProgressBar::_acc_sIsVertical$(bool value)		{ CHCKTHIS; return _acc_sIsVertical(value); }
inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gAnimTime(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getAnimTime(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gAnimTime$() { CHCKTHIS; return _acc_gAnimTime(); }

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sAnimTime(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setAnimTime(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sAnimTime$(u32 value)		{ CHCKTHIS; return _acc_sAnimTime(value); }
inline float EnginePrototype::CKLBUIProgressBar::_acc_gStart(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getStart(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIProgressBar::_acc_gStart$() { CHCKTHIS; return _acc_gStart(); }

inline float EnginePrototype::CKLBUIProgressBar::_acc_sStart(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setStart(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIProgressBar::_acc_sStart$(float value)		{ CHCKTHIS; return _acc_sStart(value); }
inline float EnginePrototype::CKLBUIProgressBar::_acc_gEnd(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getEnd(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIProgressBar::_acc_gEnd$() { CHCKTHIS; return _acc_gEnd(); }

inline float EnginePrototype::CKLBUIProgressBar::_acc_sEnd(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setEnd(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIProgressBar::_acc_sEnd$(float value)		{ CHCKTHIS; return _acc_sEnd(value); }
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageEmpty(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIProgressBar_getImgEmpty(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageEmpty$() { CHCKTHIS; return _acc_gImageEmpty(); }

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageEmpty(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setImgEmpty(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageEmpty$(System::String* value)		{ CHCKTHIS; return _acc_sImageEmpty(value); }
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageFull(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIProgressBar_getImgFull(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageFull$() { CHCKTHIS; return _acc_gImageFull(); }

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageFull(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setImgFull(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageFull$(System::String* value)		{ CHCKTHIS; return _acc_sImageFull(value); }
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageFilter(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIProgressBar_getImgFilter(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_gImageFilter$() { CHCKTHIS; return _acc_gImageFilter(); }

inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageFilter(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setImgFilter(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIProgressBar::_acc_sImageFilter$(System::String* value)		{ CHCKTHIS; return _acc_sImageFilter(value); }
inline float EnginePrototype::CKLBUIProgressBar::_acc_gValue(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getValue(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIProgressBar::_acc_gValue$() { CHCKTHIS; return _acc_gValue(); }

inline float EnginePrototype::CKLBUIProgressBar::_acc_sValue(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setValue(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIProgressBar::_acc_sValue$(float value)		{ CHCKTHIS; return _acc_sValue(value); }
inline bool EnginePrototype::CKLBUIProgressBar::_acc_gFilterVisible(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getFilterVisible(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIProgressBar::_acc_gFilterVisible$() { CHCKTHIS; return _acc_gFilterVisible(); }

inline bool EnginePrototype::CKLBUIProgressBar::_acc_sFilterVisible(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setFilterVisible(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIProgressBar::_acc_sFilterVisible$(bool value)		{ CHCKTHIS; return _acc_sFilterVisible(value); }
inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gFilterColor(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIProgressBar_getFilterColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_gFilterColor$() { CHCKTHIS; return _acc_gFilterColor(); }

inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sFilterColor(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIProgressBar_setFilterColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIProgressBar::_acc_sFilterColor$(u32 value)		{ CHCKTHIS; return _acc_sFilterColor(value); }
/*virtual*/
bool EnginePrototype::CKLBUIProgressBar::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIProgressBar,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIProgressBar::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIProgressBar::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIProgressBar::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIRubberBand'
//=============================

void EnginePrototype::CKLBUIRubberBand::_ctor_CKLBUIRubberBand() {
}

/*static*/
s32* EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_create(s32* pParent,u32 order,float x,float y,u32 resolution,s32* origin,s32* joint,s32* point,u32 flags,u32 animTime,s32 joint_order_off,s32 point_order_off,bool rot_origin,bool rot_joint,bool rot_point)
{
    return CKLBUIRubberBand_create(pParent,order,x,y,resolution,origin,joint,point,flags,animTime,joint_order_off,point_order_off,rot_origin,rot_joint,rot_point);
}

/*static*/
float EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getOriginX(s32* p)
{
    return CKLBUIRubberBand_getOriginX(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setOriginX(s32* p,float x)
{
    CKLBUIRubberBand_setOriginX(p,x);
}

/*static*/
float EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getOriginY(s32* p)
{
    return CKLBUIRubberBand_getOriginY(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setOriginY(s32* p,float y)
{
    CKLBUIRubberBand_setOriginY(p,y);
}

/*static*/
float EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getPointX(s32* p)
{
    return CKLBUIRubberBand_getPointX(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setPointX(s32* p,float x)
{
    CKLBUIRubberBand_setPointX(p,x);
}

/*static*/
float EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getPointY(s32* p)
{
    return CKLBUIRubberBand_getPointY(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setPointY(s32* p,float y)
{
    CKLBUIRubberBand_setPointY(p,y);
}

/*static*/
bool EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getFAnim(s32* p)
{
    return CKLBUIRubberBand_getFAnim(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setFAnim(s32* p,bool fAnim)
{
    CKLBUIRubberBand_setFAnim(p,fAnim);
}

/*static*/
bool EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getFAnimRT(s32* p)
{
    return CKLBUIRubberBand_getFAnimRT(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setFAnimRT(s32* p,bool fAnimRT)
{
    CKLBUIRubberBand_setFAnimRT(p,fAnimRT);
}

/*static*/
u32 EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getAnimTime(s32* p)
{
    return CKLBUIRubberBand_getAnimTime(p);
}

/*static*/
void EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setAnimTime(s32* p,u32 animTime)
{
    CKLBUIRubberBand_setAnimTime(p,animTime);
}

/*static*/
u32 EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getOrder(s32* p)
{
    return CKLBUIRubberBand_getOrder(p);
}

/*static*/
s32* EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getAssetOrigin(s32* p)
{
    return CKLBUIRubberBand_getAssetOrigin(p);
}

/*static*/
s32* EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getAssetJoint(s32* p)
{
    return CKLBUIRubberBand_getAssetJoint(p);
}

/*static*/
s32* EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_getAssetPoint(s32* p)
{
    return CKLBUIRubberBand_getAssetPoint(p);
}

/*static*/
bool EnginePrototype::CKLBUIRubberBand::_ext_CKLBUIRubberBand_setOrder(s32* p,u32 orderOrigin,u32 orderJoint,u32 orderPoint)
{
    return CKLBUIRubberBand_setOrder(p,orderOrigin,orderJoint,orderPoint);
}

EnginePrototype::CKLBUIRubberBand::CKLBUIRubberBand(EnginePrototype::CKLBUITask* parent,u32 order,float origin_x,float origin_y,System::String* origin_asset,System::String* joint_asset,System::String* point_asset,u32 resolution,u32 option_flags,u32 animation_time,s32 joint_priority_offset,s32 point_priority_offset,bool rot_origin,bool rot_joint,bool rot_point) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIRubberBand();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIRubberBand_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,origin_x,origin_y,resolution,System::__MarshallingUtils::NativeUtf8FromString(origin_asset),System::__MarshallingUtils::NativeUtf8FromString(joint_asset),System::__MarshallingUtils::NativeUtf8FromString(point_asset),option_flags,animation_time,joint_priority_offset,point_priority_offset,rot_origin,rot_joint,rot_point);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIRubberBand::CKLBUIRubberBand() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIRubberBand();
}

void EnginePrototype::CKLBUIRubberBand::setOrder(u32 orderOrigin,u32 orderJoint,u32 orderPoint)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),orderOrigin,orderJoint,orderPoint);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIRubberBand::setOrder$(u32 orderOrigin,u32 orderJoint,u32 orderPoint) { CHCKTHIS; return setOrder(orderOrigin,orderJoint,orderPoint); }



inline u32 EnginePrototype::CKLBUIRubberBand::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIRubberBand::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetOrigin(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIRubberBand_getAssetOrigin(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetOrigin$() { CHCKTHIS; return _acc_gAssetOrigin(); }

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetJoint(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIRubberBand_getAssetJoint(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetJoint$() { CHCKTHIS; return _acc_gAssetJoint(); }

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetPoint(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIRubberBand_getAssetPoint(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIRubberBand::_acc_gAssetPoint$() { CHCKTHIS; return _acc_gAssetPoint(); }

inline float EnginePrototype::CKLBUIRubberBand::_acc_gOriginX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getOriginX(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline float EnginePrototype::CKLBUIRubberBand::_acc_gOriginX$() { CHCKTHIS; return _acc_gOriginX(); }

inline float EnginePrototype::CKLBUIRubberBand::_acc_sOriginX(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setOriginX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIRubberBand::_acc_sOriginX$(float value)		{ CHCKTHIS; return _acc_sOriginX(value); }
inline float EnginePrototype::CKLBUIRubberBand::_acc_gOriginY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getOriginY(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline float EnginePrototype::CKLBUIRubberBand::_acc_gOriginY$() { CHCKTHIS; return _acc_gOriginY(); }

inline float EnginePrototype::CKLBUIRubberBand::_acc_sOriginY(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setOriginY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIRubberBand::_acc_sOriginY$(float value)		{ CHCKTHIS; return _acc_sOriginY(value); }
inline float EnginePrototype::CKLBUIRubberBand::_acc_gPointX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getPointX(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline float EnginePrototype::CKLBUIRubberBand::_acc_gPointX$() { CHCKTHIS; return _acc_gPointX(); }

inline float EnginePrototype::CKLBUIRubberBand::_acc_sPointX(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setPointX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIRubberBand::_acc_sPointX$(float value)		{ CHCKTHIS; return _acc_sPointX(value); }
inline float EnginePrototype::CKLBUIRubberBand::_acc_gPointY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getPointY(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline float EnginePrototype::CKLBUIRubberBand::_acc_gPointY$() { CHCKTHIS; return _acc_gPointY(); }

inline float EnginePrototype::CKLBUIRubberBand::_acc_sPointY(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setPointY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIRubberBand::_acc_sPointY$(float value)		{ CHCKTHIS; return _acc_sPointY(value); }
inline bool EnginePrototype::CKLBUIRubberBand::_acc_gAnimFlag(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getFAnim(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline bool EnginePrototype::CKLBUIRubberBand::_acc_gAnimFlag$() { CHCKTHIS; return _acc_gAnimFlag(); }

inline bool EnginePrototype::CKLBUIRubberBand::_acc_sAnimFlag(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setFAnim(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIRubberBand::_acc_sAnimFlag$(bool value)		{ CHCKTHIS; return _acc_sAnimFlag(value); }
inline bool EnginePrototype::CKLBUIRubberBand::_acc_gRealTimeFlag(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getFAnimRT(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline bool EnginePrototype::CKLBUIRubberBand::_acc_gRealTimeFlag$() { CHCKTHIS; return _acc_gRealTimeFlag(); }

inline bool EnginePrototype::CKLBUIRubberBand::_acc_sRealTimeFlag(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setFAnimRT(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIRubberBand::_acc_sRealTimeFlag$(bool value)		{ CHCKTHIS; return _acc_sRealTimeFlag(value); }
inline u32 EnginePrototype::CKLBUIRubberBand::_acc_gAnimTime(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIRubberBand_getAnimTime(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUIRubberBand::_acc_gAnimTime$() { CHCKTHIS; return _acc_gAnimTime(); }

inline u32 EnginePrototype::CKLBUIRubberBand::_acc_sAnimTime(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIRubberBand_setAnimTime(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIRubberBand::_acc_sAnimTime$(u32 value)		{ CHCKTHIS; return _acc_sAnimTime(value); }
/*virtual*/
bool EnginePrototype::CKLBUIRubberBand::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIRubberBand,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIRubberBand::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIRubberBand::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIRubberBand::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIScale9'
//=============================

void EnginePrototype::CKLBUIScale9::_ctor_CKLBUIScale9() {
}

/*static*/
s32* EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_create(s32* pParent,u32 order,float x,float y,s32 width,s32 height,s32* asset)
{
    return CKLBUIScale9_create(pParent,order,x,y,width,height,asset);
}

/*static*/
s32 EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_getWidth(s32* p)
{
    return CKLBUIScale9_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_setWidth(s32* p,s32 width)
{
    CKLBUIScale9_setWidth(p,width);
}

/*static*/
s32 EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_getHeight(s32* p)
{
    return CKLBUIScale9_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_setHeight(s32* p,s32 height)
{
    CKLBUIScale9_setHeight(p,height);
}

/*static*/
u32 EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_getOrder(s32* p)
{
    return CKLBUIScale9_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_setOrder(s32* p,u32 order)
{
    CKLBUIScale9_setOrder(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_getAsset(s32* p)
{
    return CKLBUIScale9_getAsset(p);
}

/*static*/
bool EnginePrototype::CKLBUIScale9::_ext_CKLBUIScale9_setAsset(s32* p,s32* asset)
{
    return CKLBUIScale9_setAsset(p,asset);
}

EnginePrototype::CKLBUIScale9::CKLBUIScale9(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,s32 width,s32 height,System::String* asset) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScale9();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIScale9_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(asset));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIScale9::CKLBUIScale9() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScale9();
}

void EnginePrototype::CKLBUIScale9::getSize(EnginePrototype::Size& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIScale9_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIScale9_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScale9::getSize$(EnginePrototype::Size& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIScale9::setSize(EnginePrototype::Size size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScale9_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIScale9_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScale9::setSize$(EnginePrototype::Size size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIScale9::setSize(s32 width,s32 height)
{
    _ext_CKLBUIScale9_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
    _ext_CKLBUIScale9_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
}

inline void EnginePrototype::CKLBUIScale9::setSize$(s32 width,s32 height) { CHCKTHIS; return setSize(width,height); }



inline u32 EnginePrototype::CKLBUIScale9::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScale9_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScale9::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIScale9::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScale9_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScale9::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline s32 EnginePrototype::CKLBUIScale9::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScale9_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScale9::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline s32 EnginePrototype::CKLBUIScale9::_acc_sWidth(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScale9_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScale9::_acc_sWidth$(s32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline s32 EnginePrototype::CKLBUIScale9::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScale9_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScale9::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline s32 EnginePrototype::CKLBUIScale9::_acc_sHeight(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScale9_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScale9::_acc_sHeight$(s32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline System::String* EnginePrototype::CKLBUIScale9::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIScale9_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIScale9::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

inline System::String* EnginePrototype::CKLBUIScale9::_acc_sAsset(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        _ext_CKLBUIScale9_setAsset(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
        EnginePrototype::NativeManagement::intercepCppError();
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIScale9::_acc_sAsset$(System::String* value)		{ CHCKTHIS; return _acc_sAsset(value); }
/*virtual*/
bool EnginePrototype::CKLBUIScale9::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIScale9,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIScale9::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIScale9::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIScale9::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'AnimationInfo'
//=============================

void EnginePrototype::AnimationInfo::_ctor_AnimationInfo() {
    m_mask = 0;
    _sm_internalArray(CS_NEW System::Array< float >(22));
}

void EnginePrototype::AnimationInfo::createAlphaAnimation(float start,float end)
{
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::A_COLOR));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::A_COLOR),start);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::A_COLOR) + 1,end);
}

inline void EnginePrototype::AnimationInfo::createAlphaAnimation$(float start,float end) { CHCKTHIS; return createAlphaAnimation(start,end); }

void EnginePrototype::AnimationInfo::createRGBAnimation(float RStart,float REnd,float GStart,float GEnd,float BStart,float BEnd)
{
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::R_COLOR));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::R_COLOR),RStart);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::R_COLOR) + 1,REnd);
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::G_COLOR));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::G_COLOR),GStart);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::G_COLOR) + 1,GEnd);
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::B_COLOR));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::R_COLOR),BStart);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::R_COLOR) + 1,BEnd);
}

inline void EnginePrototype::AnimationInfo::createRGBAnimation$(float RStart,float REnd,float GStart,float GEnd,float BStart,float BEnd) { CHCKTHIS; return createRGBAnimation(RStart,REnd,GStart,GEnd,BStart,BEnd); }

void EnginePrototype::AnimationInfo::createScaleAnimation(float start,float end)
{
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::SCALE_COORD));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::SCALE_COORD),start);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::SCALE_COORD) + 1,end);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::SCALE_COORD) + 2,start);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::SCALE_COORD) + 3,end);
}

inline void EnginePrototype::AnimationInfo::createScaleAnimation$(float start,float end) { CHCKTHIS; return createScaleAnimation(start,end); }

void EnginePrototype::AnimationInfo::createXOffsetAnimation(float start,float end)
{
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::X_COORD));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::X_COORD),start);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::X_COORD) + 1,end);
}

inline void EnginePrototype::AnimationInfo::createXOffsetAnimation$(float start,float end) { CHCKTHIS; return createXOffsetAnimation(start,end); }

void EnginePrototype::AnimationInfo::createYOffsetAnimation(float start,float end)
{
    _sm_mask$OrEq(ms_maskArr->_idx_g$((u32)EIDX::Y_COORD));
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::Y_COORD),start);
    _gm_internalArray$()->_idx_s$(ms_indexes->_idx_g$((s32)EIDX::Y_COORD) + 1,end);
}

inline void EnginePrototype::AnimationInfo::createYOffsetAnimation$(float start,float end) { CHCKTHIS; return createYOffsetAnimation(start,end); }

void EnginePrototype::AnimationInfo::_ref_getAnimInfo(u32& type,u32& affected,System::Array<float>*& arrayParam)
{
    affected = _gm_mask$();
    type = 1;
    arrayParam = CS_NEW System::Array< float >(22);
    s32 idx = 0;
    for (s32 i = 0;i <= (s32)EIDX::COUNT;++i)
    {
        u32 currentAnim = ms_maskArr->_idx_g$(i);
        if (((u32)_gm_mask$() & currentAnim) == currentAnim)
        {
            s32 currentIdx = ms_indexes->_idx_g$(i);
            arrayParam->_idx_s$(idx++,_gm_internalArray$()->_idx_g$(currentIdx));
            arrayParam->_idx_s$(idx++,_gm_internalArray$()->_idx_g$(currentIdx + 1));
            if (currentAnim == (u32)EIDX::SCALE_COORD)
            {
                arrayParam->_idx_s$(idx++,_gm_internalArray$()->_idx_g$(currentIdx + 2));
                arrayParam->_idx_s$(idx++,_gm_internalArray$()->_idx_g$(currentIdx + 3));
            }
        }
    }
}

inline void EnginePrototype::AnimationInfo::getAnimInfo$(u32& type,u32& affected,System::Array<float>*& arrayParam) { CHCKTHIS; return getAnimInfo(type,affected,arrayParam); }

inline void EnginePrototype::AnimationInfo::getAnimInfo(u32& type,u32& affected,System::Array<float>*& arrayParam) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); _ref_getAnimInfo(type,affected,arrayParam); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); }

EnginePrototype::AnimationInfo::AnimationInfo() { _ctor_AnimationInfo(); }

inline System::Array<u32>* EnginePrototype::AnimationInfo::_sms_maskArr(System::Array<u32>* _$value)		{ return (System::Array<u32>*)System::__GCObject::_RefSetValue((System::__GCObject**)&ms_maskArr,_$value); }
inline System::Array<s32>* EnginePrototype::AnimationInfo::_sms_indexes(System::Array<s32>* _$value)		{ return (System::Array<s32>*)System::__GCObject::_RefSetValue((System::__GCObject**)&ms_indexes,_$value); }
inline System::Array<float>* EnginePrototype::AnimationInfo::_sm_internalArray(System::Array<float>* _$value)  { return (System::Array<float>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_internalArray,_$value); }
inline System::Array<float>* EnginePrototype::AnimationInfo::_sm_internalArray$(System::Array<float>* _$value) { CHCKTHIS; return _sm_internalArray(_$value); }


/*virtual*/
bool EnginePrototype::AnimationInfo::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(AnimationInfo,System::Object);
}

/*virtual*/
u32 EnginePrototype::AnimationInfo::_processGC() {
    if (m_internalArray) { System::Memory::pushList(m_internalArray,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::AnimationInfo::_releaseGC() {
    if (m_internalArray && !m_internalArray->isFreed()) { m_internalArray->_removeRef((System::__GCObject**)&m_internalArray); }
}
/*virtual*/
void EnginePrototype::AnimationInfo::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_internalArray) {
      newPtr = (u8*)(&m_internalArray); oldPtr = newPtr - offset;
      m_internalArray->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIScore'
//=============================

void EnginePrototype::CKLBUIScore::_ctor_CKLBUIScore() {
}

/*static*/
s32* EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_create(s32* pParent,u32 order,s32 orderOffset,float x,float y,System::Array<s32*>* texTable,float stepX,float stepY,s32 column,bool fillZero,bool animFlags,u32 align,bool countClip)
{
    return CKLBUIScore_create(pParent,order,orderOffset,x,y,texTable ? (s32**)texTable->_getPArray() : NULL,stepX,stepY,column,fillZero,animFlags,align,countClip);
}

/*static*/
u32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getValue(s32* p)
{
    return CKLBUIScore_getValue(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setValue(s32* p,u32 value)
{
    CKLBUIScore_setValue(p,value);
}

/*static*/
u32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getOrder(s32* p)
{
    return CKLBUIScore_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setOrder(s32* p,u32 value)
{
    CKLBUIScore_setOrder(p,value);
}

/*static*/
u32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getOrderOffset(s32* p)
{
    return CKLBUIScore_getOrderOffset(p);
}

/*static*/
s32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getStepX(s32* p)
{
    return CKLBUIScore_getStepX(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setStepX(s32* p,s32 value)
{
    CKLBUIScore_setStepX(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getStepY(s32* p)
{
    return CKLBUIScore_getStepY(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setStepY(s32* p,s32 value)
{
    CKLBUIScore_setStepY(p,value);
}

/*static*/
u32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getColumn(s32* p)
{
    return CKLBUIScore_getColumn(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setColumn(s32* p,u32 value)
{
    CKLBUIScore_setColumn(p,value);
}

/*static*/
bool EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getFillZero(s32* p)
{
    return CKLBUIScore_getFillZero(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setFillZero(s32* p,bool value)
{
    CKLBUIScore_setFillZero(p,value);
}

/*static*/
bool EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getAnim(s32* p)
{
    return CKLBUIScore_getAnim(p);
}

/*static*/
s32 EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getAlign(s32* p)
{
    return CKLBUIScore_getAlign(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setAlign(s32* p,s32 align)
{
    CKLBUIScore_setAlign(p,align);
}

/*static*/
s32* EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getTextures(s32* p)
{
    return CKLBUIScore_getTextures(p);
}

/*static*/
bool EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_getCountClip(s32* p)
{
    return CKLBUIScore_getCountClip(p);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setCountClip(s32* p,bool value)
{
    CKLBUIScore_setCountClip(p,value);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setEnterAnimation(s32* p,u32 milliSecondsPlayTime,s32 timeShift,u32 type,u32 affected,System::Array<float>* arrayParam)
{
    CKLBUIScore_setEnterAnimation(p,milliSecondsPlayTime,timeShift,type,affected,arrayParam ? (float*)arrayParam->_getPArray() : NULL);
}

/*static*/
void EnginePrototype::CKLBUIScore::_ext_CKLBUIScore_setExitAnimation(s32* p,u32 milliSecondsPlayTime,s32 timeShift,u32 type,u32 affected,System::Array<float>* arrayParam)
{
    CKLBUIScore_setExitAnimation(p,milliSecondsPlayTime,timeShift,type,affected,arrayParam ? (float*)arrayParam->_getPArray() : NULL);
}

EnginePrototype::CKLBUIScore::CKLBUIScore(EnginePrototype::CKLBUITask* parent,u32 order,s32 orderOffset,float x,float y,System::Array<System::String*>* textureTable,float stepX,float stepY,s32 column,bool fillZeroFlag,bool animationFlag,s32 align,bool countClip) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScore();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIScore_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,orderOffset,x,y,System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(textureTable,textureTable->_acc_gLength$()),stepX,stepY,column,fillZeroFlag,animationFlag,(u32)align,countClip);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIScore::CKLBUIScore() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScore();
}

void EnginePrototype::CKLBUIScore::reset()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setValue(EnginePrototype::GameObject::_acc_gCppObject$(),0);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScore::reset$() { CHCKTHIS; return reset(); }

void EnginePrototype::CKLBUIScore::enterAnim(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        u32 type = 0;
        u32 affected = 0;
        System::Array<float>* param_array = NULL;
        if (animation != NULL)
        {
            animation->getAnimInfo$(type,affected,param_array);
        }
        _ext_CKLBUIScore_setEnterAnimation(EnginePrototype::GameObject::_acc_gCppObject$(),msPlayTime,timeShift,type,affected,param_array);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScore::enterAnim$(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift) { CHCKTHIS; return enterAnim(animation,msPlayTime,timeShift); }

void EnginePrototype::CKLBUIScore::exitAnim(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        u32 type = 0;
        u32 affected = 0;
        System::Array<float>* param_array = NULL;
        if (animation != NULL)
        {
            animation->getAnimInfo$(type,affected,param_array);
        }
        _ext_CKLBUIScore_setExitAnimation(EnginePrototype::GameObject::_acc_gCppObject$(),msPlayTime,timeShift,type,affected,param_array);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScore::exitAnim$(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift) { CHCKTHIS; return exitAnim(animation,msPlayTime,timeShift); }



inline u32 EnginePrototype::CKLBUIScore::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScore::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIScore::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScore::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUIScore::_acc_gOdoff(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getOrderOffset(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScore::_acc_gOdoff$() { CHCKTHIS; return _acc_gOdoff(); }

inline s32 EnginePrototype::CKLBUIScore::_acc_gStepX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getStepX(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScore::_acc_gStepX$() { CHCKTHIS; return _acc_gStepX(); }

inline s32 EnginePrototype::CKLBUIScore::_acc_sStepX(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setStepX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScore::_acc_sStepX$(s32 value)		{ CHCKTHIS; return _acc_sStepX(value); }
inline s32 EnginePrototype::CKLBUIScore::_acc_gStepY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getStepY(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScore::_acc_gStepY$() { CHCKTHIS; return _acc_gStepY(); }

inline s32 EnginePrototype::CKLBUIScore::_acc_sStepY(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setStepY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScore::_acc_sStepY$(s32 value)		{ CHCKTHIS; return _acc_sStepY(value); }
inline u32 EnginePrototype::CKLBUIScore::_acc_gCols(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getColumn(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScore::_acc_gCols$() { CHCKTHIS; return _acc_gCols(); }

inline u32 EnginePrototype::CKLBUIScore::_acc_sCols(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setColumn(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScore::_acc_sCols$(u32 value)		{ CHCKTHIS; return _acc_sCols(value); }
inline bool EnginePrototype::CKLBUIScore::_acc_gFillZero(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getFillZero(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIScore::_acc_gFillZero$() { CHCKTHIS; return _acc_gFillZero(); }

inline bool EnginePrototype::CKLBUIScore::_acc_sFillZero(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setFillZero(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIScore::_acc_sFillZero$(bool value)		{ CHCKTHIS; return _acc_sFillZero(value); }
inline bool EnginePrototype::CKLBUIScore::_acc_gIsAnim(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getAnim(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIScore::_acc_gIsAnim$() { CHCKTHIS; return _acc_gIsAnim(); }

inline u32 EnginePrototype::CKLBUIScore::_acc_gValue(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getValue(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScore::_acc_gValue$() { CHCKTHIS; return _acc_gValue(); }

inline u32 EnginePrototype::CKLBUIScore::_acc_sValue(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setValue(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScore::_acc_sValue$(u32 value)		{ CHCKTHIS; return _acc_sValue(value); }
inline s32 EnginePrototype::CKLBUIScore::_acc_gAlign(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return (EALIGN)_ext_CKLBUIScore_getAlign(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScore::_acc_gAlign$() { CHCKTHIS; return _acc_gAlign(); }

inline s32 EnginePrototype::CKLBUIScore::_acc_sAlign(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setAlign(EnginePrototype::GameObject::_acc_gCppObject$(),(s32)value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScore::_acc_sAlign$(s32 value)		{ CHCKTHIS; return _acc_sAlign(value); }
inline bool EnginePrototype::CKLBUIScore::_acc_gCountClip(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScore_getCountClip(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIScore::_acc_gCountClip$() { CHCKTHIS; return _acc_gCountClip(); }

inline bool EnginePrototype::CKLBUIScore::_acc_sCountClip(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScore_setCountClip(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIScore::_acc_sCountClip$(bool value)		{ CHCKTHIS; return _acc_sCountClip(value); }
inline System::Array<System::String*>* EnginePrototype::CKLBUIScore::_acc_gTextures(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringArrayFromNativeUtf8IntPtr(_ext_CKLBUIScore_getTextures(EnginePrototype::GameObject::_acc_gCppObject$()),10);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::Array<System::String*>* EnginePrototype::CKLBUIScore::_acc_gTextures$() { CHCKTHIS; return _acc_gTextures(); }

/*virtual*/
bool EnginePrototype::CKLBUIScore::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIScore,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIScore::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIScore::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIScore::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIScrollBar'
//=============================

void EnginePrototype::CKLBUIScrollBar::_ctor_CKLBUIScrollBar() {
}

/*static*/
s32* EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_create(s32* pParent,u32 order,float x,float y,float width,float height,s32 minValue,s32 maxValue,s32 pos,s32* image,s32 slider_size,s32 min_slider_size,u32 colorNormal,u32 colorSelect,bool vert,bool active,bool hideMode)
{
    return CKLBUIScrollBar_create(pParent,order,x,y,width,height,minValue,maxValue,pos,image,slider_size,min_slider_size,colorNormal,colorSelect,vert,active,hideMode);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getMin(s32* p)
{
    return CKLBUIScrollBar_getMin(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setMin(s32* p,s32 value)
{
    CKLBUIScrollBar_setMin(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getMax(s32* p)
{
    return CKLBUIScrollBar_getMax(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setMax(s32* p,s32 value)
{
    CKLBUIScrollBar_setMax(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getPos(s32* p)
{
    return CKLBUIScrollBar_getPos(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setPos(s32* p,s32 value)
{
    CKLBUIScrollBar_setPos(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getSliderSize(s32* p)
{
    return CKLBUIScrollBar_getSliderSize(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setSliderSize(s32* p,s32 value)
{
    CKLBUIScrollBar_setSliderSize(p,value);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getSliderSizeMin(s32* p)
{
    return CKLBUIScrollBar_getSliderSizeMin(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setSliderSizeMin(s32* p,s32 value)
{
    CKLBUIScrollBar_setSliderSizeMin(p,value);
}

/*static*/
bool EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getTouchActive(s32* p)
{
    return CKLBUIScrollBar_getTouchActive(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setTouchActive(s32* p,bool active)
{
    CKLBUIScrollBar_setTouchActive(p,active);
}

/*static*/
u32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getNormalColor(s32* p)
{
    return CKLBUIScrollBar_getNormalColor(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setNormalColor(s32* p,u32 color)
{
    CKLBUIScrollBar_setNormalColor(p,color);
}

/*static*/
u32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getActiveColor(s32* p)
{
    return CKLBUIScrollBar_getActiveColor(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setActiveColor(s32* p,u32 color)
{
    CKLBUIScrollBar_setActiveColor(p,color);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setMode(s32* p,u32 mode)
{
    CKLBUIScrollBar_setMode(p,mode);
}

/*static*/
bool EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getVertical(s32* p)
{
    return CKLBUIScrollBar_getVertical(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setVertical(s32* p,bool vertical)
{
    CKLBUIScrollBar_setVertical(p,vertical);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getWidth(s32* p)
{
    return CKLBUIScrollBar_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setWidth(s32* p,s32 width)
{
    CKLBUIScrollBar_setWidth(p,width);
}

/*static*/
s32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getHeight(s32* p)
{
    return CKLBUIScrollBar_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setHeight(s32* p,s32 height)
{
    CKLBUIScrollBar_setHeight(p,height);
}

/*static*/
u32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getOrder(s32* p)
{
    return CKLBUIScrollBar_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_setOrder(s32* p,u32 order)
{
    CKLBUIScrollBar_setOrder(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getImage(s32* p)
{
    return CKLBUIScrollBar_getImage(p);
}

/*static*/
u32 EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_getMode(s32* p)
{
    return CKLBUIScrollBar_getMode(p);
}

/*static*/
bool EnginePrototype::CKLBUIScrollBar::_ext_CKLBUIScrollBar_selectScrMgr(s32* p,s32* name,s32 len,System::Array<s32>* args)
{
    return CKLBUIScrollBar_selectScrMgr(p,name,len,args ? (s32*)args->_getPArray() : NULL);
}

EnginePrototype::CKLBUIScrollBar::CKLBUIScrollBar(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,s32 minValue,s32 maxValue,s32 pos,System::String* image,s32 sliderSize,s32 minSliderSize,u32 argbNormal,u32 argbSelect,bool vert,bool active,bool hideMode,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* callback) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScrollBar();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIScrollBar_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,width,height,minValue,maxValue,pos,System::__MarshallingUtils::NativeUtf8FromString(image),sliderSize,minSliderSize,argbNormal,argbSelect,vert,active,hideMode);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUIScrollBar::CKLBUIScrollBar() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIScrollBar();
}

/*virtual*/
void EnginePrototype::CKLBUIScrollBar::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUI_inner13<CKLBUIScrollBar>(this,&CKLBUIScrollBar::callBackFunction),3);
}

inline void EnginePrototype::CKLBUIScrollBar::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIScrollBar::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46*)anyDelegate);
}

inline void EnginePrototype::CKLBUIScrollBar::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIScrollBar::callBackFunction(u32 type,s32 pos)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,type,pos);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIScrollBar::callBackFunction$(u32 type,s32 pos) { CHCKTHIS; return callBackFunction(type,pos); }

void EnginePrototype::CKLBUIScrollBar::getSize(EnginePrototype::Size& size)
{
    size._swidth$(_ext_CKLBUIScrollBar_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
    size._sheight$(_ext_CKLBUIScrollBar_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
}

inline void EnginePrototype::CKLBUIScrollBar::getSize$(EnginePrototype::Size& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIScrollBar::setSize(EnginePrototype::Size size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIScrollBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScrollBar::setSize$(EnginePrototype::Size size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIScrollBar::setSize(s32 width,s32 height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
        _ext_CKLBUIScrollBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScrollBar::setSize$(s32 width,s32 height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIScrollBar::selectScrollManager(System::String* name,System::Array<s32>* args)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        if (args != NULL)
        {
            _ext_CKLBUIScrollBar_selectScrMgr(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(name),args->_acc_gLength$(),args);
        }
        else
        {
            _ext_CKLBUIScrollBar_selectScrMgr(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(name),0,(System::Array<s32>*)NULL);
        }
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIScrollBar::selectScrollManager$(System::String* name,System::Array<s32>* args) { CHCKTHIS; return selectScrollManager(name,args); }

inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* EnginePrototype::CKLBUIScrollBar::_sm_callback(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _$value)  { return (EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* EnginePrototype::CKLBUIScrollBar::_sm_callback$(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sWidth(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sWidth$(s32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sHeight(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sHeight$(s32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gStart(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getMin(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gStart$() { CHCKTHIS; return _acc_gStart(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sStart(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setMin(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sStart$(s32 value)		{ CHCKTHIS; return _acc_sStart(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gEnd(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getMax(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gEnd$() { CHCKTHIS; return _acc_gEnd(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sEnd(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setMax(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sEnd$(s32 value)		{ CHCKTHIS; return _acc_sEnd(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gPos(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getPos(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gPos$() { CHCKTHIS; return _acc_gPos(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sPos(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setPos(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sPos$(s32 value)		{ CHCKTHIS; return _acc_sPos(value); }
inline System::String* EnginePrototype::CKLBUIScrollBar::_acc_gImg(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIScrollBar_getImage(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIScrollBar::_acc_gImg$() { CHCKTHIS; return _acc_gImg(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gSliderSize(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getSliderSize(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gSliderSize$() { CHCKTHIS; return _acc_gSliderSize(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sSliderSize(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setSliderSize(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sSliderSize$(s32 value)		{ CHCKTHIS; return _acc_sSliderSize(value); }
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gSliderSizeMin(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getSliderSizeMin(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_gSliderSizeMin$() { CHCKTHIS; return _acc_gSliderSizeMin(); }

inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sSliderSizeMin(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setSliderSizeMin(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIScrollBar::_acc_sSliderSizeMin$(s32 value)		{ CHCKTHIS; return _acc_sSliderSizeMin(value); }
inline bool EnginePrototype::CKLBUIScrollBar::_acc_gIsVertical(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getVertical(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIScrollBar::_acc_gIsVertical$() { CHCKTHIS; return _acc_gIsVertical(); }

inline bool EnginePrototype::CKLBUIScrollBar::_acc_sIsVertical(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setVertical(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIScrollBar::_acc_sIsVertical$(bool value)		{ CHCKTHIS; return _acc_sIsVertical(value); }
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gArgbNormal(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getNormalColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gArgbNormal$() { CHCKTHIS; return _acc_gArgbNormal(); }

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sArgbNormal(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setNormalColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sArgbNormal$(u32 value)		{ CHCKTHIS; return _acc_sArgbNormal(value); }
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gArgbActive(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getActiveColor(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gArgbActive$() { CHCKTHIS; return _acc_gArgbActive(); }

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sArgbActive(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setActiveColor(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sArgbActive$(u32 value)		{ CHCKTHIS; return _acc_sArgbActive(value); }
inline bool EnginePrototype::CKLBUIScrollBar::_acc_gIsTouchActive(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getTouchActive(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIScrollBar::_acc_gIsTouchActive$() { CHCKTHIS; return _acc_gIsTouchActive(); }

inline bool EnginePrototype::CKLBUIScrollBar::_acc_sIsTouchActive(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setTouchActive(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIScrollBar::_acc_sIsTouchActive$(bool value)		{ CHCKTHIS; return _acc_sIsTouchActive(value); }
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gMode(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIScrollBar_getMode(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_gMode$() { CHCKTHIS; return _acc_gMode(); }

inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sMode(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIScrollBar_setMode(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIScrollBar::_acc_sMode$(u32 value)		{ CHCKTHIS; return _acc_sMode(value); }
/*virtual*/
bool EnginePrototype::CKLBUIScrollBar::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIScrollBar,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIScrollBar::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIScrollBar::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIScrollBar::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUISimpleItem'
//=============================

void EnginePrototype::CKLBUISimpleItem::_ctor_CKLBUISimpleItem() {
}

/*static*/
s32* EnginePrototype::CKLBUISimpleItem::_ext_CKLBUISimpleItem_create(s32* pParent,u32 order,float x,float y,s32* asset)
{
    return CKLBUISimpleItem_create(pParent,order,x,y,asset);
}

/*static*/
u32 EnginePrototype::CKLBUISimpleItem::_ext_CKLBUISimpleItem_getOrder(s32* p)
{
    return CKLBUISimpleItem_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUISimpleItem::_ext_CKLBUISimpleItem_setOrder(s32* p,u32 order)
{
    CKLBUISimpleItem_setOrder(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUISimpleItem::_ext_CKLBUISimpleItem_getAsset(s32* p)
{
    return CKLBUISimpleItem_getAsset(p);
}

EnginePrototype::CKLBUISimpleItem::CKLBUISimpleItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUISimpleItem();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUISimpleItem_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,System::__MarshallingUtils::NativeUtf8FromString(asset));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUISimpleItem::CKLBUISimpleItem() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUISimpleItem();
}



inline u32 EnginePrototype::CKLBUISimpleItem::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUISimpleItem_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUISimpleItem::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUISimpleItem::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUISimpleItem_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUISimpleItem::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUISimpleItem::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUISimpleItem_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUISimpleItem::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

/*virtual*/
bool EnginePrototype::CKLBUISimpleItem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUISimpleItem,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUISimpleItem::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUISimpleItem::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUISimpleItem::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUISWFPlayer'
//=============================

void EnginePrototype::CKLBUISWFPlayer::_ctor_CKLBUISWFPlayer() {
}

/*static*/
s32* EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_create(s32* parent,u32 order,float x,float y,s32* asset,s32* movieNameconst,System::Array<s32*>* replaceList,s32 assetCnt)
{
    return CKLBUISWFPlayer_create(parent,order,x,y,asset,movieNameconst,replaceList ? (s32**)replaceList->_getPArray() : NULL,assetCnt);
}

/*static*/
bool EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getPlay(s32* p)
{
    return CKLBUISWFPlayer_getPlay(p);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_setPlay(s32* p,bool play)
{
    CKLBUISWFPlayer_setPlay(p,play);
}

/*static*/
u32 EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getOrder(s32* p)
{
    return CKLBUISWFPlayer_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_setOrder(s32* p,u32 order)
{
    CKLBUISWFPlayer_setOrder(p,order);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_gotoFrame(s32* p,s32* label)
{
    CKLBUISWFPlayer_gotoFrame(p,label);
}

/*static*/
u32 EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getFrameRate(s32* p)
{
    return CKLBUISWFPlayer_getFrameRate(p);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_setFrameRate(s32* p,u32 fps)
{
    CKLBUISWFPlayer_setFrameRate(p,fps);
}

/*static*/
bool EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_isAnimating(s32* p)
{
    return CKLBUISWFPlayer_isAnimating(p);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_setFrameRateScale(s32* p,float scale)
{
    CKLBUISWFPlayer_setFrameRateScale(p,scale);
}

/*static*/
s32* EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getAsset(s32* p)
{
    return CKLBUISWFPlayer_getAsset(p);
}

/*static*/
s32* EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getMovieName(s32* p)
{
    return CKLBUISWFPlayer_getMovieName(p);
}

/*static*/
float EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_getVolume(s32* p)
{
    return CKLBUISWFPlayer_getVolume(p);
}

/*static*/
void EnginePrototype::CKLBUISWFPlayer::_ext_CKLBUISWFPlayer_setVolume(s32* p,float volume)
{
    CKLBUISWFPlayer_setVolume(p,volume);
}

EnginePrototype::CKLBUISWFPlayer::CKLBUISWFPlayer(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset,System::String* movieName,EnginePrototype::_Delegate_Base_CallBack_inner47* callback,System::Array<System::String*>* replaceList,s32 assetCnt) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUISWFPlayer();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUISWFPlayer_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,System::__MarshallingUtils::NativeUtf8FromString(asset),System::__MarshallingUtils::NativeUtf8FromString(movieName),((replaceList != NULL) ? System::__MarshallingUtils::NativeUtf8ArrayFromStringArray(replaceList,replaceList->_acc_gLength$()) : NULL),assetCnt);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUISWFPlayer::CKLBUISWFPlayer() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUISWFPlayer();
}

/*virtual*/
void EnginePrototype::CKLBUISWFPlayer::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerS_inner4<CKLBUISWFPlayer>(this,&CKLBUISWFPlayer::callBackFunction),0);
}

inline void EnginePrototype::CKLBUISWFPlayer::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUISWFPlayer::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner47*)anyDelegate);
}

inline void EnginePrototype::CKLBUISWFPlayer::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUISWFPlayer::callBackFunction(s32* label)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(label));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUISWFPlayer::callBackFunction$(s32* label) { CHCKTHIS; return callBackFunction(label); }

void EnginePrototype::CKLBUISWFPlayer::play()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setPlay(EnginePrototype::GameObject::_acc_gCppObject$(),true);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUISWFPlayer::play$() { CHCKTHIS; return play(); }

void EnginePrototype::CKLBUISWFPlayer::stop()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setPlay(EnginePrototype::GameObject::_acc_gCppObject$(),false);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUISWFPlayer::stop$() { CHCKTHIS; return stop(); }

void EnginePrototype::CKLBUISWFPlayer::goToFrame(System::String* label)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_gotoFrame(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(label));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUISWFPlayer::goToFrame$(System::String* label) { CHCKTHIS; return goToFrame(label); }

void EnginePrototype::CKLBUISWFPlayer::setFramerateScale(float scale)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setFrameRateScale(EnginePrototype::GameObject::_acc_gCppObject$(),scale);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUISWFPlayer::setFramerateScale$(float scale) { CHCKTHIS; return setFramerateScale(scale); }

inline EnginePrototype::_Delegate_Base_CallBack_inner47* EnginePrototype::CKLBUISWFPlayer::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner47* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner47*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner47* EnginePrototype::CKLBUISWFPlayer::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner47* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUISWFPlayer_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUISWFPlayer::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUISWFPlayer_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUISWFPlayer::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

inline System::String* EnginePrototype::CKLBUISWFPlayer::_acc_gMovieName(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUISWFPlayer_getMovieName(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUISWFPlayer::_acc_gMovieName$() { CHCKTHIS; return _acc_gMovieName(); }

inline bool EnginePrototype::CKLBUISWFPlayer::_acc_gIsPlaying(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUISWFPlayer_getPlay(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUISWFPlayer::_acc_gIsPlaying$() { CHCKTHIS; return _acc_gIsPlaying(); }

inline bool EnginePrototype::CKLBUISWFPlayer::_acc_sIsPlaying(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setPlay(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUISWFPlayer::_acc_sIsPlaying$(bool value)		{ CHCKTHIS; return _acc_sIsPlaying(value); }
inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_gFramerate(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUISWFPlayer_getFrameRate(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_gFramerate$() { CHCKTHIS; return _acc_gFramerate(); }

inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_sFramerate(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setFrameRate(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUISWFPlayer::_acc_sFramerate$(u32 value)		{ CHCKTHIS; return _acc_sFramerate(value); }
inline bool EnginePrototype::CKLBUISWFPlayer::_acc_gIsAnim(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUISWFPlayer_isAnimating(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUISWFPlayer::_acc_gIsAnim$() { CHCKTHIS; return _acc_gIsAnim(); }

inline float EnginePrototype::CKLBUISWFPlayer::_acc_gVolume(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUISWFPlayer_getVolume(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUISWFPlayer::_acc_gVolume$() { CHCKTHIS; return _acc_gVolume(); }

inline float EnginePrototype::CKLBUISWFPlayer::_acc_sVolume(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUISWFPlayer_setVolume(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUISWFPlayer::_acc_sVolume$(float value)		{ CHCKTHIS; return _acc_sVolume(value); }
/*virtual*/
bool EnginePrototype::CKLBUISWFPlayer::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUISWFPlayer,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUISWFPlayer::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUISWFPlayer::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUISWFPlayer::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUITask'
//=============================

void EnginePrototype::CKLBUITask::_ctor_CKLBUITask() {
}

/*static*/
bool EnginePrototype::CKLBUITask::_ext_CKLBUITask_getVisible(s32* p)
{
    return CKLBUITask_getVisible(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setVisible(s32* p,bool isVisible)
{
    CKLBUITask_setVisible(p,isVisible);
}

/*static*/
float EnginePrototype::CKLBUITask::_ext_CKLBUITask_getScaleX(s32* p)
{
    return CKLBUITask_getScaleX(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setScaleX(s32* p,float scaleX)
{
    CKLBUITask_setScaleX(p,scaleX);
}

/*static*/
float EnginePrototype::CKLBUITask::_ext_CKLBUITask_getScaleY(s32* p)
{
    return CKLBUITask_getScaleY(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setScaleY(s32* p,float scaleY)
{
    CKLBUITask_setScaleY(p,scaleY);
}

/*static*/
float EnginePrototype::CKLBUITask::_ext_CKLBUITask_getX(s32* p)
{
    return CKLBUITask_getX(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setX(s32* p,float x)
{
    CKLBUITask_setX(p,x);
}

/*static*/
float EnginePrototype::CKLBUITask::_ext_CKLBUITask_getY(s32* p)
{
    return CKLBUITask_getY(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setY(s32* p,float y)
{
    CKLBUITask_setY(p,y);
}

/*static*/
float EnginePrototype::CKLBUITask::_ext_CKLBUITask_getRotation(s32* p)
{
    return CKLBUITask_getRotation(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setRotation(s32* p,float rotation)
{
    CKLBUITask_setRotation(p,rotation);
}

/*static*/
u32 EnginePrototype::CKLBUITask::_ext_CKLBUITask_getArgb(s32* p)
{
    return CKLBUITask_getArgb(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setArgb(s32* p,u32 argb)
{
    CKLBUITask_setArgb(p,argb);
}

/*static*/
bool EnginePrototype::CKLBUITask::_ext_CKLBUITask_isAnim(s32* p)
{
    return CKLBUITask_isAnim(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_play(s32* p)
{
    CKLBUITask_play(p);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_stop(s32* p)
{
    CKLBUITask_stop(p);
}

/*static*/
bool EnginePrototype::CKLBUITask::_ext_CKLBUITask_setParamCount(s32* p,u32 splineCount,u32 maxKeyCount)
{
    return CKLBUITask_setParamCount(p,splineCount,maxKeyCount);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_setTarget(s32* p,u32 splineIndex,s32 targetParameter)
{
    CKLBUITask_setTarget(p,splineIndex,targetParameter);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_addKeys(s32* p,u32 splineIndex,u32 time,s32 value)
{
    CKLBUITask_addKeys(p,splineIndex,time,value);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_addKeysFixed(s32* p,u32 splineIndex,u32 time,s32 fixed16Value)
{
    CKLBUITask_addKeysFixed(p,splineIndex,time,fixed16Value);
}

/*static*/
void EnginePrototype::CKLBUITask::_ext_CKLBUITask_generateAnimation(s32* p)
{
    CKLBUITask_generateAnimation(p);
}

/*static*/
bool EnginePrototype::CKLBUITask::_ext_CKLBUITask_reconnect(s32* p,s32* nodeName)
{
    return CKLBUITask_reconnect(p,nodeName);
}

EnginePrototype::CKLBUITask::CKLBUITask(u32 classID) : EnginePrototype::CKLBTask(classID)
{
    _ctor_CKLBUITask();
}

EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::_ref_getIterator(EnginePrototype::NodeIterator*& nodeIterator)
{
    u32 counter = EnginePrototype::NativeManagement::getContextCounter();
    s32* node = EnginePrototype::NodeIterator::getNodeFromTask(this);
    nodeIterator = CS_NEW EnginePrototype::NodeIterator(counter,node);
    return nodeIterator;
}

inline EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::getIterator$(EnginePrototype::NodeIterator*& nodeIterator) { CHCKTHIS; return getIterator(nodeIterator); }

inline EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::getIterator(EnginePrototype::NodeIterator*& nodeIterator) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); EnginePrototype::NodeIterator* r = _ref_getIterator(nodeIterator); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::_ref_getIteratorFromName(System::String* name,EnginePrototype::NodeIterator*& nodeIterator)
{
    nodeIterator = getIterator$(nodeIterator);
    if (!nodeIterator->find$(name,false))
    {
        nodeIterator = NULL;
    }
    return nodeIterator;
}

inline EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::getIteratorFromName$(System::String* name,EnginePrototype::NodeIterator*& nodeIterator) { CHCKTHIS; return getIteratorFromName(name,nodeIterator); }

inline EnginePrototype::NodeIterator* EnginePrototype::CKLBUITask::getIteratorFromName(System::String* name,EnginePrototype::NodeIterator*& nodeIterator) { System::RefHolder _cs_refholder_loc_array[1]; u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array); EnginePrototype::NodeIterator* r = _ref_getIteratorFromName(name,nodeIterator); _refRemove_(_cs_count_refholder,_cs_refholder_loc_array); return r; }

void EnginePrototype::CKLBUITask::nodeReconnect(System::String* nodeName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_reconnect(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(nodeName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITask::nodeReconnect$(System::String* nodeName) { CHCKTHIS; return nodeReconnect(nodeName); }

void EnginePrototype::CKLBUITask::animationPlay()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_play(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITask::animationPlay$() { CHCKTHIS; return animationPlay(); }

void EnginePrototype::CKLBUITask::animationStop()
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_stop(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITask::animationStop$() { CHCKTHIS; return animationStop(); }

void EnginePrototype::CKLBUITask::setScale(float scaleX,float scaleY)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setScaleX(EnginePrototype::GameObject::_acc_gCppObject$(),scaleX);
        _ext_CKLBUITask_setScaleY(EnginePrototype::GameObject::_acc_gCppObject$(),scaleY);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITask::setScale$(float scaleX,float scaleY) { CHCKTHIS; return setScale(scaleX,scaleY); }

void EnginePrototype::CKLBUITask::setAnimSpline(EnginePrototype::AnimSpline_inner9* splineArray)
{
    u32 maxKeyCount = 0;
    for (s32 i = 0;i < splineArray->_acc_gSplines$()->_acc_gCount$();++i)
    {
        if (splineArray->_acc_gSplines$()->_idx_g$(i)->_acc_gKeyCount$() > maxKeyCount)
        {
            maxKeyCount = splineArray->_acc_gSplines$()->_idx_g$(i)->_acc_gKeyCount$();
        }
    }
    if (_ext_CKLBUITask_setParamCount(EnginePrototype::GameObject::_acc_gCppObject$(),(u32)splineArray->_acc_gSplines$()->_acc_gCount$(),maxKeyCount))
    {
        u32 splineIndex = 0;
        for (s32 i = 0;i < splineArray->_acc_gSplines$()->_acc_gCount$();++i)
        {
            _ext_CKLBUITask_setTarget(EnginePrototype::GameObject::_acc_gCppObject$(),splineIndex,splineArray->_acc_gSplines$()->_idx_g$(i)->_acc_gTargetType$());
            splineArray->_acc_gSplines$()->_idx_g$(i)->addKeys$(EnginePrototype::GameObject::_acc_gCppObject$(),splineIndex++);
        }
        _ext_CKLBUITask_generateAnimation(EnginePrototype::GameObject::_acc_gCppObject$());
    }
}

inline void EnginePrototype::CKLBUITask::setAnimSpline$(EnginePrototype::AnimSpline_inner9* splineArray) { CHCKTHIS; return setAnimSpline(splineArray); }

EnginePrototype::CKLBUITask::CKLBUITask() { _ctor_CKLBUITask(); }



inline float EnginePrototype::CKLBUITask::_acc_gScaleX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getScaleX(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUITask::_acc_gScaleX$() { CHCKTHIS; return _acc_gScaleX(); }

inline float EnginePrototype::CKLBUITask::_acc_sScaleX(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setScaleX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUITask::_acc_sScaleX$(float value)		{ CHCKTHIS; return _acc_sScaleX(value); }
inline float EnginePrototype::CKLBUITask::_acc_gScaleY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getScaleY(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUITask::_acc_gScaleY$() { CHCKTHIS; return _acc_gScaleY(); }

inline float EnginePrototype::CKLBUITask::_acc_sScaleY(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setScaleY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUITask::_acc_sScaleY$(float value)		{ CHCKTHIS; return _acc_sScaleY(value); }
inline float EnginePrototype::CKLBUITask::_acc_gRotation(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getRotation(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUITask::_acc_gRotation$() { CHCKTHIS; return _acc_gRotation(); }

inline float EnginePrototype::CKLBUITask::_acc_sRotation(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setRotation(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUITask::_acc_sRotation$(float value)		{ CHCKTHIS; return _acc_sRotation(value); }
inline float EnginePrototype::CKLBUITask::_acc_gX(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getX(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUITask::_acc_gX$() { CHCKTHIS; return _acc_gX(); }

inline float EnginePrototype::CKLBUITask::_acc_sX(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setX(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUITask::_acc_sX$(float value)		{ CHCKTHIS; return _acc_sX(value); }
inline float EnginePrototype::CKLBUITask::_acc_gY(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getY(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUITask::_acc_gY$() { CHCKTHIS; return _acc_gY(); }

inline float EnginePrototype::CKLBUITask::_acc_sY(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setY(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUITask::_acc_sY$(float value)		{ CHCKTHIS; return _acc_sY(value); }
inline bool EnginePrototype::CKLBUITask::_acc_gIsVisible(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getVisible(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUITask::_acc_gIsVisible$() { CHCKTHIS; return _acc_gIsVisible(); }

inline bool EnginePrototype::CKLBUITask::_acc_sIsVisible(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setVisible(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUITask::_acc_sIsVisible$(bool value)		{ CHCKTHIS; return _acc_sIsVisible(value); }
inline u32 EnginePrototype::CKLBUITask::_acc_gArgb(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_getArgb(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUITask::_acc_gArgb$() { CHCKTHIS; return _acc_gArgb(); }

inline u32 EnginePrototype::CKLBUITask::_acc_sArgb(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITask_setArgb(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUITask::_acc_sArgb$(u32 value)		{ CHCKTHIS; return _acc_sArgb(value); }
inline bool EnginePrototype::CKLBUITask::_acc_gIsNodeAnim(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITask_isAnim(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUITask::_acc_gIsNodeAnim$() { CHCKTHIS; return _acc_gIsNodeAnim(); }

/*virtual*/
bool EnginePrototype::CKLBUITask::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUITask,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBUITask::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUITask::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUITask::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

}

//=============================
// Implementation of 'Spline_inner4'
//=============================

void EnginePrototype::Spline_inner4::_ctor_Spline_inner4() {
}

EnginePrototype::Spline_inner4::Spline_inner4(s32 targetType)
{
    _ctor_Spline_inner4();
    _sm_targetType$(targetType);
}

inline void EnginePrototype::Spline_inner4::addKeyInt$(u32 time,s32 value) { CHCKTHIS; return addKeyInt(time,value); }

inline void EnginePrototype::Spline_inner4::addKeyFloat$(u32 time,float value) { CHCKTHIS; return addKeyFloat(time,value); }

inline void EnginePrototype::Spline_inner4::addKeys$(s32* p,u32 splineIndex) { CHCKTHIS; return addKeys(p,splineIndex); }

EnginePrototype::Spline_inner4::Spline_inner4() { _ctor_Spline_inner4(); }



inline s32 EnginePrototype::Spline_inner4::_acc_gTargetType(){
    return _gm_targetType$();
}

inline s32 EnginePrototype::Spline_inner4::_acc_gTargetType$() { CHCKTHIS; return _acc_gTargetType(); }

/*virtual*/
bool EnginePrototype::Spline_inner4::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Spline_inner4,System::Object);
}

/*virtual*/
u32 EnginePrototype::Spline_inner4::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::Spline_inner4::_releaseGC() {
}
/*virtual*/
void EnginePrototype::Spline_inner4::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'IntSpline_inner5'
//=============================

void EnginePrototype::IntSpline_inner5::_ctor_IntSpline_inner5() {
}

EnginePrototype::IntSpline_inner5::IntSpline_inner5(s32 targetType) : EnginePrototype::Spline_inner4(targetType)
{
    _ctor_IntSpline_inner5();
    _sm_points$(CS_NEW System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>());
}

/*virtual*/
void EnginePrototype::IntSpline_inner5::addKeyInt(u32 time,s32 value)
{
    if (value <= 32767)
    {
        _gm_points$()->Add$(CS_NEW EnginePrototype::IntPoint_inner6(time,(s16)value));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr105Obj));
    }
}

inline void EnginePrototype::IntSpline_inner5::addKeyInt$(u32 time,s32 value) { CHCKTHIS; return addKeyInt(time,value); }

/*virtual*/
void EnginePrototype::IntSpline_inner5::addKeyFloat(u32 time,float value)
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionForbiddenMethod(_$_cteStr2Obj));
}

inline void EnginePrototype::IntSpline_inner5::addKeyFloat$(u32 time,float value) { CHCKTHIS; return addKeyFloat(time,value); }

/*virtual*/
void EnginePrototype::IntSpline_inner5::addKeys(s32* p,u32 splineIndex)
{
    for (s32 i = 0;i < _gm_points$()->_acc_gCount$();++i)
    {
        EnginePrototype::CKLBUITask::_ext_CKLBUITask_addKeys(p,splineIndex,_gm_points$()->_idx_g$(i)->_acc_gTime$(),_gm_points$()->_idx_g$(i)->_acc_gValue$());
    }
}

inline void EnginePrototype::IntSpline_inner5::addKeys$(s32* p,u32 splineIndex) { CHCKTHIS; return addKeys(p,splineIndex); }

EnginePrototype::IntSpline_inner5::IntSpline_inner5() { _ctor_IntSpline_inner5(); }

inline System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* EnginePrototype::IntSpline_inner5::_sm_points(System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _$value)  { return (System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_points,_$value); }
inline System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* EnginePrototype::IntSpline_inner5::_sm_points$(System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _$value) { CHCKTHIS; return _sm_points(_$value); }


 u32 EnginePrototype::IntSpline_inner5::_acc_gKeyCount(){
    return (u32)_gm_points$()->_acc_gCount$();
}

inline u32 EnginePrototype::IntSpline_inner5::_acc_gKeyCount$() { CHCKTHIS; return _acc_gKeyCount(); }

/*virtual*/
bool EnginePrototype::IntSpline_inner5::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(IntSpline_inner5,EnginePrototype::Spline_inner4);
}

/*virtual*/
u32 EnginePrototype::IntSpline_inner5::_processGC() {
    EnginePrototype::Spline_inner4::_processGC();

    if (m_points) { System::Memory::pushList(m_points,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::IntSpline_inner5::_releaseGC() {
    EnginePrototype::Spline_inner4::_releaseGC();

    if (m_points && !m_points->isFreed()) { m_points->_removeRef((System::__GCObject**)&m_points); }
}
/*virtual*/
void EnginePrototype::IntSpline_inner5::_moveAlert(u32 offset) {
    EnginePrototype::Spline_inner4::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_points) {
      newPtr = (u8*)(&m_points); oldPtr = newPtr - offset;
      m_points->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'IntPoint_inner6'
//=============================

void EnginePrototype::IntPoint_inner6::_ctor_IntPoint_inner6() {
}

EnginePrototype::IntPoint_inner6::IntPoint_inner6(u32 time,s16 value)
{
    _ctor_IntPoint_inner6();
    _sm_time$(time);
    _sm_value$(value);
}

EnginePrototype::IntPoint_inner6::IntPoint_inner6() { _ctor_IntPoint_inner6(); }



inline u32 EnginePrototype::IntPoint_inner6::_acc_gTime(){
    return _gm_time$();
}

inline u32 EnginePrototype::IntPoint_inner6::_acc_gTime$() { CHCKTHIS; return _acc_gTime(); }

inline s16 EnginePrototype::IntPoint_inner6::_acc_gValue(){
    return _gm_value$();
}

inline s16 EnginePrototype::IntPoint_inner6::_acc_gValue$() { CHCKTHIS; return _acc_gValue(); }

/*virtual*/
bool EnginePrototype::IntPoint_inner6::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(IntPoint_inner6,System::Object);
}

/*virtual*/
u32 EnginePrototype::IntPoint_inner6::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::IntPoint_inner6::_releaseGC() {
}
/*virtual*/
void EnginePrototype::IntPoint_inner6::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'FloatSpline_inner7'
//=============================

void EnginePrototype::FloatSpline_inner7::_ctor_FloatSpline_inner7() {
}

EnginePrototype::FloatSpline_inner7::FloatSpline_inner7(s32 targetType) : EnginePrototype::Spline_inner4(targetType)
{
    _ctor_FloatSpline_inner7();
    _sm_points$(CS_NEW System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>());
}

/*virtual*/
void EnginePrototype::FloatSpline_inner7::addKeyFloat(u32 time,float value)
{
    _gm_points$()->Add$(CS_NEW EnginePrototype::FloatPoint_inner8(time,value));
}

inline void EnginePrototype::FloatSpline_inner7::addKeyFloat$(u32 time,float value) { CHCKTHIS; return addKeyFloat(time,value); }

/*virtual*/
void EnginePrototype::FloatSpline_inner7::addKeyInt(u32 time,s32 value)
{
    THROW(CS_NEW EnginePrototype::CKLBExceptionForbiddenMethod(_$_cteStr2Obj));
}

inline void EnginePrototype::FloatSpline_inner7::addKeyInt$(u32 time,s32 value) { CHCKTHIS; return addKeyInt(time,value); }

/*virtual*/
void EnginePrototype::FloatSpline_inner7::addKeys(s32* p,u32 splineIndex)
{
    for (s32 i = 0;i < _gm_points$()->_acc_gCount$();++i)
    {
        EnginePrototype::CKLBUITask::_ext_CKLBUITask_addKeysFixed(p,splineIndex,_gm_points$()->_idx_g$(i)->_acc_gTime$(),(s32)(_gm_points$()->_idx_g$(i)->_acc_gValue$() * 65536.000000));
    }
}

inline void EnginePrototype::FloatSpline_inner7::addKeys$(s32* p,u32 splineIndex) { CHCKTHIS; return addKeys(p,splineIndex); }

EnginePrototype::FloatSpline_inner7::FloatSpline_inner7() { _ctor_FloatSpline_inner7(); }

inline System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* EnginePrototype::FloatSpline_inner7::_sm_points(System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _$value)  { return (System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_points,_$value); }
inline System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* EnginePrototype::FloatSpline_inner7::_sm_points$(System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _$value) { CHCKTHIS; return _sm_points(_$value); }


 u32 EnginePrototype::FloatSpline_inner7::_acc_gKeyCount(){
    return (u32)_gm_points$()->_acc_gCount$();
}

inline u32 EnginePrototype::FloatSpline_inner7::_acc_gKeyCount$() { CHCKTHIS; return _acc_gKeyCount(); }

/*virtual*/
bool EnginePrototype::FloatSpline_inner7::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(FloatSpline_inner7,EnginePrototype::Spline_inner4);
}

/*virtual*/
u32 EnginePrototype::FloatSpline_inner7::_processGC() {
    EnginePrototype::Spline_inner4::_processGC();

    if (m_points) { System::Memory::pushList(m_points,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::FloatSpline_inner7::_releaseGC() {
    EnginePrototype::Spline_inner4::_releaseGC();

    if (m_points && !m_points->isFreed()) { m_points->_removeRef((System::__GCObject**)&m_points); }
}
/*virtual*/
void EnginePrototype::FloatSpline_inner7::_moveAlert(u32 offset) {
    EnginePrototype::Spline_inner4::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_points) {
      newPtr = (u8*)(&m_points); oldPtr = newPtr - offset;
      m_points->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'FloatPoint_inner8'
//=============================

void EnginePrototype::FloatPoint_inner8::_ctor_FloatPoint_inner8() {
}

EnginePrototype::FloatPoint_inner8::FloatPoint_inner8(u32 time,float value)
{
    _ctor_FloatPoint_inner8();
    _sm_time$(time);
    _sm_value$(value);
}

EnginePrototype::FloatPoint_inner8::FloatPoint_inner8() { _ctor_FloatPoint_inner8(); }



inline u32 EnginePrototype::FloatPoint_inner8::_acc_gTime(){
    return _gm_time$();
}

inline u32 EnginePrototype::FloatPoint_inner8::_acc_gTime$() { CHCKTHIS; return _acc_gTime(); }

inline float EnginePrototype::FloatPoint_inner8::_acc_gValue(){
    return _gm_value$();
}

inline float EnginePrototype::FloatPoint_inner8::_acc_gValue$() { CHCKTHIS; return _acc_gValue(); }

/*virtual*/
bool EnginePrototype::FloatPoint_inner8::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(FloatPoint_inner8,System::Object);
}

/*virtual*/
u32 EnginePrototype::FloatPoint_inner8::_processGC() {
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::FloatPoint_inner8::_releaseGC() {
}
/*virtual*/
void EnginePrototype::FloatPoint_inner8::_moveAlert(u32 offset) {
}

//=============================
// Implementation of 'AnimSpline_inner9'
//=============================

void EnginePrototype::AnimSpline_inner9::_ctor_AnimSpline_inner9() {
}

EnginePrototype::AnimSpline_inner9::AnimSpline_inner9()
{
    _ctor_AnimSpline_inner9();
    _sm_splines$(CS_NEW System::Collections::Generic::List<EnginePrototype::Spline_inner4*>());
}

EnginePrototype::Spline_inner4* EnginePrototype::AnimSpline_inner9::addNewSpline(s32 targetType,s32 splineType)
{
    switch (splineType) {
    case EnginePrototype::CKLBUITask::ESPLINE_TYPE::INT_SPLINE: sw_$lbl_1_0:
        {
            EnginePrototype::IntSpline_inner5* spline = CS_NEW EnginePrototype::IntSpline_inner5(targetType);
            _gm_splines$()->Add$(spline);
            return spline;
        }
    case EnginePrototype::CKLBUITask::ESPLINE_TYPE::FLOAT_SPLINE: sw_$lbl_1_1:
        {
            EnginePrototype::FloatSpline_inner7* spline = CS_NEW EnginePrototype::FloatSpline_inner7(targetType);
            _gm_splines$()->Add$(spline);
            return spline;
        }
    default : sw_$lbl_1_default:
        return NULL;
    }
}

inline EnginePrototype::Spline_inner4* EnginePrototype::AnimSpline_inner9::addNewSpline$(s32 targetType,s32 splineType) { CHCKTHIS; return addNewSpline(targetType,splineType); }

void EnginePrototype::AnimSpline_inner9::reset()
{
    _gm_splines$()->Clear$();
}

inline void EnginePrototype::AnimSpline_inner9::reset$() { CHCKTHIS; return reset(); }

inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* EnginePrototype::AnimSpline_inner9::_sm_splines(System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _$value)  { return (System::Collections::Generic::List<EnginePrototype::Spline_inner4*>*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_splines,_$value); }
inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* EnginePrototype::AnimSpline_inner9::_sm_splines$(System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _$value) { CHCKTHIS; return _sm_splines(_$value); }


inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* EnginePrototype::AnimSpline_inner9::_acc_gSplines(){
    return _gm_splines$();
}

inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* EnginePrototype::AnimSpline_inner9::_acc_gSplines$() { CHCKTHIS; return _acc_gSplines(); }

/*virtual*/
bool EnginePrototype::AnimSpline_inner9::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(AnimSpline_inner9,System::Object);
}

/*virtual*/
u32 EnginePrototype::AnimSpline_inner9::_processGC() {
    if (m_splines) { System::Memory::pushList(m_splines,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::AnimSpline_inner9::_releaseGC() {
    if (m_splines && !m_splines->isFreed()) { m_splines->_removeRef((System::__GCObject**)&m_splines); }
}
/*virtual*/
void EnginePrototype::AnimSpline_inner9::_moveAlert(u32 offset) {
    u8* oldPtr; u8* newPtr;
    if (m_splines) {
      newPtr = (u8*)(&m_splines); oldPtr = newPtr - offset;
      m_splines->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUITextInput'
//=============================

void EnginePrototype::CKLBUITextInput::_ctor_CKLBUITextInput() {
}

/*static*/
s32* EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_create(s32* parent,bool passwordMode,float x,float y,float width,float height,s32* defaultText,s32 widgetId,s32 maxLen,u32 charType)
{
    return CKLBUITextInput_create(parent,passwordMode,x,y,width,height,defaultText,widgetId,maxLen,charType);
}

/*static*/
u32 EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_getWidth(s32* p)
{
    return CKLBUITextInput_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setWidth(s32* p,u32 width)
{
    CKLBUITextInput_setWidth(p,width);
}

/*static*/
u32 EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_getHeight(s32* p)
{
    return CKLBUITextInput_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setHeight(s32* p,u32 height)
{
    CKLBUITextInput_setHeight(p,height);
}

/*static*/
s32* EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_getText(s32* p)
{
    return CKLBUITextInput_getText(p);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setText(s32* p,s32* text)
{
    CKLBUITextInput_setText(p,text);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setPlaceHolder(s32* p,s32* placeholder)
{
    CKLBUITextInput_setPlaceHolder(p,placeholder);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setColor(s32* p,bool bTouch,u32 foregroundRgb,u32 backgroundRgb)
{
    CKLBUITextInput_setColor(p,bTouch,foregroundRgb,backgroundRgb);
}

/*static*/
s32 EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_getMaxLen(s32* p)
{
    return CKLBUITextInput_getMaxLen(p);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setMaxLen(s32* p,s32 maxlen)
{
    CKLBUITextInput_setMaxLen(p,maxlen);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setCharType(s32* p,u32 chartype)
{
    CKLBUITextInput_setCharType(p,chartype);
}

/*static*/
s32 EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_getCharCount(s32* p)
{
    return CKLBUITextInput_getCharCount(p);
}

/*static*/
void EnginePrototype::CKLBUITextInput::_ext_CKLBUITextInput_setFont(s32* p,s32* fontName,float fontSize)
{
    CKLBUITextInput_setFont(p,fontName,fontSize);
}

EnginePrototype::CKLBUITextInput::CKLBUITextInput(EnginePrototype::CKLBUITask* parent,bool passwordMode,s32 x,s32 y,u32 width,u32 height,System::String* defaultText,EnginePrototype::_Delegate_Base_CallBack_inner48* callback,s32 widgetId,s32 maxLen,u32 charType) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUITextInput();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUITextInput_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),passwordMode,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(defaultText),widgetId,maxLen,charType);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUITextInput::CKLBUITextInput() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUITextInput();
}

/*virtual*/
void EnginePrototype::CKLBUITextInput::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerSU_inner6<CKLBUITextInput>(this,&CKLBUITextInput::callBackFunction),0);
}

inline void EnginePrototype::CKLBUITextInput::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUITextInput::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner48*)anyDelegate);
}

inline void EnginePrototype::CKLBUITextInput::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUITextInput::callBackFunction(s32* txt,u32 id)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,System::__MarshallingUtils::StringFromNativeUtf8(txt),id);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUITextInput::callBackFunction$(s32* txt,u32 id) { CHCKTHIS; return callBackFunction(txt,id); }

void EnginePrototype::CKLBUITextInput::getSize(EnginePrototype::USize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUITextInput_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUITextInput_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::getSize$(EnginePrototype::USize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUITextInput::setSize(EnginePrototype::USize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITextInput_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUITextInput_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setSize$(EnginePrototype::USize size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUITextInput::setSize(u32 width,u32 height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITextInput_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
        _ext_CKLBUITextInput_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setSize$(u32 width,u32 height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUITextInput::setColor(bool bTouch,u32 foregroundRgb,u32 backgroundRgb)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setColor(EnginePrototype::GameObject::_acc_gCppObject$(),bTouch,foregroundRgb,backgroundRgb);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setColor$(bool bTouch,u32 foregroundRgb,u32 backgroundRgb) { CHCKTHIS; return setColor(bTouch,foregroundRgb,backgroundRgb); }

void EnginePrototype::CKLBUITextInput::setFont(System::String* fontName,float fontSize)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setFont(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(fontName),fontSize);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setFont$(System::String* fontName,float fontSize) { CHCKTHIS; return setFont(fontName,fontSize); }

void EnginePrototype::CKLBUITextInput::setCharType(s32 chartype)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setCharType(EnginePrototype::GameObject::_acc_gCppObject$(),(u32)chartype);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setCharType$(s32 chartype) { CHCKTHIS; return setCharType(chartype); }

void EnginePrototype::CKLBUITextInput::setPlaceHolder(System::String* placeHolder)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setPlaceHolder(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(placeHolder));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUITextInput::setPlaceHolder$(System::String* placeHolder) { CHCKTHIS; return setPlaceHolder(placeHolder); }

inline EnginePrototype::_Delegate_Base_CallBack_inner48* EnginePrototype::CKLBUITextInput::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner48* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner48*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner48* EnginePrototype::CKLBUITextInput::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner48* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUITextInput::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUITextInput_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUITextInput::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline u32 EnginePrototype::CKLBUITextInput::_acc_sWidth(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUITextInput::_acc_sWidth$(u32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline u32 EnginePrototype::CKLBUITextInput::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUITextInput_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline u32 EnginePrototype::CKLBUITextInput::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline u32 EnginePrototype::CKLBUITextInput::_acc_sHeight(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUITextInput::_acc_sHeight$(u32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline System::String* EnginePrototype::CKLBUITextInput::_acc_gText(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUITextInput_getText(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUITextInput::_acc_gText$() { CHCKTHIS; return _acc_gText(); }

inline System::String* EnginePrototype::CKLBUITextInput::_acc_sText(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setText(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUITextInput::_acc_sText$(System::String* value)		{ CHCKTHIS; return _acc_sText(value); }
inline s32 EnginePrototype::CKLBUITextInput::_acc_gMaxLen(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUITextInput_getMaxLen(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline s32 EnginePrototype::CKLBUITextInput::_acc_gMaxLen$() { CHCKTHIS; return _acc_gMaxLen(); }

inline s32 EnginePrototype::CKLBUITextInput::_acc_sMaxLen(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUITextInput_setMaxLen(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUITextInput::_acc_sMaxLen$(s32 value)		{ CHCKTHIS; return _acc_sMaxLen(value); }
inline s32 EnginePrototype::CKLBUITextInput::_acc_gCharCount(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUITextInput_getCharCount(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline s32 EnginePrototype::CKLBUITextInput::_acc_gCharCount$() { CHCKTHIS; return _acc_gCharCount(); }

/*virtual*/
bool EnginePrototype::CKLBUITextInput::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUITextInput,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUITextInput::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUITextInput::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUITextInput::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUITouchPad'
//=============================

void EnginePrototype::CKLBUITouchPad::_ctor_CKLBUITouchPad() {
}

/*static*/
s32* EnginePrototype::CKLBUITouchPad::_ext_CKLBUITouchPad_create(s32* pParent,bool modal)
{
    return CKLBUITouchPad_create(pParent,modal);
}

/*static*/
bool EnginePrototype::CKLBUITouchPad::_ext_CKLBUITouchPad_setGroup(s32* p,s32* group_name)
{
    return CKLBUITouchPad_setGroup(p,group_name);
}

/*static*/
void EnginePrototype::CKLBUITouchPad::_ext_CKLBUITouchPad_setLock(s32* p,bool lock_mode)
{
    CKLBUITouchPad_setLock(p,lock_mode);
}

/*static*/
void EnginePrototype::CKLBUITouchPad::_ext_CKLBUITouchPad_setGetAll(s32* p,bool bAll)
{
    CKLBUITouchPad_setGetAll(p,bAll);
}

EnginePrototype::CKLBUITouchPad::CKLBUITouchPad(EnginePrototype::CKLBTask* parent,EnginePrototype::_Delegate_Base_CallBack_inner49* callback,bool modal) : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBUITouchPad();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUITouchPad_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),modal);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUITouchPad::CKLBUITouchPad() : EnginePrototype::CKLBTask(s_classID)
{
    _ctor_CKLBUITouchPad();
}

/*virtual*/
void EnginePrototype::CKLBUITouchPad::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUUUII_inner18<CKLBUITouchPad>(this,&CKLBUITouchPad::callBackFunction),0);
}

inline void EnginePrototype::CKLBUITouchPad::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUITouchPad::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner49*)anyDelegate);
}

inline void EnginePrototype::CKLBUITouchPad::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUITouchPad::callBackFunction(u32 execount,u32 type,u32 id,s32 x,s32 y)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,execount,type,id,x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUITouchPad::callBackFunction$(u32 execount,u32 type,u32 id,s32 x,s32 y) { CHCKTHIS; return callBackFunction(execount,type,id,x,y); }

void EnginePrototype::CKLBUITouchPad::setGetAll(bool bGetAll)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITouchPad_setGetAll(EnginePrototype::GameObject::_acc_gCppObject$(),bGetAll);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITouchPad::setGetAll$(bool bGetAll) { CHCKTHIS; return setGetAll(bGetAll); }

void EnginePrototype::CKLBUITouchPad::setLock(bool bLock)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUITouchPad_setLock(EnginePrototype::GameObject::_acc_gCppObject$(),bLock);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUITouchPad::setLock$(bool bLock) { CHCKTHIS; return setLock(bLock); }

bool EnginePrototype::CKLBUITouchPad::setGroup(System::String* group_name)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUITouchPad_setGroup(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(group_name));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUITouchPad::setGroup$(System::String* group_name) { CHCKTHIS; return setGroup(group_name); }

inline EnginePrototype::_Delegate_Base_CallBack_inner49* EnginePrototype::CKLBUITouchPad::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner49* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner49*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner49* EnginePrototype::CKLBUITouchPad::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner49* _$value) { CHCKTHIS; return _sm_callback(_$value); }


/*virtual*/
bool EnginePrototype::CKLBUITouchPad::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUITouchPad,EnginePrototype::CKLBTask);
}

/*virtual*/
u32 EnginePrototype::CKLBUITouchPad::_processGC() {
    EnginePrototype::CKLBTask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUITouchPad::_releaseGC() {
    EnginePrototype::CKLBTask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUITouchPad::_moveAlert(u32 offset) {
    EnginePrototype::CKLBTask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIVariableItem'
//=============================

void EnginePrototype::CKLBUIVariableItem::_ctor_CKLBUIVariableItem() {
}

/*static*/
s32* EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* asset)
{
    return CKLBUIVariableItem_create(pParent,order,x,y,width,height,asset);
}

/*static*/
u32 EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_getOrder(s32* p)
{
    return CKLBUIVariableItem_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_setOrder(s32* p,u32 order)
{
    CKLBUIVariableItem_setOrder(p,order);
}

/*static*/
s32* EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_getAsset(s32* p)
{
    return CKLBUIVariableItem_getAsset(p);
}

/*static*/
float EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_getWidth(s32* p)
{
    return CKLBUIVariableItem_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_setWidth(s32* p,float width)
{
    CKLBUIVariableItem_setWidth(p,width);
}

/*static*/
float EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_getHeight(s32* p)
{
    return CKLBUIVariableItem_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_setHeight(s32* p,float height)
{
    CKLBUIVariableItem_setHeight(p,height);
}

/*static*/
bool EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_changeAsset(s32* p,s32* assetName)
{
    return CKLBUIVariableItem_changeAsset(p,assetName);
}

/*static*/
void EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_changeUV(s32* p,float x,float y,float width,float height)
{
    CKLBUIVariableItem_changeUV(p,x,y,width,height);
}

/*static*/
bool EnginePrototype::CKLBUIVariableItem::_ext_CKLBUIVariableItem_setMaskAsset(s32* p,s32* assetName)
{
    return CKLBUIVariableItem_setMaskAsset(p,assetName);
}

EnginePrototype::CKLBUIVariableItem::CKLBUIVariableItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* asset) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIVariableItem();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIVariableItem_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(asset));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
}

EnginePrototype::CKLBUIVariableItem::CKLBUIVariableItem() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIVariableItem();
}

void EnginePrototype::CKLBUIVariableItem::getSize(EnginePrototype::FSize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIVariableItem_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIVariableItem_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVariableItem::getSize$(EnginePrototype::FSize& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIVariableItem::setUV(float x,float y,float width,float height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVariableItem_changeUV(EnginePrototype::GameObject::_acc_gCppObject$(),x,y,width,height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVariableItem::setUV$(float x,float y,float width,float height) { CHCKTHIS; return setUV(x,y,width,height); }

bool EnginePrototype::CKLBUIVariableItem::setMaskAsset(System::String* assetName)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVariableItem_setMaskAsset(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(assetName));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIVariableItem::setMaskAsset$(System::String* assetName) { CHCKTHIS; return setMaskAsset(assetName); }



inline u32 EnginePrototype::CKLBUIVariableItem::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVariableItem_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVariableItem::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIVariableItem::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVariableItem_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVariableItem::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline System::String* EnginePrototype::CKLBUIVariableItem::_acc_gAsset(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIVariableItem_getAsset(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline System::String* EnginePrototype::CKLBUIVariableItem::_acc_gAsset$() { CHCKTHIS; return _acc_gAsset(); }

inline System::String* EnginePrototype::CKLBUIVariableItem::_acc_sAsset(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        EnginePrototype::NativeManagement::resetCppError();
        _ext_CKLBUIVariableItem_changeAsset(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
        EnginePrototype::NativeManagement::intercepCppError();
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIVariableItem::_acc_sAsset$(System::String* value)		{ CHCKTHIS; return _acc_sAsset(value); }
inline float EnginePrototype::CKLBUIVariableItem::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVariableItem_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIVariableItem::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline float EnginePrototype::CKLBUIVariableItem::_acc_sWidth(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVariableItem_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIVariableItem::_acc_sWidth$(float value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline float EnginePrototype::CKLBUIVariableItem::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVariableItem_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline float EnginePrototype::CKLBUIVariableItem::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline float EnginePrototype::CKLBUIVariableItem::_acc_sHeight(float value){
    float _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVariableItem_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline float EnginePrototype::CKLBUIVariableItem::_acc_sHeight$(float value)		{ CHCKTHIS; return _acc_sHeight(value); }
/*virtual*/
bool EnginePrototype::CKLBUIVariableItem::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIVariableItem,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIVariableItem::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIVariableItem::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

}
/*virtual*/
void EnginePrototype::CKLBUIVariableItem::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

}

//=============================
// Implementation of 'CKLBUIVirtualDoc'
//=============================

void EnginePrototype::CKLBUIVirtualDoc::_ctor_CKLBUIVirtualDoc() {
}

/*static*/
s32* EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_create(s32* pParent,u32 order,float x,float y,u32 docWidth,u32 docHeight,u32 viewWidth,u32 viewHeight,u32 maxCommandNums,bool verticalFlag)
{
    return CKLBUIVirtualDoc_create(pParent,order,x,y,docWidth,docHeight,viewWidth,viewHeight,maxCommandNums,verticalFlag);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_clear(s32* p,u32 color)
{
    CKLBUIVirtualDoc_clear(p,color);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setFont(s32* p,u32 idx,s32* fontName,u32 fontSize)
{
    CKLBUIVirtualDoc_setFont(p,idx,fontName,fontSize);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setViewPortPos(s32* p,s32 x,s32 y)
{
    CKLBUIVirtualDoc_setViewPortPos(p,x,y);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_drawLine(s32* p,s32 x0,s32 y0,s32 x1,s32 y1,u32 color)
{
    CKLBUIVirtualDoc_drawLine(p,x0,y0,x1,y1,color);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_drawImage(s32* p,s32 x0,s32 y0,s32* image,u32 alpha)
{
    CKLBUIVirtualDoc_drawImage(p,x0,y0,image,alpha);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_fillRect(s32* p,s32 x0,s32 y0,u32 width,u32 height,u32 color,bool fill)
{
    CKLBUIVirtualDoc_fillRect(p,x0,y0,width,height,color,fill);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_drawText(s32* p,s32 x0,s32 y0,s32* str,u32 color,u32 fontidx)
{
    CKLBUIVirtualDoc_drawText(p,x0,y0,str,color,fontidx);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_startDocument(s32* p)
{
    CKLBUIVirtualDoc_startDocument(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_checkDocumentSize(s32* p)
{
    CKLBUIVirtualDoc_checkDocumentSize(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_endDocument(s32* p)
{
    CKLBUIVirtualDoc_endDocument(p);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getCommandMax(s32* p)
{
    return CKLBUIVirtualDoc_getCommandMax(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setCommandMax(s32* p,u32 command)
{
    CKLBUIVirtualDoc_setCommandMax(p,command);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getDocHeight(s32* p)
{
    return CKLBUIVirtualDoc_getDocHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setDocHeight(s32* p,u32 command)
{
    CKLBUIVirtualDoc_setDocHeight(p,command);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getDocWidth(s32* p)
{
    return CKLBUIVirtualDoc_getDocWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setDocWidth(s32* p,u32 command)
{
    CKLBUIVirtualDoc_setDocWidth(p,command);
}

/*static*/
bool EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getVertical(s32* p)
{
    return CKLBUIVirtualDoc_getVertical(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setVertical(s32* p,bool vertical)
{
    CKLBUIVirtualDoc_setVertical(p,vertical);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getViewHeight(s32* p)
{
    return CKLBUIVirtualDoc_getViewHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setViewHeight(s32* p,u32 height)
{
    CKLBUIVirtualDoc_setViewHeight(p,height);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getViewWidth(s32* p)
{
    return CKLBUIVirtualDoc_getViewWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setViewWidth(s32* p,u32 width)
{
    CKLBUIVirtualDoc_setViewWidth(p,width);
}

/*static*/
u32 EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_getOrder(s32* p)
{
    return CKLBUIVirtualDoc_getOrder(p);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setOrder(s32* p,u32 order)
{
    CKLBUIVirtualDoc_setOrder(p,order);
}

/*static*/
void EnginePrototype::CKLBUIVirtualDoc::_ext_CKLBUIVirtualDoc_setAlign(s32* p,u32 align,s32 alignWidth)
{
    CKLBUIVirtualDoc_setAlign(p,align,alignWidth);
}

EnginePrototype::CKLBUIVirtualDoc::CKLBUIVirtualDoc(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 docWidth,u32 docHeight,u32 viewWidth,u32 viewHeight,u32 maxCommandNums,bool verticalFlag,EnginePrototype::_Delegate_Base_CallBack_inner50* callback) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIVirtualDoc();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIVirtualDoc_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),order,x,y,docWidth,docHeight,viewWidth,viewHeight,maxCommandNums,verticalFlag);
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
    _sm_isLocked$(false);
}

EnginePrototype::CKLBUIVirtualDoc::CKLBUIVirtualDoc() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIVirtualDoc();
}

/*virtual*/
void EnginePrototype::CKLBUIVirtualDoc::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUIIUU_inner16<CKLBUIVirtualDoc>(this,&CKLBUIVirtualDoc::callBackFunction),0);
}

inline void EnginePrototype::CKLBUIVirtualDoc::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIVirtualDoc::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner50*)anyDelegate);
}

inline void EnginePrototype::CKLBUIVirtualDoc::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIVirtualDoc::callBackFunction(u32 type,s32 x,s32 y,u32 moveX,u32 moveY)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,(ETYPE)type,x,y,moveX,moveY);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::callBackFunction$(u32 type,s32 x,s32 y,u32 moveX,u32 moveY) { CHCKTHIS; return callBackFunction(type,x,y,moveX,moveY); }

void EnginePrototype::CKLBUIVirtualDoc::getDocSize(EnginePrototype::USize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIVirtualDoc_getDocWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIVirtualDoc_getDocHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::getDocSize$(EnginePrototype::USize& size) { CHCKTHIS; return getDocSize(size); }

void EnginePrototype::CKLBUIVirtualDoc::setDocSize(EnginePrototype::USize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setDocWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIVirtualDoc_setDocHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setDocSize$(EnginePrototype::USize size) { CHCKTHIS; return setDocSize(size); }

void EnginePrototype::CKLBUIVirtualDoc::setDocSize(u32 width,u32 height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setDocWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
        _ext_CKLBUIVirtualDoc_setDocHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setDocSize$(u32 width,u32 height) { CHCKTHIS; return setDocSize(width,height); }

void EnginePrototype::CKLBUIVirtualDoc::getViewSize(EnginePrototype::USize& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIVirtualDoc_getViewWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIVirtualDoc_getViewHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::getViewSize$(EnginePrototype::USize& size) { CHCKTHIS; return getViewSize(size); }

void EnginePrototype::CKLBUIVirtualDoc::setViewSize(EnginePrototype::USize size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setViewWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIVirtualDoc_setViewHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setViewSize$(EnginePrototype::USize size) { CHCKTHIS; return setViewSize(size); }

void EnginePrototype::CKLBUIVirtualDoc::setViewSize(u32 width,u32 height)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setViewWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
        _ext_CKLBUIVirtualDoc_setViewHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setViewSize$(u32 width,u32 height) { CHCKTHIS; return setViewSize(width,height); }

void EnginePrototype::CKLBUIVirtualDoc::setFont(u32 index,System::String* name,u32 size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setFont(EnginePrototype::GameObject::_acc_gCppObject$(),index,System::__MarshallingUtils::NativeUtf8FromString(name),size);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setFont$(u32 index,System::String* name,u32 size) { CHCKTHIS; return setFont(index,name,size); }

void EnginePrototype::CKLBUIVirtualDoc::clear(u32 argb)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_clear(EnginePrototype::GameObject::_acc_gCppObject$(),argb);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::clear$(u32 argb) { CHCKTHIS; return clear(argb); }

void EnginePrototype::CKLBUIVirtualDoc::setViewPortPos(s32 x,s32 y)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setViewPortPos(EnginePrototype::GameObject::_acc_gCppObject$(),x,y);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setViewPortPos$(s32 x,s32 y) { CHCKTHIS; return setViewPortPos(x,y); }

void EnginePrototype::CKLBUIVirtualDoc::setAlign(s32 align,s32 alignWidth)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setAlign(EnginePrototype::GameObject::_acc_gCppObject$(),(u32)align,((alignWidth == -1) ? (s32)_acc_gViewWidth$() : alignWidth));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::setAlign$(s32 align,s32 alignWidth) { CHCKTHIS; return setAlign(align,alignWidth); }

void EnginePrototype::CKLBUIVirtualDoc::startDrawList(u32 commandCount)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setCommandMax(EnginePrototype::GameObject::_acc_gCppObject$(),commandCount);
        _ext_CKLBUIVirtualDoc_checkDocumentSize(EnginePrototype::GameObject::_acc_gCppObject$());
        _ext_CKLBUIVirtualDoc_startDocument(EnginePrototype::GameObject::_acc_gCppObject$());
        _sm_isLocked$(true);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::startDrawList$(u32 commandCount) { CHCKTHIS; return startDrawList(commandCount); }

void EnginePrototype::CKLBUIVirtualDoc::endDrawList()
{
    _ext_CKLBUIVirtualDoc_endDocument(EnginePrototype::GameObject::_acc_gCppObject$());
    _sm_isLocked$(false);
}

inline void EnginePrototype::CKLBUIVirtualDoc::endDrawList$() { CHCKTHIS; return endDrawList(); }

void EnginePrototype::CKLBUIVirtualDoc::drawLine(s32 x0,s32 y0,s32 x1,s32 y1,u32 argb)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() == System::IntPtr::Zero)
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    if (_gm_isLocked$())
    {
        _ext_CKLBUIVirtualDoc_drawLine(EnginePrototype::GameObject::_acc_gCppObject$(),x0,y0,x1,y1,argb);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr110Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::drawLine$(s32 x0,s32 y0,s32 x1,s32 y1,u32 argb) { CHCKTHIS; return drawLine(x0,y0,x1,y1,argb); }

void EnginePrototype::CKLBUIVirtualDoc::drawText(s32 x0,s32 y0,System::String* str,u32 argb,u32 font_index)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() == System::IntPtr::Zero)
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    if (_gm_isLocked$())
    {
        _ext_CKLBUIVirtualDoc_drawText(EnginePrototype::GameObject::_acc_gCppObject$(),x0,y0,System::__MarshallingUtils::NativeUtf8FromString(str),argb,font_index);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr110Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::drawText$(s32 x0,s32 y0,System::String* str,u32 argb,u32 font_index) { CHCKTHIS; return drawText(x0,y0,str,argb,font_index); }

void EnginePrototype::CKLBUIVirtualDoc::drawFillRect(s32 x0,s32 y0,u32 width,u32 height,u32 argb,bool fill)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() == System::IntPtr::Zero)
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    if (_gm_isLocked$())
    {
        _ext_CKLBUIVirtualDoc_fillRect(EnginePrototype::GameObject::_acc_gCppObject$(),x0,y0,width,height,argb,fill);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr110Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::drawFillRect$(s32 x0,s32 y0,u32 width,u32 height,u32 argb,bool fill) { CHCKTHIS; return drawFillRect(x0,y0,width,height,argb,fill); }

void EnginePrototype::CKLBUIVirtualDoc::drawImage(s32 x,s32 y,System::String* image,u32 alpha)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() == System::IntPtr::Zero)
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    if (_gm_isLocked$())
    {
        EnginePrototype::NativeManagement::resetCppError();
        _ext_CKLBUIVirtualDoc_drawImage(EnginePrototype::GameObject::_acc_gCppObject$(),x,y,System::__MarshallingUtils::NativeUtf8FromString(image),alpha);
        EnginePrototype::NativeManagement::intercepCppError();
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr110Obj));
    }
}

inline void EnginePrototype::CKLBUIVirtualDoc::drawImage$(s32 x,s32 y,System::String* image,u32 alpha) { CHCKTHIS; return drawImage(x,y,image,alpha); }

inline EnginePrototype::_Delegate_Base_CallBack_inner50* EnginePrototype::CKLBUIVirtualDoc::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner50* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner50*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner50* EnginePrototype::CKLBUIVirtualDoc::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner50* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gOrder(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getOrder(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gOrder$() { CHCKTHIS; return _acc_gOrder(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sOrder(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setOrder(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sOrder$(u32 value)		{ CHCKTHIS; return _acc_sOrder(value); }
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gCmdMax(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getCommandMax(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gCmdMax$() { CHCKTHIS; return _acc_gCmdMax(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sCmdMax(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setCommandMax(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sCmdMax$(u32 value)		{ CHCKTHIS; return _acc_sCmdMax(value); }
inline bool EnginePrototype::CKLBUIVirtualDoc::_acc_gVertical(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getVertical(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline bool EnginePrototype::CKLBUIVirtualDoc::_acc_gVertical$() { CHCKTHIS; return _acc_gVertical(); }

inline bool EnginePrototype::CKLBUIVirtualDoc::_acc_sVertical(bool value){
    bool _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setVertical(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline bool EnginePrototype::CKLBUIVirtualDoc::_acc_sVertical$(bool value)		{ CHCKTHIS; return _acc_sVertical(value); }
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gDocWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getDocWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gDocWidth$() { CHCKTHIS; return _acc_gDocWidth(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sDocWidth(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setDocWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sDocWidth$(u32 value)		{ CHCKTHIS; return _acc_sDocWidth(value); }
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gDocHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getDocHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gDocHeight$() { CHCKTHIS; return _acc_gDocHeight(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sDocHeight(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setDocHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sDocHeight$(u32 value)		{ CHCKTHIS; return _acc_sDocHeight(value); }
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gViewWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getViewWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gViewWidth$() { CHCKTHIS; return _acc_gViewWidth(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sViewWidth(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setViewWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sViewWidth$(u32 value)		{ CHCKTHIS; return _acc_sViewWidth(value); }
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gViewHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        return _ext_CKLBUIVirtualDoc_getViewHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_gViewHeight$() { CHCKTHIS; return _acc_gViewHeight(); }

inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sViewHeight(u32 value){
    u32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIVirtualDoc_setViewHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
    return _returnValue_;
}
inline u32 EnginePrototype::CKLBUIVirtualDoc::_acc_sViewHeight$(u32 value)		{ CHCKTHIS; return _acc_sViewHeight(value); }
/*virtual*/
bool EnginePrototype::CKLBUIVirtualDoc::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIVirtualDoc,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIVirtualDoc::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIVirtualDoc::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIVirtualDoc::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

//=============================
// Implementation of 'CKLBUIWebArea'
//=============================

void EnginePrototype::CKLBUIWebArea::_ctor_CKLBUIWebArea() {
}

/*static*/
s32* EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_create(s32* pParent,bool mode,float x,float y,float width,float height,s32* url)
{
    return CKLBUIWebArea_create(pParent,mode,x,y,width,height,url);
}

/*static*/
s32 EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_getWidth(s32* p)
{
    return CKLBUIWebArea_getWidth(p);
}

/*static*/
void EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_setWidth(s32* p,s32 width)
{
    CKLBUIWebArea_setWidth(p,width);
}

/*static*/
s32 EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_getHeight(s32* p)
{
    return CKLBUIWebArea_getHeight(p);
}

/*static*/
void EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_setHeight(s32* p,s32 height)
{
    CKLBUIWebArea_setHeight(p,height);
}

/*static*/
s32* EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_getText(s32* p)
{
    return CKLBUIWebArea_getText(p);
}

/*static*/
void EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_setText(s32* p,s32* text)
{
    CKLBUIWebArea_setText(p,text);
}

/*static*/
void EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_setScalesPageToFit(s32* p,bool b)
{
    CKLBUIWebArea_setScalesPageToFit(p,b);
}

/*static*/
void EnginePrototype::CKLBUIWebArea::_ext_CKLBUIWebArea_setBgColor(s32* p,u32 argb)
{
    CKLBUIWebArea_setBgColor(p,argb);
}

EnginePrototype::CKLBUIWebArea::CKLBUIWebArea(EnginePrototype::CKLBUITask* parent,bool mode,float x,float y,float width,float height,System::String* url,EnginePrototype::_Delegate_Base_CallBack_inner51* callback) : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIWebArea();
    EnginePrototype::NativeManagement::resetCppError();
    s32* ptr = _ext_CKLBUIWebArea_create((parent != NULL ? parent->_acc_gCppObject$() : System::IntPtr::Zero),mode,x,y,width,height,System::__MarshallingUtils::NativeUtf8FromString(url));
    EnginePrototype::NativeManagement::intercepCppError();
    EnginePrototype::GameObject::bind$(ptr);
    _sm_callback$(callback);
}

EnginePrototype::CKLBUIWebArea::CKLBUIWebArea() : EnginePrototype::CKLBUITask(s_classID)
{
    _ctor_CKLBUIWebArea();
}

/*virtual*/
void EnginePrototype::CKLBUIWebArea::doSetupCallbacks()
{
    EnginePrototype::GameObject::registerCallBack$(CS_NEW EnginePrototype::_DelegateI_FunctionPointerUS_inner8<CKLBUIWebArea>(this,&CKLBUIWebArea::callBackFunction),0);
}

inline void EnginePrototype::CKLBUIWebArea::doSetupCallbacks$() { CHCKTHIS; return doSetupCallbacks(); }

/*virtual*/
void EnginePrototype::CKLBUIWebArea::setDelegate(System::Delegate* anyDelegate,System::String* delegateName)
{
    _sm_callback$((EnginePrototype::_Delegate_Base_CallBack_inner51*)anyDelegate);
}

inline void EnginePrototype::CKLBUIWebArea::setDelegate$(System::Delegate* anyDelegate,System::String* delegateName) { CHCKTHIS; return setDelegate(anyDelegate,delegateName); }

/*virtual*/
void EnginePrototype::CKLBUIWebArea::callBackFunction(u32 uint1,s32* url)
{
    if (_gm_callback$() != NULL)
    {
        _gm_callback$()->call$(this,uint1,System::__MarshallingUtils::StringFromNativeUtf8(url));
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBException(_$_cteStr53Obj));
    }
}

inline void EnginePrototype::CKLBUIWebArea::callBackFunction$(u32 uint1,s32* url) { CHCKTHIS; return callBackFunction(uint1,url); }

void EnginePrototype::CKLBUIWebArea::getSize(EnginePrototype::Size& size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        size._swidth$(_ext_CKLBUIWebArea_getWidth(EnginePrototype::GameObject::_acc_gCppObject$()));
        size._sheight$(_ext_CKLBUIWebArea_getHeight(EnginePrototype::GameObject::_acc_gCppObject$()));
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIWebArea::getSize$(EnginePrototype::Size& size) { CHCKTHIS; return getSize(size); }

void EnginePrototype::CKLBUIWebArea::setSize(EnginePrototype::Size size)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIWebArea_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),size._gwidth$());
        _ext_CKLBUIWebArea_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),size._gheight$());
    }
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline void EnginePrototype::CKLBUIWebArea::setSize$(EnginePrototype::Size size) { CHCKTHIS; return setSize(size); }

void EnginePrototype::CKLBUIWebArea::setSize(s32 width,s32 height)
{
    _ext_CKLBUIWebArea_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),width);
    _ext_CKLBUIWebArea_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),height);
}

inline void EnginePrototype::CKLBUIWebArea::setSize$(s32 width,s32 height) { CHCKTHIS; return setSize(width,height); }

void EnginePrototype::CKLBUIWebArea::setScalesPageToFit(bool b)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIWebArea_setScalesPageToFit(EnginePrototype::GameObject::_acc_gCppObject$(),b);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIWebArea::setScalesPageToFit$(bool b) { CHCKTHIS; return setScalesPageToFit(b); }

void EnginePrototype::CKLBUIWebArea::setBgColor(u32 argb)
{
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    {
        _ext_CKLBUIWebArea_setBgColor(EnginePrototype::GameObject::_acc_gCppObject$(),argb);
    }
    else
    {
        THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    }
}

inline void EnginePrototype::CKLBUIWebArea::setBgColor$(u32 argb) { CHCKTHIS; return setBgColor(argb); }

inline EnginePrototype::_Delegate_Base_CallBack_inner51* EnginePrototype::CKLBUIWebArea::_sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner51* _$value)  { return (EnginePrototype::_Delegate_Base_CallBack_inner51*)System::__GCObject::_RefSetValue((System::__GCObject**)&m_callback,_$value); }
inline EnginePrototype::_Delegate_Base_CallBack_inner51* EnginePrototype::CKLBUIWebArea::_sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner51* _$value) { CHCKTHIS; return _sm_callback(_$value); }


inline s32 EnginePrototype::CKLBUIWebArea::_acc_gWidth(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIWebArea_getWidth(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline s32 EnginePrototype::CKLBUIWebArea::_acc_gWidth$() { CHCKTHIS; return _acc_gWidth(); }

inline s32 EnginePrototype::CKLBUIWebArea::_acc_sWidth(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIWebArea_setWidth(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIWebArea::_acc_sWidth$(s32 value)		{ CHCKTHIS; return _acc_sWidth(value); }
inline s32 EnginePrototype::CKLBUIWebArea::_acc_gHeight(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return _ext_CKLBUIWebArea_getHeight(EnginePrototype::GameObject::_acc_gCppObject$());
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline s32 EnginePrototype::CKLBUIWebArea::_acc_gHeight$() { CHCKTHIS; return _acc_gHeight(); }

inline s32 EnginePrototype::CKLBUIWebArea::_acc_sHeight(s32 value){
    s32 _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIWebArea_setHeight(EnginePrototype::GameObject::_acc_gCppObject$(),value);
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline s32 EnginePrototype::CKLBUIWebArea::_acc_sHeight$(s32 value)		{ CHCKTHIS; return _acc_sHeight(value); }
inline System::String* EnginePrototype::CKLBUIWebArea::_acc_gUrl(){
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    return System::__MarshallingUtils::StringFromNativeUtf8(_ext_CKLBUIWebArea_getText(EnginePrototype::GameObject::_acc_gCppObject$()));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
}

inline System::String* EnginePrototype::CKLBUIWebArea::_acc_gUrl$() { CHCKTHIS; return _acc_gUrl(); }

inline System::String* EnginePrototype::CKLBUIWebArea::_acc_sUrl(System::String* value){
    System::String* _returnValue_ = value;
    if (EnginePrototype::GameObject::_acc_gCppObject$() != System::IntPtr::Zero)
    _ext_CKLBUIWebArea_setText(EnginePrototype::GameObject::_acc_gCppObject$(),System::__MarshallingUtils::NativeUtf8FromString(value));
    else
    THROW(CS_NEW EnginePrototype::CKLBExceptionNullCppObject(_$_cteStr3Obj));
    return _returnValue_;
}
inline System::String* EnginePrototype::CKLBUIWebArea::_acc_sUrl$(System::String* value)		{ CHCKTHIS; return _acc_sUrl(value); }
/*virtual*/
bool EnginePrototype::CKLBUIWebArea::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CKLBUIWebArea,EnginePrototype::CKLBUITask);
}

/*virtual*/
u32 EnginePrototype::CKLBUIWebArea::_processGC() {
    EnginePrototype::CKLBUITask::_processGC();

    if (m_callback) { System::Memory::pushList(m_callback,0); }
    return System::__GCObject::COMPLETE;
}
/*virtual*/
void EnginePrototype::CKLBUIWebArea::_releaseGC() {
    EnginePrototype::CKLBUITask::_releaseGC();

    if (m_callback && !m_callback->isFreed()) { m_callback->_removeRef((System::__GCObject**)&m_callback); }
}
/*virtual*/
void EnginePrototype::CKLBUIWebArea::_moveAlert(u32 offset) {
    EnginePrototype::CKLBUITask::_moveAlert(offset);

    u8* oldPtr; u8* newPtr;
    if (m_callback) {
      newPtr = (u8*)(&m_callback); oldPtr = newPtr - offset;
      m_callback->_moveRef((__GCObject**)oldPtr,(__GCObject**)newPtr);
    }
}

u32 EnginePrototype::GameObject::NULLHANDLER;
u32 EnginePrototype::GameObject::NBCALLBACKS;
s32* EnginePrototype::NativeManagement::ms_cppErrorFlag;
s32* EnginePrototype::NativeManagement::ms_counter;
EnginePrototype::WrapperReg* EnginePrototype::WrapperReg::reg;
u32 EnginePrototype::CSBin::s_classID;
u32 EnginePrototype::CSData::s_classID;
u32 EnginePrototype::CSDB::s_classID;
bool EnginePrototype::CSDebug::s_isBuildingMenu;
u32 EnginePrototype::CSFont::s_classID;
float EnginePrototype::CSMatrix::EPSILON;
u32 EnginePrototype::CSSound::s_classID;
u32 EnginePrototype::CKLBAsyncLoader::s_classID;
u32 EnginePrototype::CKLBGenericTask::s_classID;
u32 EnginePrototype::CKLBIntervalTimer::s_classID;
u32 EnginePrototype::CKLBNetAPI::s_classID;
u32 EnginePrototype::CKLBStoreService::s_classID;
u32 EnginePrototype::CKLBUICanvas::s_classID;
u32 EnginePrototype::CKLBUIClip::s_classID;
u32 EnginePrototype::CKLBUIControl::s_classID;
u32 EnginePrototype::CKLBUIDebugItem::s_classID;
u32 EnginePrototype::CKLBUIDragIcon::s_classID;
u32 EnginePrototype::CKLBUIForm::s_classID;
u32 EnginePrototype::CKLBUIFreeVertItem::s_classID;
u32 EnginePrototype::CKLBUIGroup::s_classID;
u32 EnginePrototype::CKLBUILabel::s_classID;
u32 EnginePrototype::CKLBUIList::s_classID;
u32 EnginePrototype::CKLBUIMoviePlayer::s_classID;
u32 EnginePrototype::CKLBUIMultiImgItem::s_classID;
u32 EnginePrototype::CKLBUIPieChart::s_classID;
u32 EnginePrototype::CKLBUIPolyline::s_classID;
u32 EnginePrototype::CKLBUIProgressBar::s_classID;
u32 EnginePrototype::CKLBUIRubberBand::s_classID;
u32 EnginePrototype::CKLBUIScale9::s_classID;
System::Array<u32>* EnginePrototype::AnimationInfo::ms_maskArr;
System::Array<s32>* EnginePrototype::AnimationInfo::ms_indexes;
u32 EnginePrototype::CKLBUIScore::s_classID;
u32 EnginePrototype::CKLBUIScrollBar::s_classID;
u32 EnginePrototype::CKLBUISimpleItem::s_classID;
u32 EnginePrototype::CKLBUISWFPlayer::s_classID;
u32 EnginePrototype::CKLBUITextInput::s_classID;
u32 EnginePrototype::CKLBUITouchPad::s_classID;
u32 EnginePrototype::CKLBUIVariableItem::s_classID;
u32 EnginePrototype::CKLBUIVirtualDoc::s_classID;
u32 EnginePrototype::CKLBUIWebArea::s_classID;
void* _global_array_initializer_6(void* array_) {
    System::Array<s32>* _array = (System::Array<s32>*)array_;

    static const s32 _arrayCTE[] = {0,2,4,8,10,12,14,16,18,20};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}
void* _global_array_initializer_4(void* array_) {
    System::Array<float>* _array = (System::Array<float>*)array_;

    static const float _arrayCTE[] = {1.000000f,0.000000f,0.000000f,0.000000f,0.000000f,1.000000f,0.000000f,0.000000f,0.000000f,0.000000f,1.000000f,0.000000f,0.000000f,0.000000f,0.000000f,1.000000f};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}
void* _global_array_initializer_3(void* array_) {
    System::Array<float>* _array = (System::Array<float>*)array_;

    static const float _arrayCTE[] = {0,0,0,0};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}
void* _global_array_initializer_2(void* array_) {
    System::Array<float>* _array = (System::Array<float>*)array_;

    static const float _arrayCTE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}
void* _global_array_initializer_1(void* array_) {
    System::Array<float>* _array = (System::Array<float>*)array_;

    static const float _arrayCTE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}
void* _global_array_initializer_0(void* array_) {
    System::Array<float>* _array = (System::Array<float>*)array_;

    static const float _arrayCTE[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    _array->_setMemCpy(_arrayCTE);
    return array_;
}

#include "callbackDef.inl"

void initFrameworkStatic() {
    EnginePrototype::GameObject::NULLHANDLER = -1;
    EnginePrototype::GameObject::NBCALLBACKS = 6;
    EnginePrototype::NativeManagement::ms_cppErrorFlag = EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_getErrorPtr();
    EnginePrototype::NativeManagement::ms_counter = EnginePrototype::NativeManagement::_ext_CKLBScriptEnv_getCallBackCount();
    EnginePrototype::WrapperReg::reg = CS_NEW EnginePrototype::WrapperReg();
    EnginePrototype::CSBin::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr44Obj);
    EnginePrototype::CSData::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr45Obj);
    EnginePrototype::CSDB::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr46Obj);
    EnginePrototype::CSDebug::s_isBuildingMenu = false;
    EnginePrototype::CSFont::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr49Obj);
    EnginePrototype::CSMatrix::EPSILON = 0.000010f;
    EnginePrototype::CSSound::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr51Obj);
    EnginePrototype::CKLBAsyncLoader::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr52Obj);
    EnginePrototype::CKLBGenericTask::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr54Obj);
    EnginePrototype::CKLBNetAPI::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr59Obj);
    EnginePrototype::CKLBStoreService::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr63Obj);
    EnginePrototype::AnimationInfo::ms_maskArr = (CS_NEW System::Array< u32 >(10))->_s(0,1 << 1)->_s(1,1 << 2)->_s(2,1 << 3)->_s(3,1 << 4)->_s(4,1 << 5)->_s(5,1 << 6)->_s(6,1 << 7)->_s(7,1 << 8)->_s(8,1 << 9)->_s(9,1 << 10);
    EnginePrototype::AnimationInfo::ms_indexes = (System::Array<s32>*)_global_array_initializer_6(CS_NEW System::Array< s32 >(10));
    EnginePrototype::CKLBIntervalTimer::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr58Obj);
    EnginePrototype::CKLBUICanvas::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr64Obj);
    EnginePrototype::CKLBUIClip::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr65Obj);
    EnginePrototype::CKLBUIControl::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr66Obj);
    EnginePrototype::CKLBUIDebugItem::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr72Obj);
    EnginePrototype::CKLBUIDragIcon::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr73Obj);
    EnginePrototype::CKLBUIForm::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr74Obj);
    EnginePrototype::CKLBUIFreeVertItem::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr77Obj);
    EnginePrototype::CKLBUIGroup::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr82Obj);
    EnginePrototype::CKLBUILabel::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr83Obj);
    EnginePrototype::CKLBUIList::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr85Obj);
    EnginePrototype::CKLBUIMoviePlayer::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr91Obj);
    EnginePrototype::CKLBUIMultiImgItem::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr92Obj);
    EnginePrototype::CKLBUIPieChart::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr95Obj);
    EnginePrototype::CKLBUIPolyline::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr96Obj);
    EnginePrototype::CKLBUIProgressBar::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr98Obj);
    EnginePrototype::CKLBUIRubberBand::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr99Obj);
    EnginePrototype::CKLBUIScale9::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr100Obj);
    EnginePrototype::CKLBUIScore::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr101Obj);
    EnginePrototype::CKLBUIScrollBar::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr102Obj);
    EnginePrototype::CKLBUISimpleItem::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr103Obj);
    EnginePrototype::CKLBUISWFPlayer::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr104Obj);
    EnginePrototype::CKLBUITextInput::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr106Obj);
    EnginePrototype::CKLBUITouchPad::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr107Obj);
    EnginePrototype::CKLBUIVariableItem::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr108Obj);
    EnginePrototype::CKLBUIVirtualDoc::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr109Obj);
    EnginePrototype::CKLBUIWebArea::s_classID = EnginePrototype::__FrameworkUtils::RegisterClass(_$_cteStr111Obj);
}

void initFramework() {
    // Register Strings into the GC.
    _$_cteStr111Obj = CS_NEW System::String(_$_cteStr111,sizeof(_$_cteStr111) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr111Obj);

    _$_cteStr110Obj = CS_NEW System::String(_$_cteStr110,sizeof(_$_cteStr110) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr110Obj);

    _$_cteStr109Obj = CS_NEW System::String(_$_cteStr109,sizeof(_$_cteStr109) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr109Obj);

    _$_cteStr108Obj = CS_NEW System::String(_$_cteStr108,sizeof(_$_cteStr108) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr108Obj);

    _$_cteStr107Obj = CS_NEW System::String(_$_cteStr107,sizeof(_$_cteStr107) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr107Obj);

    _$_cteStr106Obj = CS_NEW System::String(_$_cteStr106,sizeof(_$_cteStr106) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr106Obj);

    _$_cteStr105Obj = CS_NEW System::String(_$_cteStr105,sizeof(_$_cteStr105) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr105Obj);

    _$_cteStr104Obj = CS_NEW System::String(_$_cteStr104,sizeof(_$_cteStr104) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr104Obj);

    _$_cteStr103Obj = CS_NEW System::String(_$_cteStr103,sizeof(_$_cteStr103) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr103Obj);

    _$_cteStr102Obj = CS_NEW System::String(_$_cteStr102,sizeof(_$_cteStr102) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr102Obj);

    _$_cteStr101Obj = CS_NEW System::String(_$_cteStr101,sizeof(_$_cteStr101) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr101Obj);

    _$_cteStr100Obj = CS_NEW System::String(_$_cteStr100,sizeof(_$_cteStr100) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr100Obj);

    _$_cteStr99Obj = CS_NEW System::String(_$_cteStr99,sizeof(_$_cteStr99) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr99Obj);

    _$_cteStr98Obj = CS_NEW System::String(_$_cteStr98,sizeof(_$_cteStr98) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr98Obj);

    _$_cteStr97Obj = CS_NEW System::String(_$_cteStr97,sizeof(_$_cteStr97) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr97Obj);

    _$_cteStr96Obj = CS_NEW System::String(_$_cteStr96,sizeof(_$_cteStr96) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr96Obj);

    _$_cteStr95Obj = CS_NEW System::String(_$_cteStr95,sizeof(_$_cteStr95) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr95Obj);

    _$_cteStr94Obj = CS_NEW System::String(_$_cteStr94,sizeof(_$_cteStr94) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr94Obj);

    _$_cteStr93Obj = CS_NEW System::String(_$_cteStr93,sizeof(_$_cteStr93) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr93Obj);

    _$_cteStr92Obj = CS_NEW System::String(_$_cteStr92,sizeof(_$_cteStr92) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr92Obj);

    _$_cteStr91Obj = CS_NEW System::String(_$_cteStr91,sizeof(_$_cteStr91) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr91Obj);

    _$_cteStr90Obj = CS_NEW System::String(_$_cteStr90,sizeof(_$_cteStr90) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr90Obj);

    _$_cteStr89Obj = CS_NEW System::String(_$_cteStr89,sizeof(_$_cteStr89) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr89Obj);

    _$_cteStr88Obj = CS_NEW System::String(_$_cteStr88,sizeof(_$_cteStr88) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr88Obj);

    _$_cteStr87Obj = CS_NEW System::String(_$_cteStr87,sizeof(_$_cteStr87) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr87Obj);

    _$_cteStr86Obj = CS_NEW System::String(_$_cteStr86,sizeof(_$_cteStr86) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr86Obj);

    _$_cteStr85Obj = CS_NEW System::String(_$_cteStr85,sizeof(_$_cteStr85) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr85Obj);

    _$_cteStr84Obj = CS_NEW System::String(_$_cteStr84,sizeof(_$_cteStr84) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr84Obj);

    _$_cteStr83Obj = CS_NEW System::String(_$_cteStr83,sizeof(_$_cteStr83) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr83Obj);

    _$_cteStr82Obj = CS_NEW System::String(_$_cteStr82,sizeof(_$_cteStr82) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr82Obj);

    _$_cteStr81Obj = CS_NEW System::String(_$_cteStr81,sizeof(_$_cteStr81) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr81Obj);

    _$_cteStr80Obj = CS_NEW System::String(_$_cteStr80,sizeof(_$_cteStr80) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr80Obj);

    _$_cteStr79Obj = CS_NEW System::String(_$_cteStr79,sizeof(_$_cteStr79) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr79Obj);

    _$_cteStr78Obj = CS_NEW System::String(_$_cteStr78,sizeof(_$_cteStr78) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr78Obj);

    _$_cteStr77Obj = CS_NEW System::String(_$_cteStr77,sizeof(_$_cteStr77) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr77Obj);

    _$_cteStr76Obj = CS_NEW System::String(_$_cteStr76,sizeof(_$_cteStr76) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr76Obj);

    _$_cteStr75Obj = CS_NEW System::String(_$_cteStr75,sizeof(_$_cteStr75) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr75Obj);

    _$_cteStr74Obj = CS_NEW System::String(_$_cteStr74,sizeof(_$_cteStr74) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr74Obj);

    _$_cteStr73Obj = CS_NEW System::String(_$_cteStr73,sizeof(_$_cteStr73) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr73Obj);

    _$_cteStr72Obj = CS_NEW System::String(_$_cteStr72,sizeof(_$_cteStr72) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr72Obj);

    _$_cteStr71Obj = CS_NEW System::String(_$_cteStr71,sizeof(_$_cteStr71) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr71Obj);

    _$_cteStr70Obj = CS_NEW System::String(_$_cteStr70,sizeof(_$_cteStr70) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr70Obj);

    _$_cteStr69Obj = CS_NEW System::String(_$_cteStr69,sizeof(_$_cteStr69) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr69Obj);

    _$_cteStr68Obj = CS_NEW System::String(_$_cteStr68,sizeof(_$_cteStr68) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr68Obj);

    _$_cteStr67Obj = CS_NEW System::String(_$_cteStr67,sizeof(_$_cteStr67) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr67Obj);

    _$_cteStr66Obj = CS_NEW System::String(_$_cteStr66,sizeof(_$_cteStr66) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr66Obj);

    _$_cteStr65Obj = CS_NEW System::String(_$_cteStr65,sizeof(_$_cteStr65) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr65Obj);

    _$_cteStr64Obj = CS_NEW System::String(_$_cteStr64,sizeof(_$_cteStr64) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr64Obj);

    _$_cteStr63Obj = CS_NEW System::String(_$_cteStr63,sizeof(_$_cteStr63) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr63Obj);

    _$_cteStr62Obj = CS_NEW System::String(_$_cteStr62,sizeof(_$_cteStr62) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr62Obj);

    _$_cteStr61Obj = CS_NEW System::String(_$_cteStr61,sizeof(_$_cteStr61) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr61Obj);

    _$_cteStr60Obj = CS_NEW System::String(_$_cteStr60,sizeof(_$_cteStr60) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr60Obj);

    _$_cteStr59Obj = CS_NEW System::String(_$_cteStr59,sizeof(_$_cteStr59) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr59Obj);

    _$_cteStr58Obj = CS_NEW System::String(_$_cteStr58,sizeof(_$_cteStr58) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr58Obj);

    _$_cteStr57Obj = CS_NEW System::String(_$_cteStr57,sizeof(_$_cteStr57) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr57Obj);

    _$_cteStr56Obj = CS_NEW System::String(_$_cteStr56,sizeof(_$_cteStr56) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr56Obj);

    _$_cteStr55Obj = CS_NEW System::String(_$_cteStr55,sizeof(_$_cteStr55) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr55Obj);

    _$_cteStr54Obj = CS_NEW System::String(_$_cteStr54,sizeof(_$_cteStr54) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr54Obj);

    _$_cteStr53Obj = CS_NEW System::String(_$_cteStr53,sizeof(_$_cteStr53) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr53Obj);

    _$_cteStr52Obj = CS_NEW System::String(_$_cteStr52,sizeof(_$_cteStr52) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr52Obj);

    _$_cteStr51Obj = CS_NEW System::String(_$_cteStr51,sizeof(_$_cteStr51) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr51Obj);

    _$_cteStr50Obj = CS_NEW System::String(_$_cteStr50,sizeof(_$_cteStr50) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr50Obj);

    _$_cteStr49Obj = CS_NEW System::String(_$_cteStr49,sizeof(_$_cteStr49) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr49Obj);

    _$_cteStr48Obj = CS_NEW System::String(_$_cteStr48,sizeof(_$_cteStr48) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr48Obj);

    _$_cteStr47Obj = CS_NEW System::String(_$_cteStr47,sizeof(_$_cteStr47) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr47Obj);

    _$_cteStr46Obj = CS_NEW System::String(_$_cteStr46,sizeof(_$_cteStr46) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr46Obj);

    _$_cteStr45Obj = CS_NEW System::String(_$_cteStr45,sizeof(_$_cteStr45) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr45Obj);

    _$_cteStr44Obj = CS_NEW System::String(_$_cteStr44,sizeof(_$_cteStr44) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr44Obj);

    _$_cteStr43Obj = CS_NEW System::String(_$_cteStr43,sizeof(_$_cteStr43) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr43Obj);

    _$_cteStr42Obj = CS_NEW System::String(_$_cteStr42,sizeof(_$_cteStr42) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr42Obj);

    _$_cteStr41Obj = CS_NEW System::String(_$_cteStr41,sizeof(_$_cteStr41) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr41Obj);

    _$_cteStr40Obj = CS_NEW System::String(_$_cteStr40,sizeof(_$_cteStr40) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr40Obj);

    _$_cteStr39Obj = CS_NEW System::String(_$_cteStr39,sizeof(_$_cteStr39) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr39Obj);

    _$_cteStr38Obj = CS_NEW System::String(_$_cteStr38,sizeof(_$_cteStr38) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr38Obj);

    _$_cteStr37Obj = CS_NEW System::String(_$_cteStr37,sizeof(_$_cteStr37) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr37Obj);

    _$_cteStr36Obj = CS_NEW System::String(_$_cteStr36,sizeof(_$_cteStr36) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr36Obj);

    _$_cteStr35Obj = CS_NEW System::String(_$_cteStr35,sizeof(_$_cteStr35) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr35Obj);

    _$_cteStr34Obj = CS_NEW System::String(_$_cteStr34,sizeof(_$_cteStr34) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr34Obj);

    _$_cteStr33Obj = CS_NEW System::String(_$_cteStr33,sizeof(_$_cteStr33) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr33Obj);

    _$_cteStr32Obj = CS_NEW System::String(_$_cteStr32,sizeof(_$_cteStr32) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr32Obj);

    _$_cteStr31Obj = CS_NEW System::String(_$_cteStr31,sizeof(_$_cteStr31) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr31Obj);

    _$_cteStr30Obj = CS_NEW System::String(_$_cteStr30,sizeof(_$_cteStr30) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr30Obj);

    _$_cteStr29Obj = CS_NEW System::String(_$_cteStr29,sizeof(_$_cteStr29) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr29Obj);

    _$_cteStr28Obj = CS_NEW System::String(_$_cteStr28,sizeof(_$_cteStr28) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr28Obj);

    _$_cteStr27Obj = CS_NEW System::String(_$_cteStr27,sizeof(_$_cteStr27) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr27Obj);

    _$_cteStr26Obj = CS_NEW System::String(_$_cteStr26,sizeof(_$_cteStr26) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr26Obj);

    _$_cteStr25Obj = CS_NEW System::String(_$_cteStr25,sizeof(_$_cteStr25) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr25Obj);

    _$_cteStr24Obj = CS_NEW System::String(_$_cteStr24,sizeof(_$_cteStr24) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr24Obj);

    _$_cteStr23Obj = CS_NEW System::String(_$_cteStr23,sizeof(_$_cteStr23) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr23Obj);

    _$_cteStr22Obj = CS_NEW System::String(_$_cteStr22,sizeof(_$_cteStr22) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr22Obj);

    _$_cteStr21Obj = CS_NEW System::String(_$_cteStr21,sizeof(_$_cteStr21) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr21Obj);

    _$_cteStr20Obj = CS_NEW System::String(_$_cteStr20,sizeof(_$_cteStr20) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr20Obj);

    _$_cteStr19Obj = CS_NEW System::String(_$_cteStr19,sizeof(_$_cteStr19) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr19Obj);

    _$_cteStr18Obj = CS_NEW System::String(_$_cteStr18,sizeof(_$_cteStr18) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr18Obj);

    _$_cteStr17Obj = CS_NEW System::String(_$_cteStr17,sizeof(_$_cteStr17) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr17Obj);

    _$_cteStr16Obj = CS_NEW System::String(_$_cteStr16,sizeof(_$_cteStr16) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr16Obj);

    _$_cteStr15Obj = CS_NEW System::String(_$_cteStr15,sizeof(_$_cteStr15) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr15Obj);

    _$_cteStr14Obj = CS_NEW System::String(_$_cteStr14,sizeof(_$_cteStr14) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr14Obj);

    _$_cteStr13Obj = CS_NEW System::String(_$_cteStr13,sizeof(_$_cteStr13) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr13Obj);

    _$_cteStr12Obj = CS_NEW System::String(_$_cteStr12,sizeof(_$_cteStr12) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr12Obj);

    _$_cteStr11Obj = CS_NEW System::String(_$_cteStr11,sizeof(_$_cteStr11) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr11Obj);

    _$_cteStr10Obj = CS_NEW System::String(_$_cteStr10,sizeof(_$_cteStr10) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr10Obj);

    _$_cteStr9Obj = CS_NEW System::String(_$_cteStr9,sizeof(_$_cteStr9) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr9Obj);

    _$_cteStr8Obj = CS_NEW System::String(_$_cteStr8,sizeof(_$_cteStr8) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr8Obj);

    _$_cteStr7Obj = CS_NEW System::String(_$_cteStr7,sizeof(_$_cteStr7) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr7Obj);

    _$_cteStr6Obj = CS_NEW System::String(_$_cteStr6,sizeof(_$_cteStr6) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr6Obj);

    _$_cteStr5Obj = CS_NEW System::String(_$_cteStr5,sizeof(_$_cteStr5) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr5Obj);

    _$_cteStr4Obj = CS_NEW System::String(_$_cteStr4,sizeof(_$_cteStr4) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr4Obj);

    _$_cteStr3Obj = CS_NEW System::String(_$_cteStr3,sizeof(_$_cteStr3) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr3Obj);

    _$_cteStr2Obj = CS_NEW System::String(_$_cteStr2,sizeof(_$_cteStr2) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr2Obj);

    _$_cteStr1Obj = CS_NEW System::String(_$_cteStr1,sizeof(_$_cteStr1) / sizeof(uniChar));
    System::Memory::registerGCRoot(&_$_cteStr1Obj);

    System::__GCObject::_RefSetValue((System::__GCObject**)&_$_cteStr0Obj, System::String::Empty);

    initFrameworkStatic();
    initCallbacks();

    System::Memory::registerGCRoot(&EnginePrototype::WrapperReg::reg);
    System::Memory::registerGCRoot(&EnginePrototype::AnimationInfo::ms_maskArr);
    System::Memory::registerGCRoot(&EnginePrototype::AnimationInfo::ms_indexes);

}
