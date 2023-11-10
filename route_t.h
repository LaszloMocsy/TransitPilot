#ifndef TRANSITPILOT_ROUTE_T_H
#define TRANSITPILOT_ROUTE_T_H

#include "debugmalloc.h"
#include "tstop.h"
#include "tline.h"

typedef struct Route_t {
    int *stops, *lines;
    struct Route_t *next;
} Route;

Route *Route_init(int firstStop, int firstLine);

Route *Route_push(Route *array_head, Route *pRoute);

Route *Route_pop(Route *array_head, Route *pRoute);

void Route_addData(Route *pRoute, int stop_id, int line_id);

bool Route_IsDone(Route *pRoute);

#endif //TRANSITPILOT_ROUTE_T_H
