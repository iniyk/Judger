#include "compiler.h"

using namespace Judger;

int Compile::SetupByCmpFile(int director, const String &cmp_path) {
    FILE *cmp_file;
    char str_cmp_file_path[MAX_FILE_PATH];
    str_cmp_file_path = cmp_path.c_str();
    cmp_file = fopen(str_cmp_file_path, "r");
    
    if (cmp_file == NULL) return 2;
    LangSetting &lst = lsa[director];

    String lang_name, compiler_cmd, output_file_opt;
    char chrBuff[MAX_STR_LENGTH];
    //Read lang name
    if (fscanf(cmp_file, "%s", chrBuff) == EOF) {
        return 1;
    }
    lang_name = chrBuff;
    //Read compiler command
    if (fscanf(cmp_file, "%s", chrBuff) == EOF) {
        return 1;
    }
    compiler_cmd = chrBuff;
    //Read output file option
    if (fscanf(cmp_file, "%s", chrBuff) == EOF) {
        return 1;
    }
    output_file_opt = chrBuff;

    lst.init(lang_name, compiler_cmd);
    //Read other options
    while (!feof(cmp_file)) {
        int k;
        fscanf(cmp_file, "%d", &k);
        if (k<=0) {
            return 1;
        }
        String para, opt;
        opt = "";
        if (fscanf(cmp_file, "%s", chrBuff) == EOF) {
            return 1;   
        }
        para = chrBuff;
        for (int i=1; i<k; ++i) {
            if (fscanf(cmp_file, "%s", chrBuff) == EOF) {
                return 1;
            }
            opt += chrBuff;
        }
        lst.regOption(para, opt);
    }

    close(cmp_file);
    return 0;
}

void Compiler::init() {
    lsa.clear();
    ld.clear();
}

int Compiler::Register(const String &cmp_file) {
   int dir = lsa.size();
   LangSetting ls_empty;
   lsa.push_back(ls_empty);
   int ret = SetupByCmpFile(dir, cmp_file);
   if (ret != 0) {
        lsa.pop_back();
        return ret;
   }
   if (ld.count(lsa[dir].lang_name) == 0) {
       ld[lsa[dir].lang_name] = dir;
       return 0;
   } else {
       lsa.pop_back();
       return 3;
   }
}

int Compiler::Compile(const String &target_file_path, const String output_exec_file) {
    
}
