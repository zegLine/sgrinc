#include <stdio.h>
#include <stdlib.h>

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
    
    if (argc != 2) {
        printf("Usage: %s <storage_file>.sgr\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filePath = argv[1];
    char* fileContents = slurp_file(filePath);

    // Use fileContents as needed
    printf("%s", fileContents);
    // Don't forget to free the allocated memory when done
    free(fileContents);

    return EXIT_SUCCESS;
}
