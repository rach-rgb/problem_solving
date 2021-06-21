#include <iostream>
#include <string>
using namespace std;

void solve();
int count_chunk();
int count_chunk2();

int N;
string balls;
int result;

int main()
{
	cin >> N;
	cin >> balls;
	solve();
	cout << result << endl;

	return 0;
}

void solve()
{
	int numR = 0, numB = 0;
	int left, right;
	int tmp;

	for (int i = 0; i < N; i++)
	{
		if (balls[i] == 'R') { numR++; }
		else { numB++; }
	}

	if (numR == N || numB == N) { result = 0; return; }

	left = count_chunk();
	right = count_chunk2();

	// R..B.. by move R
	if (balls[0] == 'R') { result = numR - left; }
	else { result = numR; }

	// R..B.. by move B
	if (balls[N - 1] == 'B') { tmp = numB - right; }
	else { tmp = numB; }
	result = (result < tmp) ? result : tmp;

	// B..R.. by move R
	if (balls[N - 1] == 'R') { tmp = numR - right; }
	else { tmp = numR; }
	result = (result < tmp) ? result : tmp;

	// B..R.. by move B
	if (balls[0] == 'B') { tmp = numB - left; }
	else { tmp = numB; }
	result = (result < tmp) ? result : tmp;
}

int count_chunk() // count left chunk
{
	int count = 1;
	char color = balls[0];

	for (int i = 1; i < N; i++)
	{
		if (balls[i] == color) { count++;  }
		else { break; }
	}

	return count;
}

int count_chunk2() // count right chunk
{
	int count = 1;
	char color = balls[N-1];

	for (int i = N-2; i > -1; i--)
	{
		if (balls[i] == color) { count++; }
		else { break; }
	}

	return count;
}