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
    printf("-=O:: Generate starting points ::O=-\n\n"); //DEBUG!
    int stopA_transferCount = TStop_GetNumberOfTransfers(stopA);
    for (int i = 0; i < stopA_transferCount; ++i) {
        TRoute *newRoute = TRoute_init(stopA, stopA->transfers[i]);
        routes_head = TRoute_push(routes_head, newRoute);
    }

    //DEBUG! Print out all routes_head
    printf("-=O:: Routes after generation ::O=-\n");
    for (TRoute *current = routes_head; current != NULL; current = current->next)
        TRoute_PrintOut(current);

    // Find the path
    for (int loop_count = 1; loop_count <= 2; ++loop_count) { //DEBUG! Change to: while not all routes are finished
        printf("-=O:: Loop count: %d ::O=-\n\n", loop_count); //DEBUG!
        // Loop through all routes
        // [current_route]: The currently selected route
        for (TRoute *current_route = routes_head; current_route != NULL; current_route = current_route->next) {
            // Check if route is finished (DO NOT TOUCH)
            if (TRoute_IsDone(current_route))
                continue;

            // Is stop B on the route (the route can be finished)
            if (TRoute_IsStopOnRoute(current_route, stopB)) {
                TRoute_addData(current_route, stopB, NULL);
                continue;
            }

            // Find all transfers
            TStop **transfer_stops = NULL;
            TLine **transfer_lines = NULL;
            int numOfTransfers = TRoute_GetTransfers(current_route, &transfer_stops, &transfer_lines);

            //DEBUG! Check ~TRoute_GetTransfers~ method
            printf("-=O:: Possible transfers: %d ::O=-\n", numOfTransfers); //DEBUG!
            for (int i = 0; i < numOfTransfers; ++i) {
                printf("%s --[%s]->\n", transfer_stops[i]->name, transfer_lines[i]->sign);
            }
            printf("\n");

            // Add possible ways to routes
            if (numOfTransfers == 1)
                TRoute_addData(current_route, transfer_stops[0], transfer_lines[0]);
            //TODO: Expend this to multiple and zero possible ways

            // Free possible transfers arrays
            free(transfer_stops);
            free(transfer_lines);
        }

        //DEBUG! Print out all routes_head
        printf("-=O:: Routes at loop end ::O=-\n");
        for (TRoute *current = routes_head; current != NULL; current = current->next)
            TRoute_PrintOut(current);
        printf("\n");
    }

    // Print out all routes_head
    for (TRoute *current = routes_head; current != NULL; current = current->next)
        TRoute_PrintOut(current);

    // Free all routes_head!
    TRoute_freeArray(routes_head);
}
