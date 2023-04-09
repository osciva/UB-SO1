#! /bin/bash

if [ $# -ne 1 ]
then 
    echo "Nombre incorrecte de parametres: $0 <directori>"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "El paràmetre ha de ser un directori."
    exit 1
fi

directori=$1

for dir in $( find $directori -type d )
do
    numero_fitxers=$(find $dir -maxdepth 1 -type f  | wc -l) #maxdepth limita/acota la quantitat de subdirectoris que recorrerem
    echo "directori: $dir nfiles: $numero_fitxers"

done
