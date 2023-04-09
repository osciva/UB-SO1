#!/bin/bash

# Ps aux imprimeix tots els processos.
# Amb grep $1 selecciono els que tenen com a usuari el passat per paràmetre.
# I d'aquests processos seleccionats em quedo amb la cinquena i la sisena columna perquè 
# són les que contenen les variables VSZ i RSS respectivament




VSZ=$(ps aux | grep $1 | awk '{ totalVSZ += $5 } END { print "VSZ: " totalVSZ " bytes"}')
RSS=$(ps aux | grep $1 | awk '{ totalRSS += $6 } END { print "RSS: " totalRSS " bytes"}')



echo $VSZ
echo $RSS

exit 0