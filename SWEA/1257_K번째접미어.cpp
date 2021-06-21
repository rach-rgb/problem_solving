#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define MAXK 400

void solve();

string input;
string result;
string suffices[MAXK];
int K;

int main(void)
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> K >> input;
		solve();
		cout << "#" << i << " " << result << endl;
	}
}

void solve()
{
	int len = input.length();
	if (K > len) {
		result = "none"; 
		return;
	}

	for (int i = 0; i < len; i++)
	{
		suffices[i] = input.substr(i, len - i);
	}

	sort(suffices, suffices + len);


	result = suffices[K-1];
}