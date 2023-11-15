#include "load.h"

#define BUFFER_SIZE 64

bool LoadConfiguration(const char *fileName, TStop **stops_head, TLine **lines_head) {
    // Open config file
    FILE *configFile = fopen(fileName, "r");
    if (configFile == NULL) {
        perror("[E_0x2]: Provided configuration file cannot be opened!");
        return false;
    }

    // Read config file
    char character;
    char *data = NULL;
    int dataP, dataMaxLength, latestTravelTime;
    bool isNewTLine = true;
    TLine *latestLineCreated = NULL;
    ProcessStage currentStage;

    while ((character = fgetc(configFile)) != EOF) {
        if (isNewTLine)
            currentStage = ProcessSign;

        if (data == NULL) {
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
            TStop *currentStop = NULL;
            switch (currentStage) {
                case ProcessSign:
                    latestLineCreated = TLine_init(data);
                    *lines_head = TLine_push(*lines_head, latestLineCreated);
                    latestTravelTime = -1;
                    currentStage = ProcessStop;
                    break;
                case ProcessStop:
                    // Create new or get existing stop by name
                    currentStop = TStop_IsNameExists(*stops_head, data);
                    if (currentStop == NULL) {
                        currentStop = TStop_init(data);
                        *stops_head = TStop_push(*stops_head, currentStop);
                    }

                    // Add the latest line to the stop's transfers
                    TStop_addTransfer(currentStop, latestLineCreated);

                    // Add the stop to the line
                    TLine_addStop(latestLineCreated, currentStop, latestTravelTime);

                    currentStage = ProcessTime;
                    break;
                case ProcessTime:
                    latestTravelTime = atoi(data);
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
