#ifndef TRANSITPILOT_LOAD_H
#define TRANSITPILOT_LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "lines.h"

typedef enum ProcessStep {
    ReadSignature,
    ReadStop,
    ReadTime
} ProcessStep;

typedef struct FileLines {
    int count;
    char **array;
} FileLines;

FileLines GetEachLineFromFile(FILE *configFile);

TransitLine *ProcessFileLine(const char *fileLine);

bool LoadConfigFile(const char *fileName, TransitLineArray *storage);

#endif //TRANSITPILOT_LOAD_H
