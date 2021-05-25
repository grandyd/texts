#pragma once
#include <string>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

class Node
{
public:
	string val;

	Node* left;
	Node* right;

	Node(string _val = "", Node* _left = nullptr, Node* _right = nullptr) : val(_val), left(_left), right(_right) {};
};

void printTRL(ostream& o, Node* root, Node* curr, int level);

class Text
{
	Node* root;
	Node* curr;
	stack<Node*> path;

	void removeBranch(Node* n);
	void removeBranchIter(Node* n);
public:

	Text();

	void remove();

	void addLeft(string str);
	void addRight(string str);

	void edit(string str);

	void right();
	void left();
	void top();

	void fprint(ofstream& ofstr, Node* root, int level) {
		if (root == nullptr) return;
		for (int i = 0; i < level; i++) {
			ofstr << '\t';
		}
		ofstr << root->val << endl;
		fprint(ofstr, root->right, level + 1);
		fprint(ofstr, root->left, level);
	}
	friend ofstream& operator <<(ofstream& ofstr, Text& text) {
		ofstream ofs;
		ofs.open("text.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		text.fprint(ofstr, text.root, 0);
		return ofstr;
	}


	friend ostream& operator << (ostream& o, const Text& t);


	void fread(ifstream& ifstr, stack<Node*>* stack, Node* root, int level) {
		if (ifstr.eof()) return;
		string str;
		getline(ifstr, str);
		if (str == "" && ifstr.eof()) return;
		int count = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != '\t') break;
			count++;
		}
		if (count > level) {
			root->right = new Node;
			root->right->val = str.substr(count, str.length() - count);
			stack->push(root);
			fread(ifstr, stack, root->right, count);
		}
		else if (count == level) {
			root->left = new Node;
			root->left->val = str.substr(count, str.length() - count);
			fread(ifstr, stack, root->left, count);
		}
		else {
			for (int i = 0; i < level - count - 1; i++) {
				if (!stack->empty()) stack->pop();
				else break;
			}
			if (!stack->empty()) {
				Node* tmp = stack->top();
				tmp->left = new Node;
				tmp->left->val = str.substr(count, str.length() - count);
				stack->pop();
				fread(ifstr, stack, tmp->left, count);
			}
			else {
				throw logic_error("vsratiy file");
			}
		}
	}

	friend ifstream& operator>>(ifstream& ifstr, Text& text) {
		if (!ifstr.eof()) {
			stack<Node*>* st = new stack<Node*>;
			while (text.root != nullptr) {
				text.remove();
			}
			text.root = new Node;
			getline(ifstr, text.root->val);
			text.fread(ifstr, st, text.root, 0);
			text.curr = text.root;
			delete st;
		}
		return ifstr;
	}

};
