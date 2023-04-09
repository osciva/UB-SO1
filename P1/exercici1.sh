#! /bin/bash

if [ $# -ne 1 ]
then 
    echo "Nombre incorrecte de parametres: $0 <directori>"
    exit 1
fi

direct=$1
directoris=0
fitxers=0

for item in $(ls $direct); # recorrem els elements del directori
do
ruta="$direct/$item"       # per a obtenir la ruta completa i no mirar només pel nom

if [ -d $ruta ];           # mirem si l'element del directori és un directori(if) o si pel contrai és un fitxer(else)
then
((directoris=directoris+1))
else
((fitxers=fitxers+1))
fi
done;


echo "Fitxers: $fitxers"
echo "Directoris: $directoris"

exit 0