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
//  CiOSSysResource.h
//  GameEngine
//
//

#ifndef CiOSSysResource_h
#define CiOSSysResource_h

class CiOSSysResource
{
private:
    CiOSSysResource();
    virtual ~CiOSSysResource();
public:
    static CiOSSysResource& getInstance();

    void requestDevID();
    bool failedDevID();
    bool setDevID(const void * devToken);
    int getDevID(char * retBuf, int maxlen);

    inline bool isReceived() { return m_devId_received; }
    inline bool isSucceed() { return m_devId_succeed; }

private:
    unsigned char       m_devId[32];
    int                 m_size_devId;
    bool                m_devId_received;
    bool                m_devId_succeed;
};

#endif
