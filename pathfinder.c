#include "pathfinder.h"

/// Check if the two given stops are on tha same line
/// \param stopA <c>TStop</c> from all the stops
/// \param stopB Second <c>TStop</c> from all the stops
/// \return <c>true</c>, if the two stops are on the same line, otherwise <c>false</c>
bool IsStopsOnSameLine(TStop stopA, TStop stopB) {
    for (int i = 0; i < stopA.transferCount; ++i) {
        for (int j = 0; j < stopB.transferCount; ++j) {
            if (stopA.transfers[i] == stopB.transfers[j])
                return true;
        }
    }
    return false;
}

/// Plans a rout from stop A to B and returns the route's specs
/// \param stops The array that contains all <c>TStop</c>s
/// \param lines The array that contains all <c>TLine</c>s
/// \param stopA_id The id of stop A
/// \param stopB_id The id of stop B
void FindPath(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id) {
    if (stopA_id == -1 || stopB_id == -1) {
        printf("Stop A and B cannot be empty!\n\n");
        return;
    } else if (stopA_id == stopB_id) {
        printf("Stop A and B cannot be the same!\n\n");
        return;
    }

    Route *routes = NULL;

    // Generate the starting point(s)
    for (int i = 0; i < stops->items[stopA_id]->transferCount; ++i) {
        Route *newRoute = Route_init(stopA_id, stops->items[stopA_id]->transfers[i]);
        routes = Route_push(routes, newRoute);
    }

    //TODO: Create loop that finds the path
    int startingCount = Route_GetCount(routes);
    for (int i = 0; i < startingCount; ++i) {
        /**
         * TODO: Is current route's last line contains stop_B?
         * -> True: Add stop as last stop to route [Route is finished]
         * -> False: Copy the route at transferable option times (2 copy if there is 2 transferable lines)
         */
    }

    //DEBUG: Print out all routes
    for (Route *currentRoute = routes; currentRoute != NULL; currentRoute = currentRoute->next) {
        Route_PrintOut(currentRoute, stops, lines);
        printf("\n");
    }
    printf("\n");

    // Free all routes!
    for (Route *current = routes, *next = current->next;
         current != NULL; current = next, next = current == NULL ? NULL : current->next)
        Route_free(current);
}
