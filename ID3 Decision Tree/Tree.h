#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node{
	vector<Node*> children;
	string feature;
	string value;
};


class Tree{
	private:
	Node* root;
	Node* findNode(Node* root,string feature, string value);

	public:
	Tree(); 
	~Tree();
	void destruct(Node* node);
	Node* findNode(string feature, string value);
	Node* findNode(Node* node);

	void addChild(Node* parent, Node* child);	
	void addChild(Node* parent, string feature, string value);
	void print();
	void print(stack<Node*> *stack,int numTab);
	void printNumTabs(int numTab);
	void testInput();
	void testInput(Node* root);

	string to_string(int i);
/*	void delete(Node node);
	void delete(string feature, string value);
	void inorderTraversal(Node parentNode);
	void preorderTraversal(Node parentNode);
	void postorderTraversal(Node parentNode);*/
};


