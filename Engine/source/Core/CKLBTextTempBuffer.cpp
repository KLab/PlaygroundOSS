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
#include "CKLBTextTempBuffer.h"

u8* CKLBTextTempBuffer::m_pBuffer		= NULL;
u32 CKLBTextTempBuffer::m_surfaceSize	= 0;

/*static*/ 
bool 
CKLBTextTempBuffer::allocatorBuffer(u32 width, u32 height, u32 pixSize) 
{
	freeBuffer();
	m_surfaceSize	= width * height * pixSize;
	m_pBuffer		= KLBNEWA(u8, m_surfaceSize);
	if (!m_pBuffer) {
		m_surfaceSize = 0;
	}
	return (m_pBuffer != NULL);
}

/*static*/ 
u8*	
CKLBTextTempBuffer::reallocateBuffer(u32 width, u32 height, u32 pixSize) 
{
	if ((width * pixSize * height) <= m_surfaceSize) {
		return m_pBuffer;
	}

	if (m_pBuffer) {
		KLBDELETEA(m_pBuffer);
		m_pBuffer		= NULL;
		m_surfaceSize	= 0;
	}

	allocatorBuffer(width, height, pixSize);
	return m_pBuffer;
}

/*static*/ 
void	
CKLBTextTempBuffer::freeBuffer() 
{
	KLBDELETEA(m_pBuffer);
	m_pBuffer = NULL;
}
