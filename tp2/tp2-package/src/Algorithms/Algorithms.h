#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"
#include "Print.h"
#include "Equalty.h"
using namespace std;

//returns the selected digit for the DigitImage passed, should have only one image
// int knn(DigitImages &train, DigitImages &test, int k){
//     for (int i = 0; i < train.size(); ++i){
//         sqrt(dotProduct(train[i], vec));
//     }
// }

//Ax = y product
void productMatrixVector(Matrix &mat, vector<double> &vecIn, vector<double> &vecOut){
    for (int i = 0; i < mat.size(); ++i){
        double sum = 0;
        for (int j = 0; j < vecIn.size(); ++j)
            sum += mat[i][j] * vecIn[j];
        vecOut[i] = sum;
    }
}

//xy^t = A product
void productColRow(vector<double> &vec, Matrix &mat, double lambda = 1){
    for (int i = 0; i < vec.size(); ++i){
        for (int j = 0; j < vec.size(); ++j)
            mat[i][j] = vec[i] * vec[j] * lambda;
    }
}

//x^ty = # product
double dotProduct(vector<double> &vec1, vector<double> &vec2){
    double sum = 0;
    for (int i = 0; i < vec1.size(); ++i)
        sum += vec1[i] * vec2[i];
    return sum;
}

void randomVectorInitialize(vector<double>& vec){
    for (int i = 0; i < vec.size(); ++i){
        srand((unsigned) time(NULL));
        vec[i] = rand() + 1;
    }
}

double powerMethod(Matrix &covariances, vector<double> &res, int niter){
    vector<double> aux(res.size());
    for (int i = 0; i < niter; ++i){
        productMatrixVector(covariances, res, aux);
        double norma = sqrt(dotProduct(aux, aux));
        for (int j = 0; j < res.size(); ++j){
            res[j] = aux[j] / norma;
        }
    }
    productMatrixVector(covariances, res, aux);
    return dotProduct(res, aux) / dotProduct(res, res);
}

void deflatePCA(Matrix &covariances, Matrix &deflater){
    for (int i = 0; i < covariances.size(); ++i)
        for (int j = 0; j < covariances.size(); ++j)
            covariances[i][j] -= deflater[i][j];
}

void PCA(Matrix &covariances, Matrix &eigenVectors, vector<double> &eigenValues, int alpha, int niter){
    Matrix deflater(covariances.size(), vector<double>(covariances.size(), 0));
    for (int i = 0; i < alpha; ++i){
        randomVectorInitialize(eigenVectors[i]);
        eigenValues[i] = powerMethod(covariances, eigenVectors[i], niter); // CRITERIO DE PARADA
        productColRow(eigenVectors[i], deflater, eigenValues[i]);
        deflatePCA(covariances, deflater);
    }
}

#endif
