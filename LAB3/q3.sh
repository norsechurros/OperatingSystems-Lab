 #!/bin/bash

#source ~/Desktop/220953306/LAB3/wcwc.sh

# Rename all *.txt to *.text
for file in *.txt; do
    mv "$file" "${file%.txt}.text"
done
