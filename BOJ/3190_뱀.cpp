#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, K;
queue<pair<int, int>> snake;
int D; // east: 0, clockwise
vector<vector<int>> board; // 0: empty 1: apple -1: snake
vector<pair<int, bool>> turn;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

bool inRange(int x, int y){
    return ((0<=x) && (x<N)) && ((0<=y) && (y<N));
}

bool isCollide(int x, int y)
{
    return board[x][y]==-1;
}

int solve(){
    int T = 1;
    int tx = 0;

    int nX = snake.front().first + dx[D];
    int nY = snake.front().second + dy[D];

    while(inRange(nX, nY) && !isCollide(nX, nY)){
        if(board[nX][nY]!=1) // not apple
        {
            board[snake.front().first][snake.front().second] = 0;
            snake.pop();
        }

        board[nX][nY] = -1;
        snake.push(pair<int, int>(nX, nY));

        if((tx < turn.size())&&(turn[tx].first==T))
        {
            if(turn[tx].second){ D++; }
            else{ D--; }

            if(D==-1){ D = 3; }
            if(D==4){ D = 0;}

            tx++;
        }

        // cout << T << " : " << snake.front().first << " " << snake.front().second << " ";
        // cout << snake.back().first << " " << snake.back().second << endl;

        T++;

        nX = nX + dx[D];
        nY = nY + dy[D];
    }

    return T;
}

int main(){
    ios::sync_with_stdio(false);

    cin >> N >> K;
    
    board = vector<vector<int>>(N, vector<int>(N, 0));
    for(int i = 0; i < K; i++){
        int x, y;
        cin >> x >> y;
        board[x-1][y-1] = 1;
    }

    int L;
    cin >> L;

    turn = vector<pair<int, bool>>(L);
    for(int i = 0; i < L; i++){
        int X; char C;
        cin >> X >> C;

        bool d;
        if(C=='L'){ d = false; }
        else if(C=='D'){ d = true; }

        turn[i].first = X;
        turn[i].second = d;
    }
    
    snake.push(pair<int, int>(0, 0));
    D = 0;
    board[0][0] = -1;

    cout << solve() << endl;
}
