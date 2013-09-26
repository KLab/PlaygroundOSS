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

// nothing.

CTexture::CTexture() {
	// Do nothing.
}

CTexture::~CTexture() {
	// Do nothing.
}

CSubTexture::CSubTexture() {
	// Do nothing.
}

CSubTexture::~CSubTexture() {
	// Do nothing.
}

CFontTexture::CFontTexture():CSubTexture(),
	fixedSize(32),
	currX(0),
	currY(0),
	u0u1v0v1(null),
	wh(null)
{
}

CFontTexture::~CFontTexture() {
}

void CFontTexture::setup(s32 fixedSize) {
	this->currX = 0;
	this->currY = 0;
	this->fixedSize	= fixedSize;
}

bool CFontTexture::setupCharCount(u16 charCount) {
	wh			= KLBNEWA(u32,charCount);
	u0u1v0v1	= KLBNEWA(float,charCount * 4);
	if (wh && u0u1v0v1) {
		for (s32 n=0; n<charCount*4;) {
			u0u1v0v1[n++] = 0.0f;
			u0u1v0v1[n++] = 0.0f;
			u0u1v0v1[n++] = 0.0f;
			u0u1v0v1[n++] = 0.0f;
		}
		return true;
	} else {
		if (wh)			{ KLBDELETE(wh);		}
		if (u0u1v0v1)	{ KLBDELETE(u0u1v0v1);	}
		return false;
	}
}

void CFontTexture::registerChar(u16 c, s32 variableSize) {
	s32 idx = c << 2;
	u32	size;
	float u0, v0;
	float u1, v1;

	// 1.currX, currY define u0,v0
	convertPixelToRenderUV(this->currX, this->currY, TOP_LEFT, &u0, &v0);

	// 2.Prepair next char.
	// Horizontal
	this->currX += variableSize;

	if (this->currX > this->width) {
		this->currX = 0;
		this->currY += fixedSize;
		convertPixelToRenderUV(this->currX, this->currY, TOP_LEFT, &u0, &v0);
		this->currX += variableSize;
	}

	convertPixelToRenderUV(this->currX, this->currY + fixedSize, TOP_LEFT, &u1, &v1);


	size = (variableSize << 16) | fixedSize;

	u0u1v0v1[idx  ] = u0;
	u0u1v0v1[idx+1] = u1;
	u0u1v0v1[idx+2] = v0;
	u0u1v0v1[idx+3] = v1;
	wh[c]			= size;
}

void CFontTexture::registerChar(u16 c, u32 x, u32 y, u32 w, u32 h, bool /*rot*/, u8 marginTopLeft, u8 marginBottomRight) {
	s32 idx = c << 2;
	float u0, v0;
	float u1, v1;

	// 1.currX, currY define u0,v0
	convertPixelToRenderUV(x + marginTopLeft, y + marginTopLeft,						TOP_LEFT, &u0, &v0);
	{
//	if (rot) {
/*		convertPixelToRenderUV(x + h, y + w,	TOP_LEFT, &u1, &v1);
		u0u1v0v1[idx  ] = v0;
		u0u1v0v1[idx+1] = v1;
		u0u1v0v1[idx+2] = u0;
		u0u1v0v1[idx+3] = u1;
	} else {*/
		convertPixelToRenderUV(x + w - marginBottomRight, y + h - marginBottomRight,	TOP_LEFT, &u1, &v1);
		u0u1v0v1[idx  ] = u0;
		u0u1v0v1[idx+1] = u1;
		u0u1v0v1[idx+2] = v0;
		u0u1v0v1[idx+3] = v1;
	}

	w -= marginTopLeft + marginBottomRight;
	h -= marginTopLeft + marginBottomRight;

	wh[c]			= (w << 16) | h;
}

void CFontTexture::getChar(u16 c, float* u0, float* u1, float* v0, float* v1, float* w, float* h) {

	u16 flipH = c & 0x8000;
	u16 flipV = c & 0x4000;

	c &= 0x3FFF;
	s32 idx = c << 2;

	if (flipH) {
		*u1 = u0u1v0v1[idx  ];
		*u0 = u0u1v0v1[idx+1];
	} else {
		*u0 = u0u1v0v1[idx  ];
		*u1 = u0u1v0v1[idx+1];
	}

	if (flipV) {
		*v1 = u0u1v0v1[idx+2];
		*v0 = u0u1v0v1[idx+3];
	} else {
		*v0 = u0u1v0v1[idx+2];
		*v1 = u0u1v0v1[idx+3];
	}


	*w  = float(wh[c] >> 16);
	*h  = float(wh[c] & 0xFFFF);
}
