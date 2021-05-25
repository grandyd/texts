#include "Texts.h"



Text::Text()
{
	root = curr = 0;
}

void Text::addLeft(string str)
{
	if (root == nullptr) {
		root = curr = new Node(str);
		return;
	}
	Node* p = new Node(str, curr->left);
	curr->left = p;
}

void Text::addRight(string str)
{
	if (root == nullptr) {
		root = curr = new Node(str);
		return;
	}
	Node* p = new Node(str, curr->right);
	curr->right = p;
}

void Text::edit(string str)
{
	curr->val = str;
	return;
}


void Text::right()
{
	if (curr == nullptr) throw "curr == null";
	if (curr->right == nullptr) throw "curr->right == nullptr";

	path.push(curr);
	curr = curr->right;
}

void Text::left()
{
	if (curr == nullptr) throw "curr == null";
	if (curr->left == nullptr) throw "curr->left == nullptr";

	path.push(curr);
	curr = curr->left;
}

void Text::top()
{
	if (curr == nullptr) throw "curr == null";
	if (path.empty()) throw "path.empty()";

	curr = path.top();
	path.pop();
}

void printTRL(ostream& o, Node* root, Node* curr, int level)
{
	if (root == nullptr) return;
	if (root == curr) o << "*";
	else o << "|";
	for (int i = 0; i < level; i++)
	{
		o << "  ";
	}
	o << root->val << endl;
	printTRL(o, root->right, curr, level + 1);
	printTRL(o, root->left, curr, level);

}

ostream& operator<<(ostream& o, const Text& t)
{
	printTRL(o, t.root, t.curr, 0);
	return o;
}

void Text::remove()
{
	if (curr == nullptr) return;
	//removeBranch(curr->right);
	removeBranchIter(curr->right);

	Node* tmp = curr;
	if (!path.empty()) {
		top();
		if (curr->left == tmp) curr->left = tmp->left;
		if (curr->right == tmp) curr->right = tmp->left;
	}
	else {
		root = tmp->left;
		curr = root;
	}
	delete tmp;
}

void Text::removeBranch(Node* n)
{
	if (n == nullptr) return;
	removeBranch(n->left);
	removeBranch(n->right);
	delete n;

}
void Text::removeBranchIter(Node* n)
{
	if (n == nullptr) return;
	stack<Node* > st;
	Node* tmp = n;
	st.push(tmp);

	while (!st.empty()) {
		while (tmp->left != nullptr) {
			st.push(tmp->left);
			tmp = tmp->left;
		}
		while (tmp->right != nullptr) {
			st.push(tmp->right);
			tmp = tmp->right;
			break;
		}
		if ((tmp->left == nullptr) && (tmp->right == nullptr)) {

			delete st.top();
			st.pop();
			if (!st.empty()) {
				tmp = st.top();
				if (tmp->left == nullptr) tmp->right = nullptr;
				tmp->left = nullptr;
			}
		}
	}

}