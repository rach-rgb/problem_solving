#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<vector<int>> board;
vector<int> virus;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = { 0, 0, -1, 1};

bool inRange(int x, int y){
    return ((0<=x)&&(x<N))&&((0<=y)&&(y<M));
}

typedef struct _walls {
    int loc[3] = {0, 1, 2};

    int* new_walls(){
        int mx = N * M - 1;

        if(loc[2] == mx)
        {
            if(loc[1] == mx - 1)
            {
                if(loc[0] == mx - 2){
                    return NULL; // ends
                }
                else{
                    loc[0]++;
                    loc[1] = loc[0] + 1;
                    loc[2] = loc[1] + 1;
                    return loc;
                }
            } else {
                loc[1]++;
                loc[2] = loc[1] + 1;
            }
        } else {
            loc[2]++;
        }

        return loc;
    }
} walls;

int get_safety(vector<vector<int>>& board)
{
    int ret = 0;

    for(int i = 0; i < virus.size(); i++){
        int x = virus[i] / M, y = virus[i] % M;

        queue<pair<int, int>> q;
        q.push(pair<int, int>(x, y));
        while(!q.empty())
        {
            pair<int, int> c = q.front();
            x = c.first;
            y = c.second;
            q.pop();

            for(int d = 0; d < 4; d++){
                int nx = x + dx[d], ny = y + dy[d];

                if(inRange(nx, ny) && (board[nx][ny]==0))
                {
                    board[nx][ny] = 2;
                    q.push(pair<int, int>(nx, ny));
                }
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j]==0){ ret++; }
        }
    }

    return ret;
}

int solve(){
    int ret = 0;

    walls w;

    int* loc = w.loc;
    while(loc != NULL){
        // cout << loc[0] << loc[1] << loc[2] << endl;

        bool f = true;
        for(int i = 0; i < 3; i++){
            int x = loc[i]/M, y = loc[i]%M;
            if(board[x][y]!=0){ f = false; break; }
        }
        if(!f){ loc = w.new_walls(); continue; }

        vector<vector<int>> nboard(board);
        for(int i = 0; i < 3; i++){
            int x = loc[i]/M, y = loc[i]%M;
            nboard[x][y] = 1;
        }

        int result = get_safety(nboard);
        ret = (ret > result) ? ret : result;

        loc = w.new_walls();
    }

    return ret;
}

int main(){
    cin >> N >> M;

    board = vector<vector<int>>(N, vector<int>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];

            if(board[i][j]==2){
                virus.push_back(i*M+j);
            }
        }
    }

    cout << solve() << endl;

    return 0;
}
