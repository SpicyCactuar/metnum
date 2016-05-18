Este main corre tanto PCA como PLS-DA con los parametros correspondientes aplicando K-Fold Cross Validation.
El formato es igual al descripto en el TP:
./tp tests/test#.in tests/test#.out method
donde method:
0: aplica knn sobre los datos sin preprocesar.
1: aplica knn sobre los datos prepocesados con PCA.
2: aplica knn sobre los datos prepocesados con PLS-DA.
Cada uno computa las estadisticas correspondientes para cada caso e imprimen los alpha y gamma autovalores pedidos
3: Computa la clasificacion de la base de Test entrenando con toda la base de Train como tal.

El archivo de entrada para method 3 debe ser:
fileDir alpha gamma kalpha kgamma
