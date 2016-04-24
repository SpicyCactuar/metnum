#ifndef Types_h
#define Types_h

#include "Imports.h"

const int DEFAULT_IMAGE_SIDE_SIZE = 28;
const int DEFAULT_IMAGE_TOTAL_SIZE = DEFAULT_IMAGE_SIDE_SIZE * DEFAULT_IMAGE_SIDE_SIZE;

using Matrix = vector<vector<double> >;

struct DigitImages {
    int muestras, img_size, img_size_sqr;
    vector<int> medias, labels;
    Matrix correlation; // X
    Matrix covariances; // M = X^tX

    void populateDigitImages(string &inFileDir, int size = DEFAULT_IMAGE_SIDE_SIZE) {
        img_size = size;
        img_size_sqr = img_size * img_size;
        medias = vector<int>(img_size_sqr, 0);
        labels = vector<int>(img_size_sqr, 0);
        string nameInFile = inFileDir + "train.csv";
        ifstream input(nameInFile);
        // First line is not needed
        string line;
        int k = 0;
        getline(input, line);
        while(getline(input, line)){
            vector<double> image(img_size_sqr, 0);
            stringstream lineStream(line);
            int i = 0;
            string pixel;
            getline(lineStream, pixel, ',');
            labels[k] = stoi(pixel);
            k++;
            while(getline(lineStream, pixel, ',')){
                int iPixel = stoi(pixel);
                image[i] = iPixel;
                medias[i] += iPixel;
                i++;
            }
            correlation.push_back(image);
        }
        input.close();
        muestras = correlation.size();
        for (int i = 0; i < img_size_sqr; ++i){
            medias[i] /= muestras;
        }
        for (int i = 0; i < muestras; ++i){
            for (int j = 0; j < img_size_sqr; ++j){
                correlation[i][j] = (correlation[i][j] - medias[j]) / sqrt(muestras - 1);
            }
        }
    }

    void calculateCovariances(){
        covariances = Matrix(img_size_sqr, vector<double>(img_size_sqr, 0.0));
        for (int i = 0; i < img_size_sqr; ++i){
            for (int j = 0; j < img_size_sqr; ++j){
                int sum = 0;
                for (int k = 0; k < muestras; ++k){
                    sum += correlation[k][i] * correlation[k][j];
                }
                covariances[i][j] = sum;
            }
        }
    }

    // Printers

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
            for (int i = 0; i < muestras; ++i){
                output << endl << "LABEL" << endl << "=====" << endl << endl;
                output << labels[i] << endl << endl;
                output << "PIXELS" << endl << "======" << endl << endl;
                printCorrelation(output, i);
            }
        }
        else if(type == "covariance"){
            printCovariance(output);
        }
    }
};

#endif
