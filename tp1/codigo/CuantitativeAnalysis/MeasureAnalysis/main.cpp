//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Tests.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/InputProcessor.h"

#include <iomanip>
#include <ctime>

// --- Input arguments ---
//   -(n: iterations)
//   -(o: output file)
//   -(i: input's input file)


int main(int argc, char const *argv[]){
    // Input parameters
    int iterations, filesProcessed = 0;
    sscanf(argv[1], "%d", &iterations);
    ofstream output(argv[2]);
    ifstream inputs(argv[3]);
    string testFile;

    //Execute test for each input file
    while(getline(inputs, testFile)){
        ifstream input(testFile);

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

        for (int iteration = 0; iteration < iterations; iteration++) {

            //Copy matrix models to process each iteration

            vector<MatchesRecord> teamsMatchesRecordsGE(teamsMatchesRecords);
            vector<MatchesRecord> teamsMatchesRecordsCF(teamsMatchesRecords);

            matrix colleyMatrixGE(colleyMatrix);
            matrix colleyMatrixCF(colleyMatrix);

            vector<TeamRating> b_vectorGE(b_vector);
            vector<TeamRating> b_vectorCF(b_vector);

            vector<TeamRating> resGE(res);
            vector<TeamRating> resCF(res);

            clock_t tickGE = clock();
            gaussianElimination(colleyMatrixGE, b_vectorGE, resGE);
            totalTicksGE += clock() - tickGE;

            clock_t tickCF = clock();
            choleskyFactorization(colleyMatrixCF, b_vectorCF, resCF);
            totalTicksCF += clock() - tickCF;

            cout << "file " << ++filesProcessed << ". Iteration: " << iteration + 1 << "." << endl;
        }

        clock_t avgTicksGE = totalTicksGE / iterations;
        clock_t avgTicksCF = totalTicksCF / iterations;

        //Write results in output file
        output << "teams qty: " << n << endl;
        output << "games qty: " << k << endl;
        output << "GE average ticks: " << avgTicksGE << endl;
        output << "CF average ticks: " << avgTicksCF << endl;
        output << "----------" << endl;

    }

    output.close();

    return 0;
}
