#!/bin/bash

while true; do
    clear
    echo "========================="
    echo "     DIGITAL CLOCK       "
    echo "========================="
    # Display current time in HH:MM:SS format
    date +"     %H:%M:%S"
    echo "========================="
    sleep 1  # Wait for 1 second before refreshing
done
