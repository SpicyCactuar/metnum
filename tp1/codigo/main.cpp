//COMPILAR! g++ -o main main.cpp -std=c++11
#include "main.h"

int main(int argc, char const *argv[]){
	// si no me pasan los 4 parametros (argc es implicito) esta todo mal
	if(argc != 4){
		cout << "Falta algun parametro, son: input file, output file, algoritmo (0: CMM-EG, 1: CMM-CL, 2:WP)" << endl;
		return 0;
	}

	// leo el archivo de entrada
	ifstream input(argv[1]);
	int n, k, local, local_score, away, away_score;
	string temp;
	input >> n >> k;
	// ganados perdidos
	vector<pair<double, double> > winAndLose(n, pair<double, double>(0., 0.));
	matrix<double> scores(n, vector<double>(n, 0.));
	for(int i = 0; i < k; i++){
		input >> temp >> local >> local_score >> away >> away_score;
		local -= 1;
		away -= 1;
		if(local_score > away_score){
			winAndLose[local].first += 1;
			winAndLose[away].second += 1;
		} else {
			winAndLose[local].second += 1;
			winAndLose[away].first += 1;
		}
		scores[local][away] += 1;
		scores[away][local] += 1;
	}
	input.close();

	// armo la C
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if(j==i)
				scores[i][j] += winAndLose[i].first + winAndLose[i].second + 2;
			else
				scores[i][j] *= -1;
		}
	}

	// armo el b
	vector<pair<double, int> >b_vector(n);
	for (int i = 0; i < n; ++i)
		b_vector[i] = pair<double, int>(1 + (winAndLose[i].first - winAndLose[i].second) / 2, i);

	string method = argv[3];
	if(method == "0"){
		vector<pair<double, int> > res = eliminacionGaussiana(scores, b_vector);
		ofstream output(argv[2]);
		sort(res.begin(), res.end(), pairCompare);
		printFile(res, output);
		output.close();
	} else if(method == "1"){
		cout << "CMM-CL" << endl;
	} else	if(method == "2"){
		cout << "WP" << endl;
	} else {
		cout << "Cualquiera" << endl;
	}
	return 0;
}
