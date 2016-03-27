#include "Algorithms.h"
#include "Print.h"
#include "Equalty.h"

#ifndef Tests_h
#define Tests_h

void test_findMaxUpper();
void test_makeUpperTriangular();
void test_gaussianElimination();
void test_CholeskyAndGaussianEqualSolution();

void runTests() {
    test_findMaxUpper();
    test_makeUpperTriangular();
    test_gaussianElimination();
    test_CholeskyAndGaussianEqualSolution();
}

void test_findMaxUpper() {

    matrix myMatrix {{10, 2, 3},
                     {4, 50, 6},
                     {7, 100, 9}};
    
    int upper = findMaxUpper(myMatrix, 1);

    bool passed = upper == 2;
    cout << "findMaxUpper passed: " << passed << endl;
}

bool test_isUpperTriangular(matrix mat) {
    bool isUpperTriangular = true;
    for (int i = 1; i < mat.size() ; i++) {
        for (int j = 0; j < i; j++) {
            isUpperTriangular = isUpperTriangular && mat[i][j] == 0;
        }
    }
    return isUpperTriangular;
}

void test_makeUpperTriangular() {

    vector<TeamRating> b_vec {1.0, 2.0, 3.0};


    matrix myMatrix {{10, 2,  3},
                     {4, 50,  6},
                     {7, 100, 9}};

    makeUpperTriangular(myMatrix, b_vec);

    bool passed = test_isUpperTriangular(myMatrix);
    cout << "makeUpperTriangular passed: " << passed << endl;

}

///Example from page 350 (Burden - Analisis Numerico)
void test_gaussianElimination() {

    b_vector b {-8, -20, -2, 4.0};

    matrix myMatrix {{1, -1, 2, -1},
                     {2, -2, 3, -3},
                     {1,  1, 1,  0},
                     {1, -1, 4,  3}};

    vector<TeamRating> res {0, 0, 0, 0};

    gaussianElimination(myMatrix, b, res);

    bool passed = equalDouble(res[0], -7.0) && equalDouble(res[1], 3.0) && equalDouble(res[2], 2.0) && equalDouble(res[3], 2.0);
    cout << "gaussianElimination passed: " << passed << endl;

}

void test_CholeskyAndGaussianEqualSolution() {

    b_vector b1 {-8, -20, -2, 4.0};
    b_vector b2 {-8, -20, -2, 4.0};

    matrix myMatrix1 {{4,   12,  -16},
                      {12,  37,  -43},
                      {-16, -43, 98 }};
    matrix myMatrix2 {{4,   12,  -16},
                      {12,  37,  -43},
                      {-16, -43, 98 }};

    vector<TeamRating> res1 {0, 0, 0, 0};
    vector<TeamRating> res2 {0, 0, 0, 0};

    gaussianElimination(myMatrix1, b1, res1);
    choleskyFactorization(myMatrix2, b2, res2);


    bool passed = equalVector(res1, res2);
    cout << "CholeskyAndGaussianEqualSolution passed: " << passed << endl;

}

#endif