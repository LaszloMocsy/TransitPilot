#include "menu.h"

void ProgramLoop() {
    PrintBlock_Default("Main Menu");
    char *items[5] = {
            "List all stops",
            "List all lines",
            "Modify stop A",
            "Modify stop B",
            "Search for route(s)"
    };
    ItemSelector("Choose an action:", items, 5, TextAlignLeft);
}
