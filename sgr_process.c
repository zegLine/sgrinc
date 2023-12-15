#include "sgr_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CommandType get_command_type(const char *command) {
    if (strcmp(command, "P_SET") == 0) {
        return COMMAND_P_SET;
    } else if (strcmp(command, "BUY") == 0) {
        return COMMAND_BUY;
    } else if (strcmp(command, "RETURN") == 0) {
        return COMMAND_RETURN;
    } else {
        return COMMAND_UNKNOWN;
    }
}

void initialize_sgr_system(SGRSystem *system) {
    system->price = 0.0;
    system->containers = 0;
}

void process_sgr_commands(SGRSystem *system, const char *fileContents) {
    // Create a non-constant copy of fileContents
    char *fileContentsCopy = strdup(fileContents);
    if (fileContentsCopy == NULL) {
        perror("Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    // Initialize token and rest
    char *token, *rest = fileContentsCopy;

    while ((token = strtok_r(rest, "\n", &rest))) {
    char command[20];
    char param_str[20];  // Adjust the size accordingly

    if (sscanf(token, "%s %s", command, param_str) == 2) {
        CommandType commandType = get_command_type(command);

        switch (commandType) {
            case COMMAND_P_SET: {
                system->price = atof(param_str);  // Convert char* to float
                printf("Setting new price: %f\n", system->price);
                break;
            }
            case COMMAND_BUY: {
                system->containers += atoi(param_str);  // Convert char* to int
                printf("Buying %d containers\n", atoi(param_str));
                break;
            }
            case COMMAND_RETURN: {
                system->containers -= atoi(param_str);  // Convert char* to int
                printf("Returning %d containers\n", atoi(param_str));
                break;
            }
            case COMMAND_UNKNOWN:
                printf("Unknown command: %s\n", command);
                break;
        }
    } else {
        printf("Invalid command format: %s\n", token);
    }
}

}
