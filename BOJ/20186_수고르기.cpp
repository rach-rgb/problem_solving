#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 5000

void input();
void solve();

int N, K;
int scores[MAXN];
long result;

int main()
{
	input();
	solve();
	cout << result;
	
	return 0;
}

void input()
{
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> scores[i];
	}
}

void solve()
{
	sort(scores, scores + N);

	result = 0; // add K highest scores
	for (int i = 0; i < K; i++)
	{
		result += scores[N - 1 - i];
	}

	result = result - (K * (K - 1)) / 2;
}