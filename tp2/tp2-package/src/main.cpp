//Compile: g++ -o tp main.cpp -std=c++11
//Run con tests provistos ./tp tests/test1.in .......
#include "Algorithms.h"
#include "Tests.h"
#include "Types.h"
#include "InputProcessor.h"
#include "Print.h"
#include "MatrixAlgorithms.h"

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

    for (int iter = 0; iter < kMayus; ++iter){
        //train or test input
        getline(input, line);
        stringstream lineStream(line);
        DigitImages imagesTrain, imagesTest;
        populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
        imagesTrain.getMeans();
        imagesTrain.calculateCentralized();
        imagesTrain.calculateCovariances();
        imagesTrain.calculateMeansLabels();
        imagesTest.calculateCentralizedTest(imagesTrain.means, imagesTrain.images.size());
        Matrix eigenVectorsPCA(alpha, vector<double>(DEFAULT_IMAGE_SIZE));
        Matrix eigenVectorsPLSDA(gamma, vector<double>(DEFAULT_IMAGE_SIZE));
        vector<double> eigenValuesPCA(alpha);
        vector<double> eigenValuesPLSDA(gamma);
        int niterPCA = 1000;
        int niterPLSDA = 1000;
        //stores eigen vector and values with niter power method iterations
        PCA(imagesTrain.covariances, eigenVectorsPCA, eigenValuesPCA, alpha, niterPCA);
        for (int i = 0; i < alpha; ++i){
            output << scientific << sqrt(eigenValuesPCA[i]) << endl;
            // output << scientific << eigenValues[i] << endl;
        }
        PLSDA(imagesTrain, eigenVectorsPLSDA, eigenValuesPLSDA, gamma, niterPLSDA);
        for (int i = 0; i < gamma; ++i)
            output << scientific << eigenValuesPLSDA[i] << endl;

        if(method == "0"){
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                int digito = kNN(imagesTest.centralized[i], imagesTrain.centralized, kMinus, imagesTrain);
                cout << "la imagen: " << i << " del kNN: " << digito << " del label: " << imagesTest.images[i].label << endl;
            }
        }
        if(method == "1"){
            TC tcTrain, tcTest;
            tcTrain.init(eigenVectorsPCA, imagesTrain.centralized);
            tcTest.init(eigenVectorsPCA, imagesTest.centralized);
            for (int i = 0; i < tcTest.transformation.size(); ++i){
                int digito = kNN(tcTest.transformation[i], tcTrain.transformation, kMinus, imagesTrain);
                cout << "la imagen: " << i << " del kNN: " << digito << " del label: " << imagesTest.images[i].label << endl;
            }
        }
        if(method == "2"){
            TC tcTrain, tcTest;
            tcTrain.init(eigenVectorsPLSDA, imagesTrain.centralized);
            tcTest.init(eigenVectorsPLSDA, imagesTest.centralized);
            for (int i = 0; i < tcTest.transformation.size(); ++i){
                int digito = kNN(tcTest.transformation[i], tcTrain.transformation, kMinus, imagesTrain);
                cout << "la imagen: " << i << " del kNN: " << digito << " del label: " << imagesTest.images[i].label << endl;
            }
        }
    }
    input.close();
    output.close();
    return 0;
}
