#!/bin/bash                                                                                                                           
Word2=(`cat $2 | cut -d ' ' -f 1`)
Word1=(`cat $2 | cut -d ' ' -f 2`)
Word0n=(`cat $2 | cut -d ' ' -f 3`)
Word0p=(`cat $2 | cut -d ' ' -f 4`)

# Erase the files for new witing                                                                                                                        
> $1

sector=1
## Ring -2
echo "BEGIN,RING,-2" >> $1
echo "SECTOR,$sector" >> $1
echo "phi,eta,LUT" >> $1
for phi in {0..71}
do
    localPhi=$((phi%6))
    index=0
    eta2=15
    while [[ $eta2 -gt 7 ]]
    do
	echo "$localPhi,$eta2,0x$localPhi${Word2[$index]}" >> $1
	((index++))
	((eta2--))
    done
    
    if (( $phi == 71 ))
    then
	break
    fi

    if (( ($phi+1)%6 == 0 ))
    then
	((sector++))
	echo ",,,,,,,," >> $1
	echo "SECTOR,$sector" >> $1
	echo "phi,eta,LUT" >> $1
    fi
done

## Ring -1
sector=1
echo "BEGIN,RING,-1" >> $1
echo "SECTOR,$sector" >> $1
echo "phi,eta,LUT" >> $1
for phi in {0..71}
do
    localPhi=$((phi%6))
    eta1=10
    index=0
    while [[ $eta1 -gt 2 ]]
    do
	echo "$localPhi,$eta1,0x$localPhi${Word1[$index]}" >> $1
	((index++))
        ((eta1--))
    done

    if (( $phi == 71 ))
    then
        break
    fi
    
    if (( ($phi+1)%6 == 0 ))
    then
	((sector++))
	echo ",,,,,,,," >> $1
        echo "SECTOR,$sector" >> $1
	echo "phi,eta,LUT" >> $1
    fi
done
    
## Ring 0 NEGATIVE
sector=1
echo "BEGIN,RING,0" >> $1
echo "SECTOR,$sector" >> $1
echo "phi,eta,LUT" >> $1

for phi in {0..71}    
do
    localPhi=$((phi%6))
    eta0n=4
    eta0p=1
    fly=$((sector/2))
    index=0
    while [[ $eta0n -gt 0 ]]
    do
	if (( $fly%2 == 0))
	then
	    echo "$localPhi,$eta0n,0x$localPhi${Word0n[$index]}" >> $1
	else
	    echo "$localPhi,$eta0n,0x$localPhi${Word0p[$index]}" >> $1
	fi
        ((eta0n--))
	((index++))
    done
    
    index=0
    while [[ $eta0p -lt 5 ]]
    do
	if (( $fly%2 == 0))
        then
            echo "$localPhi,$eta0p,0x$localPhi${Word0n[$index]}" >> $1
        else
            echo "$localPhi,$eta0p,0x$localPhi${Word0p[$index]}" >> $1
        fi
        ((eta0p++))
        ((index++))
    done

    if (( $phi == 71 ))
    then
        break
    fi
     
    if (( ($phi+1)%6 == 0 ))
    then
	((sector++))
	echo ",,,,,,,," >> $1
        echo "SECTOR,$sector" >> $1
	echo "phi,eta,LUT" >> $1
    fi
done

## Ring 1
sector=1
echo "BEGIN,RING,1" >> $1
echo "SECTOR,$sector" >> $1
echo "phi,eta,LUT" >> $1

for phi in {0..71}
do
    localPhi=$((phi%6))
    eta1=15
    index=0
    while [[ $eta1 -gt 4 ]]
    do
	echo "$localPhi,$eta1,0x$localPhi${Word1[$index]}" >> $1
	((index++))
        ((eta1--))
    done

    if (( $phi == 71 ))
    then
        break
    fi

    if (( ($phi+1)%6 == 0 ))
    then
	((sector++))
	echo ",,,,,,,," >> $1
        echo "SECTOR,$sector" >> $1
	echo "phi,eta,LUT" >> $1
    fi
done

## Ring 2
sector=1
echo "BEGIN,RING,2" >> $1
echo "SECTOR,$sector" >> $1
echo "phi,eta,LUT" >> $1

for phi in {0..71}
do
    localPhi=$((phi%6))
    eta2=15
    index=0
    while [[ $eta2 -gt 10 ]]
    do
	echo "$localPhi,$eta2,0x$localPhi${Word2n[$index]}" >> $1
	((index++))
        ((eta2--))
    done
    
    if (( $phi == 71 ))
    then
        break
    fi

    if (( ($phi+1)%6 == 0 ))
    then
	((sector++))
	echo ",,,,,,,," >> $1
        echo "SECTOR,$sector" >> $1
	echo "phi,eta,LUT" >> $1
    fi
done
