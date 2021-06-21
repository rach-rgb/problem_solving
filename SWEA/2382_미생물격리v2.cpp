#include <iostream>
using namespace std;

#define MAXK 1000
#define MAXN 100
typedef struct _group {
	short x;
	short y;
	int num;
	short dir; // 1 2 3 4 (U D L R)
} group;

typedef struct _info
{
	int sum;
	int firstGroup;
	int t;
	_info() : sum(0), firstGroup(-1), t(-1) {}
} info;

void input();
void solve();
bool inRange(short x, short y);
short flip(short dir);

int N, M, K;
group groups[MAXK];
short dx[5] = { 5, -1, 1, 0, 0 };
short dy[5] = { 5, 0, 0, -1, 1 };
info board[MAXN][MAXN];
int col[MAXK];
int ncol = 0;
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
	cin >> N >> M >> K;

	short ux, uy, udir;
	int unum;
	for (int i = 0; i < K; i++)
	{
		cin >> ux >> uy >> unum >> udir;
		groups[i].x = ux;
		groups[i].y = uy;
		groups[i].num = unum;
		groups[i].dir = udir;
	}
}

void solve()
{
	result = 0;

	for (int t = 0; t < M; t++) // for each time
	{
		ncol = 0;
		for (int i = 0; i < K; i++) // for each group
		{
			group* f = &groups[i];
			if (f->num == 0) { continue; } // empty group

			//move
			short nx = f->x + dx[f->dir];
			short ny = f->y + dy[f->dir];
			f->x = nx; f->y = ny;

			// if out of range
			if (!inRange(nx, ny))
			{
				f->num /= 2;
				f->dir = flip(f->dir);
			}

			// check collision
			info* pos = &board[nx][ny];
			if ((pos->sum == 0)||(pos->t<t)) // first
			{
				pos->sum = f->num;
				pos->firstGroup = i;
				pos->t = t;
			}
			else // if others
			{
				group* prev = &groups[pos->firstGroup];
				if (pos->sum == prev->num) { col[ncol] = pos->firstGroup; ncol++; } // arrived second

				pos->sum += f->num;
				if (prev->num < f->num) // update
				{
					prev->num = f->num;
					prev->dir = f->dir;
				}
				f->num = 0; // remove
			}
		}

		// handle collision
		for (int c = 0; c < ncol; c++)
		{
			group* fG = &groups[col[c]];
			short cx = fG->x;
			short cy = fG->y;

			fG->num = board[cx][cy].sum;
			board[cx][cy].sum = 0;
		}
	}

	// sum
	for (int i = 0; i < K; i++)
	{
		if (groups[i].num != 0)
		{
			result += groups[i].num;
		}
	}

	// reset board
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j].t = -1;
			board[i][j].sum = 0;
		}
	}
}

bool inRange(short x, short y)
{
	if ((x >= 1) && (x < N-1))
	{
		if ((y >= 1) && (y < N-1))
		{
			return true;
		}
	}
	return false;
}

short flip(short dir)
{
	if (dir == 1) { return 2; }
	else if (dir == 2) { return 1; }
	else if (dir == 3) { return 4; }
	else { return 3; }
}