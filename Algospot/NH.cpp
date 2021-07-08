#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define ALPHABETS (26)
#define MOD (10007)
#define MAXN (100)
#define MAXM (100)
#define c2i(c) (c-'a')

int nodeID;

typedef struct _Node {
	int id;
	bool terminal;
	_Node* children[ALPHABETS];
	_Node* next[ALPHABETS];
	_Node* fail;

	_Node() {
		id = nodeID; nodeID++;
		for (int i = 0; i < ALPHABETS; i++) {
			children[i] = NULL;
			next[i] = NULL;
		}
		fail = NULL;
		terminal = false;
	}

	~_Node() {
		for (int i = 0; i < ALPHABETS; i++) {
			delete children[i];
		}
	}
} Node;

int N, M;
vector<string> patterns;
vector<vector<int>> cache;

void construct(Node* root, const string& s, int i) {
	if (i == s.size()) { root->terminal = true; return; }

	if (root->children[c2i(s[i])] == NULL) { // create new node
		root->children[c2i(s[i])] = new Node;
		// root->children[c2i(s[i])]->id = nodeID;
		// nodeID++;
	}

	construct(root->children[c2i(s[i])], s, i + 1);
}

void construct_failure(Node* root) {
	root->fail = root;

	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();

		for (int i = 0; i < ALPHABETS; i++) {
			if (cur->children[i] == NULL) { continue; }

			// else
			Node* next = cur->children[i];

			if (cur == root) { next->fail = root; }
			else {
				Node* t = cur->fail;
				while ((t != root) && (t->children[i] == NULL)) {
					t = t->fail;
				}
				if (t->children[i]) { t = t->children[i]; }
				next->fail = t;
			}

			next->terminal = next->terminal | next->fail->terminal;

			q.push(next);
		}
	}
}

void construct_next(Node* root) {
	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();

		for (int i = 0; i < ALPHABETS; i++) {
			if (cur->children[i] != NULL) { cur->next[i] = cur->children[i]; }
			else {
				Node* t = cur;
				while ((t->children[i] == NULL && (t->id != 0))) {
					t = t->fail;
				}

				if (t->children[i] != NULL) { cur->next[i] = t->children[i]; }
				else {
					cur->next[i] = t; // root
				}
			}
		}

		// for child node
		for (int i = 0; i < ALPHABETS; i++) {
			if (cur->children[i] == NULL) { continue; }

			// else
			Node* next = cur->children[i];
			q.push(next);
		}
	}
}

int DP(int n, Node* cur) {
	if (cur->terminal) { return 0; }
	if (n == N) { return 1; }

	int& ret = cache[n][cur->id];
	if (ret != -1) { return ret; }

	// else
	ret = 0;
	for (int i = 0; i < ALPHABETS; i++) {
		ret += DP(n + 1, cur->next[i]);
		ret %= MOD;
	}

	return ret;
}

int solve() {
	nodeID = 0;

	Node root;
	// root.id = nodeID; nodeID++;
	for (int i = 0; i < M; i++) {
		construct(&root, patterns[i], 0);
	}

	construct_failure(&root);
	construct_next(&root);

	int result = DP(0, &root);

	return result;
}

int main() {
	int T; cin >> T;
	while (T--) {
		cin >> N >> M;
		patterns = vector<string>(M);
		cache = vector<vector<int>>(N, vector<int>(10 * MAXM + 1, -1));

		for (int i = 0; i < M; i++) {
			cin >> patterns[i];
		}

		cout << solve() << endl;
	}

	return 0;
}
