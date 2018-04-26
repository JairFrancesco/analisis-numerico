#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

typedef vector<vector<double> > matriz;

void imprimirMatriz(matriz A){
    cout<<"-------------------------------------"<<endl;
    cout<<endl;

    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            cout << A[i][j] << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}

vector<double> sust_regresiva(matriz A, vector<double> b)
{
    int n = A.size();
    vector<double> X(n, 0);
    for (int i = n-1; i >= 0; i--)
    {
        double s = 0;
        for (int j = i+1; j < n; j++)
            s += A[i][j]*X[j];
        X[i] = (b[i]-s)/A[i][i];
    }
    return X;
}

matriz Escalona(matriz A){
    matriz result = A;
    int n = A.size();
    for (int j=0; j < n-1; j++) {
        for (int i = j+1; i < n; i++){
            double m = - result[i][j]/result[j][j];
            for (int k = 0; k < result[i].size(); k++)
                result[i][k] += m*result[j][k];
        }
    }
    return result;
}

vector<double> elim_gauss(matriz A, vector<double> b)
{
    matriz escalonada = Escalona(A);

    int n = escalonada.size();
    matriz Ab = escalonada;
    for (int i = 0; i < b.size(); i++)
        Ab[i].push_back(b[i]);

    matriz A2 = A;
    vector<double> b2;
    for (int i=0; i < n; i++)
        for (int j=0; j < n; j++)
            A2[i][j] = Ab[i][j];
    for (int i=0; i < n; i++)
        b2.push_back(Ab[i][n]);

    vector<double> X = sust_regresiva(A2, b2);
    return X;
}


void mostrarMatriz(matriz A)
{
    for (int i=0; i < A.size(); i++)
    {
        for (int j=0; j < A[i].size(); j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

void imprimirVector(vector<double> v)
{
    for (int i=0; i <v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}


int main()
{
    matriz A = {{10, -7, 1},
                {7, 1, -11},
                {2, 3, -1}};

    vector<double> b = {4, -3, 4};
    /*

    matriz res = Escalona(A);
    imprimirMatriz(res);

    vector<double> result = sust_regresiva(A, b);
    cout<<"Resultado: "<<endl;
    imprimirVector(result);

    */


    vector<double> X = elim_gauss(A, b);
    imprimirVector(X);
    return 0;
}
