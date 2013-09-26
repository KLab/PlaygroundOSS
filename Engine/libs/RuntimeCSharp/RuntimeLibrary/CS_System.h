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
#ifndef _CS_IntrPtr_h_
#define _CS_IntrPtr_h_

#include "../CompilerProject/BaseType.h"
#include "CS_Object.h"
#include "CS_String.h"

namespace System {

bool initRuntime();

class IntPtr {
public:
	static /*const*/ s32*	Zero;
	static /*const*/ s32	Size;
};

class UIntPtr {
public:
	static /*const*/ u32*	Zero;
	static /*const*/ s32	Size;
};

class Delegate : public Object {
private:
	static const u32	_TYPEID = _TYPE_DELEGATE;
public:
	virtual				void		_releaseGC		()											{ /* Do nothing */				}
	virtual				u32			_processGC		()											{ return COMPLETE;				}
	virtual				void		_move			(__GCObject* prevObj, __GCObject* newObj)	{ /* Do nothing */				}
	virtual				bool		_isInstanceOf	(u32 typeID)								{ _INSTANCEOF(Delegate,Object);	}
	inline				bool 		_isInstanceOf$	(u32 typeID)								{ return _isInstanceOf(typeID); }
	virtual				String*		ToString		();
	inline				String*		ToString$		()											{ return ToString();			}
};

class IDisposable { 
};
class ICloneable { 
};

}

#endif
