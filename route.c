#include "route.h"

/// Get all lines ids where the two stop is on.<br/>
/// <b style="color:red;">If it is not <c>NULL</c>, than it creates a dynamically allocated array. The caller needs to free it after use!</b>
/// \param stopA The stop A
/// \param stopB The stop B
/// \return <c>NULL</c> if the two stop is not on the same line(s). Otherwise an array with an end value of <c>-1</c>
static int *GetSameLines(TStop *stopA, TStop *stopB) {
    int count = 0;
    int *sameLines = NULL;
    for (int i = 0; i < stopA->transferCount; ++i) {
        for (int j = 0; j < stopB->transferCount; ++j) {
            if (stopA->transfers[i] == stopB->transfers[j]) {
                sameLines = (int *) realloc(sameLines, sizeof(int) * ++count);
                sameLines[count - 1] = stopA->transfers[i];
            }
        }
    }
    if (count != 0) {
        sameLines = (int *) realloc(sameLines, sizeof(int) * ++count);
        sameLines[count - 1] = -1;
    }
    return sameLines;
}

/// Get all the possible distances between stops, if there is any distance that exists.<br/>
/// <b style="color:red;">After use, the caller needs to free the dynamically allocated chained array of distances!</b>
/// \param stopA Stop A
/// \param stopB Stop B
/// \return <c>NULL</c> if there is no possible distance, otherwise a dynamically allocated chained array of all the possible distances
static Distance *GetDistanceBetweenTwoStops(TStopsArray *stops, TLinesArray *lines, int stopA_id, int stopB_id) {
    int *sameLines = GetSameLines(stops->items[stopA_id], stops->items[stopB_id]);
    if (sameLines == NULL)
        return NULL;
    Distance *distance_head = NULL;

    // Create a Distance for all the distances
    for (int i = 0; sameLines[i] != -1; ++i) {
        int line_id = sameLines[i];
        TLine *line = lines->items[line_id];

        int travelTimeSum = 0, startIdx = -1, endIdx = -1;
        // Get the id (id in the line) of stop A and stop B for travel time sum
        for (int j = 0; j < line->stopsCount; ++j) {
            if (line->stops[j] == stopA_id || line->stops[j] == stopB_id) {
                if (startIdx == -1) startIdx = j;
                else endIdx = j;
            }
        }
        // Sum all the times between the two stops
        for (int j = startIdx; j < endIdx; ++j)
            travelTimeSum += line->times[j];

        // Create the distance
        Distance *newDistance = (Distance *) malloc(sizeof(Distance));
        newDistance->next = NULL;
        newDistance->stopFrom = stopA_id;
        newDistance->stopTo = stopB_id;
        newDistance->line = line_id;
        newDistance->travelTime = travelTimeSum;

        // Add the newly created distance to the chain
        if (distance_head == NULL)
            distance_head = newDistance;
        else {
            Distance *last = distance_head;
            while (last->next != NULL)
                last = last->next;
            last->next = newDistance;
        }
    }

    free(sameLines);
    return distance_head;
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

    // Get the distances between the stops, IF they on the same line
    Distance *distances_head = GetDistanceBetweenTwoStops(stops, lines, stopA_id, stopB_id);
    if (distances_head == NULL) {
        printf("Stop A and B are NOT on the same line!\n\n");
        return;
    }
    printf("Stop A and B are on the same line! The following routes are found:\n\n");
    int i = 0;
    for (Distance *currentDistance = distances_head; currentDistance != NULL; currentDistance = currentDistance->next) {
        printf("%d.  %s --[%s]-> %s  ::  Travel time: %dm\n", i,
               stops->items[currentDistance->stopFrom]->name,
               lines->items[currentDistance->line]->sign,
               stops->items[currentDistance->stopTo]->name,
               currentDistance->travelTime);
        ++i;
    }
    printf("\n");

    // Free the chained array (distances_head)
    Distance_free(distances_head);

    /*
    // Check if the two stop is on the same line
//    int *sameLine = GetSameLines(*stops.items[stopA_id], *stops.items[stopB_id]);
//    printf("Stop A and B are %s\n\n", sameLine != NULL ? "on the same line!" : "NOT on the same line!");
//    free(sameLine);
     */
}

void Distance_free(Distance *head) {
    if (head->next != NULL)
        Distance_free(head->next);
    free(head);
}
