#!/bin/bash

search_pattern()
{
inp_file= $1
shift 
patterns="$@"

	for patterns in ${inp_file}; do
	grep "$patterns" "$inp_file"
done
} 



{

input_file = $1
shift 

while true; do
read -p "Enter a ,b,c: " choice 

case "$choice" in
a) search_pattern "$input_file" "$@" ;;
b) ;;
c) echo "exiting"; exit 0;;
*) echo "invalid"

esac

done
}
