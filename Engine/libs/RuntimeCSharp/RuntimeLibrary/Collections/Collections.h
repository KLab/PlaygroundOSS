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
#ifndef _System_Collections_h_
#define _System_Collections_h_

namespace System {
namespace Collections {
	class IEnumerator
	{
		virtual	Object* __get__Current();/*Current { get; }*/
		virtual bool	MoveNext();
		virtual void	Reset();
	};

	class IEnumerable
	{
		virtual	IEnumerator* GetEnumerator();
	};
}
}

#endif
