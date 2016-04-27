#ifndef Print_h
#define Print_h

#include "Types.h"

template<typename T>
void printVector(const vector<T>& vec){
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void printMatrix(const Matrix& mat){
    for (int i = 0; i < mat.size(); ++i)
        printVector(mat[i]);
}

#endif
