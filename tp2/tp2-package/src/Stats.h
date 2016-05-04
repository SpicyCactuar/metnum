#ifndef Stats_h
#define Stats_h

#include "Imports.h"
#include "Types.h"

void getStats(vector<int> &knnValues, vector<int> &trueValues, string &algorithm){
    string outputFile = algorithm + ".csv";
    ofstream output(outputFile, ios_base::app | ios_base::out);
    output << ", Precision, Recall" << endl;

    vector<int> truePositives(LABELS_QTY, 0);
    vector<int> falsePositives(LABELS_QTY, 0);
    vector<int> falseNegatives(LABELS_QTY, 0);
    for (int i = 0; i < knnValues.size(); ++i){
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
    double hitRate = sumPrecision / knnValues.size();
    output << "HitRate, " << hitRate << endl;
    double precisionAVG = sumPrecision / LABELS_QTY;
    output << "PrecisionAVG, " << precisionAVG << endl;
    double recallAVG = sumRecall / LABELS_QTY;
    output << "RecallAVG, " << recallAVG << endl;
    double f1Score = 2 * precisionAVG * recallAVG / (precisionAVG + recallAVG);
    output << "F1Score, " << f1Score << endl;

    output.close();
}

#endif
