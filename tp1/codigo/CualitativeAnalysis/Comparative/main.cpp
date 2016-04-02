//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Types.h"
#include "../../Algorithms/Imports.h"
#include "../../Algorithms/InputProcessor.h"
#include "../../Algorithms/Print.h"
#include "../../Algorithms/Algorithms.h"

// --- Input arguments ---
// y: season year (currently supported 2014 to 2016)
// g: games played (take in account that a basketball REGULAR season lasts 82 games)

int main(int argc, char const *argv[]){
   if (argc != 3) {
        cout << "Parameters should be:" << endl;
        cout << "--------" << " y -> season year (currently supported 2014 to 2016)" << "--------" << endl;
        cout << "--------" << " g -> games played (take in account that a basketball REGULAR season lasts 82 games)" << "--------" << endl;
        
        return 0;
    }

    // Need to parse it as "char const*" doesn't allow operator+
    string year = string(argv[1]);
    int games = atoi(argv[2]);
    
    // Input parameters
    ifstream input("./io/nba_" + year + "_scores.dat");
    ofstream output("./io/nba_" + year + "_scores.out");

    int n;  // Teams quantity
    int k;  // Games quantity

    input >> n >> k;

    vector<MatchesRecord> teamsMatchesRecords(n, MatchesRecord());      // Teams Matches Records
    matrix colleyMatrix(n, vector<double>(n, 0.0));                     // Colley Matrix
    vector<TeamRating> b_vector(n);                                     // b vector
    vector<TeamRating> resCMM(n, 0.0);                                  // CMM ratings vector
    vector<TeamRating> resWP(n, 0.0);                                   // WP ratings vector
    
    create_b_vector(b_vector, teamsMatchesRecords);

    parseScheduleUntilGamesPlayed(input, teamsMatchesRecords, colleyMatrix, k, games);
        
    input.close();
    
    cout << "CMM RESULTS" << endl;
    cout << "===========" << endl;
    choleskyFactorization(colleyMatrix, b_vector, resCMM);
    printRatings(resCMM, cout);
    cout << endl;
    
    cout << "WP RESULTS" << endl;
    cout << "==========" << endl;
    winningPercentage(teamsMatchesRecords, resWP);
    printRatings(resWP, cout);
    cout << endl;

    output.close();

    return 0;
}
