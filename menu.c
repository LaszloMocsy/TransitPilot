#include "menu.h"

extern TStop *allStops_head;
extern TLine *allLines_head;

void ProgramLoop() {
    char *items[6] = {
            "List all stops",
            "List all lines",
            "Modify stop A",
            "Modify stop B",
            "Search for route(s)",
            "Exit program"
    };

    int selectedItem;
    do {
        do {
            ClearConsole();
            PrintBlock_Default("Main Menu");
            selectedItem = ItemSelector("Choose an action:", items, 6, 6, TextAlignLeft);
        } while (selectedItem == -1);

        // Exit program
        if (selectedItem != 5) {
            ClearConsole();
            switch (selectedItem) {
                case 0:
                    PrintBlock_Default("List all stops");
                    WaitForEnter();
                    break;
                case 1:
                    PrintBlock_Default("List all lines");
                    WaitForEnter();
                    break;
                case 2:
                    PrintBlock_Default("Modify stop A");
                    WaitForEnter();
                    break;
                case 3:
                    PrintBlock_Default("Modify stop B");
                    WaitForEnter();
                    break;
                case 4:
                    PrintBlock_Default("Search for route(s)");
                    WaitForEnter();
                    break;
                default:
                    break;
            }
        }
    } while (selectedItem != 5);
}
