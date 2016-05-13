#ifndef Types_h
#define Types_h

#include "Imports.h"
#include "MatrixAlgorithms.h"

const int DEFAULT_IMAGE_SIDE_SIZE = 28;
const int DEFAULT_IMAGE_SIZE = DEFAULT_IMAGE_SIDE_SIZE * DEFAULT_IMAGE_SIDE_SIZE;
const int LABELS_QTY = 10;

const string DEFAULT_PROCESS_TIME = "Default process time";
const string KNN_TOTAL_TIME = "KNN total time";
const string KNN_PER_IMAGE_TIME = "KNN per image time";
const string PREPROCESS_DIMENSION_TIME = "Preprocess dimension time (PCA - PLS)";
const string TC_TIME = "TC time";

/** Class representing a stats Structure **/
struct AwesomeStatistic {
    int k;
    double hitRate;
    double precision;
    double recall;
    double f1Score;
    vector<vector<int>> confusion;
    int defaultProcessTime;
    int kNNTotalTime;
    double kNNPerImageTime;
    int preprocessTime;
    int tcTime;
};

/** Class representing a smart container of DigitImage(s) **/
struct DigitImages {
    vector<int> labels;
    vector<double> means, labelYMeans;
    // vector<DigitImage> images;
    Matrix images;
    Matrix centralized; // X
    Matrix centralizedPLSDA; // X
    Matrix covariances; // M = X^tX
    Matrix labelY;

    // -------- Initialization --------
    void init() {
        means = vector<double>(DEFAULT_IMAGE_SIZE, 0);
        labelYMeans = vector<double>(LABELS_QTY, 0);
    }

    // -------- Means --------
    void getMeans(){
        for (int i = 0; i < DEFAULT_IMAGE_SIZE; ++i)
            means[i] /= images.size();
        for (int i = 0; i < LABELS_QTY; ++i)
            labelYMeans[i] /= labelY.size();
    }

    // -------- Correlation --------
    void calculateCentralized(){
        for (int i = 0; i < images.size(); ++i)
            for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j){
                centralized[i][j] = (centralized[i][j] - means[j]) / sqrt(images.size() - 1);
                centralizedPLSDA[i][j] = (centralizedPLSDA[i][j] - means[j]) / sqrt(images.size() - 1);
            }
    }

    // -------- CorrelationTEST --------
    void calculateCentralizedTest(vector<double> &means, int samples){
        centralized = Matrix(images.size(), vector<double>(DEFAULT_IMAGE_SIZE));
        for (int i = 0; i < images.size(); ++i)
            for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
                centralized[i][j] = (images[i][j] - means[j]) / sqrt(samples - 1);
    }

    // -------- Covariance --------
    //XtX = M
    void calculateCovariances(){
        covariances = Matrix(DEFAULT_IMAGE_SIZE, vector<double>(DEFAULT_IMAGE_SIZE));
        for (int i = 0; i < DEFAULT_IMAGE_SIZE; ++i){
            for (int j = i; j < DEFAULT_IMAGE_SIZE; ++j){
                double sum = 0;
                for (int k = 0; k < images.size(); ++k){
                    sum += centralized[k][i] * centralized[k][j];
                }
                covariances[i][j] = sum;
                covariances[j][i] = sum;
            }
        }
    }

    // -------- MeansLabels --------
    void calculateMeansLabels(){
        for (int i = 0; i < labelY.size(); ++i)
            for (int j = 0; j < LABELS_QTY; ++j)
                labelY[i][j] = (labelY[i][j] - labelYMeans[j]) / sqrt(labelY.size() - 1);
    }
};

/** Class representing one manuscript digit image **/
struct TC {
    Matrix transformation;

    void init(Matrix &eigenVectors, Matrix &data){
        transformation = Matrix(data.size(), vector<double>(eigenVectors.size()));
        for (int i = 0; i < data.size(); ++i)
            for (int j = 0; j < eigenVectors.size(); ++j)
                transformation[i][j] = dotProduct(eigenVectors[j], data[i]);
    }
};

#endif
