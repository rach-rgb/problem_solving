#include <iostream>
#include <stack>
#include <string>
using namespace std;

// solution 1 - use only stack
int main(){
	string input;
	cin >> input;

	stack<int> s; // let '(' = 0, '[' = -1

	int i = 0;
	while(i < input.size())
	{
		char c = input[i];

		if(c=='('){
			s.push(0);
		} else if(c=='['){
			s.push(-1);
		}else
		{
			int p;
			if(c==')'){ p = 0; }
			else if(c==']'){ p =-1; }

			int tmp = 0;
			while((!s.empty()) && ((s.top()!=0) && (s.top()!=-1)))
			{
				tmp += s.top();
				s.pop();
			}

			if(s.empty() || (s.top()!=p)){ break; } // invalid
			s.pop();
			if(tmp==0) // () or []
			{
				if(p==0){ tmp = 2; }
				else{ tmp = 3; }
			} else { // ( ... ) or [ ... ]
				if(p==0){ tmp = tmp * 2; }
				else{ tmp = tmp * 3; }
			}
			s.push(tmp);

		}

		i++;
	}

	if(i!=input.size()){ cout << 0 << endl; }
	else{
		int result = 0;
		while(!s.empty())
		{
			if((s.top()==0)||(s.top()==-1)){ cout << 0 << endl; return 0; }
			else{
				result += s.top();
			}
			s.pop();
		}
		cout << result << endl;
	}

	return 0;
}


/* solution 2 - Use recursion and additional vector
#define MAXS (30)
int info[MAXS];

bool isValid(const string& input){
	stack<pair<char, int>> s;

	int i = 0;
	while(i < input.size())
	{
		char c = input[i];

		if((c=='(')||(c=='[')){
			s.push(pair<char, int>(c, i));
		} else
		{
			char p;
			if(c==')'){ p = '('; }
			else if(c==']'){ p ='['; }

			if((s.empty())||(s.top().first != p)){ return false; }
			info[i] = s.top().second;
			info[s.top().second] = i;
			s.pop();
		}

		i++;
	}

	return s.empty();
}

int calculate(const string& input, int s, int e){
	if(s+1==e)
	{
		if(input[s]=='('){ return 2; }
		else{ return 3; }
	}
	else if(info[s]==e) // multiply
	{
		if(input[s]=='('){ return 2 * calculate(input, s+1, e-1); }
		else{ return 3 * calculate(input, s+1, e-1); }
	} else { // addition
		return calculate(input, s, info[s]) + calculate(input, info[s]+1, e);
	}
}

int main(){
	string input;
	cin >> input;

	if(!isValid(input)){ cout << 0 << endl; }
	else{
		cout << calculate(input, 0, input.size()-1) << endl;
	}

	return 0;
}
*/
