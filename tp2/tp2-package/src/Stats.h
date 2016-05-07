#ifndef Stats_h
#define Stats_h

#include "Imports.h"
#include "Types.h"

void getStats(vector<int> &knnValues, vector<int> &trueValues, string &algorithm, vector<TimeEvent> &timeTracker, int kMinus, int alpha, int gamma, int kMayus){
    string outputFile = algorithm + ".csv";
    ofstream output(outputFile, ios_base::app | ios_base::out);
    output << "----,----,----" << endl;
    output << "----,Experiment,----" << endl;
    output << "k," << kMinus << endl;
    output << "alpha," << alpha << endl;
    output << "gamma," << gamma << endl;
    output << "K," << kMayus << endl;
    output << "----,Results,----" << endl;
    output << ", Precision, Recall" << endl;

    vector<int> truePositives(LABELS_QTY, 0);
    vector<int> falsePositives(LABELS_QTY, 0);
    vector<int> falseNegatives(LABELS_QTY, 0);
    Matrix confusion(LABELS_QTY, vector<double>(LABELS_QTY));
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
    double precisionAVG = sumPrecision / LABELS_QTY;
    output << "PrecisionAVG, " << precisionAVG << endl;
    double recallAVG = sumRecall / LABELS_QTY;
    output << "RecallAVG, " << recallAVG << endl;
    double f1Score = 2 * precisionAVG * recallAVG / (precisionAVG + recallAVG);
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
    for (int i = 0; i < timeTracker.size(); i++) {
        output << timeTracker[i].first << ", " << timeTracker[i].second << endl;
    }
    output << "----,----,----" << endl;

    output.close();
}

#endif
