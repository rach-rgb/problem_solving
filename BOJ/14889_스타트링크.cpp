#include <iostream>
#include <vector>
using namespace std;

#define MAXN (20)
#define INF (987654321)

int N;
short point[MAXN][MAXN];


int solve(){
	int ret = INF;

	unsigned int begin = (1 << (N / 2)) - 1, end = begin << (N / 2);
	for(unsigned int comb = begin; comb <= end; comb+=2){
		if(__builtin_popcount(comb)==N/2){ // valid combination
			// calculate points
			unsigned int teamT = 0, teamF = 0;
			for(int i = 0; i < N; i++){
				bool teamI = ((comb & (1 << i)) > 0) ? true : false;
				for(int j = 0; j < N; j++){
					bool teamJ = ((comb & (1 << j)) > 0) ? true : false;

					if(teamI==teamJ){
						if(teamI){ // add to teamT
							teamT += point[i][j];
						} else {
							teamF += point[i][j];
						}
					}
				}
			}
			
			unsigned int diff = (teamT > teamF) ? teamT - teamF : teamF - teamT;
			// cout << teamT << " " << teamF << " " << diff << endl;
			ret = (ret < diff) ? ret : diff;
		}
	}

	return ret;
}

int main(){
	ios::sync_with_stdio(false);

	cin >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> point[i][j];
		}
	}

	cout << solve() << endl;

	return 0;
}
