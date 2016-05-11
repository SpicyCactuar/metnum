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

template<typename T>
void printImage(const vector<T>& vec, ofstream &output){
    for (int i = 0; i < DEFAULT_IMAGE_SIDE_SIZE; ++i){
        for (int j = 0; j < DEFAULT_IMAGE_SIDE_SIZE; ++j){
            output << (int)vec[i*DEFAULT_IMAGE_SIDE_SIZE+j];
            if (j != DEFAULT_IMAGE_SIDE_SIZE - 1)
                output << ",";
        }
        output << endl;
    }
}

#endif
