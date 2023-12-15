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

void exec_command(char* cmd, char* arg, SGRSystem *system) {
    CommandType commandType = get_command_type(cmd);

        switch (commandType) {
            case COMMAND_P_SET: {
                system->price = atof(arg);  // Convert char* to float
                printf("Setting new price: %f\n", system->price);
                break;
            }
            case COMMAND_BUY: {
                system->containers += atoi(arg);  // Convert char* to int
                printf("Buying %d containers\n", atoi(arg));
                break;
            }
            case COMMAND_RETURN: {
                system->containers -= atoi(arg);  // Convert char* to int
                printf("Returning %d containers\n", atoi(arg));
                break;
            }
            case COMMAND_UNKNOWN:
                printf("Unknown command: %s\n", cmd);
                break;
        }
}

void initialize_sgr_system(SGRSystem *system) {
    system->price = 0.0;
    system->containers = 0;
}

void process_sgr_commands_file(SGRSystem *system, const char *fileContents) {
    // Create a non-constant copy of fileContents
    char *fileContentsCopy = strdup(fileContents);
    if (fileContentsCopy == NULL) {
        perror("Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    // Initialize token and rest
    char *token, *rest = fileContentsCopy;

    while ((token = strtok_r(rest, "\n", &rest))) {
        char *command = malloc(strlen(token) + 1);
        char *param_str = malloc(strlen(token) + 1);  // Adjust the size accordingly

        if (!command || !param_str) {
            perror("mem alloc failure");
            exit(EXIT_FAILURE);
        }

        if (sscanf(token, "%s %s", command, param_str) == 2) {

            if (strlen(param_str) > 5) {
                perror("value too high for parameter");
                exit(EXIT_FAILURE);
            }

            exec_command(command, param_str, system);
        } else {
            printf("Invalid command format: %s\n", token);
        }


        free(command);
        free(param_str);

    }

}
