#!/bin/bash

# echo "Print the third line with a \"z\" in it"

# cat /dev/stdin | cut -f 2 -d ' ' | grep z |head -3 | tail -1
###

echo "Using Let" 

let "a = 4 * 6 + 5"

echo $a
###

echo "Adding 2 command line arguments"

output=$(( $1 * $2))

echo $output
###

echo "Return Tomorrow's Date"
output=$(date | cut -f 3 -d ' ')
((output++))
echo Tomorrow is the $output
###

# echo "Print Random Word"
# option 1
# the problem is that $RANDOM is only 32767 and there are many more words than that
# head -$RANDOM /usr/share/dict/words | tail -1

# option 2
# sort -r /usr/share/dict/words | head -1


echo "Print Random Num"
echo 'How big do you want your random #?'
read var
echo $((RANDOM%var))