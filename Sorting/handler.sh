#!/bin/bash

sed -i -e "s/^#define SIZE [0-9][0-9]/#define SIZE ${1}/" randSort.cpp
head -15 randSort.cpp
if [ $(g++ randSort.cpp) ]; then
    ./a.out
else
    echo "COMPILE ERROR"
fi
