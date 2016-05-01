//Compile: g++ -o tp main.cpp -std=c++11
//Run con tests provistos ./tp tests/test1.in .......
#include "Algorithms.h"
#include "Tests.h"
#include "Types.h"
#include "InputProcessor.h"
#include "Print.h"

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)
//   -(a: algorithm -> 0: kNN, 1: PCA + kNN, 2: PLS-DA + kNN)

int main(int argc, char const *argv[]){
    if(argc != 4){
        cout << "Parameters should be: (i: input file), (o: output file), (a: algorithm -> 0: kNN, 1: PCA + kNN, 2: PLS-DA + kNN)" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string method = argv[3];

    string inFileDir, line;
    int kMinus, alpha, gamma, kMayus;

    input >> inFileDir >> kMinus >> alpha >> gamma >> kMayus;
    // skip the rest of the first line
    getline(input, line);

    for (int i = 0; i < kMayus; ++i){
        //train or test input
        getline(input, line);
        stringstream lineStream(line);
        DigitImages imagesTrain, imagesTest;
        populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
        //centralize train data set, calc covariances and centralize labels
        imagesTrain.calculateCentralized();
        imagesTrain.calculateCovariances();
        imagesTrain.calculateMedianLabels();
        Matrix eigenVectorsPCA(alpha, vector<double>(imagesTrain.covariances.size()));
        vector<double> eigenValuesPCA(alpha);
        Matrix eigenVectorsPLSDA(gamma, vector<double>(imagesTrain.imgSizeSqr));
        vector<double> eigenValuesPLSDA(gamma);
        int niter = 1000;
        //stores eigen vector and values with niter power method iterations
        PCA(imagesTrain.covariances, eigenVectorsPCA, eigenValuesPCA, alpha, niter);
        PLSDA(imagesTrain, eigenVectorsPLSDA, eigenValuesPLSDA, gamma, niter);
        for (int j = 0; j < alpha; ++j){
            output << scientific << sqrt(eigenValuesPCA[j]) << endl;
            // output << scientific << eigenValues[j] << endl;
        }
        for (int j = 0; j < gamma; ++j)
            output << scientific << eigenValuesPLSDA[j] << endl;

        if(method == "0"){
            imagesTest.calculateCentralized();
            for (int j = 0; j < imagesTest.centralized.size(); ++j){
                int digito = kNN(imagesTest.centralized[j], imagesTrain.centralized, kMinus, imagesTrain);
                cout << "la imagen: " << j << " del kNN: " << digito << " del label: " << imagesTest.images[j].label << endl;
            }
        }
        if(method == "1"){
            TC tcTrain, tcTest;
            tcTrain.init(eigenVectorsPCA, imagesTrain.centralized);
            testToTC(imagesTrain, imagesTest);
            tcTest.init(eigenVectorsPCA, imagesTest.centralized);
            // for (int j = 0; j < tcTest.transformation.size(); ++j){
            //     int digito = kNN(tcTest.transformation[j], tcTrain.transformation, kMinus, imagesTrain);
            //     cout << "la imagen: " << j << " del kNN: " << digito << " del label: " << imagesTest.images[j].label << endl;
            // }
        }
        if(method == "2"){
            TC tcTrain, tcTest;
            tcTrain.init(eigenVectorsPLSDA, imagesTrain.centralized);
            testToTC(imagesTrain, imagesTest);
            tcTest.init(eigenVectorsPLSDA, imagesTest.centralized);
            // for (int j = 0; j < tcTest.transformation.size(); ++j){
            //     int digito = kNN(tcTest.transformation[j], tcTrain.transformation, kMinus, imagesTrain);
            //     cout << "la imagen: " << j << " del kNN: " << digito << " del label: " << imagesTest.images[j].label << endl;
            // }
        }
    }
    input.close();
    output.close();
    return 0;
}
