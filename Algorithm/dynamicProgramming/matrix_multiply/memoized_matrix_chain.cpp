// 矩阵链乘法标量乘法最优次数
// 有备忘机制的自顶向下的递归方法
#include <iostream>
#include <climits>

using namespace std;

int LOOKUP_CHAIN(int m[][7], int * p, int i, int j)
{
    if(m[i][j] < INT_MAX)
        return m[i][j];

    if(i == j)
        m[i][j] = 0;
    else
        for(int k = i; k < j; k++)
        {
            int q = LOOKUP_CHAIN(m, p, i, k) + LOOKUP_CHAIN(m, p, k+1, j) + p[i-1]*p[k]*p[j];
            if(q < m[i][j])
                m[i][j] = q;
        }
    return m[i][j];
}

int main()
{
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    int m[7][7] = {0};

    int n = 6;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            m[i][j] = INT_MAX;
    cout << LOOKUP_CHAIN(m, p, 1, n) << endl;
    return 0;
}