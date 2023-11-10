#ifndef TRANSITPILOT_TLINE_T_H
#define TRANSITPILOT_TLINE_T_H

#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"

/// A transit line, that have a sign, an array of stops and an array of travel times
typedef struct {
    char *sign;
    int stopsCount;
    int *stops;
    int timeCount;
    int *times;
} TLine;

/// Struct for dynamic <c>TLine</c> array
typedef struct {
    int count;
    TLine **items;
} TLinesArray;

TLine *TLine_init(char* sign);

void TLine_AddStop(TLine *line, int stopId, int time);

void TLinesArray_push(TLinesArray *array, char* sign);

void TLine_free(TLine *line);

void TLinesArray_free(TLinesArray *array);

#endif //TRANSITPILOT_TLINE_T_H
