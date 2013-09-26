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

CBuffer::CBuffer() {
	// Do nothing.
}

CBuffer::~CBuffer() {
	// Do nothing.
}

//
// Buffer
//

void CBuffer::setDrawOffset(s32 index) {
	this->offsetDrawDyn = index * strideDyn;
	this->offsetDrawVBO = index * strideVBO;
}

void CBuffer::overrideBuffer(u32 /*vertexCount*/, float* buffer) {
	ptrBuffer = buffer;
	offsetDrawDyn = 0;
	offsetDrawVBO = 0;
}

void CBuffer::load(float* vertexArrayStart, s32 vertexSize, s32 vertexInfoID, s32 startVertex, s32 count) {
	u16 iStrideDest;
	SVertexEntry* pCurrentVertex;
	
	float* ptrDst = this->updateStart(vertexInfoID, startVertex, &iStrideDest, &pCurrentVertex);
	for (s32 n=0; n < count; n++) {
		float* ptrDstLoad = ptrDst;
		float* ptrSrcLoad = vertexArrayStart;

		switch (pCurrentVertex->type) {
		case VEC4:
			*ptrDstLoad++ = *ptrSrcLoad++;
		case VEC3:
			*ptrDstLoad++ = *ptrSrcLoad++;
		case VEC2:
			*ptrDstLoad++ = *ptrSrcLoad++;
		case VEC1F:
		case VEC4BYTE:
			*ptrDstLoad++ = *ptrSrcLoad++;
			break;
		default:
			klb_assertAlways( "Invalid vertex type");
		}

		ptrDst				+= iStrideDest;	// Next Vertex
		vertexArrayStart	+= vertexSize;	// Next Vertex
	}

	this->updateComplete(startVertex + count);
}

float*	CBuffer::updateStart	(s32 vertexInfoID, s32 startVertexIncluded, u16* stride, void* internalptr) {
	klb_assertc(this->VBOModifying == false, "Call twice updateStart without proper updateComplete.");
	klb_assertc(startVertexIncluded >= 0 && startVertexIncluded < 32768,
			"Invalid index range");

	s32 n	= 0;
	s32 end = this->dynCount + this->vboCount;
	while (n < end) {
		if (structure[n].vertexInfoID == vertexInfoID) {
			if (internalptr) {
				*((void**)internalptr) = &structure[n];
			}
			if (structure[n].isVBO) {
				klb_assertc(this->VBOModifying == false, "Call twice updateStart without proper updateComplete.");
				
				if (stride) {
					*stride = strideVBO;
				}

				if (this->VBOModified == true) {
					if (this->VBOModifyStart > startVertexIncluded) {
						this->VBOModifyStart = startVertexIncluded;
					}
				} else {
					this->VBOModifyStart = startVertexIncluded;
					this->VBOModifyEnd	 = -1;
				}
				this->VBOModified		= true;
				this->VBOModifying		= true;
				return (&(((float*)vboLocalCopy)[(startVertexIncluded*strideDyn) + structure[n].offset]));
			} else {
				if (stride) {
					*stride = strideDyn;
				}
				return (&(((float*)ptrBuffer)[(startVertexIncluded*strideDyn) + structure[n].offset]));
			}
		}
		n++;
	}

	klb_assertAlways( "Unknown vertexInfoID into buffer");
	if (stride) {
		*stride = 0;
	}
	return null;
}

void	CBuffer::updateComplete	(s32 endVertexExcluded) {
	//klb_assertc(endVertexIncluded >= 0 && endVertexIncluded < 32768,
	//		"Invalid index range");

	if (VBOModifying) {
		VBOModifying = false;
		klb_assertc(endVertexExcluded >= VBOModifyStart, "");
		if (endVertexExcluded > VBOModifyEnd) {
			this->VBOModifyEnd	 = endVertexExcluded;
		}
	}/* else { // DO nothing in case of normal buffer.
		klb_assert("Buffer was never start for modification if VBO");
	} */
}

void	CBuffer::commitVBO() {
	#ifdef STD_OPENGL
		#pragma message ("Warning : feature not supported with standard OpenGL for now")
	#else
		klb_assertc(VBOModified == true, "VBO is not modified but commitVBO is executed.");
		dglBindBuffer	(GL_ARRAY_BUFFER, this->vboID);
		GLintptr	offset	= this->VBOModifyStart * strideVBO * sizeof(float);
		GLsizeiptr	size	= (VBOModifyEnd - VBOModifyStart) * strideVBO * sizeof(float);
		void*		data	= &(((float*)vboLocalCopy)[offset >> 2]);

		dglBufferSubData	(GL_ARRAY_BUFFER, offset, size, data);
	#endif

	this->VBOModified	= false;
	this->VBOModifyEnd	= -1;
}
