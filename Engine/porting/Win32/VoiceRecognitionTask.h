#pragma once
#include "CKLBUITask.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "VoiceRecognition.h"


//音声認識タスク
class VoiceRecognitionTask : public CKLBUITask
{
	friend class CKLBTaskFactory<VoiceRecognitionTask>;
private:
	VoiceRecognitionTask();
	
	virtual ~VoiceRecognitionTask();
public:
	virtual u32 getClassID();

	static VoiceRecognitionTask * create(CKLBUITask * pParent, CKLBNode * pNode,
		bool passwdmode,
		float x, float y, float width, float height,
		const char * default_text,
		const char * on_change_callback,
		int widget_id, int maxlen, u32 chartype);

	bool initUI(CLuaState& lua);
	
	int commandUI(CLuaState& lua, int argc, int cmd);
	
	void execute(u32 deltaT);
	void dieUI();

private:
	bool init(CKLBUITask * pParent, CKLBNode * pNode, int);
	bool initCore(bool passwdmode,
		float x, float y, float width, float height,
		const char * default_text,
		const char * on_change_callback,
		int widget_id, int maxlen, u32 chartype);

	const char *     m_luaFunc;
	VoiceRecognizer * recognizer;

};


