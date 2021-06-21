#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define ALPHABETS (26)

int toNumber(char c) { return c - 'A'; }

typedef struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal; // -1 or id
	int first;

	TrieNode()
	{
		for (int i = 0; i < ALPHABETS; i++) { children[i] = NULL; }
		terminal = -1;
		first = -1;
	}

	~TrieNode()
	{
		for (int i = 0; i < ALPHABETS; i++)
		{
			if (children[i])
			{
				delete children[i];
			}
		}
	}

	void insert(const char* key, int id)
	{
		if (first == -1)
		{
			first = id;
		}

		if (*key == 0)	// base
		{
			terminal = id;
		}
		else
		{
			int next = toNumber(*key);

			if (children[next] == NULL)
			{
				children[next] = new TrieNode();
			}

			children[next]->insert(key + 1, id);
		}
	}

	int type(const char* key, int id)
	{
		if (*key == 0) { return 0; }

		if (first == id) { return 1; }
		else
		{
			int next = toNumber(*key);
			return 1 + children[next]->type(key + 1, id);
		}
	}

	TrieNode* find(const char* key)
	{
		if (*key == 0) { return this; }

		// else
		int next = toNumber(*key);

		if (children[next] == NULL)
		{
			return NULL;
		}
		else
		{
			return children[next]->find(key + 1);
		}
	}


} Node;

void solve();
int countKeys(Node* trie, const char* word);

int N, M;
int result;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N >> M;
		solve();
		cout << result << endl;
	}

	return 0;
}

void solve()
{
	result = 0;

	// construct
	vector<pair<int, string>> v;

	for (int i = 0; i < N; i++)
	{
		string s;
		int freq;
		cin >> s >> freq;

		v.push_back(make_pair(-freq, s.c_str()));
	}

	sort(v.begin(), v.end());

	Node* root = new Node();
	for (int i = 0; i < N; i++)
	{
		root->insert((v[i].second).c_str(), i);
	}
	root->first = -1;

	// find
	for (int i = 0; i < M; i++)
	{
		string s;
		cin >> s;

		result += countKeys(root, s.c_str());
	}

	result += (M - 1);
}

int countKeys(Node* trie, const char* word)
{
	Node* node = trie->find(word);

	if((node == NULL) || (node->terminal == -1))
	{
		return strlen(word);
	}

	return trie->type(word, node->terminal);
}