#!/bin/bash

# Call with ./random.sh <int_min> <int_max>

diff=$(($2 - $1))

var1=$(($RANDOM%$diff)) # Gets the correct range

var2=$(($var1 + $1)) # Shift the range to the correct position

echo $var2
