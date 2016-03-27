//Compile: g++ -o main main.cpp -std=c++11

#include "Algorithms.h"
#include "Tests.h"
#include "Types.h"
#include "InputProcessor.h"

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)
//   -(a: algorithm -> 0: CMM-EG, 1: CMM-CL, 2:WP)

int main(int argc, char const *argv[]){
    if (argc != 4) {
        cout << "Parameters should be: (i: input file), (o: output file), (a: algorithm -> 0: CMM-EG, 1: CMM-CL, 2:WP)" << endl;
        return 0;
    }

    // Input parameters
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string method = argv[3];

    int n;  // Teams quantity
    int k;  // Games quantity

    input >> n >> k;

    vector<MatchesRecord> teamsMatchesRecords(n, MatchesRecord());      // Teams Matches Records
    matrix colleyMatrix(n, vector<double>(n, 0.0));                     // Colley Matrix
    vector<TeamRating> b_vector(n);                                     // b vector
    vector<TeamRating> res(n, 0.0);                                     // results vector

    populateDataWithInput(input, teamsMatchesRecords, colleyMatrix, k);

    input.close();

    create_b_vector(b_vector, teamsMatchesRecords);


    if(method == "test"){ runTests(); return 0; }

    if(method == "0"){
        gaussianElimination(colleyMatrix, b_vector, res);
    } else if(method == "1"){
        choleskyFactorization(colleyMatrix, b_vector, res);
    } else	if(method == "2"){
        winningPercentage(teamsMatchesRecords, res);
    } else {
        cout << "Method " + method + " not supported" << endl;
    }

    printRatings(res, output);
    output.close();


    return 0;
}
