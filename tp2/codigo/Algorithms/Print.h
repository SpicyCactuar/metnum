#ifndef Print_h
#define Print_h

#include "Types.h"

void printVector(const vector<double>& vec){
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void printMatrix(const matrix& mat){
    for (int i = 0; i < mat.size(); ++i)
        printVector(mat[i]);
}

#endif
