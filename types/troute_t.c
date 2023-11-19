#include "troute_t.h"

/* Primary functions */

TRoute *TRoute_init(TStop *stop, TLine *line) {
    TRoute *newRoute = (TRoute *) malloc(sizeof(TRoute));
    newRoute->stops = (TStop **) malloc(sizeof(TStop *) * 2);
    newRoute->stops[0] = stop;
    newRoute->stops[1] = NULL;
    newRoute->lines = (TLine **) malloc(sizeof(TLine *) * 2);
    newRoute->lines[0] = line;
    newRoute->lines[1] = NULL;
    newRoute->next = NULL;
    return newRoute;
}

void TRoute_free(TRoute *route) {
    if (route == NULL) return;
    free(route->stops);
    free(route->lines);
    free(route);
}

void TRoute_freeArray(TRoute *head) {
    if (head == NULL) return;
    for (TRoute *current = head, *next = current->next;
         current != NULL; current = next, next = current == NULL ? NULL : current->next)
        TRoute_free(current);
}

TRoute *TRoute_push(TRoute *head, TRoute *route) {
    if (route == NULL) return head;
    else if (head == NULL) return route;

    TRoute *last = head;
    while (last->next != NULL) last = last->next;
    last->next = route;
    return head;
}

TRoute *TRoute_pop(TRoute *head, TRoute *route) {
    if (route == NULL) return head;
    else if (head == NULL) return NULL;

    for (TRoute *current = head, *previous = NULL; current != NULL; previous = current, current = current->next) {
        if (current == route) {
            if (previous == NULL) {
                TRoute *temp = current->next;
                free(current);
                return temp;
            } else {
                previous->next = current->next;
                free(current);
                return head;
            }
        }
    }
    return head;
}

void TRoute_addData(TRoute *route, TStop *stop, TLine *line) {
    if (stop != NULL) {
        int stops_count = TRoute_GetNumberOfStops(route) + 2;
        route->stops = (TStop **) realloc(route->stops, sizeof(TStop *) * stops_count);
        route->stops[stops_count - 2] = stop;
        route->stops[stops_count - 1] = NULL;
    }
    if (line != NULL) {
        int lines_count = TRoute_GetNumberOfLines(route) + 2;
        route->lines = (TLine **) realloc(route->lines, sizeof(TLine *) * lines_count);
        route->lines[lines_count - 2] = line;
        route->lines[lines_count - 1] = NULL;
    }
}

/* Secondary functions */

int TRoute_GetCount(TRoute *head) {
    int count = 0;
    for (TRoute *route = head; route != NULL; route = route->next, ++count);
    return count;
}

int TRoute_GetNumberOfStops(TRoute *route) {
    int count = 0;
    for (int i = 0; route->stops[i] != NULL; ++i, ++count);
    return count;
}

int TRoute_GetNumberOfLines(TRoute *route) {
    int count = 0;
    for (int i = 0; route->lines[i] != NULL; ++i, ++count);
    return count;
}

bool TRoute_IsDone(TRoute *route) {
    return TRoute_GetNumberOfStops(route) == TRoute_GetNumberOfLines(route) + 1;
}

void TRoute_PrintOut(TRoute *route) {
    int lines_count = TRoute_GetNumberOfLines(route);
    for (int i = 0; route->lines[i] != NULL; ++i) {
        if (i != 0) printf(" ");
        printf("%s --[%s]->", route->stops[i]->name, route->lines[i]->sign);
    }
    if (TRoute_IsDone(route))
        printf(" %s", route->stops[lines_count]->name);
    printf("\n");
}

bool TRoute_IsStopOnRoute(TRoute *route, TStop *stop) {
    TLine *lastLine = route->lines[TRoute_GetNumberOfLines(route) - 1];
    for (int i = 0; lastLine->stops[i] != NULL; ++i) {
        if (lastLine->stops[i] == stop)
            return true;
    }
    return false;
}

int TRoute_GetTransfers(TRoute *route, TStop ***stops, TLine ***lines) {
    int numOfTransfers = 0;
    TStop *lastStop = route->stops[TRoute_GetNumberOfStops(route) - 1];
    TLine *lastLine = route->lines[TRoute_GetNumberOfLines(route) - 1];

    TStop **transferStops = NULL;
    TLine **transferLines = NULL;

    // Search for stops that have minimum of two transfers
    int lineStops_count = TLine_GetNumberOfStops(lastLine);
    for (int i = 0; i < lineStops_count; ++i) {
        TStop *currentStop = lastLine->stops[i];
        if (currentStop == lastStop || TStop_GetNumberOfTransfers(currentStop) < 2)
            continue;

        // Loop through stop's all lines
        int stopTransfers_count = TStop_GetNumberOfTransfers(currentStop);
        for (int j = 0; j < stopTransfers_count; ++j) {
            TLine *currentLine = currentStop->transfers[j];

            // Search for unvisited lines
            bool wasVisited = false;
            int routeLines_count = TRoute_GetNumberOfLines(route);
            for (int k = 0; !wasVisited && k < routeLines_count; ++k) {
                if (currentLine == route->lines[k])
                    wasVisited = true;
            }
            if (wasVisited) continue;

            // If already added, just continue
            bool wasAlreadyAdded = false;
            for (int k = 0; k < numOfTransfers; ++k) {
                if (transferStops[k] == currentStop && transferLines[k] == currentLine)
                    wasAlreadyAdded = true;
            }
            if (wasAlreadyAdded) continue;

            // Add to possible transfers if was not visited before
            ++numOfTransfers;
            transferStops = (TStop **) realloc(transferStops, sizeof(TStop *) * numOfTransfers);
            transferStops[numOfTransfers - 1] = currentStop;
            transferLines = (TLine **) realloc(transferLines, sizeof(TLine *) * numOfTransfers);
            transferLines[numOfTransfers - 1] = currentLine;
        }
    }

    *stops = transferStops;
    *lines = transferLines;
    return numOfTransfers;
}
