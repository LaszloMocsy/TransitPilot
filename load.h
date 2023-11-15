#ifndef TRANSITPILOT_LOAD_H
#define TRANSITPILOT_LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "types/tstop_t.h"
#include "types/tline_t.h"

typedef enum ProcessStage {
    ProcessSign,
    ProcessStop,
    ProcessTime
} ProcessStage;

bool LoadConfiguration(const char *fileName, TStopsArray *stopsArray, TLinesArray *linesArray);

#endif //TRANSITPILOT_LOAD_H
