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
#ifndef _System_Collection_Generic_h_
#define _System_Collection_Generic_h_

#include "Collections/Collections.h"
#include "CS_Object.h"

namespace System {
namespace Collections {
namespace Generic {
    
	template<class T>
    class IEnumerator /*<out T> : System::Collections::IEnumerator*/
    {
	public:
		virtual bool MoveNext() = 0;
		inline bool MoveNext$()	        { CHCKTHIS; return MoveNext();      }
		virtual T _acc_gCurrent() = 0;
		inline T _acc_gCurrent$()       { CHCKTHIS; return _acc_gCurrent(); }
		virtual void Dispose() = 0;
		inline void Dispose$()          { CHCKTHIS; return Dispose();       }
    };
			
	template<class T>
	class IEnumerable /*<out T> : System::Collections::IEnumerable*/
	{
		// Summary:
		//     Returns an enumerator that iterates through the collection.
		//
		// Returns:
		//     A System.Collections.Generic.IEnumerator<T> that can be used to iterate through
		//     the collection.
		IEnumerator<T> GetEnumerator();
	};
            
    template<class T>
    class IComparer /*<in T>*/
    {
                
    };

	class KeyNotFoundException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_KEYNOTFOUNDEXCEPTION;
	public:
		virtual bool _isInstanceOf(u32 typeID) { _INSTANCEOF(KeyNotFoundException,SystemException); }
	};
}
}
}

#endif
