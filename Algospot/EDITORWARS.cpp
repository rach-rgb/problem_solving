#include <iostream>
#include <string>
using namespace std;

#define MAXN (10000)

void solve();
void initialize();
int merge(int x, int y);
int getParent(int x);
bool ack(int x, int y);
bool dis(int x, int y);

int N, M;
int par[MAXN];
int h[MAXN];
int s[MAXN];
int enemy[MAXN];
bool success;
int msize;
int cont;


int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N >> M;
		solve();
		if (success)
		{
			cout << "MAX PARTY SIZE IS " << msize << endl;
		}
		else
		{
			cout << "CONTRADICTION AT " << cont << endl;
		}
	}

	return 0;
}

void solve()
{
	success = true;
	msize = 0;
	cont = -1;
	initialize();

	for (int i = 1; i <= M; i++)
	{
		string type;
		int x, y;
		cin >> type >> x >> y;

		if (type == "ACK")
		{
			success = ack(x, y);
		}
		else
		{
			success = dis(x, y);
		}

		if (!success)
		{
			cont = i;
			break;
		}
	}

	if (success)
	{
		for (int i = 0; i < N; i++)
		{
			if (par[i] == i)
			{
				int en = enemy[i];

				if (i < en) { continue; }
				// i > en
				int s1 = s[i];
				int s2 = (en == -1) ? 0 : s[en];
				
				msize += (s1 > s2) ? s1 : s2;
			}
		}
	}

}

void initialize() {
	for (int i = 0; i < N; i++){ par[i] = i; }
	for (int i = 0; i < N; i++) { s[i] = 1; }
	for (int i = 0; i < N; i++) { h[i] = 0; }
	for (int i = 0; i < N; i++) { enemy[i] = -1; }
}

int merge(int x, int y)
{
	if (x == -1) { return y; }
	if (y == -1) { return x; }

	x = getParent(x);
	y = getParent(y);

	if (x == y) { return x; }
	if (h[x] < h[y])
	{
		par[x] = y;
		s[y] += s[x];
		return y;
	}
	else // h[x] >= h[y]
	{
		par[y] = x;
		s[x] += s[y];
		if (h[x] == h[y]) { h[x]++; }
		return x;
	}
}

int getParent(int x)
{
	if (par[x] == x) { return x; }
	else
	{
		par[x] = getParent(par[x]);
		return par[x];
	}
}

bool ack(int x, int y)
{
	x = getParent(x);
	y = getParent(y);

	if (enemy[x] == y) { return false; }

	int a = merge(x, y), b = merge(enemy[x], enemy[y]);
	enemy[a] = b;

	if (b != -1)
	{
		enemy[b] = a;
	}

	return true;
}

bool dis(int x, int y)
{
	x = getParent(x);
	y = getParent(y);

	if (x == y) { return false; }

	int a = merge(x, enemy[y]), b = merge(y, enemy[x]);
	enemy[a] = b;
	enemy[b] = a;

	return true;
}