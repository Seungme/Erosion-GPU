#!/bin/bash

IMG="../Data/bench/i_900.ppm"
echo "" > "$2"
for i in $(seq 3 2 11); do
    echo $i
    echo -n "$i," >> "$2"
    "$1" "$IMG" "$i" >> "$2"
done
