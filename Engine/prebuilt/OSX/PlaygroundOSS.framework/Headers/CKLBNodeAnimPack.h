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
#ifndef CKLBNodeAnimPack_h
#define CKLBNodeAnimPack_h

#include "CKLBLuaTask.h"
#include "CKLBNode.h"


// アニメーションノードを持たせるためのパッケージ
class CKLBNodeAnimPack
{
public:
	CKLBNodeAnimPack();
	virtual ~CKLBNodeAnimPack();

	bool                setCallback(const char * callback);
	inline const char * getCallback() { return m_callback; }

	bool skipAnim   (CKLBNode * pNode, const char * name);
	bool kickAnim   (CKLBNode * pNode, const char * name, bool doBlend, int id = 0, bool kill = false);

	bool kickEnter  (CKLBNode * pNode);
	bool kickLeave  (CKLBNode * pNode);

	void watchFinishedAnim(CKLBLuaTask * pTask);

	int getAnimCounter(const char * name);

private:
	struct ANIMCOUNT {
		ANIMCOUNT	*	prev;
		ANIMCOUNT	*	next;
		CKLBNode	*	node;	// コマンド発行ノード
		const char	*	name;	// アニメーションラベル
		int				id;		// 実行時に与えられたID値
		bool			kill;	// アニメーション終了時、タスクにkill発行
		u32				count;	// アニメーションノード数のrefCount
	};

	ANIMCOUNT		*	m_begin;
	ANIMCOUNT		*	m_end;

	const char		*	m_callback;

	bool				m_enterBlend;

	static const char * ms_labelEnter;
	static const char * ms_labelLeave;
};

#endif // CKLBNodeAnimPack_h
