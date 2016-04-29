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
    // ofstream output(argv[2]);
    string method = argv[3];

    string inFileDir, line;
    int kMinus, alpha, gamma, kMayus;

    input >> inFileDir >> kMinus >> alpha >> gamma >> kMayus;
    // skip the rest of the first line
    getline(input, line);
    for (int i = 0; i < kMayus; ++i){
        getline(input, line);
        stringstream lineStream(line);
        DigitImages imagesTrain, imagesTest;
        populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
        imagesTrain.calculateCorrelation();
        if(method == "0"){
            // TODO kNN
        }
        if(method == "1"){
            imagesTrain.calculateCovariances();
            Matrix eigenVectors(alpha, vector<double>(imagesTrain.covariances.size()));
            vector<double> eigenValues(alpha);
            TC tcTrain, tcTest;
            PCA(imagesTrain.covariances, eigenVectors, eigenValues, alpha, 500);
            tcTrain.init(eigenVectors, imagesTrain.correlation);
            testToTC(imagesTrain, imagesTest);
            tcTest.init(eigenVectors, imagesTest.correlation);
            // for (int j = 0; j < alpha; ++j)
            //     cout << scientific << eigenValues[j] << endl;
            for (int j = 0; j < tcTest.transformation.size(); ++j){
                int digito = kNN(tcTest.transformation[j], tcTrain.transformation, kMinus, imagesTrain);
                cout << "la imagen: " << j << " del kNN: " << digito << " del label: " << imagesTest.images[j].label << endl;
            }
            // imagesTrain.prettyPrint(cout, "covariance");
        }
        if(method == "2"){
            imagesTrain.calculateMedianLabels();
            Matrix eigenVectors(gamma, vector<double>(imagesTrain.imgSizeSqr));
            vector<double> eigenValues(gamma);
            TC tcTrain, tcTest;
            PLSDA(imagesTrain, eigenVectors, eigenValues, gamma, 500);
            tcTrain.init(eigenVectors, imagesTrain.correlation);
            testToTC(imagesTrain, imagesTest);
            tcTest.init(eigenVectors, imagesTest.correlation);
            for (int j = 0; j < gamma; ++j)
                cout << scientific << eigenValues[j] << endl;
            for (int j = 0; j < tcTest.transformation.size(); ++j){
                int digito = kNN(tcTest.transformation[j], tcTrain.transformation, kMinus, imagesTrain);
                cout << "la imagen: " << j << " del kNN: " << digito << " del label: " << imagesTest.images[j].label << endl;
            }
        }
    }

    // images.prettyPrint(cout, "correlation");
    input.close();
    // output.close();

/*
    //TEST DE LA DIAPO!!
    DigitImages asd;
    asd.imgSizeSqr = 2;
    asd.covariances = {{66.2134, 27.1263}, {27.1263, 12.5491}};
    Matrix eigenVectors(2, vector<double>(2));
    vector<double> eigenValues(2);
    TC tc;
    PCA(asd, eigenVectors, eigenValues, 2, 5, tc);
    printVector(eigenValues);
    printMatrix(eigenVectors);
*/
    return 0;
}
