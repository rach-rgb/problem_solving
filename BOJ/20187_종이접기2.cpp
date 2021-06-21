#include <iostream>
using namespace std;

#define MAXK 8
#define TOP 0
#define BOT 1
#define LEFT 2 
#define RIGHT 3

void input();
void solve();
void output1();
void output2();
void output3();
void output4();

int K, H;
char fold[MAXK * 2];
int anchor[4];
int result;

int main()
{
	input();
	solve();
	if (result == 1) { output1(); }
	else if (result == 2) { output2(); }
	else if (result == 3) { output3(); }
	else { output4(); }

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

	int x = anchor[TOP];
	int y = anchor[LEFT];

	if ((x % 2 == 0) && (y % 2 == 0))
	{
		if (H == 0) { result = 1; }
		else if (H == 1) { result = 2; }
		else if (H == 2) { result = 4; }
		else { result = 3; }
	}
	else if ((x % 2 != 0) && (y % 2 == 0))
	{
		if (H == 0) { result = 4; }
		else if (H == 1) { result = 3; }
		else if (H == 2) { result = 1; }
		else { result = 2; }
	}
	else if ((x % 2 == 0) && (y % 2 != 0))
	{
		if (H == 0) { result = 2; }
		else if (H == 1) { result = 1; }
		else if (H == 2) { result = 3; }
		else { result = 4; }
	}
	else //(x % 2 != 0) && (y % 2 != 0)
	{
		if (H == 0) { result = 3; }
		else if (H == 1) { result = 4; }
		else if (H == 2) { result = 2; }
		else { result = 1; }
	}
}

void output1() {
	// 0 1
	// 2 3
	for (int i = 0; i < (1 << K); i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 0 << " "; }
				else { cout << 1 << " "; }
			}
		}
		else
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 2 << " "; }
				else { cout << 3 << " "; }
			}
		}
		cout << endl;
	}
}

void output2() {
	// 1 0
	// 3 2
	for (int i = 0; i < (1 << K); i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 1 << " "; }
				else { cout << 0 << " "; }
			}
		}
		else
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 3 << " "; }
				else { cout << 2 << " "; }
			}
		}
		cout << endl;
	}
}

void output3() {
	// 3 2
	// 1 0
	for (int i = 0; i < (1 << K); i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 3 << " "; }
				else { cout << 2 << " "; }
			}
		}
		else
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 1 << " "; }
				else { cout << 0 << " "; }
			}
		}
		cout << endl;
	}
}

void output4() {
	// 2 3
	// 0 1
	for (int i = 0; i < (1 << K); i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 2 << " "; }
				else { cout << 3 << " "; }
			}
		}
		else
		{
			for (int j = 0; j < (1 << K); j++)
			{
				if (j % 2 == 0) { cout << 0 << " "; }
				else { cout << 1 << " "; }
			}
		}
		cout << endl;
	}
}