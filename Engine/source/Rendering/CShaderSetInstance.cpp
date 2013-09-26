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
#include "mem.h"

// TODO Would need later a CController only.
// #include "ApplicationFramework.h"

CShaderInstance::CShaderInstance() {
	// Do nothing.
}

CShaderInstance::~CShaderInstance() {
	// Do nothing.
}

//
// ShaderSetInstance
//

/** TODO RP : Shader System with controller implementation.
void CShaderInstance::updateByController(CController* pSrc) {
	for (s32 n=0; n < pSrc->m_componentCount; n++) {
		s32 select	= (pSrc->m_targetProperties>>5) & 0x1F;
		SHADER type = select & 0x10 ? PIXEL_SHADER : VERTEX_SHADER;
		if (pSrc->m_asFloat & (1<<n)) {
			setUniformF(type, select & 0xF, (GLfloat*)&pSrc->result[n]);
			n += (type-1);	// Skip vector size.
		} else {
			setUniformI(type, select & 0xF, (GLint*)&pSrc->result[n]);
		}
	}
}*/

void CShaderInstance::setUniformTexture(SHADER type, s32 uniformID, CTextureUsage*	pTextureUsage) {
	SInternalParam* pArray;

	if (type == VERTEX_SHADER) {
		pArray = this->paramArrayUniformVertexShader;
	} else {
		pArray = this->paramArrayUniformPixelShader;
	}

	while (pArray->vertexInfoID != uniformID) {
		pArray++;
	}

	// TODO assert invalid uniform ID

	switch (pArray->dType) {
	case TEX2D:
		pArray->pTexture = pTextureUsage;
		break;
	default:
		break;
	}
}

void CShaderInstance::setUniformI(SHADER type, s32 uniformID, GLint* values  ) {
	SInternalParam* pArray;

	// TODO assert shader type

	if (type == VERTEX_SHADER) {
		pArray = this->paramArrayUniformVertexShader;
	} else {
		pArray = this->paramArrayUniformPixelShader;
	}

	while (pArray->vertexInfoID != uniformID) {
		pArray++;
	}

	// TODO assert invalid uniform ID

	switch (pArray->dType) {
	case VEC1I:
		pArray->values[0].i = *values;
		break;
	default:
		break;
	}
}

void CShaderInstance::setUniformF(SHADER type, s32 uniformID, GLfloat* values) {
	
	// TODO Assert shader type, null pointer

	SInternalParam* pArray;

	if (type == VERTEX_SHADER) {
		pArray = this->paramArrayUniformVertexShader;
	} else {
		pArray = this->paramArrayUniformPixelShader;
	}

	while (pArray->vertexInfoID != uniformID) {
		pArray++;
	}

	s32 size;
	switch (pArray->dType) {
	case VEC1F:			size = 1;	break;
	case VEC2:			size = 2;	break;
	case VEC3:			size = 3;	break;
	case VEC4:			size = 4;	break;
	case MMAT2:			size = 4;	break;
	case MMAT3:			size = 9;	break;
	case MMAT4:			size = 16;	break;
	default:			size = 0;
	}

	// TODO assert invalid uniform ID

	memcpy32(pArray->values, values, sizeof(float)*size); 
}

void CShaderInstance::setConstantifyVertex(s32 vertexID, GLfloat* values) {
	
	// TODO Assert vertexID index, null pointer

	SInternalParam* pArray = this->paramArrayVertexVertexShader;

	while (pArray->vertexInfoID != vertexID) {
		pArray++;
	}

	s32 size;
	switch (pArray->dType) {
	case VEC1F:			size = 1;	break;
	case VEC2:			size = 2;	break;
	case VEC3:			size = 3;	break;
	case VEC4:			size = 4;	break;
	case MMAT2:			size = 4;	break;
	case MMAT3:			size = 9;	break;
	case MMAT4:			size = 16;	break;
	default:			size = 0;
	}
	
	pArray->isConstantifiedOrUniform = true;

	memcpy32(pArray->values, values, sizeof(float)*size);
}

void CShaderInstance::unConstantifyVertex(s32 vertexID) {
	
	// TODO Assert vertexID index

	SInternalParam* pArray = this->paramArrayVertexVertexShader;

	while (pArray->vertexInfoID != vertexID) {
		pArray++;
	}

	pArray->isConstantifiedOrUniform = false;
}
