#ifndef TRANSITPILOT_ROUTE_H
#define TRANSITPILOT_ROUTE_H

#include "tstop.h"
#include "tline.h"

typedef struct Route_t {
    int *stops, *lines;
} Route;

void PlanRoute(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id);

#endif //TRANSITPILOT_ROUTE_H
