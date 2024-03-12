#!/bin/bash

echo "Enter number of elements: "
read num

echo "Enter elements of array: "
read -a arr

echo "Input elements are: ${arr[@]}"

bubbleSort() {
    local array=("$@")
    local n=$1

    for ((i = 0; i < n - 1; i++)); do
        for ((j = 0; j < n - i - 1; j++)); do
            if (( ${array[j]} > ${array[j+1]} )); then
                temp=${array[j]}
                array[j]=${array[j+1]}
                array[j+1]=$temp
            fi
        done
    done

    echo "Sorted array is: ${array[@]}"
}

bubbleSort "${arr[@]}" "$num"
