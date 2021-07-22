#!/bin/bash

# Enter the letters seperated by spaces

#egrep -v [^$1$2$3$4$5$6$7] ~/english-words/words.txt | egrep $1{1}

#egrep -v [^$1$2$3$4$5$6$7] ~/english-words/words.txt | egrep $1{1} | egrep $2{1}

egrep -v [^$1$2$3$4$5$6$7] ~/english-words/words.txt | egrep $1{1} | egrep $2{1} | egrep $3{1} | egrep $4{1} | egrep $5{1} | egrep $6{1} | egrep $7{1}


