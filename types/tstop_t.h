#ifndef TRANSITPILOT_TSTOP_T_H
#define TRANSITPILOT_TSTOP_T_H

#include <stdbool.h>
#include <string.h>
#include "../lib/debugmalloc.h"
#include "tline_t.h"

typedef struct TLines_t TLine;

/// A transit stop struct that is an element of a chained array
typedef struct TStop_t {
    char *name;
    TLine **transfers;
    struct TStop_t *next;
} TStop;

/* Primary functions */

/// Create a new TStop with the given name.<br/>
/// <b style="color:red;">This function allocates memory dynamically. Free up the memory after use!</b>
/// \param name The name of the stop
/// \return The newly allocated TStop's memory address
TStop *TStop_init(char *name);

/// Free up a single struct.<br/>
/// <p style="color:orange;">Note that the transferable TLines will not be free!</p>
/// \param stop The TStop that needs to be free
void TStop_free(TStop *stop);

/// Free up the whole chained array
/// <p style="color:orange;">Note that the transferable TLine will not be free!</p>
/// \param head The head of the chained array
void TStop_freeArray(TStop *head);

/// Add the given TStop to the end of the given chained array
/// \param head The head of the chained array
/// \param stop The TStop that needs to be added to the array
/// \return Memory location for the head of the (new) chained array
TStop *TStop_push(TStop *head, TStop *stop);

/// Add transfer to existing TStop
/// \param stop The TStop to which the line will be added
/// \param line The TLine that will be added to the stop
void TStop_addTransfer(TStop *stop, TLine *line);

/* Secondary functions */

/// Check if the given name is already in the given chained array of TStops
/// \param head The head of the TStop chained array
/// \param name The name that needs to be checked
/// \return NULL if the name does not exist, otherwise the pointer of the TStop that has the same name
TStop *TStop_IsNameExists(TStop *head, char *name);

/// Get the number of transferable TLines
/// \param stop The TStop that has the transfers
/// \return The number of transfers
int TStop_GetNumberOfTransfers(TStop *stop);

/// Count all the stops in the array
/// \param head The head of the array
/// \return The number of stops in the array
int TStop_GetCount(TStop *head);

/// Get TStop by id from an array
/// \param id The id of the requested TStop
/// \return NULL if the id is invalid, otherwise the memory address of the TStop
TStop *TStop_GetStopById(TStop *head, int id);

#endif //TRANSITPILOT_TSTOP_T_H
