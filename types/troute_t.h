#ifndef TRANSITPILOT_TROUTE_T_H
#define TRANSITPILOT_TROUTE_T_H

#include "../debugmalloc.h"
#include "tstop_t.h"
#include "tline_t.h"

typedef struct TRoute_t {
    TStop **stops;
    TLine **lines;
    struct TRoute_t *next;
} TRoute;

/* Primary functions */

/// Initialize a new TRoute struct.<br/>
/// <b style="color:red;">This function allocates memory dynamically. Free up the memory after use!</b>
/// \param stop Populate the new TRoute with this stop
/// \param line Populate the new TRoute with this line
/// \return The newly created TRoute's memory address
TRoute *TRoute_init(TStop *stop, TLine *line);

/// Free up a single struct.<br/>
/// <p style="color:orange;">Note that the each TStops and each TLines will not be free!</p>
/// \param stop The TRoute that needs to be free
void TRoute_free(TRoute *route);

/// Free up the whole chained array
/// <p style="color:orange;">Note that the each TStops and each TLines will not be free!</p>
/// \param head The head of the chained array
void TRoute_freeArray(TRoute *head);

/// Add a new TRoute to the end of the chained array
/// \param head The head of the chained array
/// \param route The new item that needs to be added
/// \return The memory address of the head of the chained array
TRoute *TRoute_push(TRoute *head, TRoute *route);

/// Remove the specified TRoute from the chained array
/// \param head The head of the chained array
/// \param route The item that needs to be removed
/// \return The memory address of the head of the chained array
TRoute *TRoute_pop(TRoute *head, TRoute *route);

/// Add new stop and line to existing TRoute
/// \param route The TRoute that will contain the new data
/// \param stop The TStop that needs to be added
/// \param line The TLine that needs to be added
void TRoute_addData(TRoute *route, TStop *stop, TLine *line);

/* Secondary function */

/// Get the number of routes in a TRoute chained array
/// \param head The head of the chained array
/// \return The number of how many Routes are in the array
int TRoute_GetCount(TRoute *head);

/// Get the number of stops in a route
/// \param route The TRoute that contains the stops
/// \return The number of stops
int TRoute_GetNumberOfStops(TRoute *route);

/// Get the number of lines in a route
/// \param route The TRoute that contains the lines
/// \return The number of lines
int TRoute_GetNumberOfLines(TRoute *route);

/// Check whether the given TRoute is done (closed/finished)
/// \param route The TRoute that needs to be checked
/// \return true if the TRoute is done (closed/finished), otherwise false
bool TRoute_IsDone(TRoute *route);

/// Print out the TRoute
/// \param route The TRoute that will be printed out
void TRoute_PrintOut(TRoute *route);

/// Check if the stop is on the route
/// \param route The route that needs to contain th stop
/// \param stop The stop that needs to be contained
/// \return true if route contains the stop, otherwise false
bool TRoute_IsStopOnRoute(TRoute *route, TStop *stop);

/// Get all transfers for a route
/// \param route The route that needs to continue
/// \param lines Array of possible lines
/// \param stops Array of possible stops
/// \return Number of found possible transfers
int TRoute_GetTransfers(TRoute *route, TStop ***stops, TLine ***lines);

#endif //TRANSITPILOT_TROUTE_T_H
