#ifndef Experiments_h
#define Experiments_h

//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/Imports.h"
#include "../../Algorithms/InputProcessor.h"
#include "../../Algorithms/Print.h"
#include "../../Algorithms/Algorithms.h"

// ======== FORWARD DECLARATIONS ========
void runCholsekyAndOutput(ofstream& output, matrix& colleyMatrix, vector<TeamRating>& b, vector<TeamRating>& resCMM);
void runWPAndOutput(ofstream& output, vector<MatchesRecord>& teamsMatchesRecords, vector<TeamRating>& resWP);

// ======== EXPERIMENTS ========

// -------- EXPERIMENT 1 --------

// --- Input arguments ---
// y: season year (currently supported 2014 to 2016)
// g: games played (take in account that a basketball REGULAR season lasts 82 games)


// --- Output ---
// Output is placed in './io/nba_ratings_"y"_"g".out'

int runExperiment_1(){
    // Handle input
    string year;
    cout << "Please enter season year (currently supported: 2014 to 2016): ";
    cin >> year;

    string gamesStr;
    cout << "Please enter games played number (regular NBA seasons lasts 82 games): ";
    cin >> gamesStr;

    string inputFilePath = "./io/nba_" + year + "_scores.in";
    cout << "Input file location: " + inputFilePath << endl;

    string outputFilePath = "./io/nba_ratings_" + year + "_" + gamesStr + ".out";
    
    // Input parameters
    ifstream input(inputFilePath);
    ofstream output(outputFilePath);

    int n;  // Teams quantity
    int k;  // Games quantity    
    input >> n >> k;
    
    vector<MatchesRecord> teamsMatchesRecords(n, MatchesRecord());
    matrix colleyMatrix(n, vector<double>(n, 0.0));
    vector<TeamRating> b_vector(n);
    vector<TeamRating> resCMM(n, 0.0);
    vector<TeamRating> resWP(n, 0.0);

    int games = stoi(gamesStr);
    parseScheduleUntilGamesPlayed(input, teamsMatchesRecords, colleyMatrix, k, games);
    create_b_vector(b_vector, teamsMatchesRecords);
    
    input.close();
    
    output << "CMM RESULTS" << endl;
    output << "===========" << endl << endl;
    runCholsekyAndOutput(output, colleyMatrix, b_vector, resCMM);
    
    output << "WP RESULTS" << endl;
    output << "==========" << endl << endl;
    runWPAndOutput(output, teamsMatchesRecords, resWP);

    cout << "Output file location: " + outputFilePath << endl;

    output.close();

    return 0;
}

// -------- EXPERIMENT 2 --------
// --- Output ---
// Output is placed in './io/experiment_2.out'

int runExperiment_2() {

    string inputFilePath_distributed = "./io/experiment_2_1.in";
    string inputFilePath_non_distributed = "./io/experiment_2_2.in";
    string outputFilePath = "./io/experiment_2.out";

    cout << "Input files locations: " + inputFilePath_non_distributed + " | " + inputFilePath_distributed << endl;
    
    // Input parameters
    ifstream input_non_distributed(inputFilePath_non_distributed);
    ifstream input_distributed(inputFilePath_distributed);
    ofstream output(outputFilePath);

    int n;  // Teams quantity
    int k;  // Games quantity
    input_non_distributed >> n >> k;
    
    vector<MatchesRecord> teamsMatchesRecords_non_distributed(n, MatchesRecord());
    vector<MatchesRecord> teamsMatchesRecords_distributed(n, MatchesRecord());
    matrix colleyMatrix_non_distributed(n, vector<double>(n, 0.0));
    matrix colleyMatrix_distributed(n, vector<double>(n, 0.0));
    vector<TeamRating> b_vector_non_distributed(n);
    vector<TeamRating> b_vector_distributed(n);
    vector<TeamRating> resCMM_non_distributed(n, 0.0);
    vector<TeamRating> resWP_non_distributed(n, 0.0);
    vector<TeamRating> resCMM_distributed(n, 0.0);
    vector<TeamRating> resWP_distributed(n, 0.0);

    populateDataWithInput(input_non_distributed, teamsMatchesRecords_non_distributed, colleyMatrix_non_distributed, k);
    create_b_vector(b_vector_non_distributed, teamsMatchesRecords_non_distributed);
    
    input_non_distributed.close();
    
    output << "CMM RESULTS - NON-DISTRIBUTED" << endl;
    output << "===========" << endl << endl;
    runCholsekyAndOutput(output, colleyMatrix_non_distributed, b_vector_non_distributed, resCMM_non_distributed);

    output << "WP RESULTS - NON-DISTRIBUTED" << endl;
    output << "===========" << endl << endl;
    runWPAndOutput(output, teamsMatchesRecords_non_distributed, resWP_non_distributed);

    // Cheap way to "discard" the first line, 'n' and 'k' are the same for both files
    input_distributed >> n >> k;

    populateDataWithInput(input_distributed, teamsMatchesRecords_distributed, colleyMatrix_distributed, k);
    create_b_vector(b_vector_distributed, teamsMatchesRecords_distributed);

    input_distributed.close();

    output << "CMM RESULTS - DISTRIBUTED" << endl;
    output << "===========" << endl << endl;
    runCholsekyAndOutput(output, colleyMatrix_distributed, b_vector_distributed, resCMM_distributed);

    output << "WP RESULTS - DISTRIBUTED" << endl;
    output << "===========" << endl << endl;
    runWPAndOutput(output, teamsMatchesRecords_distributed, resWP_distributed);
    
    cout << "Output file location: " + outputFilePath << endl;

    output.close();

    return 0;
}

// ======== AUXILIARY FUNCTIONS ========

void runCholsekyAndOutput(ofstream& output, matrix& colleyMatrix, vector<TeamRating>& b, vector<TeamRating>& resCMM) {
    choleskyFactorization(colleyMatrix, b, resCMM);
    printRatings(resCMM, output);
    output << endl;
}

void runWPAndOutput(ofstream& output, vector<MatchesRecord>& teamsMatchesRecords, vector<TeamRating>& resWP) {
    winningPercentage(teamsMatchesRecords, resWP);
    printRatings(resWP, output);
    output << endl;
}

#endif