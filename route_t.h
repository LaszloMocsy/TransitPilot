#ifndef TRANSITPILOT_ROUTE_T_H
#define TRANSITPILOT_ROUTE_T_H

#include "debugmalloc.h"
#include "tstop_t.h"
#include "tline_t.h"

typedef struct Route_t {
    int *stops, *lines;
    struct Route_t *next;
} Route;

Route *Route_init(int firstStop, int firstLine);

void Route_free(Route *pRoute);

Route *Route_push(Route *array_head, Route *pRoute);

Route *Route_pop(Route *array_head, Route *pRoute);

void Route_addData(Route *pRoute, int stop_id, int line_id);

int Route_GetCount(Route *array_head);

bool Route_IsDone(Route *pRoute);

void Route_PrintOut(Route *pRoute, TStopsArray *stops, TLinesArray *lines);

#endif //TRANSITPILOT_ROUTE_T_H
