#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
vector<vector<int>> board;
int conditioner = 99;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};

bool inRange(int x, int y){
    return ((0 <= x) && (x < R)) && ((0 <= y) && (y < C));
}

int solve(){
    while(T--){
        // disperse
        vector<pair<int, pair<int, int>>> dusts;
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++)
            {
                if(board[i][j] > 0)
                {
                    int x = i, y = j;
                    int dust = 0;
                    for(int d = 0; d < 4; d++){
                        int nx = x + dx[d], ny = y + dy[d];

                        if(inRange(nx, ny) && (board[nx][ny] != -1))
                        {
                            dusts.push_back(pair<int, pair<int, int>>(board[i][j]/5, pair<int, int>(nx, ny)));
                            dust += board[i][j] / 5;
                        }
                    }
                    board[i][j] -= dust;
                }
            }
        }

        // update
        for(int i = 0; i < dusts.size(); i++){
            board[dusts[i].second.first][dusts[i].second.second] += dusts[i].first;
        }

        // air conditional
        // top
        int x = conditioner, y = 0, d = 0;
        int nx = x + dx[d], ny = y + dy[d];
        int prev = 0;

        while(board[nx][ny] != -1)
        {
            // cout << nx << " " << ny << " " << d << endl;
            int tmp = board[nx][ny];
            board[nx][ny] = prev;
            prev = tmp;

            if(!inRange(nx + dx[d], ny + dy[d])) // change direction
            {
                d++;
                if(d==4){ d = 0;}
            }

            nx = nx + dx[d];
            ny = ny + dy[d];
        }

        // bottom
        y = 0, x = conditioner + 1, d = 0;
        nx = x + dx[d], ny = y + dy[d];
        prev = 0;

        while(board[nx][ny] != -1)
        {
            int tmp = board[nx][ny];
            board[nx][ny] = prev;
            prev = tmp;

            if(!inRange(nx + dx[d], ny + dy[d])) // change direction
            {
                d--;
                if(d<0){ d = 3; }
            }

            nx = nx + dx[d];
            ny = ny + dy[d];
        }
    }

    // check
    int result = 0;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(board[i][j] > 0){
                result += board[i][j];
            }
        }
    }

    return result;
}

int main(){
    cin >> R >> C >> T;

    board = vector<vector<int>>(R, vector<int>(C));

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> board[i][j];

            if((board[i][j]==-1) && (conditioner == 99)){
                conditioner = i;
            }
        }
    }

    cout << solve() << endl;

    return 0;
}
