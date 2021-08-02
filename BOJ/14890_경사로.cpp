#include <iostream>
using namespace std;

#define MAXN (100)

int N, L;
int board[MAXN][MAXN];

int solve(){
	int result = 0;

	// row
	for(int i = 0; i < N; i++){
		bool fail = false;

		bool delay = false;
		int h = board[i][0];
		int c = 1;
		for(int j = 1; j < N; j++){
			int nh = board[i][j];

			if(h==nh){ 
				c++; 
			}
			else if((h == nh + 1) || (h + 1 == nh))
			{
				if(delay){
					if(c >= L){ delay = false; c -= L; }
					else{ fail = true; break;}
				}
				if(h < nh){
					if(c<L){ fail = true; break; }
				} else { // h > nh
					delay = true;
				}
				h = nh;
				c = 1;
			} else {
				fail = true;
				break;
			}
		}
		
		if(delay && (c >= L)){ delay = false; }

		if((!fail)&&(!delay)){ result++; }
	}

	// col
	for(int j = 0; j < N; j++){
		bool fail = false;

		bool delay = false;
		int h = board[0][j];
		int c = 1;
		for(int i = 1; i < N; i++){
			int nh = board[i][j];

			if(h==nh){ 
				c++; 
			}
			else if((h == nh + 1) || (h + 1 == nh)){
				if(delay){
					if(c >= L){ delay = false; c -= L; }
					else{ fail = true; break;}
				}

				if(h < nh){
					if(c<L){ fail = true; break; }
				} else { // h > nh
					delay = true;
				}
				h = nh;
				c = 1;
			}  else {
				fail = true;
				break;
			}
		}

		if(delay && (c >= L)){ delay = false; }

		if((!fail)&&(!delay)){ result++; }
	}

	return result;
}

int main(){
	ios::sync_with_stdio(false);

	cin >> N >> L;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> board[i][j];
		}
	}

	cout << solve() << endl;

	return 0;
}
