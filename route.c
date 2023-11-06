#include "route.h"

/// Compares the two stops' transfers
/// \param stopA The stop A
/// \param stopB The stop B
/// \return A dynamically allocated array with a last value of <c>-1</c>. <b style="color: red">Free it after use!</b>
static int *SameTransfers(TStop stopA, TStop stopB) {
    int count = 0;
    int *same = NULL;

    for (int a = 0; a < stopA.transferCount; ++a) {
        for (int b = 0; b < stopB.transferCount; ++b) {
            int aID = stopA.transfers[a];
            int bID = stopB.transfers[b];
            if (aID == bID) {
                same = (int *) realloc(same, sizeof(int) * ++count);
                same[count - 1] = aID;
            }
        }
    }

    if (same != NULL) {
        same = (int *) realloc(same, sizeof(int) * ++count);
        same[count - 1] = -1;
    }
    return same;
}

/// Plans a rout from stop A to B and returns the route's specs
/// \param stops The array that contains all <c>TStop</c>s
/// \param lines The array that contains all <c>TLine</c>s
/// \param stopA The id of stop A
/// \param stopB The id of stop B
void PlanRoute(TStopsArray stops, TLinesArray lines, int stopA, int stopB) {
    if (stopA == -1 || stopB == -1) {
        printf("\nStop A and B cannot be empty!\n\n");
        return;
    } else if (stopA == stopB) {
        printf("\nStop A and B cannot be the same!\n\n");
        return;
    }

    // Check if the two stop is on the same line
    int *sameTransfers = SameTransfers(*stops.items[stopA], *stops.items[stopB]);
    if (sameTransfers != NULL) {
        printf("\nStop A and B is on the same line!\n-> ");
        for (int i = 0; sameTransfers[i] != -1; ++i)
            printf("%s, ", lines.items[sameTransfers[i]]->sign);
        printf("\n\n");
    } else
        printf("Stop A and B is on different lines!\n\n");
}
