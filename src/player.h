#include "common.h"

namespace Judger{
    class Player
    {
    public:
        void reset(char *argv[]);
        void 

    private:
        Config config;
        BoxRunner boxrunner;
        String player_name;
        clock_t last_clock;
        
        String exec_path;
        int time_limit, memory_limit, step_time_limit;
        int if_interaction, if_overlord;

        char buffer[MAX_STR_LENGTH];
        char program_buffer[MAX_PROGRAM_OUTPUT];
        
        void LOG(const String &str);
        void setup_boxrunnrt();
        void overlord_startup();
        void player_startup();
        void runonce_startup();
    };
}