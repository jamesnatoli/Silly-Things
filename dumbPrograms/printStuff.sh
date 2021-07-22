#!/bin/bash

# <(1) is txt output> <(2) is the csv output> <(3) is the input

Word2n=(`cat $3 | cut -d ' ' -f 1`)
Word1n=(`cat $3 | cut -d ' ' -f 2`)
Word0=(`cat $3 | cut -d ' ' -f 3`)
Word1p=(`cat $3 | cut -d ' ' -f 4`)
Word2p=(`cat $3 | cut -d ' ' -f 5`)

# Erase the files for new witing
> $1
> $2

sectorCount=1
echo "THIS,IS,SECTOR,$sectorCount" >> $2

for phi in {1..72}
do
    echo "phi is $phi" >> $1
    echo "phi is $phi" >> $2 

    eta0=4
    eta1=10
    eta2=15
    index=0
    # string=""
    # CsvString=""
    echo "Ring0_N Ring0_P Ring1 Ring2" >> $1
    echo "eta2,Ring2n,eta1,Ring1n,eta0,Ring0,eta1,Ring1p,eta2,Ring2p" >> $2
    while [[ $eta1 -gt 4 ]]
    do
	if [[ $eta2 -gt 10 ]]
        then
            string+="  $eta2 0x$phi${Word2[$index]}"
            CsvString="$eta2,0x$phi${Word2n[$index]}"
        else
            string+="  ___"
            CsvString=","
        fi
	CsvString+=",$eta1,0x$phi${Word1n[$index]}"
	if [[ $eta0 -gt 0 ]]
	then
	    string="$eta0 0x$phi${Word0n[$index]} $eta0 0x$phi${Word0p[$index]}"
	    CsvString+=",$eta0,0x$phi${Word0[$index]}"
	else
	    string="___ ___"
	    CsvString+=",,"
	fi
	string+="  $eta1 0x$phi${Word1[$index]}"
	CsvString+=",$eta1,0x$phi${Word1p[$index]}"
	if [[ $eta2 -gt 10 ]]
	then
	    string+="  $eta2 0x$phi${Word2[$index]}"
	    CsvString+=",$eta2,0x$phi${Word2p[$index]}"
	else
	    string+="  ___"
	    CsvString+=",,"
	fi
	echo $string >> $1
	echo $CsvString >> $2
	((eta0--))
	((eta1--))
	((eta2--))
	((index++))
    done
    
    if (($phi%6 == 0))
    then
	echo " " >> $1
	echo ",,,,,,,," >> $2
	((sectorCount++))
	echo "THIS,IS,SECTOR,$sectorCount" >> $2
    fi
done

