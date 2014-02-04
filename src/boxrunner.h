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
    class BoxRunner {
    public:
        BoxRunner();
        /**
         * reset this object
         */
        void reset();
        /**
         * add a limit such as time limit & memeory limit
         * @param limit_name  limit name
         * @param limit_val  limit value
         */
        void addLimit(const String &limit_name, int limit_val);
        /**
         * add a run-time arguement
         * @param arg run-time arg, such as -t
         */
        void addArg(const String &arg);
        /**
         * run target file
         * @param  target_path target file path
         * @param  fd_rd       read file describe code
         * @param  fd_wt       write file describe code
         * @return             0 normal return\n
         *                     1 sandbox error\n
         *                     2 target file invalid
         */
        int Run(const String &target_path, int fd_rd, int fd_wt);
        /**
         * get last run result message
         * @return if Run() hasn't been used since last init() it will return ""\n
         *         else will get the running message : TLE, OLE, RF, MLE, RE, OK
         */
        String Result();
    private:
        //Sandbox Defination
        const String result_name[] = {"PD", "OK", "RF", "ML", "OL", "TL", "RT", "AT", "IE", "BP", NULL};
        typedef action_t* (*rule_t)(const sandbox_t*, const event_t*, action_t*);
        typedef struct
        {
           sandbox_t sbox;
           policy_t default_policy;
           rule_t sc_table[INT16_MAX + 1];
        } minisbox_t;
        typedef enum
        {
            P_ELAPSED = 0, P_CPU = 1, P_MEMORY = 2,
        } probe_t;
        //Sandbox Function
        res_t probe(const sandbox_t* psbox, probe_t key);
        void policy(const policy_t*, const event_t*, action_t*);
        action_t* _KILL_RF(const sandbox_t*, const event_t*, action_t*);
        action_t* _CONT(const sandbox_t*, const event_t*, action_t*);
        
        typedef std::vector<String> ArgsArray;

        LimitMap lm;
        ArgsArray aa;
        String result;
    };
}