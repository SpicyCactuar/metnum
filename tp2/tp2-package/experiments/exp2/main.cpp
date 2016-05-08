//Compile: g++ -o tp main.cpp -std=c++11
//Run con tests provistos ./tp tests/test1.in .......
#include "../../src/Algorithms.h"
#include "../../src/Tests.h"
#include "../../src/Types.h"
#include "../../src/InputProcessor.h"
#include "../../src/Print.h"
#include "../../src/MatrixAlgorithms.h"
#include "../../src/Stats.h"

// --- Input arguments ---
//   -(i: input file)
//   -(o: output file)
//   -(a: alpha)
//   -(g: gamma)

using namespace chrono;

int main(int argc, char const *argv[]){
    if(argc != 5){
        cout << "Parameters should be: (i: input file), (o: output file), (k: k minus), (a: alpha), (g: gamma)" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int alpha = stoi(argv[3]);
    int gamma = stoi(argv[4]);

    string inFileDir, line;
    int kMayus;

    input >> inFileDir >> kMayus;
    // skip the rest of the first line
    getline(input, line);

    for (int iter = 0; iter < kMayus; ++iter){
        vector<TimeEvent> timeTracker;
        high_resolution_clock::time_point timeIterationStart = high_resolution_clock::now();
        //train or test input
        getline(input, line);
        stringstream lineStream(line);
        DigitImages imagesTrain, imagesTest;

        populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
        imagesTrain.getMeans();
        imagesTrain.calculateCentralized();

        high_resolution_clock::time_point timeDefaultProcessEnded = high_resolution_clock::now();

        timeTracker.push_back(TimeEvent("Default Process", duration_cast<milliseconds>( timeDefaultProcessEnded - timeIterationStart ).count()));

        vector<int> knnValues(imagesTest.centralized.size());
        vector<int> trueValues(imagesTest.centralized.size());

        /////

        vector<int> kInstances = vector<int>({1, 10, 25, 50});
        for (int it = 0; it < kInstances.size() ; it++) {
            int kMinusIter = kInstances[it];
            high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                knnValues[i] = kNN(imagesTest.centralized[i], imagesTrain.centralized, kMinusIter, imagesTrain);
                trueValues[i] = imagesTest.images[i].label;
                // cout << "la imagen: " << i << " del kNN: " << knnValues[i] << " del label: " << trueValues[i] << endl;
            }
            high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
            timeTracker.push_back(TimeEvent("KNN", duration_cast<milliseconds>( timekNNEnded - timekNNStarted ).count()));
            string knnOut = argv[2];
            knnOut += "KNNTest";
            getStats(knnValues, trueValues, knnOut, timeTracker, kMinusIter, alpha, gamma, kMayus);
            timeTracker.pop_back();
        }

        /////

    }
    input.close();
    output.close();
    return 0;
}
