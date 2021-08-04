#include <iostream>
#include <vector>
using namespace std;

#define MAXG 4
#define MAXT 8

int gear[MAXG][MAXT];
int top[MAXG] = {0, 0, 0, 0};
vector<bool> visited;

int left(int n)
{
	return gear[n][(top[n]+6) % MAXT];
}

int right(int n){
	return gear[n][(top[n]+2) % MAXT];
}

void rotate(int n, bool dir){
	// cout << "rotate " << n << " by " << dir << endl;
	visited[n] = true;
	int l = left(n), r = right(n);

	if((0 < n) && (!visited[n-1])){ // check left gear
		int meet = right(n - 1);
		if(meet != l){
			rotate(n-1, !dir);
		}
	}

	if((n < MAXG - 1) && (!visited[n+1])){ // check right gear
		int meet = left(n + 1);
		if(meet != r){
			rotate(n+1, !dir);
		}
	}

	if(dir){ // clockwise
		top[n] = (top[n] + 7) % MAXT;
	} else { // counter clockwise
		top[n] = (top[n] + 1) % MAXT;
	}
}

int main(){
	string s;

	for(int i = 0; i < MAXG; i++){
		cin >> s;
		for(int j = 0; j < MAXT; j++){
			gear[i][j] = s[j] - '0';
		}
	}

	int K;
	cin >> K;

	for(int i = 0; i < K; i++){
		int g, d;
		bool dir;
		cin >> g >> d;

		if(d==1){ dir = true; }
		else{ dir = false; }

		visited = vector<bool>(MAXG, false);
		rotate(g-1, dir);

		/* cout << "DEBUG: ";
		for(int i = 0; i < MAXG; i++){
			cout << gear[i][top[i]];
		} cout << endl; */
	}

	int result = 0;
	for(int i = 0; i < MAXG; i++){
		if(gear[i][top[i]]==1){
			result += (1<<i);
		}
	}

	cout << result << endl;

	return 0;
}
