// 带备忘的自顶向下方法
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int MEMOIZED_CUT_ROD_AUX(int * p, int n, int * r);
int MEMOIZED_CUT_ROD(int * p,int n)
{
	int r[n+1] = {0};
	for(int i = 0; i < n+1; i++)
		r[i] = INT_MIN;
	return MEMOIZED_CUT_ROD_AUX(p, n, r);
}

int MEMOIZED_CUT_ROD_AUX(int * p, int n, int * r)
{
	if(r[n] >= 0)
		return r[n];
	
	int q;
	if(n == 0)
		q = 0;
	else
		q = INT_MIN;
		for(int i = 1; i <= n; i++)
			q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i, r));
	r[n] = q;
	return q;
}

int main()
{
	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int n;
	while(cin >> n)
		cout << MEMOIZED_CUT_ROD(p, n) << endl;
	return 0;
}