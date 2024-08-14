#!/bin/bash

# Display menu options
display_menu() {
    echo "Menu Options:"
    echo "1. Get Processor Information"
    echo "2. Create a Testing Directory"
    echo "3. Safe Delete"
    echo "4. MinEdit: A Minimalist CLI-Based C Program Editor"
    echo "5. Exit"
}

# Execute processor information script
get_processor_info() {
    echo "Running Script 1: Get Processor Information"
    ./get_processor_info.sh
}

# Execute create testing directory script
create_testing_directory() {
    echo "Running Script 2: Create a Testing Directory"
    echo "Enter the number of files: "
    read num_files
    ./create_testing_directory.sh "$num_files"
}

# Execute safe delete script
safe_delete() {
    echo "Running Script 3: Safe Delete"
    echo "Enter the file to delete: "
    read file_to_delete
    ./safe_delete.sh "$file_to_delete"
}

# Execute MinEdit C program
minedit() {
    echo "Running Script 4: MinEdit: A Minimalist CLI-Based C Program Editor"
    ./minedit
}

# Main function
main() {
    while true; do
        display_menu
        echo "Enter your choice: "
        read choice

        case $choice in
            1) get_processor_info ;;
            2) create_testing_directory ;;
            3) safe_delete ;;
            4) minedit ;;
            5) echo "Exiting..."; exit 0 ;;
            *) echo "Invalid choice. Please enter a number between 1 and 5." ;;
        esac
    done
}

# Call the main function
main
