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
#ifndef __CKLBTEXTTEMPBUFFER_H__
#define __CKLBTEXTTEMPBUFFER_H__

#include "BaseType.h"

class CKLBTextTempBuffer {
public:
	static u32	getBufferSurface()		{ return m_surfaceSize;	}
	static u8*	getBuffer		()		{ return m_pBuffer;		}

	static bool	allocatorBuffer	(u32 width, u32 height, u32 pixSize);
	static u8*	reallocateBuffer(u32 width, u32 height, u32 pixSize);
	static void	freeBuffer		();
private:
	static	u8*	m_pBuffer;
	static	u32 m_surfaceSize;
};

#endif
