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

CFrame::CFrame()
:pColBufferBuf		(NULL)
,pColBufferTex		(NULL)
,pDepthBufferBuf	(NULL)
,pDepthBufferTex	(NULL)
,pStencilBufferBuf	(NULL)
,next				(NULL)
,colorBuff			(0)
,depthBuff			(0)
,stencilBuff		(0)
,frameBuffID		(0)
{
}

CFrame::~CFrame() {
	if (pColBufferBuf) 		{ pColBufferBuf->decrementRefCount(); 		}
	if (pDepthBufferBuf) 	{ pDepthBufferBuf->decrementRefCount();		}
	if (pStencilBufferBuf)	{ pStencilBufferBuf->decrementRefCount();	}
}

bool CFrame::setColorBuffer(CImageBuffer*	pBuffer) {
	if (pColBufferBuf) {
		pColBufferBuf->decrementRefCount();
	}
	
	pColBufferBuf	= pBuffer;
	pColBufferTex	= NULL;
	
	if (pBuffer) {
		pBuffer->incrementRefCount();
		
		colorBuff = pBuffer->buffer;
	} else {
		colorBuff = 0;
	}
	
	#ifndef OPENGL2
		klb_assertAlways("TODO");
	#else
		dglBindFramebuffer			(	GL_FRAMEBUFFER, 	frameBuffID);
		dglFramebufferRenderbuffer	(	GL_FRAMEBUFFER,		GL_COLOR_ATTACHMENT0,
										GL_RENDERBUFFER,	colorBuff);
	#endif
	return true;
}

bool CFrame::setColorBuffer(CTexture*		pTexture, u32 mipLevel) {
	if (pColBufferBuf) {
		pColBufferBuf->decrementRefCount();
	}
	
	pColBufferBuf	= NULL;
	pColBufferTex	= pTexture;
	
	if (pTexture) {
		colorBuff = pTexture->texture;
	} else {
		colorBuff = 0;
	}
	
	#ifndef OPENGL2
        mipLevel = mipLevel;
		klb_assertAlways("TODO");
	#else
		dglBindFramebuffer			(	GL_FRAMEBUFFER, 	frameBuffID);
		dglFramebufferTexture2D		(	GL_FRAMEBUFFER,  	GL_COLOR_ATTACHMENT0,	
										GL_TEXTURE_2D /* Our engine use only that */,
										colorBuff, mipLevel);
	#endif
	return true;
}

bool CFrame::setDepthBuffer(CImageBuffer*	pBuffer) {
	if (pDepthBufferBuf) {
		pDepthBufferBuf->decrementRefCount();
	}
	
	pDepthBufferBuf	= pBuffer;
	pDepthBufferTex	= NULL;
	
	if (pBuffer) {
		pBuffer->incrementRefCount();
		
		depthBuff = pBuffer->buffer;
	} else {
		depthBuff = 0;
	}
	
	#ifndef OPENGL2
		klb_assertAlways("TODO");
	#else
		dglBindFramebuffer			(	GL_FRAMEBUFFER, 	frameBuffID);
		dglFramebufferRenderbuffer	(	GL_FRAMEBUFFER,		GL_DEPTH_ATTACHMENT,
										GL_RENDERBUFFER,	depthBuff);
	#endif
	return true;
}

bool CFrame::setDepthBuffer(CTexture*		pTexture, u32 mipLevel) {
	if (pDepthBufferBuf) {
		pDepthBufferBuf->decrementRefCount();
	}
	
	pDepthBufferBuf	= NULL;
	pDepthBufferTex	= pTexture;
	
	if (pTexture) {
		depthBuff = pTexture->texture;
	} else {
		depthBuff = 0;
	}
	
	#ifndef OPENGL2
        mipLevel = mipLevel;
		klb_assertAlways("TODO");
	#else
		dglBindFramebuffer			(	GL_FRAMEBUFFER, 	frameBuffID);
		dglFramebufferTexture2D		(	GL_FRAMEBUFFER,  	GL_DEPTH_ATTACHMENT,	
										GL_TEXTURE_2D /* Our engine use only that */,
										depthBuff, mipLevel);
	#endif
	return true;
}

bool CFrame::setStencilBuffer(CImageBuffer*	pBuffer) {
	if (pStencilBufferBuf) {
		pStencilBufferBuf->decrementRefCount();
	}
	
	pStencilBufferBuf	= pBuffer;
	
	if (pBuffer) {
		pBuffer->incrementRefCount();
		
		stencilBuff = pBuffer->buffer;
	} else {
		stencilBuff = 0;
	}
	
	#ifndef OPENGL2
		klb_assertAlways("TODO");
	#else
		dglBindFramebuffer			(	GL_FRAMEBUFFER, 	frameBuffID);
		dglFramebufferRenderbuffer	(	GL_FRAMEBUFFER,		GL_STENCIL_ATTACHMENT,
										GL_RENDERBUFFER,	stencilBuff);
	#endif
	return true;
}

bool CFrame::use(bool /*check*/) {
	#ifndef OPENGL2
	#else
	#endif	
	return false;
}
