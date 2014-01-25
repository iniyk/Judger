/*
 * Class Name : Compiler
 * Func : 
 *   Compile user's program in the way which could be watched by another thread.
 *   Supplied language : C, CPP, Java, Python
 *   Other's could add other language simplyly register by Register(), and add a .cmp file.
 */
#ifndef _JUDGER_COMPILER_
#define _JUDGER_COMPILER_

#include "common.h"

namespace Judger{

    typedef std::pair<String, String> CompileOpt;
    typedef std::vector<CompileOpt> CmpOptArr;
    typedef std::vector<string> StrVector;

    struct LangSetting{
        String lang_name;
        String compiler_cmd;
        String output_file_opt;
        CmpOptArr coa;
        LangSetting() {
            coa.clear();
            compiler_cmd = "";
            lang_name = "";
            output_file_opt = "";""
        }
        LangSetting(const String &name, const String &cmd, const String &ofo) {
            lang_name = name;
            compiler_cmd = cmd;
            output_file_opt = ofo;
            coa.clear();
        }
        void init(const String &name, const String &cmd, const String &ofo) {
            lang_name = name;
            compiler_cmd = cmd;
            output_file_opt = ofo;
            coa.clear();
        }
        void regOption(const String &para, const String &var="") {
            CompileOpt co;
            co = make_pair(para, var);
            coa.push_back(co);
        }
    };

    typedef std::vector<LangSetting> LangSettingArr;
    typedef std::map<String, int> LangDirector;

    class Compiler{
    private:
        /*------------------data-----------------*/
        LangSettingArr lsa;
        LangDirector ld;
        LimitMap lm;
        String error_message;
        /*-----------private function------------*/
        /*
         *  Func : Read an cmp file & regist a new compiler by it
         *  Input : [director, cmp_path]
         *          director : id of lsa underlabel
         *          cmp_path : cmp file path
         *  Ret   : 0 normal return
         *          1 cmp file formatting error
         *          2 cmp file path invalid
         */
        int SetupByCmpFile(int director, const String &cmp_path);
    public:
        /*
         * Func : use this function BEFORE using this class
         */
        void init();
        /*
         * Func : set up limits such as time limit & memeory limit by an ini file
         * Input : [ini_file_path]
         *          ini_file_path : setup file path
         * Ret   : 0 normal return
         *         1 ini file formatting error
         *         2 ini file path invalid
         */
        int setupLimits(const String &ini_file_path);
        /*
         * Func : register a new compiler by cmp file
         * Input : [cmp_path]
         *          cmp_path : cmp file path
         * Ret : 0 normal return
         *       1 cmp file formatting error
         *       2 cmp file path invalid
         *       3 language has already been registered
         *
         */
        int Register(const String &cmp_path);
        /*
         * Func : compile target file
         * Input : [lang_name, target_file_path, output_exec_file]
         *          lang_name : language name
         *          target_file_path : target file path
         *          output_exec_file : output execute file path
         * Ret : 0 normal return
         *       1 compile error, error message will be saven & could get it by Error() Func
         *       2 target file invalid
         *       3 language has not been registered
         *
         */
        int Compile(const String &lang_name, const String &target_file_path, const String &output_exec_file);
        /*
         * Func : get last compile error message
         * Ret : if Compile() hasn't been used since last init() it will return ""
         *       if no error occured last Compile() it will return ""
         *       else will get the error message
         *
         */
        String Error();
    };

}

#endif
