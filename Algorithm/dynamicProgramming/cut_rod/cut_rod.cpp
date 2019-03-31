// 钢条切割问题
// 朴素自顶向下递归实现
#include <iostream>
#include <algorithm>

using namespace std;

int CUT_ROT(int * p, int n)
{
	if(n == 0)
		return 0;
	int q = -1;
	for(int i = 1; i <= n; i++)
		q = max(q, p[i] + CUT_ROT(p, n - i));
	return q;
}

int main()
{
	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int n;
	while(cin >> n)
		cout << CUT_ROT(p, n) << endl;
	return 0;
}