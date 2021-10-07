#include <iostream>
#include <vector>
using namespace std;

int N, M;
int X, Y, D;
vector<vector<int>> board;

// North, East, South, West
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

bool inRange(int x, int y){
    return ((0<=x)&&(x<N)) && ((0<=y)&&(y<M));
}

int solve(){
    while(1){
        board[X][Y] = -1;

        bool f = false;
        for(int i = 0; i < 4; i++){
            D--;
            if(D==-1){ D = 3; }

            int nX = X + dx[D], nY = Y + dy[D];
            if(inRange(nX, nY)&&(board[nX][nY]==0))
            {
                X = nX, Y = nY;
                f = true;
                break;
            }
        }

        if(f){ continue; }
        else{
            int nX = X - dx[D], nY = Y - dy[D];

            if(inRange(nX, nY) && (board[nX][nY]!=1))
            {
                X = nX;
                Y = nY;
            } else {
                break;
            }
        }
    }

    int ret = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j]==-1){
                ret++;
            }
        }
    }

    return ret;
}

int main(){
    ios::sync_with_stdio(false);

    cin >> N >> M;
    cin >> X >> Y >> D;

    board = vector<vector<int>>(N,vector<int>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }

    cout << solve() << endl;

    return 0;
}
