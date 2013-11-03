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
#ifndef __GL_API_DEBUG_WRAPPER__
#define __GL_API_DEBUG_WRAPPER__

// #define USE_DEBUG_WRAPPER

// ---------------------------------------------------------------------------------------
//
//  No OpenGLES wrapper (1.x & 2.0)
//
// ---------------------------------------------------------------------------------------
#ifndef USE_DEBUG_WRAPPER
	#if defined(__APPLE__)
        #include "TargetConditionals.h"
		#if TARGET_OS_IPHONE // iOS devices or iOS Simulator
			#ifdef OPENGL2
			#import <OpenGLES/ES2/gl.h>
			#import <OpenGLES/ES2/glext.h>
			#else
			#import <OpenGLES/ES1/gl.h>
			#import <OpenGLES/ES1/glext.h>
			#endif
		#else // Mac OS X
			// #include "glew.h"
			#include <GLUT/glut.h>
			#include <OpenGL/gl.h>
            #include <OpenGL/glext.h>
			#define STD_OPENGL
		#endif
	#else
		#ifdef OPENGL2
		#include "GLES2/gl2.h"
		#include "GLES2/gl2ext.h"
		// The header file which is not in the Android environment.
		// #include "GLES2/gl2extimg.h"
		#else
			#ifdef _WIN32
				#include <windows.h>
				#include "glew.h"
				#include "glut.h"
				#include <gl/GL.h>
				#include "glext.h"
				#define STD_OPENGL
			#else
				#include "GLES/gl.h"
			#endif
		#endif
	#endif

	#ifndef OPENGL2
	// Available only in Common profile
	#define dglAlphaFunc glAlphaFunc
	#define dglClearColor   glClearColor 
	#define dglClearDepthf   glClearDepthf 
	#define dglClipPlanef   glClipPlanef 
	#define dglColor4f   glColor4f 
	#define dglDepthRangef   glDepthRangef 
	#define dglFogf   glFogf 
	#define dglFogfv   glFogfv 
	#define dglFrustumf   glFrustumf 
	#define dglGetClipPlanef   glGetClipPlanef 
	#define dglGetFloatv   glGetFloatv 
	#define dglGetLightfv   glGetLightfv 
	#define dglGetMaterialfv   glGetMaterialfv 
	#define dglGetTexEnvfv   glGetTexEnvfv 
	#define dglGetTexParameterfv   glGetTexParameterfv 
	#define dglLightModelf   glLightModelf 
	#define dglLightModelfv   glLightModelfv 
	#define dglLightf   glLightf 
	#define dglLightfv   glLightfv 
	#define dglLineWidth   glLineWidth 
	#define dglLoadMatrixf   glLoadMatrixf 
	#define dglMaterialf   glMaterialf 
	#define dglMaterialfv   glMaterialfv 
	#define dglMultMatrixf   glMultMatrixf 
	#define dglMultiTexCoord4f   glMultiTexCoord4f 
	#define dglNormal3f   glNormal3f 
	#define dglOrthof   glOrthof 
	#define dglPointParameterf   glPointParameterf 
	#define dglPointParameterfv   glPointParameterfv 
	#define dglPointSize   glPointSize 
	#define dglPolygonOffset   glPolygonOffset 
	#define dglRotatef   glRotatef 
	#define dglScalef   glScalef 
	#define dglTexEnvf   glTexEnvf 
	#define dglTexEnvfv   glTexEnvfv 
	#define dglTexParameterf   glTexParameterf 
	#define dglTexParameterfv   glTexParameterfv 
	#define dglTranslatef   glTranslatef 

	// Available in both Common and Common-Lite profiles
	#define dglActiveTexture   glActiveTexture 
	#define dglAlphaFuncx   glAlphaFuncx 
	#define dglBindBuffer   glBindBuffer 
	#define dglBindTexture   glBindTexture 
	#define dglBlendFunc   glBlendFunc 
	#define dglBufferData   glBufferData 
	#define dglBufferSubData   glBufferSubData 
	#define dglClear   glClear 
	#define dglClearColorx   glClearColorx 
	#define dglClearDepthx   glClearDepthx 
	#define dglClearStencil   glClearStencil 
	#define dglClientActiveTexture   glClientActiveTexture 
	#define dglClipPlanex   glClipPlanex 
	#define dglColor4ub   glColor4ub 
	#define dglColor4x   glColor4x 
	#define dglColorMask   glColorMask 
	#define dglColorPointer   glColorPointer 
	#define dglCompressedTexImage2D   glCompressedTexImage2D 
	#define dglCompressedTexSubImage2D   glCompressedTexSubImage2D 
	#define dglCopyTexImage2D   glCopyTexImage2D 
	#define dglCopyTexSubImage2D   glCopyTexSubImage2D 
	#define dglCullFace   glCullFace 
	#define dglDeleteBuffers   glDeleteBuffers 
	#define dglDeleteTextures   glDeleteTextures 
	#define dglDepthFunc   glDepthFunc 
	#define dglDepthMask   glDepthMask 
	#define dglDepthRangex   glDepthRangex 
	#define dglDisable   glDisable 
	#define dglDisableClientState   glDisableClientState 
	#define dglDrawArrays   glDrawArrays 
	#define dglDrawElements   glDrawElements 
	#define dglEnable   glEnable 
	#define dglEnableClientState   glEnableClientState 
	#define dglFinish   glFinish 
	#define dglFlush   glFlush 
	#define dglFogx   glFogx 
	#define dglFogxv   glFogxv 
	#define dglFrontFace   glFrontFace 
	#define dglFrustumx   glFrustumx 
	#define dglGetBooleanv   glGetBooleanv 
	#define dglGetBufferParameteriv   glGetBufferParameteriv 
	#define dglGetClipPlanex   glGetClipPlanex 
	#define dglGenBuffers   glGenBuffers 
	#define dglGenTextures   glGenTextures 
	#define dglGetError   glGetError 
	#define dglGetFixedv   glGetFixedv 
	#define dglGetIntegerv   glGetIntegerv 
	#define dglGetLightxv   glGetLightxv 
	#define dglGetMaterialxv   glGetMaterialxv 
	#define dglGetPointerv   glGetPointerv 
	#define dglGetString   glGetString 
	#define dglGetTexEnviv   glGetTexEnviv 
	#define dglGetTexEnvxv   glGetTexEnvxv 
	#define dglGetTexParameteriv   glGetTexParameteriv 
	#define dglGetTexParameterxv   glGetTexParameterxv 
	#define dglHint   glHint 
	#define dglIsBuffer   glIsBuffer 
	#define dglIsEnabled   glIsEnabled 
	#define dglIsTexture   glIsTexture 
	#define dglLightModelx   glLightModelx 
	#define dglLightModelxv   glLightModelxv 
	#define dglLightx   glLightx 
	#define dglLightxv   glLightxv 
	#define dglLineWidthx   glLineWidthx 
	#define dglLoadIdentity   glLoadIdentity 
	#define dglLoadMatrixx   glLoadMatrixx 
	#define dglLogicOp   glLogicOp 
	#define dglMaterialx   glMaterialx 
	#define dglMaterialxv   glMaterialxv 
	#define dglMatrixMode   glMatrixMode 
	#define dglMultMatrixx   glMultMatrixx 
	#define dglMultiTexCoord4x   glMultiTexCoord4x 
	#define dglNormal3x   glNormal3x 
	#define dglNormalPointer   glNormalPointer 
	#define dglOrthox   glOrthox 
	#define dglPixelStorei   glPixelStorei 
	#define dglPointParameterx   glPointParameterx 
	#define dglPointParameterxv   glPointParameterxv 
	#define dglPointSizex   glPointSizex 
	#define dglPolygonOffsetx   glPolygonOffsetx 
	#define dglPopMatrix   glPopMatrix 
	#define dglPushMatrix   glPushMatrix 
	#define dglReadPixels   glReadPixels 
	#define dglRotatex   glRotatex 
	#define dglSampleCoverage   glSampleCoverage 
	#define dglSampleCoveragex   glSampleCoveragex 
	#define dglScalex   glScalex 
	#define dglScissor   glScissor 
	#define dglShadeModel   glShadeModel 
	#define dglStencilFunc   glStencilFunc 
	#define dglStencilMask   glStencilMask 
	#define dglStencilOp   glStencilOp 
	#define dglTexCoordPointer   glTexCoordPointer 
	#define dglTexEnvi   glTexEnvi 
	#define dglTexEnvx   glTexEnvx 
	#define dglTexEnviv   glTexEnviv 
	#define dglTexEnvxv   glTexEnvxv 
	#define dglTexImage2D   glTexImage2D 
	#define dglTexParameteri   glTexParameteri 
	#define dglTexParameterx   glTexParameterx 
	#define dglTexParameteriv   glTexParameteriv 
	#define dglTexParameterxv   glTexParameterxv 
	#define dglTexSubImage2D   glTexSubImage2D 
	#define dglTranslatex   glTranslatex 
	#define dglVertexPointer   glVertexPointer 
	#define dglViewport   glViewport 

	#else

	#define dglActiveTexture  glActiveTexture 
	#define dglAttachShader  glAttachShader 
	#define dglBindAttribLocation  glBindAttribLocation 
	#define dglBindBuffer  glBindBuffer 
	#define dglBindFramebuffer  glBindFramebuffer 
	#define dglBindRenderbuffer  glBindRenderbuffer 
	#define dglBindTexture  glBindTexture 
	#define dglBlendColor  glBlendColor 
	#define dglBlendEquation  glBlendEquation 
	#define dglBlendEquationSeparate  glBlendEquationSeparate 
	#define dglBlendFunc  glBlendFunc 
	#define dglBlendFuncSeparate  glBlendFuncSeparate 
	#define dglBufferData  glBufferData 
	#define dglBufferSubData  glBufferSubData 
	#define dglCheckFramebufferStatus  glCheckFramebufferStatus 
	#define dglClear  glClear 
	#define dglClearColor  glClearColor 
	#define dglClearDepthf  glClearDepthf 
	#define dglClearStencil  glClearStencil 
	#define dglColorMask  glColorMask 
	#define dglCompileShader  glCompileShader 
	#define dglCompressedTexImage2D  glCompressedTexImage2D 
	#define dglCompressedTexSubImage2D  glCompressedTexSubImage2D 
	#define dglCopyTexImage2D  glCopyTexImage2D 
	#define dglCopyTexSubImage2D  glCopyTexSubImage2D 
	#define dglCreateProgram  glCreateProgram 
	#define dglCreateShader  glCreateShader 
	#define dglCullFace  glCullFace 
	#define dglDeleteBuffers  glDeleteBuffers 
	#define dglDeleteFramebuffers  glDeleteFramebuffers 
	#define dglDeleteProgram  glDeleteProgram 
	#define dglDeleteRenderbuffers  glDeleteRenderbuffers 
	#define dglDeleteShader  glDeleteShader 
	#define dglDeleteTextures  glDeleteTextures 
	#define dglDepthFunc  glDepthFunc 
	#define dglDepthMask  glDepthMask 
	#define dglDepthRangef  glDepthRangef 
	#define dglDetachShader  glDetachShader 
	#define dglDisable  glDisable 
	#define dglDisableVertexAttribArray  glDisableVertexAttribArray 
	#define dglDrawArrays  glDrawArrays 
	#define dglDrawElements  glDrawElements 
	#define dglEnable  glEnable 
	#define dglEnableVertexAttribArray  glEnableVertexAttribArray 
	#define dglFinish  glFinish 
	#define dglFlush  glFlush 
	#define dglFramebufferRenderbuffer  glFramebufferRenderbuffer 
	#define dglFramebufferTexture2D  glFramebufferTexture2D 
	#define dglFrontFace  glFrontFace 
	#define dglGenBuffers  glGenBuffers 
	#define dglGenerateMipmap  glGenerateMipmap 
	#define dglGenFramebuffers  glGenFramebuffers 
	#define dglGenRenderbuffers  glGenRenderbuffers 
	#define dglGenTextures  glGenTextures 
	#define dglGetActiveAttrib  glGetActiveAttrib 
	#define dglGetActiveUniform  glGetActiveUniform 
	#define dglGetAttachedShaders  glGetAttachedShaders 
	#define dglGetAttribLocation  glGetAttribLocation 
	#define dglGetBooleanv  glGetBooleanv 
	#define dglGetBufferParameteriv  glGetBufferParameteriv 
	#define dglGetError  glGetError 
	#define dglGetFloatv  glGetFloatv 
	#define dglGetFramebufferAttachmentParameteriv  glGetFramebufferAttachmentParameteriv 
	#define dglGetIntegerv  glGetIntegerv 
	#define dglGetProgramiv  glGetProgramiv 
	#define dglGetProgramInfoLog  glGetProgramInfoLog 
	#define dglGetRenderbufferParameteriv  glGetRenderbufferParameteriv 
	#define dglGetShaderiv  glGetShaderiv 
	#define dglGetShaderInfoLog  glGetShaderInfoLog 
	#define dglGetShaderPrecisionFormat  glGetShaderPrecisionFormat 
	#define dglGetShaderSource  glGetShaderSource 
	#define dglGetString  glGetString 
	#define dglGetTexParameterfv  glGetTexParameterfv 
	#define dglGetTexParameteriv  glGetTexParameteriv 
	#define dglGetUniformfv  glGetUniformfv 
	#define dglGetUniformiv  glGetUniformiv 
	#define dglGetUniformLocation  glGetUniformLocation 
	#define dglGetVertexAttribfv  glGetVertexAttribfv 
	#define dglGetVertexAttribiv  glGetVertexAttribiv 
	#define dglGetVertexAttribPointerv  glGetVertexAttribPointerv 
	#define dglHint  glHint 
	#define dglIsBuffer  glIsBuffer 
	#define dglIsEnabled  glIsEnabled 
	#define dglIsFramebuffer  glIsFramebuffer 
	#define dglIsProgram  glIsProgram 
	#define dglIsRenderbuffer  glIsRenderbuffer 
	#define dglIsShader  glIsShader 
	#define dglIsTexture  glIsTexture 
	#define dglLineWidth  glLineWidth 
	#define dglLinkProgram  glLinkProgram 
	#define dglPixelStorei  glPixelStorei 
	#define dglPolygonOffset  glPolygonOffset 
	#define dglReadPixels  glReadPixels 
	#define dglReleaseShaderCompiler  glReleaseShaderCompiler 
	#define dglRenderbufferStorage  glRenderbufferStorage 
	#define dglSampleCoverage  glSampleCoverage 
	#define dglScissor  glScissor 
	#define dglShaderBinary  glShaderBinary 
	#define dglShaderSource  glShaderSource 
	#define dglStencilFunc  glStencilFunc 
	#define dglStencilFuncSeparate  glStencilFuncSeparate 
	#define dglStencilMask  glStencilMask 
	#define dglStencilMaskSeparate  glStencilMaskSeparate 
	#define dglStencilOp  glStencilOp 
	#define dglStencilOpSeparate  glStencilOpSeparate 
	#define dglTexImage2D  glTexImage2D 
	#define dglTexParameterf  glTexParameterf 
	#define dglTexParameterfv  glTexParameterfv 
	#define dglTexParameteri  glTexParameteri 
	#define dglTexParameteriv  glTexParameteriv 
	#define dglTexSubImage2D  glTexSubImage2D 
	#define dglUniform1f  glUniform1f 
	#define dglUniform1fv  glUniform1fv 
	#define dglUniform1i  glUniform1i 
	#define dglUniform1iv  glUniform1iv 
	#define dglUniform2f  glUniform2f 
	#define dglUniform2fv  glUniform2fv 
	#define dglUniform2i  glUniform2i 
	#define dglUniform2iv  glUniform2iv 
	#define dglUniform3f  glUniform3f 
	#define dglUniform3fv  glUniform3fv 
	#define dglUniform3i  glUniform3i 
	#define dglUniform3iv  glUniform3iv 
	#define dglUniform4f  glUniform4f 
	#define dglUniform4fv  glUniform4fv 
	#define dglUniform4i  glUniform4i 
	#define dglUniform4iv  glUniform4iv 
	#define dglUniformMatrix2fv  glUniformMatrix2fv 
	#define dglUniformMatrix3fv  glUniformMatrix3fv 
	#define dglUniformMatrix4fv  glUniformMatrix4fv 
	#define dglUseProgram  glUseProgram 
	#define dglValidateProgram  glValidateProgram 
	#define dglVertexAttrib1f  glVertexAttrib1f 
	#define dglVertexAttrib1fv  glVertexAttrib1fv 
	#define dglVertexAttrib2f  glVertexAttrib2f 
	#define dglVertexAttrib2fv  glVertexAttrib2fv 
	#define dglVertexAttrib3f  glVertexAttrib3f 
	#define dglVertexAttrib3fv  glVertexAttrib3fv 
	#define dglVertexAttrib4f  glVertexAttrib4f 
	#define dglVertexAttrib4fv  glVertexAttrib4fv 
	#define dglVertexAttribPointer  glVertexAttribPointer 
	#define dglViewport  glViewport 
#endif

#else
	// ---------------------------------------------------------------------------------------
	//
	//  With OpenGLES wrapper (1.x & 2.0)
	//
	// ---------------------------------------------------------------------------------------
	#ifndef OPENGL2
	// Wrapper OpenGL 1.x

	// Available only in Common profile
	void dglAlphaFunc (GLenum func, GLclampf ref);
	void dglClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void dglClearDepthf (GLclampf depth);
	void dglClipPlanef (GLenum plane, const GLfloat *equation);
	void dglColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void dglDepthRangef (GLclampf zNear, GLclampf zFar);
	void dglFogf (GLenum pname, GLfloat param);
	void dglFogfv (GLenum pname, const GLfloat *params);
	void dglFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
	void dglGetClipPlanef (GLenum pname, GLfloat eqn[4]);
	void dglGetFloatv (GLenum pname, GLfloat *params);
	void dglGetLightfv (GLenum light, GLenum pname, GLfloat *params);
	void dglGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
	void dglGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params);
	void dglGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
	void dglLightModelf (GLenum pname, GLfloat param);
	void dglLightModelfv (GLenum pname, const GLfloat *params);
	void dglLightf (GLenum light, GLenum pname, GLfloat param);
	void dglLightfv (GLenum light, GLenum pname, const GLfloat *params);
	void dglLineWidth (GLfloat width);
	void dglLoadMatrixf (const GLfloat *m);
	void dglMaterialf (GLenum face, GLenum pname, GLfloat param);
	void dglMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
	void dglMultMatrixf (const GLfloat *m);
	void dglMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	void dglNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
	void dglOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
	void dglPointParameterf (GLenum pname, GLfloat param);
	void dglPointParameterfv (GLenum pname, const GLfloat *params);
	void dglPointSize (GLfloat size);
	void dglPolygonOffset (GLfloat factor, GLfloat units);
	void dglRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void dglScalef (GLfloat x, GLfloat y, GLfloat z);
	void dglTexEnvf (GLenum target, GLenum pname, GLfloat param);
	void dglTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
	void dglTexParameterf (GLenum target, GLenum pname, GLfloat param);
	void dglTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
	void dglTranslatef (GLfloat x, GLfloat y, GLfloat z);

	// Available in both Common and Common-Lite profiles
	void dglActiveTexture (GLenum texture);
	void dglAlphaFuncx (GLenum func, GLclampx ref);
	void dglBindBuffer (GLenum target, GLuint buffer);
	void dglBindTexture (GLenum target, GLuint texture);
	void dglBlendFunc (GLenum sfactor, GLenum dfactor);
	void dglBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
	void dglBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
	void dglClear (GLbitfield mask);
	void dglClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
	void dglClearDepthx (GLclampx depth);
	void dglClearStencil (GLint s);
	void dglClientActiveTexture (GLenum texture);
	void dglClipPlanex (GLenum plane, const GLfixed *equation);
	void dglColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	void dglColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
	void dglColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void dglColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void dglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
	void dglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
	void dglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	void dglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void dglCullFace (GLenum mode);
	void dglDeleteBuffers (GLsizei n, const GLuint *buffers);
	void dglDeleteTextures (GLsizei n, const GLuint *textures);
	void dglDepthFunc (GLenum func);
	void dglDepthMask (GLboolean flag);
	void dglDepthRangex (GLclampx zNear, GLclampx zFar);
	void dglDisable (GLenum cap);
	void dglDisableClientState (GLenum array);
	void dglDrawArrays (GLenum mode, GLint first, GLsizei count);
	void dglDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
	void dglEnable (GLenum cap);
	void dglEnableClientState (GLenum array);
	void dglFinish (void);
	void dglFlush (void);
	void dglFogx (GLenum pname, GLfixed param);
	void dglFogxv (GLenum pname, const GLfixed *params);
	void dglFrontFace (GLenum mode);
	void dglFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
	void dglGetBooleanv (GLenum pname, GLboolean *params);
	void dglGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
	void dglGetClipPlanex (GLenum pname, GLfixed eqn[4]);
	void dglGenBuffers (GLsizei n, GLuint *buffers);
	void dglGenTextures (GLsizei n, GLuint *textures);
	GLenum dglGetError (void);
	void dglGetFixedv (GLenum pname, GLfixed *params);
	void dglGetIntegerv (GLenum pname, GLint *params);
	void dglGetLightxv (GLenum light, GLenum pname, GLfixed *params);
	void dglGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
	void dglGetPointerv (GLenum pname, void **params);
	const GLubyte * dglGetString (GLenum name);
	void dglGetTexEnviv (GLenum env, GLenum pname, GLint *params);
	void dglGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params);
	void dglGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
	void dglGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params);
	void dglHint (GLenum target, GLenum mode);
	GLboolean dglIsBuffer (GLuint buffer);
	GLboolean dglIsEnabled (GLenum cap);
	GLboolean dglIsTexture (GLuint texture);
	void dglLightModelx (GLenum pname, GLfixed param);
	void dglLightModelxv (GLenum pname, const GLfixed *params);
	void dglLightx (GLenum light, GLenum pname, GLfixed param);
	void dglLightxv (GLenum light, GLenum pname, const GLfixed *params);
	void dglLineWidthx (GLfixed width);
	void dglLoadIdentity (void);
	void dglLoadMatrixx (const GLfixed *m);
	void dglLogicOp (GLenum opcode);
	void dglMaterialx (GLenum face, GLenum pname, GLfixed param);
	void dglMaterialxv (GLenum face, GLenum pname, const GLfixed *params);
	void dglMatrixMode (GLenum mode);
	void dglMultMatrixx (const GLfixed *m);
	void dglMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
	void dglNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
	void dglNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
	void dglOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
	void dglPixelStorei (GLenum pname, GLint param);
	void dglPointParameterx (GLenum pname, GLfixed param);
	void dglPointParameterxv (GLenum pname, const GLfixed *params);
	void dglPointSizex (GLfixed size);
	void dglPolygonOffsetx (GLfixed factor, GLfixed units);
	void dglPopMatrix (void);
	void dglPushMatrix (void);
	void dglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
	void dglRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
	void dglSampleCoverage (GLclampf value, GLboolean invert);
	void dglSampleCoveragex (GLclampx value, GLboolean invert);
	void dglScalex (GLfixed x, GLfixed y, GLfixed z);
	void dglScissor (GLint x, GLint y, GLsizei width, GLsizei height);
	void dglShadeModel (GLenum mode);
	void dglStencilFunc (GLenum func, GLint ref, GLuint mask);
	void dglStencilMask (GLuint mask);
	void dglStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
	void dglTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void dglTexEnvi (GLenum target, GLenum pname, GLint param);
	void dglTexEnvx (GLenum target, GLenum pname, GLfixed param);
	void dglTexEnviv (GLenum target, GLenum pname, const GLint *params);
	void dglTexEnvxv (GLenum target, GLenum pname, const GLfixed *params);
	void dglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	void dglTexParameteri (GLenum target, GLenum pname, GLint param);
	void dglTexParameterx (GLenum target, GLenum pname, GLfixed param);
	void dglTexParameteriv (GLenum target, GLenum pname, const GLint *params);
	void dglTexParameterxv (GLenum target, GLenum pname, const GLfixed *params);
	void dglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	void dglTranslatex (GLfixed x, GLfixed y, GLfixed z);
	void dglVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void dglViewport (GLint x, GLint y, GLsizei width, GLsizei height);
	
	#else
	
	void dglActiveTexture (GLenum texture);
	void dglAttachShader (GLuint program, GLuint shader);
	void dglBindAttribLocation (GLuint program, GLuint index, const GLchar* name);
	void dglBindBuffer (GLenum target, GLuint buffer);
	void dglBindFramebuffer (GLenum target, GLuint framebuffer);
	void dglBindRenderbuffer (GLenum target, GLuint renderbuffer);
	void dglBindTexture (GLenum target, GLuint texture);
	void dglBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void dglBlendEquation ( GLenum mode );
	void dglBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
	void dglBlendFunc (GLenum sfactor, GLenum dfactor);
	void dglBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void dglBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
	void dglBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	GLenum dglCheckFramebufferStatus (GLenum target);
	void dglClear (GLbitfield mask);
	void dglClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void dglClearDepthf (GLclampf depth);
	void dglClearStencil (GLint s);
	void dglColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void dglCompileShader (GLuint shader);
	void dglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	void dglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
	void dglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	void dglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	GLuint dglCreateProgram (void);
	GLuint dglCreateShader (GLenum type);
	void dglCullFace (GLenum mode);
	void dglDeleteBuffers (GLsizei n, const GLuint* buffers);
	void dglDeleteFramebuffers (GLsizei n, const GLuint* framebuffers);
	void dglDeleteProgram (GLuint program);
	void dglDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers);
	void dglDeleteShader (GLuint shader);
	void dglDeleteTextures (GLsizei n, const GLuint* textures);
	void dglDepthFunc (GLenum func);
	void dglDepthMask (GLboolean flag);
	void dglDepthRangef (GLclampf zNear, GLclampf zFar);
	void dglDetachShader (GLuint program, GLuint shader);
	void dglDisable (GLenum cap);
	void dglDisableVertexAttribArray (GLuint index);
	void dglDrawArrays (GLenum mode, GLint first, GLsizei count);
	void dglDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
	void dglEnable (GLenum cap);
	void dglEnableVertexAttribArray (GLuint index);
	void dglFinish (void);
	void dglFlush (void);
	void dglFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	void dglFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	void dglFrontFace (GLenum mode);
	void dglGenBuffers (GLsizei n, GLuint* buffers);
	void dglGenerateMipmap (GLenum target);
	void dglGenFramebuffers (GLsizei n, GLuint* framebuffers);
	void dglGenRenderbuffers (GLsizei n, GLuint* renderbuffers);
	void dglGenTextures (GLsizei n, GLuint* textures);
	void dglGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	void dglGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	void dglGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
	int  glGetAttribLocation (GLuint program, const GLchar* name);
	void dglGetBooleanv (GLenum pname, GLboolean* params);
	void dglGetBufferParameteriv (GLenum target, GLenum pname, GLint* params);
	GLenum dglGetError (void);
	void dglGetFloatv (GLenum pname, GLfloat* params);
	void dglGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params);
	void dglGetIntegerv (GLenum pname, GLint* params);
	void dglGetProgramiv (GLuint program, GLenum pname, GLint* params);
	void dglGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
	void dglGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params);
	void dglGetShaderiv (GLuint shader, GLenum pname, GLint* params);
	void dglGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
	void dglGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
	void dglGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
	const GLubyte* glGetString (GLenum name);
	void dglGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params);
	void dglGetTexParameteriv (GLenum target, GLenum pname, GLint* params);
	void dglGetUniformfv (GLuint program, GLint location, GLfloat* params);
	void dglGetUniformiv (GLuint program, GLint location, GLint* params);
	int  glGetUniformLocation (GLuint program, const GLchar* name);
	void dglGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params);
	void dglGetVertexAttribiv (GLuint index, GLenum pname, GLint* params);
	void dglGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer);
	void dglHint (GLenum target, GLenum mode);
	GLboolean dglIsBuffer (GLuint buffer);
	GLboolean dglIsEnabled (GLenum cap);
	GLboolean dglIsFramebuffer (GLuint framebuffer);
	GLboolean dglIsProgram (GLuint program);
	GLboolean dglIsRenderbuffer (GLuint renderbuffer);
	GLboolean dglIsShader (GLuint shader);
	GLboolean dglIsTexture (GLuint texture);
	void dglLineWidth (GLfloat width);
	void dglLinkProgram (GLuint program);
	void dglPixelStorei (GLenum pname, GLint param);
	void dglPolygonOffset (GLfloat factor, GLfloat units);
	void dglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
	void dglReleaseShaderCompiler (void);
	void dglRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	void dglSampleCoverage (GLclampf value, GLboolean invert);
	void dglScissor (GLint x, GLint y, GLsizei width, GLsizei height);
	void dglShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
	void dglShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	void dglStencilFunc (GLenum func, GLint ref, GLuint mask);
	void dglStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
	void dglStencilMask (GLuint mask);
	void dglStencilMaskSeparate (GLenum face, GLuint mask);
	void dglStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
	void dglStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
	void dglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
	void dglTexParameterf (GLenum target, GLenum pname, GLfloat param);
	void dglTexParameterfv (GLenum target, GLenum pname, const GLfloat* params);
	void dglTexParameteri (GLenum target, GLenum pname, GLint param);
	void dglTexParameteriv (GLenum target, GLenum pname, const GLint* params);
	void dglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
	void dglUniform1f (GLint location, GLfloat x);
	void dglUniform1fv (GLint location, GLsizei count, const GLfloat* v);
	void dglUniform1i (GLint location, GLint x);
	void dglUniform1iv (GLint location, GLsizei count, const GLint* v);
	void dglUniform2f (GLint location, GLfloat x, GLfloat y);
	void dglUniform2fv (GLint location, GLsizei count, const GLfloat* v);
	void dglUniform2i (GLint location, GLint x, GLint y);
	void dglUniform2iv (GLint location, GLsizei count, const GLint* v);
	void dglUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z);
	void dglUniform3fv (GLint location, GLsizei count, const GLfloat* v);
	void dglUniform3i (GLint location, GLint x, GLint y, GLint z);
	void dglUniform3iv (GLint location, GLsizei count, const GLint* v);
	void dglUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void dglUniform4fv (GLint location, GLsizei count, const GLfloat* v);
	void dglUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w);
	void dglUniform4iv (GLint location, GLsizei count, const GLint* v);
	void dglUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void dglUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void dglUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	void dglUseProgram (GLuint program);
	void dglValidateProgram (GLuint program);
	void dglVertexAttrib1f (GLuint indx, GLfloat x);
	void dglVertexAttrib1fv (GLuint indx, const GLfloat* values);
	void dglVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y);
	void dglVertexAttrib2fv (GLuint indx, const GLfloat* values);
	void dglVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z);
	void dglVertexAttrib3fv (GLuint indx, const GLfloat* values);
	void dglVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void dglVertexAttrib4fv (GLuint indx, const GLfloat* values);
	void dglVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
	void dglViewport (GLint x, GLint y, GLsizei width, GLsizei height);
	
	#endif

#endif


#endif
