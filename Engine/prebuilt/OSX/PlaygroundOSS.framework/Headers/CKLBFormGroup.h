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
#ifndef CKLBFormGroup_h
#define CKLBFormGroup_h

#include "CKLBUISystem.h"

class CKLBFormGroup
{
private:
	CKLBFormGroup();
	virtual ~CKLBFormGroup();
public:
	static CKLBFormGroup& getInstance();

	void release();

	bool addForm(SFormCtrlList * list, const char * group_name);
	bool delForm(SFormCtrlList * list);

	inline bool isExclusive(SFormCtrlList * list) {
		GROUP * pGrp = (GROUP *)list->pGroup;
		bool grpEx = (pGrp) ? true : false;
		return list->bExclusive || grpEx;
	}

	inline bool isWorking(SFormCtrlList * list, void * locker = NULL) {
		if(list->bExclusive && list->bWorking) return true;
		GROUP * pGrp = (GROUP *)list->pGroup;
		if(pGrp && pGrp->working) {
			if(!locker || locker != pGrp->locker) return true;
		}
		return false;
	}

	inline void setWorking(SFormCtrlList * list, bool working, void * locker = NULL) {
		if(list->bExclusive) list->bWorking = working;
		GROUP * pGrp = (GROUP *)list->pGroup;
		if(pGrp) {
			pGrp->working = working;
			pGrp->locker = (working) ? locker : NULL;
			pGrp->worker = (working) ? list   : NULL;
		}
	}

private:
	struct GROUP {
		GROUP		*	prev;
		GROUP		*	next;

		// グループの持つ属性
		const char	*	name;
		bool			exclusive;	// 排他制御(trueで排他)
		bool			working;	// 操作中
		void		*	locker;		// ロックした者の識別子(ポインタ)

		SFormCtrlList	*	worker;

		// グループ所属のコントロールリスト構造体リスト(「リスト」が多くてめんどくさい)
		SFormCtrlList	*	begin;
		SFormCtrlList	*	end;
	};

	GROUP * searchGroup(const char * group_name);
	GROUP * createGroup(const char * group_name);
	void    checkGroup(GROUP * pGrp);

	GROUP		*	m_begin;
	GROUP		*	m_end;
};

#endif // CKLBFormGroup_h
