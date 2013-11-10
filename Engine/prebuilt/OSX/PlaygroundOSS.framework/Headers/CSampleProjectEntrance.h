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
#ifndef CSampleProjectEntrance_h
#define CSampleProjectEntrance_h

#include "CPFInterface.h"
#include "CKLBGameApplication.h"

class CSampleProjectEntrance : public CKLBGameApplication
{
private:
	CSampleProjectEntrance();
	virtual ~CSampleProjectEntrance();
public:
    static CSampleProjectEntrance * getInstance();

private:
	bool initLocalSystem(CKLBAssetManager& mgrAsset);
	void localFinish();
};

#endif // CSampleProjectEntrance_h
