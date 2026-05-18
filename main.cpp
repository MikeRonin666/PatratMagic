#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

int n;
int a[101][101],grade=0;

void impar(int n)
{
    int i = 1, j = (n + 1) / 2;
    for (int num = 1; num <= n * n; num++)
    {
        a[i][j] = num;
        int ni = i - 1;
        int nj = j + 1;
        if (ni == 0) ni = n;
        if (nj == n + 1) nj = 1;
        if (a[ni][nj])
        {
            i++;
        }
        else
        {
            i = ni;
            j = nj;
        }
    }
}

void parPar(int n)
{
    int num = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = num++;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if ((i % 4 == 1 || i % 4 == 0) && (j % 4 == 1 || j % 4 == 0))
                a[i][j] = n*n + 1 - a[i][j];
            else if ((i % 4 == 2 || i % 4 == 3) && (j % 4 == 2 || j % 4 == 3))
                a[i][j] = n*n + 1 - a[i][j];
}

void parImpar(int n)
{
    int k = n / 2;
    int size = k * k;
    int b[101][101] = {0};

    // 1. Generăm pătratul magic impar de bază (k x k) în b
    int i = 1, j = (k + 1) / 2;
    for (int num = 1; num <= size; num++)
    {
        b[i][j] = num;
        int ni = i - 1, nj = j + 1;
        if (ni == 0) ni = k;
        if (nj == k + 1) nj = 1;
        if (b[ni][nj]) i++;
        else
        {
            i = ni;
            j = nj;
        }
    }

    // 2. Umplem cele 4 cadrane ale matricei 'a'
    for (int r = 1; r <= k; r++)
    {
        for (int c = 1; c <= k; c++)
        {
            a[r][c] = b[r][c];                 // Cadranul A (stânga-sus)
            a[r + k][c + k] = b[r][c] + size;     // Cadranul B (dreapta-jos)
            a[r][c + k] = b[r][c] + 2 * size;     // Cadranul C (dreapta-sus)
            a[r + k][c] = b[r][c] + 3 * size;     // Cadranul D (stânga-jos)
        }
    }

    int m = (n - 2) / 4; // Numărul de coloane ce trebuie schimbate
    int mid = k / 2 + 1; // Rândul din mijloc al cadranelor de sus

    // 3. Schimbăm elementele între cadranele din stânga (A și D)
    for (int r = 1; r <= k; r++)
    {
        for (int c = 1; c <= m; c++)
        {
            if (r == mid)
            {
                // Excepția Strachey: pe rândul din mijloc,
                // mutăm zona de swap cu o coloană la dreapta
                swap(a[r][c + m], a[r + k][c + m]);
            }
            else
            {
                // Pentru restul rândurilor, schimbăm primele m coloane
                swap(a[r][c], a[r + k][c]);
            }
        }
    }

    // 4. Schimbăm elementele între cadranele din dreapta (C și B)
    // Această parte este necesară doar pentru n > 6
    for (int r = 1; r <= k; r++)
    {
        for (int c = n - m + 2; c <= n; c++)
        {
            swap(a[r][c], a[r + k][c]);
        }
    }
}

void oglindire(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n / 2; j++)
        {
            int aux = a[i][j];
            a[i][j] = a[i][n - j + 1];
            a[i][n - j + 1] = aux;
        }
    }
}

void transpunere(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int aux = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = aux;
        }
    }
}

void afisare()
{
    cout<<"+";
    for(int i=0; i<n*6; i++)
        cout<<"-";
    cout<<"\b+";
    cout<<endl;
    for (int i = 1; i <= n; i++)
    {
        cout<<"\b|";
        for (int j = 1; j <= n; j++)
        {
            cout<<setw(3)<<a[i][j]<<setw(3)<< "|";
            Sleep(50);
        }
        cout<<setw(3)<<"\b\b |";
        cout << "\n";
    }
    cout<<"+";
    for(int i=0; i<n*6; i++)
        cout<<"-";
    cout<<"\b+";
}

void tiparesteLent(string text, int timp)
{
    for(char c:text)
    {
        cout<<c<<flush;
        Sleep(timp);
    }
    cout<<endl;
}

int main()
{
    int input;

    tiparesteLent("========================================", 10);
    tiparesteLent("   GENERATOR DE PATRATE MAGICE    ", 20);
    tiparesteLent("========================================", 10);
    cout<<"\n\n\n";

    tiparesteLent("APASATI 1 SA INCEPETI",20);
    cin>>input;


    switch(input)
    {
    case 1:
        system("cls");
    tiparesteLent("Introduceti dimensiunea n: ",20);
    cin >> n;
    if (n % 2 == 1) impar(n);
    else if (n % 4 == 0) parPar(n);
    else parImpar(n);

    for(int i=0; i<4; i++)
    {
        cout<<"Varianta "<<(i*2)+1<<" ("<<grade<<" grade)"<<endl<<endl;
        afisare();
        cout<<endl;
        oglindire(n);
        cout<<"Varianta "<<(i*2)+2<< " (Reflexie):"<<endl<<endl;
        afisare();
        oglindire(n);
        transpunere(n);
        oglindire(n);
        grade+=90;

        cout<<endl;
    }
    tiparesteLent("GENERAT CU SUCCES!",30);
    break;
    }


}
