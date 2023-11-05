#ifndef TRANSITPILOT_TRANSIT_H
#define TRANSITPILOT_TRANSIT_H

#include "debugmalloc.h"

/// A transit stop, that have a name and an array of transferable lines
typedef struct {
    char *name;
    int *transfers;
} TransitStop;

/// Struct for dynamic <c>TransitStop</c> array
typedef struct {
    int count;
    TransitStop *items;
} ArrayOfTransitStops;

TransitStop *TransitStop_init();

void TransitStop_free(TransitStop *stop);

void ArrayOfTransitStops_free(ArrayOfTransitStops *array);

#endif //TRANSITPILOT_TRANSIT_H
