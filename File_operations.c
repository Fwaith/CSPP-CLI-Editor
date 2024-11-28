#include "File_operations.h"

void create_file(char arguments[]) {  
    FILE *file = fopen(arguments, "r");
    // If the file already exists
    if (file != NULL) {
        fclose(file);
        printf("Warning: File '%s' already exists, making a new file will overwrite the old one\n", arguments);
        printf("Proceed to overwrite file ? (y/n)\n");
        printf(">>");
        printf(" ");
        char conformation[10];
        fgets(conformation, sizeof(conformation), stdin);
        // Remove the newline character from the input
        conformation[strcspn(conformation, "\n")] = '\0';
        if (strcmp(conformation, "y") == 0) {
            // Removes the old file and create a new one
            file = fopen(arguments, "w");
            printf("'%s' created successfully\n", arguments);
            fclose(file);
        }
        // Cancels the file creation process
        else if (strcmp(conformation, "n") == 0) {
            printf("File creation cancelled\n");
        }
        else {
            printf("Invalid input\n");
            printf("File creation cancelled\n");
        }
    }
    // If the file doesn't exist
    else {
        file = fopen(arguments, "w");
        printf("'%s' created successfully\n", arguments);
        fclose(file);
    } 
}

void copy_file(char arguments[]) {
    FILE *file = fopen(arguments, "r");
    // If the file doesn't exist
    if (file == NULL) {
        printf("Error: No such file exists, unable to copy file\n");
        return;
    }
    fclose(file); // Close the source file to avoid conflicts
    char copyName[256];
    snprintf(copyName, sizeof(copyName), "%s - Copy", arguments);
    // Check if the first copy name exists
    int counter = 1;
    while ((file = fopen(copyName, "r")) != NULL) {
        fclose(file);
        snprintf(copyName, sizeof(copyName), "%s - Copy(%d)", arguments, ++counter);
    }
    // Create the copy file
    FILE *src = fopen(arguments, "r");
    FILE *dest = fopen(copyName, "w");
    if (src == NULL || dest == NULL) {
        printf("Error: Unable to create copy of the file.\n");
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }
    // Copy content from source file to destination file
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(src);
    fclose(dest);
    printf("File successfully copied to '%s'.\n", copyName);
}

void delete_file(char arguments[]) {
    FILE *file = fopen(arguments, "r");
    // If the file exists
    if (file != NULL) {
        fclose(file);
        // Attempt to delete the file
        if (remove(arguments) == 0) {
            printf("File '%s' deleted successfully.\n", arguments);
        } 
        else {
            printf("Error: Unable to delete file '%s'.\n", arguments);
        }
    }
    // If the file doesn't exist
    else { 
        printf("Error: No such file exists, unable to delete file\n");
    }
}

void show_file(char arguments[]) {
    FILE *file = fopen(arguments, "r");
    // If the file exists
    if (file != NULL) {
        fclose(file);
    }
    // If the file doesn't exist
    else {
        fclose(file);
        printf("Error: No such file exists, unable to show file\n");
    }
}