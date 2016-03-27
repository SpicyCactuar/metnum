#ifndef Algorithms_h
#define Algorithms_h

#include "Imports.h"
#include "Types.h"

using namespace std;

// ---- Forward declarations ----

void makeUpperTriangular(matrix& mat, b_vector& b_vec);
void backSubstitution(matrix& mat, b_vector& b_vec, vector<TeamRating>& res);
void makeLowerTriangularCholesky(matrix& mat);
void forwardSubstitution(matrix& mat, b_vector& b_vec, vector<TeamRating>& res);

// ---- Winning Percentage ----

void winningPercentage(vector<MatchesRecord>& matchesRecords, vector<TeamRating>& res){
    for (int i = 0; i < matchesRecords.size(); ++i)
        res[i] = matchesRecords[i].won / matchesRecords[i].totalPlayed();
}

// ---- Gaussian Elimination ----

void gaussianElimination(matrix& mat, b_vector& b_vec, vector<TeamRating>& res){
    // armo la U
    makeUpperTriangular(mat, b_vec);
    // resuelvo Ux = b
    backSubstitution(mat, b_vec, res);
}

// ---- Cholesky Factorization ----

void choleskyFactorization(matrix& mat, b_vector& b_vec, vector<TeamRating>& res){
    // armo el sistema LL^t
    makeLowerTriangularCholesky(mat);
    vector<TeamRating> aux(mat.size());
    // resuelvo L * z = b
    forwardSubstitution(mat, b_vec, aux);
    // resuelvo L^t * x = z
    backSubstitution(mat, aux, res);
}

// ---- Matrix helpers ----

/// x  x  x  x  x
/// 0  x  x  x  x
/// 0  0 (1) x  x
/// 0  0 (5) x  x
/// 0  0 (3) x  x
///
/// Finds the higest number in the actual column starting from the i'th iteration.
/// In the example above, the algorithm would return 3 (4rd row)
int findMaxUpper(const matrix& mat, int actual) {
    int max = actual;
    for (int i = actual + 1; i < mat.size(); ++i)
        if(abs(mat[i][actual]) > abs(mat[max][actual]))
            max = i;
    return max;
}

/// x x x x
/// 0 x x x
/// 0 0 x x
/// 0 0 0 x
///
/// Makes matrix upper triangular as described above.
/// Used for Gaussian elimination.
void makeUpperTriangular(matrix& mat, b_vector& b_vec) {
    for (int i = 0; i < mat.size(); ++i){
        // Get the highest number int the column to minimize rounding errors.
        int i_max = findMaxUpper(mat, i);
        if(mat[i_max][i] != 0){
            //Swap matrix rows with the one with the highest number
            swap(mat[i_max], mat[i]);
            swap(b_vec[i_max], b_vec[i]);
            for (int j = i+1; j < mat.size(); ++j){
                double c = mat[j][i]/mat[i][i]; // the Quotient to make each row 0.
                mat[j][i] = 0.0;
                for (int k = i+1; k < mat.size(); ++k)
                    mat[j][k] -= c * mat[i][k];
                b_vec[j] -= c * b_vec[i];
            }
        } else {
            // The max value cannot be 0
            throw 20;
        }
    }
}

///pre: upper triangular matrix
///This method solves the equations when the input matrix is upper triangular.
///It returns the solution in a TeamRating vector.
void backSubstitution(matrix& mat, b_vector& b_vec, vector<TeamRating>& res) {
    int size = int(mat.size());
    for (int i = size - 1; i >= 0; --i) {
        double partialSum = 0.0;
        for (int j = i+1; j < mat.size(); ++j)
            partialSum += mat[i][j] * res[j];
        res[i] = (b_vec[i] - partialSum) / mat[i][i];
    }
}

/// ------ Cholesky algorithm. TODO: Check

void makeLowerTriangularCholesky(matrix& mat) {
    for (int i = 0; i < mat.size(); ++i){
        double partial_sum = 0.;
        for (int j = 0; j < i; ++j)
            partial_sum += pow(mat[i][j], 2);
        mat[i][i] = sqrt(mat[i][i] - partial_sum);
        for (int j = i+1; j < mat.size(); ++j){
            partial_sum = 0.;
            for (int k = 0; k < i; ++k)
                partial_sum += mat[i][k] * mat[j][k];
            mat[j][i] = (mat[j][i] - partial_sum) / mat[i][i];
            mat[i][j] = mat[j][i];
        }
    }
}

void forwardSubstitution(matrix& mat, b_vector& b_vec, vector<TeamRating>& res) {
    for (int i = 0; i < mat.size(); ++i){
        double partial_sum = 0.;
        for (int j = i-1; j >= 0; --j)
            partial_sum += mat[i][j] * res[j];
        res[i] = (b_vec[i] - partial_sum) / mat[i][i];
    }
}

#endif