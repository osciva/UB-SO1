#! /bin/bash

if [ $# -ne 2 ]
then 
    echo "Nombre incorrecte de parametres: $0 <directori><extensió>"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "El paràmetre ha de ser un directori..."
    exit 1
fi


directori=$1



fitxers=$(find $directori -name "*.$2" -type f | sort | head ) # Para buscar todos los ficheros con la extensión pasada por 
#parámetro a partir del directorio pasado por parámetro, ordenarlos y head que se queda por defecto con las 10 primeras lineas (==head -10 ) 
echo "$fitxers"

exit 0