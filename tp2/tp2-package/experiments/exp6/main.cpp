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

    input >> inFileDir;
    getline(input, line);

    getline(input, line);
    stringstream lineStream(line);
    DigitImages imagesTrain, imagesTest;

    populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);

    vector<int> counts(LABELS_QTY, 0);
    Matrix avgs(LABELS_QTY, vector<double>(DEFAULT_IMAGE_SIZE, 0));
    for (int i = 0; i < imagesTrain.images.size(); ++i){
        for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
            avgs[imagesTrain.labels[i]][j] += imagesTrain.images[i][j];
        counts[imagesTrain.labels[i]]++;
    }
    for (int i = 0; i < LABELS_QTY; ++i)
        for (int j = 0; j < DEFAULT_IMAGE_SIZE; ++j)
            avgs[i][j] /= counts[i];
    for (int i = 0; i < LABELS_QTY; ++i){
        string out = argv[2];
        out += to_string(i);
        out += ".out";
        ofstream output(out);
        printImage(avgs[i], output);
        output.close();
    }
    input.close();
    return 0;
}
