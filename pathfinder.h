#ifndef TRANSITPILOT_PATHFINDER_H
#define TRANSITPILOT_PATHFINDER_H

#include <string.h>
#include "types/tstop_t.h"
#include "types/tline_t.h"
#include "types/troute_t.h"

/// Plan a route from A to B
/// \param stopA The first stop
/// \param stopB The second stop
void FindPath(TStop *stopA, TStop *stopB);

#endif //TRANSITPILOT_PATHFINDER_H
