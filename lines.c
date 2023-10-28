#include "lines.h"

/// Creates a new `TransitLine` struct and adds it to the specified `TransitLineArray`. After use, it needs to be freed!
/// \param storage The "storage" that will contain its dynamic address
/// \param signature The line's unique signature. Max 4 character long
/// \return The newly created `TransitLine`'s memory address
TransitLine *CreateTransitLine(TransitLineArray *storage, char signature[4]) {
    TransitLine *newLine = (TransitLine *) malloc(sizeof(TransitLine) * 1);
    if (newLine == NULL)
        return NULL;

    strcpy(newLine->signature, signature);
    newLine->stop_count = 0;
    newLine->stops = NULL;
    newLine->times = NULL;

    ++storage->count;
    storage->array = (TransitLine **) realloc(storage->array, sizeof(TransitLine *) * storage->count);
    storage->array[storage->count - 1] = newLine;

    return newLine;
}

/// Adds a new stop to an existing `TransitLine`. After use, it needs to be freed!
/// \param line The line to which the new stop will be added
/// \param stop The stop that will be added to the line
/// \param time Travel time (in seconds) between the stop to be added and the last stop added. If this is the first stop, its value is not taken into account
void AddStopToTransitLine(TransitLine *line, char *stop, int time) {
    ++line->stop_count;
    line->stops = (char **) realloc(line->stops, sizeof(char *) * line->stop_count);
    line->stops[line->stop_count - 1] = stop;
    if (line->stop_count > 1) {
        line->times = (int *) realloc(line->times, sizeof(int) * line->stop_count - 1);
        line->times[line->stop_count - 2] = time;
    }
}

/// Free up everything in the given `TransitLineArray`
/// \param storage The `TransitLineArray` that needs to be freed up
void FreeTransitLineArray(TransitLineArray *storage) {
    for (int idx_a = 0; idx_a < storage->count; ++idx_a) {
        TransitLine *line = storage->array[idx_a];
        for (int idx_b = 0; idx_b < line->stop_count; ++idx_b)
            free(line->stops[idx_b]);
        free(line->stops);
        free(line->times);
        free(line);
    }
    free(storage);
}
