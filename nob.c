
#define NOB_IMPLEMENTATION
#include "nob.h"

#define LIBRARY_DUKTAPE_PATH "Libraries/duktape/src"
#define LIBRARY_DUKTAPE_EXTRAS_PATH "Libraries/duktape/extras/module-duktape"
#define SCRIPTS_DIR "./Deployment/assets"
#define change_dir _chdir

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    // "-Wall", "-Wextra"
    nob_cmd_append(&cmd, "clang","-ggdb3","-I.","-I"LIBRARY_DUKTAPE_PATH,"-I"LIBRARY_DUKTAPE_EXTRAS_PATH,LIBRARY_DUKTAPE_EXTRAS_PATH"/duk_module_duktape.c" , LIBRARY_DUKTAPE_PATH"/duktape.c", "-o", "./Deployment/dtsc.exe", "./src/main.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    // change_dir(SCRIPTS_DIR);
    // nob_cmd_append(&cmd,"powershell","../../node_modules/.bin/tsc.ps1","--target","ES5", "dtsc.ts");
    // if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    // change_dir("../..");
    return 0;
}