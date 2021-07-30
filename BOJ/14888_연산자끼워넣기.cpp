#include <iostream>
#include <cstring>
using namespace std;

#define MAXN (11)
#define PINF (1987654321)
#define NINF (-1987654321)

int N;
int A[MAXN];
int DP[MAXN][MAXN][MAXN][MAXN][MAXN];
int op[4];

int DFS(int i, int a, int b, int c, int d, bool flag){
	int& ret = DP[i][a][b][c][d];
	if(ret!=-1){ return ret; }

	// else
	int mx, val, prev;
	if(flag){ mx  = NINF; }
	else{ mx = PINF; }

	if(a+1 <= op[0]){ 
		prev = DFS(i-1, a+1, b, c, d, flag);
		val = prev + A[i];

		if(flag){
			mx = (mx > val) ? mx : val;	
		} else {
			mx = (mx < val) ? mx : val;	
		}	
	}

	if(b+1 <= op[1]){ 
		prev = DFS(i-1, a, b + 1, c, d, flag);
		val = prev - A[i];

		if(flag){
			mx = (mx > val) ? mx : val;	
		} else {
			mx = (mx < val) ? mx : val;	
		}	
	}

	if(c+1 <= op[2]){ 
		prev = DFS(i-1, a, b, c+1, d, flag);
		val = prev * A[i];

		if(flag){
			mx = (mx > val) ? mx : val;	
		} else {
			mx = (mx < val) ? mx : val;	
		}	
	}

	if(d+1 <= op[3]){ 
		prev = DFS(i-1, a, b, c, d + 1, flag);
		val = prev / A[i];

		if(flag){
			mx = (mx > val) ? mx : val;	
		} else {
			mx = (mx < val) ? mx : val;	
		}	
	}

	ret = mx;

	return ret;
}

int main(){
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	for(int i = 0; i < 4; i++){
		cin >> op[i];
	}

	memset(DP, -1, sizeof(DP));
	DP[0][op[0]][op[1]][op[2]][op[3]] = A[0];

	cout << DFS(N-1, 0, 0, 0, 0, true) << endl;

	memset(DP, -1, sizeof(DP));
	DP[0][op[0]][op[1]][op[2]][op[3]] = A[0];

	cout << DFS(N-1, 0, 0, 0, 0, false) << endl;

	return 0;
}
