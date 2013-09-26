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
#ifndef CWin32KeyChain_h
#define CWin32KeyChain_h

class CWin32KeyChain
{
public:
	CWin32KeyChain();
	virtual ~CWin32KeyChain();

	const char * getValue(const char * service_name, const char * key);
	bool setValue(const char * service_name, const char * key, const char * value);
	bool delValue(const char * service_name, const char * key);

	bool loadKeyChain(const char * filename);
	bool saveKeyChain(const char * filename);

private:

	void clean();

	// KEYVALUE は key と値(文字列)の対応を持つ
	struct KEYVALUE {
		KEYVALUE	*	prev;
		KEYVALUE	*	next;

		const char	*	key;
		const char	*	value;
	};

	// サービス名称ごとにKEYVALUE一覧を持つ
	struct SERVICE {
		SERVICE	*	prev;
		SERVICE	*	next;

		const char	*	service_name;

		KEYVALUE	*	begin;
		KEYVALUE	*	end;
	};

	SERVICE		*	m_begin;
	SERVICE		*	m_end;
};

#endif // CWin32KeyChain_h
