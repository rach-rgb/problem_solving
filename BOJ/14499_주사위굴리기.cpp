#include <iostream>
#include <vector>
using namespace std;

int N, M, X, Y;
vector<vector<int>> board;
vector<int> order;

vector<int> dice(6, 0);

const int oppos[6] = {5, 4, 3, 2, 1, 0};
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};

bool inRange(int x, int y){
    return ((0<=x) && (x<N)) && ((0<=y) && (y<M));
}

void moveDice(int d)
{
    vector<int> tmp = dice;
    if(d == 0){
        dice[0] = tmp[3];
        dice[2] = tmp[0];
        dice[3] = tmp[5];
        dice[5] = tmp[2];
    } else if(d == 1){
        dice[0] = tmp[2];
        dice[2] = tmp[5];
        dice[3] = tmp[0];
        dice[5] = tmp[3];
    }else if(d == 2){
        dice[0] = tmp[4];
        dice[1] = tmp[0];
        dice[4] = tmp[5];
        dice[5] = tmp[1];
    }else{ // d == 3
        dice[0] = tmp[1];
        dice[1] = tmp[5];
        dice[4] = tmp[0];
        dice[5] = tmp[4];
    }

    return;
}

void play(){
    for(int i = 0; i < order.size(); i++){
        int dir = order[i];

        int nx = X + dx[dir], ny = Y + dy[dir];

        if(!inRange(nx, ny)){ continue; }

        moveDice(dir);

        // print top
        cout << dice[0] << endl;

        // update bottom
        if(board[nx][ny]==0){ board[nx][ny] = dice[5]; }
        else{ dice[5] = board[nx][ny]; board[nx][ny] = 0; }

        // update
        X = nx; Y = ny;
    }
}

int main(){
    int k;

    cin >> N >> M >> X >> Y;
    cin >> k;

    board = vector<vector<int>>(N, vector<int>(M));
    order = vector<int>(k);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < k; i++){
        cin >> order[i];
        order[i]--;
    }

    play();

    return 0;
}
