#ifndef Types_h
#define Types_h

#include "Imports.h"

const int DEFAULT_IMAGE_SIDE_SIZE = 28;
// TODO: Check this value
const int DEFAULT_IMAGES_AMOUNT = 2;

using Matrix = vector<vector<double> >;
using Pixels = vector<double>;

/** Class representing one manuscript digit image **/

struct DigitImage {

    Pixels pixels;

    // -------- Distance --------

    int distanceTo(DigitImage &image) {
        return 0;
    }

};

/** Class representing a smart container of DigitImage(s) **/

struct DigitImagesHelper {
    
    int samples, img_size, img_size_sqr;
    vector<int> medians, labels;
    vector<DigitImage> images;
    Matrix correlation; // X
    Matrix covariances; // M = X^tX

    /* // -------- Input population --------

    void populateDigitImages(string &inFileDir, int size = DEFAULT_IMAGE_SIDE_SIZE) {
        img_size = size;
        img_size_sqr = img_size * img_size;
        medians = vector<int>(img_size_sqr, 0);
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
                medians[i] += iPixel;
                i++;
            }
            correlation.push_back(image);
        }
        input.close();
        samples = correlation.size();
        for (int i = 0; i < img_size_sqr; ++i){
            medians[i] /= samples;
        }
        for (int i = 0; i < samples; ++i){
            for (int j = 0; j < img_size_sqr; ++j){
                correlation[i][j] = (correlation[i][j] - medians[j]) / sqrt(samples - 1);
            }
        }
    } */

    // -------- Initialization --------

    void init(int size, int amount) {
        img_size = size;
        img_size_sqr = img_size * img_size;
        medians = vector<int>(img_size_sqr, 0);
        labels = vector<int>(img_size_sqr, 0);

        samples = amount;
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
