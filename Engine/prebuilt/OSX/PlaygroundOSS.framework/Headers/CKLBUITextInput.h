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
#ifndef CKLBUITextBox_h
#define CKLBUITextBox_h

#include "CKLBUITask.h"
#include "CKLBTextInputNode.h"

/*!
* \class CKLBUITextInput
* \brief Text Input Task Class
* 
* CKLBUITextInput is a UITask managing text inputs.
* In addition to providing desing and display APIs, it also provides some control ones 
* such as a maximum length control.
*/
class CKLBUITextInput : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUITextInput>;
private:
	CKLBUITextInput();
	virtual ~CKLBUITextInput();
public:
	virtual u32 getClassID();

	static CKLBUITextInput * create(CKLBUITask * pParent, CKLBNode * pNode,
									bool passwdmode,
									float x, float y, float width, float height,
									const char * default_text,
									const char * on_change_callback,
									int widget_id, int maxlen, u32 chartype);

	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline u32  getWidth()					{ return m_width;	}
	inline void setWidth(u32 width)			{
		// m_widthは変更なしだが、textBoxのwidthが初期値の場合があるためどちらもみるように変更  2013/03/25   //
		if (m_width != width || m_pTextBox->getWidth() != width) {
			m_width = width;
			m_pTextBox->setWidth(width);
			REFRESH_A;
		}
	}

	inline u32 getHeight()					{ return m_height;	}
	inline void setHeight(u32 height)		{
		// m_heightは変更なしだが、textBoxのheightが初期値の場合があるためどちらもみるように変更  2013/03/25   //
		if (m_height != height || m_pTextBox->getHeight() != height) {
			m_height = height;
			m_pTextBox->setHeight(height);
			REFRESH_B;
		}
	}

	inline const char*  getText()			        { return m_pTextBox->getText();		}
	inline void         setText(const char* text)	{
		setStrC(m_text, text);
		m_pTextBox->setText(text);
	}

	inline void setPlaceHolder(const char * placeholder) { m_pTextBox->setPlaceHolder(placeholder); }

	inline int	getMaxLen()					{ return m_pTextBox->getMaxlen();	}
	inline void setMaxLen(int maxLen)		{ m_pTextBox->setMaxlen(maxLen);	}

	inline void setCharType(u32 charType)	{ m_pTextBox->setCharType((IWidget::TEXTCHARTYPE)charType); }

	inline s32	getCharCount()				{ return CKLBUtility::charCountUtf8(m_pTextBox->getText()); }

	inline void setColor(bool bTouch, u32 fg_rgb, u32 bg_rgb) {
		fg_rgb |= 0xff000000;
        bg_rgb |= 0xff000000;
		m_pTextBox->setColor(bTouch, fg_rgb, bg_rgb);
	}

	inline void setFont(const char* fontName, float fontSize) { m_pTextBox->setFont(fontName, fontSize); }
    
    inline void setAlign(int _alignType) { if(!m_pTextBox) return; m_pTextBox->setAlign((IWidget::TEXTALIGNMENTTYPE)_alignType); }

private:
	bool init(  CKLBUITask * pParent, CKLBNode * pNode,
				bool passwdmode,
				float x, float y, float width, float height,
				const char * default_text,
				const char * on_change_callback,
				int widget_id, int maxlen, u32 chartype);

	bool initCore(	bool passwdmode,
					float x, float y, float width, float height,
					const char * default_text,
					const char * on_change_callback,
					int widget_id, int maxlen, u32 chartype);

	const char*			m_text;
	CKLBUITextBox	*	m_pTextBox;
	const char		*	m_callback;
	u32					m_width;
	u32					m_height;
	int					m_ID;

	static	PROP_V2		ms_propItems[];
};

#endif // CKLBUITextBox_h
