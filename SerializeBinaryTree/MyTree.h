#pragma once
#include <iostream>

using namespace std;


struct Node
{
	Node* left;
	Node* right;
	int data;
};

class MyTree
{
public:

	friend class SerializeTree;

	MyTree()
	{
		root = NULL;
	}

	~MyTree()
	{
		if (root != NULL)
		{
			deleteNodes(root->left);
			deleteNodes(root->right);
			delete root;
		}
	}

	void AddNode(int data)
	{
		if (root == NULL)
		{
			root = newNode(data);
		}
		else
		{
			Node* node = newNode(data);
			addNodeToTree(node, root);
		}
	}

	void PrintToStream(ostream& outstr)
	{
		printToStream(outstr, root);
	}

private:

	Node* root;

	Node* newNode(int data)
	{
		Node* node = new Node();
		node->data = data;
		node->left = NULL;
		node->right = NULL;

		return node;
	}

	void addNodeToTree(Node* node, Node* start)
	{
		if (start->left == NULL)
		{
			start->left = node;
		}
		else if (start->right == NULL)
		{
			start->right = node;
		}
		else
		{
			addNodeToTree(node, start->left);
		}
	}

	void deleteNodes(Node* node)
	{
		if (node->right != NULL)
		{
			deleteNodes(node->right);
		}
		
		if (node->left != NULL)
		{
			deleteNodes(node->left);
		}

		delete node;
	}

	void printToStream(ostream& outstr, Node* node)
	{
		if (node != NULL)
		{
			outstr << node->data;
			printToStream(outstr, node->right);
			printToStream(outstr, node->left);
		}
	}
};
