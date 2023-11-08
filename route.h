#ifndef TRANSITPILOT_ROUTE_H
#define TRANSITPILOT_ROUTE_H

#include "tstop.h"
#include "tline.h"

typedef struct Distance_t {
    int stopFrom, stopTo, line, travelTime;
    struct Distance_t *next;
} Distance;

static int *GetSameLines(TStop *stopA, TStop *stopB);

static Distance *GetDistanceBetweenTwoStops(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id);

void PlanRoute(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id);

void Distance_free(Distance *head);

#endif //TRANSITPILOT_ROUTE_H
