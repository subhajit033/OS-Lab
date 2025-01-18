#!/bin/bash

# Function to convert a date to the number of seconds since Unix Epoch
date_to_seconds() {
    date -d "$1" +%s
}

# Prompt user to enter the first date
read -p "Enter the first date (dd/mm/yyyy): " date1

# Prompt user to enter the second date
read -p "Enter the second date (dd/mm/yyyy): " date2

# Convert the dates to seconds since the Unix epoch
date1_seconds=$(date_to_seconds "$date1")
date2_seconds=$(date_to_seconds "$date2")

# Calculate the absolute difference in seconds
diff_seconds=$((date2_seconds - date1_seconds))
if [ $diff_seconds -lt 0 ]; then
    diff_seconds=$(( -1 * diff_seconds )) # Make the difference positive
fi

# Convert seconds to days
diff_days=$((diff_seconds / 86400))

# Display the result
echo "The difference between $date1 and $date2 is $diff_days days."
