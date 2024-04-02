#!/bin/bash

# Read input values for variables a and b
read a b

# Check if a is equal to b
if [ "$a" == "$b" ]; then
    echo "$a is equal to $b"
# Check if a is greater than b
elif [ "$a" -gt "$b" ]; then
    echo "$a is greater than $b"
# Check if a is less than b
elif (( a < b )); then
    echo "$a is less than $b"
# If none of the above conditions are met, print a default message
else
    echo "None of the conditions are met"
fi
