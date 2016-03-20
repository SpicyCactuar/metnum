#include <bits/stdc++.h>

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
int find_max(const matrix<T>& mat, int actual){
	int max = actual;
	for (int i = actual+1; i < mat.size(); ++i)
		if(abs(mat[actual][i]) > abs(mat[actual][actual]))
			max = i;
	return max;
}

template<typename T, typename Q>
void make_upper_triangular(matrix<T>& mat, vector<Q>& vec){
	for (int i = 0; i < mat.size(); ++i){
		// busco fila con el mayor elemento
		int i_max = find_max(mat, i);
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

template<typename T, typename Q>
void solve_upper_triangular(matrix<T>& mat, vector<Q>& vec, vector<pair<double, int> >& res){
	for (int i = mat.size()-1; i >= 0; --i){
		double partial_sum = 0.;
		for (int j = i+1; j < mat.size(); ++j)
			partial_sum += mat[i][j] * res[j].first;
		res[i] = pair<double, int>((vec[i].first - partial_sum) / mat[i][i], vec[i].second);
	}
}

template<typename T, typename Q>
void eliminacionGaussiana(matrix<T>& mat, vector<Q>& vec, vector<pair<double, int> >& res){
	// armo el sistema triangular superior
	make_upper_triangular(mat, vec);
	// resuelvo el sistema triangular superior
	solve_upper_triangular(mat, vec, res);
}
