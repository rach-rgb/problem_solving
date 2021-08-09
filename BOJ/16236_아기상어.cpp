#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN (20)
#define INF (500)

short N;
vector<vector<short>> board;
vector<vector<bool>> visited;
vector<vector<short>> dist;
short x, y;
short fsize;
short fcount;
const pair<int, int> fail(-1, -1);
const int dx[4] = { -1, 1, 0, 0};
const int dy[4] = { 0, 0, -1, 1};

bool inRange(int x, int y){
	return ((x>=0) && (x<N)) && ((y>=0) && (y<N));
}

pair<int, int> BFS(int x, int y){
	vector<pair<int, int>> cands;
	int mdist = INF;
	queue<pair<int, int>> q;

	q.push(pair<int, int>(x, y));

	while(!q.empty()){
		pair<int, int> cur = q.front();
		q.pop();

		if(visited[cur.first][cur.second]){ continue; }
		if(dist[cur.first][cur.second] > mdist - 1){ continue; }

		visited[cur.first][cur.second] = true;
		for(int i = 0; i < 4; i++){
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];

			if((!inRange(nx, ny)) || visited[nx][ny] || 
				(board[nx][ny] > fsize)){ continue; }
			else {
				dist[nx][ny] = dist[cur.first][cur.second] + 1;
				if((board[nx][ny] < fsize) && (board[nx][ny] != 0)){ // can eat
					cands.push_back(pair<int, int>(nx, ny));
					mdist = dist[nx][ny];
				}
				q.push(pair<int, int>(nx, ny));
			}
		}
	}

	if(cands.empty()){ return fail; }
	else{
		sort(cands.begin(), cands.end());
		return cands[0];
	}
}

int solve(){
	int time = 0;
	fsize = 2; fcount = 0;

	while(true){
		visited = vector<vector<bool>>(N, vector<bool>(N, false));
		dist = vector<vector<short>>(N, vector<short>(N, INF));
		dist[x][y] = 0;

		pair<int, int> fish = BFS(x, y);
		if(fish==fail){ break; } // no fish
		else {
			x = fish.first; y = fish.second;
			board[x][y] = 0; // erase fish
			time += dist[x][y];

			fcount++;
			if(fcount==fsize){
				fsize++;
				fcount =  0;
			}
		}

	}

	return time;
}

int main(){
	cin >> N;

	board = vector<vector<short>>(N, vector<short>(N));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> board[i][j];

			if(board[i][j]==9)
			{
				x = i; y = j;
				board[i][j] = 0;
			}
		}
	}

	cout << solve() << endl;

	return 0;
}
