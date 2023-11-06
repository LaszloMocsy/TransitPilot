#include "load.h"
#include "transit.h"

int main(int argc, char *argv[]) {
    TStopsArray stopsArray = {0, NULL};

    if (argc != 2) {
        perror("[E_0x1]: No configuration file was provided!");
        return 1;
    }

    bool _loop = LoadConfiguration(argv[1], &stopsArray);
    if (!_loop) return 2;

    //DEBUG:START
    printf("\n==: stopsArray count: %d :==\n\n", stopsArray.count);
    for (int i = 0; i < stopsArray.count; ++i) {
        printf("%s :: %d\n", stopsArray.items[i]->name, stopsArray.items[i]->transferCount);
    }
    printf("\n\n");
    //DEBUG:END

    while (_loop) {
        printf("Choose one of the following actions:\n"
               "[ 1 ]  List all lines and stops\n"
               "[ 2 ]  Modify starting stop\n"
               "[ 3 ]  Modify ending stop\n"
               "[ 4 ]  Plan a route\n"
               "[ 0 ]  Exit program\n");
        int action;
        do {
            printf("> ");
            scanf("%d", &action);
            switch (action) {
                case 1:
                    printf("\n--> List all lines and stops\n\n");
                    break;
                case 2:
                    printf("\n--> Modify starting stop\n\n");
                    break;
                case 3:
                    printf("\n--> Modify ending stop\n\n");
                    break;
                case 4:
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
    return 0;
}