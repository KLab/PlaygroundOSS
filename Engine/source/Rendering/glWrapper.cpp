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
#include "glWrapper.h"
#include "assert_klb.h"
#include <stdio.h>

// static bool gl_log = false;

static GLenum lastError = 0;
static void processError() {
	GLenum err = glGetError();
	if (err) {
		if (lastError == 0) {
			klb_assertAlways("OpenGLERRROR");
			lastError = err;
		}
	}
}

static GLenum getLastError() {
	GLenum err = lastError;
	lastError = 0;
	return err;
}

#ifdef USE_DEBUG_WRAPPER

//
// Include only done in glWrapper.h when WRAPPER is NOT used.
//
#if defined(__APPLE__)
    #ifdef OPENGL2
    #import <OpenGLES/ES2/gl.h>
    #import <OpenGLES/ES2/glext.h>
    #else
    #import <OpenGLES/ES1/gl.h>
    #import <OpenGLES/ES1/glext.h>
    #endif
#else
    #ifdef OPENGL2
    #include "GLES2/gl2.h"
	#include "GLES2/gl2ext.h"
    // The header file which is not in the Android environment.
	// #include "GLES2/gl2extimg.h"
    #else
    #include "GLES/gl.h"
    #endif
#endif

	
#ifndef OPENGL2
// Available only in Common profile
void dglAlphaFunc  (GLenum func, GLclampf ref) 													{ glAlphaFunc (func, ref); processError(); };
void dglClearColor  (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) 				{ glClearColor (red, green, blue, alpha); processError(); };
void dglClearDepthf  (GLclampf depth) 															{ glClearDepthf (depth); processError(); };
void dglClipPlanef  (GLenum plane, const GLfloat *equation) 									{ glClipPlanef (plane, equation); processError(); };
void dglColor4f  (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) 						{ glColor4f (red, green, blue, alpha); processError(); };
void dglDepthRangef  (GLclampf zNear, GLclampf zFar) 											{ glDepthRangef (zNear, zFar); processError(); };
void dglFogf  (GLenum pname, GLfloat param) 													{ glFogf (pname, param); processError(); };
void dglFogfv  (GLenum pname, const GLfloat *params) 											{ glFogfv (pname, params); processError(); };
void dglFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
																								{ glFrustumf(left,right,bottom,top,zNear,zFar); processError(); } 
void dglGetClipPlanef (GLenum pname, GLfloat eqn[4])											{ glGetClipPlanef(pname,eqn); processError(); } 
void dglGetFloatv  (GLenum pname, GLfloat *params) 												{ glGetFloatv (pname, params); processError(); };
void dglGetLightfv  (GLenum light, GLenum pname, GLfloat *params) 								{ glGetLightfv (light, pname, params); processError(); };
void dglGetMaterialfv  (GLenum face, GLenum pname, GLfloat *params) 							{ glGetMaterialfv (face, pname, params); processError(); };
void dglGetTexEnvfv  (GLenum env, GLenum pname, GLfloat *params) 								{ glGetTexEnvfv (env, pname, params); processError(); };
void dglGetTexParameterfv  (GLenum target, GLenum pname, GLfloat *params) 						{ glGetTexParameterfv (target, pname, params); processError(); };
void dglLightModelf  (GLenum pname, GLfloat param) 												{ glLightModelf (pname, param); processError(); };
void dglLightModelfv  (GLenum pname, const GLfloat *params) 									{ glLightModelfv (pname, params); processError(); };
void dglLightf  (GLenum light, GLenum pname, GLfloat param) 									{ glLightf (light, pname, param); processError(); };
void dglLightfv  (GLenum light, GLenum pname, const GLfloat *params) 							{ glLightfv (light, pname, params); processError(); };
void dglLineWidth  (GLfloat width) 																{ glLineWidth (width); processError(); };
void dglLoadMatrixf  (const GLfloat *m) 														{ glLoadMatrixf (m); processError(); };
void dglMaterialf  (GLenum face, GLenum pname, GLfloat param) 									{ glMaterialf (face, pname, param); processError(); };
void dglMaterialfv  (GLenum face, GLenum pname, const GLfloat *params) 							{ glMaterialfv (face, pname, params); processError(); };
void dglMultMatrixf  (const GLfloat *m) 														{ glMultMatrixf (m); processError(); };
void dglMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)				{ glMultiTexCoord4f(target,s,t,r,q); processError(); }
void dglNormal3f  (GLfloat nx, GLfloat ny, GLfloat nz) 											{ glNormal3f (nx, ny, nz); processError(); };
void dglOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
																								{ glOrthof(left,right,bottom,top,zNear,zFar); processError(); }
void dglPointParameterf  (GLenum pname, GLfloat param) 											{ glPointParameterf (pname, param); processError(); };
void dglPointParameterfv  (GLenum pname, const GLfloat *params) 								{ glPointParameterfv (pname, params); processError(); };
void dglPointSize  (GLfloat size) 																{ glPointSize (size); processError(); };
void dglPolygonOffset  (GLfloat factor, GLfloat units) 											{ glPolygonOffset (factor, units); processError(); };
void dglRotatef  (GLfloat angle, GLfloat x, GLfloat y, GLfloat z) 								{ glRotatef (angle, x, y, z); processError(); };
void dglScalef  (GLfloat x, GLfloat y, GLfloat z) 												{ glScalef (x, y, z); processError(); };
void dglTexEnvf  (GLenum target, GLenum pname, GLfloat param) 									{ glTexEnvf (target, pname, param); processError(); };
void dglTexEnvfv  (GLenum target, GLenum pname, const GLfloat *params) 							{ glTexEnvfv (target, pname, params); processError(); };
void dglTexParameterf  (GLenum target, GLenum pname, GLfloat param) 							{ glTexParameterf (target, pname, param); processError(); };
void dglTexParameterfv  (GLenum target, GLenum pname, const GLfloat *params) 					{ glTexParameterfv (target, pname, params); processError(); };
void dglTranslatef  (GLfloat x, GLfloat y, GLfloat z) 											{ glTranslatef (x, y, z); processError(); };

// Available in both Common and Common-Lite profiles
void dglActiveTexture  (GLenum texture) 														{ 
	if (gl_log) { printf("glActivateTexture(GL_TEXTURE%i);\n",texture - GL_TEXTURE0); }
	glActiveTexture (texture); processError(); 
};
void dglAlphaFuncx  (GLenum func, GLclampx ref) 												{ glAlphaFuncx (func, ref); processError(); };
void dglBindBuffer  (GLenum target, GLuint buffer) 												{ glBindBuffer (target, buffer); processError(); };
void dglBindTexture  (GLenum target, GLuint texture) 											{
	if (gl_log) { printf("glBindTexture(GL_TEXTURE_2D, %i);\n",texture); }
	glBindTexture (target, texture); processError();
};
void dglBlendFunc  (GLenum sfactor, GLenum dfactor) 											{ glBlendFunc (sfactor, dfactor); processError(); };
void dglBufferData  (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) 			{ glBufferData (target, size, data, usage); processError(); };
void dglBufferSubData  (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) 	{ glBufferSubData (target, offset, size, data); processError(); };
void dglClear  (GLbitfield mask) 																{ glClear (mask); processError(); };
void dglClearColorx  (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) 				{ glClearColorx (red, green, blue, alpha); processError(); };
void dglClearDepthx  (GLclampx depth) 															{ glClearDepthx (depth); processError(); };
void dglClearStencil  (GLint s) 																{ glClearStencil (s); processError(); };
void dglClientActiveTexture  (GLenum texture) 													{
	if (gl_log) { printf("glClientActivateTexture(GL_TEXTURE%i);\n",texture - GL_TEXTURE0); }
	glClientActiveTexture (texture); processError(); 
};
void dglClipPlanex  (GLenum plane, const GLfixed *equation) 									{ glClipPlanex (plane, equation); processError(); };
void dglColor4ub  (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) 					{ glColor4ub (red, green, blue, alpha); processError(); };
void dglColor4x  (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) 						{ glColor4x (red, green, blue, alpha); processError(); };
void dglColorMask  (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) 			{ glColorMask (red, green, blue, alpha); processError(); };
void dglColorPointer  (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) 			{ glColorPointer (size, type, stride, pointer); processError(); };

void dglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) 
	{ glCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data); processError(); }

void dglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
	{ glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data); processError(); }

void dglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
	{ glCopyTexImage2D (target, level, internalformat, x, y, width, height, border); processError(); }

void dglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{ glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height); processError(); }

const char* getStringCap(GLenum cap) {
	switch (cap) {
		case GL_ALPHA_TEST					: return "GL_ALPHA_TEST";
		case GL_BLEND						: return "GL_BLEND";
		case GL_COLOR_LOGIC_OP				: return "GL_COLOR_LOGIC_OP";
		case GL_CLIP_PLANE0					: return "GL_CLIP_PLANE0";
		case GL_CLIP_PLANE1					: return "GL_CLIP_PLANE1";
		case GL_CLIP_PLANE2					: return "GL_CLIP_PLANE2";
		case GL_CLIP_PLANE3					: return "GL_CLIP_PLANE3";
		case GL_CLIP_PLANE4					: return "GL_CLIP_PLANE4";
		case GL_CLIP_PLANE5					: return "GL_CLIP_PLANE5";
		case GL_COLOR_MATERIAL				: return "GL_COLOR_MATERIAL";
		case GL_CULL_FACE					: return "GL_CULL_FACE";
		case GL_DEPTH_TEST					: return "GL_DEPTH_TEST";
		case GL_DITHER						: return "GL_DITHER";
		case GL_FOG							: return "GL_FOG";
		case GL_LIGHT0						: return "GL_LIGHT0";
		case GL_LIGHTING					: return "GL_LIGHTING";
		case GL_LINE_SMOOTH					: return "GL_LINE_SMOOTH";
		case GL_MULTISAMPLE					: return "GL_MULTISAMPLE";
		case GL_NORMALIZE					: return "GL_NORMALIZE";
		case GL_POINT_SMOOTH				: return "GL_POINT_SMOOTH";
		case GL_POINT_SPRITE_OES			: return "GL_POINT_SPRITE_OES";
		case GL_POLYGON_OFFSET_FILL			: return "GL_POLYGON_OFFSET_FILL";
		case GL_RESCALE_NORMAL				: return "GL_RESCALE_NORMAL";
		case GL_SAMPLE_ALPHA_TO_COVERAGE	: return "GL_SAMPLE_ALPHA_TO_COVERAGE";
		case GL_SAMPLE_ALPHA_TO_ONE			: return "GL_SAMPLE_ALPHA_TO_ONE";
		case GL_SAMPLE_COVERAGE				: return "GL_SAMPLE_COVERAGE";
		case GL_SCISSOR_TEST				: return "GL_SCISSOR_TEST";
		case GL_STENCIL_TEST				: return "GL_STENCIL_TEST";
		case GL_TEXTURE_2D					: 
			return "GL_TEXTURE_2D";
		default: 
			return "Unknown";
	}
}

const char* getStringClientState(GLenum array_) {
	switch (array_) {
	case GL_COLOR_ARRAY				: 
		return "GL_COLOR_ARRAY";		
	case GL_NORMAL_ARRAY			: 
		return "GL_NORMAL_ARRAY";
	case GL_POINT_SIZE_ARRAY_OES	: 
		return "GL_POINT_SIZE_ARRAY_OES";
	case GL_TEXTURE_COORD_ARRAY		: 
		return "GL_TEXTURE_COORD_ARRAY";
	case GL_VERTEX_ARRAY			: 
		return "GL_VERTEX_ARRAY";
	default:
		return "Unknown";
	}
}

void dglCullFace  (GLenum mode) 																{ glCullFace (mode); processError(); };
void dglDeleteBuffers  (GLsizei n, const GLuint *buffers) 										{ glDeleteBuffers (n, buffers); processError(); };
void dglDeleteTextures  (GLsizei n, const GLuint *textures) 									{ glDeleteTextures (n, textures); processError(); };
void dglDepthFunc  (GLenum func) 																{ glDepthFunc (func); processError(); };
void dglDepthMask  (GLboolean flag) 															{ glDepthMask (flag); processError(); };
void dglDepthRangex  (GLclampx zNear, GLclampx zFar) 											{ glDepthRangex (zNear, zFar); processError(); };
void dglDisable  (GLenum cap) 																	{ 
	if (gl_log) { printf("glDisable(%s);\n",getStringCap(cap)); }
	glDisable (cap); processError(); 
};
void dglDisableClientState  (GLenum array_)														{
	if (gl_log) { printf("glDisableClientState(%s);\n",getStringClientState(array_)); }	
	glDisableClientState (array_); processError(); 
};
void dglDrawArrays  (GLenum mode, GLint first, GLsizei count) 									{ glDrawArrays (mode, first, count); processError(); };
void dglDrawElements  (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) 			{ glDrawElements (mode, count, type, indices); processError(); };
void dglEnable  (GLenum cap) 																	{ 
	if (gl_log) { printf("glEnable(%s);\n",getStringCap(cap)); }
	glEnable (cap); processError(); 
};
void dglEnableClientState  (GLenum array_) 														{ 
	if (gl_log) { printf("glEnableClientState(%s);\n",getStringClientState(array_)); }	
	glEnableClientState (array_); processError(); 
};
void dglFinish (void)																			{ glFinish(); processError(); };
void dglFlush (void)																			{ glFlush(); processError(); };
void dglFogx  (GLenum pname, GLfixed param) 													{ glFogx (pname, param); processError(); };
void dglFogxv  (GLenum pname, const GLfixed *params) 											{ glFogxv (pname, params); processError(); };
void dglFrontFace  (GLenum mode) 																{ glFrontFace (mode); processError(); };
void dglFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
	{ glFrustumx (left, right, bottom, top, zNear, zFar); processError(); }
void dglGetBooleanv  (GLenum pname, GLboolean *params) 											{ glGetBooleanv (pname, params); processError(); };
void dglGetBufferParameteriv  (GLenum target, GLenum pname, GLint *params) 						{ glGetBufferParameteriv (target, pname, params); processError(); };
void dglGetClipPlanex (GLenum pname, GLfixed eqn[4])
	{ glGetClipPlanex (pname, eqn); processError(); }
void dglGenBuffers  (GLsizei n, GLuint *buffers) 												{ glGenBuffers (n, buffers); processError(); };
void dglGenTextures  (GLsizei n, GLuint *textures) 												{ glGenTextures (n, textures); processError(); };
GLenum dglGetError (void)	{ processError(); return getLastError(); }
void dglGetFixedv  (GLenum pname, GLfixed *params) 												{ glGetFixedv (pname, params); processError(); };
void dglGetIntegerv  (GLenum pname, GLint *params) 												{ glGetIntegerv (pname, params); processError(); };
void dglGetLightxv  (GLenum light, GLenum pname, GLfixed *params) 								{ glGetLightxv (light, pname, params); processError(); };
void dglGetMaterialxv  (GLenum face, GLenum pname, GLfixed *params) 							{ glGetMaterialxv (face, pname, params); processError(); };
void dglGetPointerv  (GLenum pname, void **params) 												{ glGetPointerv (pname, params); processError(); };
const GLubyte * dglGetString  (GLenum name) 													{ const GLubyte* res = glGetString (name); processError(); return res; };
void dglGetTexEnviv  (GLenum env, GLenum pname, GLint *params) 									{ glGetTexEnviv (env, pname, params); processError(); };
void dglGetTexEnvxv  (GLenum env, GLenum pname, GLfixed *params) 								{ glGetTexEnvxv (env, pname, params); processError(); };
void dglGetTexParameteriv  (GLenum target, GLenum pname, GLint *params) 						{ glGetTexParameteriv (target, pname, params); processError(); };
void dglGetTexParameterxv  (GLenum target, GLenum pname, GLfixed *params) 						{ glGetTexParameterxv (target, pname, params); processError(); };
void dglHint  (GLenum target, GLenum mode) 														{ glHint (target, mode); processError(); };
GLboolean dglIsBuffer  (GLuint buffer) 															{ GLboolean res = glIsBuffer (buffer); processError(); return res; };
GLboolean dglIsEnabled  (GLenum cap) 															{ GLboolean res = glIsEnabled (cap); processError(); return res; };
GLboolean dglIsTexture  (GLuint texture) 														{ GLboolean res = glIsTexture (texture); processError(); return res; };
void dglLightModelx  (GLenum pname, GLfixed param) 												{ glLightModelx (pname, param); processError(); };
void dglLightModelxv  (GLenum pname, const GLfixed *params) 									{ glLightModelxv (pname, params); processError(); };
void dglLightx  (GLenum light, GLenum pname, GLfixed param) 									{ glLightx (light, pname, param); processError(); };
void dglLightxv  (GLenum light, GLenum pname, const GLfixed *params) 							{ glLightxv (light, pname, params); processError(); };
void dglLineWidthx  (GLfixed width) 															{ glLineWidthx (width); processError(); };
void dglLoadIdentity (void)																		{ glLoadIdentity(); processError(); };
void dglLoadMatrixx  (const GLfixed *m) 														{ glLoadMatrixx (m); processError(); };
void dglLogicOp  (GLenum opcode) 																{ glLogicOp (opcode); processError(); };
void dglMaterialx  (GLenum face, GLenum pname, GLfixed param) 									{ glMaterialx (face, pname, param); processError(); };
void dglMaterialxv  (GLenum face, GLenum pname, const GLfixed *params) 							{ glMaterialxv (face, pname, params); processError(); };
void dglMatrixMode  (GLenum mode) 																{ glMatrixMode (mode); processError(); };
void dglMultMatrixx  (const GLfixed *m) 														{ glMultMatrixx (m); processError(); };
void dglMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)				{ glMultiTexCoord4x (target, s, t, r, q); processError(); };
void dglNormal3x  (GLfixed nx, GLfixed ny, GLfixed nz) 											{ glNormal3x (nx, ny, nz); processError(); };
void dglNormalPointer  (GLenum type, GLsizei stride, const GLvoid *pointer) 					{ glNormalPointer (type, stride, pointer); processError(); };
void dglOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
																								{ glOrthox (left, right, bottom, top, zNear, zFar); processError(); };
void dglPixelStorei  (GLenum pname, GLint param) 												{ glPixelStorei (pname, param); processError(); };
void dglPointParameterx  (GLenum pname, GLfixed param) 											{ glPointParameterx (pname, param); processError(); };
void dglPointParameterxv  (GLenum pname, const GLfixed *params) 								{ glPointParameterxv (pname, params); processError(); };
void dglPointSizex  (GLfixed size) 																{ glPointSizex (size); processError(); };
void dglPolygonOffsetx  (GLfixed factor, GLfixed units) 										{ glPolygonOffsetx (factor, units); processError(); };
void dglPopMatrix (void)																		{ glPopMatrix(); processError(); }
void dglPushMatrix (void)																		{ glPushMatrix(); processError(); }
void dglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
	{ glReadPixels (x, y, width, height, format, type, pixels); processError(); }
void dglRotatex  (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) 								{ glRotatex (angle, x, y, z); processError(); };
void dglSampleCoverage  (GLclampf value, GLboolean invert) 										{ glSampleCoverage (value, invert); processError(); };
void dglSampleCoveragex  (GLclampx value, GLboolean invert) 									{ glSampleCoveragex (value, invert); processError(); };
void dglScalex  (GLfixed x, GLfixed y, GLfixed z) 												{ glScalex (x, y, z); processError(); };
void dglScissor  (GLint x, GLint y, GLsizei width, GLsizei height) 								{ glScissor (x, y, width, height); processError(); };
void dglShadeModel  (GLenum mode) 																{ glShadeModel (mode); processError(); };
void dglStencilFunc  (GLenum func, GLint ref, GLuint mask) 										{ glStencilFunc (func, ref, mask); processError(); };
void dglStencilMask  (GLuint mask) 																{ glStencilMask (mask); processError(); };
void dglStencilOp  (GLenum fail, GLenum zfail, GLenum zpass) 									{ glStencilOp (fail, zfail, zpass); processError(); };
void dglTexCoordPointer  (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) 		{
	if (gl_log) { printf("glTexCoordPointer(...);\n"); }	
	glTexCoordPointer (size, type, stride, pointer); processError(); 
};
void dglTexEnvi  (GLenum target, GLenum pname, GLint param) 									{ glTexEnvi (target, pname, param); processError(); };
void dglTexEnvx  (GLenum target, GLenum pname, GLfixed param) 									{ glTexEnvx (target, pname, param); processError(); };
void dglTexEnviv  (GLenum target, GLenum pname, const GLint *params) 							{ glTexEnviv (target, pname, params); processError(); };
void dglTexEnvxv  (GLenum target, GLenum pname, const GLfixed *params) 							{ glTexEnvxv (target, pname, params); processError(); };
void dglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
	{ glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels); processError(); }
void dglTexParameteri  (GLenum target, GLenum pname, GLint param) 								{ glTexParameteri (target, pname, param); processError(); };
void dglTexParameterx  (GLenum target, GLenum pname, GLfixed param) 							{ glTexParameterx (target, pname, param); processError(); };
void dglTexParameteriv  (GLenum target, GLenum pname, const GLint *params) 						{ glTexParameteriv (target, pname, params); processError(); };
void dglTexParameterxv  (GLenum target, GLenum pname, const GLfixed *params) 					{ glTexParameterxv (target, pname, params); processError(); };
void dglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
	{ glTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels); processError(); }
void dglTranslatex  (GLfixed x, GLfixed y, GLfixed z) 											{ glTranslatex (x, y, z); processError(); };
void dglVertexPointer  (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) 		{ glVertexPointer (size, type, stride, pointer); processError(); };
void dglViewport  (GLint x, GLint y, GLsizei width, GLsizei height) 							{ glViewport (x, y, width, height); processError(); };
#else
void dglActiveTexture  (GLenum texture) 														{ glActiveTexture (texture); processError(); };
void dglAttachShader  (GLuint program, GLuint shader) 											{ glAttachShader (program, shader); processError(); };
void dglBindAttribLocation  (GLuint program, GLuint index, const GLchar* name) 					{ glBindAttribLocation (program, index, name); processError(); };
void dglBindBuffer  (GLenum target, GLuint buffer) 												{ glBindBuffer (target, buffer); processError(); };
void dglBindFramebuffer  (GLenum target, GLuint framebuffer) 									{ glBindFramebuffer (target, framebuffer); processError(); };
void dglBindRenderbuffer  (GLenum target, GLuint renderbuffer) 									{ glBindRenderbuffer (target, renderbuffer); processError(); };
void dglBindTexture  (GLenum target, GLuint texture) 											{ glBindTexture (target, texture); processError(); };
void dglBlendColor  (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) 				{ glBlendColor (red, green, blue, alpha); processError(); };
void dglBlendEquation  ( GLenum mode ) 															{ glBlendEquation (); processError(); };
void dglBlendEquationSeparate  (GLenum modeRGB, GLenum modeAlpha) 								{ glBlendEquationSeparate (modeRGB, modeAlpha); processError(); };
void dglBlendFunc  (GLenum sfactor, GLenum dfactor) 											{ glBlendFunc (sfactor, dfactor); processError(); };
void dglBlendFuncSeparate  (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) 	{ glBlendFuncSeparate (srcRGB, dstRGB, srcAlpha, dstAlpha); processError(); };
void dglBufferData  (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) 			{ glBufferData (target, size, data, usage); processError(); };
void dglBufferSubData  (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) 	{ glBufferSubData (target, offset, size, data); processError(); };
GLenum dglCheckFramebufferStatus  (GLenum target) 												{ GLenum res = glCheckFramebufferStatus (target); processError(); return res; };
void dglClear  (GLbitfield mask) 																{ glClear (mask); processError(); };
void dglClearColor  (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) 				{ glClearColor (red, green, blue, alpha); processError(); };
void dglClearDepthf  (GLclampf depth) 															{ glClearDepthf (depth); processError(); };
void dglClearStencil  (GLint s) 																{ glClearStencil (s); processError(); };
void dglColorMask  (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) 			{ glColorMask (red, green, blue, alpha); processError(); };
void dglCompileShader  (GLuint shader) 															{ glCompileShader (shader); processError(); };
void dglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	{ glCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data); processError(); }
void dglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
	{ glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data); processError(); }
void dglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	{ glCopyTexImage2D (target,level,internalformat,x,y,width,height,border);  processError(); }
void dglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	{ glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height); processError(); }
GLuint dglCreateProgram (void)																	{ GLuint res = glCreateProgram(); processError(); return res; } 
GLuint dglCreateShader  (GLenum type) 															{ GLuint res = glCreateShader (type); processError(); return res; };
void dglCullFace  (GLenum mode) 																{ glCullFace (mode); processError(); };
void dglDeleteBuffers  (GLsizei n, const GLuint* buffers) 										{ glDeleteBuffers (n, buffers); processError(); };
void dglDeleteFramebuffers  (GLsizei n, const GLuint* framebuffers) 							{ glDeleteFramebuffers (n, framebuffers); processError(); };
void dglDeleteProgram  (GLuint program) 														{ glDeleteProgram (program); processError(); };
void dglDeleteRenderbuffers  (GLsizei n, const GLuint* renderbuffers) 							{ glDeleteRenderbuffers (n, renderbuffers); processError(); };
void dglDeleteShader  (GLuint shader) 															{ glDeleteShader (shader); processError(); };
void dglDeleteTextures  (GLsizei n, const GLuint* textures) 									{ glDeleteTextures (n, textures); processError(); };
void dglDepthFunc  (GLenum func) 																{ glDepthFunc (func); processError(); };
void dglDepthMask  (GLboolean flag) 															{ glDepthMask (flag); processError(); };
void dglDepthRangef  (GLclampf zNear, GLclampf zFar) 											{ glDepthRangef (zNear, zFar); processError(); };
void dglDetachShader  (GLuint program, GLuint shader) 											{ glDetachShader (program, shader); processError(); };
void dglDisable  (GLenum cap) 																	{ glDisable (cap); processError(); };
void dglDisableVertexAttribArray  (GLuint index) 												{ glDisableVertexAttribArray (index); processError(); };
void dglDrawArrays  (GLenum mode, GLint first, GLsizei count) 									{ glDrawArrays (mode, first, count); processError(); };
void dglDrawElements  (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) 			{ glDrawElements (mode, count, type, indices); processError(); };
void dglEnable  (GLenum cap) 																	{ glEnable (cap); processError(); };
void dglEnableVertexAttribArray  (GLuint index) 												{ glEnableVertexAttribArray (index); processError(); };
void dglFinish (void)																			{ glFinish(); processError(); }
void dglFlush (void)																			{ glFlush(); processError(); }
void dglFramebufferRenderbuffer  (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) 
																								{ glFramebufferRenderbuffer (target, attachment, renderbuffertarget, renderbuffer); processError(); };
void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void dglFrontFace  (GLenum mode) 																{ glFrontFace (mode); processError(); };
void dglGenBuffers  (GLsizei n, GLuint* buffers) 												{ glGenBuffers (n, buffers); processError(); };
void dglGenerateMipmap  (GLenum target) 														{ glGenerateMipmap (target); processError(); };
void dglGenFramebuffers  (GLsizei n, GLuint* framebuffers) 										{ glGenFramebuffers (n, framebuffers); processError(); };
void dglGenRenderbuffers  (GLsizei n, GLuint* renderbuffers) 									{ glGenRenderbuffers (n, renderbuffers); processError(); };
void dglGenTextures  (GLsizei n, GLuint* textures) 												{ glGenTextures (n, textures); processError(); };
void dglGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	{ glGetActiveAttrib (program, index, bufsize, length, size, type, name); processError(); }

void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	{ glGetActiveUniform (program, index, bufsize, length, size, type, name); processError(); }

void dglGetAttachedShaders  (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) { glGetAttachedShaders (program, maxcount, count, shaders); processError(); };
int  dglGetAttribLocation  (GLuint program, const GLchar* name) 								{ int res = glGetAttribLocation (program, name); processError(); return res; };
void dglGetBooleanv  (GLenum pname, GLboolean* params) 											{ glGetBooleanv (pname, params); processError(); };
void dglGetBufferParameteriv  (GLenum target, GLenum pname, GLint* params) 						{ glGetBufferParameteriv (target, pname, params); processError(); };
GLenum dglGetError (void)	{ processError(); return getLastError(); }
void dglGetFloatv  (GLenum pname, GLfloat* params) 												{ glGetFloatv (pname, params); processError(); };
void dglGetFramebufferAttachmentParameteriv  (GLenum target, GLenum attachment, GLenum pname, GLint* params) 
																								{ glGetFramebufferAttachmentParameteriv (target, attachment, pname, params); processError(); };
void dglGetIntegerv  (GLenum pname, GLint* params) 												{ glGetIntegerv (pname, params); processError(); };
void dglGetProgramiv  (GLuint program, GLenum pname, GLint* params) 							{ glGetProgramiv (program, pname, params); processError(); };
void dglGetProgramInfoLog  (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog) { glGetProgramInfoLog (program, bufsize, length, infolog); processError(); };
void dglGetRenderbufferParameteriv  (GLenum target, GLenum pname, GLint* params) 				{ glGetRenderbufferParameteriv (target, pname, params); processError(); };
void dglGetShaderiv  (GLuint shader, GLenum pname, GLint* params) 								{ glGetShaderiv (shader, pname, params); processError(); };
void dglGetShaderInfoLog  (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog) 	{ glGetShaderInfoLog (shader, bufsize, length, infolog); processError(); };
void dglGetShaderPrecisionFormat  (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) 
																								{ glGetShaderPrecisionFormat (shadertype, precisiontype, range, precision); processError(); };
void dglGetShaderSource  (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)		{ glGetShaderSource (shader, bufsize, length, source); processError(); };
const GLubyte* dglGetString  (GLenum name) 														{ const GLubyte* res = glGetString (name); processError(); return res; };
void dglGetTexParameterfv  (GLenum target, GLenum pname, GLfloat* params) 						{ glGetTexParameterfv (target, pname, params); processError(); };
void dglGetTexParameteriv  (GLenum target, GLenum pname, GLint* params) 						{ glGetTexParameteriv (target, pname, params); processError(); };
void dglGetUniformfv  (GLuint program, GLint location, GLfloat* params) 						{ glGetUniformfv (program, location, params); processError(); };
void dglGetUniformiv  (GLuint program, GLint location, GLint* params) 							{ glGetUniformiv (program, location, params); processError(); };
int  dglGetUniformLocation  (GLuint program, const GLchar* name) 								{ int res = glGetUniformLocation (program, name); processError(); return res; };
void dglGetVertexAttribfv  (GLuint index, GLenum pname, GLfloat* params) 						{ glGetVertexAttribfv (index, pname, params); processError(); };
void dglGetVertexAttribiv  (GLuint index, GLenum pname, GLint* params) 							{ glGetVertexAttribiv (index, pname, params); processError(); };
void dglGetVertexAttribPointerv  (GLuint index, GLenum pname, GLvoid** pointer) 				{ glGetVertexAttribPointerv (index, pname, pointer); processError(); };
void dglHint  (GLenum target, GLenum mode) 														{ glHint (target, mode); processError(); };
GLboolean dglIsBuffer  (GLuint buffer) 															{ GLboolean res = glIsBuffer (buffer); processError(); return res; };
GLboolean dglIsEnabled  (GLenum cap) 															{ GLboolean res = glIsEnabled (cap); processError(); return res; };
GLboolean dglIsFramebuffer  (GLuint framebuffer) 												{ GLboolean res = glIsFramebuffer (framebuffer); processError(); return res; };
GLboolean dglIsProgram  (GLuint program) 														{ GLboolean res = glIsProgram (program); processError(); return res; };
GLboolean dglIsRenderbuffer  (GLuint renderbuffer) 												{ GLboolean res = glIsRenderbuffer (renderbuffer); processError(); return res; };
GLboolean dglIsShader  (GLuint shader) 															{ GLboolean res = glIsShader (shader); processError(); return res; };
GLboolean dglIsTexture  (GLuint texture) 														{ GLboolean res = glIsTexture (texture); processError(); return res; };
void dglLineWidth  (GLfloat width) 																{ glLineWidth (width); processError(); };
void dglLinkProgram  (GLuint program) 															{ glLinkProgram (program); processError(); };
void dglPixelStorei  (GLenum pname, GLint param) 												{ glPixelStorei (pname, param); processError(); };
void dglPolygonOffset  (GLfloat factor, GLfloat units) 											{ glPolygonOffset (factor, units); processError(); };
void dglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
	{ glReadPixels (x, y, width, height, format, type, pixels); processError(); }
void dglReleaseShaderCompiler (void)
	{ glReleaseShaderCompiler(); processError(); }
void dglRenderbufferStorage  (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) 
																								{ glRenderbufferStorage (target, internalformat, width, height); processError(); };
void dglSampleCoverage  (GLclampf value, GLboolean invert) 										{ glSampleCoverage (value, invert); processError(); };
void dglScissor  (GLint x, GLint y, GLsizei width, GLsizei height) 								{ glScissor (x, y, width, height); processError(); };
void dglShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
	{ glShaderBinary (n, shaders, binaryformat, binary, length); processError(); }
void dglShaderSource  (GLuint shader, GLsizei count, const GLchar** string, const GLint* length) { glShaderSource (shader, count, string, length); processError(); };
void dglStencilFunc  (GLenum func, GLint ref, GLuint mask) 										{ glStencilFunc (func, ref, mask); processError(); };
void dglStencilFuncSeparate  (GLenum face, GLenum func, GLint ref, GLuint mask) 				{ glStencilFuncSeparate (face, func, ref, mask); processError(); };
void dglStencilMask  (GLuint mask) 																{ glStencilMask (mask); processError(); };
void dglStencilMaskSeparate  (GLenum face, GLuint mask) 										{ glStencilMaskSeparate (face, mask); processError(); };
void dglStencilOp  (GLenum fail, GLenum zfail, GLenum zpass) 									{ glStencilOp (fail, zfail, zpass); processError(); };
void dglStencilOpSeparate  (GLenum face, GLenum fail, GLenum zfail, GLenum zpass) 				{ glStencilOpSeparate (face, fail, zfail, zpass); processError(); };
void dglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{ glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels); processError(); }
void dglTexParameterf  (GLenum target, GLenum pname, GLfloat param) 							{ glTexParameterf (target, pname, param); processError(); };
void dglTexParameterfv  (GLenum target, GLenum pname, const GLfloat* params) 					{ glTexParameterfv (target, pname, params); processError(); };
void dglTexParameteri  (GLenum target, GLenum pname, GLint param)								{ glTexParameteri (target, pname, param); processError(); };
void dglTexParameteriv  (GLenum target, GLenum pname, const GLint* params) 						{ glTexParameteriv (target, pname, params); processError(); };
void dglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{ glTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels); processError(); }
void dglUniform1f  (GLint location, GLfloat x) 													{ glUniform1f (location, x); processError(); };
void dglUniform1fv  (GLint location, GLsizei count, const GLfloat* v) 							{ glUniform1fv (location, count, v); processError(); };
void dglUniform1i  (GLint location, GLint x) 													{ glUniform1i (location, x); processError(); };
void dglUniform1iv  (GLint location, GLsizei count, const GLint* v) 							{ glUniform1iv (location, count, v); processError(); };
void dglUniform2f  (GLint location, GLfloat x, GLfloat y) 										{ glUniform2f (location, x, y); processError(); };
void dglUniform2fv  (GLint location, GLsizei count, const GLfloat* v) 							{ glUniform2fv (location, count, v); processError(); };
void dglUniform2i  (GLint location, GLint x, GLint y) 											{ glUniform2i (location, x, y); processError(); };
void dglUniform2iv  (GLint location, GLsizei count, const GLint* v) 							{ glUniform2iv (location, count, v); processError(); };
void dglUniform3f  (GLint location, GLfloat x, GLfloat y, GLfloat z) 							{ glUniform3f (location, x, y, z); processError(); };
void dglUniform3fv  (GLint location, GLsizei count, const GLfloat* v) 							{ glUniform3fv (location, count, v); processError(); };
void dglUniform3i  (GLint location, GLint x, GLint y, GLint z) 									{ glUniform3i (location, x, y, z); processError(); };
void dglUniform3iv  (GLint location, GLsizei count, const GLint* v) 							{ glUniform3iv (location, count, v); processError(); };
void dglUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)					{ glUniform4f (location, x, y, z, w); processError() }
void dglUniform4fv  (GLint location, GLsizei count, const GLfloat* v) 							{ glUniform4fv (location, count, v); processError(); };
void dglUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w)							{ glUniform4i (location, x, y, z, w); processError(); }
void dglUniform4iv  (GLint location, GLsizei count, const GLint* v) 							{ glUniform4iv (location, count, v); processError(); };
void dglUniformMatrix2fv  (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) 
																								{ glUniformMatrix2fv (location, count, transpose, value); processError(); };
void dglUniformMatrix3fv  (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) 
																								{ glUniformMatrix3fv (location, count, transpose, value); processError(); };
void dglUniformMatrix4fv  (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) 
																								{ glUniformMatrix4fv (location, count, transpose, value); processError(); };
void dglUseProgram  (GLuint program) 															{ glUseProgram (program); processError(); };
void dglValidateProgram  (GLuint program) 														{ glValidateProgram (program); processError(); };
void dglVertexAttrib1f  (GLuint indx, GLfloat x) 												{ glVertexAttrib1f (indx, x); processError(); };
void dglVertexAttrib1fv  (GLuint indx, const GLfloat* values) 									{ glVertexAttrib1fv (indx, values); processError(); };
void dglVertexAttrib2f  (GLuint indx, GLfloat x, GLfloat y) 									{ glVertexAttrib2f (indx, x, y); processError(); };
void dglVertexAttrib2fv  (GLuint indx, const GLfloat* values) 									{ glVertexAttrib2fv (indx, values); processError(); };
void dglVertexAttrib3f  (GLuint indx, GLfloat x, GLfloat y, GLfloat z) 							{ glVertexAttrib3f (indx, x, y, z); processError(); };
void dglVertexAttrib3fv  (GLuint indx, const GLfloat* values) 									{ glVertexAttrib3fv (indx, values); processError(); };
void dglVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);				{ glVertexAttrib4f (indx, x, y, z, w); processError(); }
void dglVertexAttrib4fv  (GLuint indx, const GLfloat* values) 									{ glVertexAttrib4fv (indx, values); processError(); };
void dglVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
{ glVertexAttribPointer (indx, size, type, normalized, stride, ptr); processError(); }
void dglViewport  (GLint x, GLint y, GLsizei width, GLsizei height) 							{ glViewport (x, y, width, height); processError(); };

#endif

#endif
