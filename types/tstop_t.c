#include "tstop_t.h"

/* Primary functions */

TStop *TStop_init(char *name) {
    TStop *newStop = (TStop *) malloc(sizeof(TStop));
    newStop->name = name;
    newStop->transfers = (TLine **) malloc(sizeof(TLine *));
    newStop->transfers[0] = NULL;
    newStop->next = NULL;
    return newStop;
}

void TStop_free(TStop *stop) {
    if (stop == NULL) return;
    free(stop->name);
    free(stop->transfers);
    free(stop);
}

void TStop_freeArray(TStop *head) {
    if (head == NULL) return;
    for (TStop *current = head, *next = current->next;
         current != NULL; current = next, next = current == NULL ? NULL : current->next)
        TStop_free(current);
}

TStop *TStop_push(TStop *head, TStop *stop) {
    if (stop == NULL) return head;
    else if (head == NULL) return stop;

    TStop *last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = stop;
    return head;
}

void TStop_addTransfer(TStop *stop, TLine *line) {
    int newSize = TStop_GetNumberOfTransfers(stop) + 2;
    stop->transfers = (TLine **) realloc(stop->transfers, sizeof(TLine *) * newSize);
    stop->transfers[newSize - 2] = line;
    stop->transfers[newSize - 1] = NULL;
}

/* Secondary functions */

TStop *TStop_IsNameExists(TStop *head, char *name) {
    for (TStop *current = head; current != NULL; current = current->next)
        if (strcmp(current->name, name) == 0)
            return current;
    return NULL;
}

int TStop_GetNumberOfTransfers(TStop *stop) {
    int count = 0;
    for (TLine *line = stop->transfers[0]; line != NULL; line = stop->transfers[count])
        ++count;
    return count;
}
