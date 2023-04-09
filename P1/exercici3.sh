#!/bin/bash

if [ $# -ne 2 ]
then 
    echo "Nombre incorrecte de parametres: $0 <Directori> <String>"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "El primer paràmetre ha de ser un directori."
    exit 1
fi

directori=$1
cadena=$2
var=${cadena,,} # Convertim la paraula a minúscules, així ens assegurem que no hi hagi problemes


longitud_paraula=${#var} # Agafem la longitud de la paraula

for item in $(ls $directori); # recorrem els elements del directori
do
ruta=$directori/$item # per a obtenir la ruta completa i no mirar només pel nom
coincidencies=0       # variable que farà de comptador de les paraules que comencen per la String passada per paràmetre
if [ -f $ruta ];
then
    fitxer=$(cat $ruta) # emmagatzemem el contingut del fitxer en la variable fitxer
    
    for word in $fitxer # recorrem cada paraula emmagatzemada del fitxer
    do
        longitudParaulaFitxer=${#word} # comprovem la longitud de cada paraula del fitxer

        if [ $longitudParaulaFitxer -ge $longitud_paraula ]; then # comprovem que la longitud de la paraula sigui >= longitud String passada per paràmetre

            half_word="${word:0:$longitud_paraula}" # guardem en una variable els n primers elements de la paraula on n = longitud de la String passada per paràmetre
            
            if [ $cadena = "$half_word" ]; then  # mirem si coïncideix la String passada per paràmetre amb les n primeres lletres
                echo "$item : $word "
                ((coincidencies=coincidencies+1))
            
            fi
        fi    
    done
    echo "Total $item: $coincidencies"
fi
done

exit 0


