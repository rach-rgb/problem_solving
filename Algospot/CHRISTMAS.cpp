#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int waysToBuy(const vector<int>& psum, int K)
{
	const int MOD = 20091101;
	int result = 0;

	vector<long long> count(K, 0);
	for (int i = 0; i < psum.size(); i++)
	{
		count[psum[i]]++;
	}

	for (int i = 0; i < K; i++)
	{
		if (count[i] >= 2)
		{
			result = (result + ((count[i] * (count[i] - 1)) / 2)) % MOD;
		}
	}

	return result;
}

int maxBuys(const vector<int>& psum, int K)
{
	vector<int> dp(psum.size(), 0);
	vector<int> prev(K, -1);

	for (int i = 0; i < psum.size(); i++)
	{
		int ret, val1 = 0, val2 = 0;

		// don't buy i
		if (i > 0) { val1 = dp[i - 1]; }

		// buy i
		int loc = prev[psum[i]];
		if (loc != -1)
		{
			val2 = 1 + dp[loc];
		}
		else if (psum[i] == 0) { val2 = 1; }

		ret = (val1 > val2) ? val1 : val2;
		dp[i] = ret;

		prev[psum[i]] = i;
	}

	return dp.back() - 1;
}

int main(void)
{
	ios::sync_with_stdio(false);

	int C;
	cin >> C;

	for (int i = 0; i < C; i++)
	{
		int N, K;
		cin >> N >> K;

		vector<int> v(N);
		for (int i = 0; i < N; i++)
		{
			cin >> v[i];
		}

		vector<int> psum(N + 1);
		psum[0] = 0;

		for (int i = 1; i <= N; i++)
		{
			psum[i] = (psum[i - 1] + v[i - 1]) % K;
		}

		cout << waysToBuy(psum, K) << " " << maxBuys(psum, K) << endl;
	}
}