#!/bin/bash
# Filtramos todas las posibles combinaciones origen-destino. 

# Definimos algunas variables. Ojo que a bash no le gustan los espacios cerca del "=".
year="2008"
infile="../data/2008.csv"
outfile="../data/od_comb_2008.csv"

cut -f17,18 -d, $infile | sort | uniq > $outfile
