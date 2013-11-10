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
#ifndef CKLBJsonItem_h
#define CKLBJsonItem_h

#include <stdlib.h>
#include "BaseType.h"

/*!
* \class CKLBJsonItem
* \brief JSON Item Class
* 
* 
*/
class CKLBJsonItem
{
public:
	CKLBJsonItem(CKLBJsonItem * pParent);
	virtual ~CKLBJsonItem();

	// キー取得
	inline const char * key() const { return m_key; }

	bool setKey(const char * keyname);

	// データ型種別
	typedef enum {
		J_NULL,
		J_BOOLEAN,
		J_INT,
		J_DOUBLE,
		J_STRING,
		J_MAP,			// { 〜 } mapにはkeyが無い場合がある。
		J_ARRAY,		// [ 〜 ] arrayにはkeyがある。
	} JSON_TYPE;

	// map と array は Json 的には異なるが、このデータでは同様に階層構造で扱う。

	inline const JSON_TYPE getType() const { return m_type; }

	static CKLBJsonItem * ReadJsonData(const char * json_string, u32 json_size = 0);

	inline CKLBJsonItem * next	() { return m_next;			}
	inline CKLBJsonItem * prev	() { return m_prev;			}
	inline CKLBJsonItem * child	() { return m_child_begin;	}
	inline CKLBJsonItem * parent() { return m_pParent;		}

	inline bool getBool	() const { return m_value.b;		}
	inline int  getInt	() const { return (int)getInt64();	}
	inline s64  getInt64() const {
		if(m_type == J_INT) return m_value.i;
		if(m_type == J_DOUBLE) return (s64)m_value.d;
		if(m_type == J_STRING) {
			s64 val = 0;
			const char * p = m_value.s;
			s64 sign = 1LL;
			if(*p == '-') {
				sign = -1LL;
				p++;
			}
			while(int c = *p++) {
				val = val * 10LL + (s64)(c - '0');
			}
			val = val * sign;
			return val;
		}
		return 0LL;
	}
	inline double getDouble() const {
		if(m_type == J_DOUBLE) return m_value.d;
		if(m_type == J_INT) return (double)m_value.i;
		if(m_type == J_STRING) {
			double val;
			sscanf(m_value.s, "%lf", &val);
			return val;
		}
		return 0.0;
	}
	inline const char * getString() const { return m_value.s; }

	CKLBJsonItem * searchChild(const char * key);

private:
	CKLBJsonItem	*	m_pParent;	// 親アイテム

	CKLBJsonItem	*	m_child_begin;	// 子アイテム
	CKLBJsonItem	*	m_child_end;

	CKLBJsonItem	*	m_prev;		// 兄弟(前)
	CKLBJsonItem	*	m_next;		// 兄弟(次)

	const char		*	m_key;		// キー(名前)

private:

	union VAR {
		bool			b;
		s64				i;
		double			d;
		const char	*	s;
	} m_value;

	JSON_TYPE		m_type;

	typedef struct {
		CKLBJsonItem	*	pParent;
		CKLBJsonItem	*	pCurrent;
		CKLBJsonItem	*	pFirst;
	} JSON_State;

	static int read_null		(void * ctx);
	static int read_boolean		(void * ctx, int boolean);
	static int read_int			(void * ctx, long long integerVal);
	static int read_double		(void * ctx, double doubleVal);
	static int read_string		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_start_map	(void * ctx, unsigned int size);  
	static int read_map_key		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_end_map		(void * ctx);
	static int read_start_array	(void * ctx, unsigned int size);
	static int read_end_array	(void * ctx);
};


#endif // CKLBJsonItem_h
