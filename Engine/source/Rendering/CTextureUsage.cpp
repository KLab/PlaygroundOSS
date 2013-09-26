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

CTextureUsage::CTextureUsage()
:samplingSetupDone(false) {
	// Do nothing.
}

CTextureUsage::~CTextureUsage() {
	// Do nothing.
}

//
// Texture usage.
//

void	CTextureUsage::init(CTextureBase* pTexture) {
	this->samplingSetupDone = false;
	this->minSampling = GL_LINEAR;

	CTexture* topTexture = pTexture->pMaster;
	if (topTexture->isMipmapped) {
		this->maxSampling = GL_LINEAR_MIPMAP_NEAREST;
	} else {
		this->maxSampling = GL_LINEAR;
	}

	this->pTexture	= pTexture;
	this->pNext		= null;
	this->uMode		= GL_REPEAT;
	this->vMode		= GL_REPEAT;
}

void 	CTextureUsage::activate(s32 sampler) {
	// Select NEW(texture id.
	CTexture* pTexture = this->pTexture->pMaster;
	if (pTexture->isDoubleBuffered) {
		GLuint	textureID;
		
		if (pMgr->getFrame() != pTexture->frame) {
			// Texture IS double buffered
			if (pTexture->textureDoubleBuff == pTexture->activeTexture) {
				textureID = pTexture->texture;
			} else {
				textureID = pTexture->textureDoubleBuff;
			}
			pTexture->activeTexture = textureID;
			pTexture->frame = pMgr->getFrame();
		} else {
			textureID = pTexture->activeTexture;
		}
	}

	// Activate.
	pTexture->pMgr->assignSampler(this, sampler);
}

void	CTextureUsage::setSampling(SAMPLING minmode, SAMPLING magmode) {
	samplingSetupDone = false;

	switch (minmode) {
	case LINEAR:
		this->minSampling = GL_LINEAR;
		break;
	case NEAREST:
	default:
		this->minSampling = GL_NEAREST;
		break;
	}

	if (pTexture->pMaster->isMipmapped) {
		GLuint samplingType;
		switch (magmode & 1) {
		case LINEAR:
			if (magmode & BLEND_IFMIPMAP_BIT) {
				samplingType = GL_LINEAR_MIPMAP_LINEAR;
			} else {
				samplingType = GL_LINEAR_MIPMAP_NEAREST;
			}
			break;
		default:
		case NEAREST:
			if (magmode & BLEND_IFMIPMAP_BIT) {
				samplingType = GL_NEAREST_MIPMAP_LINEAR;
			} else {
				samplingType = GL_NEAREST_MIPMAP_NEAREST;
			}
			break;
		}
		this->maxSampling = samplingType;
	} else {
		switch (magmode) {
		case LINEAR:
			this->maxSampling = GL_LINEAR;
			break;
		case NEAREST:
		default:
			this->maxSampling = GL_NEAREST;
			break;
		}
	}
}

void 	CTextureUsage::setWrapping(WRAPPING U_mode, WRAPPING V_mode) {
	GLenum mode;
	switch (U_mode) {
	case CLAMP_TO_EDGE:
#ifdef STD_OPENGL
		mode = GL_CLAMP;
#else
		mode = GL_CLAMP_TO_EDGE;
#endif
		break;
	/* Only in OpenGL 2.0 : Disabled for now.
	case MIRRORED:
		mode = GL_MIRRORED_REPEAT;
		break;
		*/
	default:
	case REPEAT:
		mode = GL_REPEAT;
		break;
	};

	this->uMode = mode;

	switch (V_mode) {
	case CLAMP_TO_EDGE:
#ifdef STD_OPENGL
		mode = GL_CLAMP;
#else
		mode = GL_CLAMP_TO_EDGE;
#endif
		break;
	/* Only in OpenGL 2.0 : Disabled for now.
	case MIRRORED:
		mode = GL_MIRRORED_REPEAT;
		break;*/
	default:
	case REPEAT:
		mode = GL_REPEAT;
		break;
	};

	this->vMode = mode;
}

