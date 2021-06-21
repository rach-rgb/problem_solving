#include <iostream>
#include <string>
using namespace std;

void input();
void solve();

int N;
int result;

int main()
{
	input();
	solve();
	cout << result << endl;

	return 0;
}

void input()
{
	cin >> N;
}

void solve()
{
	result = 0;
	for (int i = 1; i <= N; i++)
	{
		int n = i;
		while (n > 0)
		{
			int div = n % 10;
			if (div == 3 || div == 6 || div == 9)
			{
				result++;
			}
			n = n / 10;
		}
	}
}