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

    int routes_count = 0;
    Route *routes = NULL;

    // Generate the starting point(s)
    for (int i = 0; i < stops->items[stopA_id]->transferCount; ++i) {
        routes = (Route *) realloc(routes, sizeof(Route) * ++routes_count);
        int *spStops = malloc(sizeof(int));
        int *spLines = malloc(sizeof(int));

        spStops[0] = stopA_id;
        spLines[0] = stops->items[stopA_id]->transfers[i];

        Route newStartingPoint = {spStops, spLines, 1, 1};
        routes[i] = newStartingPoint;
    }

    // Extend each routes' end
    for (int i = 0, iMax = routes_count; i < iMax; ++i) {
        Route *currentRoute = &routes[i];
        if (currentRoute->stops_count == currentRoute->lines_count) {
            int lastStop_id = currentRoute->stops[currentRoute->stops_count - 1];
            if (IsStopsOnSameLine(*stops->items[lastStop_id], *stops->items[stopB_id])) {
                currentRoute->stops = (int *) realloc(currentRoute->stops, sizeof(int) * ++currentRoute->stops_count);
                currentRoute->stops[currentRoute->stops_count - 1] = stopB_id;
            }
        } // else, the route has been found (do not touch the route)
    }

    //DEBUG: Print out all the starting point (routes)
    for (int i = 0; i < routes_count; ++i) {
        printf("%d. ", i);
        Route *currentRoute = &routes[i];
        for (int j = 0; j < currentRoute->stops_count; ++j) {
            printf(" %s", stops->items[currentRoute->stops[j]]->name);
            if (j < currentRoute->lines_count)
                printf(" --[%s]->", lines->items[currentRoute->lines[j]]->sign);
        }
        printf("\n");
    }
    printf("\n");

    //FIXME: Free all routes!
}
