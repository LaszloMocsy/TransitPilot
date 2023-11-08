#include "route.h"

/// Plans a rout from stop A to B and returns the route's specs
/// \param stops The array that contains all <c>TStop</c>s
/// \param lines The array that contains all <c>TLine</c>s
/// \param stopA_id The id of stop A
/// \param stopB_id The id of stop B
void PlanRoute(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id) {
    if (stopA_id == -1 || stopB_id == -1) {
        printf("Stop A and B cannot be empty!\n\n");
        return;
    } else if (stopA_id == stopB_id) {
        printf("Stop A and B cannot be the same!\n\n");
        return;
    }
}
