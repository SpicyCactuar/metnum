#ifndef Types_h
#define Types_h

#include "Imports.h"
const int DEFAULT_IMAGE_SIDE_SIZE = 28;

using Matrix = vector<vector<double> >;
using Pixels = vector<double>;

//x^ty = # product
double dotProduct(vector<double> &vec1, vector<double> &vec2){
    double sum = 0;
    for (int i = 0; i < vec1.size(); ++i)
        sum += vec1[i] * vec2[i];
    return sum;
}

/** Class representing one manuscript digit image **/
struct DigitImage {
    //faltaria poner label por defecto = -1
    int label;
    Pixels pixels;
};
/** Class representing a smart container of DigitImage(s) **/

struct DigitImages {
    int imgSizeSqr;
    vector<int> medians;
    vector<DigitImage> images;
    Matrix correlation; // X
    Matrix covariances; // M = X^tX

    // -------- Initialization --------
    void init() {
        imgSizeSqr = DEFAULT_IMAGE_SIDE_SIZE * DEFAULT_IMAGE_SIDE_SIZE;
        medians = vector<int>(imgSizeSqr, 0);
    }

    void calculateCorrelation(){
        for (int i = 0; i < medians.size(); ++i)
            medians[i] /= images.size();
        for (int i = 0; i < images.size(); ++i)
            for (int j = 0; j < medians.size(); ++j)
                correlation[i][j] = (correlation[i][j] - medians[j]) / sqrt(images.size() - 1);
    }

    // -------- Covariance --------
    void calculateCovariances(){
        covariances = Matrix(imgSizeSqr, vector<double>(imgSizeSqr));
        for (int i = 0; i < imgSizeSqr; ++i){
            for (int j = i; j < imgSizeSqr; ++j){
                double sum = 0;
                for (int k = 0; k < images.size(); ++k){
                    sum += correlation[k][i] * correlation[k][j];
                }
                covariances[i][j] = sum;
                covariances[j][i] = sum;
            }
        }
    }

    // -------- Printers --------
    void printCorrelation(ostream &output, int index) {
        int i = 0, j = 0;
        for (int k = 0; k < imgSizeSqr; ++k) {
            if(j == 0)
                output << '[';
            output << correlation[index][k];
            if(j == DEFAULT_IMAGE_SIDE_SIZE - 1){
                j = 0;
                i++;
                output << ']' << endl;
            }
            else{
                j++;
                output << ',';
            }
        }
    }

    void printCovariance(ostream &output) {
        for (int i = 0; i < imgSizeSqr; ++i) {
            for (int j = 0; j < imgSizeSqr; ++j) {
                if(j == 0)
                    output << '[';
                output << covariances[i][j];
                if(j == imgSizeSqr - 1)
                    output << ']' << endl;
                else
                    output << ',';
            }
        }
    }

    void prettyPrint(ostream &output, string type) {
        if(type == "correlation"){
            for (int i = 0; i < images.size(); ++i){
                output << endl << "LABEL" << endl << "=====" << endl << endl;
                output << images[i].label << endl << endl;
                output << "PIXELS" << endl << "======" << endl << endl;
                printCorrelation(output, i);
            }
        }
        else if(type == "covariance"){
            printCovariance(output);
        }
    }
};

/** Class representing one manuscript digit image **/
struct TC {
    Matrix transformation;

    void init(Matrix &eigenVectors, Matrix &correlation){
        transformation = Matrix(correlation.size(), vector<double>(eigenVectors.size()));
        for (int i = 0; i < correlation.size(); ++i)
            for (int j = 0; j < eigenVectors.size(); ++j)
                transformation[i][j] = dotProduct(eigenVectors[j], correlation[i]);
    }
};

#endif
