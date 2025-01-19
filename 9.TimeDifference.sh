#!/bin/bash

# Function to convert DD/MM/YYYY to YYYY-MM-DD
convert_date_format() {
    echo "$1" | awk -F/ '{printf "%04d-%02d-%02d", $3, $2, $1}'
}

# Prompt user to enter the first date
read -p "Enter the first date (dd/mm/yyyy): " date_a

# Prompt user to enter the second date
read -p "Enter the second date (dd/mm/yyyy): " date_b

# Convert dates to YYYY-MM-DD format
date1=$(convert_date_format "$date_a")
date2=$(convert_date_format "$date_b")

# Convert dates to seconds since the Unix epoch
date1_seconds=$(date -d "$date1" +%s)
date2_seconds=$(date -d "$date2" +%s)

# Validate if date conversion succeeded


# Calculate the absolute difference in seconds
diff_seconds=$((date2_seconds - date1_seconds))
if [ $diff_seconds -lt 0 ]; then
    diff_seconds=$(( -1 * diff_seconds )) # Make the difference positive
fi

# Convert seconds to days
diff_days=$((diff_seconds / 86400))

# Display the result
echo "The difference between $date_a and $date_b is $diff_days days."
