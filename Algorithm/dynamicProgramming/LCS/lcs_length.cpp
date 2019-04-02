/************************************************
*算法：动态规划
*说明：计算最长子序列LCS问题
************************************************/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void LCS_LENGTH(string & X, string & Y, vector<vector<int>> & c, vector<vector<string>> & b)
{
    int m = X.length();
    int n = Y.length();
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(X[i-1] == Y[j-1])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = "LU";
            }
            else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = "UP";
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = "LF";
            }
        }
    }
}

void PRINT_LCS(vector<vector<string>> & b, string & X, int i, int j)
{
    if(i == 0 || j == 0)
        return;
    if(b[i][j] == "LU")
    {
        PRINT_LCS(b, X, i - 1, j - 1);
        cout << X[i - 1];
    }
    else if(b[i][j] == "UP")
        PRINT_LCS(b, X, i - 1, j);
    else
        PRINT_LCS(b, X, i, j - 1);

}

int main()
{
    string X("ABCBDAB");
    string Y("BDCABA");

    int m = X.length();
    int n = Y.length();

    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    vector<vector<string>> b(m + 1, vector<string>(n + 1, "NO"));

    LCS_LENGTH(X, Y, c, b);

    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            cout << c[i][j] << ": " << b[i][j];
            if(j != n)
                cout << "   ";
            else
                cout << endl;
        }
    }

    PRINT_LCS(b, X, m, n);
    cout << endl;

    return 0;
}
