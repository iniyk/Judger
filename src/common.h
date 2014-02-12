#ifndef _JUDGER_COMMON_
#define _JUDGER_COMMON_

#ifdef __DEBUG__
    
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <time.h>

#include <map>
#include <vector>
#include <string>

#include <unistd.h>
#include <sysexits.h>
#include <syscall.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "policy.h"

namespace Judger{
    typedef std::string String;
    typedef std::map<String, int> LimitMap;
    typedef std::vector<string> StrVector;
    
    const int MAX_FILE_PATH = 1024;
    const int MAX_STR_LENGTH = 1024;
    const int MAX_ARG_NUMBER = 20;
    const int MAX_PROGRAM_OUTPUT = 4096;
    const int MAX_INT_LENGTH = 40;
    const int MAX_INT64 = 32767;
    
    const int AUTO_TIME_LIMIT = 5000000;            //5sec
    const int AUTO_MEMORY_LIMIT = 32*1024*1024;     //32MB
    const int AUTO_DISK_LIMIT = 32*1024*1024;       //32MB
    
    const String config_file_path("/etc/Judger/Judger.conf");
    const String player_log_file_path("/var/Judger/player.log");
    
    typedef void (*LogFunc)(const String&);
    
    void setup_var() {
        init_banlist();
    }
    
    void silent_log_func(const String &str) {
        //nothing will be done
    }

    void seperate(const String &str, StrVector &res, char sep = ' ') {
        int len = str.length();
        char buffer[MAX_STR_LENGTH];
        int now = 0;
        
        res.clean();
        
        for (int i=0; i<len; ++i) {
            if (str[i]==sep || (sep=='\n' && str[i]=='\r')) {
                if (now>0) {
                    buffer[now] = 0;
                    res.push_back(String(buffer));
                    now = 0;
                }
            } else {
                buffer[now++] = str[i];
            }
        }
        
        if (now>0) {
            buffer[now] = 0;
            res.push_back(String(buffer));
            now = 0;
        }
    }
    
    String int2string(int x) {
        char tmp[MAX_INT_LENGTH];
        sprintf(tmp, "%d", x);
        String ret = tmp;
        return ret;
    }
    
    int limitstring2resource(const String &limit_str) {
        if (limit_str == "TIME") {
            return RLIMIT_CPU;
        }
        if (limit_str == "MEMORY") {
            return RLIMIT_DATA;
        }
        if (limit_str == "FILE") {
            return RLIMIT_NOFILE;
        }
        if (limit_str == "PROCESS") {
            return RLIMIT_NPROC;
        }
        if (limit_str == "STACK") {
            return RLIMIT_STACK;
        }
    }
    
    inline bool alphaornumber(char x) {
        if (x>='a' && x<='z') return true;
        if (x>='A' && x<='Z') return true;
        if (x>='0' && x<='9') return true;
        return false;
    }
    
    unsigned long ts2ms(struct timespec ts) {
        return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    }
    
    /* convert syscall_t to 15bit sc_table index */
    int16_t sc2idx(syscall_t scinfo) {
#ifdef __x86_64__
        assert((scinfo.scno >= 0) && (scinfo.scno < 1024) && 
            (scinfo.mode >= 0) && (scinfo.mode < 32));
        return (int16_t)(scinfo.scno | (scinfo.mode << 10));
#else /* __i386__ */
        assert((scinfo >= 0) && (scinfo < 1024));
        return (int16_t)(scinfo);
#endif /* __x86_64__ */
    }

    /* tag syscall number with linux32 abi mask */
    int16_t abi32(int scno) {
        assert((scno >= 0) && (scno < 1024));
#ifdef __x86_64__
        return (int16_t)(scno | (1 << 10));
#else /* __i386__ */
        return (int16_t)(scno);
#endif /* __x86_64__ */
    }
}

#endif