#!/bin/bash

timeString=$(date | cut -f 4 -d ' ')
hours=$(echo $timeString | cut -f 1 -d ':')
mins=$(echo $timeString | cut -f 2 -d ':')
secs=$(echo $timeString | cut -f 3 -d ':')
sumSec=$(echo "$hours*3600 + $mins*60 + $secs" | bc -l)
percent=$(echo "($sumSec/86400)" | bc -l)
dHours=$(echo "$percent/10" | bc -l | head -c 3 | tail -c 2)
dMins=$(echo "$percent" | bc -l | head -c 4 | tail -c 2)
dSecs=$(echo "$percent" | bc -l| head -c 6| tail -c 2)
echo "$dHours:$dMins:$dSecs"



