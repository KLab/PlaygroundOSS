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
#include "RenderingFramework.h"
#include "mem.h"				// memcpy

CIndexBuffer::CIndexBuffer() {
	// Do nothing.
}

CIndexBuffer::~CIndexBuffer() {
	// Do nothing.
}

//
// Index Buffer
//

void CIndexBuffer::setDrawOffset(s32 index) {
	this->offsetDraw = index;
}

void CIndexBuffer::overrideBuffer(u32 /*indexCount*/, u16* buffer) {
	ptrBuffer	= (short*)buffer;
	offsetDraw	= 0;
}

void CIndexBuffer::load(short* pIndex, s32 startIndex, s32 count) {
	short* ptrDst = this->updateStart(startIndex);
	memcpy16(ptrDst,pIndex,count*sizeof(short));
	this->updateComplete(startIndex + count);
}

short* CIndexBuffer::updateStart(s32 startIndexIncluded) {
	klb_assertc(startIndexIncluded >= 0 && startIndexIncluded < 32768,
			"Invalid index range");

	if (vboID != 0) {
		klb_assertc(this->VBOModifying == false, "Call twice updateStart without proper updateComplete.");
		if (VBOModified == true) {
			if (VBOModifyStart > startIndexIncluded) {
				VBOModifyStart = startIndexIncluded;
			}
		} else {
			this->VBOModifyStart = startIndexIncluded;
			this->VBOModifyEnd	 = -1;
		}
		this->VBOModified		= true;
		this->VBOModifying		= true;

	}
	return &(((short*)ptrBuffer)[startIndexIncluded]);
}

void CIndexBuffer::updateComplete(s32 endIndexExcluded) {
	// klb_assertc((endIndexIncluded >= 0 && endIndexIncluded < 32768), "Invalid index range");

	if (VBOModifying) {
		VBOModifying = false;
		klb_assertc(endIndexExcluded >= VBOModifyStart, "Update end before start");
		if (endIndexExcluded > VBOModifyEnd) {
			this->VBOModifyEnd	 = endIndexExcluded;
		}
	}/* else { // DO nothing in case of normal buffer.
		assert("Buffer was never start for modification if VBO");
	} */
}

void CIndexBuffer::commitVBO() {
	#ifdef STD_OPENGL
		#pragma message ("Warning : feature not supported with standard OpenGL for now")
	#else
		klb_assertc(VBOModified == true, "VBO is not modified but commitVBO is executed.");
		dglBindBuffer	(GL_ELEMENT_ARRAY_BUFFER, this->vboID);
		GLintptr	offset	= this->VBOModifyStart * sizeof(short);
		GLsizeiptr	size	= (VBOModifyEnd - VBOModifyStart) * sizeof(short);
		void*		data	= &(((short*)ptrBuffer)[offset >> 1]);

		dglBufferSubData	(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	#endif

	this->VBOModified	= false;
	this->VBOModifyEnd	= -1;
}
