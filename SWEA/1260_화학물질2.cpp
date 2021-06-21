#include <iostream>
#include <utility>
#include <cstring>
using namespace std;

#define MAXN 100
#define MAXS 20
#define MAXINT 987654321

void input();
void solve();
void getMatrix();
void findMatrix(int x, int y);
void findSequence();
void solve_DP();
int getMult(int i, int j);

int N;
int board[MAXN][MAXN];
int S; // # of submatrix
pair<int, int> matrix[MAXS]; // dimension of matrix
int sequence[MAXS]; // longest sequence
pair<int, int> m[MAXS]; // dimesion of matrix in correct order
int mult[MAXS][MAXS]; // minimum required multiplication
int result;

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " " << result << endl;
	}
	return 0;
}

void input()
{
	cin >> N;
	// matrix
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
}

void solve()
{
	result = 0;

	// store matrix information
	getMatrix();

	// find longest sequence
	findSequence();

	// store matrix in order
	for (int i = 0; i < S; i++)
	{
		m[i].first = matrix[sequence[i]].first;
		m[i].second = matrix[sequence[i]].second;
	}

	// get minimum matrix multiplication
	solve_DP();

	result = mult[0][S - 1];
}

void getMatrix()
{
	S = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] != 0) // find matrix
			{
				findMatrix(i, j);
			}
		}
	}
}

// find matrix start from (x, y)
void findMatrix(int x, int y)
{
	// get height
	for (int i = x; i < N; i++)
	{
		if (board[i][y] == 0)
		{
			matrix[S].second = i - x;
			break;
		}
		if (i == N - 1)
		{
			matrix[S].second = i - x + 1;
		}
	}

	// get width
	for (int j = y; j < N; j++)
	{
		if (board[x][j] == 0)
		{
			matrix[S].first = j - y;
			break;
		}
		if (j == N - 1)
		{
			matrix[S].first = j - y + 1;
		}
	}

	// fiil as 0s
	for (int i = x; i < x + matrix[S].second; i++)
	{
		for (int j = y; j < y + matrix[S].first; j++)
		{
			board[i][j] = 0;
		}
	}

	S++;
}

void findSequence()
{
	int sizes[MAXN + 1]; // sizes[x] = y => stick y has front size x (1<=size<=N)
	memset(sizes, -1, sizeof(int) * (MAXN + 1));

	// store sizes[]
	for (int i = 0; i < S; i++)
	{
		int x = matrix[i].first;
		sizes[x] = i;
	}

	// find sequence(index)
	for (int i = 0; i < S; i++)
	{
		int len = 1;
		int cur = i;
		sequence[0] = cur;
		while (len < S)
		{
			int next = sizes[matrix[cur].second];

			if (next == -1) { break; } // no matching stick

			// add stick information
			sequence[len] = next;
			cur = next;
			len++;
		}

		if (len == S) // complete sequence
		{
			break;
		}
	}
}

void solve_DP()
{
	// init
	for (int i = 0; i < S; i++)
	{
		for (int j = i; j < S; j++)
		{
			if (i == j) { mult[i][j] = 0; }
			else { mult[i][j] = -1; }
		}
	}

	getMult(0, S - 1);
}

int getMult(int i, int j)
{
	int ret = mult[i][j];

	if (ret != -1) { return ret; }

	ret = MAXINT;
	for (int k = i; k < j; k++)
	{
		int cmp = getMult(i, k) + getMult(k + 1, j) + m[i].first * m[k].second * m[j].second;
		ret = (ret < cmp) ? ret : cmp;
	}
	mult[i][j] = ret;

	return ret;
}