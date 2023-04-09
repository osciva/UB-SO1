#!/bin/bash

if [ $# -ne 1 ]
then 
    echo "Nombre incorrecte de parametres: $0 <fitxer.txt>"
    exit 1
fi

# Comprovem que el parametre no és un directori.

if [ -d $1 ]
then
    echo "El paràmetre no pot ser un directori."
    exit 1
fi

nombreFitxersExistents=0
nombreFitxersInexistents=0

vector=$(cat $1)

for f in $vector 
do 
    
    if [[ -d $f || -f $f ]]; then
        nombreFitxersExistents=$(($nombreFitxersExistents+1))
    else
        nombreFitxersInexistents=$(($nombreFitxersInexistents+1))

    fi
done

echo "Existeixen: $nombreFitxersExistents" 
echo "No existeixen: $nombreFitxersInexistents" 
