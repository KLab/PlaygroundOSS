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
#ifndef H_HEADER_PROTECT_ENCRYPTFILE_H
#define H_HEADER_PROTECT_ENCRYPTFILE_H

#include "BaseType.h"
#include "encryptUserContext.h"

/*!
    @class  DecryptBaseClass
    @brief  複合化基礎クラス
 */
class CDecryptBaseClass {
public:
	SUserStruct	m_userCtx;
	bool		m_decrypt;
	bool		m_useNew;
private:
	void		decrypt(void* ptr, u32 length);
public:
	CDecryptBaseClass();
	inline void decryptBlck(void* ptr, u32 length) {
		if (m_decrypt) { decrypt(ptr, length); }
	}

	u32			decryptSetup(const u8* ptr, const u8* hdr);
	void		gotoOffset	(u32 offset);
};

#endif
