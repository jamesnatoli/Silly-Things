#!/bin/bash

# put a 0 if FROM hex, put a 1 if TO hex (as second parameter)

function letterConvert {
    case "$1" in
	a)
	    result=10
	    ;;
	b)
	    result=11
	    ;;
	c)
	    result=12
	    ;;
	d)
	    result=13
	    ;;
	e)
	    result=14
	    ;;
	f)
	    result=15
	    ;;
	*)
	    result=$1
	    ;;
    esac
    echo $result
}

length=${#1}

function fromHex{
    digit=($(echo $1 | grep -o .))
    
    # can access the digits in here
    let counter=length-1
    
    sum=0
    for i in ${digit[@]}
    do
	num=$(letterConvert $i)
	let sum+="16**$counter * $num"
	((counter--))
    done
    
    echo "$1 in decimal is $sum"
}

function toHex {
    number=$1
    while [[ number -gt 0 ]]
}