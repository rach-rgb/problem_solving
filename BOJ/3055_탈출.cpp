#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXR (50)

int R, C;
int board[MAXR][MAXR];
int cost[MAXR][MAXR];
int Dx, Dy, Sx, Sy;
queue<pair<int, int>> w;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool inRange(int x, int y){
	return ((0<=x) && (x<R)) && ((0<=y) && (y<C));
}

bool isGoal(int x, int y){
	return (x==Dx) && (y==Dy);
}

// return -1 if impossible
int solve(){

	queue<pair<int, int>> q;
	q.push(pair<int, int>(Sx, Sy));
	cost[Sx][Sy] = 0;

	int t = 0;

	while((!q.empty()) && (cost[Dx][Dy]==-1)){
		t++;
		// cout << "time: " << t << endl;
		
		// beaver
		int qs = q.size();
		for(int i = 0; i < qs; i++)
		{
			int cx = q.front().first;
			int cy = q.front().second;
			q.pop();

			if(board[cx][cy]==1){ continue; } // skip
			// Debug
			// cout << "beaver: " << cx << " " << cy << endl;

			for(int d = 0; d < 4; d++){
				int nx = cx + dx[d];
				int ny = cy + dy[d];

				if(inRange(nx, ny) && (board[nx][ny]!=1) && board[nx][ny]!=3)
				{
					if((cost[nx][ny] == -1) || (cost[nx][ny] > cost[cx][cy] + 1))
					{
						cost[nx][ny] = cost[cx][cy] + 1;
						q.push(pair<int, int>(nx, ny));
					}
				}
			}
		}

		// water
		int ws = w.size();
		for(int i = 0; i < ws; i++){
			int cx = w.front().first;
			int cy = w.front().second;
			w.pop();

			// Debug
			// cout << "water: " << cx << " " << cy << endl;

			for(int d = 0; d < 4; d++){
				int nx = cx + dx[d];
				int ny = cy + dy[d];

				if(inRange(nx, ny) && (board[nx][ny]==0))
				{
					board[nx][ny] = 1;
					w.push(pair<int, int>(nx, ny));
				}
			}
		}
	}

	return cost[Dx][Dy];
}

int main(){
	cin >> R >> C;

	for(int r = 0; r < R; r++){
		for(int c = 0; c < C; c++){
			char x; cin >> x;

			if(x=='.'){ board[r][c] = 0; }
			else if(x=='*'){ board[r][c] = 1; w.push(pair<int, int>(r, c)); }
			else if(x=='D'){ board[r][c] = 2;  Dx = r; Dy = c; }
			else if(x=='S'){ board[r][c] = 0; Sx = r; Sy = c; }
			else{ board[r][c] = 3; }
		}
	}

	memset(cost, -1, sizeof(cost));

	int result = solve();
	if(result != -1){ cout << result << endl; }
	else{ cout << "KAKTUS" << endl; }

	return 0;
}
