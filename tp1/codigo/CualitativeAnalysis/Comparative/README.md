Instrucciones para ejecución de los experimentos Comparativos
=============================================================

1) Compilación -> "g++ -o main main.cpp -std=c++11"
2) Ejecución -> "./main 'e'", e: número de experimento cuyos valores válidos son {1, 2, 3}
	2.1) Para el caso del experimento 1, hay un 'prompt' para pedir el input que consiste de:
			- s: año de temporada cuyos valores válidos son {2014, 2015, 2016}
			- k: número de encuentros que quiero que tengan todos los equipos aproximadamente, tener en cuenta que son temporadas de la NBA

Formato de entrada
==================

El formato de entrada es el standard del trabajo práctico tal y como lo planteo la cátedra

Formato de salida
=================

El formato de salida cuenta con títulos que indican el algoritmo usado para generar el ranking seguido del ranking formulado por el mismo.
Cada línea corresponde al rating otorgado a cada equipo, en otras palabras la línea i corresponde al r_i, dónde i NO está indexado.
