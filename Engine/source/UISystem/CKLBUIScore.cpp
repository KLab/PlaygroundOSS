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
#include "CKLBUIScore.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"

// Command Values
enum {
	UI_SCORE_RESET = 0,
	UI_SCORE_SET,
	UI_SCORE_SETFLOAT,
	UI_SCORE_SETDOT,
	UI_SCORE_GET,
	UI_SCORE_ENTERANIM,
	UI_SCORE_EXITANIM,
	UI_SCORE_ALIGN,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_SCORE_RESET",     UI_SCORE_RESET      },
	{ "UI_SCORE_SET",       UI_SCORE_SET        },
	{ "UI_SCORE_GET",       UI_SCORE_GET        },
	{ "UI_SCORE_ENTERANIM", UI_SCORE_ENTERANIM  },
	{ "UI_SCORE_EXITANIM",  UI_SCORE_EXITANIM   },
	{ "UI_SCORE_ALIGN",     UI_SCORE_ALIGN      },
	{ "UI_SCORE_SETFLOAT",	UI_SCORE_SETFLOAT },
	{ "UI_SCORE_DOT",		UI_SCORE_SETDOT },

	{ "SCORE_ALIGN_RIGHT",	CKLBUIScore::ALIGN_RIGHT    },
	{ "SCORE_ALIGN_CENTER",	CKLBUIScore::ALIGN_CENTER   },
	{ "SCORE_ALIGN_LEFT",	CKLBUIScore::ALIGN_LEFT     },

	{ "ANM_X_COORD_0",          CKLBSplineNode::ANM_X_COORD_0       },
	{ "ANM_Y_COORD_1",          CKLBSplineNode::ANM_Y_COORD_1       },
	{ "ANM_SCALE_COORD_2",      CKLBSplineNode::ANM_SCALE_COORD_2   },
	{ "ANM_R_COLOR_3",          CKLBSplineNode::ANM_R_COLOR_3       },
	{ "ANM_G_COLOR_4",          CKLBSplineNode::ANM_G_COLOR_4       },
	{ "ANM_B_COLOR_5",          CKLBSplineNode::ANM_B_COLOR_5       },
	{ "ANM_A_COLOR_6",          CKLBSplineNode::ANM_A_COLOR_6       },
	{ "ANM_SCALEX_COORD_7",     CKLBSplineNode::ANM_SCALEX_COORD_7  },
	{ "ANM_SCALEY_COORD_8",     CKLBSplineNode::ANM_SCALEY_COORD_8  },
	{ "ANM_ROTATION_COORD_9",   CKLBSplineNode::ANM_ROTATION_COORD_9},

	{ "ANM_TYPE_LINEAR",        CKLBSplineNode::ANM_LINEAR          },
	{ "ANM_TYPE_SWING",         CKLBSplineNode::ANM_SWING           },
	{ "ANM_TYPE_EASEINQUAD",    CKLBSplineNode::ANM_EASEINQUAD      },
	{ "ANM_TYPE_EASEOUTQUAD",   CKLBSplineNode::ANM_EASEOUTQUAD     },
	{ "ANM_TYPE_EASEINOUTQUAD", CKLBSplineNode::ANM_EASEINOUTQUAD   },
	{ "ANM_TYPE_EASEINCUBIC",   CKLBSplineNode::ANM_EASEINCUBIC     },
	{ "ANM_TYPE_EASEOUTCUBIC",  CKLBSplineNode::ANM_EASEOUTCUBIC    },
	{ "ANM_TYPE_EASEINOUTCUBIC",CKLBSplineNode::ANM_EASEINOUTCUBIC  },
	{ "ANM_TYPE_EASEINQUART",   CKLBSplineNode::ANM_EASEINQUART     },
	{ "ANM_TYPE_EASEINBACK",    CKLBSplineNode::ANM_EASEINBACK      },
	{ "ANM_TYPE_EASEOUTBACK",   CKLBSplineNode::ANM_EASEOUTBACK     },
	{ "ANM_TYPE_EASEINOUTBACK", CKLBSplineNode::ANM_EASEINOUTBACK   },

	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIScore> factory("UI_Score", CLS_KLBUISCORE, cmd);

CKLBUIScore::CKLBUIScore()
: CKLBUITask    ()
, m_pScoreNode  (NULL)
{
	setNotAlwaysActive();
	for (int n=0; n<10; n++) {
		m_asset[n] = NULL;
	}
	m_newScriptModel = true;
}

CKLBUIScore::~CKLBUIScore() {
	for (int n = 0; n<10; n++) {
		KLBDELETEA(m_asset[n]);
	}
}

u32
CKLBUIScore::getClassID()
{
	return CLS_KLBUISCORE;
}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIScore::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUIScore::setOrder,		(getBoolT)&CKLBUIScore::getOrder,		0	},
	{	"odoff",	R_UINTEGER,	NULL,									(getBoolT)&CKLBUIScore::getOrderOffset,	0	},
	{	"stepX",	INTEGER,	(setBoolT)&CKLBUIScore::setStepX,		(getBoolT)&CKLBUIScore::getStepX,		0	},
	{	"stepY",	INTEGER,	(setBoolT)&CKLBUIScore::setStepY,		(getBoolT)&CKLBUIScore::getStepY,		0	},
	{	"cols",		UINTEGER,	(setBoolT)&CKLBUIScore::setColumn,		(getBoolT)&CKLBUIScore::getColumn,		0	},
	{	"fillz",	BOOLEANT,	(setBoolT)&CKLBUIScore::setFillZero,	(getBoolT)&CKLBUIScore::getFillZero,	0	},
	{	"anim",		R_BOOLEANT,	NULL,									(getBoolT)&CKLBUIScore::getAnim,		0	},
	{	"value",	UINTEGER,	(setBoolT)&CKLBUIScore::setValue,		(getBoolT)&CKLBUIScore::getValue,		0	},
	{	"align",	UINTEGER,	(setBoolT)&CKLBUIScore::setAlign,		(getBoolT)&CKLBUIScore::getAlign,		0	},
	{	"countclip",BOOLEANT,	(setBoolT)&CKLBUIScore::setCountClip,	(getBoolT)&CKLBUIScore::getCountClip,	0	},

	{	"tex0",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex0,		0	},
	{	"tex1",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex1,		0	},
	{	"tex2",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex2,		0	},
	{	"tex3",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex3,		0	},
	{	"tex4",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex4,		0	},
	{	"tex5",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex5,		0	},
	{	"tex6",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex6,		0	},
	{	"tex7",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex7,		0	},
	{	"tex8",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex8,		0	},
	{	"tex9",		R_STRING,	NULL,									(getBoolT)&CKLBUIScore::getTex9,		0	}
};

enum {
	ARG_PARENT = 1,
	ARG_ORDER,
	ARG_ODOFF,

	ARG_X,
	ARG_Y,
	ARG_TEXTBL,
	ARG_STEP_X,
	ARG_STEP_Y,
	ARG_COLS,
	ARG_FILLZERO,
	ARG_ANIM,
	ARG_ALIGN,
	ARG_COUNTCLIP,

	ARG_REQUIRE = ARG_ANIM,
	ARG_NUMS = ARG_COUNTCLIP
};

CKLBUIScore *
CKLBUIScore::create(CKLBUITask * pParent, CKLBNode * pNode,
					u32 order, s32 order_offset, float x, float y, 
					const char ** tex_table, float stepX, float stepY, int column, 
					bool fillzero, bool anim_flags, u32 align, bool countclip)
{
	CKLBUIScore * pTask = KLBNEW(CKLBUIScore);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, order, order_offset, x, y, tex_table, stepX, stepY, column, fillzero, anim_flags, align, countclip)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIScore::init(CKLBUITask * pParent, CKLBNode * pNode,
                  u32 order, s32 order_offset, float x, float y, 
                  const char ** tex_table, float stepX, float stepY, int column, 
                  bool fillzero, bool anim_flag, u32 align, bool countclip)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, order_offset, x, y, tex_table, stepX, stepY, column, fillzero, anim_flag, align, countclip);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIScore::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

	// 引数の数が合わない場合
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	float   x            = lua.getFloat(ARG_X);
	float   y            = lua.getFloat(ARG_Y);
	u32     order        = lua.getInt(ARG_ORDER);
	s32     order_offset = lua.getInt(ARG_ODOFF);
	float   stepX        = lua.getFloat(ARG_STEP_X);
	float   stepY        = lua.getFloat(ARG_STEP_Y);
	int     column       = lua.getInt(ARG_COLS);
	bool    fillzero     = lua.getBool(ARG_FILLZERO);
	bool    anim_flag    = lua.getBool(ARG_ANIM);
	int     align        = (argc >= ARG_ALIGN)     ? lua.getInt(ARG_ALIGN)      : ALIGN_RIGHT;
	bool    countclip    = (argc >= ARG_COUNTCLIP) ? lua.getBool(ARG_COUNTCLIP) : false;

	const char * tex_list[10];
	lua.retValue(ARG_TEXTBL);	// 対象となる配列をスタックトップに積む
	lua.retNil();				// nil をスタックトップに積む
	int tex_cnt = 0;
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1) - 1;			// Lua配列の添え字は1からなので、-1する。
		const char * str = lua.getString(-1);

		// 与えられた配列のindexに整数以外が使われているときや、
		// 範囲を超えたものがある場合はエラー扱いとする。
		klb_assert((idx >= 0 && idx <= 9), "BAD INDEX [%s] in texture array.", str);
		if(idx < 0 || idx > 9) {	// 数値以外のインデックスが指定されていたり、範囲を超えている場合
			return false;
		}
		const char * texname = lua.getString(-2);	// テクスチャ名称が格納されている。
		tex_list[idx] = texname;
		tex_cnt++;
		lua.pop(2);
	}
	lua.pop(1);
	// テクスチャの数が足りなければエラーとする。
	if(tex_cnt != 10) {
		klb_assert(tex_cnt == 10, "%s(%d): The number of textures is insufficient. ", lua.getScriptName(), lua.getNumLine()); 
		return false;
	}

	return initCore(order, order_offset, x, y, tex_list, stepX, stepY, column, fillzero, anim_flag, align, countclip);
}

bool
CKLBUIScore::initCore(u32 order, s32 order_offset, float x, float y, 
                      const char ** tex_table, float stepX, float stepY, int column, 
                      bool fillzero, bool anim_flag, u32 align, bool countclip)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);
	m_order         = order;
	m_orderOffset   = order_offset;
	m_stepX         = (int)stepX;
	m_stepY         = (int)stepY;
	m_column        = column;
	m_bFillZero     = fillzero;
	m_anim          = anim_flag;
	m_align         = align;
	m_bCountClip    = countclip;
	m_dotStepX		= 0;
	m_dotStepY		= 0;
	m_value         = 0xFFFFFFFF;
	m_fValue        = -12345678.0f;
	setValue(0);
	setValueFloat(0.0f, 0);
	RESET_B;	// Reset flag done by setValueFloat.


	// align設定用の幅を計算
	m_width  = stepX * column;
	m_height = stepY * column;

	// 保持できる最大値+1を計算
	m_maxvalue = 1;
    for(int i = 0; i < column; i++) { m_maxvalue = m_maxvalue * 10; }

	for(int idx = 0; idx < 10; idx++) {
		setStrC(m_asset[idx], tex_table[idx]);
	}

	CKLBTextureAsset * pTexAsset;
	pTexAsset = (CKLBTextureAsset *)CKLBUtility::loadAssetScript( m_asset[0], &m_handle, NULL, true);

	const char * texname[10];
	for(int i = 0; i < 10; i++) {
		texname[i] = m_asset[i] + 8;
	}

	m_pScoreNode = KLBNEW(CKLBScoreNode);
    if(!m_pScoreNode) {
		CKLBDataHandler::releaseHandle(m_handle);
        return false;
    }
    
    for(int i = 0; i < 10; i++) {
        m_numTex[i] = pTexAsset->getImage(texname[i]);
        if(m_numTex[i] == 0) {
			CKLBScriptEnv::getInstance().error("TEXB differs from [%s] by [%s].", texname[0], texname[i]);
			CKLBDataHandler::releaseHandle(m_handle);
			return false;
		}
    }

    bool bResult = m_pScoreNode->init(	order,
			                            order_offset,
			                            m_numTex,
			                            m_stepX,
										m_stepY,
										column,
										fillzero,
									    anim_flag);
    
    getNode()->addNode(m_pScoreNode, 0);
	m_pScoreNode->markUpMatrix();
	m_bScoreUpdate = true;

	if(!bResult) CKLBDataHandler::releaseHandle(m_handle);

	return bResult;
}

void
CKLBUIScore::execute(u32 deltaT)
{
	deltaT = deltaT; // Avoid Warning

	bool useFloat = CHANGE_B;
	s32 fDot = 0;
	int column;
	if (useFloat) {
		m_pScoreNode->setScoreFloat(m_fValue, m_fPrec, true);
		if (!m_bFillZero) {
			column = countColumn(m_pScoreNode->getScore());
			fDot = 1;
		}
	} else {
		int value = m_value;
		if(m_bCountClip && value >= m_maxvalue) value = m_maxvalue - 1;
		m_pScoreNode->setScore(value, true);
		column = countColumn(value);	// 桁数をカウント
	}
	m_pScoreNode->setPriority(m_order);
	m_pScoreNode->update();

	if(!m_bFillZero) {
		int offX;
		int offY;
		int stepX = m_stepX;
		int stepY = m_stepY;
		int max_cols = m_column;
		int dotStepX = (m_dotStepX * fDot);
		int dotStepY = (m_dotStepY * fDot);
        if(column > max_cols) { column = max_cols; }
		switch(m_align)
		{
		default:
		case ALIGN_RIGHT:
			offX = 0;
			offY = 0;
			break;
		case ALIGN_CENTER:
			offX = ((m_width  - stepX * column) + dotStepX) / 2;
			offY = ((m_height - stepY * column) + dotStepY) / 2;
			break;
		case ALIGN_LEFT:
			offX = (m_width  - (stepX * column)) + dotStepX;
			offY = (m_height - (stepY * column)) + dotStepY;
			break;
		}
		m_pScoreNode->setTranslate(-offX, -offY);
	}
	RESET_A;
	RESET_B;
}

void
CKLBUIScore::dieUI()
{
	CKLBUtility::deleteNode(m_pScoreNode, m_handle);
}

// 表示の必要がある桁数を数える
int
CKLBUIScore::countColumn(u32 value)
{
	int cnt = 0;
	do {
		cnt++;
		value = (value - (value % 10)) / 10;
	} while(value > 0);
	return cnt;
}

void CKLBUIScore::setDot(const char* dotAsset, s32 width, s32 height) {
	CKLBTextureAsset * pAsset		= m_numTex[0]->getTexture();

	u32 handle = 0;
	CKLBTextureAsset * pTexAsset	= (CKLBTextureAsset *)CKLBUtility::loadAssetScript( dotAsset, &handle, 0, true);
	if (pAsset != pTexAsset) {
		CKLBScriptEnv::getInstance().error("DOT image %s not inside same texture as score 0..9 graphics.", dotAsset);
	}

	if (handle) {
		// Release double lock
		CKLBDataHandler::releaseHandle(handle);
	}

	CKLBImageAsset* pImgAsset = pAsset->getImage(dotAsset + 8); // Skip asset://

	m_dotStepX = width;
	m_dotStepY = height;

	// Assign ressource
	m_pScoreNode->setDot(pImgAsset,width,height);
}

const char* CKLBUIScore::getDot() {
	return NULL; // TODO
}

int
CKLBUIScore::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	case UI_SCORE_RESET:
		setValue(0);
		m_bScoreUpdate = true;
		break;
	case UI_SCORE_SET:
		{
			if(argc != 3) {
				lua.retNil();
				ret = 1;
				break;
			}
			int value = lua.getInt(3);
			if(m_bCountClip && value >= m_maxvalue) value = m_maxvalue - 1;
			setValue(value);
		}
		break;
	case UI_SCORE_SETFLOAT:
		{
			if(argc != 4) {
				lua.retNil();
				ret = 1;
				break;
			}
			float value = lua.getFloat(3);
			int pos = lua.getInt(4);
			if(m_bCountClip && value >= m_maxvalue) value = m_maxvalue - 1;
			setValueFloat(value, pos);
		}
		break;
	case UI_SCORE_SETDOT:
		{
			if(argc != 5) {
				lua.retNil();
				ret = 1;
				break;
			}

			setDot(lua.getString(3), lua.getInt(4), lua.getInt(5));
		}
		break;
	case UI_SCORE_GET:
		{	
			int value = getValue();
			lua.retInt(value);
			ret = 1;
		}
		break;
	case UI_SCORE_ENTERANIM:
		{
			if(argc != 8) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			s32  mspt       = lua.getInt(3);
			s32  tshift     = lua.getInt(4);
			bool onlychg    = lua.getBool(5);
			int  type       = lua.getInt(6);
			u32  affected   = lua.getInt(7);
			float mat[8];
			klb_assert(type > 0, "UI_Score: UI_SCORE_ENTERANIM type == 0");

			// 配列を読む
			lua.retValue(8);
			lua.retNil();
			while(lua.tableNext()) {
				lua.retValue(-2);
				int idx = lua.getInt(-1) - 1;
				klb_assert((idx >= 0 && idx < 8), "%s(%d): bad array index. UI_SCORE_ENTERANIM", lua.getScriptName(), lua.getNumLine());
				mat[idx] = lua.getFloat(-2);
				lua.pop(2);
			}
			lua.pop(1);

			klb_assert(type != 0, "Custom animation is not authorized (type 0)");
			m_pScoreNode->setEnterAnimation(mspt, tshift, onlychg, type, affected, mat);
		}
		break;
	case UI_SCORE_EXITANIM:
		{
			if(argc != 8) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			s32  mspt       = lua.getInt(3);
			s32  tshift     = lua.getInt(4);
			bool onlychg    = lua.getBool(5);
			int  type       = lua.getInt(6);
			u32  affected   = lua.getInt(7);
			float mat[4];
			klb_assert(type > 0, "UI_Score: UI_SCORE_ENTERANIM type == 0");

			// 配列を読む
			lua.retValue(8);
			lua.retNil();
			while(lua.tableNext()) {
				lua.retValue(-2);
				int idx = lua.getInt(-1) - 1;
				mat[idx] = lua.getFloat(-2);
				lua.pop(2);
			}
			lua.pop(1);

			klb_assert(type != 0, "Custom animation is not authorized (type 0)");
			m_pScoreNode->setExitAnimation(mspt, tshift, onlychg, type, affected, mat);
		}
		break;
	case UI_SCORE_ALIGN:
		{
			bool bResult = false;
			if(argc == 3) {
				int align = lua.getInt(3);
				setAlign(align);
				bResult = true;
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	}
	return ret;
}
