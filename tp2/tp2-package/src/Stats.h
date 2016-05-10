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
    output << ", Precision, Recall" << endl;

    vector<int> truePositives(LABELS_QTY, 0);
    vector<int> falsePositives(LABELS_QTY, 0);
    vector<int> falseNegatives(LABELS_QTY, 0);
    vector<vector<int>> confusion(LABELS_QTY, vector<int>(LABELS_QTY));
    for (int i = 0; i < knnValues.size(); ++i){
        confusion[trueValues[i]][knnValues[i]]++;
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
        output << i << ", ";
        output << precision << ", ";
        output << recall << endl;
    }
    double hitRate = sumHitRate / knnValues.size();
    output << "HitRate, " << hitRate << endl;
    double precision = sumPrecision / LABELS_QTY;
    output << "Precision, " << precision << endl;
    double recall = sumRecall / LABELS_QTY;
    output << "Recall, " << recall << endl;
    double f1Score = 2 * precision * recall / (precision + recall);
    output << "F1Score, " << f1Score << endl;

    output << "----,Confusion,----" << endl;
    output << ",Predicted" << endl;
    output << "Actual,0,1,2,3,4,5,6,7,8,9" << endl;
    for (int i = 0; i < LABELS_QTY; i++) {
        output << i << ",";
        for (int j = 0; j < LABELS_QTY; j++) {
            output << confusion[i][j] << ",";
        }
        output << endl;
    }

    output << "----,Time Results,----" << endl;
    for (auto it = timeTracker.begin(); it != timeTracker.end(); it++) {
        output << it->first << ", " << it->second << endl;
    }
    output << "----,----,----" << endl;


    ////// SET STATS

    stats.hitRate = hitRate;
    stats.precision = precision;
    stats.recall = recall;
    stats.f1Score = f1Score;
    stats.confusion = confusion;
    stats.defaultProcessTime = timeTracker[DEFAULT_PROCESS_TIME];
    stats.kNNTotalTime = timeTracker[KNN_TOTAL_TIME];
    stats.kNNPerImageTime = timeTracker[KNN_PER_IMAGE_TIME];
    stats.preprocessTime = timeTracker[PREPROCESS_DIMENSION_TIME];
    stats.tcTime = timeTracker[TC_TIME];


    output.close();
}

template <typename T>
double getAverage(vector<T> vec) {
    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum/vec.size();
}

template <typename T>
double getSTDev(vector<T> vec) {
    double sum = 0;
    double avg = getAverage(vec);
    for (int i = 0; i < vec.size(); i++) {
        sum += pow(vec[i] - avg, 2);
    }
    return sqrt(sum/vec.size());
}

void processStatsAnalysis(vector<vector<AwesomeStatistic>> &kMayusStats, int alpha, int gamma, string algorithm) {

    //[K][k]

    string outputName = "Analysis-" + algorithm + ".csv";
    ofstream output(outputName);

    double hitRateAvg, hitRateSTD;
    double precisionAvg, precisionSTD;
    double recallAvg, recallSTD;
    double f1ScoreAvg, f1ScoreSTD;
    vector<vector<int>> confusionSum(LABELS_QTY, vector<int>(LABELS_QTY, 0));
    double defaultProcessTimeAvg, defaultProcessTimeSTD;
    double kNNTotalTimeAvg, kNNTotalTimeSTD;
    double kNNPerImageTimeAvg, kNNPerImageTimeSTD;
    double preprocessTimeAvg, preprocessTimeSTD;
    double tcTimeAvg, tcTimeSTD;

    vector<double> vechitRate(kMayusStats.size());
    vector<double> vecprecision(kMayusStats.size());
    vector<double> vecrecall(kMayusStats.size());
    vector<double> vecf1Score(kMayusStats.size());
    vector<double> vecdefaultProcessTime(kMayusStats.size());
    vector<double> veckNNTotalTime(kMayusStats.size());
    vector<double> veckNNPerImageTime(kMayusStats.size());
    vector<double> vecpreprocessTime(kMayusStats.size());
    vector<double> vectcTime(kMayusStats.size());

    for (int kMinus = 0; kMinus < kMayusStats[0].size(); kMinus++) {

        for (int kMayus = 0; kMayus < kMayusStats.size(); kMayus++) {

            vechitRate[kMayus] = kMayusStats[kMayus][kMinus].hitRate;
            vecprecision[kMayus] = kMayusStats[kMayus][kMinus].precision;
            vecrecall[kMayus] = kMayusStats[kMayus][kMinus].recall;
            vecf1Score[kMayus] = kMayusStats[kMayus][kMinus].f1Score;
            vecdefaultProcessTime[kMayus] = kMayusStats[kMayus][kMinus].defaultProcessTime;
            veckNNTotalTime[kMayus] = kMayusStats[kMayus][kMinus].kNNTotalTime;
            veckNNPerImageTime[kMayus] = kMayusStats[kMayus][kMinus].kNNPerImageTime;
            vecpreprocessTime[kMayus] = kMayusStats[kMayus][kMinus].preprocessTime;
            vectcTime[kMayus] = kMayusStats[kMayus][kMinus].tcTime;
            for (int i = 0; i < LABELS_QTY; ++i) {
                for (int j = 0; j < LABELS_QTY; ++j) {
                    confusionSum[i][j] += kMayusStats[kMayus][kMinus].confusion[i][j];
                }
            }
        }

        hitRateAvg = getAverage(vechitRate);
        hitRateSTD = getSTDev(vechitRate);

        precisionAvg = getAverage(vecprecision);
        precisionSTD = getSTDev(vecprecision);

        recallAvg = getAverage(vecrecall);
        recallSTD = getSTDev(vecrecall);

        f1ScoreAvg = getAverage(vecf1Score);
        f1ScoreSTD = getSTDev(vecf1Score);

        defaultProcessTimeAvg = getAverage(vecdefaultProcessTime);
        defaultProcessTimeSTD = getSTDev(vecdefaultProcessTime);

        kNNTotalTimeAvg = getAverage(veckNNTotalTime);
        kNNTotalTimeSTD = getSTDev(veckNNTotalTime);

        kNNPerImageTimeAvg = getAverage(veckNNPerImageTime);
        kNNPerImageTimeSTD = getSTDev(veckNNPerImageTime);

        preprocessTimeAvg = getAverage(vecpreprocessTime);
        preprocessTimeSTD = getSTDev(vecpreprocessTime);

        tcTimeAvg = getAverage(vectcTime);
        tcTimeSTD = getSTDev(vectcTime);



        output << "k," << kMinus << endl;
        output << "alpha," << alpha << endl;
        output << "gamma," << gamma << endl;

        output << "Hit Rate Avg," << hitRateAvg << endl;
        output << "Hit Rate STD," << hitRateSTD << endl;

        output << "Precision Avg," << precisionAvg << endl;
        output << "Precision STD," << precisionSTD << endl;

        output << "Recall Avg," << recallAvg << endl;
        output << "Recall STD," << recallSTD << endl;

        output << "F1 Score Avg," << f1ScoreAvg << endl;
        output << "F1 Score STD," << f1ScoreSTD << endl;

        output << "Default Process Time Avg," << defaultProcessTimeAvg << endl;
        output << "Default Process Time STD," << defaultProcessTimeSTD << endl;

        output << "KNN Total Time Avg," << kNNTotalTimeAvg << endl;
        output << "KNN Total Time STD," << kNNTotalTimeSTD << endl;

        output << "KNN Per Image Time Avg," << kNNPerImageTimeAvg << endl;
        output << "KNN Per Image Time STD," << kNNPerImageTimeSTD << endl;

        output << "Preprocess Dimension Time Avg," << preprocessTimeAvg << endl;
        output << "Preprocess Dimension Time STD," << preprocessTimeSTD << endl;

        output << "TC Time Avg," << tcTimeAvg << endl;
        output << "TC Time STD," << tcTimeSTD << endl;

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
