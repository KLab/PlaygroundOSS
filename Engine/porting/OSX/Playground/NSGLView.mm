/*
 File: NSGLView.m
 Abstract:
 The NSGLView class creates an OpenGL context and delegates to the OpenGLRenderer class for creating and drawing the shaders.
 
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

#import "NSGLView.h"
#import "OpenGLRenderer.h"
#include "CiOSPlatform.h"
#include "CiOSPathConv.h"

@interface NSGLView (PrivateMethods)
- (void)initGL;
- (void)drawView;

@end

@implementation NSGLView

OpenGLRenderer *m_renderer;

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime {
	// There is no autorelease pool when this method is called
	// because it will be called from a background thread
	// It's important to create one or you will leak objects
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
	[self drawView];
    
	[pool release];
	return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now, const CVTimeStamp *outputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) {
	CVReturn result = [(NSGLView *)displayLinkContext getFrameForTime : outputTime];
	return result;
}

- (void)awakeFromNib {
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		// Must specify the 3.2 Core Profile to use OpenGL 3.2
#if ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
		NSOpenGLPFAOpenGLProfile,
		NSOpenGLProfileVersion3_2Core,
#endif
		0
	};
    
	NSOpenGLPixelFormat *pf = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs] autorelease];
    
	if (!pf) {
		NSLog(@"No OpenGL pixel format");
	}
    
	// TODO: implement path overriding
    
	const char *g_pathInstall = PATH_INSTALL;
	const char *g_pathExtern = PATH_EXTERN;
	CPFInterface& pfif = CPFInterface::getInstance();
	// CiOSPathConv& pathconv = CiOSPathConv::getInstance();
	// pathconv.setPath(g_pathInstall, g_pathExtern);
	CiOSPlatform *pPlatform = new CiOSPlatform(nullptr, 1.0f);
	pfif.setPlatformRequest(pPlatform);
    
	GameSetup();
    
	pfif.client().setFilePath(NULL);
	NSLog(@"Playground launched");
	if (!pfif.client().initGame()) {
		klb_assertAlways("Could not initialize game, most likely memory error");
	}
    
    
	NSOpenGLContext *context = [[[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil] autorelease];
    
	[self setPixelFormat:pf];
    
	[self setOpenGLContext:context];
}

- (void)prepareOpenGL {
	[super prepareOpenGL];
    
	// Make all the OpenGL calls to setup rendering
	//  and build the necessary rendering objects
	[self initGL];
    
	// Create a display link capable of being used with all active displays
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    
	// Set the renderer output callback function
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
    
	// Set the display link for the current renderer
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    
	// Activate the display link
	CVDisplayLinkStart(displayLink);
}

- (void)initGL {
	// Make this openGL context current to the thread
	// (i.e. all openGL on this thread calls will go to this context)
	[[self openGLContext] makeCurrentContext];
    
	// Synchronize buffer swaps with vertical refresh rate
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
	// Init our renderer.  Use 0 for the defaultFBO which is appropriate for MacOS (but not iOS)
	m_renderer = [[OpenGLRenderer alloc] initWithDefaultFBO:0];
}

- (void)reshape {
	[super reshape];
    
	// We draw on a secondary thread through the display link
	// When resizing the view, -reshape is called automatically on the main thread
	// Add a mutex around to avoid the threads accessing the context simultaneously when resizing
	CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
    
	NSRect rect = [self bounds];
    
	[m_renderer resizeWithWidth:rect.size.width AndHeight:rect.size.height];
    
	CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void)drawView {
	[[self openGLContext] makeCurrentContext];
    
	// We draw on a secondary thread through the display link
	// When resizing the view, -reshape is called automatically on the main thread
	// Add a mutex around to avoid the threads accessing the context simultaneously	when resizing
	CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
    
	[m_renderer render];
    
	CGLFlushDrawable((CGLContextObj)[[self openGLContext] CGLContextObj]);
	CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void)dealloc {
	// Stop the display link BEFORE releasing anything in the view
	// otherwise the display link thread may call into the view and crash
	// when it encounters something that has been release
	CVDisplayLinkStop(displayLink);
    
	CVDisplayLinkRelease(displayLink);
    
	// Release the display link AFTER display link has been released
	[m_renderer release];
    
	[super dealloc];
}

@end
