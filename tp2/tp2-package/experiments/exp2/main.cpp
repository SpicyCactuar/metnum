//Compile: g++ -o tp main.cpp -std=c++11
//Run con tests provistos ./tp tests/test1.in .......
#include "Algorithms.h"
#include "Tests.h"
#include "Types.h"
#include "InputProcessor.h"
#include "Print.h"
#include "MatrixAlgorithms.h"
#include "Stats.h"

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
        //train or test input
        getline(input, line);

        vector<int> alphaValues = {1, 2};
//        vector<int> alphaValues = {1, 2, 3, 10, 25, 50, 100, 200};
        for (int alphaIt = 0; alphaIt < alphaValues.size(); alphaIt++) {

            stringstream lineStream(line);

            int alpha = alphaValues[alphaIt];
            int gamma = alphaValues[alphaIt];

            vector<TimeEvent> timeTracker;

            high_resolution_clock::time_point timeIterationStart = high_resolution_clock::now();
            DigitImages imagesTrain, imagesTest;
            Matrix eigenVectorsPCA(alpha, vector<double>(DEFAULT_IMAGE_SIZE));
            Matrix eigenVectorsPLSDA(gamma, vector<double>(DEFAULT_IMAGE_SIZE));
            vector<double> eigenValuesPCA(alpha);
            vector<double> eigenValuesPLSDA(gamma);
            int niterPCA = 1000;
            int niterPLSDA = 1000;

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

            timeTracker.push_back(TimeEvent("Default Process", duration_cast<milliseconds>( timeDefaultProcessEnded - timeIterationStart ).count()));
            timeTracker.push_back(TimeEvent("PCA", duration_cast<milliseconds>( timePCAEnded - timePCAStarted ).count()));
            timeTracker.push_back(TimeEvent("PLS", duration_cast<milliseconds>( timePLSEnded - timePCAEnded ).count()));

            ///// knn PCA /////
            vector<int> kMin = {1, 10, 25, 50, 100}, labelRes;
            vector<vector<int> > knnValuesPCA(kMin.size(), vector<int>(imagesTest.centralized.size()));
            vector<int> trueValuesPCA(imagesTest.centralized.size());

            high_resolution_clock::time_point timeTC_PCA_start = high_resolution_clock::now();
            TC tcTrainPCA, tcTestPCA;
            tcTrainPCA.init(eigenVectorsPCA, imagesTrain.centralized);
            tcTestPCA.init(eigenVectorsPCA, imagesTest.centralized);
            high_resolution_clock::time_point timeTC_PCA_end = high_resolution_clock::now();
            timeTracker.push_back(TimeEvent("TC PCA", duration_cast<milliseconds>( timeTC_PCA_end - timeTC_PCA_start ).count()));

            double timeAcumulator = 0;
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
                kNN(tcTestPCA.transformation[i], tcTrainPCA.transformation, kMin, labelRes, imagesTrain);
                high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
                timeAcumulator += duration_cast<milliseconds>( timekNNEnded - timekNNStarted ).count();

                trueValuesPCA[i] = imagesTest.images[i].label;
                for (int it = 0; it < labelRes.size(); it++) {
                    knnValuesPCA[it][i] = labelRes[it];
                }

            }

            timeTracker.push_back(TimeEvent("KNN PCA total", timeAcumulator));
            timeTracker.push_back(TimeEvent("KNN PCA per image", timeAcumulator/imagesTest.centralized.size()));


            string knnOut = argv[2];
            knnOut += "KNN-PCA-Test";
            for (int i = 0; i < kMin.size(); i++) {
                getStats(knnValuesPCA[i], trueValuesPCA, knnOut, timeTracker, kMin[i], alpha, gamma, kMayus);
            }
            
            ///// end knn PCA /////


            ///// knn PLS /////

            vector<vector<int> > knnValuesPLS(kMin.size(), vector<int>(imagesTest.centralized.size()));
            vector<int> trueValuesPLS(imagesTest.centralized.size());

            high_resolution_clock::time_point timeTC_PLS_start = high_resolution_clock::now();
            TC tcTrainPLSDA, tcTestPLSDA;
            tcTrainPLSDA.init(eigenVectorsPLSDA, imagesTrain.centralized);
            tcTestPLSDA.init(eigenVectorsPLSDA, imagesTest.centralized);
            high_resolution_clock::time_point timeTC_PLS_end = high_resolution_clock::now();
            timeTracker.push_back(TimeEvent("TC PLS", duration_cast<milliseconds>( timeTC_PLS_end - timeTC_PLS_start ).count()));

            timeAcumulator = 0;
            for (int i = 0; i < imagesTest.centralized.size(); ++i){
                high_resolution_clock::time_point timekNNStarted = high_resolution_clock::now();
                kNN(tcTestPLSDA.transformation[i], tcTrainPLSDA.transformation, kMin, labelRes, imagesTrain);
                high_resolution_clock::time_point timekNNEnded = high_resolution_clock::now();
                timeAcumulator += duration_cast<milliseconds>( timekNNEnded - timekNNStarted ).count();

                trueValuesPLS[i] = imagesTest.images[i].label;
                for (int it = 0; it < labelRes.size(); it++) {
                    knnValuesPLS[it][i] = labelRes[it];
                }

            }

            timeTracker.push_back(TimeEvent("KNN PLS total", timeAcumulator));
            timeTracker.push_back(TimeEvent("KNN PLS per image", timeAcumulator/imagesTest.centralized.size()));

            knnOut = argv[2];
            knnOut += "KNN-PLS-Test";
            for (int i = 0; i < kMin.size(); i++) {
                getStats(knnValuesPLS[i], trueValuesPLS, knnOut, timeTracker, kMin[i], alpha, gamma, kMayus);
            }
            
            ///// end knn PLS /////


        }
    }
    input.close();
    output.close();
    return 0;
}
