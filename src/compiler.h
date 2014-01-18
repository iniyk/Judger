/*
 * Class Name : Compiler
 * Func : 
 *   Compile user's program in the way which could be execute by sandbox.
 *   Supplied language : C, CPP, Java, Python
 *   Other's could add other language simplyly register by Register(), and add a .cmp file.
 */

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

const MAX_FILE_PATH = 1024;

typedef std::string String;
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
    /*-----------private function------------*/
    int SetupByCmpFile(int director, const String &cmp_path);
public:
    void init();
    int Register(const String &cmp_path);
    int Compile(const String &target_file_path, const String &output_exec_file);
};

}
