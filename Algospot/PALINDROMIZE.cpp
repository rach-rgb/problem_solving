#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXS (100000)

void solve();
void failure();

string S;
string SR; // reversed string
int fail[MAXS]; // fail function for reversd string
int result;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> S;
		SR = S;
		reverse(SR.begin(), SR.end());
		solve();
		cout << result << endl;
	}

	return 0;
}

// construct failure function
void failure()
{
	memset(fail, 0, sizeof(int) * MAXS);

	int begin = 1, matched = 0;
	while (begin + matched < SR.size())
	{
		if (SR[begin + matched] == SR[matched])
		{
			matched++;
			fail[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
			{
				begin++;
			}
			else
			{
				begin = begin + matched - fail[matched - 1];
				matched = fail[matched - 1];
			}
		}
	}
}

void solve()
{
	result = 0;

	int begin = 0, matched = 0;
	while (begin < S.size())
	{
		if ((matched < S.size()) && (S[begin + matched] == SR[matched]))
		{
			matched++;
			if (begin + matched == S.size()) { break; }
		}
		else
		{
			if (matched == 0)
			{
				begin++;
			}
			else
			{
				begin = begin + matched - fail[matched - 1];
				matched = fail[matched - 1];
			}
		}
	}
	result = S.size() * 2 - matched;
}