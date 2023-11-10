#include "route_t.h"

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

Route *Route_push(Route *array_head, Route *pRoute) {
    if (array_head == NULL) return pRoute;
    Route *last = array_head;
    while (last->next != NULL) last = last->next;
    last->next = pRoute;
    return array_head;
}

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

bool Route_IsDone(Route *pRoute) {
    int stops_count = 1; // (-1)
    for (int i = 0; pRoute->stops[i] != -1; ++i) ++stops_count;
    int lines_count = 1; // (-1)
    for (int i = 0; pRoute->lines[i] != -1; ++i) ++lines_count;
    return stops_count == lines_count + 1;
}

void Route_printOut(Route *pRoute, TStopsArray *stops, TLinesArray *lines) {
    int i = 0;
    while (pRoute->lines[i] != -1) {
        if (i != 0) printf(" ");
        printf("%s --[%s]->", stops->items[pRoute->stops[i]]->name, lines->items[pRoute->lines[i]]->sign);
        ++i;
    }
    if (Route_IsDone(pRoute))
        printf("%s", stops->items[pRoute->stops[i]]->name);
}
