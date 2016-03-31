#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

// --- Input arguments ---
//   -(1: output directory)
//   -(2: teams initial qty)
//   -(3: results qty)

int main(int argc, char const *argv[]){
    // Input params
    int teams;               // initial Teams quantity
    int qty;               // qty
    // Read input
    sscanf(argv[2], "%d", &teams);
    sscanf(argv[3], "%d", &qty);

    //Loop for each teams qty
    string ouputFile = argv[1];
    ouputFile += to_string(qty) + "b_" + to_string(teams) + ".in"; // Eg: 50b_20.in
    ofstream output(ouputFile);
    for (int b = 0; b < qty; ++b) {
        //Generate output path

        for (int i = 0; i < teams; ++i) {
            output << ((rand() % teams) + 1) << " \n"[i == (teams - 1)];
        }
    }
    output.close();
    return 0;
}
