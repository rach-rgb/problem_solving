#include <iostream>
#include <queue>
using namespace std;

#define MOD (20090711)

typedef struct _seq {
	int a;
	int b;
	int val;

	_seq(int ua, int ub) : a(ua), b(ub), val(1983) {};

	int getVal()
	{
		int ret = val;
		val = (((val * (long long)a)) % MOD + b) % MOD;

		return ret;
	}

} seq;

void input();
void solve();

int N, A, B;
int result;

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		cout << result << endl;
	}

	return 0;
}

void input()
{
	cin >> N >> A >> B;
}

void solve()
{
	result = 0;

	seq s(A, B);

	priority_queue<int, vector<int>, greater<int>> pq1; // min root
	priority_queue<int> pq2; // max root

	int v1 = s.getVal();
	int v2 = s.getVal();

	if (v1 < v2) { 
		pq2.push(v1); pq1.push(v2); 
		result = (v1 * 2) % MOD; 
	}
	else { 
		pq2.push(v2); pq1.push(v1); 
		result = (v2 * 2) % MOD; } //  v1 >= v2

	for (int i = 2; i < N; i++)
	{
		int v = s.getVal();

		int x = pq1.top(), y = pq2.top();

		if (pq1.size() == pq2.size())
		{
			if (y <= v) { pq1.push(v); }
			else { 
				pq2.pop();
				pq1.push(y);
				pq2.push(v);
			}

			result = (result + pq1.top()) % MOD;
		}
		else
		{
			if (x >= v) { pq2.push(v); }
			else
			{
				pq1.pop();
				pq2.push(x);
				pq1.push(v);
			}

			result = (result + pq2.top()) % MOD;
		}
	}
}