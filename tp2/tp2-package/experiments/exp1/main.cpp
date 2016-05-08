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

using namespace chrono;

int main(int argc, char const *argv[]){
    if(argc != 3){
        cout << "Parameters should be: (i: input file), (o: output file)" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

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
        imagesTest.calculateCentralizedTest(imagesTrain.means, (int)imagesTrain.images.size());

        high_resolution_clock::time_point timeDefaultProcessEnded = high_resolution_clock::now();

        timeTracker.push_back(TimeEvent("Default Process", duration_cast<milliseconds>( timeDefaultProcessEnded - timeIterationStart ).count()));

        ///// knn /////

        vector<int> kMin = {1, 10, 25, 50, 100}, labelRes;
        vector<vector<int> > knnValues(kMin.size(), vector<int>(imagesTest.centralized.size()));
        vector<int> trueValues(imagesTest.centralized.size());

        double timeAcumulator = 0;
        for (int i = 0; i < imagesTest.centralized.size(); ++i){
            high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
            kNN(imagesTest.centralized[i], imagesTrain.centralized, kMin, labelRes, imagesTrain);
            high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
            timeAcumulator += duration_cast<milliseconds>( timekNNEnded - timekNNStarted ).count();

            trueValues[i] = imagesTest.images[i].label;
            for (int it = 0; it < labelRes.size(); it++) {
                knnValues[it][i] = labelRes[it];
            }

        }

        timeTracker.push_back(TimeEvent("KNN total", timeAcumulator));
        timeTracker.push_back(TimeEvent("KNN per image", timeAcumulator/imagesTest.centralized.size()));

        string knnOut = argv[2];
        knnOut += "KNNTest";
        for (int i = 0; i < kMin.size(); i++) {
            getStats(knnValues[i], trueValues, knnOut, timeTracker, kMin[i], 0, 0, kMayus);
        }

        ///// end knn /////

    }
    input.close();
    output.close();
    return 0;
}
