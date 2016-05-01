#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"
#include "Print.h"
#include "Equalty.h"

//x - y = z
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
    // in case of draw, lower digit wins
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

//xA = y product
//REQUIERE *** NON EMPTY MATRIX ***
void productVectorMatrix(vector<double> &vecIn, Matrix &mat, vector<double> &vecOut){
    for (int i = 0; i < mat[0].size(); ++i){
        double sum = 0;
        for (int j = 0; j < mat.size(); ++j)
            sum += mat[j][i] * vecIn[j];
        vecOut[i] = sum;
    }
}

//xy^t = A product
void productColRow(vector<double> &vec1, vector<double> &vec2, Matrix &mat, double lambda = 1){
    for (int i = 0; i < vec1.size(); ++i){
        for (int j = 0; j < vec2.size(); ++j)
            mat[i][j] = vec1[i] * vec2[j] * lambda;
    }
}

//AB = C product
//REQUIERE *** NON EMPTY MATRIX ***
void productMatMat(Matrix &mat1, Matrix &mat2, Matrix &matOut, bool mat1Traspose = false, bool mat2Traspose = false, double lambda = 1){
    //AtBt = C
    if(mat1Traspose && mat2Traspose){/* Not needed for now */}
    //AtB = C
    else if(mat1Traspose){
        for (int i = 0; i < mat1[0].size(); ++i){
            for (int j = 0; j < mat2[0].size(); ++j){
                double sum = 0;
                for (int k = 0; k < mat1.size(); ++k){
                    sum += mat1[k][i] * mat2[k][j];
                }
                matOut[i][j] = sum * lambda;
            }
        }
    }
    //ABt = C
    else if(mat2Traspose){/* Not needed for now */}
    //AB = C
    else{
        for (int i = 0; i < mat1.size(); ++i){
            for (int j = 0; j < mat2[0].size(); ++j){
                double sum = 0;
                for (int k = 0; k < mat2.size(); ++k){
                    sum += mat1[i][k] * mat2[k][j];
                }
                matOut[i][j] = sum * lambda;
            }
        }
    }
}

//XXt = Y
void productMatMatSimetric(Matrix &matIn, Matrix &matOut, double lambda = 1){
    for (int i = 0; i < matIn.size(); ++i){
        for (int j = i; j < matIn.size(); ++j){
            double sum = 0;
            for (int k = 0; k < matIn[i].size(); ++k){
                sum += matIn[i][k] * matIn[j][k];
            }
            matOut[i][j] = sum;
            matOut[j][i] = sum;
        }
    }
}

void randomVectorInitialize(vector<double> &vec){
    for (int i = 0; i < vec.size(); ++i){
        srand((unsigned) time(NULL));
        vec[i] = (rand() % 100000) + 1; // ver que valor tiene que ir aca, tengo entendido que un cero rompe
    }
}

double powerMethod(Matrix &mat, vector<double> &res, int niter){
    vector<double> aux(res.size());
    for (int i = 0; i < niter; ++i){
        productMatrixVector(mat, res, aux);
        double norma = sqrt(dotProduct(aux, aux));
        for (int j = 0; j < res.size(); ++j){
            res[j] = aux[j] / norma;
        }
    }
    // productMatrixVector(mat, res, aux);
    return dotProduct(res, aux);
}

void substractMatMat(Matrix &mat1, Matrix &mat2, Matrix &matOut){
    for (int i = 0; i < matOut.size(); ++i)
        for (int j = 0; j < matOut[i].size(); ++j)
            matOut[i][j] = mat1[i][j] - mat2[i][j];
}

void PCA(Matrix &covariances, Matrix &eigenVectors, vector<double> &eigenValues, int alpha, int niter){
    Matrix deflater(covariances.size(), vector<double>(covariances.size()));
    for (int i = 0; i < alpha; ++i){
        randomVectorInitialize(eigenVectors[i]);
        eigenValues[i] = powerMethod(covariances, eigenVectors[i], niter); // CRITERIO DE PARADA
        productColRow(eigenVectors[i], eigenVectors[i], deflater, eigenValues[i]);
        substractMatMat(covariances, deflater, covariances);
    }
}

void PLSDA(DigitImages &images, Matrix &eigenVectors, vector<double> &eigenValues, int gamma, int niter){
    Matrix XtY(images.imgSizeSqr, vector<double>(LABELS_QTY)); // XtY = (YtX)t
    Matrix Mi(images.imgSizeSqr, vector<double>(images.imgSizeSqr));
    Matrix TiTitX(images.centralizedPLSDA.size(), vector<double>(images.imgSizeSqr));
    Matrix TiTitY(images.labelY.size(), vector<double>(LABELS_QTY));
    vector<double> Ti(images.centralizedPLSDA.size());
    vector<double> TitX(images.imgSizeSqr);
    vector<double> TitY(LABELS_QTY);
    for (int i = 0; i < gamma; ++i){
        productMatMat(images.centralizedPLSDA, images.labelY, XtY, true);
        productMatMatSimetric(XtY, Mi); // XtY * (XtY)t
        randomVectorInitialize(eigenVectors[i]);
        eigenValues[i] = powerMethod(Mi, eigenVectors[i], niter); // CRITERIO DE PARADA
        productMatrixVector(images.centralizedPLSDA, eigenVectors[i], Ti);
        double norma = sqrt(dotProduct(Ti, Ti));
        for (int j = 0; j < Ti.size(); ++j)
            Ti[j] /= norma;
        productVectorMatrix(Ti, images.centralizedPLSDA, TitX);
        productColRow(Ti, TitX, TiTitX);
        substractMatMat(images.centralizedPLSDA, TiTitX, images.centralizedPLSDA);
        productVectorMatrix(Ti, images.labelY, TitY);
        productColRow(Ti, TitY, TiTitY);
        substractMatMat(images.labelY, TiTitY, images.labelY);
    }
}

void testToTC(DigitImages &imagesTrain, DigitImages &imagesTest){
    imagesTest.centralized = Matrix(imagesTest.images.size(), vector<double>(imagesTest.imgSizeSqr));
    for (int i = 0; i < imagesTest.images.size(); ++i)
        for (int j = 0; j < imagesTest.images[i].pixels.size(); ++j)
            imagesTest.centralized[i][j] = (imagesTest.images[i].pixels[j] - imagesTrain.medians[j]) / sqrt(imagesTrain.images.size() - 1);
}

#endif
