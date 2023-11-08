#include "menu.h"

/// Lists all <c>TStop</c>s from an array
/// \param stops The array that needs to be printed out
/// \param lines Required for the lines' sign
void ListAllStops(TStopsArray stops, TLinesArray lines) {
    printf("\n=== Stops (%d) ===\n"
           "<id>. <stop name>  ->  <transferable lines' sign>\n\n", stops.count);
    for (int i = 0; i < stops.count; ++i) {
        TStop *stop = stops.items[i];
        printf("%d. %s  ->  ", i, stop->name);
        for (int j = 0; j < stop->transferCount; ++j) {
            printf("%s", lines.items[stop->transfers[j]]->sign);
            if (j < stop->transferCount - 1)
                printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}

/// Lists all <c>TLine</c>s from an array
/// \param lines The array that needs to be printed out
/// \param stops Required for the stops' name
void ListAllLines(TLinesArray lines, TStopsArray stops) {
    printf("\n=== Lines (%d) ===\n"
           "<line's sign>  ->  <from> - <to>\n\n", lines.count);
    for (int i = 0; i < lines.count; ++i) {
        TLine *line = lines.items[i];
        printf("%s  ->  %s - %s\n",
               line->sign,
               stops.items[line->stops[0]]->name,
               stops.items[line->stops[line->stopsCount - 1]]->name);
    }
    printf("\n");
}

/// Gets the id of the <c>TStop</c> from the user
/// \param output The id of the valid <c>TStop</c>
/// \param max The last id that is valid
void ReadStopId(int *output, int max) {
    int input;
    do {
        printf("Enter a valid id [0-%d]: ", max);
        scanf("%d", &input);
    } while (input < 0 || input > max);
    *output = input;
    printf("\n");
}
