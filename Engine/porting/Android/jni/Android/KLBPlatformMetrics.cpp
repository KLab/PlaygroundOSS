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
#include <sys/types.h>
#include <unistd.h>

#include "BaseType.h"
#include "KLBPlatformMetrics.h"

KLBPlatformMetrics::KLBPlatformMetrics() :
last_rss(-1),
log_buf_len(1024),
log_suffix(0),
logging_enabled(true),
signals_patched(false),
device_ident(NULL),
device_ident_len(0),
log_fp(NULL)
{
}

KLBPlatformMetrics::~KLBPlatformMetrics() {
}

KLBPlatformMetrics* KLBPlatformMetrics::getInstance() {
	static KLBPlatformMetrics metrics;
	return &metrics;
}

void KLBPlatformMetrics::patchSignals() {
}

void KLBPlatformMetrics::signalHandler(int signal, siginfo_t *info, void *reserved) {
}

void KLBPlatformMetrics::unpatchSignals() {
}

void KLBPlatformMetrics::start() {
}

void KLBPlatformMetrics::stop() {
}

s32 KLBPlatformMetrics::ReportingThreadParam(void * hThread, void * data)
{
    return 0;
}

s32 KLBPlatformMetrics::PostingThreadParam(void * hThread, void * data)
{
    return 0;
}

void KLBPlatformMetrics::rotateLog(bool is_lock_gained) {
}

int KLBPlatformMetrics::uploadLogs(bool is_terminating) {
	return 0;
}

int KLBPlatformMetrics::rotateAndUploadLog(bool is_terminating) {
	return 0;
}

void KLBPlatformMetrics::appendLog(const char* msg, int msg_len, u8 msg_type) {
}

void KLBPlatformMetrics::reportImmediately(const char* msg) {
}

int KLBPlatformMetrics::getFdCount() {
	return 0;
}

void KLBPlatformMetrics::getOrGenerateDeviceIdent(const char* basefile_path) {
}

int KLBPlatformMetrics::generateDeviceIdent(char* outbuf, int buflen)
{
	return 0;
}

inline int KLBPlatformMetrics::logMeasuringThreadCpu(u16 target) {
	return 0;
}

void KLBPlatformMetrics::measureThreadCpu(u16 target) {
}

void KLBPlatformMetrics::logFrameSummary(int deltaT, s64 frameProcStart) {
}
