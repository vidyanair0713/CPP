#include<iostream>
#include<conio.h>

using namespace std;

typedef struct Node
{
	int data;
	Node* left;
	Node* right;
};

Node* createNode(int iData)
{
	Node* temp = new Node();

	temp->data = iData;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void inorder(Node* root);
bool lookup(int iSearchData, Node* root);

int main()
{
	Node* root = new Node();

	root->data = 15;
	root->left = NULL;
	root->right = NULL;

	root->left = createNode(10);
	root->left->left = createNode(5);
	root->right = createNode(20);
	root->right->right = createNode(25);

	inorder(root);
	cout << endl;
	int input;
	cout << "Enter the value to lookup" <<endl;
	cin >> input;
	bool res = lookup(input, root);

	if (res == true)
	{
		cout << "Found element in tree" << endl;
	} 
	else
	{
		cout << "Failed to find element in tree" << endl;
	}
	_getch();
}

bool lookup(int iSearchData, Node *root)
{
	if (root == NULL) {
		return false;
	}
	if (iSearchData == root->data) {
		return true;

	}
	else if (iSearchData < root->data && root->left != NULL) {
		return lookup(iSearchData, root->left);
	}
	else if(iSearchData > root->data && root->right != NULL) {
		return lookup(iSearchData, root->right);

	}

}

void inorder(Node* root)
{
	if (root == NULL) {
		return;
	}
	cout << root->data << " ";
	inorder(root->left);
	inorder(root->right);

	
}