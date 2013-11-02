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

#ifdef OPENGL2

#include "shaderSource.inl"

const char* CKLBOGLWrapper::patch(const char* shader, const char* glslTransform) {
	return NULL;
}

CShader*	CKLBOGLWrapper::createShader(SRenderState::RENDER_MODE mode, SHADER_TYPE type, const SParam* listParam) {
	const char* src = null;

	if (type == VERTEX_SHADER) {
		switch (mode) {
		case SRenderState::ONLY_COLOR:
			src = s_vertColorOnly;
			break;
		case SRenderState::ONLY_TEXTURE:
			src = s_vertTexture;
			break;
		case SRenderState::TEXTURE_MUL_COLOR:
			src = sh_vertColTexture;
			break;
		case SRenderState::ES2_BRIGHTNESS:
			src = sh_brightNessVS;
			break;
		case SRenderState::ES2_COLORIZE:
		case SRenderState::ES2_SATURATE:
		case SRenderState::ES2_RAMP:
			src = sh_vertColTexture;
			break;
		case SRenderState::ES2_TONE:
			if (this->support3DTexture()) {
				src = sh_toneVS_3D;
			} else {
				src = sh_toneVS_2D;
			}
			break;
		case SRenderState::ES2_MOSAIC:
			src = sh_mosaicVS;
			break;
		}
	} else {
		switch (mode) {
		case SRenderState::ONLY_COLOR:
			src = s_fragColorOnly;
			break;
		case SRenderState::ONLY_TEXTURE:
			src = s_fragTexture;
			break;
		case SRenderState::TEXTURE_MUL_COLOR:
			src = sh_fragColTexture;
			break;
		case SRenderState::ES2_BRIGHTNESS:
			src = sh_fragColTexture;
			break;
		case SRenderState::ES2_COLORIZE:
			src = sh_colorizePS;
			break;
		case SRenderState::ES2_SATURATE:
			src = sh_saturatePS;
			break;
		case SRenderState::ES2_RAMP:
			src = sh_curvePS;
			break;
		case SRenderState::ES2_TONE:
			if (this->support3DTexture()) {
				src = sh_tonePS_3D;
			} else {
				src = sh_tonePS_2D;
			}
			break;
		case SRenderState::ES2_MOSAIC:
			src = sh_mosaicPS;
			break;
		}
	}

	return createShader(src, type, listParam);
}

// Shaders.
CShader*	CKLBOGLWrapper::createShader		(const char* source, SHADER_TYPE type, const SParam* listParam) {
	CShader* pNewShader = KLBNEW(CShader);
	if (pNewShader) {
		GLuint shaderID = dglCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
		if (shaderID != 0) {
			GLint compiled;

			dglShaderSource(shaderID, 1, &source, null);
			// Compile the shader
			dglCompileShader(shaderID);
			// Check the compile status
			dglGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

			if (compiled) {
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
					pNewShader->shaderObj	= shaderID;
					pNewShader->pNext		= this->shaderList;
					this->shaderList		= pNewShader; 

					return pNewShader;
				}
			}
			dglDeleteShader(shaderID);
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
			GLuint progID = dglCreateProgram();
			if (progID) {
				// Attach
				dglAttachShader(progID, pVertexShader->shaderObj);
				dglAttachShader(progID, pPixelShader->shaderObj);
			
				pNewShaderSet->pInstances	= null;
				pNewShaderSet->pMgr			= this;

				//
				// Iterate through vertex shader attribute 
				//
				s32 iterator = 0;
				CShader::SInternalParam* pParam = &pVertexShader->arrayParam[pVertexShader->countUniform];
				while (iterator < pVertexShader->countStreamInfo) {
					dglBindAttribLocation(progID, iterator, pParam->param.name);	// Actually only associated with vertex.
					iterator++;
					pParam++;				
				}

				dglLinkProgram(progID);

				GLint success = 0;
				dglGetProgramiv(progID, GL_LINK_STATUS, &success);
				if (success)
				{
					s32 uniformIndex = 0;
					for (s32 n=0; n < 2; n++) {
						CShader* pShader;
						if (n==0) { pShader = pVertexShader; } else { pShader = pPixelShader; }
				
						CShader::SInternalParam* pParam = pShader->arrayParam;
						iterator = 0;
						while (iterator < pShader->countUniform) {
							// Becomes UniformID
							pNewShaderSet->locationArray[uniformIndex++] = dglGetUniformLocation(progID, pParam->param.name);
							iterator++;
							pParam++;
						}
					}

					pNewShaderSet->programObj	= progID;
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
				dglDeleteProgram(progID);
			}

			if (pNewShaderSet->locationArray) {
				KLBDELETE(pNewShaderSet->locationArray);
			}
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

	//
	// Delete shader from GL
	//
	dglDeleteShader(pShader->shaderObj);

	// Free param
	if (pShader->arrayParam) {
		KLBDELETE(pShader->arrayParam);
	}

	// Delete object
	KLBDELETE(pShader);
}

void CKLBOGLWrapper::releaseShaderSet(CShaderSet* pFullShader) {
	klb_assertc(pFullShader != nullptr,						"null shader set");

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
	// Release open GL associated program.

	dglDeleteProgram(pFullShader->programObj);

	if (pFullShader->locationArray) {
		KLBDELETE(pFullShader->locationArray);
	}

	pFullShader->vertexShader->refCount--;
	pFullShader->pixelShader->refCount--;

	if (pFullShader->vertexShader->refCount == 0) {
		this->releaseShader(pFullShader->vertexShader);
	}

	if (pFullShader->pixelShader->refCount == 0) {
		this->releaseShader(pFullShader->pixelShader);
	}

	KLBDELETE(pFullShader);
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

	// Force buffer to commit changes if they are VBO and were not updated.

	u32 n=0;
	while (n < bufferCount) {
		CBuffer* pBuffer = ppBuffer[n];
		n++;

		if (pBuffer->VBOModified) {
			pBuffer->commitVBO();
		}
	}
	
	if (pIndexBuffer->VBOModified) {
		pIndexBuffer->commitVBO();
	}
	
	if (m_lastShaderInstance != instance) {
		// Same Shader with different param is also a possibility.
		if (!m_lastShaderInstance || (m_lastShaderInstance->m_pShaderSet != instance->m_pShaderSet)) {
			// Use Shader only when program really changes.
			dglUseProgram(instance->m_pShaderSet->programObj);
		}

		// Transform matrix
//		u32 _projectionUniform = dglGetUniformLocation(instance->m_pShaderSet->programObj, "Projection");
//		dglUniformMatrix4fv(_projectionUniform, 1, 0, displayMatrix2D);
		m_lastShaderInstance = instance;
	}
    u32 _projectionUniform = dglGetUniformLocation(instance->m_pShaderSet->programObj, "Projection");
    dglUniformMatrix4fv(_projectionUniform, 1, 0, displayMatrix2D);

	//
	// Process all input for shaders.
	//
	CShader* pVertexS	= instance->m_pShaderSet->vertexShader;
	s32 maxVertexInput	= pVertexS->countStreamInfo;
	s32 count			= 0;
	while (count < maxVertexInput) {
		CShaderInstance::SInternalParam* pParam = &instance->paramArrayVertexVertexShader[count];
		if (pParam->isConstantifiedOrUniform)
		{
			dglDisableVertexAttribArray(count);
			
			// Constantified
			switch (pParam->dType & 0x0F) {
			case VEC1F:
				dglVertexAttrib1fv(count, (GLfloat*)pParam->values);
				break;
			case VEC2:
				dglVertexAttrib2fv(count, (GLfloat*)pParam->values);
				break;
			case VEC3:
				dglVertexAttrib3fv(count, (GLfloat*)pParam->values);
				break;
			case VEC4BYTE:
			case VEC4:
				dglVertexAttrib4fv(count, (GLfloat*)pParam->values);
				break;
			default:
				klb_assertAlways("Invalid Type for vertex attribute");
			}
		} else {
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
						dglEnableVertexAttribArray(count);
						dglVertexAttribPointer(				count, 
															size, 
															type, 
															normalized, 
															(pBuffer->strideVBO * sizeof(float)), 
															(const void*)((pEntries->offset + pBuffer->offsetDrawVBO) * sizeof(float)));
					} else {
						_glBindBuffer(0);
						dglEnableVertexAttribArray(count);
						dglVertexAttribPointer(				count,
															size,
															type,
															normalized,
															(pBuffer->strideDyn * sizeof(float)),
															&(((float*)pBuffer->ptrBuffer)[pEntries->offset + pBuffer->offsetDrawDyn]));
					}
					// Break and go to next array.
					break;
				}
			}
		}
		count++;
	}

	//
	// Process uniform parameters.
	//
	count = 0;
	s32 countTexture = 0;
	s32* pLocation = instance->m_pShaderSet->locationArray;	// Vertex + Pixel shader.

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
			s32 location = *pLocation++;
			switch (pParam->dType & 0x0F) {
			case VEC1I:
				dglUniform1iv(location, 1, (GLint*)(pParam->values));
				break;
			case VEC1F:
				dglUniform1fv(location, 1, (GLfloat*)(pParam->values));
				break;
			case VEC2:
				dglUniform2fv(location, 1, (GLfloat*)(pParam->values));
				break;
			case VEC3:
				dglUniform3fv(location, 1, (GLfloat*)(pParam->values));
				break;
			case VEC4:
				dglUniform4fv(location, 1, (GLfloat*)(pParam->values));
				break;
			case MMAT2:
				dglUniformMatrix2fv(location, 1, GL_FALSE, (GLfloat*)(pParam->values));
				break;
			case MMAT3:
				dglUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*)(pParam->values));
				break;
			case MMAT4:
				dglUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)(pParam->values));
				break;
			case TEX2D:
				if (pParam->pTexture == NULL) {
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

							// Link active texture unit to uniform
							dglUniform1i(location, countTexture);
							countTexture++;
						} else {
							// klb_assertAlways("Texture attribute is not mapped to a valid texture");
						}
					} else {
						klb_assertAlways("No texture information when shader use texture");
					}
				} /*else {
					// Assign texture to texture unit and apply parameters.
					CTextureUsage* pUsage = pParam->pTexture;
					pUsage->activate(countTexture);
					// Link active texture unit to uniform
					dglUniform1i(location, countTexture);
					countTexture++;
				}*/

				break;
			}
			pParam++;
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

