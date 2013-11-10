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
#ifndef CKLBUIGroup_h
#define CKLBUIGroup_h

#include "CKLBUITask.h"
#include "CKLBNodeAnimPack.h"

/*!
* \class CKLBUIGroup
* \brief Group Task Class
* 
* CKLBUIGroup allows to easily manage UITasks groups.
* With CKLBUIGroup you can anim or skip the anim of a whole group of tasks 
* at the same time with a single command.
*/
class CKLBUIGroup : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIGroup>;
private:
	CKLBUIGroup();
	virtual ~CKLBUIGroup();

	bool init(CKLBUITask* parent, CKLBNode* pNode, float x, float y);
	bool initCore(float x, float y);
public:
	u32 getClassID();

	static CKLBUIGroup* create(CKLBUITask* parent, CKLBNode* pNode, float x, float y);
	bool initUI     (CLuaState& lua);
	int  commandUI  (CLuaState& lua, int argc, int cmd);
	void execute    (u32 deltaT);
	void dieUI      ();

	inline bool setAnimCallback	(const char* callback)			{ return m_animpack.setCallback(callback);				}
	inline bool setAnimation	(const char* name, bool blend)	{ return m_animpack.kickAnim(getNode(), name, blend);	}
	inline bool skipAnim		(const char* name)				{ return m_animpack.skipAnim(getNode(), name);			}
	inline bool isAnim			(const char* name)				{ return name ? (m_animpack.getAnimCounter(name) > 0) : false; }

	CKLBNodeAnimPack	m_animpack;

	static	PROP_V2		ms_propItems[];
};


#endif // CKLBUIGroup_h
