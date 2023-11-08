#include "route.h"

/// Check if the two given stops are on tha same line
/// \param stopA <c>TStop</c> from all the stops
/// \param stopB Second <c>TStop</c> from all the stops
/// \return <c>true</c>, if the two stops are on the same line, otherwise <c>false</c>
bool IsOnSameLine(TStop stopA, TStop stopB) {
    for (int i = 0; i < stopA.transferCount; ++i) {
        for (int j = 0; j < stopB.transferCount; ++j) {
            if (stopA.transfers[i] == stopB.transfers[j])
                return true;
        }
    }
    return false;
}

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

    bool isOnSameLine = IsOnSameLine(*stops->items[stopA_id], *stops->items[stopB_id]);
    printf("\nThe two stops are %s\n\n", isOnSameLine ? "on the same line!" : "NOT on the same line!");
    //FIXME: Create new function for checking if the two stops are on the same line
}
