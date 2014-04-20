#include "VoiceRecognition.h"

void __stdcall NotifyCallback(WPARAM wParam, LPARAM lParam)
{

	ISpRecoContext *pRecoContext = (ISpRecoContext *)wParam;
	bool IsQuit = false;

	//イベントキューに蓄積されたイベントの処理。
	SPEVENT SpEvent; memset(&SpEvent, 0, sizeof(SPEVENT));
	ULONG Fetched = 0;
	while (SUCCEEDED(pRecoContext->GetEvents(1, &SpEvent, &Fetched)) && Fetched)
	{
		switch (SpEvent.eEventId)
		{
		case SPEI_HYPOTHESIS://仮定イベント。
		case SPEI_RECOGNITION://確定イベント。
			if (SpEvent.elParamType == SPET_LPARAM_IS_OBJECT)
			{
				//「SpEvent.lParam」を結果オブジェクトISpRecoResultとして扱う。
				ISpRecoResult* pResult = (ISpRecoResult *)SpEvent.lParam;

				//ISpRecoResultのGetText関数で認識結果を文字列で取得できる。
				WCHAR *pResultText = NULL;
				if (SUCCEEDED(pResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &pResultText, NULL)))
				{
					//ルール名やルールIDを知るためにフレーズ情報を取得。
					SPPHRASE* pSpPhrase = NULL;
					if (SUCCEEDED(pResult->GetPhrase(&pSpPhrase)))
					{
						if (SpEvent.eEventId == SPEI_HYPOTHESIS)
							wprintf(L" [名:%s/ID:%lu]%s\n", pSpPhrase->Rule.pszName, pSpPhrase->Rule.ulId, pResultText);
						else
							wprintf(L"*[名:%s/ID:%lu]%s\n", pSpPhrase->Rule.pszName, pSpPhrase->Rule.ulId, pResultText);

						g_RecoResult.setResult(pResultText);
						//取得したフレーズ情報領域は解放する必要があるが、領域内の各要素まで個別に解放する必要はない。
						CoTaskMemFree(pSpPhrase); pSpPhrase = NULL;
					}

					//取得した文字列は解放する必要がある。
					CoTaskMemFree(pResultText); pResultText = NULL;
				}
			}
			break;
		default:
			break;
		}

		if (SpEvent.elParamType != SPEI_UNDEFINED)
		{
			if (SpEvent.elParamType == SPET_LPARAM_IS_POINTER || SpEvent.elParamType == SPET_LPARAM_IS_STRING)
				CoTaskMemFree((void *)SpEvent.lParam);
			else if (SpEvent.elParamType == SPET_LPARAM_IS_TOKEN || SpEvent.elParamType == SPET_LPARAM_IS_OBJECT)
				((IUnknown*)SpEvent.lParam)->Release();
		}
		memset(&SpEvent, 0, sizeof(SPEVENT));
	}

}