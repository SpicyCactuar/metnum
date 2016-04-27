//Compile: g++ -o main main.cpp -std=c++11
//Run con tests provistos ./main ../../tests/test1.in .......
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

    string inFileDir;
    int kMinus, alpha, gamma, kMayus;

    input >> inFileDir >> kMinus >> alpha >> gamma >> kMayus;
    DigitImagesHelper imagesHelper;
    populateDigitImagesHelper(imagesHelper, inFileDir);
    if(method == "0"){
        // TODO kNN
    }
    if(method == "1"){
        imagesHelper.calculateCovariances();
        Matrix eigenVectors(alpha, vector<double>(imagesHelper.img_size_sqr));
        vector<double> eigenValues(imagesHelper.img_size_sqr);
        PCA(imagesHelper.covariances, eigenVectors, eigenValues, alpha, 5);
        // imagesHelper.prettyPrint(cout, "covariance");
    }
    if(method == "2"){
        // TODO PLS-DA + kNN
    }

    // imagesHelper.prettyPrint(cout, "correlation");
    input.close();
    // output.close();

/*
    //TEST DE LA DIAPO!!
    DigitImagesHelper asd;
    asd.img_size_sqr = 2;
    asd.covariances = {{66.2134, 27.1263}, {27.1263, 12.5491}};
    Matrix eigenVectors(2, vector<double>(2));
    vector<double> eigenValues(2);
    PCA(asd.covariances, eigenVectors, eigenValues, 2, 5);
    printVector(eigenValues);
    printMatrix(eigenVectors);
*/
    return 0;
}
