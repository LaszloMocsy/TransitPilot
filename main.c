#include "load.h"
#include "tstop.h"
#include "tline.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    TStopsArray stopsArray = {0, NULL};
    TLinesArray linesArray = {0, NULL};

    if (argc != 2) {
        perror("[E_0x1]: No configuration file was provided!");
        return 1;
    }

    bool _loop = LoadConfiguration(argv[1], &stopsArray, &linesArray);
    if (!_loop) return 2;

    while (_loop) {
        printf("Choose one of the following actions:\n"
               "[ 1 ]  List all stops (%d)\n"
               "[ 2 ]  List all lines (%d)\n"
               "[ 3 ]  Modify starting stop\n"
               "[ 4 ]  Modify ending stop\n"
               "[ 5 ]  Plan a route\n"
               "[ 0 ]  Exit program\n",
               stopsArray.count,
               linesArray.count);
        int action;
        do {
            printf("> ");
            scanf("%d", &action);
            switch (action) {
                case 1:
                    ListAllStops(stopsArray, linesArray);
                    break;
                case 2:
                    ListAllLines(linesArray, stopsArray);
                    break;
                case 3:
                    printf("\n--> Modify starting stop\n\n");
                    break;
                case 4:
                    printf("\n--> Modify ending stop\n\n");
                    break;
                case 5:
                    printf("\n--> Plan a route\n\n");
                    break;
                case 0:
                    _loop = false;
                    break;
                default:
                    // Invalid action was submitted, it will ask again for an action
                    break;
            }
        } while (action != 0 && !(action >= 1 && action <= 4));
    }

    TStopsArray_free(&stopsArray);
    TLinesArray_free(&linesArray);
    return 0;
}