#include "load.h"

#define BUFFER_SIZE 64

/// Load the specified configuration file if it exists
/// \param fileName The name of the configuration file
/// \return `true` if the process was successful, otherwise `false`
bool LoadConfiguration(const char *fileName) {
    // Open config file
    FILE *configFile = fopen(fileName, "r");
    if (configFile == NULL) {
        perror("[E_0x2]: Provided configuration file cannot be opened!");
        return false;
    }

    // Read config file
    char character;
    char *data = NULL;
    int dataP, dataMaxLength;
    bool isNewTLine = true;
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
            switch (currentStage) {
                case ProcessSign:
                    printf("---==O: %s :O==---\n", data);
                    currentStage = ProcessStop;
                    break;
                case ProcessStop:
                    printf("Stop: %s\n", data);
                    currentStage = ProcessTime;
                    break;
                case ProcessTime:
                    printf("Time: %d\n", atoi(data));
//                    free(data); // FIXME: Uncomment this line after debug
                    currentStage = ProcessStop;
                    break;
            }

            free(data); //FIXME: Remove to reserve the data string (for signs and stops)
            data = NULL;
        } else
            data[dataP++] = character;

        isNewTLine = character == '\n';
    }

    fclose(configFile);
    return true;
}
