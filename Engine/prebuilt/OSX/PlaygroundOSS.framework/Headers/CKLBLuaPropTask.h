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
#ifndef CKLBLuaPropTask_h
#define CKLBLuaPropTask_h

#include "CKLBLuaTask.h"
#include "CKLBUtility.h"

class CKLBLuaPropTask;
typedef void (CKLBLuaPropTask::*setBoolT)		(bool);
typedef void (CKLBLuaPropTask::*setIntT)		(s32);
typedef void (CKLBLuaPropTask::*setUintT)		(u32);
typedef void (CKLBLuaPropTask::*setFloatT)		(float);
typedef void (CKLBLuaPropTask::*setStrT)		(const char*);
typedef void (CKLBLuaPropTask::*setPtrT)		(void*);
typedef void (CKLBLuaPropTask::*setGenIntT)		(u32, s32);

typedef bool (CKLBLuaPropTask::*getBoolT)		(void);
typedef s32  (CKLBLuaPropTask::*getIntT)		(void);
typedef u32  (CKLBLuaPropTask::*getUintT)		(void);
typedef float (CKLBLuaPropTask::*getFloatT)		(void);
typedef const char* (CKLBLuaPropTask::*getStrT)	(void);
typedef void* (CKLBLuaPropTask::*getPtrT)		(void);
typedef s32 (CKLBLuaPropTask::*getGenIntT)		(u32);

template <typename T, size_t N>
inline
size_t SizeOfArray( const T(&)[ N ] )
{
  return N;
}

typedef enum {
	NIL,
	BOOLEANT,
	INTEGER,
	UINTEGER = INTEGER,
	NUMERIC,
	STRING,
	POINTER,
	DYNAMIC_INT,

	TYPE_MASK	= 0x0F,
	READ_ONLY	= 0x10,

	R_INTEGER	= INTEGER  | READ_ONLY,
	R_UINTEGER  = UINTEGER | READ_ONLY,
	R_STRING    = STRING   | READ_ONLY,
	R_BOOLEANT  = BOOLEANT | READ_ONLY,
	R_NUMERIC   = NUMERIC  | READ_ONLY,
	R_POINTER	= POINTER  | READ_ONLY,
} PROPTYPE;

/*!
* \class CKLBLuaPropTask
* \brief Lua Prop Task class
* 
* CKLBLuaPropTask is a CKLBLuaTask with properties (int, uint, float, string, bool, pointers).
* These properties can be read and/or written by the scripting part of the game,
* depending on their declaration.
* It is an abstract class for every class in the Engine using properties.
*/
class CKLBLuaPropTask : public CKLBLuaTask
{
	friend class CKLBLuaEnv;
public:
    u32 getClassID();
	CKLBLuaPropTask();
	virtual ~CKLBLuaPropTask();

    virtual TASKTYPE getTaskType();

	virtual bool initScript(CLuaState& lua) = 0;

	// CKLBLuaTask にあったデフォルトの
	// virtual int commandScript(CLuaState& lua);
	// は、そのまま使えるし、オーバーライドしてもよい。
	virtual void execute(u32 deltaT) = 0;
	virtual void die() = 0;

	struct PROP {
		const char * name;		// プロパティインデックス
		PROPTYPE	 type;		// プロパティの型
		union {
			bool		b;		// boolean
			s32			i;		// integer
			float		n;		// real (float)
			char	*	s;		// string
			void	*	p;		// pointer (userlightdata)
		} value;
		bool		checked;
	};

	struct PROP_V2 {
		const char * name;		// property index
		PROPTYPE	 type;		// property type
		union {
			setBoolT	b;
			setIntT		i;
			setUintT	ui;
			setFloatT	f;
			setStrT		s;
			setPtrT		p;
			setGenIntT	g;
		} setter;
		union {
			getBoolT	b;
			getIntT		i;
			getUintT	ui;
			getFloatT	f;
			getStrT		s;
			getPtrT		p;
			getGenIntT	g;
		} getter;
		size_t			offset;
		/*
		union {
			bool		b;		// boolean
			s32			i;		// integer
			float		n;		// real (float)
			char	*	s;		// string
			void	*	p;		// pointer (userlightdata)
		} value;*/
		bool		checked;
	};


	// 保持すべきプロパティ領域を登録する。
	// 内部で生成された配列領域のインデックスは、
	// names 配列で与えられた順番と一致することが保証される。
	bool setupPropertyList(const char * names[], u32 length = 0);

	// 設定済みのプロパティリストを破棄せず、
	// 与えられたプロパティリストを追加する。
	bool addPropertyList(const char * names[]);

	// プロパティ名から内部配列のインデックスを得る。
	int findProperty(const char * name);

	// 値を設定する(idx は findProperty()で返される値)
	void setNil(int idx);
	void setBool(int idx, bool val);
	void setInt(int idx, int val);
	void setNum(int idx, float val);
	bool setStr(int idx, const char * val);
	bool setMem(int idx, const char * val, u32 size );

	// 型を取得する
	inline PROPTYPE getType(int idx) {
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return m_arrProp[idx].type; 
	}

	// 値を取得する
	inline bool isNil(int idx) { 
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return ((m_arrProp[idx].type & TYPE_MASK)== NIL); 
	}
	inline bool getBool(int idx) { 
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return ((m_arrProp[idx].type & TYPE_MASK)== BOOLEANT) ? m_arrProp[idx].value.b : false; 
	}
	inline int  getInt(int idx) {
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return ((m_arrProp[idx].type & TYPE_MASK)== INTEGER)
			? m_arrProp[idx].value.i
			: (((m_arrProp[idx].type & TYPE_MASK) == NUMERIC) ? (int)m_arrProp[idx].value.n : 0);
	}
	inline float getNum(int idx) {
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return ((m_arrProp[idx].type & TYPE_MASK) == NUMERIC)
			? m_arrProp[idx].value.n
			: (((m_arrProp[idx].type & TYPE_MASK) == INTEGER) ? (float)m_arrProp[idx].value.i : 0.0f);
	}
	inline const char * getStr(int idx) {
		klb_assert(!m_newScriptModel, "Old Scripting model only");
		return ((m_arrProp[idx].type & TYPE_MASK)== STRING) ? m_arrProp[idx].value.s : 0; 
	}

	inline void setUpdateFlag	()			{ m_bUpdateByScript = true;  }
	inline void clearUpdateFlag	()			{ m_bUpdateByScript = false; }
	inline bool getUpdateFlag	() const	{ return m_bUpdateByScript;  }
	inline int	getPropertyCount() const	{ return m_cntProp;			 }

	// Lua の配列と内部プロパティをやり取りするメソッド
	int getPropertyByScript(lua_State * L);
	int setPropertyByScript(lua_State * L);

	inline int isNewScriptModel() { return m_newScriptModel; }

protected:
	bool			m_newScriptModel;

    // スクリプトからのプロパティ取得直前に行う処理があれば、このmethodに実装する
    virtual void preGetProp();
    
    // スクリプトからのプロパティ設定直後に行う処理があれば、このmethodに実装する。
    virtual void afterSetProp();

private:
	bool			m_bUpdateByScript;
	int				m_cntProp;		// プロパティ総数
	PROP		*	m_arrProp;		// プロパティ配列
	PROP_V2		*	m_arrPropV2;	// プロパティ配列
};


#endif // CKLBLuaPropTask_h
