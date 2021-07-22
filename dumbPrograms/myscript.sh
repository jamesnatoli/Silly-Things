#!/bin/bash
# Sample Scipt

echo Hi there!

var=$( cat GermanWords.txt )

echo $var
echo

name=dummy/under
mkdir -p $name
cd $name
touch exampleFile

cd -

title=other
mkdir $title
echo here1
cp -R dummy other
