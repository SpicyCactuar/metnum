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
    int label;
    Pixels pixels;
};
/** Class representing a smart container of DigitImage(s) **/

struct DigitImagesHelper {
    int samples, img_size, img_size_sqr;
    vector<int> medians;
    vector<DigitImage> images;
    Matrix correlation; // X
    Matrix covariances; // M = X^tX

    // -------- Initialization --------
    void init() {
        img_size = DEFAULT_IMAGE_SIDE_SIZE;
        img_size_sqr = img_size * img_size;
        medians = vector<int>(img_size_sqr, 0);
    }
    // -------- Covariance --------

    void calculateCovariances(){
        covariances = Matrix(img_size_sqr, vector<double>(img_size_sqr, 0.0));
        for (int i = 0; i < img_size_sqr; ++i){
            for (int j = 0; j < img_size_sqr; ++j){
                int sum = 0;
                for (int k = 0; k < samples; ++k){
                    sum += correlation[k][i] * correlation[k][j];
                }
                covariances[i][j] = sum;
            }
        }
    }
    // -------- Printers --------

    void printCorrelation(ostream &output, int index) {
        int i = 0, j = 0;
        for (int k = 0; k < img_size_sqr; ++k) {
            if(j == 0)
                output << '[';
            output << correlation[index][k];
            if(j == img_size - 1){
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
        for (int i = 0; i < img_size_sqr; ++i) {
            for (int j = 0; j < img_size_sqr; ++j) {
                if(j == 0)
                    output << '[';
                output << covariances[i][j];
                if(j == img_size_sqr - 1)
                    output << ']' << endl;
                else
                    output << ',';
            }
        }
    }

    void prettyPrint(ostream &output, string type) {
        if(type == "correlation"){
            for (int i = 0; i < samples; ++i){
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

    void init(Matrix &eigenVectors, vector<DigitImage> &images){
        transformation = Matrix(images.size(), vector<double>(eigenVectors.size()));
        for (int i = 0; i < images.size(); ++i)
            for (int j = 0; j < eigenVectors.size(); ++j)
                transformation[i][j] = dotProduct(eigenVectors[j], images[i].pixels);
    }
};

#endif
