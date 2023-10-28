#ifndef TRANSITPILOT_LOAD_H
#define TRANSITPILOT_LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"

struct FileLines;

struct FileLines GetEachLineFromFile(FILE *configFile);
bool LoadConfigFile(const char *fileName);

#endif //TRANSITPILOT_LOAD_H
