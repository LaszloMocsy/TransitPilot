#include "tline_t.h"

/* Primary funtions */

TLine *TLine_init(char *sign) {
    TLine *newLine = (TLine *) malloc(sizeof(TLine));
    newLine->sign = sign;
    newLine->stops = (TStop **) malloc(sizeof(TStop *));
    newLine->stops[0] = NULL;
    newLine->times = (int *) malloc(sizeof(int));
    newLine->times[0] = -1;
    newLine->next = NULL;
    return newLine;
}

void TLine_free(TLine *line) {
    if (line == NULL) return;
    free(line->sign);
    free(line->stops);
    free(line->times);
    free(line);
}

void TLine_freeArray(TLine *head) {
    if (head == NULL) return;
    for (TLine *current = head, *next = current->next;
         current != NULL; current = next, next = current == NULL ? NULL : current->next)
        TLine_free(current);
}

TLine *TLine_push(TLine *head, TLine *line) {
    if (line == NULL) return head;
    else if (head == NULL) return line;

    TLine *last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = line;
    return head;
}

void TLine_addStop(TLine *line, TStop *stop, int time) {
    int newStopsSize = TLine_GetNumberOfStops(line) + 2;
    line->stops = (TStop **) realloc(line->stops, sizeof(TStop) * newStopsSize);
    line->stops[newStopsSize - 2] = stop;
    line->stops[newStopsSize - 1] = NULL;

    if (time > -1) {
        int newTimesSize = TLine_GetNumberOfTimes(line) + 2;
        line->times = (int *) realloc(line->times, sizeof(int) * newTimesSize);
        line->times[newTimesSize - 2] = time;
        line->times[newTimesSize - 1] = -1;
    }
}

/* Secondary functions */

int TLine_GetNumberOfStops(TLine *line) {
    int count = 0;
    for (TStop *stop = line->stops[0]; stop != NULL; stop = line->stops[count])
        ++count;
    return count;
}

int TLine_GetNumberOfTimes(TLine *line) {
    int count = 0;
    for (int time = line->times[0]; time != -1; time = line->times[count])
        ++count;
    return count;
}

int TLine_GetCount(TLine *head) {
    int count = 0;
    for (TLine *line = head; line != NULL; line = line->next)
        ++count;
    return count;
}
