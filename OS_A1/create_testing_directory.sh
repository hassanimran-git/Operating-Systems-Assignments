#!/bin/bash

# Ensure num of files provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <number_of_files>"
    exit 1
fi

# Create directory if doesnit exist
mkdir -p TestData || exit 1

# create N files with random text
for ((i=1; i<=$1; i++)); do
    echo "Creating file f$i"
    shuf -n 20 /usr/share/dict/words > TestData/f$i.txt
done

echo "Testing directory TestData created with $1 files."
