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
#include "CKLBUITask.h"
#include "CKLBDrawTask.h"

//
// すべてのUIタスクが持つプロパティのリスト
// Note : keep the order because of CKLBFormIF.cpp::updateStandardNode(...)
//
const char	*	CKLBUITask::ms_propList[] = {
	"alpha",	// Keep COLOR after ALPHA !
	"color",
	"scaleX",	// Keep SCALEY after SCALEX !
	"scaleY",
	"rot",
	"x",		// Keep Y after X
	"y",
	"visible",
	0
};

CKLBUITask::CKLBUITask(TASK_PHASE phase)
: CKLBLuaPropTask()
, m_phase       (phase)
, m_initX       (0.0f)
, m_initY       (0.0f)
, m_pRegParent  (NULL)
, m_visible     (true)
{
}

CKLBUITask::~CKLBUITask() 
{
}

CKLBTask::TASKTYPE
CKLBUITask::getTaskType()
{
    return TASK_LUA_UI;
}

bool
CKLBUITask::setupNode()
{
	m_pUINode = KLBNEW(CKLBSplineNode);
    if(!m_pUINode) { return false; }
	m_pUINode->setUITask(this);
	m_pUINode->resetAsInternalNode();
	m_pUINode->setName("CKLBUITask Node");
	return true;
}

bool
CKLBUITask::registUI(CKLBUITask * pParent, bool result, CKLBTask * pRegParent)
{
	// UIタスクの親が pParentで指定されている場合、別の非UIタスクを pRegParent に指定することはできない。
	// pParent が 0 の場合、pRegParent が 0 でなければそちらが親タスクとして使用される。
	klb_assert((pParent && !pRegParent) || (!pParent), "double parent assign.");

	if(!result) {
		KLBDELETE(m_pUINode);
		return false;
	}

	// UIタスクすべてが持つべきプロパティを追加する。
	if (!m_newScriptModel) {
		m_beginIndex = getPropertyCount();
		if(!addPropertyList(ms_propList)) {
			KLBDELETE(m_pUINode);
			return false;
		}
		// デフォルト値を設定しておく
		setInt(PRG_ALPHA    + m_beginIndex, 0xff);
		setInt(PRG_COLOR    + m_beginIndex, 0x00ffffff);
		setNum(PRG_SCALE_X  + m_beginIndex, 1.0f);
		setNum(PRG_SCALE_Y  + m_beginIndex, 1.0f);
		setNum(PRG_ROT      + m_beginIndex, 0.0f);
		setNum(PRG_X        + m_beginIndex, m_initX);
		setNum(PRG_Y        + m_beginIndex, m_initY);
		setBool(PRG_VISIBLE + m_beginIndex, true);
	} else {
		m_beginIndex = 0;
		// デフォルト値を設定しておく
		m_alpha = 0xff;
		m_color = 0x00ffffff;
		setVisible(m_visible);
	}

	// 初期化が成功し、なおかつ親UIがある場合、親UIのノードに自身のノードを追加する。
	if (pParent && (pParent->getClassID() & CLS_NONVISUALTASK)) {
		pParent = NULL;
	}

	if(pParent) {
		pParent->getNode()->addNode(m_pUINode);
	} else {
		// 親タスクが指定されていない場合は、Root直下につなぐ。
		CKLBDrawResource& res = CKLBDrawResource::getInstance();
		res.getRoot()->addNode(m_pUINode);
	}

	if (!m_newScriptModel) {
		// 親が決まったのでプロパティ値を反映させる
		setGenericProperty();	// プロパティ値を反映させる
	} else {
		setColor(m_color);
		setAlpha(m_alpha);
		// m_pUINode->setVisible(true);
		m_pUINode->setTranslate(m_initX, m_initY);
		m_pUINode->markUpMatrix();
	}
	m_bInnerUpdate = false;

	// UIタスク以外の親を指定する場合、pParent == 0 かつ pRegParent != 0 となっている。
	CKLBTask * pFinalParent = (pParent) ? pParent : pRegParent;

	// 親UIタスクの子として自身を登録し、初期化終了。
	bool bResult = regist(pFinalParent, m_phase);
    if(!bResult) {
        KLBDELETE(m_pUINode);
    }
    return bResult;
}

bool
CKLBUITask::initScript(CLuaState& lua)
{
	// 最低一つはパラメータが必要(親タスクのポインタあるいは0)
    if(lua.numArgs() < 1) { return false; }
	CKLBUITask * pParent = (lua.isNil(1)) ? NULL : (CKLBUITask *)lua.getPointer(1);

    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initUI(lua);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	return registUI(pParent, bResult, m_pRegParent);
}

void
CKLBUITask::die()
{
	dieUI();
	KLBDELETE(m_pUINode);
}

void CKLBUITask::setColor(u32 color) {
	m_color = (color & 0x00ffffff);
	
	SColorVector cvec;
	cvec.m_type = 0;
	cvec.m_vector[0] = (float)((color >> 16) & 0xff) / 255.0f;
	cvec.m_vector[1] = (float)((color >> 8 ) & 0xff) / 255.0f;
	cvec.m_vector[2] = (float)((color >> 0 ) & 0xff) / 255.0f;
	cvec.m_vector[3] = (float)m_alpha / 255.0f;

	m_pUINode->setColorMatrix(cvec);
}

u32 CKLBUITask::getColor() {
	u32 r = (u32)(m_pUINode->m_localColorMatrix.m_vector[0] * 255.0);
	u32 g = (u32)(m_pUINode->m_localColorMatrix.m_vector[1] * 255.0);
	u32 b = (u32)(m_pUINode->m_localColorMatrix.m_vector[2] * 255.0);
	return (r<<16) | (g<<8) | b;
}

void CKLBUITask::setAlpha(u32 alpha) {
	m_alpha = (alpha & 0xff);
	SColorVector cvec;
	cvec.m_type = 0;
	cvec.m_vector[0] = (float)((m_color >> 16) & 0xff) / 255.0f;
	cvec.m_vector[1] = (float)((m_color >> 8 ) & 0xff) / 255.0f;
	cvec.m_vector[2] = (float)((m_color >> 0 ) & 0xff) / 255.0f;
	cvec.m_vector[3] = (float)m_alpha / 255.0f;

	m_pUINode->setColorMatrix(cvec);
}

u32 CKLBUITask::getAlpha() {
	return (u32)(m_pUINode->m_localColorMatrix.m_vector[3] * 255.0);
}

bool CKLBUITask::reconnect(const char* nodeName) {
	// まず、自身に親がいるか否かを調べる。
	// 親がいなければエラー、親がUIタスクでなくてもエラー。
	CKLBTask * pParent = getParent();
	if (!pParent || pParent->getTaskType() != TASK_LUA_UI) {
		return false;
	}

	// UIタスクの親がいるなら、その親の持つノードから名前で検索する
	CKLBUITask * pUIParent  = (CKLBUITask *)pParent;
	CKLBNode * pParentNode  = pUIParent->getNode();
	CKLBNode * pMyBaseNode  = this->getNode();
	CKLBNode * pNode        = pParentNode->search(nodeName);

	// 該当するノードが見つからなければエラー
	if (!pNode) {
		return false;
	}

	// 該当するノードが見つかったので、接続を付け替える。
	pParentNode->removeNode(pMyBaseNode);
	pNode->addNode(pMyBaseNode);

	return true;
}

bool
CKLBUITask::updateUIProperty()
{
	klb_assert(!m_newScriptModel, "Never called by new scripting model");

	bool bAnim = m_pUINode->isAnimating();
	if(bAnim) {
		// アニメーション中なので、
		// アニメーションによって変動するパラメータをプロパティに反映する
		float rot = m_pUINode->getRotation();
		float scaleX = m_pUINode->getScaleX();
		float scaleY = m_pUINode->getScaleY();
		// 座標情報
		float x = m_pUINode->m_matrix.m_matrix[MAT_TX];
		float y = m_pUINode->m_matrix.m_matrix[MAT_TX];
		// 色情報
		SColorVector &vec = m_pUINode->m_localColorMatrix;
		u32 color = 0;
		u32 alpha =  (u32)(vec.m_vector[3] * 255.0);
		for(int i = 0; i < 3; i++) {
			color |= (u32)(vec.m_vector[i] * 255.0) << (i * 8);
		}		
		setNum(PRG_X        + m_beginIndex, x);
		setNum(PRG_Y        + m_beginIndex, y);
		setNum(PRG_SCALE_X  + m_beginIndex, scaleX);
		setNum(PRG_SCALE_Y  + m_beginIndex, scaleY);
		setNum(PRG_ROT      + m_beginIndex, rot);
		setNum(PRG_COLOR    + m_beginIndex, color);
		setNum(PRG_ALPHA    + m_beginIndex, alpha);
	}
	// その上で操作されたプロパティがある場合は、その値で上書きする。
	// (アニメーション中はあまり意味がないとは思われる)
	if(!getUpdateFlag() && !m_bInnerUpdate) return false;
	m_bInnerUpdate = false;
	return setGenericProperty();
}

bool
CKLBUITask::setGenericProperty()
{
	klb_assert(!m_newScriptModel, "Never called by new scripting model");

	u32 alpha = getInt(PRG_ALPHA + m_beginIndex);
	u32 color = getInt(PRG_COLOR + m_beginIndex);
	float scaleX = getNum(PRG_SCALE_X + m_beginIndex);
	float scaleY = getNum(PRG_SCALE_Y + m_beginIndex);
	float x      = getNum(PRG_X       + m_beginIndex);
	float y      = getNum(PRG_Y       + m_beginIndex);
	float rot    = getNum(PRG_ROT     + m_beginIndex);

	SColorVector cvec;
	cvec.m_type = 0;
	for(int i = 0; i < 3; i++) {
		int col = 0xff & (color >> (16 - 8 * i));
		cvec.m_vector[i] = (float)(col) / 255.0f;
	}
	cvec.m_vector[3] = (float)alpha / 255.0f;
	bool visible = getBool(PRG_VISIBLE + m_beginIndex);
	m_pUINode->setColorMatrix(cvec);
	m_pUINode->setScale(scaleX, scaleY);
	m_pUINode->setTranslate(x, y);
	m_pUINode->setVisible(visible);
	m_pUINode->setRotation(rot);

	return true;
}

int
CKLBUITask::commandUI(CLuaState& lua, int /*argc*/, int /*cmd*/)
{
	lua.retBoolean(false);
	return 1;
}

int
CKLBUITask::commandScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBoolean(false);
		return 1;
	}
	int cmd = lua.getInt(2);
	int ret = 0;
	switch(cmd)
	{
	default:
		ret = commandUI(lua, argc, cmd);
		break;
	case UI_GENERIC_NODE_RECONNECT:
		{
			// 親タスクの持つ基点ノードから名前による検索を行い、
			// 見つかれば自身を接続するノードを、親タスクの起点ノードからそのノードに切り替える。
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			// まず、自身に親がいるか否かを調べる。
			// 親がいなければエラー、親がUIタスクでなくてもエラー。
			CKLBTask * pParent = getParent();
			if(!pParent || pParent->getTaskType() != TASK_LUA_UI) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			// UIタスクの親がいるなら、その親の持つノードから名前で検索する
			CKLBUITask * pUIParent = (CKLBUITask *)pParent;
			const char * node_name = lua.getString(3);
			CKLBNode * pParentNode = pUIParent->getNode();
			CKLBNode * pMyBaseNode = this->getNode();
			CKLBNode * pNode = pParentNode->search(node_name);

			// 該当するノードが見つからなければエラー
			if(!pNode) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			// 該当するノードが見つかったので、接続を付け替える。
			pParentNode->removeNode(pMyBaseNode);
			pNode->addNode(pMyBaseNode);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_GENERIC_SET_NAME:
		{
			bool bResult = false;
			if(argc == 3) {
				CKLBNode * pNode = getNode();
				if(!pNode->getName()) {
					const char * name = lua.getString(3);
					bResult = pNode->setName(name);
				}
			}
			lua.retBoolean(bResult);
			ret = 1;
		}
		break;
	case UI_GENERIC_ANIM_SET_SPLINE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			bool result = setSplineAnim(lua, 3);
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_ANIM_PLAY:
		{
			bool result = false;
			if(argc == 2) {
				m_pUINode->play();
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_ANIM_STOP:
		{
			bool result = false;
			if(argc == 2) {
				m_pUINode->stop();
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_IS_ANIM:
		{
			bool result = false;
			if(argc == 2) {
				result = m_pUINode->isAnimating();
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_SET_COLOR:
		{
			bool result = false;
			if(argc == 4) {
				u32 alpha = lua.getInt(3);
				u32 rgb = lua.getInt(4);
				if (!m_newScriptModel) {
					setInt(PRG_ALPHA + m_beginIndex, alpha);
					setInt(PRG_COLOR + m_beginIndex, rgb);
				}
				setAlpha(alpha);
				setColor(rgb);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_SET_SCALE:
		{
			bool result = false;
			if(argc == 4) {
				float scaleX = lua.getFloat(3);
				float scaleY = lua.getFloat(4);
				if (!m_newScriptModel) {
					setNum(PRG_SCALE_X + m_beginIndex, scaleX);
					setNum(PRG_SCALE_Y + m_beginIndex, scaleY);
				}
				setScaleX(scaleX);
				setScaleY(scaleY);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_SET_ROT:
		{
			bool result = false;
			if(argc == 3) {
				float rot = lua.getFloat(3);
				if (!m_newScriptModel) {
					setNum(PRG_ROT + m_beginIndex, rot);
				}
				setRotation(rot);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GENERIC_SET_VISIBLE:
		{
			bool result = false;
			if(argc == 3) {
				bool visible = lua.getBool(3);
				if (!m_newScriptModel) {
					setBool(PRG_VISIBLE + m_beginIndex, visible);
				}
				setVisible(visible);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}

bool
CKLBUITask::setSplineAnim(CLuaState& lua, int pos)
{
	bool result = true;

	m_pUINode->stop();
	// path-1: spline数と、最大のkey数を得る。
	int spline = 0;
	int max_key_count = 0;
	lua.retValue(pos);
	lua.retNil();
	while(lua.tableNext()) {
		spline++;	// スプライン数
		int num = getSplineKeyCount(lua, -1);
        if(num > max_key_count) { max_key_count = num; }
		lua.pop(1);
	}

	// node にスプライン数、最大キー数を登録する
	m_pUINode->setParamCount(spline, max_key_count);

	// path-2: splineを登録する
	int spline_index = 0;
	lua.retNil();
	while(lua.tableNext()) {
		// スタックのトップにメンバのテーブルが積まれている。
		// これは一つのターゲット分に相当する。
		result &= setSplineAnimTarget(lua, -1, spline_index, max_key_count);
		spline_index++;
		lua.pop(1);
	}
	lua.pop(1);

	m_pUINode->generateAnimation();

	return result;
}

int
CKLBUITask::getSplineKeyCount(CLuaState& lua, int /*pos*/)
{
	int count = 0;

	lua.retString("keys");
	lua.tableGet();

	lua.retNil();
	while(lua.tableNext()) {
		count++;
		lua.pop(1);
	}
	lua.pop(1);
	return count;
}

bool
CKLBUITask::setSplineAnimTarget(CLuaState& lua, int /*pos*/, int spline_index, int max_key_count)
{
	bool result = true;

	// target を取得
	lua.retString("target");
	lua.tableGet();
	u32 target = lua.getInt(-1);
	lua.pop(1);

	// ターゲットを設定
	m_pUINode->setTarget(spline_index, target);

	// 値のモードを取得。無ければ SPL_VALUE_INT と同じ動作。
	lua.retString("mode");
	lua.tableGet();
	u32 mode = (lua.isNil(-1)) ? SPL_VALUE_INT : lua.getInt(-1);
	lua.pop(1);

	// spline のキーを登録する。
	lua.retString("keys");
	lua.tableGet();
	for(int i = 1; i <= max_key_count; i++) {
		lua.retInt(i);	// 数値indexをスタックに積む
		lua.tableGet();
		if(lua.isNil(-1)) {
			lua.pop(1);
			break;
		}

		// key テーブルの1要素となるテーブルがスタックトップにある
		lua.retInt(1);
		lua.tableGet();
		u32 v_time = lua.getInt(-1);
		lua.pop(1);

		lua.retInt(2);
		lua.tableGet();
		if(mode == SPL_VALUE_INT) {
			s16 value = lua.getInt(-1); 
			m_pUINode->addKeys(spline_index, v_time, value);
		} else {
			double f_value = lua.getFloat(-1);
			s32 value = (s32)(f_value * 65536.0);	// fixed
			m_pUINode->addKeysFixed(spline_index, v_time, value);
		}
		lua.pop(2);
	}
	lua.pop(1);

	return result;
}
