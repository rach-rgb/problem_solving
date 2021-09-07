#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXR (9999)

int N, M, K;
vector<vector<int>> board;
vector<vector<int>> rotation;
const int dx[5] = {1, 0, -1, 0, 1};
const int dy[5] = {0, 1, 0, -1, 0};
const int rdx[5] = {0, 1, 0, -1, 0};
const int rdy[5] = {1, 0, -1, 0, 1};

void rotate(vector<vector<int>>& board, int ix, int iy, int side, bool reverse){

	queue<int> q;
	int x = ix, y = iy;
	int d = 0, count = 0;

	int pv = board[x][y];
	if((count+1)%side==0){ d++; }
	if(!reverse){
		x = x + rdx[d];
		y = y + rdy[d];
	} else {
		x = x + dx[d];
		y = y + dy[d];
	}

	count = 1;

	for(count; count < 4 * side + 1; count++){
		int tmp = board[x][y];
		board[x][y] = pv;
		pv = tmp;

		if((count+1)%side==0){ count++; d++; }
		if(!reverse){
			x = x + rdx[d];
			y = y + rdy[d];
		} else {
			x = x + dx[d];
			y = y + dy[d];
		}
	}
}

void rotate(vector<vector<int>>& board, vector<int> info, bool reverse){
	for(int i = 1; i <= info[2]; i++){
		int x = info[0] - i - 1, y = info[1] - i - 1;
		int side = 2 * i + 1;

		rotate(board, x, y, side, reverse);
	}
}

int calculate(vector<bool> used, vector<vector<int>>& board){
	int result = MAXR;

	for(int i = 0; i < K; i++){
		if(!used[i]){
			rotate(board, rotation[i], false);

			used[i] = true;
			int r = calculate(used, board);
			result = (result < r) ? result : r;

			// restore
			used[i] = false;
			rotate(board, rotation[i], true);
		}
	}

	// base
	if(result == MAXR){
		for(int i = 0; i < N; i++){
			int sum = 0;
			for(int j = 0; j < M; j++){
				sum += board[i][j];
				if(sum > result){ break; } // early terminates
			}
			result = (result < sum) ? result : sum;
		}
	}

	return result;
}

int solve(){
	vector<bool> used(K, false);

	return calculate(used, board);
}

int main(){
	ios::sync_with_stdio(false);

	cin >> N >> M >> K;
	board = vector<vector<int>>(N, vector<int>(M));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> board[i][j];
		}
	}

	rotation = vector<vector<int>>(K, vector<int>(3));
	for(int i = 0; i < K; i++){
		cin >> rotation[i][0] >> rotation[i][1] >> rotation[i][2];
	}

	cout << solve() << endl;
	return 0;
}
