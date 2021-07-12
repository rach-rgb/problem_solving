/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/
#include <iostream>
#include <algorithm>


using namespace std;

#define MAXN (200000)

int amenu[MAXN];
int bmenu[MAXN];

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */

	 // freopen("input.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		int N, K;
		cin >> N >> K;

		for (int i = 0; i < N; i++) {
			cin >> amenu[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> bmenu[i];
		}

		sort(amenu, amenu + N);
		sort(bmenu, bmenu + N);

		int mval = -1;
		for (int i = 0; i < K; i++) {
			int val = amenu[i] + bmenu[K - i - 1];

			mval = (mval > val) ? mval : val;
		}

		Answer = mval;

		/////////////////////////////////////////////////////////////////////////////////////////////

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
