#ifndef TRANSITPILOT_LINES_H
#define TRANSITPILOT_LINES_H

#include "debugmalloc.h"

typedef struct TransitLine {
    char signature[4];
    int stop_count;
    char **stops;
    int *times;
} TransitLine;

typedef struct TransitLineArray {
    int count;
    TransitLine **array;
} TransitLineArray;

TransitLine *CreateTransitLine(TransitLineArray *storage, char signature[4]);

void AddStopToTransitLine(TransitLine *line, char *stop, int time);

void FreeTransitLineArray(TransitLineArray *storage);

#endif //TRANSITPILOT_LINES_H
