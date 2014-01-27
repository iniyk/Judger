#ifndef _JUDGER_CONFIG_
#define _JUDGER_CONFIG_

#include "common.h"

namespace Judegr{
    class Config{
    public:
        Config();
        int init(const String &file_path);
        int selectSection(const String &section);
        int getSection(const StrVector &pararr, const StrVector &valarr);
        String getConfig(const String &par);
    private:
        typedef std::map<String, String> ConfigSectionData;
        
        struct Section{
            String section_name;
            ConfigSectionData cd;
            Section() {
                cd.clear();
            }
            Section(const String &name) {
                section_name = name;
                cd.clear();
            }
            void Set(const String &par, const String &val) {
                cd[par] = val;
            }
            String Get(const String &par) {
                if (cd.count(par)) {
                    return cd[par];
                }
                return "";
            }
        };
        
        typedef std::vector<Section> Data;
        Data data;
        String section_now;
    };
}

#endif