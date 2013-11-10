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
#ifndef CKLBUISWFPlayer_h
#define CKLBUISWFPlayer_h

#include "CKLBUITask.h"
#include "CKLBSWFPlayer.h"

/*!
* \class CKLBUISWFPlayer
* \brief SWF Player Task Class
* 
* CKLBUISWFPlayer is a Flash Player that can read and display our SWFAssets.
*/
class CKLBUISWFPlayer : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUISWFPlayer>;
protected:
	CKLBUISWFPlayer();
	virtual ~CKLBUISWFPlayer();
public:
	static CKLBUISWFPlayer * create(CKLBUITask * pParent, CKLBNode * pNode,
						            u32 order, float x, float y, const char * asset,
						            const char * movie_name, const char * complete_callback,
						            const char ** replace_list, int asset_cnt);

	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

    u32 getClassID();

	inline bool getPlay() { return m_play; }
    inline void setPlay(bool play) {
		if (m_play != play) {
			m_play = play;
			m_pSWFNode->setPlay(play);
			REFRESH_A;
		}
	}

	inline u32 getOrder()			{ return m_order;		}
    inline void setOrder(u32 order) {
		if (order != m_order) {
			m_order = order;
			REFRESH_A;
		}
	}

	inline const char*  getCallBack()	                    { return m_callBack;	         }
    inline void         setCallBack(const char* callBack)   { setStrC(m_callBack, callBack); }
	
	inline const char* getAsset()		{ return m_asset;		}

	inline const char* getMovieName()	{ return m_movieName;	}

	inline void gotoFrame(const char* label) {
		u16 fnum;
		m_pSWFNode->findCodeFrame((char *)label, &fnum);
		m_pSWFNode->gotoFrame(fnum);
		if (fnum == NULL_IDX) {
				DEBUG_PRINT("[SCRIPT] Flash GOTOFRAME %s not found.", label);
		}
	}

	inline u16	getFrameRate()			{ return 1000/m_pSWFNode->getFrameRate();		}
	inline void setFrameRate(u32 fps)	{ m_pSWFNode->setFrameRate((u16)(1000/fps));	}

	inline bool isAnimating()			{ return m_pSWFNode->isStillAnimating();		}

	inline void setFrameRateScale(float scale) {
		float rate = (float)m_defaultRate * scale;
		m_pSWFNode->setFrameRate((u16)rate);
	}

	inline float getVolume()				{ return m_pSWFNode->getVolumeSE();	}
	inline void  setVolume(float volume)	{ m_pSWFNode->setVolumeSE(volume);	}

private:

	const char*	m_callBack;
	const char* m_movieName;
	const char* m_asset;
	u32			m_order;
	bool		m_play;

	CKLBSWFMovie		*	m_pSWFNode;

	struct LABEL {
		LABEL	   * next;

		const char * label;
		const char * callback;
		u16			 index;
	};

	LABEL			*	m_beginLabel;
	u32					m_flashHandle;

	u16					m_defaultRate;
	static	PROP_V2		ms_propItems[];

	enum {
		REPLACE_BLOCK = 10
	};

	void receiveMsg	(CKLBObject* emitter, u32 msgID, u32 msgParam);

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
			  u32 order, float x, float y, const char * asset,
			  const char * movie_name, const char * complete_callback,
			  const char ** replace_list = NULL, int asset_cnt = 0);

	bool initCore(  u32 order,
					float x, float y, const char * asset,
					const char * movie_name, const char * complete_callback,
					const char ** asset_list = NULL, int replace_cnt = 0);

	const char **   replaceAssets       (CLuaState& lua, int pos, int * retcnt);
	bool            removeReplaceList   (const char ** list, int cnt);
	void            reachFrame          (const char* label, const char* callBack);

};



#endif // CKLBUISWFPlayer_h
