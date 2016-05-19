#ifndef MatrixAlgorithms_h
#define MatrixAlgorithms_h

using Matrix = vector<vector<double>>;

void randomVectorInitialize(vector<double> &vec){
    for (int i = 0; i < vec.size(); ++i){
        srand((unsigned) time(NULL));
        vec[i] = (rand() % 100000) + 1; // ver que valor tiene que ir aca, tengo entendido que un cero rompe
    }
}

//x - y = z
void substractVecVec(vector<double> &vec1, vector<double> &vec2, vector<double> &res){
    for (int i = 0; i < res.size(); ++i)
        res[i] = vec1[i] - vec2[i];
}

void substractMatMat(Matrix &mat1, Matrix &mat2, Matrix &matOut){
    for (int i = 0; i < matOut.size(); ++i)
        for (int j = 0; j < matOut[i].size(); ++j)
            matOut[i][j] = mat1[i][j] - mat2[i][j];
}

//x^ty = # product
double dotProduct(vector<double> &vec1, vector<double> &vec2){
    double sum = 0;
    for (int i = 0; i < vec1.size(); ++i)
        sum += vec1[i] * vec2[i];
    return sum;
}

//xy^t = A product
void productColRow(vector<double> &vec1, vector<double> &vec2, Matrix &mat, double lambda = 1){
    for (int i = 0; i < vec1.size(); ++i){
        for (int j = 0; j < vec2.size(); ++j)
            mat[i][j] = vec1[i] * vec2[j] * lambda;
    }
}

//xA = y product
//REQUIERE *** NON EMPTY MATRIX ***
void productVectorMatrix(vector<double> &vecIn, Matrix &mat, vector<double> &vecOut){
    for (int i = 0; i < mat[0].size(); ++i){
        double sum = 0;
        for (int j = 0; j < mat.size(); ++j)
            sum += mat[j][i] * vecIn[j];
        vecOut[i] = sum;
    }
}

//Ax = y product
void productMatrixVector(Matrix &mat, vector<double> &vecIn, vector<double> &vecOut){
    for (int i = 0; i < mat.size(); ++i){
        double sum = 0;
        for (int j = 0; j < vecIn.size(); ++j)
            sum += mat[i][j] * vecIn[j];
        vecOut[i] = sum;
    }
}

//AB = C product
//REQUIERE *** NON EMPTY MATRIX ***
void productMatMat(Matrix &mat1, Matrix &mat2, Matrix &matOut, bool mat1Traspose = false, bool mat2Traspose = false, double lambda = 1){
    //AtBt = C
    if(mat1Traspose && mat2Traspose){/* Not needed for now */}
    //AtB = C
    else if(mat1Traspose){
        for (int i = 0; i < mat1[0].size(); ++i){
            for (int j = 0; j < mat2[0].size(); ++j){
                double sum = 0;
                for (int k = 0; k < mat1.size(); ++k){
                    sum += mat1[k][i] * mat2[k][j];
                }
                matOut[i][j] = sum * lambda;
            }
        }
    }
    //ABt = C
    else if(mat2Traspose){/* Not needed for now */}
    //AB = C
    else{
        for (int i = 0; i < mat1.size(); ++i){
            for (int j = 0; j < mat2[0].size(); ++j){
                double sum = 0;
                for (int k = 0; k < mat2.size(); ++k){
                    sum += mat1[i][k] * mat2[k][j];
                }
                matOut[i][j] = sum * lambda;
            }
        }
    }
}

//XXt = Y
void productMatMatSimetric(Matrix &matIn, Matrix &matOut, double lambda = 1){
    for (int i = 0; i < matIn.size(); ++i){
        for (int j = i; j < matIn.size(); ++j){
            double sum = 0;
            for (int k = 0; k < matIn[i].size(); ++k){
                sum += matIn[i][k] * matIn[j][k];
            }
            matOut[i][j] = sum;
            matOut[j][i] = sum;
        }
    }
}

#endif
