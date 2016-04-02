#ifndef InputProcessor_h
#define InputProcessor_h

#include "Algorithms.h"

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

bool gamesPlayedThresholdExceeded(vector<MatchesRecord>& teamsMatchesRecords, int games) {
    for (MatchesRecord& record : teamsMatchesRecords) {
        if(((int) record.totalPlayed()) < games) {
            return false;
        }
    }
    
    return true;
}

/// Parses the schedule until every team played at least 'gamesQty' games
/// 'k', which according to problem domain is total games plaged, is passed to have a stopping criteria
void parseScheduleUntilGamesPlayed(istream& input, vector<MatchesRecord>& teamsMatchesRecords, matrix& colleyMatrix, int k, int gamesQty) {
    int n = int(teamsMatchesRecords.size());
    int local, local_score, away, away_score; // Teams and colleyMatrix
    string temp; // Date identifier. Currently not used.

    for(int i = 0; i < k && !gamesPlayedThresholdExceeded(teamsMatchesRecords, gamesQty); i++){
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

#endif
