#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"
#include "Print.h"
#include "Equalty.h"

const int LABELS_QTY = 10;

void substractVecVec(vector<double> &vec1, vector<double> &vec2, vector<double> &res){
    for (int i = 0; i < res.size(); ++i)
        res[i] = vec1[i] - vec2[i];
}

int kNN(vector<double> &test, Matrix &train, int k, DigitImages &digitImagesTrain){
    // distance, index
    vector<pair<double, int> > distances(train.size());
    vector<int> labels(LABELS_QTY, 0);
    vector<double> diff(test.size());
    for (int i = 0; i < train.size(); ++i){
        substractVecVec(test, train[i], diff);
        distances[i].first = dotProduct(diff, diff);
        distances[i].second = i;
    }
    sort(distances.begin(), distances.end());
    for (int i = 0; i < k; ++i)
        labels[digitImagesTrain.images[distances[i].second].label]++;
    int max = labels[0], label = 0;
    // TODO: extract to function
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
        vec[i] = rand() + 1; // ver que valor tiene que ir aca, tengo entendido que un cero rompe
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

void PCA(DigitImages &images, Matrix &eigenVectors, vector<double> &eigenValues, int alpha, int niter, TC &tc){
    Matrix deflater(images.covariances.size(), vector<double>(images.covariances.size(), 0));
    for (int i = 0; i < alpha; ++i){
        randomVectorInitialize(eigenVectors[i]);
        eigenValues[i] = powerMethod(images.covariances, eigenVectors[i], niter); // CRITERIO DE PARADA
        productColRow(eigenVectors[i], deflater, eigenValues[i]);
        deflatePCA(images.covariances, deflater);
    }
    tc.init(eigenVectors, images.correlation);
}

void testToTC(DigitImages &imagesTrain, DigitImages &imagesTest, Matrix &eigenVectors, TC &tc){
    imagesTest.correlation = Matrix(imagesTest.images.size(), vector<double>(imagesTest.imgSizeSqr));
    for (int i = 0; i < imagesTest.images.size(); ++i)
        for (int j = 0; j < imagesTest.images[i].pixels.size(); ++j)
            imagesTest.correlation[i][j] = (imagesTest.images[i].pixels[j] - imagesTrain.medians[j]) / sqrt(imagesTrain.images.size() - 1);
    tc.init(eigenVectors, imagesTest.correlation);
}

#endif
