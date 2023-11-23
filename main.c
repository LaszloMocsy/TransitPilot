#include "load.h"
#include "types/tstop_t.h"
#include "types/tline_t.h"
#include "menu.h"
#include "lib/econio.h"

TStop *allStops_head = NULL;
TLine *allLines_head = NULL;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("[E_0x1]: No configuration file was provided!");
    } else if (!LoadConfiguration(argv[1], &allStops_head, &allLines_head)) {
        perror("[E_0x3]: Config file loading has failed!");
    } else {
        econio_set_title("Transit Pilot v1");
        ClearConsole();
        ProgramLoop();

        printf("\n");
        econio_textcolor(COL_DARKGRAY);
        PrintString("Program terminated!", "", "", CONSOLE_WIDTH, TextAlignRight, true);
        econio_sleep(2);
    }

    TStop_freeArray(allStops_head);
    TLine_freeArray(allLines_head);
    return 0;
}
