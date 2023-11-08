#include "route.h"

/// Get all lines ids where the two stop is on.<br/>
/// <b style="color:red;">If it is not <c>NULL</c>, than it creates a dynamically allocated array. The caller needs to free it after use!</b>
/// \param stopA The stop A
/// \param stopB The stop B
/// \return <c>NULL</c> if the two stop is not on the same line(s). Otherwise an array with an end value of <c>-1</c>
static int *GetSameLines(TStop stopA, TStop stopB) {
    int count = 0;
    int *sameLines = NULL;
    for (int i = 0; i < stopA.transferCount; ++i) {
        for (int j = 0; j < stopB.transferCount; ++j) {
            if (stopA.transfers[i] == stopB.transfers[j]) {
                sameLines = (int *) realloc(sameLines, sizeof(int) * ++count);
                sameLines[count - 1] = stopA.transfers[i];
            }
        }
    }
    if (count != 0) {
        sameLines = (int *) realloc(sameLines, sizeof(int) * ++count);
        sameLines[count - 1] = -1;
    }
    return sameLines;
}

/// Plans a rout from stop A to B and returns the route's specs
/// \param stops The array that contains all <c>TStop</c>s
/// \param lines The array that contains all <c>TLine</c>s
/// \param stopA_id The id of stop A
/// \param stopB_id The id of stop B
void PlanRoute(TStopsArray stops, TLinesArray lines, int stopA_id, int stopB_id) {
    if (stopA_id == -1 || stopB_id == -1) {
        printf("Stop A and B cannot be empty!\n\n");
        return;
    } else if (stopA_id == stopB_id) {
        printf("Stop A and B cannot be the same!\n\n");
        return;
    }

    // Check if the two stop is on the same line
    int *sameLine = GetSameLines(*stops.items[stopA_id], *stops.items[stopB_id]);
    printf("Stop A and B are %s\n\n", sameLine != NULL ? "on the same line!" : "NOT on the same line!");
    free(sameLine);
}
