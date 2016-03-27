//Compile: g++ -o main main.cpp -std=c++11

#include "../Algorithms/Algorithms.h"
#include "../Algorithms/Tests.h"
#include "../Algorithms/Types.h"



int main(int argc, char const *argv[]){
    // si no me pasan los 4 parametros (argc es implicito) esta todo mal
    if(argc != 4){
        cout << "Falta algun parametro, son: input file, output file, algoritmo (0: CMM-EG, 1: CMM-CL, 2:WP)" << endl;
        return 0;
    }

    // leo el archivo de entrada
    ifstream input(argv[1]);

    int n; // Teams quantity
    int k;  // Games quantity
    int local, local_score, away, away_score; // Teams and colleyMatrix
    string temp; // Date identifier. Currently not used.

    input >> n >> k;

    vector<MatchesRecord> teamsMatchesRecords(n, MatchesRecord());
    matrix colleyMatrix(n, vector<double>(n, 0.0));

    for(int i = 0; i < k; i++){
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
    input.close();

    // If i == j
    for (int i = 0; i < n; ++i){
        colleyMatrix[i][i] += teamsMatchesRecords[i].totalPlayed() + 2;
    }

    // armo el b
    vector<TeamRating>b_vector(n);
    for (int i = 0; i < n; ++i) {
        b_vector[i] = 1 + (teamsMatchesRecords[i].won - teamsMatchesRecords[i].lost) / 2;
    }

    string method = argv[3];
    if(method == "0"){
        vector<TeamRating> res(n, 0.0);
        gaussianElimination(colleyMatrix, b_vector, res);
        ofstream output(argv[2]);
        printRatings(res, output);
        output.close();
    } else if(method == "1"){
        vector<TeamRating> res(n, 0.0);
        choleskyFactorization(colleyMatrix, b_vector, res);
        ofstream output(argv[2]);
        printRatings(res, output);
        output.close();
    } else	if(method == "2"){
        vector<TeamRating> res(n, 0.0);
        ofstream output(argv[2]);
        winningPercentage(teamsMatchesRecords, res);
        printRatings(res, output);
    } else if(method == "test"){
        runTests();
    } else {
        cout << "Método " + method + "no soportado actualmente" << endl;
    }

    return 0;
}
