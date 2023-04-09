#!/bin/bash

if [ $# -ne 1 ]
then 
    echo "Nombre incorrecte de parametres: $0 <String>"
    exit 1
fi


var=$1 
var=${var,,} # Convertim la paraula a minúscules, així ens assegurem que no hi hagi problemes


longitud_paraula=${#var} # Agafem la longitud de la paraula per a la longitud del for invers
paraula_reversed=""      # declarem una variable anomenada paraula_reversed que contindrà la paraula escrita al revés


for ((i = longitud_paraula; i >= 0; i--)) # recorrem la paraula pasada per paràmetre a l'inversa

do
    
    paraula_reversed+=${var:$i:1} # anem afegint cada lletra que recorrem(per així tenir la paraula en ordre invers)

done

if [ "$var" = "$paraula_reversed" ]; then # si la paraula pasada per paràmetre equival a la paraula en inversa és un palíndrom, sinó no
    echo "És un palíndrom"
else
    echo "No és un palíndrom"
fi

exit 0