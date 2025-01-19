#!/bin/bash

# Prompt the user to input five city names
echo "Enter five city names (one per line):"
read -a cities
# Store the city names in an array
#cities=("$city1" "$city2" "$city3" "$city4" "$city5")

# Sort city names in ascending order
echo "Cities in ascending order:"
echo "${cities[@]}" | tr ' ' '\n' | sort

# Sort city names in descending order
echo "Cities in descending order:"
echo "${cities[@]}" | tr ' ' '\n' | sort -r