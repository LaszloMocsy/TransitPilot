#include "tstop_t.h"

/// Dynamically allocated `TStop`. <b style="color: red">Free it after use with <c>TransitStop_free()</c> method!</b>
/// \param name Name of the <c>TStop</c>
/// \return The pointer for the newly created, empty <c>TStop</c>
TStop *TStop_init(char *name) {
    TStop *new = (TStop *) malloc(sizeof(TStop));
    new->name = name;
    new->transferCount = 0;
    new->transfers = NULL;
    return new;
}

/// Push a new <c>TStop</c> to an existing <c>TStopsArray</c>
/// \param array The existing array
/// \param name The name of the new <c>TStop</c>
/// \param transfer The id of the transfer
/// \return The stop's id in the array
int TStopsArray_push(TStopsArray *array, char *name, int transfer) {
    TStop *stop = NULL;
    bool isStopExists = false;
    bool isTransferExists = false;
    int id = array->count;

    for (int i = 0; !isStopExists && i < array->count; ++i)
        if (strcmp(array->items[i]->name, name) == 0) {
            free(name);
            isStopExists = true;
            stop = array->items[i];
            id = i;
            for (int j = 0; !isTransferExists && j < stop->transferCount; ++j)
                if (stop->transfers[j] == transfer)
                    isTransferExists = true;
        }

    if (stop == NULL)
        stop = TStop_init(name);
    if (!isTransferExists) {
        stop->transfers = (int *) realloc(stop->transfers, sizeof(int) * ++stop->transferCount);
        stop->transfers[stop->transferCount - 1] = transfer;
    }
    if (!isStopExists) {
        array->items = (TStop **) realloc(array->items, sizeof(TStop *) * (++array->count));
        array->items[array->count - 1] = stop;
    }

    return id;
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
