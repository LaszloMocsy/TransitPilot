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

/// Load the specified configuration file if it exists
/// \param fileName The name of the configuration file
/// \param stops_head The memory address of the array of TStops
/// \param lines_head The memory address of the array of TLines
/// \return `true` if the process was successful, otherwise `false`
bool LoadConfiguration(const char *fileName, TStop **stops_head, TLine **lines_head);

#endif //TRANSITPILOT_LOAD_H
