#ifndef TRANSITPILOT_PATHFINDER_H
#define TRANSITPILOT_PATHFINDER_H

#include "types/tstop_t.h"
#include "types/tline_t.h"
#include "types/route_t.h"

bool IsStopsOnSameLine(TStop stopA, TStop stopB);

void FindPath(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id);

#endif //TRANSITPILOT_PATHFINDER_H
