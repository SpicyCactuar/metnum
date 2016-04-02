//Compile: g++ -o main main.cpp -std=c++11

#include "../../Algorithms/Algorithms.h"
#include "../../Algorithms/Tests.h"
#include "../../Algorithms/Types.h"
#include <algorithm>

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)
//   -(t: team to climb)

void populateDataWithInput(istream& input, vector<MatchesRecord>& teamsMatchesRecords, matrix& colleyMatrix, int gamesQty) {

    int n = int(teamsMatchesRecords.size());
    int local, local_score, away, away_score; // Teams and colleyMatrix
    string temp; // Date identifier. Currently not used.

    for(int i = 0; i < gamesQty; i++){
        input >> temp >> local >> local_score >> away >> away_score;
        local -= 1;
        away -= 1;
        if(local_score > away_score){
            teamsMatchesRecords[local].addWon();
            teamsMatchesRecords[away].addLost();
        } else {
            teamsMatchesRecords[local].addLost();
            teamsMatchesRecords[away].addWon();
        }
        colleyMatrix[local][away] -= 1; // If i != j
        colleyMatrix[away][local] -= 1;
    }

    // If i == j
    for (int i = 0; i < n; ++i){
        colleyMatrix[i][i] += teamsMatchesRecords[i].totalPlayed() + 2;
    }
}

void create_b_vector(vector<TeamRating>& b_vector, vector<MatchesRecord>& teamsMatchesRecords) {
    for (int i = 0; i < b_vector.size(); ++i) {
        b_vector[i] = 1 + (teamsMatchesRecords[i].won - teamsMatchesRecords[i].lost) / 2;
    }
}

int findMaxIndex(vector<double>& vec) {
    int index = 0;
    double max = vec[0];
    for (int i = 1; i < vec.size(); ++i){
        if(vec[i] > max){
            max = vec[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, char const *argv[]){
    if (argc != 4) {
        cout << "Parameters should be: (i: input file), (o: output file), (t: team to climb)" << endl;
        return 0;
    }

    // Input parameters
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int n;  // Teams quantity
    int k;  // Games quantity
    int teamToClimb = atoi(argv[3]) - 1;
    input >> n >> k;

    vector<MatchesRecord> teamsMatchesRecords(n, MatchesRecord());      // Teams Matches Records
    matrix colleyMatrix(n, vector<double>(n, 0.0));                     // Colley Matrix
    vector<TeamRating> b_vector(n);                                     // b vector
    vector<TeamRating> res(n, 0.0);                                     // results vector

    populateDataWithInput(input, teamsMatchesRecords, colleyMatrix, k);

    input.close();

    create_b_vector(b_vector, teamsMatchesRecords);
    choleskyFactorization(colleyMatrix, b_vector, res);
    int posMax, i = 0;
    //making the last team id become the first
    while((posMax = findMaxIndex(res)) != teamToClimb){
        teamsMatchesRecords[posMax].subsWon();
        teamsMatchesRecords[posMax].addLost();
        teamsMatchesRecords[teamToClimb].addWon();
        teamsMatchesRecords[teamToClimb].subsLost();
        create_b_vector(b_vector, teamsMatchesRecords);
        solveLLtMatrix(colleyMatrix, b_vector, res);
        i++;
    }
    output << "Minimun games to win " << i << endl;
    printRatings(res, output);
    output.close();
    return 0;
}
