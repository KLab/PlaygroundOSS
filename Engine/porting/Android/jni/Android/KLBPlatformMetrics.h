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
#ifndef KLBPlatformMetrics_h
#define KLBPlatformMetrics_h

#include <malloc.h>
#include <pthread.h>
#include <sys/resource.h>
#include <signal.h>

#include "curl.h"
#include "KLBPlatformMetricsCommon.h"

#if defined(DEBUG) || defined(DEBUG_PERFORMANCE)
# undef REPORT_METRICS
# define REPORT_METRICS(msg) KLBPlatformMetrics::getInstance()->reportImmediately(msg)
# undef MEASURE_THREAD_CPU_BEGIN
# define MEASURE_THREAD_CPU_BEGIN(type) KLBPlatformMetrics::getInstance()->measureThreadCpu(TASKTYPE_BEGIN | (type))
# undef MEASURE_THREAD_CPU_END
# define MEASURE_THREAD_CPU_END(type)   KLBPlatformMetrics::getInstance()->measureThreadCpu(TASKTYPE_END   | (type))
#endif

class KLBPlatformMetrics {
public:
	~KLBPlatformMetrics();
    static KLBPlatformMetrics* getInstance();
	static s32 ReportingThreadParam(void * hThread, void * data);
	static s32 PostingThreadParam(void * hThread, void * data);
	void start();
	void stop();
	void reportImmediately(const char* msg = "");
	void appendLog(const char* msg, int msg_len = 0, u8 msg_type = MSGTYPE_RAWLOG);
	void rotateLog(bool is_lock_gained = false);
	int uploadLogs(bool is_terminating = false);
	int rotateAndUploadLog(bool is_terminating = false);
	inline struct sigaction* getDefaultSignalHandlers() { return &default_signal_handlers[0]; }
	void measureThreadCpu(u16 type);
	void logFrameSummary(int deltaT, s64 frameProcStart);

private:
	KLBPlatformMetrics();
	void patchSignals();
	void unpatchSignals();
	static void signalHandler(int signal, siginfo_t *info, void *reserved);
	int getFdCount();
	void getOrGenerateDeviceIdent(const char* basefile_path);
	int generateDeviceIdent(char* outbuf, int buflen);
	int logMeasuringThreadCpu(u16 target);

	bool signals_patched;
    void* reportingThread;
    void* postingThread;
	static const int REPORT_INTERVAL_SEC = 2;
	int page_size;
	long last_rss;
	pthread_mutex_t report_mutex;
	pthread_mutex_t logging_mutex;
	pthread_mutex_t thlog_mutex;
	struct rusage basic_metrics;
	struct mallinfo malloc_info;
	struct sigaction pfmtrx_signal_handler;
	struct sigaction default_signal_handlers[NSIG];
	char* log_buf;
	unsigned log_buf_len;
	int log_suffix;
    const char* log_fullpath;
	CURL* curl_obj;
	bool logging_enabled;
	char* device_ident;
	int device_ident_len;
	FILE* log_fp;
	enum MSGTYPES {
		MSGTYPE_INIT = 1,
		MSGTYPE_RAWLOG = 2,
		MSGTYPE_RES_REPORT = 3,
		MSGTYPE_SCREENSHOT = 4,
		MSGTYPE_THREAD_MEASURE = 5,
		MSGTYPE_FRAME_SUMMARY = 6
	};
};

#endif
