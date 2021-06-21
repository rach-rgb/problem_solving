#include <iostream>
#include <string>
#include <stack>
using namespace std;

void solve();
bool open(char c);
bool match(char c1, char c2);

string s;

bool result;

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> s;
		solve();
		if (result) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
	return 0;
}

void solve()
{
	result = true;
	stack<char> st;

	for (int i = 0; i < s.size(); i++)
	{
		if (open(s[i]))
		{
			st.push(s[i]);
		}
		else
		{
			if (st.empty()) { result = false; break; }

			char c = st.top();
			if (match(c, s[i]))
			{
				st.pop();
			}
			else
			{
				result = false;
				break;
			}
		}
	}

	if (result && (!st.empty())) { result = false; }

	while (!st.empty()) { st.pop(); }

}

bool open(char c)
{
	if ((c=='(') || (c=='{') || (c=='['))
	{
		return true;
	}
	else { return false; }
}

bool match(char c1, char c2)
{
	if ((c1 == '(') && (c2 == ')'))
	{
		return true;
	}
	else if ((c1 == '{') && (c2 == '}'))
	{
		return true;
	}
	else if ((c1 == '[') && (c2 == ']'))
	{
		return true;
	}
	
	return false;
}