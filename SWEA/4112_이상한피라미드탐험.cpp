#include <iostream>
#include <cmath>
using namespace std;

void solve();

int A, B;
int result;

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> A >> B;
		solve();
		cout << "#" << i << " " << result << endl;
	}

	return 0;
}

void solve()
{
	result = 0;

	if (A > B) { int tmp = A; A = B; B = tmp; } // make A <= B

	int A_r, B_r;
	double A_f, B_f;
	bool A_find = false, B_find = false;

	A_f = (-1 + sqrt(8 * A + 1)) / 2.0;
	A_r = (int)A_f;
	if (A_r != A_f) { A_r++; }

	B_f = (-1 + sqrt(8 * B + 1)) / 2.0;
	B_r = (int)B_f;
	if (B_r != B_f) { B_r++; }

	if (A_r == B_r) { result = B - A; }
	else
	{
		int mim, mam;

		mim = A;
		for (int i = A_r; i < B_r; i++)
		{
			mim += i;
		}
		mam = mim + (B_r - A_r);

		if (B < mim)
		{
			result = (B_r - A_r) + (mim - B);
		}
		else if (mam < B)
		{
			result = (B_r - A_r) + (B - mam);
		}
		else
		{
			result = B_r - A_r;
		}
	}
}