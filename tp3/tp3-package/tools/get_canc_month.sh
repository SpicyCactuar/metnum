#!/bin/bash
# Buscamos numero de vuelos cancelados por mes entre dos aeropuertos. 

# Definimos algunas variables. Ojo que a bash no le gustan los espacios cerca del "=".
year="2000"
infile="../data/2000.csv"
outfile="../data/canc_by_month-dsm-ord-2000.csv"

orig_ap="DSM" 
dest_ap="ORD"

# La secuencia es:
# 1. Primero filtramos por vuelos cancelados. Esto lo hacemos una unica vez y lo guardamos en el archivo canc_aux.csv
# 2. Del output de 1, filtramos las lineas que matchean el mes. Esto es facil de hacer con el comando grep.
# 3. Contamos la cantidad de lineas con el comando wc.
# El resultado queda en $outfile, es un vector con las cancelaciones por mes del año elegido.

awk -F, '$17 == "'"$orig_ap"'" && $18 == "'"$dest_ap"'" && $22=="1"' $infile > canc_aux.csv
for i in `seq 1 12`; do cat canc_aux.csv | grep $year,$i | wc -l; done > $outfile;

# Borramos el archivo auxiliar.
rm canc_aux.csv
