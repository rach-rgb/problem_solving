#include <iostream>
#include <map>
using namespace std;

void solve();
bool isDominated(int x, int y);
void remove(int x, int y);

int N;
int result;
map<int, int> coords;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		solve();
		cout << result << endl;
	}

	return 0;
}

void solve()
{
	result = 0;
	coords.clear();

	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;

		if (!isDominated(x, y))
		{
			remove(x, y);
			coords.insert(pair<int, int>(x, y));
		}

		result += coords.size();
	}
}

bool isDominated(int x, int y)
{
	map<int, int>::iterator it = coords.lower_bound(x);

	if (it == coords.end()) { return false; }
	else
	{
		return (it->second > y);
	}
}

void remove(int x, int y)
{
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.begin()) { return; }

	it--;
	while(true)
	{
		if (it->second < y)
		{
			if (it == coords.begin())
			{
				coords.erase(it);
				break;
			}
			else
			{
				map<int, int>::iterator jt = it;
				it--;
				coords.erase(jt);;
			}
		}
		else
		{
			break;
		}
	}
}

