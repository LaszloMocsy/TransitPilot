#ifndef TRANSITPILOT_ROUTE_H
#define TRANSITPILOT_ROUTE_H

#include "tstop.h"
#include "tline.h"

static int *GetSameLines(TStop stopA, TStop stopB);

void PlanRoute(TStopsArray stops, TLinesArray lines, int stopA_id, int stopB_id);

#endif //TRANSITPILOT_ROUTE_H
