#!/bin/bash

# ensure only one argument 
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file_to_delete>"
    exit 1
fi

# check if given file exists
if [ ! -f "$1" ]; then
    echo "Error: File '$1' does not exist!"
    exit 1
fi

mkdir -p "MyTrash" || exit 1
mv "$1" "MyTrash/"
echo "File '$1' moved to trash directory 'MyTrash'."
