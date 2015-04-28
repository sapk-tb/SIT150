#!/bin/bash


test_algo(){
	while read algo; do
	  echo $algo
	  time ./a.exe -t $algo -f $1
	done < liste_algo
}

for FILE in $*
do
        echo $FILE
        test_algo $FILE
done

