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

CShader::CShader():
	enableTexture(false),
	enableColor(false)
{
	// Do nothing.
}

CShader::~CShader() {
	// Do nothing.
}

CShaderSet::CShaderSet() {
	// Do nothing.
}

CShaderSet::~CShaderSet() {
	// Do nothing.
}

//
// ShaderSet
//

CShaderInstance* CShaderSet::createInstance() {
	CShaderInstance* pNewInstance = KLBNEW(CShaderInstance);
	if (pNewInstance) {
		bool err = false;
		pNewInstance->m_pShaderSet	= this;
		
		pNewInstance->enableColor	= this->enableColor;
		pNewInstance->enableTexture = this->enableTexture;

		// Count number of vertex input on shader
		pNewInstance->paramArrayVertexVertexShader	= KLBNEWA(CShaderInstance::SInternalParam,this->vertexShader->countStreamInfo);

		err = (pNewInstance->paramArrayVertexVertexShader == null);

		if (this->vertexShader->countUniform) {
			pNewInstance->paramArrayUniformVertexShader	= KLBNEWA(CShaderInstance::SInternalParam,this->vertexShader->countUniform);
			err |= (pNewInstance->paramArrayUniformVertexShader == null);
		} else {
			pNewInstance->paramArrayUniformVertexShader	= null;
		}

		if (this->pixelShader->countUniform) {
			pNewInstance->paramArrayUniformPixelShader	= KLBNEWA(CShaderInstance::SInternalParam,this->pixelShader->countUniform);
			err |= (pNewInstance->paramArrayUniformPixelShader == null);
		} else {
			pNewInstance->paramArrayUniformPixelShader	= null;
		}

		if (err != false) {
			// free arrays
			if (pNewInstance->paramArrayUniformPixelShader) {
				KLBDELETE(pNewInstance->paramArrayUniformPixelShader);
			}

			if (pNewInstance->paramArrayUniformVertexShader) {
				KLBDELETE(pNewInstance->paramArrayUniformVertexShader);
			}

			if (pNewInstance->paramArrayVertexVertexShader) {
				KLBDELETE(pNewInstance->paramArrayVertexVertexShader);
			}

			KLBDELETE(pNewInstance);
			pNewInstance = null;
		} else {
			//
			// Copy all params to instance.
			//
			CShaderInstance::SInternalParam* pParam = pNewInstance->paramArrayVertexVertexShader;			
			CShader::SInternalParam* pSrc = &this->vertexShader->arrayParam[this->vertexShader->countUniform];
			for (s32 n=0; n < this->vertexShader->countStreamInfo; n++) {
				pParam->dType						= pSrc->param.dType;
				pParam->isConstantifiedOrUniform	= false;	// Vertex by default.
				pParam->vertexInfoID				= pSrc->param.vertexORuniformID;

				pParam++;
				pSrc++;
			}

			pParam = pNewInstance->paramArrayUniformVertexShader;
			pSrc = this->vertexShader->arrayParam;
			for (s32 n=0; n < this->vertexShader->countUniform; n++) {
				pParam->dType						= pSrc->param.dType;
				pParam->isConstantifiedOrUniform	= true;
				pParam->pTexture					= NULL;
				pParam->vertexInfoID				= pSrc->param.vertexORuniformID;
				memset32(pParam->values, 0, 16*4);
				pParam++;
				pSrc++;
			}

			pParam = pNewInstance->paramArrayUniformPixelShader;
			pSrc = this->pixelShader->arrayParam;
			for (s32 n=0; n < this->pixelShader->countUniform; n++) {
				pParam->dType						= pSrc->param.dType;
				pParam->isConstantifiedOrUniform	= true;
				pParam->pTexture					= NULL;
				pParam->vertexInfoID				= pSrc->param.vertexORuniformID;
				memset32(pParam->values, 0, 16*4);
				pParam++;
				pSrc++;
			}

			//
			// Link list.
			//
			pNewInstance->pNext = this->pInstances; 
			this->pInstances	= pNewInstance;
		}
	}
	return pNewInstance;
}

void CShaderSet::releaseAllInstances() {
	CShaderInstance* p = this->pInstances;
	while (p) {
		CShaderInstance* pNext = p->pNext;

		if (p->paramArrayUniformPixelShader)	{	KLBDELETE(p->paramArrayUniformPixelShader);		}
		if (p->paramArrayUniformVertexShader)	{	KLBDELETE(p->paramArrayUniformVertexShader);		}
		if (p->paramArrayVertexVertexShader)	{	KLBDELETE(p->paramArrayVertexVertexShader);		}

		KLBDELETE(p);
		p = pNext;
	}
	this->pInstances = null;
}

void CShaderSet::releaseInstance(CShaderInstance* pInstance) {
	klb_assertc(pInstance != NULL,						"null shader");
	klb_assertc(pInstance->m_pShaderSet == this,"Invalid shader set");

	CShaderInstance* p		= this->pInstances;
	CShaderInstance* pPrev	= null;

	while (p != pInstance) {
		pPrev = p; p = p->pNext;
	}

	if (pPrev == null) {
		this->pInstances = p->pNext;
	} else {
		pPrev->pNext = p->pNext;
	}

	if (p->paramArrayUniformPixelShader)	{	KLBDELETE(p->paramArrayUniformPixelShader);	}
	if (p->paramArrayUniformVertexShader)	{	KLBDELETE(p->paramArrayUniformVertexShader);	}
	if (p->paramArrayVertexVertexShader)	{	KLBDELETE(p->paramArrayVertexVertexShader);	}

	KLBDELETE(p);
}
