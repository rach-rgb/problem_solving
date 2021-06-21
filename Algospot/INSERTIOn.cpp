#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

#define MAXN (50000)

typedef struct _node {
	int data;
	int pri, size;
	_node* left;
	_node* right;

	_node(int ud) : data(ud), pri(rand()), size(1), left(NULL), right(NULL) {}

	void setLeft(_node* next)
	{
		left = next;
		calcSize();
	}

	void setRight(_node* next)
	{
		right = next;
		calcSize();
	}

	int calcSize()
	{
		size = 1;
		if (left) { size += left->size; }
		if (right) { size += right->size; }

		return size;
	}

} node;

void input();
void solve();
node* insert(node* root, node* cur);
node* construct();
pair<node*, node*> split(node* root, int val);
node* find(node* root, int k);
node* merge(node* left, node* right);
node* erase(node* root, int k);

int N;
int moves[MAXN];
int result[MAXN];

int main()
{
	ios::sync_with_stdio(false);
	srand(5323);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		for (int j = 0; j < N; j++)
		{
			cout << result[j] << " ";
		}
		cout << endl;
	}

	return 0;
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> moves[i]; // 0 - indexed
	}
}

void solve()
{
	node* root = construct();

	for (int i = N - 1; i >= 0; i--)
	{
		node* c = find(root, (i + 1) - moves[i]);
		result[i] = c->data;
		root = erase(root, c->data);

		delete c;
	}
}

node* construct()
{
	node* root = new node(1);


	for (int i = 2; i <= N; i++)
	{
		node* cur = new node(i);

		root = insert(root, cur);
	}

	return root;
}

node* insert(node* root, node* cur)
{
	if (root == NULL) { return cur; }
	if (cur == NULL) { return root; }

	if (root->pri >= cur->pri)
	{
		if (root->data > cur->data)
		{
			root->setLeft(insert(root->left, cur));
			// root->left = insert(root->left, cur);
		}
		else if (root->data < cur->data)
		{
			root->setRight(insert(root->right, cur));
			// root->right = insert(root->right, cur);
		}

		// root->size++;

		return root;
	}
	else // (root->pri < cur->pri) // need to chage root
	{
		// cur->size += root->size;

		if (root->data < cur->data)
		{
			pair<node*, node*> s = split(root->right, cur->data);
			
			cur->setLeft(root);
			cur->setRight(s.second);
			root->setRight(s.first);
			// cur->left = root;
			// cur->right = s.second;
			// root->right = s.first;

			/* if (s.second != NULL) {
				root->size -= s.second->size;
			} */
		}
		else if (root->data > cur->data)
		{
			pair<node*, node*> s = split(root->right, cur->data);

			cur->setLeft(s.first);
			cur->setRight(root);
			root->setLeft(s.second);
			// cur->left = s.first;
			// cur->right = root;
			// root->left = s.second;

			/* if (s.first != NULL)
			{
				root->size -= s.first->size;
			} */
		}

		return cur;
	}
}


pair<node*, node*> split(node* root, int val)
{
	if (root == NULL) { return pair<node*, node*>(NULL, NULL); }

	if (root->data < val)
	{
		pair<node*, node*> s = split(root->right, val);

		root->setRight(s.first);
		// root->right = s.first;
		/* if (s.second != NULL) {
			root->size = root->size - s.second->size;
		} */

		return pair<node*, node*>(root, s.second);
	}
	else if (root->data > val)
	{
		pair<node*, node*> s = split(root->right, val);

		root->setLeft(s.second);
		// root->left = s.second;
		/* if (s.first != NULL) {
			root->size = root->size - s.first->size;
		} */

		return pair<node*, node*>(s.first, root);
	}
}

node* find(node* root, int k)
{
	if ((root->left == NULL) && (root->right == NULL)) { return root; }

	if (root->left == NULL) { 
		if (k == 1) { return root; }
		else { return find(root->right, k - 1); }
	}

	// root->left != NULL
	if (root->left->size == k - 1)
	{
		return root;
	}
	else if (root->left->size >= k)
	{
		return find(root->left, k);
	}
	else
	{
		return find(root->right, k - (root->left->size) - 1);
	}
}

node* erase(node* root, int k)
{
	if (root == NULL) { return NULL; }

	if (root->data == k)
	{
		return merge(root->left, root->right);
	}

	// else
	if (k < root->data)
	{
		root->setLeft(erase(root->left, k));
		// root->left = erase(root->left, k);
		// root->size--;
	}
	else if (k > root->data)
	{
		root->setRight(erase(root->right, k));
		// root->right = erase(root->right, k);
		// root->size--;
	}

	return root;
}

node* merge(node* left, node* right)
{
	if (left == NULL) { return right; }
	if (right == NULL) { return left; }

	// else
	node* root;
	if (left->pri < right->pri)
	{
		root = right;
		root->setLeft(merge(left, root->left));
		// root->left = merge(left, root->left);
	}
	else // (left->pri >= right->pri)
	{
		root = left;
		root->setRight(merge(root->right, right));
		// root->right = merge(root->right, right);
	}

	// root->size = left->size + right->size;

	return root;
}