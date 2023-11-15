#include "load.h"
#include "types/tstop_t.h"
#include "types/tline_t.h"
#include "menu.h"
#include "pathfinder.h"

int main(int argc, char *argv[]) {
    TStopsArray stopsArray = {0, NULL};
    TLinesArray linesArray = {0, NULL};
    int stopA = -1, stopB = -1;

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
               "[ 3 ]  Modify stop A (%s)\n"
               "[ 4 ]  Modify stop B (%s)\n"
               "[ 5 ]  Plan a route between stop A and B\n"
               "[ 0 ]  Exit program\n",
               stopsArray.count,
               linesArray.count,
               stopA == -1 ? "---" : stopsArray.items[stopA]->name,
               stopB == -1 ? "---" : stopsArray.items[stopB]->name);
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
                    printf("\n=== Modify starting stop ===\n\n");
                    ReadStopId(&stopA, stopsArray.count - 1);
                    break;
                case 4:
                    printf("\n=== Modify ending stop ===\n\n");
                    ReadStopId(&stopB, stopsArray.count - 1);
                    break;
                case 5:
                    printf("\n=== Plan a route ===\n\n");
                    FindPath(&stopsArray, &linesArray, stopA, stopB);
                    break;
                case 0:
                    _loop = false;
                    break;
                default:
                    // Invalid action was submitted, it will ask again for an action
                    break;
            }
        } while (action != 0 && !(action >= 1 && action <= 5));
    }

    TStopsArray_free(&stopsArray);
    TLinesArray_free(&linesArray);
    return 0;
}