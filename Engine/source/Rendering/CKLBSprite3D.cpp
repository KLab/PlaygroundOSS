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
#include "CKLBSprite3D.h"
#include "CKLBNode.h"

static const SVertexEntry cteListVertex3D[3] = {
	//	StreamID	Offset	VBO?	Type
	{		1,		0,		false,	VEC4	 | VERTEX},	// Coordinate.
	{		2,		0,		false,	VEC2	 | TEXTURE},	// Texture UV.
	{ /*NA*/0,/*NA*/0,/*NA*/false,	END_LIST}	// Mark end of list.
};

void CKLBSprite3D::switchImage(CKLBImageAsset* pImage) {
	if (m_pImageAsset != pImage) {
		// Use switch image.
		CKLBSprite::switchImage(pImage);
		
		// Bind/Rebind index and buffer
		CKLBOGLWrapper& oglW = CKLBOGLWrapper::getInstance();

		if (!m_pIdxBuff) {
			// Create Buffer
			m_pIdxBuff = oglW.createIndexBuffer(m_uiIndexCount, false, this->m_pIndex);
		} else {
			m_pIdxBuff->overrideBuffer(m_uiIndexCount, this->m_pIndex);
		}
		
		if (!m_pBuff) {
			// Create Buffer
			m_pBuff = oglW.createVertexBuffer(m_uiVertexCount, cteListVertex3D, this->m_pVertex);
		} else {
			//
			m_pBuff->overrideBuffer(m_uiVertexCount, this->m_pVertex);
		}
		
		// Bind Buffer
		m_recompute = true;	// Model as changed.
	}
}

void CKLBSprite3D::set3DMatrix(float* matrix3d) {
	m_recompute = true;
	memcpy(m_matrixLocal, matrix3d, 16*sizeof(float));
}

void CKLBSprite3D::use2DSceneGraph(bool use) {
	if (m_bUse2DSceneGraph != use) {
		m_bUse2DSceneGraph = use;
		m_recompute = true;
	}
}

void CKLBSprite3D::applyNode(CKLBNode* pNode) {
	if (m_recompute || m_bUse2DSceneGraph) {
		if (m_bUse2DSceneGraph) {
			// Compose Local 3d matrix and 2d Matrix into compose 3d Matrix
			float node[16];
			float* src = pNode->m_composedMatrix.m_matrix;

			// Embbed 2D Matrix into 3D Matrix.
			node[0] = src[0];	node[1] = src[1];	node[2] = 0.0f;	node[3] = src[4];
			node[4] = src[2];	node[5] = src[3];	node[6] = 0.0f;	node[7] = src[5];
			node[8] = 0.0f;		node[9] = 0.0f;		node[10]= 1.0f; node[11]= 0.0f;
			node[12]= 0.0f;		node[13]= 0.0f;		node[14]= 0.0f; node[15]= 1.0f;

			// Compute Transformed matrix.
			for(int y = 0; y < 4; y++) {
				for(int x = 0; x < 4; x++) {
					m_matrixTransform[y*4+x] = 0.0f;
					for(int n = 0; n < 4; n++) {
						m_matrixTransform[y*4+x] += m_matrixLocal[y*4+n] * node[n*4+x];
					}
				}
			}
		} else {
			memcpy(m_matrixTransform,m_matrixLocal, sizeof(float) * 16);
		}
		
		//
		// Transform all vertex manually with transform matrix.
		//
		for (int vert=0; vert < m_uiVertexCount; vert++) {
			float* v	= &m_pVertex[vert*4];					// Vec 4 Dest
			float* src	= this->m_pImageAsset->getXYBuffer();	// Vec 3 Source

			// Matrix Transform.
			for(int n = 0; n < 4; n++) {
				v[n] = 0.0f;
				for(int m = 0; m < 3; m++) {
					v[n] += src[m] * m_matrixTransform[(m*4)+n];
				}
				v[n] += m_matrixTransform[(3*4)+n];	// Vec[3] is always 1.
			}
		}
	}
}

void CKLBSprite3D::draw() {
	//
	// Perform Rendering
	//
	CKLBOGLWrapper&	pOGLMgr	= CKLBOGLWrapper::getInstance();

	pOGLMgr.applyState(&s_3Dstate);

	m_pIdxBuff->setDrawOffset(0);
	m_pBuff->setDrawOffset(0);

	// For now texture is only one texture.
	CTextureUsage* pArrTexture[1];
	s32 idUniform[1];
	pArrTexture			[0]		= this->m_pTexture;
	idUniform			[0]		= 1;

	CBuffer* arrBuff[1] = {
		m_pBuff
	};

	// Clear Z Buffer
	dglClear(GL_DEPTH_BUFFER_BIT);

	// Render 3D Object
	pOGLMgr.draw(	GL_TRIANGLES,
					s_pShaderInstance,
					arrBuff,
					1,
					m_pIdxBuff,
					pArrTexture,
					idUniform, 
					m_uiIndexCount);
}

CShaderSet*			CKLBSprite3D::s_pShaderSet			= NULL;
CShaderInstance*	CKLBSprite3D::s_pShaderInstance		= NULL;
CShader*			CKLBSprite3D::s_pPShader			= NULL;
CShader*			CKLBSprite3D::s_pVShader			= NULL;
SRenderState		CKLBSprite3D::s_3Dstate;

CKLBSprite3D::CKLBSprite3D()
:m_pIdxBuff			(NULL)
,m_pBuff			(NULL)
,m_bUse2DSceneGraph	(true)
,m_recompute		(true)
{
	m_commandType = RENDERCOMMAND_3D | RENDERCOMMAND_SPRITE;

	if (s_pVShader == NULL) {
		CKLBOGLWrapper&		pOGLMgr
						= CKLBOGLWrapper::getInstance();
		// TODO RP : Hardcoded shader, vertex format.
		//   Render state,
		// -------------------------------------- SHADER
		const static SParam paramsVert[] = {
			// Name				Uniform?	StreamID	Data Type
			//								or
			//								UniformID
			{	"pos_attr"		,false		,1			,VEC4	| VERTEX },	// Coordinate.
			{	"uv_attr"		,false		,2			,VEC2	| TEXTURE},	// UV.
			{	""				,false		,0			,END_LIST}	// Mark end of list.
		};

		const static SParam paramsShader[] = {
			// Name				Uniform?	StreamID	Data Type
			//								or
			//								UniformID
			{	"texture"		,true		,1			,TEX2D    | TEXTURE },
	//		{	"power"			,true		,2			,VEC1F				},
	//		{	"table"			,true		,1			,TEX2D    | TEXTURE },
			{	""				,false		,0			,END_LIST}		// Mark end of list.
		};

		// Create shader vertex & pixel
		SRenderState::RENDER_MODE mode = SRenderState::TEXTURE_MUL_COLOR;
		s_pVShader		= pOGLMgr.createShader(mode, CKLBOGLWrapper::VERTEX_SHADER, paramsVert);
		s_pPShader		= pOGLMgr.createShader(mode, CKLBOGLWrapper::PIXEL_SHADER, paramsShader);

		// Map the shader together.
		s_pShaderSet	= pOGLMgr.createShaderSet(s_pVShader, s_pPShader);
		// Create instance of shader for param
		s_pShaderInstance = s_pShaderSet->createInstance();
		// ----------------------------------------------

		// Render State.
		s_3Dstate.setDepthState(true, true, SRenderState::LESS);
		s_3Dstate.setBlend(SRenderState::ALPHA);
	}

	// Reset
	for (int n=0; n < 16; n++) 
	{ m_matrixLocal[n] = 0.0f; }

	// Diagonal.
	m_matrixLocal[0 ] = 1.0f;
	m_matrixLocal[5 ] = 1.0f;
	m_matrixLocal[10] = 1.0f;
	m_matrixLocal[15] = 1.0f;

}

CKLBSprite3D::~CKLBSprite3D() {
	CKLBOGLWrapper& oglW = CKLBOGLWrapper::getInstance();
	if (m_pIdxBuff) {
		oglW.releaseIndexBuffer(m_pIdxBuff);
	}
	if (m_pBuff) {
		oglW.releaseVertexBuffer(m_pBuff);
	}
}
