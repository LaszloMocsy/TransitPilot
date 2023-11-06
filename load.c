#include "load.h"

#define BUFFER_SIZE 64

/// Load the specified configuration file if it exists
/// \param fileName The name of the configuration file
/// \param stopsArray An array of <c>TStop</c>s
/// \return `true` if the process was successful, otherwise `false`
bool LoadConfiguration(const char *fileName, TStopsArray *stopsArray, TLinesArray *linesArray) {
    // Open config file
    FILE *configFile = fopen(fileName, "r");
    if (configFile == NULL) {
        perror("[E_0x2]: Provided configuration file cannot be opened!");
        return false;
    }

    // Read config file
    char character;
    char *data = NULL;
    int dataP, dataMaxLength, lastTime;
    bool isNewTLine = true;
    ProcessStage currentStage;

    while ((character = fgetc(configFile)) != EOF) {
        if (isNewTLine)
            currentStage = ProcessSign;

        if (data == NULL) {
            lastTime = -1;
            dataP = 0;
            dataMaxLength = BUFFER_SIZE;
            data = (char *) malloc(sizeof(char) * dataMaxLength);
        } else if (dataP == dataMaxLength) {
            dataMaxLength += BUFFER_SIZE;
            data = (char *) realloc(data, sizeof(char) * dataMaxLength);
        }

        if (character == ';' || character == '\n') {
            data[dataP] = '\0';

            // Process data ("string" between ';' and '\n')
            int id;
            switch (currentStage) {
                case ProcessSign:
                    TLinesArray_push(linesArray, data);
                    currentStage = ProcessStop;
                    break;
                case ProcessStop:
                    id = TStopsArray_push(stopsArray, data, linesArray->count - 1);
                    TLine_AddStop(linesArray->items[linesArray->count - 1], id, lastTime);
                    currentStage = ProcessTime;
                    break;
                case ProcessTime:
                    lastTime = atoi(data);
                    free(data);
                    currentStage = ProcessStop;
                    break;
            }

            data = NULL;
        } else
            data[dataP++] = character;

        isNewTLine = character == '\n';
    }

    fclose(configFile);
    return true;
}
