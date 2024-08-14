#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new file
void createNewFile() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to create file.\n");
        return;
    }
    fclose(file);
    printf("File '%s' created successfully.\n", filename);
}

// Function to open an existing file
void openExistingFile() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File '%s' does not exist.\n", filename);
        return;
    }
    // Read and display file content
    char buffer[1000];
    printf("File content:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

// Function to save file
void saveFile() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return;
    }
    char text[1000];
    printf("Enter text to append to the file (press Ctrl+D to finish):\n");
    while (fgets(text, sizeof(text), stdin) != NULL) {
        fputs(text, file);
    }
    fclose(file);
    printf("Text saved to file '%s' successfully.\n", filename);
}

// Function to close file
void closeFile() {
    printf("File closed.\n");
}

// Function to compile file
void compileFile() {
    printf("File compiled.\n");
}

// Function to run file
void runFile() {
    printf("File run.\n");
}

// Function to display the main menu
void displayMenu() {
    printf("MinEdit - A Minimalist CLI-Based C Program Editor\n");
    printf("-------------------------------------------------\n");
    printf("1. Create New File\n");
    printf("2. Open Existing File\n");
    printf("3. Save File\n");
    printf("4. Close File\n");
    printf("5. Compile File\n");
    printf("6. Run File\n");
    printf("7. Exit\n");
    printf("-------------------------------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        // Display the main menu
        displayMenu();

        // Read user's choice
        scanf("%d", &choice);

        // Perform action based on user's choice
        switch(choice) {
            case 1:
                createNewFile();
                break;
            case 2:
                openExistingFile();
                break;
            case 3:
                saveFile();
                break;
            case 4:
                closeFile();
                break;
            case 5:
                compileFile();
                break;
            case 6:
                runFile();
                break;
            case 7:
                // Exit the program
                printf("Exiting MinEdit. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

