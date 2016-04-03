//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/Imports.h"
#include "../../Algorithms/InputProcessor.h"
#include "../../Algorithms/Print.h"
#include "../../Algorithms/Algorithms.h"
#include "./Experiments.h"

// --- Input arguments ---
// e: Experiment number (currently supported: 1 to -)

int main(int argc, char const *argv[]){
   if (argc < 2) {
        cout << "First parameter should be Experiment Number" << endl << endl;
        cout << "Check README or Experiments.h file for information on input/output of each experiment" << endl;
        return 1;
    }

    int experimentNumber = atoi(argv[1]);

    switch(experimentNumber) {
        case 1:
            return runExperiment_1();
        case 2:
            return runExperiment_2();
        default:
            cout << "Invalid experiment number" << endl;
            cout << "Currently supported are: 1 to 2" << endl << endl;
            return 1;
    }
}
