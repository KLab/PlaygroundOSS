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
//
//  CKLBClientBase.h
//  GameEngine
//
#ifndef CKLBGameApplication_h
#define CKLBGameApplication_h

#include "CKLBLuaTask.h"
#include "CPFInterface.h"
#include "CKLBObject.h"

class CKLBAssetManager;

class CKLBGameApplication : public IClientRequest
{
public:
    CKLBGameApplication();
    virtual ~CKLBGameApplication();

	void setInitParam	(u32 param, void* complexSetup);
	bool initGame		();
	void finishGame		();
    
	bool setScreenInfo	(bool rotate, int width, int height);
	bool setFilePath	(const char * strPath);
    
	virtual 
	bool executeCommand	(const char* command);
	void reboot			();

    void resetViewport	();

	virtual FILE* getShellOutput();
	virtual void  setShellOutput(FILE* stream);

protected:
	struct AllocationSize {
		/* Maximum number of single unique node inside dictionnary*/
		u32		dictionnaryNodePoolSize;
		/* Maximum number of handler associated with ressources*/
		u32		handlerPoolSize;
		/* Maximum number of ui parts for all loaded form assets */
		u32		formTemplateNodeCount;
		/* Maximum number of real asset (texture, form, audio sound) loaded at the same time*/
		u32		maxAssetCount;
	};
	
	virtual void pauseGame				(bool pause);

	virtual void setupAllocation		(AllocationSize* pStruct);
	virtual int  getPhysicalScreenWidth	();
	virtual int  getPhysicalScreenHeight();

    // デフォルトでは標準のシステムタスクを起動する。
    virtual bool callInitialTasks(int width, int height);

	// その他初期化処理
	virtual bool initOther();

    // デフォルトでは全方向許可
    virtual bool reportScreenRotation(ORIGIN origin, SCRMODE mode);        
    // デフォルトでは縦横いずれでも全画面使用
    virtual void changeScreenMatrix(ORIGIN origin, int width, int height);
    
    
    
    // ポインティングデバイスによる入力(物理座標)
    virtual void inputPoint(int id, IClientRequest::INPUT_TYPE type, int x, int y);
    
    virtual void inputDeviceKey(int keyId, char eventType);

    // その他OSコントロールによるイベント通知
    virtual void controlEvent(EVENT_TYPE type, IWidget * pWidget,
								size_t datasize1, void * pData1,
								size_t datasize2, void * pData2);
    
    // デフォルトでは常に論理的左上を原点とする
    virtual void changePointingMatrix(ORIGIN origin, int width, int height);
    
    
    bool	frameFlip			(u32 deltaT);
	s32		getFrameTime		();
	void	setFrameTime		(s32 time);
    void	changeScreenInfo	(ORIGIN origin, int width, int height);
    bool	initSystem			(AllocationSize* pSizes);
    virtual 
	bool	initLocalSystem		(CKLBAssetManager& mgrAsset);
	virtual 
	void	localFinish			();
    
	int						m_width;
	int						m_height;
	int						m_frameTime;
    IClientRequest::ORIGIN  m_origin;
	bool					m_useDefaultDB;
	bool					m_useDefaultFont;
    bool                    m_updateRotation;
	bool					m_reboot;
	const char			*	m_bootFile;
	FILE*					m_outStream;
};

#endif
