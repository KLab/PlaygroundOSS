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
//  platformhandler.cpp
//

#include "CPFInterface.h"
#include "OSWidget.h"
;

IWidget::~IWidget() {}

IClientRequest::IClientRequest() {}
IClientRequest::~IClientRequest() {}

IPlatformRequest::IPlatformRequest() {}
IPlatformRequest::~IPlatformRequest() {}

CPFInterface * CPFInterface::instance = NULL;

// CPFInterface は登録された CPFStrategy の method を呼び出すだけなので、
// Singleton 以外の部分については inline 定義される。
CPFInterface::CPFInterface()
: m_pClient     (NULL)
, m_pPlatform   (NULL) 
{
}

CPFInterface::~CPFInterface() 
{
}

CPFInterface&
CPFInterface::getInstance() {
    /*
    static CPFInterface instance;
    return instance;
     */
    if(!instance) {
        instance = new CPFInterface();
    }
    return *instance;
}


bool
CPFInterface::isBigEndian()
{
    u16     num = 0x7700;
    char *  ptr = (char *)&num;
    return (*ptr == 0x77);
}
