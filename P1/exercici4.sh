#!/bin/bash

if [ $# -ne 2 ]
then 
    echo "Nombre incorrecte de parametres: $0 <directori> <int>"
    exit 1
fi

# Comprovem que el primer parametre és un directori.

if [ ! -d $1 ]
then
    echo "El primer paràmetre ha de ser un directori."
    exit 1
fi


directori=$1
bytes=$2


ls -l $directori > f.txt

text=$(awk '{print $9, $5}' f.txt) # guardem en la variable text la novena i la cinquena columna corresponents a el nom del fitxer i el tamany respectivament
comptador=0

for elem in $text
do
    # la variable text queda tal que així: nomfitxer.txt tamany nomfitxer2.txt tamany2 nomfitxer3.txt tamany3 ... etc
    # per tant, agafem els elements senars (comptant des de 0)de la variable text (és a dir, agafem només els tamanys (5a columna) 
    # que és el que ens interessa i guardem a la variable "anterior" el nom de l'arxiu)

    if [ $(( comptador%2 )) -eq 1 ]
    then

        # comprobem que sigui mes gran que el tamany(en bytes) passat per paràmetre i que sigui un fitxer

        if [ $elem -ge $bytes ] && [ -f $directori/$anterior ]
        then
            echo "$anterior: $elem"
        fi

    fi

    anterior=$elem

    ((comptador++))

done

exit 0