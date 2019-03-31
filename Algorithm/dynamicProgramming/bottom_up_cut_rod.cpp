// 带备忘的自底向上方法
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int EXTENDED_BOTTOM_UP_CUT_ROD(int * p, int n, int * s)
{
	int r[n+1];
    r[0] = 0;
    int q;
	for(int j = 1; j <= n; j++)
    {
        q = INT_MIN;
        for(int i = 1; i <= j; i++)
            if(q < p[i] + r[j-i])
            {
                q = p[i] + r[j-i];
                s[j] = i;
            }
        r[j] = q;
    }
	return r[n];
}

void PRINT_CUT_ROD_SOLUTION(int * p, int n, int * s)
{
    int r = EXTENDED_BOTTOM_UP_CUT_ROD(p, n, s);
    cout << "最大收益: " << r << endl << "最优解: ";

    if(n == 0)
    {
        cout << 0 << endl << endl;
        return;
    }

    while(n > 0)
    {
        cout << s[n];
        n = n - s[n];
        if(n > 0)
            cout << ' ';
    }
    cout << endl << endl;
}

int main()
{
	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int s[11] = {0};
	int n;
	while(cin >> n)
    {
        PRINT_CUT_ROD_SOLUTION(p, n, s);
    }		
	return 0;
}