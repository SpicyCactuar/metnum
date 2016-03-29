//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Tests.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/InputProcessor.h"

#include <iomanip>
#include <ctime>
#include <sstream>

// --- Input arguments ---
//   -(o: output file)
//   -(i: input file)
//   -(i: input b_data)

int main(int argc, char const *argv[]){
    // Input parameters
    int bsProcessed = 0;
    ofstream output(argv[1]);
    ifstream input(argv[2]);
    ifstream b_data(argv[3]);
    string bInputs;

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

    clock_t totalTicksGE = 0.0;
    clock_t totalTicksCF = 0.0;

    vector<MatchesRecord> teamsMatchesRecordsCF(teamsMatchesRecords);
    matrix colleyMatrixCF(colleyMatrix);
    vector<TeamRating> b_vectorCF(b_vector);
    vector<TeamRating> resCF(res);
    makeLowerTriangularCholesky(colleyMatrixCF);

    //Execute test for each b without the default first
    while(getline(b_data, bInputs)){
        //Copy matrix models to process each iteration
        vector<MatchesRecord> teamsMatchesRecordsGE(teamsMatchesRecords);
        matrix colleyMatrixGE(colleyMatrix);
        vector<TeamRating> b_vectorGE(b_vector);
        vector<TeamRating> resGE(res);

        //Load b
        stringstream ss(bInputs);
        string b_in;
        for (int i = 0; i < n; ++i){
            getline(ss, b_in, ' ');
            b_vectorGE[i] = stoi(b_in);
            b_vectorCF[i] = stoi(b_in);
        }

        clock_t tickGE = clock();
        gaussianElimination(colleyMatrixGE, b_vectorGE, resGE);
        totalTicksGE += clock() - tickGE;

        clock_t tickCF = clock();
        solveLLtMatrix(colleyMatrixCF, b_vectorCF, resCF);
        totalTicksCF += clock() - tickCF;

        cout << "file " << ++bsProcessed << endl;
    }
    clock_t avgTicksGE = totalTicksGE / bsProcessed;
    clock_t avgTicksCF = totalTicksCF / bsProcessed;
    //Write results in output file
    output << "teams qty: " << n << endl;
    output << "games qty: " << k << endl;
    output << "GE average ticks: " << avgTicksGE << endl;
    output << "CF average ticks: " << avgTicksCF << endl;
    output << "----------" << endl;
    output.close();
    return 0;
}
