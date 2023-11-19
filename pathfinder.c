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
    int routes_count = 0, routes_done = 0;

    printf("~~~ Start with %d routes ~~~\n\n", routes_count); //DEBUG!

    // Generate the starting point(s)
    printf("-=O:: Generate starting points ::O=-\n\n"); //DEBUG!
    int stopA_transferCount = TStop_GetNumberOfTransfers(stopA);
    for (int i = 0; i < stopA_transferCount; ++i) {
        TRoute *newRoute = TRoute_init(stopA, stopA->transfers[i]);
        routes_head = TRoute_push(routes_head, newRoute);
        ++routes_count;
    }

    //DEBUG! Print out all routes_head
    printf("-=O:: Routes after generation ::O=-\n");
    for (TRoute *current = routes_head; current != NULL; current = current->next)
        TRoute_PrintOut(current);
    printf("\n");

    // Find the path
    int iteration_count = 0;
    do {
        routes_done = 0;

        printf("-=O:: Loop count: %d ::O=-\n\n", iteration_count); //DEBUG!

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

            //DEBUG! Check ~TRoute_GetTransfers~ method
            printf("-=O:: Possible transfers: %d ::O=-\n", numOfTransfers); //DEBUG!
            for (int i = 0; i < numOfTransfers; ++i) {
                printf("%s --[%s]->\n", transfer_stops[i]->name, transfer_lines[i]->sign);
            }
            printf("\n");

            //DEBUG!
            printf("-=O:: Before possible ways ::O=-\n");
            TRoute_PrintOut(current_route);

            // Add possible ways to routes
            if (numOfTransfers == 0) {
                routes_head = TRoute_pop(routes_head, current_route);
                current_route = previous_route;
                --routes_count;
            } else printf("-=O:: After possible ways ::O=-\n"); //DEBUG! Only the else
            for (int i = 0; i < numOfTransfers; ++i) {
                if (i > 0) {
                    // Add ~copied_route~ to routes array
                    printf("Copy from: "); //DEBUG!
                    TRoute_PrintOut(current_route); //DEBUG!
                    TRoute *copied_route = TRoute_copy(current_route);
                    printf("Copy to (copied): "); //DEBUG!
                    TRoute_PrintOut(copied_route); //DEBUG!
                    previous_route = current_route;
                    current_route = copied_route;
                    previous_route->next = current_route;
                    current_route->next = next_route;
                    printf("Copy to (current): "); //DEBUG!
                    TRoute_PrintOut(current_route); //DEBUG!
                    ++routes_count;
                }
                TRoute_addData(current_route, transfer_stops[i], transfer_lines[i]);

                TRoute_PrintOut(current_route); //DEBUG!
            }
            printf("\n"); //DEBUG!

            // Free possible transfers arrays
            free(transfer_stops);
            free(transfer_lines);
        }

        //DEBUG! Print out all routes_head
        printf("-=O:: Routes at loop end [%d;%d] ::O=-\n", routes_count, routes_done);
        for (TRoute *current = routes_head; current != NULL; current = current->next)
            TRoute_PrintOut(current);
        printf("\n");

        ++iteration_count;
    } while (routes_count > routes_done && iteration_count < MAX_ITERATIONS);

    printf("~~~ End with %d routes under %d iterations [%d;%d] ~~~\n\n", routes_count, iteration_count, routes_count, routes_done); //DEBUG!

    // Print out all routes_head
    for (TRoute *current = routes_head; current != NULL; current = current->next)
        TRoute_PrintOut(current);

    // Free all routes_head!
    TRoute_freeArray(routes_head);
}
