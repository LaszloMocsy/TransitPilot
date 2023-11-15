#include "pathfinder.h"

void FindPath(TStop *stopA, TStop *stopB) {
    if (stopA == NULL || stopB == NULL) {
        printf("Stop A and B cannot be empty!\n\n");
        return;
    } else if (strcmp(stopA->name, stopB->name) == 0) {
        printf("Stop A and B cannot be the same!\n\n");
        return;
    }

    TRoute *routes_head = NULL;

    // Generate the starting point(s)
    int stopA_transferCount = TStop_GetNumberOfTransfers(stopA);
    for (int i = 0; i < stopA_transferCount; ++i) {
        TRoute *newRoute = TRoute_init(stopA, stopA->transfers[i]);
        routes_head = TRoute_push(routes_head, newRoute);
    }

    //TODO: Create loop that finds the path
    int startingCount = TRoute_GetCount(routes_head);
    for (int i = 0; i < startingCount; ++i) {
        /**
         * TODO: Is current route's last line contains stop_B?
         * -> True: Add stop as last stop to route [TRoute is finished]
         * -> False: Copy the route at transferable option times (2 copy if there is 2 transferable lines)
         */
    }

    // Print out all routes_head
    for (TRoute *current = routes_head; current != NULL; current = current->next)
        TRoute_PrintOut(current);

    // Free all routes_head!
    TRoute_freeArray(routes_head);
}
