#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100
#define MAXW 10

void input();
void solve();
int game(int sx, int sy, int dir);
bool inRange(int x, int y);
bool isEnd(int x, int y);
int reverseDir(int d);
int changeDir(int type, int d);
bool isWarp(int x, int y);
int warpX(int type, int x);
int warpY(int type, int y);

int N;
int board[MAXN][MAXN];
int wx[MAXW + 1];
int wy[MAXW + 1];

int sx, sy; // start point
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int result;

int main()
{
	ios::sync_with_stdio(false);

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
	
	memset(wx, -1, sizeof(int) * (MAXW+1));
	memset(wy, -1, sizeof(int) * (MAXW+1));

	int val;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> val;
			board[i][j] = val;
			
			if ((val >= 6) && (val <= 10)) // hole
			{
				if (wx[val] == -1)
				{
					wx[val] = i;
					wy[val] = j;
				}
				else // occupied
				{
					wx[val - 6] = i;
					wy[val - 6] = j;
				}
			}
		}
	}
}

void solve()
{
	result = 0;

	int point;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] != 0) { continue; }

			for (int d = 0; d < 4; d++) // four direction
			{
				sx = i;
				sy = j;

				point = game(i, j, d);
				result = (result > point) ? result : point;
			}
		}
	}
}

// game start from sx, sy
int game(int sx, int sy, int dir)
{
	int point = 0;

	int x = sx, y = sy, d = dir;
	int nx, ny;

	while (true)
	{
		// cout << x << " " << y << " " << d << endl;
		// move one step
		nx = x + dx[d];
		ny = y + dy[d];

		if (isEnd(nx, ny)) { break; } // end
		else if (!inRange(nx, ny)) // wall
		{
			d = reverseDir(d);
			x = nx;
			y = ny;
			point++;
		}
		else if (isWarp(nx, ny)) // warp
		{
			int type = board[nx][ny];
			x = warpX(type, nx);
			y = warpY(type, ny);
		}
		else if (board[nx][ny]!=0) // direction block
		{
			int type = board[nx][ny];

			d = changeDir(type, d); // new direction
			x = nx;
			y = ny;
			point++;
		}
		else // empty
		{
			x = nx;
			y = ny;
		}
	}

	return point;
}

bool inRange(int x, int y)
{
	if ((x >= 0) && (x < N))
	{
		if ((y >= 0) && (y < N))
		{
			return true;
		}
	}
	return false;
}

bool isEnd(int x, int y)
{
	if ((x == sx) && (y == sy)) // return to start point
	{
		return true;
	}
	else if (board[x][y] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int reverseDir(int d)
{
	if (d == 0) { return 1; }
	else if (d == 1) { return 0; }
	else if (d == 2) { return 3; }
	else { return 2; }
}

int changeDir(int type, int d)
{
	switch (type)
	{
	case 1:
		if ((d == 1) || (d == 2))
		{
			return reverseDir(d);
		}
		else if (d == 3)
		{
			return 1;
		}
		else // d == 0
		{
			return 2;
		}
		break;

	case 2:
		if ((d == 1) || (d == 3))
		{
			return reverseDir(d);
		}
		else if (d == 0)
		{
			return 3;
		}
		else // d == 2
		{
			return 1;
		}
		break;

	case 3:
		if ((d == 0) || (d == 3))
		{
			return reverseDir(d);
		}
		else if (d == 1)
		{
			return 3;
		}
		else // d == 2
		{
			return 0;
		}
		break;

	case 4:
		if ((d == 0) || (d == 2))
		{
			return reverseDir(d);
		}
		else if (d == 3)
		{
			return 0;
		}
		else // d == 1
		{
			return 2;
		}
		break;
	case 5:
		return reverseDir(d);
	}
	return -1; //error
}

bool isWarp(int x, int y)
{
	if (board[x][y] >= 6)
	{
		if (board[x][y] <= 10)
		{
			return true;
		}
	}
	return false;
}

int warpX(int type, int x)
{
	if (wx[type] == x)
	{
		return wx[type - 6];
	}
	else {
		return wx[type];
	}
}

int warpY(int type, int y)
{
	if (wy[type] == y)
	{
		return wy[type - 6];
	}
	else {
		return wy[type];
	}
}