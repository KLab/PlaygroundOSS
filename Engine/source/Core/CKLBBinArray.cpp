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
#include "CPFInterface.h"
#include "CKLBBinArray.h"
#include "CKLBUtility.h"
;
CKLBBinArray	*	CKLBBinArray::ms_begin	= 0;
CKLBBinArray	*	CKLBBinArray::ms_end	= 0;

CKLBBinArray::CKLBBinArray() : m_size(0), m_pBuf(0), m_prev(0), m_next(0), m_name(0)
{
	m_prev = ms_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		ms_begin = this;
	}
	ms_end = this;
}

CKLBBinArray::~CKLBBinArray()
{
	KLBDELETEA(m_pBuf);
	KLBDELETEA(m_name);

	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		ms_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		ms_end = m_prev;
	}
}

u32
CKLBBinArray::getClassID()
{
	return CLS_KLBBINARRAY;
}


void
CKLBBinArray::removeAll()
{
	CKLBBinArray * pBIN = ms_begin;
	while(pBIN) {
		CKLBBinArray * pNXT = pBIN->m_next;
		KLBDELETE(pNXT);
		pBIN = pNXT;
	}
}

bool
CKLBBinArray::dumpAll()
{
	bool bResult = false;
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	CKLBBinArray * pBIN = ms_begin;
	while(pBIN) {
		pForm.logging("[BIN]<%p>: %s", pBIN, pBIN->m_name);
		pBIN = pBIN->m_next;
		bResult = true;
	}
	return bResult;
}

bool
CKLBBinArray::loadAsset(const char * path)
{
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();
	IReadStream * pStream = pfif.openReadStream(path, pfif.useEncryption());
	if(!pStream || pStream->getStatus() != IReadStream::NORMAL) {
		delete pStream;
		return false;
	}

	size_t size = pStream->getSize();
	u8 * pBuf = KLBNEWA(u8, size);
	if(!pBuf) {
		delete pStream;
		return false;
	}
	pStream->readBlock(pBuf, size);
	delete pStream;

	m_size = size;
	m_pBuf = pBuf;
	m_name = CKLBUtility::copyString(path);	// �p�X�𖼏̂ɂ���

	return true;
}
