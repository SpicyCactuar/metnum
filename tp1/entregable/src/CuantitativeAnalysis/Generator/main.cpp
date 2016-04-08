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
//   -(3: teams interval)
//   -(4: teams final qty)

int main(int argc, char const *argv[]){
    if(argc != 5){ cout << "Parameters should be: (f: output file), (i: teams initial qty), (i: teams interval), (f: teams final qty)" << endl; return 0; }

    // Input params
    int nInitial;               // initial Teams quantity
    int interval;               // interval
    int nFinal;                 // final Teams quantity
    int k;                      // Games quantity
    int maxScore = 100;

    // Read input
    sscanf(argv[2], "%d", &nInitial);
    sscanf(argv[3], "%d", &interval);
    sscanf(argv[4], "%d", &nFinal);

    //Loop for each teams qty
    for (int n = nInitial; n <= nFinal; n += interval) {

        k = 10 * n; // There will be 10*teams games

        //Generate output path
        string ouputFile = argv[1];
        ouputFile = ouputFile + "test" + to_string(n) + ".in"; // Eg: test20.in
        ofstream output(ouputFile);

        output << n << " " << k << endl;

        for (int i = 0; i < k; i++) {
            int teamLocal = (rand() % n) + 1; // Team: number between 1 - n inclusive
            int teamAway = (rand() % n) + 1;
            if (teamAway == teamLocal) { teamAway = (++teamLocal % n) + 1; }

            int scoreLocal = (rand() % maxScore) + 1;
            int scoreAway = (rand() % maxScore) + 1;
            if (scoreLocal == scoreAway) { scoreAway = (++scoreLocal % n) + 1; }

            output << 1 << " " << teamLocal << " " << scoreLocal << " " << teamAway << " " << scoreAway << endl;
        }
        
        output.close();

    }

    return 0;
}
