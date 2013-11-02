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

#ifndef OPENGL2

CShader*	CKLBOGLWrapper::createShader(SRenderState::RENDER_MODE /*mode*/, SHADER_TYPE type, const SParam* listParam) {
	return createShader(null, type, listParam);
}

// Shaders.
CShader*	CKLBOGLWrapper::createShader		(const char* /*source*/, SHADER_TYPE /*type*/, const SParam* listParam) {
	CShader* pNewShader = KLBNEW(CShader);
	if (pNewShader) {
		//
		// Parse the list of parameters
		//
		const SParam* parser = listParam;
				
		bool type;
				
		if (parser) {
			s32 uniCount = 0;
			s32 verCount = 0;
			while (parser->dType != END_LIST) {
				if (parser->isUniform) {
					uniCount++;
				} else {
					verCount++;
				}
				if (parser->dType & TEXTURE) {
					pNewShader->enableTexture = true;
				}
				if (parser->dType & COLOR) {
					pNewShader->enableColor = true;
				}
				parser++;
			}

			pNewShader->countUniform		= uniCount;
			pNewShader->countStreamInfo		= verCount;

			pNewShader->arrayParam			= KLBNEWA(CShader::SInternalParam,uniCount + verCount);

			if (pNewShader->arrayParam) {
				CShader::SInternalParam* pUniParam = pNewShader->arrayParam;
				CShader::SInternalParam* pVerParam = &pNewShader->arrayParam[uniCount];
				parser = listParam;

				while (parser->dType != END_LIST) {
					if (parser->isUniform) {
						pUniParam->param = *parser++;
						pUniParam++;
					} else {
						pVerParam->param = *parser++;
						pVerParam++;
					}
				}

			}
				
			type							= true;
		} else {
			pNewShader->countUniform		= 0;
			pNewShader->countStreamInfo		= 0;
			pNewShader->arrayParam			= null;
			type							= false;
		}


		if ((pNewShader->arrayParam && type) || (!type)) {
			pNewShader->refCount	= 0;
			pNewShader->shaderObj	= 1;
			pNewShader->pNext		= this->shaderList;
			this->shaderList		= pNewShader; 

			return pNewShader;
		}
			
		KLBDELETE(pNewShader);
		pNewShader = null;
	}
	return pNewShader;
}

// Rendering Shader.
CShaderSet*	CKLBOGLWrapper::createShaderSet	(CShader* pVertexShader, CShader* pPixelShader) {
	CShaderSet* pNewShaderSet = KLBNEW(CShaderSet);
	if (pNewShaderSet) {
		s32 size = pVertexShader->countUniform + pPixelShader->countUniform;
		if (size) {
			pNewShaderSet->locationArray = KLBNEWA(s32,size);
		} else {
			pNewShaderSet->locationArray = null;
		}

		if ((pNewShaderSet->locationArray) || (size == 0)) {
			pNewShaderSet->pInstances	= null;
			pNewShaderSet->pMgr			= this;

			pNewShaderSet->pNext		= this->shaderSetList;
			this->shaderSetList			= pNewShaderSet;

			pVertexShader->refCount++;
			pPixelShader->refCount++;

			pNewShaderSet->pixelShader	= pPixelShader;
			pNewShaderSet->vertexShader	= pVertexShader;

			pNewShaderSet->enableTexture	= pPixelShader->enableTexture | pVertexShader->enableTexture;
			pNewShaderSet->enableColor		= pPixelShader->enableColor   | pVertexShader->enableColor;

			return pNewShaderSet;
		}
		KLBDELETE(pNewShaderSet);
	}
	return null;
}

void CKLBOGLWrapper::releaseShader(CShader* pShader) {
	CShader* p = this->shaderList;
	CShader* prev = null;
	while (p != pShader) {
		prev = p;
		p = p->pNext;
	}

	//
	// Remove from link list.
	//
	if (prev == null) {
		this->shaderList = pShader->pNext;
	} else {
		prev->pNext = pShader->pNext;
	}

	// Free param
	if (pShader->arrayParam) {
		KLBDELETE(pShader->arrayParam);
		pShader->arrayParam = NULL;	// 2012.12.11  念の為
	}

	// Delete object
	KLBDELETE(pShader);
	pShader = NULL;	// 2012.12.11  念の為
}

void CKLBOGLWrapper::releaseShaderSet(CShaderSet* pFullShader) {
	klb_assertc(pFullShader != NULL,						"null shader set");

	CShaderSet* p		= this->shaderSetList;
	CShaderSet* pPrev	= null;

	while (p != pFullShader) {
		pPrev = p; p = p->pNext;
	}

	if (pPrev == null) {
		this->shaderSetList = p->pNext;
	} else {
		pPrev->pNext = p->pNext;
	}
	
	// Release all instances.
	pFullShader->releaseAllInstances();

	if (pFullShader->locationArray) {
		KLBDELETE(pFullShader->locationArray);
	}

	pFullShader->vertexShader->refCount--;
	pFullShader->pixelShader->refCount--;

	if (pFullShader->vertexShader->refCount == 0) {
		this->releaseShader(pFullShader->vertexShader);
		pFullShader->vertexShader = NULL;	// 2012.12.11  念の為
	}

	if (pFullShader->pixelShader->refCount == 0) {
		this->releaseShader(pFullShader->pixelShader);
		pFullShader->pixelShader = NULL;	// 2012.12.11  念の為
	}

	KLBDELETE(pFullShader);
	pFullShader = NULL;	// 2012.12.11  念の為
}

void CKLBOGLWrapper::draw(
			GLenum				mode, 
			CShaderInstance*	instance,
			CBuffer**			ppBuffer,
			u32					bufferCount,
			CIndexBuffer*		pIndexBuffer,
			CTextureUsage**		array_pTexture,
			s32*				uniformID,
			s32					indexCount) {
	klb_assert(instance		, "null shader instance");
	klb_assert(ppBuffer		, "null vertex buffer");
	klb_assert(pIndexBuffer	, "null index buffer");

	CShader* pVertexS	= instance->m_pShaderSet->vertexShader;
	s32 maxVertexInput	= pVertexS->countStreamInfo;

	// Force buffer to commit changes if they are VBO and were not updated.
	if (pIndexBuffer->VBOModified) {
		pIndexBuffer->commitVBO();
	}

	//
	// Force VBO Commit.
	//
	u32 n=0;
	while (n < bufferCount) {
		CBuffer* pBuffer = ppBuffer[n];
		n++;

		if (pBuffer->VBOModified) {
			pBuffer->commitVBO();
		}
	}
		
	//
	// Process all input for shaders.
	//

	s32 count			= 0;
	while (count < maxVertexInput) {
		CShaderInstance::SInternalParam* pParam = &instance->paramArrayVertexVertexShader[count];
		if (pParam->isConstantifiedOrUniform)
		// Constantified
		{
			switch (pParam->dType >> 4) {
			case (VERTEX>>4):
				// Do nothing.
				klb_assertAlways("Can not constantify coordinates.");
				break;
			case (COLOR>>4):
				_glBindBuffer(0);
				dglColor4f(pParam->values[0].f, pParam->values[1].f, pParam->values[2].f, pParam->values[3].f);
				dglColorPointer(4, GL_FLOAT, 0, null);	// Force constant.
				break;
			case (TEXTURE>>4):
				_glBindBuffer(0);
				dglMultiTexCoord4f(GL_TEXTURE0, pParam->values[0].f, pParam->values[1].f, pParam->values[2].f, pParam->values[3].f); 
				dglTexCoordPointer(2, GL_FLOAT, 0, null);	// Force constant.
				break;
			case (NORM>>4):
				_glBindBuffer(0);
				dglNormal3f(pParam->values[0].f, pParam->values[1].f, pParam->values[2].f);
				dglNormalPointer(GL_FLOAT, 0, null);	// Force constant.
				break;
			}
		}
		else
		// Buffer
		{
			//
			// Search in buffer the source mapping the shader input.
			//
			s32 vertID = instance->paramArrayVertexVertexShader[count].vertexInfoID;

			u32 n=0;
			while (n < bufferCount) {
				CBuffer* pBuffer = ppBuffer[n];
				n++;

				SVertexEntry* pEntries = pBuffer->structure;
				SVertexEntry* pEntriesEnd = &pEntries[pBuffer->dynCount + pBuffer->vboCount];
				while ((pEntries->vertexInfoID != vertID) && (pEntries < pEntriesEnd)) {
					pEntries++;
				}

				if (pEntries < pEntriesEnd) {
					GLint size = GLint(pParam->dType & 0xF);
					GLenum type	= GL_FLOAT;
					GLboolean normalized = GL_FALSE;
					if (size == VEC4BYTE) {
						size = 4;
						type = GL_UNSIGNED_BYTE;
						normalized = GL_TRUE;
					}

					if (pEntries->isVBO) {
						_glBindBuffer(pBuffer->vboID);
						switch (pParam->dType >> 4) {
						case (VERTEX>>4):
							dglVertexPointer		(size, type, (pBuffer->strideVBO * sizeof(float)), (const void*)((pEntries->offset + pBuffer->offsetDrawVBO) * sizeof(float)));
							break;
						case (COLOR>>4):
							dglColorPointer		(4, type, (pBuffer->strideVBO * sizeof(float)), (const void*)((pEntries->offset + pBuffer->offsetDrawVBO) * sizeof(float)));
							break;
						case (TEXTURE>>4):
							dglTexCoordPointer	(2, GL_FLOAT, (pBuffer->strideVBO * sizeof(float)), (const void*)((pEntries->offset + pBuffer->offsetDrawVBO) * sizeof(float)));
							break;
						case (NORM>>4):
							dglNormal3f(pParam->values[0].f, pParam->values[1].f, pParam->values[2].f);
							dglNormalPointer		(GL_FLOAT, (pBuffer->strideVBO * sizeof(float)), (const void*)((pEntries->offset + pBuffer->offsetDrawVBO) * sizeof(float)));
							break;
						}
					} else {
						_glBindBuffer(0);

						switch (pParam->dType >> 4) {
						case (VERTEX>>4):
							dglVertexPointer		(size, type, (pBuffer->strideDyn * sizeof(float)), &(((float*)pBuffer->ptrBuffer)[pEntries->offset + pBuffer->offsetDrawDyn]));
							break;
						case (COLOR>>4):
							dglColorPointer		(4, type, (pBuffer->strideDyn * sizeof(float)), &(((float*)pBuffer->ptrBuffer)[pEntries->offset + pBuffer->offsetDrawDyn]));
							break;
						case (TEXTURE>>4):
							dglTexCoordPointer	(2, GL_FLOAT, (pBuffer->strideDyn * sizeof(float)), &(((float*)pBuffer->ptrBuffer)[pEntries->offset + pBuffer->offsetDrawDyn]));
                      		break;
						case (NORM>>4):
							dglNormal3f(pParam->values[0].f, pParam->values[1].f, pParam->values[2].f);
							dglNormalPointer		(GL_FLOAT, (pBuffer->strideDyn * sizeof(float)), &(((float*)pBuffer->ptrBuffer)[pEntries->offset + pBuffer->offsetDrawDyn]));
							break;
						}
					}

					// skip search.
					break;
				}
			}
		}
		count++;
	}

	/*
		// TODO put "hint" in vertex def to be able to map correct API.
		// TODO setup all buffers OR constant.
	*/

	//
	// Process uniform parameters.
	//
	s32 countTexture = 0;
//	s32* pLocation = instance->m_pShaderSet->locationArray;	// Vertex + Pixel shader.

	if (instance->enableColor) {
		if (enableColor != TRUE_BOOL_U8) {
			enableColor = TRUE_BOOL_U8;
			dglEnableClientState(GL_COLOR_ARRAY);
		}
	} else {
		if (enableColor != FALSE_BOOL_U8) {
			enableColor = FALSE_BOOL_U8;
			dglDisableClientState(GL_COLOR_ARRAY);
		}
	}

	if (instance->enableTexture) {
		if (enableTexture != TRUE_BOOL_U8) {
			enableTexture = TRUE_BOOL_U8;
			dglEnable(GL_TEXTURE_2D);
			dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		for (s32 n=0; n < 2; n++) {
			CShaderInstance::SInternalParam* pParam;
			CShaderInstance::SInternalParam* maxVertexUniform;
		
			//
			// Vertex & Pixel Shader. (MUST BE SAME ORDER AS CreateShaderSet !!!)
			//
			if (n == 0) {
				pParam = instance->paramArrayUniformVertexShader;
				maxVertexUniform = &pParam[pVertexS->countUniform];
			} else {
				pParam = instance->paramArrayUniformPixelShader;
				maxVertexUniform = &pParam[instance->m_pShaderSet->pixelShader->countUniform];
			}

			while (pParam < maxVertexUniform) {
				switch (pParam->dType & 0x0F) {
				case TEX2D:
					//
					// Process texture
					//
					CTextureUsage**	pTex	= array_pTexture;
					if (pTex != null) {
						s32*			pUniID	= uniformID;
						while ((*pTex != null) && (pParam->vertexInfoID != *pUniID)) {
							pTex++;
							pUniID++;
						}

						if (*pTex != null) {
							// Assign texture to texture unit and apply parameters.
							CTextureUsage* pUsage = *pTex;
							pUsage->activate(countTexture);
						} else {
							// klb_assertAlways("Texture attribute is not mapped to a valid texture");
						}
					} else {
						klb_assertAlways("No texture information when shader use texture");
					}

					break;
				}
				pParam++;
			}
		}
	} else {
		if (enableTexture != FALSE_BOOL_U8) {
			enableTexture = FALSE_BOOL_U8;
			dglDisable(GL_TEXTURE_2D);
			dglDisableClientState(GL_TEXTURE_COORD_ARRAY);
			// Should be enough.
			// glActiveTexture(GL_TEXTURE0);					// Remove texture from sampler
			// glBindTexture(GL_TEXTURE0,0);
		}
	}

	//
	// Handle Index Buffer & Draw call.
	//
	if (pIndexBuffer->isVBO) {
		if (lastElementArrayBuffer != pIndexBuffer->vboID) {
			lastElementArrayBuffer = pIndexBuffer->vboID;
			dglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->vboID);
		}
		dglDrawElements(mode, indexCount, GL_UNSIGNED_SHORT, 0);
	} else {
		if (lastElementArrayBuffer != 0) {
			lastElementArrayBuffer = 0;
			dglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		dglDrawElements(mode, indexCount, GL_UNSIGNED_SHORT, &pIndexBuffer->ptrBuffer[pIndexBuffer->offsetDraw]);
	}
}
#endif
