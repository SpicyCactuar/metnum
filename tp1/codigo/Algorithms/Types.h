#ifndef Types_h
#define Types_h

using namespace std;

using matrix = vector<vector<double> >;
using b_vector = vector<double>;
using TeamRating = double;

struct MatchesRecord {
    double won;
    double lost;

    MatchesRecord(){ won = lost = 0.0; }

    void addWon() { won += 1.0; }

    void addLost() { lost += 1.0; }

    double totalPlayed() { return won + lost; }
};

#endif
