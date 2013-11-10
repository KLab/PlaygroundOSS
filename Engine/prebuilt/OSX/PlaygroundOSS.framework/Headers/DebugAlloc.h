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
#ifndef DebugAlloc_h
#define DebugAlloc_h
#include <stdlib.h>

void * operator new(size_t size);
void * operator new[](size_t size);

void operator delete(void * ptr);
void operator delete[](void * ptr);

class CMemDebug
{
public:
	inline static void setFailNums		(int nums)		{ m_numFail = nums;  }
	inline static void setFailCounter	(int count = 0) { m_cntFail = count; }

	inline static bool isFail() {
		if(!m_numFail) return false;
		if(m_cntFail + 1 >= m_numFail) {
			return true;
		}
		m_cntFail++;
		return false;
	}
private:
	static int		m_cntFail;
	static int		m_numFail;
};
#endif // DebugAlloc_h
