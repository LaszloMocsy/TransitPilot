#include "load.h"
#include "types/tstop_t.h"
#include "types/tline_t.h"
#include "pathfinder.h"

/// Get the TStop from the user
/// \param title The text that needs to be displayed before the process
/// \param maxId The last id in the array
/// \param head The head of the array
/// \return The memory address of the TStop that the user chosen
TStop *GetStopFromInput(const char *title, int maxId, TStop *head);

int main(int argc, char *argv[]) {
    TStop *stops_head = NULL, *stopA = NULL, *stopB = NULL;
    TLine *lines_head = NULL;

    if (argc < 2) {
        perror("[E_0x1]: No configuration file was provided!");
        return 1;
    }

    bool _loop = LoadConfiguration(argv[1], &stops_head, &lines_head);
    if (!_loop) return 2;

    while (_loop) {
        printf("Choose one of the following actions:\n"
               "[ 1 ]  List all stops (%d)\n"
               "[ 2 ]  List all lines (%d)\n"
               "[ 3 ]  Modify stop A (%s)\n"
               "[ 4 ]  Modify stop B (%s)\n"
               "[ 5 ]  Plan a route between stop A and B\n"
               "[ 0 ]  Exit program\n",
               TStop_GetCount(stops_head),
               TLine_GetCount(lines_head),
               stopA == NULL ? "---" : stopA->name,
               stopB == NULL ? "---" : stopB->name);
        int action;
        do {
            printf("> ");
            scanf("%d", &action);
            switch (action) {
                case 1:
                    printf("\n=== Stops (%d) ===\n\n", TStop_GetCount(stops_head));
                    int i = 0;
                    for (TStop *current = stops_head; current != NULL; current = current->next) {
                        printf("%d. %s\n", i, current->name);
                        ++i;
                    }
                    break;
                case 2:
                    printf("\n=== Lines (%d) ===\n\n", TLine_GetCount(lines_head));
                    for (TLine *current = lines_head; current != NULL; current = current->next) {
                        printf("%s :  %s -> %s\n", current->sign, current->stops[0]->name, "...");
                    }
                    break;
                case 3:
                    stopA = GetStopFromInput("Modify starting stop", TStop_GetCount(stops_head) - 1, stops_head);
                    break;
                case 4:
                    stopB = GetStopFromInput("Modify ending stop", TStop_GetCount(stops_head) - 1, stops_head);
                    break;
                case 5:
                    printf("\n=== Route planning ===\n\n");
                    FindPath(stopA, stopB);
                    break;
                case 0:
                    _loop = false;
                    break;
                default:
                    // Invalid action was submitted, it will ask again for an action
                    break;
            }
        } while (action != 0 && !(action >= 1 && action <= 5));
        printf("\n");
    }

    TStop_freeArray(stops_head);
    TLine_freeArray(lines_head);
    return 0;
}

TStop *GetStopFromInput(const char *title, int maxId, TStop *head) {
    printf("\n=== %s ===\n\n", title);
    int inputA;
    do {
        printf("Enter a valid id [0-%d]: ", maxId);
        scanf("%d", &inputA);
    } while (inputA < 0 || inputA > maxId);
    return TStop_GetStopById(head, inputA);
}
