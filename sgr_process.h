#ifndef SGR_PROCESS_H
#define SGR_PROCESS_H

typedef struct {
    float price; // Price for the deposit
    int containers; // Number of containers in the system
} SGRSystem;

typedef enum {
    COMMAND_P_SET,
    COMMAND_BUY,
    COMMAND_RETURN,
    COMMAND_UNKNOWN
} CommandType;

void initialize_sgr_system(SGRSystem *system);
void process_sgr_commands_file(SGRSystem *system, const char *fileContents);

#endif // SGR_PROCESS_H
