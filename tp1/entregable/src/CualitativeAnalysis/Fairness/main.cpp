//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Tests.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/InputProcessor.h"

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)

int main(int argc, char const *argv[]){
    if (argc != 3) {
        cout << "Parameters should be: (i: input file), (o: output file)" << endl;
        return 0;
    }

    // Input parameters
    ifstream input(argv[1]);
    ofstream output(argv[2]);

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
    choleskyFactorization(colleyMatrix, b_vector, res);

    printRatings(res, output);
    output.close();


    return 0;
}
