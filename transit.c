#include "transit.h"

/// Dynamically allocated `TransitStop`. <b style="color: red">Free it after use with <c>TransitStop_free()</c> method!</b>
/// \return The pointer for the newly created, empty <c>TransitStop</c>
TransitStop *TransitStop_init() {
    TransitStop *p = (TransitStop *) malloc(sizeof(TransitStop));
    p->name = NULL;
    p->transfers = NULL;
    return p;
}

/// Free up dynamically allocated <c>TransitStop</c>
/// \param stop The pointer of the <c>TransitStop</c> that needs to be freed up
void TransitStop_free(TransitStop *stop) {
    free(stop->name);
    free(stop->transfers);
    free(stop);
}

/// Free up dynamically allocated <c>ArrayOfTransitStops</c>
/// \param array The pointer of the <c>ArrayOfTransitStops</c> that needs to be freed up
void ArrayOfTransitStops_free(ArrayOfTransitStops *array) {
    for (int i = 0; i < array->count; ++i)
        TransitStop_free(&array->items[i]);
    free(array);
}
