#pragma once

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>

#include <sapi.h>
#include <string>
#include <iostream>


//通知結果を保持する
class RecognitionResult {
public:
	std::wstring getResult() {
		std::wstring ret = result;
		result = L"";//内容をとったら空にしておく
		return ret;
	}
	void setResult(const std::wstring& str) {
		result = str;
	}
private:
	std::wstring result;
};
static RecognitionResult g_RecoResult; //とりあえずグローバル変数として宣言


//音声認識イベントのコールバック関数
void __stdcall NotifyCallback(WPARAM wParam, LPARAM lParam);


//COMオブジェクトの自動解放をカプセル化したもの。
template <class T> class AutoCom
{
	T *pCom;
public:
	

	AutoCom(void) 
		:pCom(nullptr) 
	{
	}
	AutoCom(T *pSrcCom)
		:pCom(nullptr) {
		operator=(pSrcCom);
	}
	~AutoCom(void) {
		if (pCom) { 
			pCom->Release(); 
			pCom = nullptr; 
		} 
	}

	bool IsAvailable(void) {
		return pCom ? true : false; 
	}
	
	bool IsNull(void) {
		return pCom ? false : true; 
	}

	operator T*(void) {
		return pCom; 
	}
	
	operator T**(void) { 
		return &pCom; 
	}
	
	operator T&(void) {  
		return *pCom; 
	}
	
	T& operator*(void) { 
		return *pCom; 
	}
	
	T** operator&(void) { 
		if (pCom) { 
			pCom->Release(); 
			pCom = nullptr; 
		}
		return &pCom;
	}
	
	T* operator->(void) { 
		return pCom; 
	}
	
	T* operator=(T *pSrcCom) {
		if (pSrcCom == pCom) { 
			return pCom; }
		
		if (pCom) { 
			pCom->Release(); 
		}
		pCom = pSrcCom; 
		
		return pCom;
	}

	T* get() {
		return pCom;
	}
	//COMオブジェクト生成。
	HRESULT create(GUID ClsID, GUID IID = __uuidof(T))
	{
		if (pCom){ pCom->Release(); pCom = NULL; }
		HRESULT hResult = CoCreateInstance(ClsID, NULL, CLSCTX_ALL, IID, (LPVOID *)&pCom);
		if (FAILED(hResult))pCom = NULL;
		return hResult;
	}
};

//音声認識用のクラス
class VoiceRecognizer
{
	AutoCom<ISpRecognizer> m_acRecognizer;
	AutoCom<ISpRecoContext> m_acRecoContext;
	AutoCom<ISpRecoGrammar> m_acRecoGrammar;
	AutoCom<ISpObjectTokenCategory> m_acRecognizerCategory;
	AutoCom<IEnumSpObjectTokens> m_acRecognizerTokens;
	AutoCom<ISpObjectToken> m_acRecognizerToken;
	AutoCom<ISpObjectTokenCategory> m_acAudioInputCategory;
public:
	void initialize() {
		HRESULT hResult = S_OK;

		//ISpRecognizerの生成
		m_acRecognizer.create(CLSID_SpInprocRecognizer);

		//認識エンジンの設定。
		m_acRecognizerCategory.create(CLSID_SpObjectTokenCategory);
		hResult = m_acRecognizerCategory->SetId(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Recognizers", TRUE);
		hResult = m_acRecognizerCategory->EnumTokens(NULL, NULL, &m_acRecognizerTokens);

		//認識エンジンの一覧を走査し日本語認識エンジンを探す。
		while (true) {
			if (FAILED(m_acRecognizerTokens->Next(1, &m_acRecognizerToken, NULL)) || m_acRecognizerToken.IsNull()) {
				break;
			}

			BOOL IsMatches = FALSE;
			hResult = m_acRecognizerToken->MatchesAttributes(L"language=411", &IsMatches);
			if (IsMatches == TRUE) {
				hResult = m_acRecognizer->SetRecognizer(m_acRecognizerToken);
			}
		}

		//音声入力の設定。
		m_acAudioInputCategory.create(CLSID_SpObjectTokenCategory);
		if (m_acAudioInputCategory.IsAvailable()) {
			hResult = m_acAudioInputCategory->SetId(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\AudioInput", TRUE);
			//標準入力デバイスIDの取得。
			WCHAR *pDefaultAudioInputId = NULL;
			if (FAILED(m_acAudioInputCategory->GetDefaultTokenId(&pDefaultAudioInputId))) {
				pDefaultAudioInputId = NULL;
			}
			//標準入力デバイスIDから標準入力デバイスを生成し設定。
			if (pDefaultAudioInputId) {
				AutoCom<ISpObjectToken> acAudioInputToken;
				acAudioInputToken.create(CLSID_SpObjectToken);
				acAudioInputToken->SetId(NULL, pDefaultAudioInputId, FALSE);
				hResult = m_acRecognizer->SetInput(acAudioInputToken, TRUE);

				CoTaskMemFree(pDefaultAudioInputId); pDefaultAudioInputId = NULL;
			}
		}

		//ISpRecoContextの生成と設定。
		m_acRecognizer->CreateRecoContext(&m_acRecoContext);
		hResult = m_acRecoContext->SetNotifyCallbackFunction(NotifyCallback, (WPARAM)m_acRecoContext.get(), 0);
		hResult = m_acRecoContext->SetInterest(SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_HYPOTHESIS),
			SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_HYPOTHESIS));

		//ISpRecoGrammarの生成と設定。
		m_acRecoContext->CreateGrammar(NULL, &m_acRecoGrammar);


		//認識文法の設定
		//TODO:XMLから文法をロードするようにする
		SPSTATEHANDLE SpStateHandle;
		m_acRecoGrammar->GetRule(NULL, 1, SPRAF_TopLevel | SPRAF_Active, TRUE, &SpStateHandle);
		m_acRecoGrammar->AddWordTransition(SpStateHandle, NULL, L"みぎ", L"、 ", SPWT_LEXICAL, 1, NULL);
		m_acRecoGrammar->GetRule(NULL, 2, SPRAF_TopLevel | SPRAF_Active, TRUE, &SpStateHandle);
		m_acRecoGrammar->AddWordTransition(SpStateHandle, NULL, L"ひだり", L"、 ", SPWT_LEXICAL, 1, NULL);

		m_acRecoGrammar->Commit(0);

		hResult = m_acRecoGrammar->SetRuleIdState(0, SPRS_ACTIVE);
	}
};