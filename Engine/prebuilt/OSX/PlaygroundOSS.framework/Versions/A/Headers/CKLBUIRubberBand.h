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
#ifndef CKLBUIRubberBand_h
#define CKLBUIRubberBand_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIRubberBand
* \brief Rubber Band Task Class
* 
* CKLBUIRubberBand allows to create dynamic Rubber Bands.
*/
class CKLBUIRubberBand : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIRubberBand>;
private:
	CKLBUIRubberBand();
	virtual ~CKLBUIRubberBand();

	bool initCore(	u32 order, float x, float y, u32 resolution, const char* origin, const char* joint, const char* point, u32 flags, u32 animTime,
					int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point);

	bool init(	CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 resolution, const char* origin, const char* joint, const char* point, u32 flags, u32 animTime,
				int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point);
public:
	u32 getClassID();
	static CKLBUIRubberBand* create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 resolution, const char* origin, const char* joint, const char* point, u32 flags, u32 animTime,
									int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point);

	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua);

	void execute(u32 deltaT);
	void dieUI  ();

	inline float getOriginX ()			{ return m_originX;		}
	inline void  setOriginX (float x)	{ m_originX = x;		}

	inline float getOriginY ()			{ return m_originY;		}
	inline void  setOriginY (float y)	{ m_originY = y;		}

	inline void  setPointX  (float x)	{ m_x = x;				}
	inline float getPointX  ()			{ return m_x;			}

	inline void  setPointY  (float y)	{ m_y = y;				}
	inline float getPointY  ()			{ return m_y;			}

	inline void  setFAnim   (bool fAnim){ m_fAnim = fAnim;		}
	inline bool	 getFAnim   ()			{ return m_fAnim;		}

	inline void  setFAnimRT (bool fAnim){ m_fAnimRT = fAnim;	}
	inline bool	 getFAnimRT ()			{ return m_fAnimRT;		}

	inline void  setAnimTime(u32 time)	{ m_animTime = time;	}
	inline u32   getAnimTime()			{ return m_animTime;	}

	inline virtual u32 getOrder         () { return m_order;        }
	inline const char* getAssetOrigin   () { return m_assetOrigin;  }
	inline const char* getAssetJoint    () { return m_assetJoint;   }
	inline const char* getAssetPoint    () { return m_assetPoint;   }

	inline bool setOrder(u32 order_origin, u32 order_joint, u32 order_point) {
		m_pOriginNode->setPriority(order_origin);
		m_pPointNode->setPriority(order_point);
		for(int i = 0; i < m_reso - 1; i++) {
			m_pJointNode[i]->setPriority(order_joint);
		}
		return true;
	}

private:
	u32		    m_order;
	float	    m_originX;
	float	    m_originY;
	float	    m_x;
	float	    m_y;
	const char*	m_assetOrigin;
	const char* m_assetJoint;
	const char* m_assetPoint;

	CKLBNode		*	m_pOriginNode;		// 起点となるスプライト(角度に合わせ回転する)
	CKLBNode		*	m_pPointNode;		// 先端のスプライト(角度に合わせ回転する)
	CKLBNode		**	m_pJointNode;		// 節となるスプライト(回転しない)

	CKLBDynSprite	*	m_sprOrigin;		// 起点用
	CKLBDynSprite	*	m_sprPoint;			// 先端用
	CKLBDynSprite	**	m_sprJoint;			// 節用

	struct POINT {
		float x;
		float y;
	};
	int					m_cntOrigin;
	POINT			*	m_vertOrigin;

	int					m_cntPoint;
	POINT			*	m_vertPoint;

	int					m_cntJoint;
	POINT			*	m_vertJoint;

	u32					m_handle_origin;	// 起点テクスチャのハンドル
	u32					m_handle_point;		// 先端テクスチャのハンドル
	u32					m_handle_joint;		// 節テクスチャのハンドル

	CKLBImageAsset	*	m_img_origin;
	CKLBImageAsset	*	m_img_point;
	CKLBImageAsset	*	m_img_joint;

	bool				m_rot_origin;
	bool				m_rot_joint;
	bool				m_rot_point;

	int					m_reso;				// 分割数

	bool				m_fAnim;			// アニメーションの有無
	bool				m_fAnimRT;			// 時間指定のリアルタイムフラグ(false = フレーム指定)
	u32					m_animTime;			// アニメーション時間(1ループ)
	u32					m_animCount;		// 経過時間カウント


	POINT				m_origin;
	POINT				m_point;

	static	PROP_V2		ms_propItems[];
	static float		ms_norot_mat[4];
private:
	CKLBDynSprite * create_rotSprite(CKLBNode * node, u32 order, CKLBImageAsset * asset,
									 int * vertCnt, POINT ** arrVert);
	void rot_vertex(CKLBDynSprite * dynSpr, CKLBImageAsset * pAsset, int cntVert, POINT * pbuf, float * mat);
};

#endif // CKLBUIRubberBand_h
