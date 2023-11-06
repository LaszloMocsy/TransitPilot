#ifndef TRANSITPILOT_ROUTE_H
#define TRANSITPILOT_ROUTE_H

#include "tstop.h"
#include "tline.h"

static int *SameTransfers(TStop stopA, TStop stopB);

void PlanRoute(TStopsArray stops, TLinesArray lines, int stopA, int stopB);

#endif //TRANSITPILOT_ROUTE_H
