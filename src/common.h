#ifndef _JUDGER_COMMON_
#define _JUDGER_COMMON_

#ifdef __DEBUG__
    #include <assert.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>

namespace Judger{
    const int MAX_FILE_PATH = 1024;
    const int MAX_STR_LENGTH = 1024;

    typedef std::string String;
    typedef std::map<String, int> LimitMap;
}
#endif