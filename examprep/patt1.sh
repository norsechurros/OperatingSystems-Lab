#!/bin/bash

search_pattern() {
    input_file=$1
    shift
    patterns="$@"

    for pattern in "$patterns"; do
        echo "Searching for pattern \"$pattern\" in $input_file:"
        grep "$pattern" "$input_file"
    done
}

input_file=$1
shift

while true; do
    read -p "Enter a, b, or c: " choice 

    case "$choice" in
        a) search_pattern "$input_file" "$@" ;;
        b) echo "Delete functionality not implemented yet" ;;
        c) echo "Exiting" ; exit 0 ;;
        *) echo "Invalid choice" ;;
    esac
done
