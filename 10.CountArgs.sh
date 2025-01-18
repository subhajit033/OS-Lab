#!/bin/bash

# Count the total number of arguments
total_args=$#

# Display the total number of arguments in uppercase (as text)
echo "Total number of arguments: $total_args"

# Display each argument in uppercase
for arg in "$@"; do
    echo "$arg" | tr 'a-z' 'A-Z'
done
