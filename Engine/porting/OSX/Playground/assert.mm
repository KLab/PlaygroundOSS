#include "assert.h"
#include <stdio.h>
#include <stdarg.h>

#include "CPFInterface.h"

#include "CiOSPlatform.h"

extern "C" {
    void assertFunction(int line, const char *file, const char *msg, ...) {
        va_list argp;
        char pszBuf[1024];
        
        va_start(argp, msg);
        vsprintf(pszBuf, msg, argp);
        va_end(argp);
        
        char alertBuf[4096];
        sprintf(alertBuf, "Assert l.%i in %s : %s", line, file, pszBuf);
        NSString *alert_msg = [NSString stringWithCString:alertBuf encoding:NSUTF8StringEncoding];
        
        NSLog(@"%s", alertBuf);
        
        CiOSPlatform *pPlatform = CiOSPlatform::getInstance();
    }
    
    void msgBox(char *log) {
    }
}
