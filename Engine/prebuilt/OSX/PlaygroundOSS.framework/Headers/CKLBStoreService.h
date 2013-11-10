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
//  CKLBStoreService.h
//  GameEngine
//
//

#ifndef CKLBStoreService_h
#define CKLBStoreService_h

#include "CKLBLuaTask.h"
#include "CKLBOSCtrlEvent.h"
#include "CKLBLuaEnv.h"

/*!
* \class CKLBStoreService
* \brief Store Service Task class.
* 
* CKLBStoreService is responsible for the different interactions with the Application Store,
* as getting the products list or buying items.
* This task is platform independant as it uses IPlatformRequest to process its requests.
*/
class CKLBStoreService : public CKLBLuaTask
{
    friend class CKLBTaskFactory<CKLBStoreService>;
private:
    CKLBStoreService();
    virtual ~CKLBStoreService();
	bool init(const char* callback);
public:
	virtual u32 getClassID();
	static CKLBStoreService* create(const char* callback);

    bool	initScript		(CLuaState& lua);
    int		commandScript	(CLuaState& lua);
    
    void	execute			(u32 deltaT);
    void	die				();
    
	void	buyItems		(const char* item) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		pForm.buyStoreItems(item);
	}

	inline void getProducts(const char* json, bool currency) { CPFInterface::getInstance().platform().getStoreProducts(json, currency); }

private:
    int cbStoreFailed			(const OSCTRL * item);
    int cbStorePurchashed		(const OSCTRL * item);
    int cbStorePurchashing		(const OSCTRL * item);
    int cbStoreRestore			(const OSCTRL * item);
    int cbStoreRestoreCompleted	(const OSCTRL * item);
    int cbStoreRestoreFailed	(const OSCTRL * item);
    int cbStoreGetProducts		(const OSCTRL * item);
    
	inline void execCallback(IClientRequest::EVENT_TYPE status, const char * itemId = "", const char * data = "") {
		if(m_callback) CKLBScriptEnv::getInstance().call_storeEvent(m_callback, this, status, itemId, data);
	}
 
private:
    const char          *   m_callback;
};


#endif
