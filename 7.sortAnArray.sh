#!/bin/bash

# Prompt the user to enter numbers separated by spaces
read -p "Enter numbers separated by spaces: " -a numbers

# Sort the numbers in ascending order using `sort`
sorted_numbers=($(echo "${numbers[@]}" | tr ' ' '\n' | sort -n))

# Display the sorted numbers
echo "Numbers in ascending order: ${sorted_numbers[@]}"
