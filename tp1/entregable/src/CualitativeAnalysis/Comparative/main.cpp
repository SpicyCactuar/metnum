//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/Imports.h"
#include "../../Algorithms/InputProcessor.h"
#include "../../Algorithms/Print.h"
#include "../../Algorithms/Algorithms.h"
#include "./Experiments.h"

// --- Input arguments ---
// e: Experiment number (currently supported: 1 to 3)

int main(int argc, char const *argv[]){
   if (argc < 2) {
        cout << "First parameter should be Experiment Number" << endl << endl;
        return 1;
    }

    int experimentNumber = atoi(argv[1]);

    switch(experimentNumber) {
        case 1:
            return runExperiment_1();
        case 2:
            return runExperiment_2();
        case 3:
            return runExperiment_3();
        default:
            cout << "Invalid experiment number" << endl;
            cout << "Currently supported are: 1 to 3" << endl << endl;
            return 1;
    }
}
