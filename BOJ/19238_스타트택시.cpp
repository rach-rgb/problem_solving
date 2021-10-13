#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF (987654321)

int N, M, F;
int X, Y;
vector<vector<int>> board;
vector<vector<int>> dist;
vector<pair<int, int>> goal;
vector<int> cost;

const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };

bool inRange(int x, int y) {
	return ((0 <= x) && (x < N)) && ((0 <= y) && (y < N));
}

int get_cost(int x, int y, int gx, int gy) {
	dist = vector<vector<int>>(N, vector<int>(N, INF));

	queue<pair<int, int>> q;
	q.push(pair<int, int>(x, y));
	dist[x][y] = 0;

	bool done = false;

	while (!q.empty() && (!done))
	{
		pair<int, int> cur = q.front();
		int x = cur.first;
		int y = cur.second;
		int cdist = dist[x][y];
		q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d], ny = y + dy[d];

			if (inRange(nx, ny) && (board[nx][ny] != 1))
			{
				if (dist[nx][ny] > cdist + 1)
				{
					dist[nx][ny] = cdist + 1; //update
					if ((nx == gx) && (ny == gy)) { done = true; break; }

					q.push(pair<int, int>(nx, ny));
				}
			}
		}
	}

	return dist[gx][gy];
}

vector<int> find_customer(int x, int y) {
	vector<int> r(3);
	r[0] = -1;
	int ret_dist = INF;

	dist = vector<vector<int>>(N, vector<int>(N, INF));

	queue<pair<int, int>> q;
	q.push(pair<int, int>(x, y));
	dist[x][y] = 0;

	bool done = false;

	int idx = board[X][Y] - 2;
	if ((0 <= idx) && (idx < M))
	{
		r[0] = idx;
		r[1] = X;
		r[2] = Y;
		return r;
	}

	while (!q.empty() && (!done))
	{
		pair<int, int> cur = q.front();
		int x = cur.first;
		int y = cur.second;
		int cdist = dist[x][y];
		q.pop();

		if (cdist > ret_dist) { break; }

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d], ny = y + dy[d];

			if (inRange(nx, ny) && (board[nx][ny] != 1))
			{
				if (dist[nx][ny] > cdist + 1)
				{
					dist[nx][ny] = cdist + 1; //update
					q.push(pair<int, int>(nx, ny));

					int idx = board[nx][ny] - 2;
					if ((0 <= idx) && (idx < M))
					{
						if (ret_dist > dist[nx][ny])
						{
							ret_dist = dist[nx][ny];
							r[0] = idx;
							r[1] = nx;
							r[2] = ny;
						}
						else if (ret_dist == dist[nx][ny]) { // ret_dist == dist[nx][ny]
							if ((r[1] > nx) || ((r[1] == nx) && (r[2] > ny))) {
								r[0] = idx;
								r[1] = nx;
								r[2] = ny;
							}
						}
					}
				}
			}
		}
	}

	return r;
}

int solve() {
	while (1) {
		vector<int> ret = find_customer(X, Y);
		if (ret[0] == -1) { break; }
		else if (F - dist[ret[1]][ret[2]] - cost[ret[0]] < 0)
		{
			return -1;
		}
		else {
			F +=  cost[ret[0]] - dist[ret[1]][ret[2]];
			X = goal[ret[0]].first;
			Y = goal[ret[0]].second;

			cost[ret[0]] = INF;
			board[ret[1]][ret[2]] = 0;
		}
	}

	for (int i = 0; i < M; i++) {
		if (cost[i] != INF) { return -1; }
	}

	return F;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N >> M >> F;
	board = vector<vector<int>>(N, vector<int>(N));
	goal = vector<pair<int, int>>(M);
	cost = vector<int>(M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	cin >> X >> Y;
	X--; Y--;

	for (int i = 0; i < M; i++) {
		int x, y, gx, gy;
		cin >> x >> y >> gx >> gy;

		x--; y--; gx--; gy--;

		board[x][y] = i + 2;
		goal[i] = pair<int, int>(gx, gy);
		cost[i] = get_cost(x, y, gx, gy);
		if (cost[i] == INF) { cout << -1 << "\n"; return 0; }
	}

	cout << solve() << "\n";

	return 0;
}
