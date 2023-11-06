#ifndef TRANSITPILOT_MENU_H
#define TRANSITPILOT_MENU_H

#include <stdio.h>
#include "tstop.h"
#include "tline.h"

void ListAllStops(TStopsArray stops, TLinesArray lines);

void ListAllLines(TLinesArray lines, TStopsArray stops);

void ReadStopId(int *output, int max);

#endif //TRANSITPILOT_MENU_H
