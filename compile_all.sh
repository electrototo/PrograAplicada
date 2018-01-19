#!/usr/bin/env bash

# autor: cristobal liendo
# fecha: 19/01/18
# compila los archivos apuntados por los argumentos con la terminacion ".exe"

if [ -d $1 ]; then
    for file in $(basename $1)/*.c
    do
        NAME=$(basename ${file%.*})
        gcc -o $(basename $1)/$NAME.exe $file
    done
else
    echo "FATAL: path is not a directory"
fi
