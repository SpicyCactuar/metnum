#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

// --- Input arguments ---
//   -(f: output directory)
//   -(n: teams qty)
//   -(k: games qty)

int main(int argc, char const *argv[]){
    if(argc != 4){ cout << "Parameters should be: (f: output file), (n: teams qty), (k: games qty)" << endl; return 0; }

    // Input params
    int n;                      // Teams quantity
    int k;                      // Games quantity
    int maxScore = 100;

    // Read input
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%d", &k);

    //Generate output path
    string ouputFile = argv[1];
    ouputFile = ouputFile + "test" + to_string(n) + "_" + to_string(k) + ".in"; // Eg: test20_100.in
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

    return 0;
}
