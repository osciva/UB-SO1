#!/bin/bash

if [ $# -ne 3 ]
then 
    echo "Nombre incorrecte de parametres: $0 <Directori> <Extensió> <String>"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "El primer paràmetre ha de ser un directori."
    exit 1
fi

directori=$1
cadena=$3

var=${cadena,,} # Convertim la paraula a minúscules, així ens assegurem que no hi hagi problemes




variable=$(find $1 -name "*.$2")
for elem in $variable;
do
    num=$(grep -i -o $3 $elem | wc -l)
    echo "$elem"
    echo "Surt $num vegades"  # find $directori otorga el nombre de todos los ficheros, 
# el comando grep cuenta el número de veces que aparece la cadena en el archivo y wc -l le dice a wc que cuente el número de líneas. 
# Así es como se deduce el número total de palabras coincidentes.

done
exit 0