#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"
#include "Print.h"
#include "Equalty.h"
#include "MatrixAlgorithms.h"

void kNN(vector<double> &test, Matrix &train, vector<int> &ks, vector<int> &labelRes, DigitImages &digitImagesTrain){
    // distance, index
    vector<pair<double, int>> distances(train.size());
    vector<int> labels(LABELS_QTY, 0);
    vector<double> diff(test.size());
    labelRes = vector<int>(ks.size());
    for (int i = 0; i < train.size(); ++i){
        substractVecVec(test, train[i], diff);
        distances[i].first = dotProduct(diff, diff);
        distances[i].second = i;
    }
    sort(distances.begin(), distances.end());
    for (int iter = 0; iter < ks.size(); ++iter){
        for (int i = 0; i < ks[iter]; ++i)
            labels[digitImagesTrain.images[distances[i].second].label]++;
        int max = labels[0], label = 0;
        // TODO: extract to function
        for (int i = 1; i < labels.size(); ++i){
            if (labels[i] > max){
                max = labels[i];
                label = i;
            }
        }
        labelRes[iter] = label;
        // in case of draw, lower digit wins
    }
}

double powerMethod(Matrix &mat, vector<double> &vec, int niter){
    vector<double> aux(vec.size());
    for (int iter = 0; iter < niter; ++iter){
        productMatrixVector(mat, vec, aux);
        double norma = sqrt(dotProduct(aux, aux));
        for (int i = 0; i < vec.size(); ++i){
            vec[i] = aux[i] / norma;
        }
    }
    productMatrixVector(mat, vec, aux);
    return dotProduct(vec, aux);
}

void PCA(Matrix &covariances, Matrix &eigenVectors, vector<double> &eigenValues, int alpha, int niter){
    Matrix deflater(covariances.size(), vector<double>(covariances.size()));
    for (int iter = 0; iter < alpha; ++iter){
        randomVectorInitialize(eigenVectors[iter]);
        eigenValues[iter] = powerMethod(covariances, eigenVectors[iter], niter); // CRITERIO DE PARADA
        productColRow(eigenVectors[iter], eigenVectors[iter], deflater, eigenValues[iter]);
        substractMatMat(covariances, deflater, covariances);
    }
}

void PLSDA(DigitImages &images, Matrix &eigenVectors, vector<double> &eigenValues, int gamma, int niter){
    Matrix XtY(DEFAULT_IMAGE_SIZE, vector<double>(LABELS_QTY)); // XtY = (YtX)t
    Matrix Mi(DEFAULT_IMAGE_SIZE, vector<double>(DEFAULT_IMAGE_SIZE));
    Matrix TiTitX(images.centralizedPLSDA.size(), vector<double>(DEFAULT_IMAGE_SIZE));
    Matrix TiTitY(images.labelY.size(), vector<double>(LABELS_QTY));
    vector<double> Ti(images.centralizedPLSDA.size());
    vector<double> TitX(DEFAULT_IMAGE_SIZE);
    vector<double> TitY(LABELS_QTY);
    for (int iter = 0; iter < gamma; ++iter){
        productMatMat(images.centralizedPLSDA, images.labelY, XtY, true);
        productMatMatSimetric(XtY, Mi); // XtY * (XtY)t
        randomVectorInitialize(eigenVectors[iter]);
        eigenValues[iter] = powerMethod(Mi, eigenVectors[iter], niter); // CRITERIO DE PARADA
        productMatrixVector(images.centralizedPLSDA, eigenVectors[iter], Ti);
        double norma = sqrt(dotProduct(Ti, Ti));
        for (int i = 0; i < Ti.size(); ++i)
            Ti[i] /= norma;
        productVectorMatrix(Ti, images.centralizedPLSDA, TitX);
        productColRow(Ti, TitX, TiTitX);
        substractMatMat(images.centralizedPLSDA, TiTitX, images.centralizedPLSDA);
        productVectorMatrix(Ti, images.labelY, TitY);
        productColRow(Ti, TitY, TiTitY);
        substractMatMat(images.labelY, TiTitY, images.labelY);
    }
}

#endif
