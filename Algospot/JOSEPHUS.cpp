#include <iostream>
#include <list>
using namespace std;

void solve();

int N, K;
int result1, result2;

int main()
{
	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		cin >> N >> K;
		solve();
		cout << result1 << " " << result2 << endl;
	}

	return 0;
}

void solve()
{
	list<int> l;
	list<int>::iterator target;

	for (int i = 1; i <= N; i++)
	{
		l.push_back(i);
	}

	int count = N;
	target = l.begin();
	while (count > 2)
	{
		if ((*target) == l.back()) { l.erase(target); target = l.begin(); }
		else { target = l.erase(target); }

		count--;

		// move iterator
		for (int i = 0; i < K - 1; i++) {
			target++;
			if (target == l.end()) { target = l.begin(); }
		}
	}

	target = l.begin();
	result1 = *(target);
	target++;
	result2 = *(target);

	return;
}