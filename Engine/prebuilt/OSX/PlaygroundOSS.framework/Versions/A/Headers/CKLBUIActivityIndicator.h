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
//  CKLBUIActivityIndicator.h
//  GameEngine
//
//
//

#ifndef CKLBUIActivityIndicator_h
#define CKLBUIActivityIndicator_h

#include "CKLBUITask.h"
#include "CPFInterface.h"
#include "OSWidget.h"
#include "CKLBActivityIndicatorNode.h"

/*!
* \class CKLBUIActivityIndicator
* \brief UI Activity Indicator Task Class
* This task display an OS native "busy" indicator to show that the device is busy doing some work.
* As an example, when application is connecting or transfering data with the server.
*/
class CKLBUIActivityIndicator : public CKLBUITask
{
    friend class CKLBTaskFactory<CKLBUIActivityIndicator>;
private:
    CKLBUIActivityIndicator();
    virtual ~CKLBUIActivityIndicator();
public:
    u32 getClassID();
    
	static CKLBUIActivityIndicator * create(CKLBUITask * pParent, CKLBNode * pNode,
                                            int show_type,
                                            float x, float y, float width, float height,
                                            int widget_id = 0);
    
	bool initUI     (CLuaState& lua);
	int commandUI   (CLuaState& lua, int argc, int cmd);
    
	void execute    (u32 deltaT);
	void dieUI      ();
private:
    
    bool init(CKLBUITask * pParent, CKLBNode * pNode,
              int show_type,
              float x, float y, float width, float height,
              int widget_id);
    
	bool initCore(int show_type,
                  float x, float y, float width, float height,
                  int widget_id);

private:
    CKLBActivityIndicatorNode   *   m_pActivityIndicator;
	int                             m_ID;
    
	static const char           *   ms_propItems[];
};


#endif
