#include "load.h"

#define BUFFER_SIZE 512

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

    // Read each line of the config file
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
            line_buffer[idx++] = (char) character;
            character = getc(configFile);
        }
        
        line_buffer[idx] = '\0';
        if (strlen(line_buffer)) {
            //TODO: Process line (line_buffer)
        }
        free(line_buffer);
    } while (character != EOF);

    fclose(configFile);
    return true;
}
