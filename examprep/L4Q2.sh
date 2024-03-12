#!/bin/bash

for file in "$@"; do

	if [ -f "$file" ]; then
	read -p "Do you wanna remove $file? (y/n: )" choice 
	case "$choice" in 
	y|Y) rm "$file" ;;
	n|N) echo "not removed" ;;
	*) echo "invalid"
	esac
	else echo "not a valid file"
	fi
done
