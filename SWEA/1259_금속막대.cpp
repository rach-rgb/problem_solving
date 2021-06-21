// assume: no stick has same front size or same back size
#include <iostream>
#include <utility>
#include <cstring>
using namespace std;

#define MAXN 20
#define MAXS 30

void input();
void solve();
int LS(int cur);

int N;
pair<int, int> sticks[MAXN];
int sizes[MAXS + 1]; // sizes[x] = y => sticks[y] has front size x
int L;
int result[MAXN];
int cur_result[MAXN];

int main(void)
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " ";
		for (int j = 0; j < L; j++)
		{
			cout << sticks[result[j]].first << " " << sticks[result[j]].second << " ";
		}
		cout << endl;
	}
}

void input()
{
	cin >> N;

	memset(sizes, -1, sizeof(int) * MAXS);
	for (int i = 0; i < N; i++)
	{
		cin >> sticks[i].first >> sticks[i].second;
		sizes[sticks[i].first] = i;
	}
}

void solve()
{
	L = 0;
	int l;

	for (int i = 0; i < N; i++)
	{
		l = LS(i);
		if (l > L) {
			L = l;
			memcpy(result, cur_result, sizeof(int) * L);
		}
	}
}

// return length of sequence start from cur
int LS(int cur)
{
	int ret = 0;
	int back = sticks[cur].second;

	cur_result[0] = cur;
	ret++;

	while (sizes[back] != -1)
	{
		cur = sizes[back];
		back = sticks[cur].second;

		cur_result[ret] = cur;
		ret++;
	}

	return ret;
}