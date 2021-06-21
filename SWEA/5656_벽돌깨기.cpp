#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXW 12
#define MAXH 15

typedef struct _coord
{
	int x;
	int y;
	int r;
	_coord(int ux, int uy, int ur) : x(ux), y(uy), r(ur) {}
} coord;

void input();
void solve();
void DFS(int(*block)[MAXW], int n, int remain);
void copyBlock(int(*src)[MAXW], int(*dst)[MAXW]);
void adjustBlock(int(*blocks)[MAXW]);
int removeBlock(int(*block)[MAXW], int k, int remain);

int N, W, H;
int blocks[MAXH][MAXW];
int total;
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
	cin >> N >> W >> H;
	
	total = 0;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> blocks[i][j];
			if (blocks[i][j]) { total++; }
		}
	}
}

void solve()
{
	result = H * W;

	DFS(blocks, 0, total);
}

void DFS(int (*block)[MAXW], int n, int remain)
{
	if (n == N) { // no more change
		result = (result < remain) ? result : remain; return; 
	}

	// all blocks can be removed
	if (remain <= N - n) { result = 0; return; }

	// else
	for (int i = 0; i < W; i++)
	{
		int newBlock[MAXH][MAXW];
		copyBlock(block, newBlock);
		int newRemain = removeBlock(newBlock, i, remain);
		
		if (newRemain != remain)
		{
			DFS(newBlock, n + 1, newRemain);
		}
	}
}

void copyBlock(int(*src)[MAXW], int(*dst)[MAXW])
{
	for (int i = 0; i < H; i++)
	{
		memcpy(dst + i, src + i, sizeof(int) * W);
	}
}

// when ball is fell at k
int removeBlock(int(*block)[MAXW], int k, int remain)
{
	int x = H, y = k;
	queue<coord> q;

	// find first target
	for (int i = 0; i < H; i++)
	{
		if (block[i][k] != 0) { x = i; break; }
	}
	if (x == H) { return remain; } // no change

	q.push(coord(x, y, block[x][y]));

	while (!q.empty())
	{
		coord cur = q.front();
		q.pop();

		int qx = cur.x;
		int qy = cur.y;
		int r = cur.r;

		// up
		for (int i = qx-1; (i >= 0) && (qx-i<r); i--)
		{
			int nr = block[i][qy];

			if (nr > 1) { q.push(coord(i, qy, nr)); block[i][qy] = 0;  continue; }
			else if (nr == 1) { block[i][qy] = 0; remain--; }
			 // remove block
		}

		// down
		for (int i = qx+1; (i < H) && (i - qx < r); i++)
		{
			int nr = block[i][qy];

			if (nr > 1) { q.push(coord(i, qy, nr)); block[i][qy] = 0; continue; }
			else if (nr == 1) { block[i][qy] = 0; remain--; }
		}

		// left
		for (int j = qy-1; (j >= 0) && (qy - j < r); j--)
		{
			int nr = block[qx][j];

			if (nr > 1) { q.push(coord(qx, j, nr)); block[qx][j] = 0; continue; }
			else if (nr == 1) { block[qx][j] = 0; remain--; }
		}

		// right
		for (int j = qy + 1; (j < W) && (j - qy < r); j++)
		{
			int nr = block[qx][j];

			if (nr > 1) { q.push(coord(qx, j, nr)); block[qx][j] = 0; continue; }
			else if (nr == 1) { block[qx][j] = 0; remain--; }
		}

		// remove itself
		block[qx][qy] = 0; remain--;
	}

	adjustBlock(block);

	return remain;
}

void adjustBlock(int(*blocks)[MAXW])
{
	int hop[MAXH];

	for (int j = 0; j < W; j++)
	{
		int empty = 0;
		hop[H - 1] = 0;
		if (blocks[H - 1][j] == 0) { empty++; }

		for (int i = H - 2; i >= 0; i--)
		{
			if (blocks[i][j] == 0) // empty space
			{
				empty++;
				hop[i] = empty - 1;
			}
			else
			{
				hop[i] = empty;
			}
		}

		for (int k = H - 1; k >= 0; k--)
		{
			blocks[k + hop[k]][j] = blocks[k][j];
		}

		for (int k = 0; k < empty; k++)
		{
			blocks[k][j] = 0;
		}
	}
}