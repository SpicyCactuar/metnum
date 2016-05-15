//Compile: g++ -o2 tp main.cpp -std=c++11
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

    vector<int> alphaValues = {10, 50, 100, 300};
    vector<int> gammaValues = {4, 8, 12, 16};

//    vector<int> alphaValues = {5, 10, 25, 50, 75, 100, 200, 300};
//    vector<int> gammaValues = {2, 4, 6, 8, 10, 12, 14, 16};
    vector<vector<vector<AwesomeStatistic>>> alphakMayusStatsPCA(alphaValues.size());
    vector<vector<vector<AwesomeStatistic>>> gammakMayusStatsPLS(gammaValues.size());

    for (int iter = 0; iter < kMayus; ++iter){
        //train or test input
        getline(input, line);

        for (int alphaIt = 0; alphaIt < alphaValues.size(); alphaIt++) {
            stringstream lineStream(line);

            int alpha = alphaValues[alphaIt];
            int gamma = gammaValues[alphaIt];

            map<string, int> timeTrackerPCA;
            map<string, int> timeTrackerPLS;

            high_resolution_clock::time_point timeIterationStart = high_resolution_clock::now();
            DigitImages imagesTrain, imagesTest;
            Matrix eigenVectorsPCA(alpha, vector<double>(DEFAULT_IMAGE_SIZE));
            Matrix eigenVectorsPLSDA(gamma, vector<double>(DEFAULT_IMAGE_SIZE));
            vector<double> eigenValuesPCA(alpha);
            vector<double> eigenValuesPLSDA(gamma);
            int niterPCA = 1200;
            int niterPLSDA = 1200;

            populateDigitImages(imagesTrain, imagesTest, inFileDir, lineStream);
            imagesTrain.getMeans();
            imagesTrain.calculateCentralized();
            imagesTrain.calculateCovariances();
            imagesTrain.calculateMeansLabels();
            imagesTest.calculateCentralizedTest(imagesTrain.means, (int)imagesTrain.images.size());
            high_resolution_clock::time_point timeDefaultProcessEnded = high_resolution_clock::now();

            high_resolution_clock::time_point timePCAStarted = high_resolution_clock::now();
            PCA(imagesTrain.covariances, eigenVectorsPCA, eigenValuesPCA, alpha, niterPCA);
            high_resolution_clock::time_point timePCAEnded = high_resolution_clock::now();
            PLSDA(imagesTrain, eigenVectorsPLSDA, eigenValuesPLSDA, gamma, niterPLSDA);
            high_resolution_clock::time_point timePLSEnded = high_resolution_clock::now();

            timeTrackerPCA[DEFAULT_PROCESS_TIME] = (int)duration_cast<milliseconds>(timeDefaultProcessEnded - timeIterationStart).count();
            timeTrackerPCA[PREPROCESS_DIMENSION_TIME] = (int)duration_cast<milliseconds>(timePCAEnded - timePCAStarted).count();

            timeTrackerPLS[DEFAULT_PROCESS_TIME] = (int)duration_cast<milliseconds>(timeDefaultProcessEnded - timeIterationStart).count();
            timeTrackerPLS[PREPROCESS_DIMENSION_TIME] = (int)duration_cast<milliseconds>(timePLSEnded - timePCAEnded).count();

            ///// knn PCA /////
            vector<int> kMin = {1, 2, 3, 4, 5, 10, 15, 20, 25, 50, 75, 100, 150, 200}, labelRes;
            vector<vector<int>> knnValuesPCA(kMin.size(), vector<int>(imagesTest.centralized.size()));
            vector<int> trueValuesPCA(imagesTest.centralized.size());

            high_resolution_clock::time_point timeTC_PCA_start = high_resolution_clock::now();
            TC tcTrainPCA, tcTestPCA;
            tcTrainPCA.init(eigenVectorsPCA, imagesTrain.centralized);
            tcTestPCA.init(eigenVectorsPCA, imagesTest.centralized);
            high_resolution_clock::time_point timeTC_PCA_end = high_resolution_clock::now();
            timeTrackerPCA[TC_TIME] = (int)duration_cast<milliseconds>(timeTC_PCA_end - timeTC_PCA_start).count();

            double timeAcumulator = 0;
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
                kNN(tcTestPCA.transformation[i], tcTrainPCA.transformation, kMin, labelRes, imagesTrain.labels);
                high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
                timeAcumulator += duration_cast<milliseconds>(timekNNEnded - timekNNStarted).count();

                trueValuesPCA[i] = imagesTest.labels[i];
                for (int it = 0; it < labelRes.size(); it++)
                    knnValuesPCA[it][i] = labelRes[it];
            }
            timeTrackerPCA[KNN_TOTAL_TIME] = timeAcumulator;
            timeTrackerPCA[KNN_PER_IMAGE_TIME] = timeAcumulator/imagesTest.centralized.size();

            string knnOut = argv[2];
            knnOut += + "KNN-PCA-Test-(" + to_string(kMayus) + "-Partitions)";
            vector<AwesomeStatistic> kMinusStatsPCA(kMin.size());
            for (int i = 0; i < kMin.size(); i++)
                getStats(knnValuesPCA[i], trueValuesPCA, knnOut, timeTrackerPCA, kMin[i], alpha, gamma, kMayus, iter, kMinusStatsPCA[i]);
            ///// end knn PCA /////
            alphakMayusStatsPCA[alphaIt].push_back(kMinusStatsPCA);

            ///// knn PLS /////
            vector<vector<int>> knnValuesPLS(kMin.size(), vector<int>(imagesTest.centralized.size()));
            vector<int> trueValuesPLS(imagesTest.centralized.size());

            high_resolution_clock::time_point timeTC_PLS_start = high_resolution_clock::now();
            TC tcTrainPLSDA, tcTestPLSDA;
            tcTrainPLSDA.init(eigenVectorsPLSDA, imagesTrain.centralized);
            tcTestPLSDA.init(eigenVectorsPLSDA, imagesTest.centralized);
            high_resolution_clock::time_point timeTC_PLS_end = high_resolution_clock::now();
            timeTrackerPLS[TC_TIME] = (int)duration_cast<milliseconds>(timeTC_PLS_end - timeTC_PLS_start).count();

            timeAcumulator = 0;
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
                kNN(tcTestPLSDA.transformation[i], tcTrainPLSDA.transformation, kMin, labelRes, imagesTrain.labels);
                high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
                timeAcumulator += duration_cast<milliseconds>(timekNNEnded - timekNNStarted).count();

                trueValuesPLS[i] = imagesTest.labels[i];
                for (int it = 0; it < labelRes.size(); it++)
                    knnValuesPLS[it][i] = labelRes[it];
            }
            timeTrackerPLS[KNN_TOTAL_TIME] = timeAcumulator;
            timeTrackerPLS[KNN_PER_IMAGE_TIME] = timeAcumulator/imagesTest.centralized.size();

            knnOut = argv[2];
            knnOut += + "KNN-PLS-Test-(" + to_string(kMayus) + "-Partitions)";
            vector<AwesomeStatistic> kMinusStatsPLS(kMin.size());
            for (int i = 0; i < kMin.size(); i++)
                getStats(knnValuesPLS[i], trueValuesPLS, knnOut, timeTrackerPLS, kMin[i], alpha, gamma, kMayus, iter, kMinusStatsPLS[i]);
            ///// end knn PLS /////
            gammakMayusStatsPLS[alphaIt].push_back(kMinusStatsPLS);
        }
    }

    for (int alphaIt = 0; alphaIt < alphaValues.size(); ++alphaIt){
        string analysisNamePCA = "PCA-(" + to_string(kMayus) + "-Partitions)-alpha-" + to_string(alphaValues[alphaIt]);
        string analysisNamePLS = "PLS-(" + to_string(kMayus) + "-Partitions)-gamma-" + to_string(gammaValues[alphaIt]);
        processStatsAnalysis(alphakMayusStatsPCA[alphaIt], analysisNamePCA, alphaValues[alphaIt]);
        processStatsAnalysis(gammakMayusStatsPLS[alphaIt], analysisNamePLS, gammaValues[alphaIt]);
    }

    input.close();
    return 0;
}
