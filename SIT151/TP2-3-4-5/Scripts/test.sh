#!/bin/bash
     
     
test_algo(){
	for exe in ../*.exe; do
	    echo "Test avec : $exe"
	    /usr/bin/time -v $exe $1 > /dev/null
	done
}
     
for FILE in $*
    do
    echo ""
    echo "Fichier à traiter : $FILE"
    test_algo $FILE
done
     
