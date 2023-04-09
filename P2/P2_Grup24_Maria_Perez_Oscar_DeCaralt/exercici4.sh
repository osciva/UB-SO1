#!/bin/bash


# Agafem els fitxers que es troben dins del directori i comptem quants hi ha.

fitxers=$(find $1 -type f | wc -l)
echo $fitxers" files"

# Agafem els bytes.

sum=0

find $1 -type f -exec ls -l {} \; | awk '{ sum+=$5 } END { print sum " bytes" }'

exit 0
