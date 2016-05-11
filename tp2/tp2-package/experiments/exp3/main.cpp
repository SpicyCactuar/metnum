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
    int alpha;

    input >> inFileDir >> alpha;
    // skip the rest of the first line
    getline(input, line);

    getline(input, line);
    stringstream lineStream(line);
    DigitImages imagesTrain, imagesTest;
    Matrix eigenVectors(alpha, vector<double>(DEFAULT_IMAGE_SIZE));
    vector<double> eigenValues(alpha);
    int niterPCA = 1000;

    populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
    imagesTrain.getMeans();
    imagesTrain.calculateCentralized();
    imagesTrain.calculateCovariances();

    PCA(imagesTrain.covariances, eigenVectors, eigenValues, alpha, niterPCA);

    Matrix xMeans(imagesTrain.centralized.size(), vector<double>(DEFAULT_IMAGE_SIZE, 0));
    for (int i = 0; i < xMeans.size(); ++i)
        for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
            xMeans[i][j] += imagesTrain.centralized[i][j] * sqrt(xMeans.size() - 1);
    vector<double> aux(xMeans.size());
    productMatrixVector(xMeans, eigenVectors[0], aux);
    productColRow(aux, eigenVectors[0], xMeans);
    for (int i = 0; i < xMeans.size(); ++i)
        for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
            xMeans[i][j] += imagesTrain.means[j];
    aux = vector<double>(DEFAULT_IMAGE_SIZE, 0);
    for (int i = 0; i < DEFAULT_IMAGE_SIZE; ++i){
        for (int j = 0; j < xMeans.size(); ++j){
            aux[i] += xMeans[j][i];
        }
    }
    for (int i = 0; i < aux.size(); ++i){
        aux[i] /= xMeans.size();
    }
    printImage(aux, output);

    // vector<double> aux(imagesTrain.centralized.size());
    // productMatrixVector(imagesTrain.centralized, eigenVectors[0], aux);
    // Matrix res(aux.size(), vector<double>(DEFAULT_IMAGE_SIZE));
    // productColRow(aux, eigenVectors[0], res);

    // for (int i = 0; i < res.size(); ++i)
    //     for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
    //         res[i][j] = res[i][j] * sqrt(imagesTrain.images.size() - 1) + imagesTrain.means[j];

    input.close();
    output.close();
    return 0;
}
