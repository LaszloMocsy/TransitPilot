#include "route_t.h"

/// Initialize a new <c>Route</c> struct. <b style="color:red;">The caller needs to free the <c>Route</c> after use!</b>
/// \param firstStop Populate the new <c>Route</c> with this stop
/// \param firstLine Populate the new <c>Route</c> with this line
/// \return The newly created <c>Route</c>'s memory address
Route *Route_init(int firstStop, int firstLine) {
    Route *newRoute = (Route *) malloc(sizeof(Route));
    newRoute->next = NULL;
    newRoute->stops = (int *) malloc(sizeof(int) * 2);
    newRoute->stops[0] = firstStop;
    newRoute->stops[1] = -1;
    newRoute->lines = (int *) malloc(sizeof(int) * 2);
    newRoute->lines[0] = firstLine;
    newRoute->lines[1] = -1;
    return newRoute;
}

/// Free up the given <c>Route</c>
/// \param pRoute The <c>Route</c> that needs to be freed up
void Route_free(Route *pRoute) {
    if (pRoute != NULL) {
        free(pRoute->stops);
        free(pRoute->lines);
        free(pRoute);
    }
}

/// Add a new <c>Route</c> to the end of the chained array
/// \param array_head The head of the chained array
/// \param pRoute The new item that needs to be added
/// \return The memory address of the head of the chained array
Route *Route_push(Route *array_head, Route *pRoute) {
    if (array_head == NULL) return pRoute;
    Route *last = array_head;
    while (last->next != NULL) last = last->next;
    last->next = pRoute;
    return array_head;
}

/// Remove the specified <c>Route</c> from the chained array
/// \param array_head The head of the chained array
/// \param pRoute The item that needs to be removed
/// \return The memory address of the head of the chained array
Route *Route_pop(Route *array_head, Route *pRoute) {
    if (array_head == NULL) return NULL;
    for (Route *current = array_head, *previous = NULL; current != NULL; previous = current, current = current->next) {
        if (current == pRoute) {
            if (previous == NULL) {
                Route *temp = current->next;
                free(current);
                return temp;
            } else {
                previous->next = current->next;
                free(current);
                return array_head;
            }
        }
    }
    return array_head;
}

/// Add new stop and line to existing <c>Route</c>
/// \param pRoute The <c>Route</c> that will contain the new data
/// \param stop_id The stop's id
/// \param line_id The line's id
void Route_addData(Route *pRoute, int stop_id, int line_id) {
    if (stop_id != -1) {
        int stops_count = 2; // (-1) + stop_id
        for (int i = 0; pRoute->stops[i] != -1; ++i) ++stops_count;
        pRoute->stops = (int *) realloc(pRoute->stops, sizeof(int) * stops_count);
        pRoute->stops[stops_count - 2] = stop_id;
        pRoute->stops[stops_count - 1] = -1;
    }
    if (line_id != -1) {
        int lines_count = 2; // (-1) + line_id
        for (int i = 0; pRoute->lines[i] != -1; ++i) ++lines_count;
        pRoute->lines = (int *) realloc(pRoute->lines, sizeof(int) * lines_count);
        pRoute->lines[lines_count - 2] = lines_count;
        pRoute->lines[lines_count - 1] = -1;
    }
}

/// Check whether the given <c>Route</c> is done (closed/finished)
/// \param pRoute The <c>Route</c> that needs to be checked
/// \return <c>true</c> if the <c>Route</c> is done (closed/finished), otherwise <c>false</c>
bool Route_IsDone(Route *pRoute) {
    int stops_count = 1; // (-1)
    for (int i = 0; pRoute->stops[i] != -1; ++i) ++stops_count;
    int lines_count = 1; // (-1)
    for (int i = 0; pRoute->lines[i] != -1; ++i) ++lines_count;
    return stops_count == lines_count + 1;
}

/// Print out to the <c>stdout</c> the given <c>Route</c>
/// \param pRoute The <c>Route</c> that will be printed out
/// \param stops The array of stops
/// \param lines The array of lines
void Route_PrintOut(Route *pRoute, TStopsArray *stops, TLinesArray *lines) {
    int i = 0;
    for (; pRoute->lines[i] != -1; ++i) {
        if (i != 0) printf(" ");
        printf("%s --[%s]->", stops->items[pRoute->stops[i]]->name, lines->items[pRoute->lines[i]]->sign);
    }
    if (Route_IsDone(pRoute))
        printf("%s", stops->items[pRoute->stops[i]]->name);
}
