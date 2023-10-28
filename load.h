#ifndef TRANSITPILOT_LOAD_H
#define TRANSITPILOT_LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"

typedef struct FileLines {
    int count;
    char **array;
} FileLines;

struct FileLines GetEachLineFromFile(FILE *configFile);

bool LoadConfigFile(const char *fileName);

#endif //TRANSITPILOT_LOAD_H
