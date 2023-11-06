#include "tline.h"

/// Dynamically allocated `TLine`. <b style="color: red">Free it after use with <c>TransitLine_free()</c> method!</b>
/// \param sign Sign of the <c>TLine</c>
/// \return The pointer for the newly created, empty <c>TLine</c>
TLine *TLine_init(char *sign) {
    TLine *new = (TLine *) malloc(sizeof(TLine));
    new->sign = sign;
    new->stops = NULL;
    new->stopsCount = 0;
    new->timeCount = 0;
    new->times = NULL;
    return new;
}

/// Add a stop's id to an existing <c>TLine</c>
/// \param line The <c>TLine</c> that has the stop
/// \param stopId The id of the <c>TStop</c>
/// \param time The travelling time to the stop on the line
void TLine_AddStop(TLine *line, int stopId, int time) {
    line->stops = (int *) realloc(line->stops, sizeof(int) * ++line->stopsCount);
    line->stops[line->stopsCount - 1] = stopId;
    if (line->stopsCount > 1) {
        line->times = (int *) realloc(line->times, sizeof(int) * ++line->timeCount);
        line->times[line->timeCount - 1] = time;
    }
}

/// Push a new <c>TLine</c> to an existing <c>TLinesArray</c>
/// \param array The existing array
/// \param sign The sign of the new <c>TLine</c>
void TLinesArray_push(TLinesArray *array, char *sign) {
    array->items = (TLine **) realloc(array->items, sizeof(TLine *) * (++array->count));
    array->items[array->count - 1] = TLine_init(sign);
}

/// Free up dynamically allocated <c>TLine</c>
/// \param line The pointer of the <c>TLine</c> that needs to be freed up
void TLine_free(TLine *line) {
    free(line->sign);
    free(line->stops);
    free(line->times);
    free(line);
}

/// Free up <c>TLinesArray</c>'s dynamically allocated data
/// \param array The pointer of the <c>TLinesArray</c> that needs to be freed up
void TLinesArray_free(TLinesArray *array) {
    for (int i = 0; i < array->count; ++i)
        TLine_free(array->items[i]);
    free(array->items);
}
