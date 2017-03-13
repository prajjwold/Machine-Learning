#include "Tree.h"

Tree::Tree(){
	root=new Node();
	root->feature="rootfeature";
	root->value="rootvalue";
}

Tree::~Tree(){
	destruct(root);
}

void Tree::destruct(Node* node){
	if(node!=NULL){
		for(int i=0;i<(node->children).size();i++){
			destruct(node->children[i]);
			delete node->children[i];
		}
	}
}
Node* Tree::findNode(Node* node){
	return findNode(root,node->feature,node->value);


}

Node* Tree::findNode(string feature,string value){
	return findNode(root,feature,value);
}


Node* Tree::findNode(Node* root,string feature, string value){
	Node* current = root;
	if(current==NULL){return NULL;}
	if(current->feature.compare(feature)==0 && current->value.compare(value)==0){
		// cout<<"node found"<<endl;
		// cout<<"Feature: "<<current->feature<<endl;
		// cout<<"Value: "<<current->value<<endl;
		return current;
	}
	for(int i=0;i<(current->children).size();i++){
		return findNode(current->children[i],feature,value);
	}
}

void Tree::addChild(Node* parent, Node* child){
	Node* parentNode=findNode(parent);
	if(parentNode==NULL){
		cout<<"Cannot find the parent node to add the child"<<endl;
		return;
	}
	else{
		(parentNode->children).push_back(child);
		return;
	}
	cout<<"Cannot add the child node"<<endl;
}	

void Tree::addChild(Node* parent, string feature, string value){
	Node* child=new Node();
	child->feature=feature;
	child->value=value;
	addChild(parent,child);
}


void Tree::print(){
	stack<Node*> *stack;
	Node* current=root;
	for(int i=(current->children).size()-1;i>=0;i--){
		stack->push(current->children[i]);
	}
	int numTab=0;
	print(stack,numTab);
}

void Tree::print(stack<Node*> *stack,int numTab){
	cout<<"Print"<<endl;
	Node* current=stack->top();
	cout<<"Print"<<endl;
	stack->pop();

	printNumTabs(numTab);
	cout<<current->feature<<current->value<<":"<<endl;
	numTab--;
	for(int i=(current->children).size()-1;i>=0;i--){
		stack->push((current->children)[i]);
		numTab++;
	}
}

void Tree::printNumTabs(int tab){
	for(int i=0;i<tab;i++)
	cout<<"\t";
}

void Tree::testInput(){
	testInput(root);
}

void Tree::testInput(Node* root){
	Node* current=root;
	cout<<"TestInput"<<endl;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=4;j++){
			Node* temp= new Node();
			temp->feature="f";
			temp->feature+=to_string(i);
			temp->value="v";
			temp->value+=to_string(i)+to_string(j);

			//addChild(current,temp);
			cout<<"Added: "<<temp->feature<<":"<<temp->value<<endl;
			delete temp;
		}
		cout<<endl;
	}
}


string Tree::to_string(int i) // convert int to string
{
    stringstream s;
    s << i;
    return s.str();
}
