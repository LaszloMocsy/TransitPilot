#ifndef TRANSITPILOT_TLINE_T_H
#define TRANSITPILOT_TLINE_T_H

#include <stdbool.h>
#include <string.h>
#include "../debugmalloc.h"
#include "tstop_t.h"

typedef struct TStop_t TStop;

/// A transit line struct that is an element of a chained array
typedef struct TLines_t {
    char *sign;
     TStop **stops;
    int *times;
    struct TLines_t *next;
} TLine;

/* Primary functions */

/// Initialize a new TLine with the given sign.<br/>
/// <b style="color:red;">This function allocates memory dynamically. Free up the memory after use!</b>
/// \param sign The sign of the line
/// \return The newly allocated TLine's memory address
TLine *TLine_init(char *sign);

/// Free up a single struct.<br/>
/// <p style="color:orange;">Note that the stops will not be free!</p>
/// \param line The TLine that needs to be free
void TLine_free(TLine *line);

/// Free up the whole chained array
/// <p style="color:orange;">Note that the stops will not be free!</p>
/// \param head The head of the chained array
void TLine_freeArray(TLine *head);

/// Add the given TLine to the end of the given chained array
/// \param head The head of the chained array
/// \param line The TLine that needs to be added to the array
/// \return Memory location for the head of the (new) chained array
TLine *TLine_push(TLine *head, TLine *line);

/// Add transfer to existing TStop
/// \param stop The TStop to which the line will be added
/// \param line The TLine that will be added to the stop
void TLine_addStop(TLine *line, TStop *stop, int time);

/* Secondary functions */

/// Get the number of stops on a line
/// \param line The TLine that has the stops
/// \return The number of stops
int TLine_GetNumberOfStops(TLine *line);

/// Get the number of travelling time on a line
/// \param line The TLine that has the travelling times
/// \return The number of travelling times
int TLine_GetNumberOfTimes(TLine *line);

/// Count all the lines in the array
/// \param head The head of the array
/// \return The number of lines in the array
int TLine_GetCount(TLine *head);

#endif //TRANSITPILOT_TLINE_T_H
