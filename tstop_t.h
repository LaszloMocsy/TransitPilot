#ifndef TRANSITPILOT_TSTOP_T_H
#define TRANSITPILOT_TSTOP_T_H

#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"

/// A transit stop, that have a name and an array of transferable lines
typedef struct {
    char *name;
    int transferCount;
    int *transfers;
} TStop;

/// Struct for dynamic <c>TStop</c> array
typedef struct {
    int count;
    TStop **items;
} TStopsArray;

TStop *TStop_init(char *name);

int TStopsArray_push(TStopsArray *array, char *name, int transfer);

void TStop_free(TStop *stop);

void TStopsArray_free(TStopsArray *array);

#endif //TRANSITPILOT_TSTOP_T_H
