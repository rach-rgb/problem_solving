#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXW 12
#define MAXH 15

short board[MAXH][MAXW];
int holes[MAXH];

typedef struct _explode {
	short x;
	short y;
	short r;
	_explode(short ux, short uy, short val) : x(ux), y(uy), r(val) {}
} loc;

void input();
void solve();
void DFS(short(*blocks)[MAXW], int ball, int remain);
void copyArray(short(*dst)[MAXW], short(*src)[MAXW]);
void dropBlocks(short(*dst)[MAXW]);

bool inRange(short x, short y);

int N, W, H;

int remain;
queue<loc> q; // balls to be explode
short dx[4] = { 0,0,1,-1 };
short dy[4] = { 1, -1, 0, 0 };

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
	cin >> N >> W >> H;
	
	remain = 0;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> board[i][j];
			if (board[i][j])
			{
				remain++;
			}
		}
	}
}

void solve()
{
	result = remain;

	DFS(board, 0, remain);
}

void DFS(short (*blocks)[MAXW], int ball, int remain)
{
	if (result == 0) { return; }
	if (remain == 0) { result = 0; return; }

	if (ball >= N) { // no more try
		result = (result < remain) ? result : remain; 
		return; 
	}

	for (int x = 0; x < W; x++) // drop to x
	{
		if (result == 0) { return; }

		short newBlocks[MAXH][MAXW];
		copyArray(newBlocks, blocks);

		int newRemain = remain;

		// remove blocks
		// find start point
		short topLoc = 0;
		while ((blocks[topLoc][x] == 0) && (topLoc < H))
		{
			topLoc++;
		}

		// empty column
		if (topLoc == H) { continue; }

		short r = newBlocks[topLoc][x];

		if (r == 1) // one explode
		{
			newRemain--;
			newBlocks[topLoc][x] = 0;
			DFS(newBlocks, ball + 1, newRemain);
			continue;
		}

		// else r > 1
		q.push(loc(topLoc, x, r));
		newRemain--;
		newBlocks[topLoc][x] = 0; // remove block

		while (!q.empty())
		{
			loc cur = q.front();
			q.pop();
			short x = cur.x;
			short y = cur.y;
			short r = cur.r;

			short nX;
			short nY;
			for (int d = 0; d < 4; d++)
			{
				for (int l = 1; l <= r - 1; l++)
				{
					nX = x + dx[d] * l;
					nY = y + dy[d] * l;
					
					if (inRange(nX, nY)) // valid location
					{
						short* point = &newBlocks[nX][nY];

						if ((*point) > 1)
						{
							q.push(loc(nX, nY, *(point)));
							newRemain--;
							(*point) = 0;
						}
						else if ((*point) == 1)
						{
							newRemain--;
							(*point) = 0;
						}
					}
				}
			}
			
		}

		dropBlocks(newBlocks);

		DFS(newBlocks, ball + 1, newRemain);
	}
}

void copyArray(short(*dst)[MAXW], short(*src)[MAXW])
{
	for (int i = 0; i < H; i++)
	{
		memcpy(dst + i, src + i, sizeof(short) * W);
	}
}

bool inRange(short x, short y)
{
	if ((x >= 0) && (x < H))
	{
		if ((y >= 0) && (y < W))
		{
			return true;
		}
	}

	return false;
}

void dropBlocks(short(*blocks)[MAXW])
{
	for (int w = 0; w < W; w++) // for each column
	{
		// count top loc
		int topLoc = 0;
		while ((blocks[topLoc][w] == 0) && (topLoc < H))
		{
			topLoc++;
		}

		if (topLoc == H) { continue; } // no balls

		int h = H - 1;

		// count empty space
		if (blocks[H - 1][w]) { holes[H - 1] = 0; }
		else { holes[H-1] = 1; }

		for (h--; h >= 0; h--)
		{
			if (blocks[h][w]) { holes[h] = holes[h+1]; }
			else { holes[h] = holes[h+1] + 1; }
		}



		// drop blocks
		for (h = H - 2; h >= topLoc; h--)
		{
			blocks[h + holes[h + 1]][w] = blocks[h][w];
		}

		// fill with 0s
		for (h = 0; h < topLoc + holes[topLoc]; h++)
		{
			blocks[h][w] = 0;
		}
	}
}