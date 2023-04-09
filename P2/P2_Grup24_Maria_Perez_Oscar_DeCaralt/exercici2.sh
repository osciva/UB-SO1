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

fitxers=$(find $1 -type f -size +$2c | sort | head) #Para buscar todos los 
#ficheros con los bytes pasados por parámetro a partir del directorio pasado por parámetro, 
#ordenarlos y head que se queda por defecto con las 10 primeras lineas (==head -10 ) #| sort | head 

echo "$(wc -c $fitxers | awk '{print $2 " : " $1}')"; 

exit 0