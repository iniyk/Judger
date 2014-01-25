/*
 * Class Name : BoxRunner
 * Func : 
 *   Run user's program in the way which could be execute by sandbox.
 *   Supplied language : C, CPP, Java, Python
 */
 
#ifndef _JUDGER_COMPILER_
#define _JUDGER_COMPILER_

#include "common.h"
#include "sandbox.h"

namespace Judger{
    typedef std::vector<String> ArgsArray;
    class BoxRunner {
    private:
        LimitMap lm;
        ArgsArray aa;
        String result;
    public:
        /*
         * Func : use this function BEFORE using this class
         */
        void init();
        /*
         * Func : add a limit such as time limit & memeory limit
         * Input : [limit_name, limit_val]
         *          limit_name : limit name
         *          limit_val : limit value
         */
        void addLimit(const String &limit_name, int limit_val);
        /*
         * Func : add a run-time arguement
         * Input : [arg]
         *          arg : run-time arg, such as -t
         *
         */
        void addArg(const String &arg);
        /*
         * Func : run target file
         * Input : [target_path, fd_rd, fd_wt]
         *          target_path : target file path
         *          fd_rd : read file describe code
         *          fd_wt : write file describe code
         * Ret : 0 normal return
         *       1 sandbox error
         *       2 target file invalid
         *
         */
        int Run(const String &target_path, int fd_rd, int fd_wt);
        /*
         * Func : get last run result message
         * Ret : if Run() hasn't been used since last init() it will return ""
         *       else will get the running message : TLE, OLE, RF, MLE, RE, OK
         *
         */
        String Result();
    };
}