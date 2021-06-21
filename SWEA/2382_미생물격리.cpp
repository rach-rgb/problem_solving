#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100
#define MAXK 1000

typedef struct _info {
	short x;
	short y;
	int num;
	short dir;
} info;

void input();
void solve();
void resetBoard();
bool isBorder(info* x);

int N, M, K;
int result;
info infos[MAXK];
int board[MAXN][MAXN];
short dx[5] = { 0, -1, 1, 0, 0 }; //** direction is represented as 1, 2, 3, 4
short dy[5] = { 0, 0, 0, -1, 1 };

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
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++)
	{
		cin >> infos[i].x >> infos[i].y >> infos[i].num >> infos[i].dir;
	}
}

void solve()
{
	int tmp[MAXK];

	result = 0;

	memset(tmp, -1, K * sizeof(int));
	for (int i = 0; i < M; i++) // for each timestamp
	{
		resetBoard();
		for (int j = 0; j < K; j++) // for each cluster
		{
			if (infos[j].num == 0) { continue; }
			if (tmp[j] != -1) { infos[j].num = tmp[j]; tmp[j] = -1; } // update merged cluster

			short dir = infos[j].dir;

			// move
			infos[j].x += dx[dir];
			infos[j].y += dy[dir];

			// check border
			if (isBorder(&infos[j])) {
				if (dir == 1 || dir == 3) { infos[j].dir++; }
				else { infos[j].dir--; }
				infos[j].num = infos[j].num / 2;
			}

			// merge cluster
			if (board[infos[j].x][infos[j].y]!=-1) // need to merge
			{
				int prev = board[infos[j].x][infos[j].y];

				if (tmp[prev] == -1) { tmp[prev] = infos[prev].num + infos[j].num; } // ** store total germs in tmp[]
				else { tmp[prev] += infos[j].num; }

				if (infos[prev].num < infos[j].num) {
					infos[prev].num = infos[j].num; 
					infos[prev].dir = infos[j].dir; 
				} // ** update direction and number of microorganism in kluster

				// remove current cluster
				infos[j].num = 0;
			}
			else // check
			{
				board[infos[j].x][infos[j].y] = j;
			}
		}
	}

	for (int i = 0; i < K; i++)
	{
		if (tmp[i] != -1) { result += tmp[i]; }
		else
		{
			result += infos[i].num;
		}	
	}
}

void resetBoard()
{
	for (int i = 0; i < N; i++)
	{
		memset(board[i], -1, N*sizeof(int));
	}
}

bool isBorder(info* x)
{
	if (x->x == 0 || x->x == N - 1) { return true; }
	else if (x->y == 0 || x->y == N - 1) { return true; }
	return false;
}