#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXS 20 // number of submatrix
#define MAXN 100
#define row(p) (result[p].first)
#define col(p) (result[p].second)

void input();
void solve();
bool mycmp(pair<int, int> x, pair<int, int> y);
bool isFound(int x, int y);

int N; // demension
int S; // # of submatrix
int matrix[MAXN][MAXN];
int dimX[MAXS];
int dimY[MAXS];
pair<int, int> result[MAXS];

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " " << S << " ";
		for (int j = 0; j < S; j++)
		{
			cout << row(j) << " " << col(j) << " ";
		}
		cout << endl;
	}
}

void input()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

void solve()
{
	S = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int k = matrix[i][j];

			//if (k != 0 && !isFound(i, j))
			if(k!=0)
			{
				dimX[S] = i;
				dimY[S] = j;

				// find col
				while (j < N)
				{
					k = matrix[i][j];

					if (k == 0)
					{
						col(S) = j - dimY[S];
						break;
					}

					if (j == N - 1) // && k!=0
					{
						col(S) = N - dimY[S];
						break;
					}
					j++;
				}

				// find row
				j--;
				while (i < N)
				{
					k = matrix[i][j];

					if (k == 0)
					{
						row(S) = i - dimX[S];
						break;
					}

					if (i == N - 1) // && k!=0
					{
						row(S) = i - dimX[S];
						break;
					}
					i++;
				}

				// erase as 0
				for (int i = dimX[S]; i < dimX[S] + row(S); i++)
				{
					for (int j = dimY[S]; j < dimY[S] + col(S); j++)
					{
						matrix[i][j] = 0;
					}


				}
				//restore i, and corresponding j
				i = dimX[S];
				j = dimY[S] + col(S) - 1;

				S++;
			}


		}
	}

	sort(result, result + S , mycmp);
}


bool mycmp(pair<int, int> x, pair<int, int> y)
{
	int val1 = x.first * x.second;
	int val2 = y.first * y.second;

	if (val1 < val2) { return true; }
	else if (val1 > val2) { return false; }
	else
	{
		if (x.first < y.first) { return true; }
		else { return false; }
	}
}

bool isFound(int x, int y)
{
	for (int i = 0; i < S; i++)
	{
		if ((dimX[i] <= x) && (x < dimX[i] + row(i)))
		{
			if ((dimY[i] <= y) && (y < dimY[i] + col(i)))
			{
				return true;
			}
		}
	}
	return false;
}