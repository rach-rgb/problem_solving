#include <vector>
#include <iostream>
using namespace std;

int main(){
	int N;
	cin >> N;

	vector<vector<pair<int, int>>> tasks(N + 1);
	for(int i = 1; i <= N; i++){
		int T, P;
		cin >> T >> P;

		int lastDay = T + i - 1;
		if(lastDay <= N){
			tasks[lastDay].push_back(pair<int, int>(T, P));
		}
	}

	vector<int> DP(N + 1, 0);
	for(int i = 1; i <= N; i++){
		DP[i] = DP[i - 1];
		for(int j = 0; j < tasks[i].size(); j++){
			int t = tasks[i][j].first;
			int p = tasks[i][j].second;

			int nP = DP[i-t] + p;
			DP[i] = (DP[i] > nP) ? DP[i] : nP;
		}
	}

	cout << DP[N]<< endl;

	return 0;
}
