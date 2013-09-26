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
//
//  CiOSHttpStream.cpp
//  GameEngine
//
//

#include "CiOSHttpStream.h"

CiOSHttpStream::CiOSHttpStream() : m_fullpath(0), m_bufHTTP(0) {}
CiOSHttpStream::~CiOSHttpStream()
{
    delete [] m_bufHTTP;
    delete [] m_fullpath;
}

CiOSHttpStream *
CiOSHttpStream::openStream(const char *path, const char *home)
{
    CiOSHttpStream * pStream = 0;
    pStream = new CiOSHttpStream();
    
    if(!pStream) {
        return 0;
    }
    pStream->m_fullpath = 0;
    char * buf = new char [ strlen(path) + 1 ];
    if(!buf) {
        pStream->m_eStat = NOT_FOUND;
        return pStream;
    }
    strcpy(buf, path);
    pStream->m_fullpath = (const char *)buf;
    // HTTP/HTTPSアクセスでリソースを取得する
    
        
}