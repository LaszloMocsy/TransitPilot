#ifndef TRANSITPILOT_LOAD_H
#define TRANSITPILOT_LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "transit.h"

typedef enum ProcessStage {
    ProcessSign,
    ProcessStop,
    ProcessTime
} ProcessStage;

bool LoadConfiguration(const char *fileName, TStopsArray *stopsArray);

#endif //TRANSITPILOT_LOAD_H
