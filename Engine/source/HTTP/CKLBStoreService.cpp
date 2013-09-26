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
//  CKLBStoreService.cpp
//  GameEngine
//
//


#include "CKLBStoreService.h"
#include "CKLBUtility.h"
#include "CKLBScriptEnv.h"
#include "CLuaState.h"
#include "CPFInterface.h"
enum {
	// Command Values定義
  STORESERVICE_BUY_ITEMS,
  STORESERVICE_GET_PRODUCTS,
  STORESERVICE_FINISH_TRANSACTION
};

static IFactory::DEFCMD cmd[] = {
    { "STORESERVICE_BUY_ITEMS",		STORESERVICE_BUY_ITEMS 	},
    { "STORESERVICE_FINISH_TRANSACTION", STORESERVICE_FINISH_TRANSACTION },
    { "STORESERVICE_GET_PRODUCTS",	STORESERVICE_GET_PRODUCTS 	},
    
    { "STORE_FAILED",               IClientRequest::E_STORE_FAILED },
    { "STORE_PURCHASHING",          IClientRequest::E_STORE_PURCHASHING },
    { "STORE_PURCHACHED",           IClientRequest::E_STORE_PURCHASHED },
    { "STORE_RESTORE",              IClientRequest::E_STORE_RESTORE },
    { "STORE_RESTORE_COMPLETED",    IClientRequest::E_STORE_RESTORE_COMPLETED },
    { "STORE_RESTORE_FAILED",       IClientRequest::E_STORE_RESTORE_FAILED },
    { "STORE_GET_PRODUCTS" ,        IClientRequest::E_STORE_GET_PRODUCTS },
	{0, 0}
};

static CKLBTaskFactory<CKLBStoreService> factory("STORE_Service", CLS_KLBSTORESERVICE, cmd);

enum {
	ARG_CALLBACK = 1,
	ARG_REQUIRE = ARG_CALLBACK,
	ARG_STORE_MAX = ARG_CALLBACK
};


CKLBStoreService::CKLBStoreService()
: CKLBLuaTask	()
, m_callback	(NULL)
{
}

CKLBStoreService::~CKLBStoreService() 
{
	KLBDELETEA(m_callback);
}

u32 
CKLBStoreService::getClassID() 
{
	return CLS_KLBSTORESERVICE;
}

/*static*/
CKLBStoreService* 
CKLBStoreService::create(const char* callback) 
{
	CKLBStoreService* pTask = KLBNEW(CKLBStoreService);
    if (!pTask) { return NULL; }
	if (!pTask->init(callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool 
CKLBStoreService::init(const char* callback) 
{
	if(callback) { setStrC(m_callback, callback); }

    // OsCtrlEventのキューを使用するため、ポーズ中にもイベント回収可能なレベルを使用する。
	return regist(NULL, P_IMPORTANT);
}

bool
CKLBStoreService::initScript(CLuaState& lua)
{
    int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_STORE_MAX) { return false; }

    const char * callback = lua.getString(ARG_CALLBACK);
    if(!init(callback)) {
		return false;
	}
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    pForm.initStoreTransactionObserver();
	return true;
}

int
CKLBStoreService::commandScript(CLuaState& lua)
{
  int ret = 0;
  int argc = lua.numArgs();
  if(argc < 2) {
    lua.retBool(false);
    return 1;
  }
  int cmd = lua.getInt(2);
  IPlatformRequest& pForm = CPFInterface::getInstance().platform();
  switch(cmd)
    {
    case STORESERVICE_BUY_ITEMS:
      {
    	  klb_assert(argc == 3, "Must specify 1 item for STORESERVICE_BUY_ITEMS");
          pForm.buyStoreItems(lua.getString(3));
      }
      break;
    case STORESERVICE_GET_PRODUCTS:
      {
        if(argc == 4) {
          /*
            1: task
            2: command
            3: products
            4: currency文字列で取得するか否か
          */
          const char* json      = lua.getString(3);
          bool        currency  = lua.getBoolean(4);
          pForm.getStoreProducts(json, currency);
        }
      }
      break;
    case STORESERVICE_FINISH_TRANSACTION:
    {
        if(argc == 3) {
            /*
             1: task
             2: command
             3: receipt
             */
            const char* receipt = lua.getString(3);
            pForm.finishStoreTransaction(receipt);
        }
        
    
      break;
    }
    default:
      {
        lua.retBool(false);
        ret = 1;
      }
      break;
    }

  return ret;
}

void
CKLBStoreService::execute(u32 /*deltaT*/)
{
    CKLBOSCtrlQueue& osq  = CKLBOSCtrlQueue::getInstance();
    const OSCTRL *   item = NULL;
    osq.startItem();
    // Widgetポインタが当てられてないがメッセージキューの割当は区別する必要が有るので疑似値を使用する
    while(0 != (item = osq.getItem(0))) {
        switch(item->type)
        {
        case IClientRequest::E_STORE_FAILED:            cbStoreFailed(item);           	break;
        case IClientRequest::E_STORE_PURCHASHED:        cbStorePurchashed(item);       	break;
        case IClientRequest::E_STORE_PURCHASHING:       cbStorePurchashing(item);      	break;
        case IClientRequest::E_STORE_RESTORE:           cbStoreRestore(item);          	break;
        case IClientRequest::E_STORE_RESTORE_COMPLETED: cbStoreRestoreCompleted(item); 	break;
        case IClientRequest::E_STORE_RESTORE_FAILED:    cbStoreRestoreFailed(item);    	break;
        case IClientRequest::E_STORE_GET_PRODUCTS: 		cbStoreGetProducts(item); 		break;
        case IClientRequest::E_STORE_BAD_ITEMID: 		cbStoreFailed(item); 			break;
        default:
            break;
        }
    }
}

void
CKLBStoreService::die()
{
	// 2012.11.27  解放漏れがあったので修正
	if( m_callback ) {
		KLBDELETEA( m_callback );
		m_callback = NULL;
	}
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    pForm.releaseStoreTransactionObserver();
}

int
CKLBStoreService::cbStoreFailed(const OSCTRL * item)
{
    const char * itemId = (const char *)item->data1;
	execCallback(IClientRequest::E_STORE_FAILED, itemId);
    
    return 0;
}

int
CKLBStoreService::cbStorePurchashed(const OSCTRL * item)
{
    const char * itemId  = (const char *)item->data1;
	const char * receipt = (const char *)item->data2;
	execCallback(IClientRequest::E_STORE_PURCHASHED, itemId, receipt);

    return 0;
}

int
CKLBStoreService::cbStorePurchashing(const OSCTRL * item)
{
    const char * itemId = (const char *)item->data1;
	execCallback(IClientRequest::E_STORE_PURCHASHING, itemId);
    
    return 0;
}
int
CKLBStoreService::cbStoreRestore(const OSCTRL * item)
{
    const char * itemId = (const char *)item->data1;
	execCallback(IClientRequest::E_STORE_RESTORE, itemId);
    
    return 0;
}

int
CKLBStoreService::cbStoreRestoreCompleted(const OSCTRL * /*item*/)
{
	execCallback(IClientRequest::E_STORE_RESTORE_COMPLETED, "");
    
    return 0;
}

int
CKLBStoreService::cbStoreRestoreFailed(const OSCTRL * /*item*/)
{
    execCallback(IClientRequest::E_STORE_RESTORE_FAILED, "");
    return 0;
}

int
CKLBStoreService::cbStoreGetProducts(const OSCTRL * item)
{
    if (item) {
        const char* products = static_cast<const char*>(item->data1);
        execCallback(IClientRequest::E_STORE_GET_PRODUCTS, "", products);
    }
    
    return 0;
}
