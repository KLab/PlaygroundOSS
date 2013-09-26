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
#include "CKLBUIProgressBar.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"

// Command Values
enum {
	UI_PROGRESS_RESET = 0,
	UI_PROGRESS_SET,
	UI_PROGRESS_SET_IMAGE,
	UI_PROGRESS_MAX,
	UI_PROGRESS_GET,

	UI_PROGRESS_FILTER_VISIBLE,
	UI_PROGRESS_FILTER_COLOR,
	UI_PROGRESS_FILTER_ANIM,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_PROGRESS_RESET",		UI_PROGRESS_RESET       },
	{ "UI_PROGRESS_SET",		UI_PROGRESS_SET         },
	{ "UI_PROGRESS_SET_IMAGE",	UI_PROGRESS_SET_IMAGE   },
	{ "UI_PROGRESS_MAX",		UI_PROGRESS_MAX         },
	{ "UI_PROGRESS_GET",		UI_PROGRESS_GET         },

	{ "UI_PROGRESS_FILTER_VISIBLE",	UI_PROGRESS_FILTER_VISIBLE  },
	{ "UI_PROGRESS_FILTER_COLOR",	UI_PROGRESS_FILTER_COLOR    },
	{ "UI_PROGRESS_FILTER_ANIM",	UI_PROGRESS_FILTER_ANIM     },

	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIProgressBar> factory("UI_ProgressBar", CLS_KLBUIPROGRESS, cmd);


CKLBUIProgressBar::CKLBUIProgressBar()
: CKLBUITask    ()
, m_texHandle   (0)
, m_bFilterSW   (false)
, m_bColAnim    (false)
, m_emptyImage  (NULL)
, m_fullImage   (NULL)
, m_pTexAsset   (NULL)
, m_filterImage (NULL)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIProgressBar::~CKLBUIProgressBar() 
{
	KLBDELETEA(m_emptyImage);
	KLBDELETEA(m_fullImage);
	KLBDELETEA(m_filterImage);
}

// 共通インデックスバッファ
const u16 CKLBUIProgressBar::ms_indices[] = {
	0, 1, 2,
	3, 2, 1,
	4, 5, 6,
	7, 6, 5,

	// filter
	8, 9, 10,
	11, 10, 9
};

CKLBLuaPropTask::PROP_V2 CKLBUIProgressBar::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",			NUMERIC,	(setBoolT)&CKLBUIProgressBar::setWidth,			(getBoolT)&CKLBUIProgressBar::getWidth,			0	},
	{	"height",			NUMERIC,	(setBoolT)&CKLBUIProgressBar::setHeight,		(getBoolT)&CKLBUIProgressBar::getHeight,		0	},
	{	"order",			UINTEGER,	(setBoolT)&CKLBUIProgressBar::setOrder,			(getBoolT)&CKLBUIProgressBar::getOrder,			0	},
	{	"f_vert",			BOOLEANT,	(setBoolT)&CKLBUIProgressBar::setVertical,		(getBoolT)&CKLBUIProgressBar::getVertical,		0	},
	{	"t_anim",			UINTEGER,	(setBoolT)&CKLBUIProgressBar::setAnimTime,		(getBoolT)&CKLBUIProgressBar::getAnimTime,		0	},
	{	"start",			NUMERIC,	(setBoolT)&CKLBUIProgressBar::setStart,			(getBoolT)&CKLBUIProgressBar::getStart,			0	},
	{	"end",				NUMERIC,	(setBoolT)&CKLBUIProgressBar::setEnd,			(getBoolT)&CKLBUIProgressBar::getEnd,			0	},
	{	"img_empty",		R_STRING,	NULL,											(getBoolT)&CKLBUIProgressBar::getImgEmpty,		0	},
	{	"img_full",			R_STRING,	NULL,											(getBoolT)&CKLBUIProgressBar::getImgFull,		0	},
	{	"value",			NUMERIC,	(setBoolT)&CKLBUIProgressBar::setValue,			(getBoolT)&CKLBUIProgressBar::getValue,			0	},
	{	"img_filter",		STRING,		(setBoolT)&CKLBUIProgressBar::setImgFilter,		(getBoolT)&CKLBUIProgressBar::getImgFilter,		0	},
	{	"filter_visible",	BOOLEANT,	(setBoolT)&CKLBUIProgressBar::setFilterVisible,	(getBoolT)&CKLBUIProgressBar::getFilterVisible,	0	},
	{	"filter_color",		UINTEGER,	(setBoolT)&CKLBUIProgressBar::setFilterColor,	(getBoolT)&CKLBUIProgressBar::getFilterColor,	0	}
};

// 引数のインデックス定義
enum {
	ARG_PARENT = 1,
	ARG_ORDER,

	ARG_X,
	ARG_Y,
	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_IMG_FULL,
	ARG_IMG_EMPTY,

	ARG_START,
	ARG_END,
	ARG_ANIM,
	ARG_VERT,

	ARG_BARFILTER,

	ARG_TOTAL = ARG_BARFILTER,
	ARG_REQUIRE = ARG_IMG_FULL	// 最低限必要なパラメータ数
};

CKLBUIProgressBar *
CKLBUIProgressBar::create(CKLBUITask * pParent, CKLBNode * pNode,
                          u32 order, float x, float y, float width, float height,
                          const char * full_image, const char * empty_image,
                          s32 start_pix, s32 end_pix, int anim, bool vert,
                          const char * barfilter_image)
{
	CKLBUIProgressBar * pTask = KLBNEW(CKLBUIProgressBar);
    if(!pTask) { return NULL; }
    if(start_pix < 0) { start_pix = 0;                     }
	if(end_pix   < 0) { end_pix = (vert) ? height : width; }
	if(!pTask->init(pParent, pNode, order, x, y, width, height,
					full_image, empty_image, start_pix, end_pix, anim, vert,
					barfilter_image)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIProgressBar::init(CKLBUITask * pParent, CKLBNode * pNode,
                        u32 order, float x, float y, float width, float height,
                        const char * full_image, const char * empty_image,
                        s32 start_pix, s32 end_pix, int anim, bool vert,
                        const char * barfilter_image)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, width, height,
							full_image, empty_image, start_pix, end_pix, anim, vert,
							barfilter_image);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}


bool
CKLBUIProgressBar::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

    if(argc > ARG_TOTAL || argc < ARG_REQUIRE) { return false; }
	u32   order  = lua.getInt(ARG_ORDER);
	float x      = lua.getFloat(ARG_X);
	float y      = lua.getFloat(ARG_Y);
	float width  = lua.getFloat(ARG_WIDTH);
	float height = lua.getFloat(ARG_HEIGHT);
	const char * img_full  = lua.getString(ARG_IMG_FULL);
	const char * img_empty = lua.getString(ARG_IMG_EMPTY);

	bool  vert  = (argc >= ARG_VERT)  ? lua.getBool(ARG_VERT)   : false;
	int   anim  = (argc >= ARG_ANIM)  ? lua.getInt(ARG_ANIM)    : 0;
	float start = (argc >= ARG_START) ? lua.getFloat(ARG_START) : 0.0f;
	float end   = (argc >= ARG_END)   ? lua.getFloat(ARG_END)   : ((!vert) ? width : height);
	const char * img_barfilter = (argc >= ARG_BARFILTER) ? lua.getString(ARG_BARFILTER) : NULL;

	return initCore(order, x, y, width, height, img_full, img_empty, start, end, anim, vert, img_barfilter);
}

bool
CKLBUIProgressBar::initCore(u32 order,
                            float x, float y, float width, float height,
                            const char * full_image, const char * empty_image,
                            s32 start_pix, s32 end_pix, int anim, bool vert,
                            const char * img_barfilter)
{
	// 対応するプロパティリストを規定する。
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	// 起動関数のパラメータとして初期値を受け取る
	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	setOrder(order);
	setWidth(width);
	setHeight(height);
	if(empty_image)     { setStrC(m_emptyImage, empty_image);	}
	if(full_image)      { setStrC(m_fullImage, full_image);		}
	if(img_barfilter)   { setStrC(m_filterImage, img_barfilter);}
	
	float start = start_pix;
	float end   = end_pix;

	m_isVertical 	= vert;
	m_anim_length	= anim;
	m_startPixelF 	= ((start != -1) ? start : 0.0f);
	m_endPixelF	  	= ((end != -1)	 ? end   : width);

	m_fStart	  	= 0.0f;
	m_fEnd        	= 1.0f;


	// 初期値は 0.0
	m_fValue = 1.0f;	// Force setValue to be completely executed.
	setValue(0.0f);

	// 必要とされるオブジェクトを生成する
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	// イメージの取得
	const char * imgname[3];
	const char * asset_name = m_fullImage;
	imgname[0] = m_fullImage;
	imgname[1] = m_emptyImage;
	imgname[2] = m_filterImage;
	{
		const char * scheme[] = {
			"asset://",
			"file://install/",
			"file://external/",
			0
		};
		for(int i = 0; i < 3; i++) {
			if(!imgname[i]) continue;
			for(int j = 0; scheme[j]; j++) {
				int len = strlen(scheme[j]);
				if(!strncmp(imgname[i], scheme[j], len)) {
					imgname[i] += len;
					break;
				}
			}
		}
	}

	m_pTexAsset = (CKLBTextureAsset *)CKLBUtility::loadAssetScript(asset_name, &m_texHandle, NULL, true);
	if(!m_pTexAsset) {
		return false;
	}

	for(int i = 0; i < 3; i++) {
		m_pTex[i] = NULL;
		if(!imgname[i]) continue;
		m_pTex[i] = m_pTexAsset->getImage(imgname[i]);

		// 同じ .texb 内部に存在しない場合はエラー
		if(m_pTex[i] == NULL) {
			CKLBScriptEnv::getInstance().error("TEXB differs between [%s] and [%s].", imgname[0], imgname[1]);
			CKLBDataHandler::releaseHandle(m_texHandle);
			return false;
		}

		klb_assert(m_pTex[i]->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Must use a standard rectangular image in ProgressBar task.");
	}
	m_vertices = 8;
	m_indices = 12;
	if(imgname[2]) {
		m_vertices += 4;
		m_indices += 6;
	}
	m_pDynSprite = pRdrMgr.allocateCommandDynSprite(m_vertices, m_indices); // 三角形4個分 (+ フィルタで計6個)
	m_pNode = KLBNEW(CKLBNode);
	if ((!m_pDynSprite) || (!m_pNode)) {
		CKLBDataHandler::releaseHandle(m_texHandle);
		return false;
	}

	setupProgressBarConstant();
	setFilterVisible(false);

	// 二つのDynSpriteを自分のNodeに登録
	m_pNode->setRender(m_pDynSprite);
	m_pNode->setRenderOnDestroy(true);

	// m_pNode->setVisible(true);

	// プロパティから初期状態を設定する
	m_prevRate = getValue();
	setBorder(m_prevRate);

	// 自身の持つノードに追加
	getNode()->addNode(m_pNode);

	REFRESH_A;
	REFRESH_B;

	return true;
}

u32
CKLBUIProgressBar::getClassID()
{
	return CLS_KLBUIPROGRESS;
}

int
CKLBUIProgressBar::commandUI(CLuaState& lua, int argc, int cmd)
{
	//if(argc < 2 || 3 < argc) return 0;
	int ret = 0;
	switch(cmd)
	{
	case UI_PROGRESS_RESET:
		{
			reset();
		}
		break;
	case UI_PROGRESS_SET:
		{
			if(argc != 3) { return 0; }
			float val = lua.getFloat(3);
			setValue(val);
		}
		break;
	case UI_PROGRESS_SET_IMAGE:
       {
           bool bResult = false;
           if(argc == 4) {
               bool isEmpty = lua.getBool(3);
               const char * path = lua.getString(4);
               bResult = setImg(isEmpty, path);
           }
           lua.retBool(bResult);
           ret = 1;
       }
       break;
	case UI_PROGRESS_MAX:
		setValue(m_fEnd);
		break;
	case UI_PROGRESS_GET:
		{
			float val = getValue();
			lua.retDouble(val);
			ret = 1;
		}
		break;
	case UI_PROGRESS_FILTER_VISIBLE:
		{
			bool bResult = false;
			if(argc == 3) {
				bool visible = lua.getBool(3);
				setFilterVisible(visible);
				bResult = true;
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	case UI_PROGRESS_FILTER_COLOR:
		{
			bool bResult = false;
			if(argc == 4) {
				u32 alpha = lua.getInt(3);
				u32 rgb   = lua.getInt(4);
				u32 color = ((alpha & 0xff) << 24) | (rgb & 0xffffff);
				setFilterColor(color);
				bResult = true;
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	case UI_PROGRESS_FILTER_ANIM:
		{
			bool bResult = false;
			if(argc >= 3 && argc <= 8) {
				bool bColAnim = lua.getBool(3);
				u32 alpha1 = (argc >= 4) ? lua.getInt(4) : 0xff;
				u32 color1 = (argc >= 5) ? lua.getInt(5) : 0xffffff;
				u32 alpha2 = (argc >= 6) ? lua.getInt(6) : 0xff;
				u32 color2 = (argc >= 7) ? lua.getInt(7) : 0xffffff;
				u32 freq   = (argc >= 8) ? lua.getInt(8) : 500;
				color1 = ((alpha1 & 0xff) << 24) | (color1 & 0xffffff);
				color2 = ((alpha2 & 0xff) << 24) | (color2 & 0xffffff);
				bResult = setFilterAnim(bColAnim, color1, color2, freq);
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	}
	return ret;
}

void
CKLBUIProgressBar::dieUI()
{
	CKLBUtility::deleteNode(m_pNode, m_texHandle);
}

void
CKLBUIProgressBar::execute(u32 deltaT)
{
	// Order Changed.
	if(CHANGE_A) {
		CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
		// 表示プライオリティを設定
		int order = getOrder();
		m_pDynSprite->changeOrder(pRdrMgr, order);
		RESET_A;
	}

	// Geometry, value change.
	if(CHANGE_B) {
		REFRESH_C;	// Cascade C change.
		m_iTimeCnt = 0;
		m_nowRate = m_prevRate;
		RESET_B;
	}

	if(CHANGE_D) {
		setupProgressBarConstant();
		setBorder(m_lastValue);
		RESET_D;
	}

	if(CHANGE_C) {
		u32 p_anim = getAnimTime();
		m_iTimeCnt += deltaT;

		float rate = (!p_anim) ? 1.0f : ((float)m_iTimeCnt/p_anim);
        if(rate > 1.0f) { rate = 1.0f; }

		float value = m_nowRate + (getValueNormalized() - m_nowRate) * rate;

		// アニメーション中に書き換える
		if(m_lastValue != value) {
			setBorder(value);
		}
		if(rate >= 1.0f) {
			RESET_C;
			m_prevRate = getValueNormalized();
		}
	}

	// フィルタのカラーアニメーションが有効ならば再生する。
	if(m_bColAnim) {
		// 変数名はm_animfreqだが、値は「周期(period)」であることに注意。周波数(frequency)ではない。
		m_animTime += deltaT;
		while(m_animTime > m_animfreq) { m_animTime -= m_animfreq; }
		float theta = 2.0f * M_PI * m_animTime / (float)m_animfreq;
		float value = (sin(theta) + 1.0f) / 2.0f;

		u32 col = 0;
		int shift = 0;
		for(int i = 0; i < 4; i++) {
			shift = i * 8;
			float a = ((m_animcol[0] >> shift) & 0xff) / 255.0f;
			float b = ((m_animcol[1] >> shift) & 0xff) / 255.0f;
			float c = a + (b - a) * value;
			col |= (0xff & (int)(c * 0xff)) << shift;
		}
		setFilterColor(col);
	}
}

void
CKLBUIProgressBar::setupProgressBarConstant() {
	float p_start   = m_startPixelF;
	float p_end     = m_endPixelF;
	bool  p_vert    = m_isVertical;
	float p_width   = m_fWidth;
	float p_height  = m_fHeight;

	//
	// Setup Index Buffer.
	//
	u16* pBuff = m_pDynSprite->getSrcIndexBuffer();
	memcpy(pBuff, CKLBUIProgressBar::ms_indices, m_indices*sizeof(u16));
	m_pDynSprite->setTexture(m_pTex[0]);

	m_idx_a = (p_start < p_end) ? E_full : E_empty;
	m_idx_b = (p_start < p_end) ? E_empty : E_full;
	m_idx_c = E_filter;

	//
	// Setup Constant UV
	//
	float* verticesUV = m_pDynSprite->getSrcUVBuffer();
	if (!p_vert) {
		// 左端uv
		m_pTex[m_idx_a]->getUV(0, &(verticesUV[0]), &(verticesUV[1]));
		m_pTex[m_idx_a]->getUV(3, &(verticesUV[4]), &(verticesUV[5]));
		// 右端uv
		m_pTex[m_idx_b]->getUV(1, &(verticesUV[10]), &(verticesUV[11]));
		m_pTex[m_idx_b]->getUV(2, &(verticesUV[14]), &(verticesUV[15]));
	} else {
		// 右端uv
		m_pTex[m_idx_b]->getUV(3, &(verticesUV[12]), &(verticesUV[13]));
		m_pTex[m_idx_b]->getUV(2, &(verticesUV[14]), &(verticesUV[15]));
		// 上端uv
		m_pTex[m_idx_a]->getUV(0, &(verticesUV[0]), &(verticesUV[1]));
		m_pTex[m_idx_a]->getUV(1, &(verticesUV[2]), &(verticesUV[3]));
	}

	// フィルタがある場合、フィルタ各頂点のUVを指定する
	// フィルタは分断されず伸縮されるため、すべてのUVを事前に設定してよい。
	if(m_pTex[m_idx_c]) {
		m_pTex[m_idx_c]->getUV(0, &(verticesUV[16]), &(verticesUV[17]));
		m_pTex[m_idx_c]->getUV(1, &(verticesUV[18]), &(verticesUV[19]));
		m_pTex[m_idx_c]->getUV(2, &(verticesUV[22]), &(verticesUV[23]));
		m_pTex[m_idx_c]->getUV(3, &(verticesUV[20]), &(verticesUV[21]));
	}

	//
	// Setup Constant XY
	//
	float* verticesXY = m_pDynSprite->getSrcXYBuffer();
	if (!p_vert) {
		// xy の操作
		// 左パーツ(idx_a)
		verticesXY[0] = 0.0f;
		verticesXY[1] = 0.0f;

		// [2] : Variable
		verticesXY[3] = 0.0f;

		verticesXY[4] = 0.0f;
		verticesXY[5] = p_height;

		// [6] : Variable
		verticesXY[7] = p_height;

		// 右パーツ(idx_b)
		// [8] : Variable
		verticesXY[9] = 0.0f;

		verticesXY[10] = p_width;
		verticesXY[11] = 0.0f;

		// [12] : Variable
		verticesXY[13] = p_height;

		verticesXY[14] = p_width;
		verticesXY[15] = p_height;

		if(m_pTex[m_idx_c]) {
			if(m_idx_a == E_full) {
				m_filterXY[0] = p_start;
				m_filterXY[1] = 0.0f;

				// m_filterXY[2] = 可変
				m_filterXY[3] = 0.0f;

				m_filterXY[4] = p_start;
				m_filterXY[5] = p_height;

				// m_filterXY[6] = 可変
				m_filterXY[7] = p_height;
			} else {
				// m_filterXY[0] = 可変;
				m_filterXY[1] = 0.0f;

				m_filterXY[2] = p_start;
				m_filterXY[3] = 0.0f;

				// m_filterXY[4] = 可変;
				m_filterXY[5] = p_height;

				m_filterXY[6] = p_start;
				m_filterXY[7] = p_height;
			}
		}
	} else {
		// 上パーツ
		verticesXY[0] = 0.0f;
		verticesXY[1] = 0.0f;
		verticesXY[2] = p_width;
		verticesXY[3] = 0.0f;
		verticesXY[4] = 0.0f;
		verticesXY[6] = p_width;


		// 下パーツ
		verticesXY[8] = 0.0f;
		verticesXY[10] = p_width;
		verticesXY[12] = 0.0f;
		verticesXY[13] = p_height;
		verticesXY[14] = p_width;
		verticesXY[15] = p_height;

		if(m_pTex[m_idx_c]) {
			if(m_idx_a == E_full) {
				m_filterXY[0] = 0.0f;
				m_filterXY[1] = p_start;
				m_filterXY[2] = p_width;
				m_filterXY[3] = p_start;

				m_filterXY[4] = 0.0f;
				// m_filterXY[5] = 可変

				m_filterXY[6] = p_width;
				// m_filterXY[7] = 可変
			} else {
				m_filterXY[0] = 0.0f;
				// m_filterXY[1] = 可変

				m_filterXY[2] = p_width;
				// m_filterXY[3] = 可変

				m_filterXY[4] = 0.0f;
				m_filterXY[5] = p_start;
				m_filterXY[6] = p_width;
				m_filterXY[7] = p_start;
			}
		}
	}
}

void
CKLBUIProgressBar::setBorder(float value)
{
	m_lastValue = value;

	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	// 表示プライオリティを設定
	m_pDynSprite->changeOrder(pRdrMgr, getOrder());

	// その他の情報
	bool  p_vert;
	float p_start, p_end, p_border;
	float p_value;
	p_vert 	= getVertical();
	p_start = m_startPixelF;
	p_end   = m_endPixelF;
	p_value = value;

	p_border = p_start + (p_end - p_start) * p_value;
	
	float* verticesUV = m_pDynSprite->getSrcUVBuffer();
	float* verticesXY = m_pDynSprite->getSrcXYBuffer();

	if(!p_vert) {		// 横方向成長
		//
		// Geometry Change
		//
		verticesXY[2]   = p_border;
		verticesXY[6]   = p_border;
		verticesXY[8]   = p_border;
		verticesXY[12]  = p_border;
		if(m_pTex[m_idx_c]) {
			if(m_idx_a == E_full) {
				m_filterXY[2] = p_border;
				m_filterXY[6] = p_border;
			} else {
				m_filterXY[0] = p_border;
				m_filterXY[4] = p_border;
			}
		}

		float rate, u, v;
		rate = p_border / m_fWidth;	// 画像の分割比率

		// 左端uv
		// Constant done at creation.
		// m_pTex[idx_a]->getUV(0, &(verticesUV[0]), &(verticesUV[1]));
		// m_pTex[idx_a]->getUV(3, &(verticesUV[4]), &(verticesUV[5]));

		m_pTex[m_idx_a]->getUV(1, &u, &v);
		verticesUV[2] = verticesUV[0] + (u - verticesUV[0]) * rate;
		verticesUV[3] = verticesUV[1] + (v - verticesUV[1]) * rate;
		m_pTex[m_idx_a]->getUV(2, &u, &v);
		verticesUV[6] = verticesUV[4] + (u - verticesUV[4]) * rate;
		verticesUV[7] = verticesUV[5] + (v - verticesUV[5]) * rate;

		// 右端uv
		// m_pTex[idx_b]->getUV(1, &(verticesUV[10]), &(verticesUV[11]));
		// m_pTex[idx_b]->getUV(2, &(verticesUV[14]), &(verticesUV[15]));

		m_pTex[m_idx_b]->getUV(0, &u, &v);
		verticesUV[8] = u + (verticesUV[10] - u) * rate;
		verticesUV[9] = v + (verticesUV[11] - v) * rate;
		m_pTex[m_idx_b]->getUV(3, &u, &v);
		verticesUV[12] = u + (verticesUV[14] - u) * rate;
		verticesUV[13] = v + (verticesUV[15] - v) * rate;
	} else {			// 縦方向成長
		//
		// Geometry Change
		//
		verticesXY[5]   = p_border;
		verticesXY[7]   = p_border;
		verticesXY[9]   = p_border;
		verticesXY[11]  = p_border;

		if(m_pTex[m_idx_c]) {
			if(m_idx_a == E_full) {
				m_filterXY[5] = p_border;
				m_filterXY[7] = p_border;
			} else {
				m_filterXY[1] = p_border;
				m_filterXY[3] = p_border;
			}
		}

		float rate, u, v;
		rate = p_border / m_fHeight;	// 画像の分割比率

		// 上端uv
		// m_pTex[idx_a]->getUV(0, &(verticesUV[0]), &(verticesUV[1]));
		// m_pTex[idx_a]->getUV(1, &(verticesUV[2]), &(verticesUV[3]));

		m_pTex[m_idx_a]->getUV(3, &u, &v);
		verticesUV[4] = verticesUV[0] + (u - verticesUV[0]) * rate;
		verticesUV[5] = verticesUV[1] + (v - verticesUV[1]) * rate;

		m_pTex[m_idx_a]->getUV(2, &u, &v);
		verticesUV[6] = verticesUV[2] + (u - verticesUV[2]) * rate;
		verticesUV[7] = verticesUV[3] + (v - verticesUV[3]) * rate;

		// 右端uv
		// m_pTex[idx_b]->getUV(3, &(verticesUV[12]), &(verticesUV[13]));
		// m_pTex[idx_b]->getUV(2, &(verticesUV[14]), &(verticesUV[15]));

		m_pTex[m_idx_b]->getUV(0, &u, &v);
		verticesUV[8] = u + (verticesUV[12] - u) * rate;
		verticesUV[9] = v + (verticesUV[13] - v) * rate;

		m_pTex[m_idx_b]->getUV(1, &u, &v);
		verticesUV[10] = u + (verticesUV[14] - u) * rate;
		verticesUV[11] = v + (verticesUV[14] - v) * rate;
	}

	if(m_bFilterSW && m_pTex[m_idx_c]) {
		// filter が指定されていて、なおかつ有効になっていれば頂点情報を反映する
		memcpy(verticesXY + 16, m_filterXY, 8 * sizeof(float));
	}
	m_pDynSprite->mark(CKLBDynSprite::MARK_CHANGE_UV | CKLBDynSprite::MARK_CHANGE_XY);
	m_pNode->markUpMatrix();
}

bool 
CKLBUIProgressBar::setImg(bool isEmpty, const char* imageName)
{
	if(!imageName) { return false; }

	if(CKLBUtility::safe_strcmp(imageName, isEmpty ? m_emptyImage : m_fullImage) != 0) {
		const char * imgname;
		imgname = imageName;

		{
			const char * scheme[] = {
				"asset://",
				"file://install/",
				"file://external/",
				0
			};
			for(int j = 0; scheme[j]; j++) {
				int len = strlen(scheme[j]);
				if(!strncmp(imgname, scheme[j], len)) {
					imgname += len;
					break;
				}
			}
		}

		CKLBImageAsset* image = m_pTexAsset->getImage(imgname);

		if(!image) {
			klb_assertAlways("[%s] is not in the assigned texture.",imgname);
			return false;
		}

		klb_assert(image->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Must use a standard rectangular image in ProgressBar task.");

		if(isEmpty) {
			setStrC(m_emptyImage,imageName);
			m_pTex[1] = image;
		} else {
			setStrC(m_fullImage,imageName);
			m_pTex[0] = image;
		}

		REFRESH_D;
	}

	return true;
}

void
CKLBUIProgressBar::setFilterColor(u32 argb)
{
	u8 v[4];
	v[0] = (argb >> 16);
	v[1] = (argb >>  8);
	v[2] = (argb      );
	v[3] = (argb >> 24);


	// Memory RGBA
	u32 rgba = *((u32*)v);
	for(int i = 8; i < 12; i++) {
		m_pDynSprite->setVertexColor(m_pNode,i, rgba);
	}
	m_FilterCol = argb;
}

void
CKLBUIProgressBar::setFilterVisible(bool visible)
{
	m_bFilterSW = visible;

	// filter を disable したときは、filter用頂点を全て 0.0f にすることで表示されないようにする。
	if(!visible && m_pTex[m_idx_c]) {
		float* verticesXY = m_pDynSprite->getSrcXYBuffer();
		for(int i = 16; i < 24; i++) verticesXY[i] = 0.0f;
	}
}

bool
CKLBUIProgressBar::setFilterAnim(bool bFilterAnim, u32 col1, u32 col2, u32 freq)
{
	m_bColAnim      = bFilterAnim;
	m_animfreq      = freq;
	m_animcol[0]    = col1;
	m_animcol[1]    = col2;
	m_animTime      = 0;

	return true;
}
