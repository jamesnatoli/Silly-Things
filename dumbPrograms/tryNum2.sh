#!/bin/bash

## $1 is output
## $2 is input
## $3 is the mapping file (Ordered_Mapping.csv)

Word2=(`head $2 | tail -8 | cut -d ' ' -f 4`)
Word1=(`head $2 | tail -8 | cut -d ' ' -f 3`)
Word0n=(`head $2 | tail -8 | cut -d ' ' -f 2`)
Word0p=(`head $2 | tail -8 | cut -d ' ' -f 1`)

bits=(`cat $3 | cut -d ',' -f 7`)
sides=(`cat $3 | cut -d ',' -f 1`)
phis=(`cat $3 | cut -d ',' -f 3`)

rings=('-2' '-1' '0' '1' '2')

# index to access the bits
bc=1

> $1

echo "sides,ring,sector,bigphi,phi,eta,LUT,bit" >> $1
for ring in "${rings[@]}"
do
    for sector in {1..12}
    do
	for phi in {0..5}
	do
	    index=0
	    eta2=15
	    eta1=10
	    eta0=9
	    
	    if [ "$ring" == "-2" ] || [ "$ring" == "2" ]
	    then
		while [[ $eta2 -gt 10 ]]
		do
		    echo "${sides[bc]},$ring,$sector,${phis[$bc]},$phi,$eta2,0x$phi${Word2[$index]},${bits[$bc]}" >> $1
		    localsides=${sides[bc]}
		    ((bc++))
		    ((index++))
		    ((eta2--))
		done
		echo "$localsides,$ring,$sector,-,-,-,-,-1" >> $1
		echo "$localsides,$ring,$sector,-,-,-,-,-1" >> $1
		echo "$localsides,$ring,$sector,-,-,-,-,-1" >> $1
		# echo ",,,,,,,,,,,,," >> $1
	    fi
	    
	    if [ "$ring" == "-1" ] || [ "$ring" == "1" ]
	    then
		while [[ $eta1 -gt 4 ]]
		do
		    localring=$((ring - 2))
		    echo "${sides[bc]},$ring,$sector,${phis[$bc]},$phi,$eta1,0x$phi${Word1[$index]},${bits[$bc]}" >> $1
		    ((bc++))
		    ((index++))
		    ((eta1--))
		done
		echo "${sides[bc]},$ring,$sector,-,-,-,-,-1" >> $1
		echo "${sides[bc]},$ring,$sector,-,-,-,-,-1" >> $1
		# echo ",,,,,,,,,,,,," >> $1
            fi
	    
	    fly=$((sector/2)) # to help make this less dumb
	    # this will be even when sector = 1, 4, 5, 8, 9, and 12
	    # and odd when sector = 2, 3, 6, 7, 10, and 11
	    if [ "$ring" == "0" ]
	    then
		while [[ $eta0 -gt 1 ]]
		do
		    localeta=$((eta0/2)) # This will make it double
		    if (( $fly%2 == 1)) ## check if sector is even
		    then # positive
			echo "${sides[bc]},$ring,$sector,${phis[$bc]},$phi,$localeta,0x$phi${Word0p[$index]},${bits[$bc]}" >> $1
		    else # negative
			echo "${sides[bc]},$ring,$sector,${phis[$bc]},$phi,$localeta,0x$phi${Word0n[$index]},${bits[$bc]}" >> $1
		    fi
		    ((bc++))
		    ((eta0--))
		    ((index++))
		done
		# echo ",,,,,,,,,,,,," >> $1
	    fi
	done # close phi
	echo ",,,,,,,,,,,,," >> $1
    done # close sector
done # close ring
