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
#ifndef CKLBUIMoviePlayer_h
#define CKLBUIMoviePlayer_h

#include "CKLBUITask.h"
#include "CKLBMovieNode.h"

/*!
* \class CKLBUIMoviePlayer
* \brief Movie Player Task Class
* 
* CKLBUIMoviePlayer is used to play movies into the Game.
* It provides a few APIs to manage the movie display and some
* playing option (play, stop, pause, resume).
* The task is platform independant as it uses a CKLBMovieNode which
* uses itself an implementation of IWidget that is platform specific.
*
* /!\ CKLBUIMoviePlayer does NOT work on Windows at the moment.
*/
class CKLBUIMoviePlayer : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIMoviePlayer>;
private:
	CKLBUIMoviePlayer();
	virtual ~CKLBUIMoviePlayer();
public:
	u32 getClassID();

	static CKLBUIMoviePlayer * create(CKLBUITask * pParent, CKLBNode * pNode,
                                      bool mode, float x, float y,
                                      float width, float height,
                                      const char * url, const char * callback);
    
	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);
    
	void execute(u32 deltaT);
	void dieUI  ();

	inline void setWidth(u32 width) {
		if (width != m_width) {
			m_width = width;
			REFRESH_A;
		}
	}
	
	inline u32  getWidth() {
		return m_width;
	}

	inline void setHeight(u32 height) {
		if (height != m_height) {
			m_height = height;
			REFRESH_A;
		}
	}

	inline u32  getHeight() {
		return m_height;
	}

	inline void setText(const char* text) {
		if (text) {
			if (CKLBUtility::safe_strcmp(text, m_url)!=0) {
				setStrC(m_url,text);
				REFRESH_B;
			}
		} else {
			if (CKLBUtility::safe_strcmp("", m_url)!=0) {
				setStrC(m_url,"");
				REFRESH_B;
			}
		}
	}
	inline const char* getText() { return m_url; }

	inline void moviePlay   ()				{ m_pMovieNode->command(IWidget::MV_PLAY);   }
	inline void movieStop   ()				{ m_pMovieNode->command(IWidget::MV_STOP);   }
	inline void moviePause  ()				{ m_pMovieNode->command(IWidget::MV_PAUSE);  }
	inline void movieResume ()				{ m_pMovieNode->command(IWidget::MV_RESUME); }

private:
	u32	        m_width;
	u32         m_height;
	const char* m_url;

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
              bool mode, float x, float y,
              float width, float height,
              const char * url, const char * callback);
    
	bool initCore(bool mode, float x, float y,
                  float width, float height,
                  const char * url, const char * callback);
    
	CKLBMovieNode	*	m_pMovieNode;
    
    const char      *   m_cmdCallback;
    
	static	PROP_V2		ms_propItems[];
};

#endif // CKLBUIMoviePlayer_h
