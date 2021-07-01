#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 8

int N;
vector<vector<bool>> board;
int id[2][MAXN][MAXN];
bool graph[MAXN * MAXN][MAXN * MAXN];
vector<int> ids[2];
vector<bool> visited;
vector<int> matched;

const int dx[2] = { 1, 1 };
const int dy[2] = { 1, -1 };

void input() {
	cin >> N;

	// initialize
	board = vector<vector<bool>>(N, vector<bool>(N));
	memset(graph, false, sizeof(graph));
	memset(id, -1, sizeof(id));
	ids[0].clear(); ids[1].clear();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			char x;
			cin >> x;
			if (x == '.')
			{
				board[i][j] = true;
			}
			else {
				board[i][j] = false;
			}
		}
	}
}

bool inRange(int x, int y) {
	if ((x < 0) || (x >= N)) { return false; }
	else { return ((y >= 0) && (y < N)); }
}

void construct() {
	for (int d = 0; d < 2; d++) {
		for (int x = 0; x < N; ++x) {
			for (int y = 0; y < N; ++y) {
				if (board[x][y])
				{
					int nx = x - dx[d], ny = y - dy[d];
					if (inRange(nx, ny) && id[d][nx][ny] != -1) {
						id[d][x][y] = id[d][nx][ny];
					}
					else {
						id[d][x][y] = ids[0].size() + ids[1].size();
						ids[d].push_back(id[d][x][y]);
					}

					if (d == 1) { // create dir1 -> dir2 edge
						int id1 = id[0][x][y], id2 = id[1][x][y];
						if (id1 != -1) {
							graph[id1][id2] = true;
						}
					}
				}
			}
		}
	}
}

bool DFS(int a) {
	if (visited[a]) { return false; }

	visited[a] = true;

	for (int i = 0; i < ids[1].size(); i++) {
		int b = ids[1][i];

		if (graph[a][b]) {
			if ((matched[b] == -1) || (DFS(matched[b]))) {
				matched[b] = a;
				matched[a] = b;
				return true;
			}
		}
	}

	return false;
}

int solve() {
	int result = 0;
	construct();

	matched = vector<int>(ids[0].size() + ids[1].size(), -1);

	for (int i = 0; i < ids[0].size(); i++) {
		int a = ids[0][i];
		if (matched[a]==-1) {
			visited = vector<bool>(ids[0].size() + ids[1].size());

			if(DFS(a))
			{
				result++;
			}
		}
	}
	
	return result;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		input();
		cout << solve() << endl;
	}

	return 0;
}
