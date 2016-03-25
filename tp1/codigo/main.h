#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
using matrix = vector<vector<T> >;

template<typename T, typename Q>
ostream& operator<<(ostream& os, const pair<T, Q>& p ){
    return os << "(" << p.first << " " << p.second << ")";
}

bool pairCompare(const pair<double, int>& first, const pair<double, int>& second) {
    return first.second < second.second;
}

template<typename T>
void printVector(const vector<T>& vec){
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void printFile(const vector<pair<double, int> >& vec, ostream& os){
    for (int i = 0; i < vec.size(); ++i){
        // os << vec[i].second << " " << vec[i].first << endl;
        os << vec[i].first << endl;
    }
}

template<typename T>
void printMatrix(const matrix<T>& mat){
    for (int i = 0; i < mat.size(); ++i)
        printVector(mat[i]);
}

template<typename T>
int find_max_upper(const matrix<T>& mat, int actual){
    int max = actual;
    for (int i = actual+1; i < mat.size(); ++i)
        if(abs(mat[actual][i]) > abs(mat[actual][max]))
            max = i;
    return max;
}

template<typename T, typename Q>
void make_upper_triangular(matrix<T>& mat, vector<Q>& vec){
    for (int i = 0; i < mat.size(); ++i){
        // busco fila con el mayor elemento
        int i_max = find_max_upper(mat, i);
        // si tiene 0 avanzo (creo que no es necesario por como es la matriz, pero nunca esta demas)
        // si algun equipo no juega, tal vez se chotee feo
        if(mat[i_max][i] != 0){
            // intercambio la columna actual por la del maximo, en el b tambien (es una columna mas de C)
            swap(mat[i_max], mat[i]);
            swap(vec[i_max], vec[i]);
            for (int j = i+1; j < mat.size(); ++j){
                // magia para generar la matriz triangular superior
                double c = mat[j][i]/mat[i][i];
                mat[j][i] = 0;
                for (int k = i+1; k < mat.size(); ++k)
                    mat[j][k] -= c * mat[i][k];
                vec[j].first -= c * vec[i].first;
            }
        }
    }
}

template<typename T>
void make_lower_triangular_cholesky(matrix<T>& mat){
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

template<typename T, typename Q>
void back_substitution(matrix<T>& mat, vector<Q>& vec, vector<Q>& res){
    for (int i = int(mat.size()-1); i >= 0; --i){
        double partial_sum = 0.;
        for (int j = i+1; j < mat.size(); ++j)
            partial_sum += mat[i][j] * res[j].first;
        res[i] = Q((vec[i].first - partial_sum) / mat[i][i], vec[i].second);
    }
}

template<typename T, typename Q>
void forward_substitution(matrix<T>& mat, vector<Q>& vec, vector<Q>& res){
    for (int i = 0; i < mat.size(); ++i){
        double partial_sum = 0.;
        for (int j = i-1; j >= 0; --j)
            partial_sum += mat[i][j] * res[j].first;
        res[i] = Q((vec[i].first - partial_sum) / mat[i][i], vec[i].second);
    }
}

template<typename T, typename Q>
void gaussianElimination(matrix<T>& mat, vector<Q>& vec, vector<Q>& res){
    // armo la U
    make_upper_triangular(mat, vec);
    // resuelvo Ux = b
    back_substitution(mat, vec, res);
}

template<typename T, typename Q>
void choleskyFactorization(matrix<T>& mat, vector<Q>& vec, vector<Q>& res){
    // armo el sistema LL^t
    make_lower_triangular_cholesky(mat);
    vector<Q> aux(mat.size());
    // resuelvo L * z = b
    forward_substitution(mat, vec, aux);
    // resuelvo L^t * x = z
    back_substitution(mat, aux, res);
}

template<typename T, typename Q>
void winningPercentage(vector<T>& vec, vector<Q>& res){
    for (int i = 0; i < vec.size(); ++i)
        res[i] = Q(vec[i].first / (vec[i].first + vec[i].second), i);
}

