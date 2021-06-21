/* stack을 사용한 울타리 자르기 */
#include <iostream>
#include <stack>
using namespace std;

#define MAXN 20000

void input();
void solve();

int N;
int fence[MAXN+1];

long long result;

int main()
{
	ios::sync_with_stdio(false);
	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		input();
		solve();
		cout << result << endl;
	}
	return 0;
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> fence[i];
	}
	fence[N] = 0; // dummy
}

void solve()
{
	result = 0;
	stack<int> s;
	long long area;

	for (int i = 0; i <= N; i++)
	{
		if (s.empty()) { s.push(i); continue; }

		if (fence[s.top()] <= fence[i])
		{
			s.push(i);
		}
		else
		{
			while ((!s.empty()) && (fence[s.top()] > fence[i]))
			{
				int j = s.top();
				s.pop();

				int width;
				if (!s.empty()) { width = i - s.top() - 1; }
				else { width = i; }

				area = ((long long)fence[j] * (long long)width);
				result = (result > area) ? result : area;
			}
			s.push(i);
		}
	}

	s.pop();
}