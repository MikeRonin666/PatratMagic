#include <iostream>
using namespace std;

int a[10][10];
void Citire(int &n , int v[10][10])
{
    //cout<<"n: "; cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>v[i][j];
}
void Afisare(int n , int v[10][10])
{
    for(int i=0; i<n; i++)
        {for(int j=0; j<n; j++)
            cout<<v[i][j]<<' ';
        cout<<endl;
        }
}

void Impar(int n)
{
    int a[n][n];

    for(int x = 0; x < n; x++) 
        for(int y = 0; y < n; y++) 
            a[x][y] = 0;

    int i=n/2,
    j=n-1;
    a[i][j]=1;
    
    for(int k=2; k<=n*n; k++)
    {
        i=i-1;
        j=j+1;

        if(i<0) i=n-1;
        if(j>=n) j=0;

        if(a[i][j]!=0)
        {
            i=i+1;
            j=j-2;
            if(i >= n) i = 0;
            if(j < 0) j = j+n; //?
        }
        if(i < 0 && j == n) 
        {
            i=0;
            j=n-2;
        }

        a[i][j]=k;

    }

   for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }

}
void ParPar(int n)
{
    int k=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            a[i][j]=++k;
    for(int i=1;i<=n/4;++i)
        for(int j=n/4+1;j<=n-n/4;++j)
            swap(a[i][j],a[n-i+1][n-j+1]);
    for(int i=1;i<=n/4;++i)
        for(int j=n/4+1;j<=n-n/4;++j)
            swap(a[j][i],a[n-j+1][n-i+1]);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            cout<<a[i][j]<<' ';
        cout<<'\n';
    } 
}

void PareImpare(int n)
{
    // 1. Setup: n is singly even (e.g., 6, 10), so m is odd (e.g., 3, 5).
    int m = n / 2;
    int k = (n - 2) / 4; 
    
    int a[n][n];

    // Initialize only the first quadrant A to 0 for collision detection
    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            a[i][j] = 0;

    // 2. Fill the Quadrants
    // Pattern: A | C
    //          --+--
    //          D | B
    // A uses numbers 1..m^2
    // B uses m^2+1..2m^2 (Bottom-Right)
    // C uses 2m^2+1..3m^2 (Top-Right)
    // D uses 3m^2+1..4m^2 (Bottom-Left)

    // Using standard Siamese (Top-Middle start) for the sub-grids
    int row = 0;
    int col = m / 2;

    for(int x = 1; x <= m*m; x++)
    {
        // Fill A (Top-Left)
        a[row][col] = x;
        // Fill B (Bottom-Right) -> value + m*m
        a[row + m][col + m] = x + m * m;
        // Fill C (Top-Right) -> value + 2*m*m
        a[row][col + m] = x + 2 * m * m;
        // Fill D (Bottom-Left) -> value + 3*m*m
        a[row + m][col] = x + 3 * m * m;

        // Move Logic (Siamese)
        int next_row = row - 1;
        int next_col = col + 1;

        if(next_row < 0) next_row = m - 1;
        if(next_col >= m) next_col = 0;

        if(a[next_row][next_col] != 0)
        {
            next_row = row + 1;
            next_col = col;
        }

        row = next_row;
        col = next_col;
    }

    // 3. Swapping Rules (Strachey Method)

    // Left Side Swap (Swap columns 0 to k-1 between A and D)
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < k; j++)
        {
            // Standard: swap column j
            int swap_col = j;
            
            // Exception: In the middle row of the quadrant, shift swap 1 step right
            if(i == m / 2) 
                swap_col = j + 1;

            swap(a[i][swap_col], a[i + m][swap_col]);
        }
    }

    // Right Side Swap (Swap last k-1 columns between C and B)
    // This only runs if n > 6
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < k - 1; j++)
        {
            int swap_col = n - 1 - j;
            swap(a[i][swap_col], a[i + m][swap_col]);
        }
    }

    // 4. Print
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}
bool Verificare(int n, int a[10][10])
{
    int sumad1=0, sumad2=0;
    for(int i=0; i<n; i++) ///suma diagonala princiapala si secundara
    {
        sumad1+=a[i][i];
        sumad2+=a[i][n-i-1];
    }
    if(sumad1 != sumad2) return false;

    for(int i=0; i<n; i++)
    {
        int sumaR=0, sumaC=0;
        for(int j=0; j<n; j++)
        {
            sumaR+= a[i][j]; ///suma randuri
            sumaC+=a[j][i]; ///suma coloane
        }
        if(sumaR != sumaC || sumaR != sumad1) return false;
    }
    return true;
    
}

int main()
{
    int n;
    cout<<"n: "; cin>>n;
 /* Citire(n,v);
    cout<<endl; */
    //Afisare(n,v);
    cout<<endl;
    
    if(n%2)
        Impar(n);
    if(n%4==0)
        ParPar(n);
    else PareImpare(n);

 /*    if(Verificare(n,v)) cout<<"Patratul este magic!";
    else cout<<"Patratul nu este magic!";*/


}