#include <iostream>
using namespace std;

#define MAXK 8
#define TOP 0
#define BOT 1
#define LEFT 2 
#define RIGHT 3

void input();
void solve();
void unfold(char dir);
int new_hole(char dir, int hole);

int K, H;
char fold[MAXK * 2];
int holes[(1 << MAXK)][(1 << MAXK)];
int anchor[4];
int new_anchor[4];

int main()
{
	input();
	solve();
	for (int i = 0; i < 1 << K; i++)
	{
		for (int j = 0; j < 1 << K; j++)
		{
			cout << holes[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

void input()
{
	cin >> K;
	
	for (int i = 0; i < 2*K; i++)
	{
		cin >> fold[i];
	}

	cin >> H;
}

void solve()
{
	anchor[TOP] = 0;
	anchor[BOT] = (1 << K) - 1;
	anchor[LEFT] = 0;
	anchor[RIGHT] = (1 << K) - 1;

	for (int i = 0; i < 2 * K; i++)
	{
		char dir = fold[i];
		switch (dir) {
		case 'R':
			anchor[LEFT] = (anchor[RIGHT] + anchor[LEFT]) / 2 + 1;
			break;
		case 'L':
			anchor[RIGHT] = (anchor[RIGHT] + anchor[LEFT]) / 2;
			break;
		case 'D':
			anchor[TOP] = (anchor[TOP] + anchor[BOT]) / 2 + 1;
			break;
		case 'U':
			anchor[BOT] = (anchor[TOP] + anchor[BOT]) / 2;
			break;
		}
	}

	holes[anchor[TOP]][anchor[LEFT]] = H;

	for (int i = 0; i < 2 * K; i++)
	{
		char dir = fold[2 * K - 1 - i];

		switch (dir) {
		case 'R':
			new_anchor[TOP] = anchor[TOP]; new_anchor[BOT] = anchor[BOT];
			new_anchor[LEFT] = 2 * anchor[LEFT] - anchor[RIGHT] - 1;
			new_anchor[RIGHT] = anchor[LEFT] - 1;
			unfold(dir);
			anchor[LEFT] = new_anchor[LEFT];
			break;
		case 'L':
			new_anchor[TOP] = anchor[TOP]; new_anchor[BOT] = anchor[BOT];
			new_anchor[LEFT] = anchor[RIGHT] + 1;
			new_anchor[RIGHT] = 2 * anchor[RIGHT] - anchor[LEFT] + 1;
			unfold(dir);
			anchor[RIGHT] = new_anchor[RIGHT];
			break;
		case 'D':
			new_anchor[LEFT] = anchor[LEFT]; new_anchor[RIGHT] = anchor[RIGHT];
			new_anchor[BOT] = anchor[TOP] - 1;
			new_anchor[TOP] = 2 * anchor[TOP] - anchor[BOT] - 1;
			unfold(dir);
			anchor[TOP] = new_anchor[TOP];
			break;
		case 'U':
			new_anchor[LEFT] = anchor[LEFT]; new_anchor[RIGHT] = anchor[RIGHT];
			new_anchor[TOP] = anchor[BOT] + 1;
			new_anchor[BOT] = 2 * anchor[BOT] - anchor[TOP] + 1;
			unfold(dir);
			anchor[BOT] = new_anchor[BOT];
			break;
		}
	}
}

void unfold(char dir)
{
	switch (dir)
	{
	case 'R':
		for (int i = new_anchor[TOP]; i <= new_anchor[BOT]; i++)
		{
			for (int j = new_anchor[LEFT]; j <= new_anchor[RIGHT]; j++)
			{
				holes[i][j] = new_hole(dir, holes[i][2 * new_anchor[RIGHT] - j + 1]);
			}
		}
		break;
	case 'L':
		for (int i = new_anchor[TOP]; i <= new_anchor[BOT]; i++)
		{
			for (int j = new_anchor[LEFT]; j <= new_anchor[RIGHT]; j++)
			{
				holes[i][j] = new_hole(dir, holes[i][2 * new_anchor[LEFT] - j - 1]);
			}
		}
		break;
	case 'D':
		for (int i = new_anchor[TOP]; i <= new_anchor[BOT]; i++)
		{
			for (int j = new_anchor[LEFT]; j <= new_anchor[RIGHT]; j++)
			{
				holes[i][j] = new_hole(dir, holes[2 * new_anchor[BOT] - i + 1][j]);
			}
		}
		break;
	case 'U':
		for (int i = new_anchor[TOP]; i <= new_anchor[BOT]; i++)
		{
			for (int j = new_anchor[LEFT]; j <= new_anchor[RIGHT]; j++)
			{
				holes[i][j] = new_hole(dir, holes[2 * new_anchor[TOP] - i - 1][j]);
			}
		}
		break;
	}
}

int new_hole(char dir, int hole)
{
	if (dir == 'L' || dir == 'R')
	{
		if (hole == 0) { return 1; }
		else if (hole == 1) { return 0; }
		else if (hole == 2) { return 3; }
		else if (hole == 3) { return 2; }
	}
	else
	{
		if (hole == 0) { return 2; }
		else if (hole == 1) { return 3; }
		else if (hole == 2) { return 0; }
		else if (hole == 3) { return 1; }
	}
}