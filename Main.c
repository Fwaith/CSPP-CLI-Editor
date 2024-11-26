#include "Append_file.h"
#include "Copy_file.h"
#include "Create_file.h"
#include "Delete_file.h"
#include "Delete_line.h"
#include "Insert_line.h"
#include "Show_change_log.h"
#include "Show_file.h"
#include "Show_help.h"
#include "Show_line.h"
#include "Show_number_of_lines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define INSTALL_PATH_SRC "ate.exe" // Source path of the executable
#define INSTALL_PATH_DEST "C:\\Windows\\ate.exe" // Destination path
#else
#include <sys/stat.h>
#define INSTALL_PATH_SRC "./ate" // Source path of the executable
#define INSTALL_PATH_DEST "/usr/local/bin/ate" // Destination path
#endif

int is_installed() {
    char buffer[MAX_PATH]; // Buffer to hold the full path of the executable

    // Use SearchPath to find 'ate.exe' in the PATH
    if (SearchPath(NULL, "ate.exe", NULL, MAX_PATH, buffer, NULL) != 0) {
        return 1; // Found 'ate.exe'
    }
    return 0; // Not found
}

// Function to install the 'ate' command
void install() {
    // Check if 'ate' is already installed
    if (is_installed()) {
        printf("'ate' is already installed. Skipping installation.\n");
        return;
    }
    char command[256]; // Buffer to store the command

#ifdef _WIN32
    // Copy the executable to C:\Windows
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH_DEST);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    } else {
        printf("Error: Failed to install 'ate'. Try running as Administrator.\n");
    }
#else
    // Move the executable to /usr/local/bin
    snprintf(command, sizeof(command), "sudo mv \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH_DEST);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    } else {
        printf("Error: Failed to install 'ate'. Try running with sudo.\n");
    }
#endif
}

int main() {
    install();
    char input[100];  // Buffer to store user input
    int running = 0;  // Control variable for the loop

    printf("Welcome to the A-Text-Editor Command-Line Editor\n");
    printf("Type 'ate help' for a full list of commands.\n");

    while (running == 0) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;    
        if (strcmp(input, "ate exit")==0) {
            running = 1;
        } 
        else if (strcmp(input, "ate help")==0) {
            show_help();
        } 
        else {
            printf("Invalid command\n");
        }
    }
    return 0;
}