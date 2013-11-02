/*
 File: OpenGLRenderer.m
 Abstract:
 The OpenGLRenderer class creates and draws objects.
 Most of the code is OS independent.
 
 Version: 1.6
 
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple
 Inc. ("Apple") in consideration of your agreement to the following
 terms, and your use, installation, modification or redistribution of
 this Apple software constitutes acceptance of these terms.  If you do
 not agree with these terms, please do not use, install, modify or
 redistribute this Apple software.
 
 In consideration of your agreement to abide by the following terms, and
 subject to these terms, Apple grants you a personal, non-exclusive
 license, under Apple's copyrights in this original Apple software (the
 "Apple Software"), to use, reproduce, modify and redistribute the Apple
 Software, with or without modifications, in source and/or binary forms;
 provided that if you redistribute the Apple Software in its entirety and
 without modifications, you must retain this notice and the following
 text and disclaimers in all such redistributions of the Apple Software.
 Neither the name, trademarks, service marks or logos of Apple Inc. may
 be used to endorse or promote products derived from the Apple Software
 without specific prior written permission from Apple.  Except as
 expressly stated in this notice, no other rights or licenses, express or
 implied, are granted by Apple herein, including but not limited to any
 patent rights that may be infringed by your derivative works or by other
 works in which the Apple Software may be incorporated.
 
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
 MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
 STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 
 Copyright (C) 2012 Apple Inc. All Rights Reserved.
 
 */

#import "OpenGLRenderer.h"
#import "matrixUtil.h"
#import "imageUtil.h"
#import "modelUtil.h"
#import "sourceUtil.h"
#include "CiOSPlatform.h"


#define GetGLError()                                    \
{                                                       \
GLenum err = glGetError();                          \
while (err != GL_NO_ERROR) {                        \
NSLog(@"GLError %s set in File:%s Line:%d\n",   \
GetGLErrorString(err),                  \
__FILE__,                               \
__LINE__);                              \
err = glGetError();                             \
}                                                   \
}

// Toggle this to disable vertex buffer objects
// (i.e. use client-side vertex array objects)
// This must be 1 if using the GL3 Core Profile on the Mac
#define USE_VERTEX_BUFFER_OBJECTS 1

// Indicies to which we will set vertex array attibutes
// See buildVAO and buildProgram
enum {
	POS_ATTRIB_IDX,
	NORMAL_ATTRIB_IDX,
	TEXCOORD_ATTRIB_IDX
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

@implementation OpenGLRenderer

GLuint m_characterPrgName;
GLint m_characterMvpUniformIdx;
GLuint m_characterVAOName;
GLuint m_characterTexName;
demoModel *m_characterModel;
GLenum m_characterPrimType;
GLenum m_characterElementType;
GLuint m_characterNumElements;
GLfloat m_characterAngle;


GLuint m_viewWidth;
GLuint m_viewHeight;


GLboolean m_useVBOs;

- (void)resizeWithWidth:(GLuint)width AndHeight:(GLuint)height {
	glViewport(0, 0, width, height);
    
	m_viewWidth = width;
	m_viewHeight = height;
}

- (void)render {
	IClientRequest& client = CPFInterface::getInstance().client();
	s32 deltaT = client.getFrameTime();
	client.frameFlip(deltaT);
	// Set up the modelview and projection matricies
	GLfloat modelView[16];
	GLfloat projection[16];
	GLfloat mvp[16];
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Use the program for rendering our character
	glUseProgram(m_characterPrgName);
    
	// Calculate the projection matrix
	mtxLoadPerspective(projection, 90, (float)m_viewWidth / (float)m_viewHeight, 5.0, 10000);
    
	// Calculate the modelview matrix to render our character
	//  at the proper position and rotation
	mtxLoadTranslate(modelView, 0, 150, -450);
	mtxRotateXApply(modelView, -90.0f);
	mtxRotateApply(modelView, m_characterAngle, 0.7, 0.3, 1);
    
	// Multiply the modelview and projection matrix and set it in the shader
	mtxMultiply(mvp, projection, modelView);
    
	// Have our shader use the modelview projection matrix
	// that we calculated above
	glUniformMatrix4fv(m_characterMvpUniformIdx, 1, GL_FALSE, mvp);
    
	// Bind the texture to be used
	glBindTexture(GL_TEXTURE_2D, m_characterTexName);
    
	// Bind our vertex array object
	glBindVertexArray(m_characterVAOName);
    
	// Cull back faces now that we no longer render
	// with an inverted matrix
	glCullFace(GL_BACK);
    
	// Draw our character
	if (m_useVBOs) {
		glDrawElements(GL_TRIANGLES, m_characterNumElements, m_characterElementType, 0);
	}
	else {
		glDrawElements(GL_TRIANGLES, m_characterNumElements, m_characterElementType, m_characterModel->elements);
	}
    
	// Update the angle so our character keeps spinning
	m_characterAngle++;
}

static GLsizei GetGLTypeSize(GLenum type) {
	switch (type) {
		case GL_BYTE:
			return sizeof(GLbyte);
            
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
            
		case GL_SHORT:
			return sizeof(GLshort);
            
		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort);
            
		case GL_INT:
			return sizeof(GLint);
            
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
            
		case GL_FLOAT:
			return sizeof(GLfloat);
	}
	return 0;
}

- (GLuint)buildTexture:(demoImage *)image {
	GLuint texName;
    
	// Create a texture object to apply to model
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
    
	// Set up filter and wrap modes for this texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
	// Indicate that pixel rows are tightly packed
	//  (defaults to stride of 4 which is kind of only good for
	//  RGBA or FLOAT data types)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
	// Allocate and load image data into texture
	glTexImage2D(GL_TEXTURE_2D, 0, image->format, image->width, image->height, 0,
	             image->format, image->type, image->data);
    
	// Create mipmaps for this texture for better image quality
	glGenerateMipmap(GL_TEXTURE_2D);
    
	GetGLError();
    
	return texName;
}

- (id)initWithDefaultFBO:(GLuint)defaultFBOName {
	if ((self = [super init])) {
		NSLog(@"%s %s", glGetString(GL_RENDERER), glGetString(GL_VERSION));
        
		////////////////////////////////////////////////////
		// Build all of our and setup initial state here  //
		// Don't wait until our real time run loop begins //
		////////////////////////////////////////////////////
        
		m_defaultFBOName = defaultFBOName;
        
		m_viewWidth = 100;
		m_viewHeight = 100;
        
        
		m_characterAngle = 0;
        
		m_useVBOs = USE_VERTEX_BUFFER_OBJECTS;
        
		NSString *filePathName = nil;
        
		//////////////////////////////
		// Load our character model //
		//////////////////////////////
        
		filePathName = [[NSBundle mainBundle] pathForResource:@"demon" ofType:@"model"];
		m_characterModel = mdlLoadModel([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);
        
		// Cache the number of element and primType to use later in our glDrawElements calls
		m_characterNumElements = m_characterModel->numElements;
		m_characterPrimType = m_characterModel->primType;
		m_characterElementType = m_characterModel->elementType;
        
		if (m_useVBOs) {
			//If we're using VBOs we can destroy all this memory since buffers are
			// loaded into GL and we've saved anything else we need
			mdlDestroyModel(m_characterModel);
			m_characterModel = NULL;
		}
        
        
		////////////////////////////////////
		// Load texture for our character //
		////////////////////////////////////
        
		filePathName = [[NSBundle mainBundle] pathForResource:@"demon" ofType:@"png"];
		demoImage *image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding], false);
        
		// Build a texture object with our image data
		m_characterTexName = [self buildTexture:image];
        
		// We can destroy the image once it's loaded into GL
		imgDestroyImage(image);
        
        
		////////////////////////////////////////////////////
		// Load and Setup shaders for character rendering //
		////////////////////////////////////////////////////
        
		demoSource *vtxSource = NULL;
		demoSource *frgSource = NULL;
        
		filePathName = [[NSBundle mainBundle] pathForResource:@"character" ofType:@"vsh"];
		vtxSource = srcLoadSource([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);
        
		filePathName = [[NSBundle mainBundle] pathForResource:@"character" ofType:@"fsh"];
		frgSource = srcLoadSource([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);
        
		srcDestroySource(vtxSource);
		srcDestroySource(frgSource);
        
		m_characterMvpUniformIdx = glGetUniformLocation(m_characterPrgName, "modelViewProjectionMatrix");
        
		if (m_characterMvpUniformIdx < 0) {
			NSLog(@"No modelViewProjectionMatrix in character shader");
		}
        
		////////////////////////////////////////////////
		// Set up OpenGL state that will never change //
		////////////////////////////////////////////////
        
		// Depth test will always be enabled
		glEnable(GL_DEPTH_TEST);
        
		// We will always cull back faces for better performance
		glEnable(GL_CULL_FACE);
        
		// Always use this clear color
		glClearColor(0.5f, 0.4f, 0.5f, 1.0f);
        
		// Draw our scene once without presenting the rendered image.
		//   This is done in order to pre-warm OpenGL
		// We don't need to present the buffer since we don't actually want the
		//   user to see this, we're only drawing as a pre-warm stage
		[self render];
        
		// Reset the m_characterAngle which is incremented in render
		m_characterAngle = 0;
        
		// Check for errors to make sure all of our setup went ok
		GetGLError();
	}
    
	return self;
}

- (void)dealloc {
	// Cleanup all OpenGL objects and
	glDeleteTextures(1, &m_characterTexName);
    
	mdlDestroyModel(m_characterModel);
    
	[super dealloc];
}

@end
