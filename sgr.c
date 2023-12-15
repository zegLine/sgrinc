#include "sgr_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* slurp_file(const char * filepath) {
    FILE* file = fopen(filepath, "rb");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* filecontents = (char*)malloc(filesize + 1);
    if (filecontents == NULL) {
        fclose(file);
        perror("Mem alloc fail");
        exit(EXIT_FAILURE);
    }

    fread(filecontents, 1, filesize, file);
    fclose(file);

    filecontents[filesize] = '\0';

    return filecontents;
}

int main(int argc, char **argv) {

    SGRSystem sgrSystem;
    initialize_sgr_system(&sgrSystem);

    
    if (argc == 2) {
        // Run the program with a file
        const char* filePath = argv[1];
        char* fileContents = slurp_file(filePath);

        // Use fileContents as needed
        printf("%s", fileContents);

        // Process SGR commands from file
        process_sgr_commands(&sgrSystem, fileContents);

        // Free memory for now
        free(fileContents);
    } else if (argc == 1) {
        // No parameters provided, wait for user input
        printf("Enter SGR commands. Type 'exit' to quit.\n");
        char inputBuffer[1024];
        size_t i = 0;
        while (1) {
            int c = getchar();

            if (c == '\n' || c == EOF) {
                inputBuffer[i] = '\0';

                if (strcmp(inputBuffer, "exit") == 0) {
                    break;
                }

                // Process SGR commands from user input
                process_sgr_commands(&sgrSystem, inputBuffer);

                // Reset the buffer index
                i = 0;
            } else if (i < sizeof(inputBuffer) - 1) {
                // Store the character in the buffer
                inputBuffer[i++] = (char)c;
            }
        }
    } else {
        printf("Usage: %s <storage_file>.sgr\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}