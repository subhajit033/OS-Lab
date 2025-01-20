#!/bin/bash

# Print today's date
echo "Today's Date: $(date +'%Y-%m-%d')"

# Print the current time
echo "Current Time: $(date +'%H:%M:%S')"

# Print the current month's calendar explicitly
current_month=$(date '+%m')    # Get the current month (numeric)
current_year=$(date '+%Y')     # Get the current year
echo "Current Month's Calendar:"
cal $current_month $current_year
