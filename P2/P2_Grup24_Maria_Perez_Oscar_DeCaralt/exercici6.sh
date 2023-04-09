#!/bin/bash

niub=$1
tipo=$2
grup=$3

#comprovem si el niub existeix

if [[ $(grep -c $niub alumnes.csv) == 0 ]]
then
	echo "No s'ha trobat el niub"
	exit 1
fi

#si existeix agafem la fila del niub (niub, practiques, problemes)

filaActual=$(awk -F ";" '{print $1 ";" $2 ";" $3}' alumnes.csv | grep $niub)
echo "fila actual $filaActual"

#filaActual = niub14965042;B00;CF0

ProbOrig=${filaActual:17:3}
PracOrig=${filaActual:13:3}

#echo $PracOrig
#echo $ProbOrig


if [ $tipo = "problemes" ] 
then
    echo "fila nova $niub;$PracOrig;$grup"
    sed 's/$filaActual/$niub;$PracOrig;$grup/g' alumnes.csv
    echo "Grup de problemes canviat correctament" 
          
fi

if [ $tipo = "practiques" ]
then
    echo "fila nova $niub;$grup;$ProbOrig"
    sed 's/$filaActual/$niub;$grup;$ProbOrig/g' alumnes.csv
    echo "Grup de practiques canviat correctament"                
fi

exit 0