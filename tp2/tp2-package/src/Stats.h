#ifndef Stats_h
#define Stats_h

#include "Imports.h"
#include "Types.h"

void getStats(vector<int> &knnValues, vector<int> &trueValues, string &algorithm, map<string, int> &timeTracker, int kMinus, int alpha, int gamma, int kMayus, int kActual, AwesomeStatistic &stats){
    string outputFile = algorithm + ".csv";
    ofstream output(outputFile, ios_base::app | ios_base::out);
    output << "----,----,----" << endl;
    output << "----,Experiment,----" << endl;
    output << "k," << kMinus << endl;
    output << "alpha," << alpha << endl;
    output << "gamma," << gamma << endl;
    output << "K total," << kMayus << endl;
    output << "K actual," << kActual << endl;
    output << "----,Results,----" << endl;

    vector<int> truePositives(LABELS_QTY, 0);
    vector<int> falsePositives(LABELS_QTY, 0);
    vector<int> falseNegatives(LABELS_QTY, 0);
    stats.confusion = vector<vector<int>>(LABELS_QTY, vector<int>(LABELS_QTY, 0));
    for (int i = 0; i < knnValues.size(); ++i){
        stats.confusion[trueValues[i]][knnValues[i]]++;
        if(knnValues[i] == trueValues[i])
            truePositives[knnValues[i]]++;
        else{
            falsePositives[knnValues[i]]++;
            falseNegatives[trueValues[i]]++;
        }
    }
    double sumHitRate = 0, sumPrecision = 0, sumRecall = 0;
    for (int i = 0; i < LABELS_QTY; ++i){
        double totalPrecision = truePositives[i] + falsePositives[i];
        double totalRecall = truePositives[i] + falseNegatives[i];
        double precision = truePositives[i] / totalPrecision;
        double recall = truePositives[i] / totalRecall;
        sumHitRate += truePositives[i];
        sumPrecision += precision;
        sumRecall += recall;
    }
    stats.hitRate = sumHitRate / knnValues.size();
    output << "HitRate, " << stats.hitRate << endl;
    stats.precision = sumPrecision / LABELS_QTY;
    output << "Precision, " << stats.precision << endl;
    stats.recall = sumRecall / LABELS_QTY;
    output << "Recall, " << stats.recall << endl;
    stats.f1Score = 2 * stats.precision * stats.recall / (stats.precision + stats.recall);
    output << "F1Score, " << stats.f1Score << endl;

    output << "----,Confusion,----" << endl;
    output << "Actual\\Predicted,0,1,2,3,4,5,6,7,8,9" << endl;
    for (int i = 0; i < LABELS_QTY; i++) {
        output << i << ",";
        for (int j = 0; j < LABELS_QTY; j++)
            output << stats.confusion[i][j] << ",";
        output << endl;
    }

    output << "----,Time Results,----" << endl;
    for (auto it = timeTracker.begin(); it != timeTracker.end(); it++)
        output << it->first << ", " << it->second << endl;
    output << "----,----,----" << endl;

    ////// SET STATS
    stats.defaultProcessTime = timeTracker[DEFAULT_PROCESS_TIME];
    stats.kNNTotalTime = timeTracker[KNN_TOTAL_TIME];
    stats.kNNPerImageTime = timeTracker[KNN_PER_IMAGE_TIME];
    stats.preprocessTime = timeTracker[PREPROCESS_DIMENSION_TIME];
    stats.tcTime = timeTracker[TC_TIME];
    stats.k = kMinus;
    output.close();
}

template <typename T>
double getAverage(vector<T> vec) {
    double sum = 0;
    for (int i = 0; i < vec.size(); i++)
        sum += vec[i];
    return sum/vec.size();
}

template <typename T>
double getSTDev(vector<T> vec) {
    double sum = 0, avg = getAverage(vec);
    for (int i = 0; i < vec.size(); i++)
        sum += pow(vec[i] - avg, 2);
    return sqrt(sum/vec.size());
}

void processStatsAnalysis(vector<vector<AwesomeStatistic>> &kMayusStats, string &algorithm, int alpha = 0) {
    //[K][k]
    string outputName = "Analysis-" + algorithm + ".csv";
    ofstream output(outputName);

    vector<double> vecHitRate(kMayusStats.size());
    vector<double> vecPrecision(kMayusStats.size());
    vector<double> vecRecall(kMayusStats.size());
    vector<double> vecF1Score(kMayusStats.size());
    vector<double> vecDefaultProcessTime(kMayusStats.size());
    vector<double> vecKNNTotalTime(kMayusStats.size());
    vector<double> vecKNNPerImageTime(kMayusStats.size());
    vector<double> vecPreprocessTime(kMayusStats.size());
    vector<double> vecTCTime(kMayusStats.size());

    for (int kMinus = 0; kMinus < kMayusStats[0].size(); kMinus++) {
        vector<vector<int>> confusionSum(LABELS_QTY, vector<int>(LABELS_QTY, 0));
        for (int kMayus = 0; kMayus < kMayusStats.size(); kMayus++) {
            vecHitRate[kMayus] = kMayusStats[kMayus][kMinus].hitRate;
            vecPrecision[kMayus] = kMayusStats[kMayus][kMinus].precision;
            vecRecall[kMayus] = kMayusStats[kMayus][kMinus].recall;
            vecF1Score[kMayus] = kMayusStats[kMayus][kMinus].f1Score;
            vecDefaultProcessTime[kMayus] = kMayusStats[kMayus][kMinus].defaultProcessTime;
            vecKNNTotalTime[kMayus] = kMayusStats[kMayus][kMinus].kNNTotalTime;
            vecKNNPerImageTime[kMayus] = kMayusStats[kMayus][kMinus].kNNPerImageTime;
            vecPreprocessTime[kMayus] = kMayusStats[kMayus][kMinus].preprocessTime;
            vecTCTime[kMayus] = kMayusStats[kMayus][kMinus].tcTime;
            for (int i = 0; i < LABELS_QTY; ++i) {
                for (int j = 0; j < LABELS_QTY; ++j) {
                    confusionSum[i][j] += kMayusStats[kMayus][kMinus].confusion[i][j];
                }
            }
        }

        output << "k," << kMayusStats[0][kMinus].k << endl;
        output << "alpha/gamma," << alpha << endl;

        output << "Hit Rate Avg," << getAverage(vecHitRate) << endl;
        output << "Hit Rate STD," << getSTDev(vecHitRate) << endl;

        output << "Precision Avg," << getAverage(vecPrecision) << endl;
        output << "Precision STD," << getSTDev(vecPrecision) << endl;

        output << "Recall Avg," << getAverage(vecRecall) << endl;
        output << "Recall STD," << getSTDev(vecRecall) << endl;

        output << "F1 Score Avg," << getAverage(vecF1Score) << endl;
        output << "F1 Score STD," << getSTDev(vecF1Score) << endl;

        output << "Default Process Time Avg," << getAverage(vecDefaultProcessTime) << endl;
        output << "Default Process Time STD," << getSTDev(vecDefaultProcessTime) << endl;

        output << "KNN Total Time Avg," << getAverage(vecKNNTotalTime) << endl;
        output << "KNN Total Time STD," << getSTDev(vecKNNTotalTime) << endl;

        output << "KNN Per Image Time Avg," << getAverage(vecKNNPerImageTime) << endl;
        output << "KNN Per Image Time STD," << getSTDev(vecKNNPerImageTime) << endl;

        output << "Preprocess Dimension Time Avg," << getAverage(vecPreprocessTime) << endl;
        output << "Preprocess Dimension Time STD," << getSTDev(vecPreprocessTime) << endl;

        output << "TC Time Avg," << getAverage(vecTCTime) << endl;
        output << "TC Time STD," << getSTDev(vecTCTime) << endl;

        output << "----,Confusion,----" << endl;
        output << "Actual\\Predicted,0,1,2,3,4,5,6,7,8,9" << endl;

        for (int i = 0; i < LABELS_QTY; i++) {
            output << i << ",";
            for (int j = 0; j < LABELS_QTY; j++) {
                output << confusionSum[i][j] << ",";
            }
            output << endl;
        }
        output << "----,-----,----" << endl;
        output << "----,-----,----" << endl;
    }
    output.close();
}

#endif
