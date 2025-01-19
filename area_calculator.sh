#!/bin/bash

# Function to calculate the area of a circle
area_circle() {
    echo -n "Enter the radius of the circle: "
    read radius
    area=$(echo "3.14159 * $radius * $radius" | bc)
    echo "The area of the circle is: $area"
}

# Function to calculate the area of a rectangle
area_rectangle() {
    echo -n "Enter the length of the rectangle: "
    read length
    echo -n "Enter the width of the rectangle: "
    read width
    area=$(echo "$length * $width" | bc)
    echo "The area of the rectangle is: $area"
}

# Function to calculate the area of a triangle
area_triangle() {
    echo -n "Enter the base of the triangle: "
    read base
    echo -n "Enter the height of the triangle: "
    read height
    area=$(echo "0.5 * $base * $height" | bc)
    echo "The area of the triangle is: $area"
}

# Main menu for user input
while true; do
    echo
    echo "Select the shape to calculate area:"
    echo "1. Circle"
    echo "2. Rectangle"
    echo "3. Triangle"
    echo "4. Exit"
    echo -n "Enter your choice (1-4): "
    read choice

    case $choice in
        1)
            area_circle
            ;;
        2)
            area_rectangle
            ;;
        3)
            area_triangle
            ;;
        4)
            echo "Exiting program. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please select a valid option."
            ;;
    esac
done
