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

    string inFileDir, line;
    int kMayus;

    input >> inFileDir >> kMayus;
    // skip the rest of the first line
    getline(input, line);

    vector<vector<AwesomeStatistic>> kMayusStats;

    for (int iter = 0; iter < kMayus; ++iter){
        map<string, int> timeTracker;
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

        timeTracker[DEFAULT_PROCESS_TIME] = (int)duration_cast<milliseconds>(timeDefaultProcessEnded - timeIterationStart).count();

        ///// knn /////

        vector<int> kMin = {1, 2, 3, 5, 10, 25, 50, 100, 200}, labelRes;
        vector<vector<int> > knnValues(kMin.size(), vector<int>(imagesTest.centralized.size()));
        vector<int> trueValues(imagesTest.centralized.size());

        double timeAcumulator = 0;
        for (int i = 0; i < imagesTest.centralized.size(); ++i){
            high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
            kNN(imagesTest.centralized[i], imagesTrain.centralized, kMin, labelRes, imagesTrain);
            high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
            timeAcumulator += duration_cast<milliseconds>( timekNNEnded - timekNNStarted ).count();

            trueValues[i] = imagesTest.images[i].label;
            for (int it = 0; it < labelRes.size(); it++)
                knnValues[it][i] = labelRes[it];
        }

        timeTracker[KNN_TOTAL_TIME] = timeAcumulator;
        timeTracker[KNN_PER_IMAGE_TIME] = timeAcumulator/imagesTest.centralized.size();

        string knnOut = argv[2];
        knnOut += + "KNNTest-(" + to_string(kMayus) + "-Partitions)";

        vector<AwesomeStatistic> kMinusStats(kMin.size());
        for (int i = 0; i < kMin.size(); i++)
            getStats(knnValues[i], trueValues, knnOut, timeTracker, kMin[i], 0, 0, kMayus, iter, kMinusStats[i]);
        ///// end knn /////
        kMayusStats.push_back(kMinusStats);
    }
    string analysisName = "KNN-(" + to_string(kMayus) + "-Partitions)";
    processStatsAnalysis(kMayusStats, analysisName);

    input.close();
    return 0;
}
