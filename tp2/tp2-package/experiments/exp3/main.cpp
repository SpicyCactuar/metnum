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
    int niter = 1000;

    populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
    imagesTrain.getMeans();
    imagesTrain.calculateCentralized();
    imagesTrain.calculateCovariances();

    PCA(imagesTrain.covariances, eigenVectors, eigenValues, alpha, niter);

    vector<double> aux(DEFAULT_IMAGE_SIZE);
    for (int k = 0; k < eigenVectors.size(); ++k){
        ofstream output(argv[2] + to_string(k));
        double max = eigenVectors[k][0], min = eigenVectors[k][0];
        for (int i = 1; i < DEFAULT_IMAGE_SIZE; ++i){
            if(eigenVectors[k][i] > max)
                max = eigenVectors[k][i];
            else if(eigenVectors[k][i] < min)
                min = eigenVectors[k][i];
        }
        for (int i = 0; i < DEFAULT_IMAGE_SIZE; ++i){
            aux[i] = eigenVectors[k][i] - min;
            aux[i] *= 255;
            aux[i] /= (max - min);
        }
        printImage(aux, output);
        output.close();
    }

    // vector<double> aux(imagesTrain.centralized.size());
    // productMatrixVector(imagesTrain.centralized, eigenVectors[0], aux);
    // Matrix res(aux.size(), vector<double>(DEFAULT_IMAGE_SIZE));
    // productColRow(aux, eigenVectors[0], res);

    // for (int i = 0; i < res.size(); ++i)
    //     for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
    //         res[i][j] = res[i][j] * sqrt(imagesTrain.images.size() - 1) + imagesTrain.means[j];

    input.close();
    return 0;
}
