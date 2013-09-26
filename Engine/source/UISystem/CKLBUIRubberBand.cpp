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
#define _USE_MATH_DEFINES
#include <math.h>
#include "CKLBUIRubberBand.h"
#include "CKLBUtility.h"

// Command Values
enum {
	UI_RUBBAND_SET_ORIGIN,
	UI_RUBBAND_SET_POINT,
	UI_RUBBAND_SET_ORDER,

	RB_ANIM_ENABLE   = 0x00000001,
	RB_ANIM_REALTIME = 0x00000002,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_RUBBAND_SET_ORIGIN",	UI_RUBBAND_SET_ORIGIN },
	{ "UI_RUBBAND_SET_POINT",	UI_RUBBAND_SET_POINT },

	{ "UI_RUBBAND_SET_ORDER",	UI_RUBBAND_SET_ORDER },

	{ "RB_ANIM_ENABLE",		RB_ANIM_ENABLE },
	{ "RB_ANIM_REALTIME",	RB_ANIM_REALTIME },

	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIRubberBand> factory("UI_RubberBand", CLS_KLBUIRUBBERBAND, cmd);

float CKLBUIRubberBand::ms_norot_mat[4] = { 1.0f, 0.0f, 0.0f, -1.0f };

CKLBUIRubberBand::CKLBUIRubberBand()
: CKLBUITask    ()
, m_assetOrigin (NULL)
, m_assetJoint  (NULL)
, m_assetPoint  (NULL)
{
	m_newScriptModel = true;
}

CKLBUIRubberBand::~CKLBUIRubberBand() 
{
	KLBDELETEA(m_assetOrigin);
	KLBDELETEA(m_assetJoint);
	KLBDELETEA(m_assetPoint);
}

u32
CKLBUIRubberBand::getClassID()
{
	return CLS_KLBUIRUBBERBAND;
}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIRubberBand::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",		R_UINTEGER,	NULL,										(getBoolT)&CKLBUIRubberBand::getOrder,			0	}, // 表示オーダー

	{	"asset_origin",	R_STRING,	NULL,										(getBoolT)&CKLBUIRubberBand::getAssetOrigin,	0	},
	{	"asset_joint",	R_STRING,	NULL,										(getBoolT)&CKLBUIRubberBand::getAssetJoint,		0	},
	{	"asset_point",	R_STRING,	NULL,										(getBoolT)&CKLBUIRubberBand::getAssetPoint,		0	},

	{	"originX",		NUMERIC,	(setBoolT)&CKLBUIRubberBand::setOriginX,	(getBoolT)&CKLBUIRubberBand::getOriginX,		0	},
	{	"originY",		NUMERIC,	(setBoolT)&CKLBUIRubberBand::setOriginY,	(getBoolT)&CKLBUIRubberBand::getOriginY,		0	},

	{	"pointX",		NUMERIC,	(setBoolT)&CKLBUIRubberBand::setPointX,		(getBoolT)&CKLBUIRubberBand::getPointX,			0	},
	{	"pointY",		NUMERIC,	(setBoolT)&CKLBUIRubberBand::setPointY,		(getBoolT)&CKLBUIRubberBand::getPointY,			0	},
		
	{	"f_anim",		BOOLEANT,	(setBoolT)&CKLBUIRubberBand::setFAnim,		(getBoolT)&CKLBUIRubberBand::getFAnim,			0	},
	{	"f_realtime",	BOOLEANT,	(setBoolT)&CKLBUIRubberBand::setFAnimRT,	(getBoolT)&CKLBUIRubberBand::getFAnimRT,		0	},
	{	"anim_time",	UINTEGER,	(setBoolT)&CKLBUIRubberBand::setAnimTime,	(getBoolT)&CKLBUIRubberBand::getAnimTime,		0	}
};

// 引数のインデックス定義
enum {
	ARG_PARENT = 1,

	ARG_ORDER,

	ARG_X,
	ARG_Y,

	ARG_ASSET_ORIGIN,
	ARG_ASSET_JOINT,
	ARG_ASSET_POINT,

	ARG_RESOLUTION,

	ARG_FLAGS,

	ARG_ANIM_TIME,

	ARG_JOINT_ORDER_OFFSET,
	ARG_POINT_ORDER_OFFSET,

	ARG_ROT_ORIGIN,
	ARG_ROT_JOINT,
	ARG_ROT_POINT,

	ARG_REQUIRE = ARG_ASSET_POINT,
	ARG_NUMS = ARG_ROT_POINT
};

CKLBUIRubberBand* 
CKLBUIRubberBand::create(
    CKLBUITask* pParent, 
    CKLBNode* pNode, 
    u32 order, float x, float y, u32 resolution, 
    const char* origin, const char* joint, const char* point, 
    u32 flags, u32 animTime,
    int joint_order_off, int point_order_off,
    bool rot_origin, bool rot_joint, bool rot_point) 
{
	CKLBUIRubberBand* pTask = KLBNEW(CKLBUIRubberBand);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, order,x,y,resolution,origin,joint,point,flags,animTime,joint_order_off,point_order_off,rot_origin,rot_joint,rot_point)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool 
CKLBUIRubberBand::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 resolution, const char* origin, const char* joint, const char* point, u32 flags, u32 animTime,
                       int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point) 
{
    if(!setupNode()) { return false; }
	bool bResult = initCore(order,x,y,resolution,origin,joint,point,flags,animTime,joint_order_off,point_order_off,rot_origin,rot_joint,rot_point);
	bResult = registUI(pParent, bResult);
	if (pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}


bool CKLBUIRubberBand::initCore(u32 order, float x, float y, u32 resolution, const char* origin, const char* joint, const char* point, u32 flags, u32 animTime,
								int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(0, 0);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order     = order;
	m_originX   = x;
	m_originY   = y;

	// 初期の先端位置は起点と同じ
	m_x         = m_originX;
	m_y         = m_originY;

	m_reso      = resolution;
    if(!m_reso) { m_reso = 10; }    // 0 の場合は10分割

	setStrC(m_assetOrigin, origin);
	setStrC(m_assetJoint,  joint);
	setStrC(m_assetPoint,  point);

	m_rot_origin = rot_origin;
	m_rot_joint  = rot_joint;
	m_rot_point  = rot_point;

	m_fAnim     = (flags & RB_ANIM_ENABLE)   ? true : false;
	m_fAnimRT   = (flags & RB_ANIM_REALTIME) ? true : false;
	m_animTime  = animTime;

	m_animCount = 0;

	// 一通り値が取れたので、nodeやspriteを用意する。
	
	// 分割数-1の個数だけ、JointNodeの配列を確保する
	m_pJointNode = KLBNEWA(CKLBNode *, m_reso - 1);
    if(!m_pJointNode) { return false; }
	m_sprJoint = KLBNEWA(CKLBDynSprite *, m_reso - 1);
	if(!m_sprJoint) {
		KLBDELETEA(m_pJointNode);
		return false;
	}

	CKLBImageAsset * pImgOrigin = (CKLBImageAsset *)CKLBUtility::loadAssetScript( m_assetOrigin, &m_handle_origin);
	CKLBImageAsset * pImgJoint  = (CKLBImageAsset *)CKLBUtility::loadAssetScript( m_assetJoint,  &m_handle_joint);
	CKLBImageAsset * pImgPoint  = (CKLBImageAsset *)CKLBUtility::loadAssetScript( m_assetPoint,  &m_handle_point);

	m_img_origin = pImgOrigin;
	m_img_point  = pImgPoint;
	m_img_joint  = pImgJoint;

	// JointのNodeを作る
	bool bResult = true;
	POINT ** arrPoint = &m_vertJoint;
	int *    cntValue = &m_cntJoint;
	
	for(int i = 0; i < m_reso - 1; i++) {
		// m_pJointNode[i] = pImgJoint->createSubTree(m_order + joint_order_off);

		m_pJointNode[i] = KLBNEW(CKLBNode);
		if(!m_pJointNode[i]) {
			bResult = false;
			continue;
		}
		m_sprJoint[i] = create_rotSprite(m_pJointNode[i], order + joint_order_off, pImgJoint, cntValue, arrPoint);
		// 同じassetを使用するので、頂点配列および頂点数の取得は一回で充分。
		cntValue = NULL;
		arrPoint = NULL;

		getNode()->addNode(m_pJointNode[i]);
		m_pJointNode[i]->setTranslate(x, y);
	}
	if(!bResult) {
		for(int i = 0; i < m_reso - 1; i++) {
			KLBDELETE(m_pJointNode[i]);
		}
		KLBDELETEA(m_pJointNode);
		CKLBDataHandler::releaseHandle(m_handle_origin);
		CKLBDataHandler::releaseHandle(m_handle_joint);
		CKLBDataHandler::releaseHandle(m_handle_point);
		return false;
	}

	// 起点と終点のDynSpriteを作る
	m_pOriginNode = KLBNEW(CKLBNode);
	m_sprOrigin = create_rotSprite(m_pOriginNode, m_order, pImgOrigin, &m_cntOrigin, &m_vertOrigin);

	m_pPointNode = KLBNEW(CKLBNode);
	m_sprPoint  = create_rotSprite(m_pPointNode, m_order + point_order_off, pImgPoint, &m_cntPoint, &m_vertPoint);

	return true;
}

bool
CKLBUIRubberBand::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	u32 flags    = (argc >= ARG_FLAGS)      ? lua.getInt(ARG_FLAGS)     : 0;
	u32 animTime = (argc >= ARG_ANIM_TIME)  ? lua.getInt(ARG_ANIM_TIME) : 0;

	int joint_order_off = ((argc >= ARG_JOINT_ORDER_OFFSET) && !lua.isNil(ARG_JOINT_ORDER_OFFSET)) ? lua.getInt(ARG_JOINT_ORDER_OFFSET) : 1;
	int point_order_off = ((argc >= ARG_POINT_ORDER_OFFSET) && !lua.isNil(ARG_POINT_ORDER_OFFSET)) ? lua.getInt(ARG_POINT_ORDER_OFFSET) : 2;

	bool rot_origin = (argc >= ARG_ROT_ORIGIN) ? lua.getBool(ARG_ROT_ORIGIN) : true;
	bool rot_joint  = (argc >= ARG_ROT_JOINT)  ? lua.getBool(ARG_ROT_JOINT)  : false;
	bool rot_point  = (argc >= ARG_ROT_POINT)  ? lua.getBool(ARG_ROT_POINT)  : true;

	return initCore(
		lua.getInt(ARG_ORDER),lua.getFloat(ARG_X), lua.getFloat(ARG_Y),
		lua.getInt(ARG_RESOLUTION),
		lua.getString(ARG_ASSET_ORIGIN),
		lua.getString(ARG_ASSET_JOINT),
		lua.getString(ARG_ASSET_POINT),
		flags,
		animTime,
		joint_order_off,
		point_order_off,
		rot_origin, rot_joint, rot_point);
}

CKLBDynSprite *
CKLBUIRubberBand::create_rotSprite(CKLBNode * node, u32 order, CKLBImageAsset * asset, int * vertCnt, POINT ** arrVert)
{
	// 与えられたテクスチャの頂点数を得る
	int vertCount   = asset->getVertexCount();
	int indxCount   = asset->getIndexCount();
	int triangleNum = (indxCount + 2) / 3;	// 構成するために必要な三角形の数
	u16 * pIndex    = asset->getIndexBuffer();

    if(vertCnt) { *vertCnt = vertCount; }
	if(arrVert) {
		POINT * arrPoint = KLBNEWA(POINT, vertCount);
		*arrVert = arrPoint;
	}
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
	CKLBDynSprite * dynSpr = pRdrMgr.allocateCommandDynSprite(triangleNum*3,triangleNum*3); // 三角形4個分のDynamicSprite	CKLBDynSprite

	dynSpr->setTexture(asset);
	node->setRender(dynSpr);
	node->setRenderOnDestroy(true);
	node->setPriority(order);

	// 頂点のuvを割り当てる。uvは以後割り当て不要。
	for(int i = 0; i < indxCount; i++) {
		float u, v;
		float x, y;
		int idx = pIndex[i];
		asset->getXY(idx, &x, &y);		// assetからxy取得
		asset->getUV(idx, &u, &v);		// assetからuv取得
		dynSpr->setVertexXY(i, x, y);	// DynSpriteの頂点にxyを指定
		dynSpr->setVertexUV(i, u, v);	// DynSpriteの頂点にuvを指定
	}

	getNode()->addNode(node);

	return dynSpr;
}

int
CKLBUIRubberBand::commandUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBool(false);
		return 1;
	}
	int cmd = lua.getInt(2);
	int ret = 1;
	switch(cmd)
	{
	case UI_RUBBAND_SET_ORDER:
		{
			bool bResult = false;
			if(argc == 5) {
				u32 order_origin = lua.getInt(3);
				u32 order_joint  = lua.getInt(4);
				u32 order_point  = lua.getInt(5);
				
				bResult = setOrder(order_origin, order_joint, order_point);
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	}
	return ret;
}

void
CKLBUIRubberBand::dieUI()
{
	CKLBUtility::deleteNode(m_pOriginNode, m_handle_origin);
	CKLBUtility::deleteNode(m_pPointNode, m_handle_point);

	for(int i = 0; i < m_reso - 1; i++) {
		KLBDELETE(m_pJointNode[i]);
	}
	CKLBDataHandler::releaseHandle(m_handle_joint);
	KLBDELETEA(m_sprJoint);
	KLBDELETEA(m_pJointNode);

	KLBDELETEA(m_vertOrigin);
	KLBDELETEA(m_vertPoint);
	KLBDELETEA(m_vertJoint);
}

void
CKLBUIRubberBand::execute(u32 deltaT)
{
	float dx, dy;
	float x, y;
	float animRate;
	x = m_originX;
	y = m_originY;
	dx = m_x - x;
	dy = m_y - y;

	if(m_fAnim) {
		if(m_fAnimRT) {
			m_animCount += deltaT;	// 実時間式
		} else {
			m_animCount++;			// フレームカウント式
		}
		if(m_animTime > 0) {
			while(m_animCount >= m_animTime) {
				m_animCount -= m_animTime;
			}
		}

		// アニメーションレート
		animRate = (float)m_animCount / (float)m_animTime;
	} else {
		animRate = 1.0f;
	}
	// 間のポイントが採るべき位置を設定
	for(int i = 0; i < m_reso - 1; i++) {
		float n = (float)i + animRate;

		m_pJointNode[i]->setTranslate(x + (dx * n / m_reso), y + (dy * n / m_reso));
	}
	// 位置を指定
	m_pOriginNode->setTranslate(x, y);
	m_pPointNode->setTranslate(x + dx, y + dy);

	// 先端と基点は回転させる。

	// 傾きから回転の角度を得る
	float theta = 0.0f;
	float adx   = (dx > 0.0f) ? dx : -dx;
	float ady   = (dy > 0.0f) ? dy : -dy;
	if(fabs(adx) < 1.0f && fabs(ady) < 1.0f) {
		theta = 0.0f;
	} else {
		theta = (adx > ady) ? atan(ady/adx) : (M_PI / 2 - atan(adx/ady));
	}
	if(dx < 0) { theta = M_PI - theta; }
    if(dy < 0) { theta = -theta;       }

	float sin_h = sin(theta);
	float cos_h = cos(theta);

	float mat[4];
	mat[0] = cos_h;
	mat[1] = sin_h;
	mat[2] = sin_h;
	mat[3] = -cos_h;

	rot_vertex(m_sprOrigin, m_img_origin, m_cntOrigin, m_vertOrigin, (m_rot_origin) ? mat : ms_norot_mat);
	rot_vertex(m_sprPoint,  m_img_point,  m_cntPoint,  m_vertPoint,  (m_rot_point)  ? mat : ms_norot_mat);
	m_pOriginNode->markUpMatrix();
	m_pPointNode->markUpMatrix();

	// 間の点も回転させる
	for(int i = 0; i < m_reso - 1; i++) {
		rot_vertex(m_sprJoint[i], m_img_joint, m_cntJoint, m_vertJoint, (m_rot_joint) ? mat : ms_norot_mat);
		m_pJointNode[i]->markUpMatrix();
	}
}

void
CKLBUIRubberBand::rot_vertex(CKLBDynSprite * dynSpr, CKLBImageAsset * pAsset, int cntVert, POINT * pbuf, float * mat)
{
	// 持っている頂点をすべて与えられたマトリクスで回転させる
	for(int i = 0; i < cntVert; i++) {
		float x, y;
		pAsset->getXY(i, &x, &y);
		pbuf[i].x = x * mat[0] + y * mat[2];
		pbuf[i].y = x * mat[1] + y * mat[3];
	}

	// 各頂点の座標を指定する
	int cntIndex = pAsset->getIndexCount();
	u16 * pIndex = pAsset->getIndexBuffer();
	for(int i = 0; i < cntIndex; i++) {
		int idx = pIndex[i];
		dynSpr->setVertexXY(i, pbuf[idx].x, pbuf[idx].y);	// DynSpriteの頂点にxyを指定
	}

}
