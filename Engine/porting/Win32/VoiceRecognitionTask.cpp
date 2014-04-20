#include "VoiceRecognitionTask.h"

static IFactory::DEFCMD cmd[] = {
	{ 0, 0 }
};

static CKLBTaskFactory<VoiceRecognitionTask> factory("UI_VOICE_RECOGNITION", CLS_VOICE_RECOGNITION, cmd);

VoiceRecognitionTask::VoiceRecognitionTask() {

}

VoiceRecognitionTask::~VoiceRecognitionTask() {
}

u32 VoiceRecognitionTask::getClassID() {
	return CLS_VOICE_RECOGNITION;
}

VoiceRecognitionTask * VoiceRecognitionTask::create(CKLBUITask * pParent, CKLBNode * pNode,
	bool passwdmode,
	float x, float y, float width, float height,
	const char * default_text,
	const char * on_change_callback,
	int widget_id, int maxlen, u32 chartype) {

	return new VoiceRecognitionTask();
}

bool VoiceRecognitionTask::initUI(CLuaState& lua) {
	return true;
}
int VoiceRecognitionTask::commandUI(CLuaState& lua, int argc, int cmd) {
	return 1;
}

void VoiceRecognitionTask::execute(u32 deltaT) {
	std::wstring result = g_RecoResult.getResult();
	if (result == L"") {
		return;
	}
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.retGlobal(m_luaFunc);

	//Lua‚É–ß‚è’l‚ð•Ô‚·
	char retStr[256] = {};
	wcstombs(retStr, result.c_str(), 256);
	lua.retString(retStr);
}
void VoiceRecognitionTask::dieUI() {

}

bool VoiceRecognitionTask::init(CKLBUITask * pParent, CKLBNode * pNode, int) {

	if (this->recognizer == nullptr) {
		recognizer = new VoiceRecognizer();
	}

	recognizer->initialize();
	return true;
}

bool VoiceRecognitionTask::initCore(bool passwdmode,
	float x, float y, float width, float height,
	const char * default_text,
	const char * on_change_callback,
	int widget_id, int maxlen, u32 chartype){
		setStrC(m_luaFunc, on_change_callback);

	return true;
}



