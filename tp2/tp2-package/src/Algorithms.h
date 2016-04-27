#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"
#include "Print.h"
#include "Equalty.h"

const int LABELS_QTY = 10;
int kNN(vector<double> &test, Matrix &train, int k, DigitImagesHelper &digitImagesTrain){
    vector<pair<double, int> > distances(train.size());
    vector<int> labels(LABELS_QTY, 0);
    for (int i = 0; i < train.size(); ++i){
        distances[i].first = dotProduct(train[i], test);
        distances[i].second = i;
    }
    sort(distances.rbegin(), distances.rend()); //hack to order in descend order
    for (int i = 0; i < k; ++i)
        labels[digitImagesTrain.images[distances[i].second].label]++;
    int max = labels[0], label = 0;
    for (int i = 1; i < labels.size(); ++i){
        if (labels[i] > max){
            max = labels[i];
            label = i;
        }
    }
    return label;
}

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

void PCA(DigitImagesHelper &imagesHelper, Matrix &eigenVectors, vector<double> &eigenValues, int alpha, int niter, TC &tc){
    Matrix deflater(imagesHelper.covariances.size(), vector<double>(imagesHelper.covariances.size(), 0));
    for (int i = 0; i < alpha; ++i){
        randomVectorInitialize(eigenVectors[i]);
        eigenValues[i] = powerMethod(imagesHelper.covariances, eigenVectors[i], niter); // CRITERIO DE PARADA
        productColRow(eigenVectors[i], deflater, eigenValues[i]);
        deflatePCA(imagesHelper.covariances, deflater);
    }
    tc.init(eigenVectors, imagesHelper.images);
}

void testToTC(DigitImagesHelper &imagesHelperTrain, DigitImagesHelper &imagesHelperTest, Matrix &eigenVectors, TC &tc){
    // for (int i = 0; i < imagesHelperTest.images.size(); ++i)
    //     for (int j = 0; j < imagesHelperTest.images[i].pixels.size(); ++j)
    //         imagesHelperTest.images[i].pixels[j] = (imagesHelperTest.images[i].pixels[j] - imagesHelperTrain.medians[j]) / sqrt(imagesHelperTrain.samples - 1);
    tc.init(eigenVectors, imagesHelperTest.images);
}

#endif
