#include "Algorithms.h"

#ifndef Print_h
#define Print_h

void printVector(const vector<double>& vec){
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void printMatrix(const matrix& mat){
    for (int i = 0; i < mat.size(); ++i)
        printVector(mat[i]);
}

void printRatings(const vector<TeamRating>& vec, ostream& os){
    for (int i = 0; i < vec.size(); ++i){
        os << vec[i] << endl;
    }
}

#endif
