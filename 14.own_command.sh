#!/bin/bash

# Check if exactly three arguments are passed
if [ "$#" -ne 3 ]; then
    echo "Usage: compute <operation> <num1> <num2>"
    echo "Operations: add, sub, mul, div"
    exit 1
fi

operation=$1
num1=$2
num2=$3

# Perform the calculation based on the operation
case $operation in
    add)
        result=$(echo "$num1 + $num2" | bc)
        echo "Result: $num1 + $num2 = $result"
        ;;
    sub)
        result=$(echo "$num1 - $num2" | bc)
        echo "Result: $num1 - $num2 = $result"
        ;;
    mul)
        result=$(echo "$num1 * $num2" | bc)
        echo "Result: $num1 * $num2 = $result"
        ;;
    div)
        # Check for division by zero
        if [ "$num2" == "0" ]; then
            echo "Error: Division by zero is not allowed."
            exit 1
        fi
        result=$(echo "scale=2; $num1 / $num2" | bc)
        echo "Result: $num1 / $num2 = $result"
        ;;
    *)
        echo "Invalid operation. Please use: add, sub, mul, or div."
        exit 1
        ;;
esac
