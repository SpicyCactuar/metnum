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
    DigitImages images;
    images.populateDigitImages(inFileDir);
    if(method == "0"){
        // TODO kNN
    }
    if(method == "1"){
        images.calculateCovariances();
        Matrix eigenVectors(images.img_size_sqr, vector<double>(images.img_size_sqr));
        vector<double> eigenValues(images.img_size_sqr);
        PCA(images.covariances, eigenVectors, eigenValues, 5);
        // images.prettyPrint(cout, "covariance");
    }
    if(method == "2"){
        // TODO PLS-DA + kNN
    }

    // images.prettyPrint(cout, "correlation");
    input.close();
    // output.close();
    return 0;
}
