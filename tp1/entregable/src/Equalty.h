#ifndef Equalty_h
#define Equalty_h

bool equalDouble(double a, double b, double tolerance = 0.000001) {
    return abs(a - b) < tolerance;
}

bool equalVector(vector<double> a, vector<double> b, double tolerance = 0.00001) {
    bool equal = true;
    int size = int(a.size());
    for (int i = 0; i < size; i++) {
        equal = equal && equalDouble(a[i], b[i]);
    }
    return equal;
}

#endif
