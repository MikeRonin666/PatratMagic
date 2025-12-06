#include <iostream>
#include <iomanip>
using namespace std;

/**
2 7 6
9 5 1
4 3 8
*/

void citire(int **&v,int n,char c)
{
    int i,j;
    cout<<"Dati elementele matricei "<<c<<endl;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        cin>>v[i][j];
}

void afisare(int **v, int n)
{
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++) cout<<setw(6)<<v[i][j];
        cout<<endl;
    }
}

bool verificareMagic(int **v,int n)
{
    int i,j,sumM=0,suma;

    ///Calculam suma magica folosing prima linie
    for(i=0;i<n;i++)
        sumM+=v[0][i];


    ///Verificam celelalte linii
    for(i=1;i<n;i++)
    {
        suma=0;
        for(j=0;j<n;j++)
            suma+=v[i][j];

        if(suma!=sumM)
            return 0;
    }


    ///Verificam coloanele
    for(i=0;i<n;++i)
    {
        suma=0;
        for(j=0;j<n;j++)
            suma+=v[j][i];

        if(suma!=sumM)
            return 0;
    }

    ///Verificam diagonala principala
    suma=0;
    for(i=0;i<n;i++)
        suma+=v[i][i];
    if(suma!=sumM)
        return 0;

    ///Verificam diagonala secundara
    suma=0;
    for(i=0;i<n;i++)
        suma+=v[i][n-i-1];
    if(suma!=sumM)
        return 0;

    ///Returnam 1 daca e patrat magic
    return 1;
}

int main()
{
    int **v;
    int n;
    cout<<"Introduceti n: ";cin>>n;
    v = new int*[n];
    for(int i=0;i<n;i++)
        v[i]=new int [n];
    citire(v,n,'A');
    if(verificareMagic(v,n))
        cout<<"Patrat magic!";
    else cout<<"Patratul nu este magic!";


    for(int i=0;i<n;i++)
        delete [] v[i];
    delete [] v;

    return 0;
}
