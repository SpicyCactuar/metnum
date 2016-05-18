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
    getline(input, line);

    getline(input, line);
    stringstream lineStream(line);
    DigitImages imagesTrain, imagesTest;
    Matrix eigenVectorsPCA(3, vector<double>(DEFAULT_IMAGE_SIZE));
    vector<double> eigenValuesPCA(3);
    Matrix eigenVectorsPLSDA(3, vector<double>(DEFAULT_IMAGE_SIZE));
    vector<double> eigenValuesPLSDA(3);
    int niterPCA = 1000;
    int niterPLSDA = 1000;

    populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
    imagesTrain.getMeans();
    imagesTrain.calculateCentralized();
    imagesTrain.calculateCovariances();
    imagesTrain.calculateMeansLabels();

    PCA(imagesTrain.covariances, eigenVectorsPCA, eigenValuesPCA, 3, niterPCA);
    PLSDA(imagesTrain, eigenVectorsPLSDA, eigenValuesPLSDA, 3, niterPLSDA);
    TC tcTrainPCA, tcTrainPLSDA;
    tcTrainPCA.init(eigenVectorsPCA, imagesTrain.centralized);
    tcTrainPLSDA.init(eigenVectorsPLSDA, imagesTrain.centralized);
    for (int i = 0; i < tcTrainPCA.transformation.size(); ++i){
        output << imagesTrain.labels[i] << ",";
        for (int j = 0; j < 3; ++j){
            output << tcTrainPCA.transformation[i][j] << ",";
            output << tcTrainPLSDA.transformation[i][j] << ",";
        }
        output << endl;
    }

    input.close();
    output.close();
    return 0;
}
