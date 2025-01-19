#!/bin/bash

# Prompt the user to enter the input file name
read -p "Enter the input file name: " input_file

# Prompt the user to enter the line number to fetch (m)
read -p "Enter the line number to fetch (m): " m

# Check if the file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' does not exist."
    exit 1
fi

# Count the number of lines in the file
total_lines=$(wc -l < "$input_file")

# Check if m is less than n
if [ "$m" -ge "$total_lines" ]; then
    echo "Error: m ($m) should be less than the total number of lines ($total_lines)."
    exit 1
fi

# Fetch the mth line and store it in another file
output_file="output_line_$m.txt"
sed -n "${m}p" "$input_file" > "$output_file"

# Display the result
echo "The mth line has been saved to $output_file."
echo "Contents of '$output_file':"
cat "$output_file"
