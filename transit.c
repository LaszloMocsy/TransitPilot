#include "transit.h"

/// Dynamically allocated `TStop`. <b style="color: red">Free it after use with <c>TransitStop_free()</c> method!</b>
/// \param name Name of the <c>TStop</c>
/// \return The pointer for the newly created, empty <c>TStop</c>
TStop *TStop_init(char *name) {
    TStop *p = (TStop *) malloc(sizeof(TStop));
    p->name = name;
    p->transferCount = 0;
    p->transfers = NULL;
    return p;
}

/// Push a new <c>TStop</c> to an existing <c>TStopsArray</c>
/// \param array The existing array
/// \param name The name of the new <c>TStop</c>
/// \param transfer The id of the transfer
void TStopsArray_push(TStopsArray *array, char *name, int transfer) {
    for (int i = 0; i < array->count; ++i)
        if (strcmp(array->items[i]->name, name) == 0) {
            free(name);

            TStop *stop = array->items[i];
            for (int j = 0; j < stop->transferCount; ++j)
                if (stop->transfers[j] == transfer)
                    return;

            //Add new transfer to an existing `TStop` in `TStopsArray`
            stop->transfers = (int *) realloc(stop->transfers, sizeof(int) * ++stop->transferCount);
            stop->transfers[stop->transferCount - 1] = transfer;

            return;
        }

    //TODO: Make it simple, use to variable 1 for the stop and one for the transfer
    TStop *newStop = TStop_init(name);
    //Add new transfer to the `TStop`
    newStop->transfers = (int *) realloc(newStop->transfers, sizeof(int) * ++newStop->transferCount);
    newStop->transfers[newStop->transferCount - 1] = transfer;
    // Add new `TStop` to the array
    array->items = (TStop **) realloc(array->items, sizeof(TStop *) * (++array->count));
    array->items[array->count - 1] = newStop;
}

/// Free up dynamically allocated <c>TStop</c>
/// \param stop The pointer of the <c>TStop</c> that needs to be freed up
void TStop_free(TStop *stop) {
    free(stop->name);
    free(stop->transfers);
    free(stop);
}

/// Free up <c>TStopsArray</c>'s dynamically allocated data
/// \param array The pointer of the <c>TStopsArray</c> that needs to be freed up
void TStopsArray_free(TStopsArray *array) {
    for (int i = 0; i < array->count; ++i)
        TStop_free(array->items[i]);
    free(array->items);
}
