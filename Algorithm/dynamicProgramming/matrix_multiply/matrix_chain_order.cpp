// 矩阵链乘法标量乘法最优次数
// 自底向上方法
#include <iostream>
#include <climits>

using namespace std;

void MATRIX_CHAIN_ORDER(int * p, int n, int m[][7], int s[][7])
{
    n -= 1;
    
    for(int l = 2; l <= n; l++)
    {
        for(int i = 1; i <= n-l+1; i++)
        {
            int j = i + l -1;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j-1; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void PRINT_OPTIMAL_PARENS(int s[][7], int i, int j)
{
    if(i == j)
        cout << "A" << i;
    else
        {
            cout << "(";
            PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
            PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
            cout << ")";
        }
}

int main()
{
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    int m[7][7] = {0};
    int s[7][7] = {0};

    MATRIX_CHAIN_ORDER(p, 7, m, s);

/*
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            {
                cout << m[i][j];
                if(j != 6)
                    cout << ' ';
                else
                    cout << endl; 
            }

    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            {
                cout << s[i][j];
                if(j != 6)
                    cout << ' ';
                else
                    cout << endl; 
            }
*/
    PRINT_OPTIMAL_PARENS(s, 1, 6);
    cout << endl;
    return 0;
}