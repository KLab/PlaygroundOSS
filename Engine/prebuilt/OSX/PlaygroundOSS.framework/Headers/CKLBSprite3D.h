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
#ifndef __CKLB_SPRITE3D__
#define __CKLB_SPRITE3D__

#include "CKLBRendering.h"

class CKLBSprite3D : public CKLBSprite {
public:
	void switchImage		(CKLBImageAsset* pImage);
	void set3DMatrix		(float* matrix3d);
	void use2DSceneGraph	(bool use);
	void draw				();

	// Inheritance.
	virtual	void applyNode(CKLBNode* pNode);
protected:
	CKLBSprite3D ();
	~CKLBSprite3D();
private:
	float			m_matrixLocal[16];
	float			m_matrixTransform[16];
	CIndexBuffer*	m_pIdxBuff;
	CBuffer*		m_pBuff;
	bool			m_bUse2DSceneGraph;
	bool			m_recompute;

	static CShader*				s_pVShader;
	static CShader*				s_pPShader;
	static CShaderSet*			s_pShaderSet;
	static CShaderInstance*		s_pShaderInstance;
	static SRenderState			s_3Dstate;
};

#endif
