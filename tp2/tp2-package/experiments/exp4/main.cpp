//Compile: g++ -o tp main.cpp -std=c++11
//Run con tests provistos ./tp tests/test1.in .......
#include "../../src/Algorithms.h"
#include "../../src/Tests.h"
#include "../../src/Types.h"
#include "../../src/InputProcessor.h"
#include "../../src/Print.h"
#include "../../src/MatrixAlgorithms.h"

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)

int main(int argc, char const *argv[]){
    if(argc != 3){
        cout << "Parameters should be: (i: input file), (o: output file)" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    string inFileDir, line;

    input >> inFileDir;
    // skip the rest of the first line
    getline(input, line);

    getline(input, line);
    stringstream lineStream(line);
    DigitImages imagesTrain, imagesTest;
    Matrix eigenVectorsPCA(DEFAULT_IMAGE_SIZE, vector<double>(DEFAULT_IMAGE_SIZE));
    vector<double> eigenValuesPCA(DEFAULT_IMAGE_SIZE);
    Matrix eigenVectorsPLSDA(DEFAULT_IMAGE_SIZE, vector<double>(DEFAULT_IMAGE_SIZE));
    vector<double> eigenValuesPLSDA(DEFAULT_IMAGE_SIZE);
    int niterPCA = 1000;
    int niterPLSDA = 1000;

    populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
    imagesTrain.getMeans();
    imagesTrain.calculateCentralized();
    imagesTrain.calculateCovariances();
    imagesTrain.calculateMeansLabels();

    PCA(imagesTrain.covariances, eigenVectorsPCA, eigenValuesPCA, DEFAULT_IMAGE_SIZE, niterPCA);
    PLSDA(imagesTrain, eigenVectorsPLSDA, eigenValuesPLSDA, DEFAULT_IMAGE_SIZE, niterPLSDA);

    double partialPCA = 0, partialPLSDA = 0;
    for (int i = 0; i < DEFAULT_IMAGE_SIZE; ++i) {
        partialPCA += eigenValuesPCA[i];
        partialPLSDA += eigenValuesPLSDA[i];
        output << partialPCA << "," << partialPLSDA << endl;
    }

    input.close();
    output.close();
    return 0;
}
