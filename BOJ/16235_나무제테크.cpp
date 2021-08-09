#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define MAXN (10)

int N, M, K;
int A[MAXN][MAXN];
int add[MAXN][MAXN];
int field[MAXN][MAXN];
int dx[8] = {-1, -1, -1, 0, 0, +1, +1, +1};
int dy[8] = {-1, 0, +1, -1, +1, -1, 0, +1};
deque<int> trees[MAXN][MAXN];
int newTree[MAXN][MAXN];

bool inRange(int x, int y){
	return ((x >= 0) && (x < N)) && ((y >= 0) && (y < N));
}

int solve(){
	for(int t = 0; t < K; t++){
		for(int x = 0; x < N; x++){
			for(int y = 0; y < N; y++){
				add[x][y] = 0;

				// cout << "DEBUG: " << trees[0][0].size() << endl;
				deque<int>::iterator it;
				for(it = trees[x][y].begin(); it != trees[x][y].end(); it++)
				{
					// cout << "DEBUG2: " << trees[0][0].size() << endl;
					// cout << "DEBUG2: " << *(it) << endl;
					int age = *(it);
					if(age <= field[x][y])
					{
						field[x][y] -= age;
						(*it)++;

						if((age+1)%5 == 0){ // reproduce
							for(int k = 0; k < 8; k++){
								if(inRange(x+dx[k], y + dy[k])){
									newTree[x+dx[k]][y+dy[k]]++;
								}
							}
						}
					} else {
						// erase from back
						while(trees[x][y].size() != (it-trees[x][y].begin())){
							add[x][y] += (trees[x][y].back()) / 2;
							trees[x][y].pop_back();
						}
						break;
					}
					// cout << "DEBUG3: " << trees[0][0].size() << endl;
					// cout << "DEBUG3: " << *(it) << endl;
				}
			}
		}
		// cout << "DEBUG4: " << trees[0][0].size() << endl;
		for(int x= 0; x < N; x++){
			for(int y = 0; y < N; y++){
				// field info
				field[x][y] += (A[x][y] + add[x][y]);

				// tree info
				while(newTree[x][y] > 0)
				{
					trees[x][y].push_front(1);

					newTree[x][y]--;
				}

				/* DEBUG
				list<int>::iterator it;
				for(it = trees[x][y].begin(); it != trees[x][y].end(); it++){
					cout << x << y << *(it) << endl;
				} */		
			}
		}
	}

	int result = 0;
	for(int x= 0; x < N; x++){
		for(int y = 0; y < N; y++){
			result += trees[x][y].size();
		}
	}

	return result;
}

int main(){
	ios::sync_with_stdio(false);

	cin >> N >> M >> K;

	// field
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			field[i][j] = 5;
		}
	}

	// A
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> A[i][j];
		}
	}

	// tree information
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			newTree[i][j] = 0;
		}
	}

	for(int i = 0; i < M; i++){
		int x, y, z;
		cin >> x >> y >> z;
		trees[x-1][y-1].push_back(z);
	}

	cout << solve() << endl;

	return 0;
}
