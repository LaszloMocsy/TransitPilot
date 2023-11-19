#include "pathfinder.h"

#define MAX_ITERATIONS 20

void FindPath(TStop *stopA, TStop *stopB) {
    if (stopA == NULL || stopB == NULL) {
        printf("Stop A and B cannot be empty!\n\n");
        return;
    } else if (strcmp(stopA->name, stopB->name) == 0) {
        printf("Stop A and B cannot be the same!\n\n");
        return;
    }

    TRoute *routes_head = NULL;
    int routes_count = 0, routes_done = 0, iteration_count = 0;

    // Generate the starting point(s)
    int stopA_transferCount = TStop_GetNumberOfTransfers(stopA);
    for (int i = 0; i < stopA_transferCount; ++i) {
        TRoute *newRoute = TRoute_init(stopA, stopA->transfers[i]);
        routes_head = TRoute_push(routes_head, newRoute);
        ++routes_count;
    }

    // Find the path
    do {
        routes_done = 0;

        // Loop through all routes
        for (TRoute *previous_route = NULL, *current_route = routes_head, *next_route = current_route->next;
             current_route != NULL || next_route != NULL;
             previous_route = current_route, current_route = next_route,
             next_route = current_route != NULL ? current_route->next : NULL) {
            // Check if route is finished (DO NOT TOUCH)
            if (TRoute_IsDone(current_route)) {
                ++routes_done;
                continue;
            }

            // Is stop B on the route (the route can be finished)
            if (TRoute_IsStopOnRoute(current_route, stopB)) {
                TRoute_addData(current_route, stopB, NULL);
                ++routes_done;
                continue;
            }

            // Find all transfers
            TStop **transfer_stops = NULL;
            TLine **transfer_lines = NULL;
            int numOfTransfers = TRoute_GetTransfers(current_route, &transfer_stops, &transfer_lines);

            // Add possible ways to routes
            if (numOfTransfers == 0) {
                routes_head = TRoute_pop(routes_head, current_route);
                current_route = previous_route;
                --routes_count;
            }
            for (int i = 0; i < numOfTransfers; ++i) {
                if (i > 0) {
                    // Add ~copied_route~ to routes array
                    TRoute *copied_route = TRoute_copy(current_route);
                    previous_route = current_route;
                    current_route = copied_route;
                    previous_route->next = current_route;
                    current_route->next = next_route;
                    ++routes_count;
                }
                TRoute_addData(current_route, transfer_stops[i], transfer_lines[i]);
            }

            // Free possible transfers arrays
            free(transfer_stops);
            free(transfer_lines);
        }

        ++iteration_count;
    } while (routes_count > routes_done && iteration_count < MAX_ITERATIONS);

    // Print out all routes_head
    printf("Between %s and %s, %d route has been found.\n", stopA->name, stopB->name, routes_count);
    int id = 1;
    for (TRoute *current = routes_head; current != NULL; current = current->next) {
        printf("\n%d. route; Travelling time: %dm; Line change: %d\n", id, TRoute_GetTravellingTime(current),
               TRoute_GetNumberOfLines(current) - 1);
        TRoute_PrintOut(current);
        ++id;
    }

    // Free all routes_head!
    TRoute_freeArray(routes_head);
}
