#include <iostream>
#include <queue>
using namespace std;

void solve();
void update();

int K, N;

unsigned int last;
int result;

int main()
{
	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		cin >> K >> N;
		solve();
		cout << result << endl;
	}

	return 0;
}

void solve()
{
	result = 0;
	last = 1983;
	queue<int> q;

	int psum = 0; // sum of numbers in queue
	for (int i = 1; i <= N; i++) // [j, i]
	{
		int cur = (last % 10000) + 1; // i 번째 입력 신호

		q.push(cur);
		psum += cur;

		if (psum == K) { result++; }
		else if (psum > K)
		{
			while (psum > K) // until psum <= K
			{
				int del = q.front();
				q.pop();
				psum -= del;
			}
			if (psum == K) { result++; }
		}

		update();
	}
}

void update()
{
	last =  last * 214013 + 2531011;
}