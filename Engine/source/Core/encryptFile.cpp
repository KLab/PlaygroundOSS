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
// ---------------------------------------------------------------
#include <string.h>
#include "encryptFile.h"

/*!
    @brief  コンストラクタ
 */
CDecryptBaseClass::CDecryptBaseClass()
: m_decrypt	(false)
, m_useNew	(false)
{
	// User context.
	// m_userCtx.members = initValue
}

/*!
    @brief  複合化
    @param[in]  void* ptr       暗号化されたデータ
    @param[in]  u32 length      データの長さ
    @return     void
 */
void CDecryptBaseClass::decrypt(void* ptr, u32 length) {
	// "Transparent" encryption : do nothing.
}

/*!
    @brief  複合化準備
    @param[in]  const u8* ptr   ファイルパス
    @return     void
 */
u32 CDecryptBaseClass::decryptSetup(const u8* ptr, const u8* hdr) {
	// m_userCtx.m_rot	= 0;
	// if (hdr[0] == MAGIC_BYTE0 && hdr[2] == MAGIC_BYTE1 && hdr[3] == MAGIC_BYTE2 && hdr[3] == MAGIC_BYTE3) {
	// 		m_useNew = true;
	// } else {
			m_useNew = false;
	// }
	m_decrypt	= true;
    //m_decrypt = false;
	return m_useNew ? 1 : 0;
}

void CDecryptBaseClass::gotoOffset(u32 offset) {
	// Recompute and update your encryption context if we jump at a certain position into the encrypted stream.
	// gotoOffset is ALWAYS called BEFORE decrypt if a jump in the decoding stream occurs.
}
