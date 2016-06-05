#!/bin/bash
# Filtrar columnas fecha, aerolinea, nro. de vuelo 
infile="../data/2008.csv"
outfile="../data/date-carrier-filter.csv"

# -f indica que columnas, "-d," significa "delimitador es una ','".
cut -f1,2,3,9,10 -d, $infile > $outfile
