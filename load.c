#include "load.h"

#define BUFFER_SIZE 64;

/// Returns all lines from the file, each as a dynamic char array. After use, all the dynamic char arrays need to be freed!
/// \param configFile Source file
/// \return A custom struct that contains the strings and the count of them
FileLines GetEachLineFromFile(FILE *configFile) {
    FileLines obj = {0, NULL};

    int character;
    do {
        character = getc(configFile);
        int idx = 0;
        int bufferMaxLength = BUFFER_SIZE;
        char *line_buffer = (char *) malloc(sizeof(char) * bufferMaxLength);

        while (character != '\n' && character != EOF) {
            if (idx == bufferMaxLength) {
                bufferMaxLength += BUFFER_SIZE;
                line_buffer = (char *) realloc(line_buffer, bufferMaxLength);
            }
            line_buffer[idx] = (char) character;
            character = getc(configFile);
            ++idx;
        }
        line_buffer[idx] = '\0';

        if (strlen(line_buffer)) {
            char *newString = (char *) malloc(sizeof(char) * (strlen(line_buffer) + 1));
            strcpy(newString, line_buffer);
            ++obj.count;
            obj.array = (char **) realloc(obj.array, sizeof(char *) * obj.count);
            obj.array[obj.count - 1] = newString;
        }

        free(line_buffer);
    } while (character != EOF);

    return obj;
}

/// Processes a string from the configuration file.
/// \param fileLine The string that needs to be processed
/// \return The memory address of the newly created `TransitLine`
TransitLine *ProcessFileLine(const char *fileLine) {
    TransitLine *transitLine;
    int textLength = 0;
    char *text = NULL;
    int time = -1;
    ProcessStep currentStep = ReadSignature;

    for (int idx = 0; idx < (strlen(fileLine) + 1); ++idx) {
        char character = fileLine[idx];

        if (character != ';' && character != '\0') {
            ++textLength;
            text = (char *) realloc(text, sizeof(char) * textLength);
            text[textLength - 1] = character;
        } else {
            ++textLength;
            text = (char *) realloc(text, sizeof(char) * textLength);
            text[textLength - 1] = '\0';

            switch (currentStep) {
                case ReadSignature:
                    transitLine = CreateTransitLine(text);
                    free(text);
                    currentStep = ReadStop;
                    break;
                case ReadStop:
                    AddStopToTransitLine(transitLine, text, time);
                    currentStep = ReadTime;
                    break;
                case ReadTime:
                    sscanf(text, "%d", &time);
                    free(text);
                    currentStep = ReadStop;
                    break;
            }
            text = NULL;
            textLength = 0;
        }
    }
    free(text);

    if (currentStep == ReadSignature || currentStep == ReadStop)
        perror("[E_0x3]: Invalid line in the configuration file!");

    return transitLine;
}

/// Loads the specified configuration file if it exists
/// \param fileName The name of the configuration file
/// \param storage A `TransitLineArray` that will be populated with the configuration files data
/// \return `true` if the load was successful, otherwise `false`
bool LoadConfigFile(const char *fileName, TransitLineArray *storage) {
    FILE *configFile = fopen(fileName, "r");
    if (configFile == NULL) {
        perror("[E_0x2]: Provided configuration file cannot be opened!");
        return false;
    }

    FileLines eachLineFromFile = GetEachLineFromFile(configFile); //TODO: Process each line
    for (int idx = 0; idx < eachLineFromFile.count; ++idx) {
        TransitLine *line = ProcessFileLine(eachLineFromFile.array[idx]);
        PushTransitLineToTransitLineArray(storage, line);
    }

    for (int idx = 0; idx < eachLineFromFile.count; ++idx)
        free(eachLineFromFile.array[idx]);
    free(eachLineFromFile.array);

    fclose(configFile);
    return true;
}
