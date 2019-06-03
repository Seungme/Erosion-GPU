#!/bin/bash

IMGDIR="../Data/bench/"
FILES=$(echo ${IMGDIR}i_*)
echo "" > "$2"
for i in $(seq 10 10 2000); do
    FILE="${IMGDIR}i_$i.ppm"
    echo $i
    echo -n "$i," >> "$2"
    "$1" "$FILE" 3 >> "$2"
done
