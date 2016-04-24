//Compile: g++ -o main main.cpp -std=c++11

/**
+ COMPILATION
* 
* g++ -o main main.cpp -std=c++11
* 
*/

#include "Algorithms.h"
#include "Tests.h"
#include "Types.h"
#include "InputProcessor.h"

// --- Input arguments ---
// TODO: Fill with input args and description

int main(int argc, char const *argv[]){
    DigitImage image;
	ifstream input("input.txt");

	// Skip First Line
    while(input.get() != '\n');

    populateDigitImage(input, image);

    image.prettyPrint(cout);

    input.close();

    return 0;
}
