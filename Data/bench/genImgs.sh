#!/bin/bash

for i in $(seq 10 10 2000); do
    convert $1 -scale "${i}x${i}" "i_$i.ppm"
done
