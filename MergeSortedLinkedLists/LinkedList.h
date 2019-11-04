#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <iostream>
#include <fstream>

using std::ostream;
using std::istream;
using std::endl;


struct Node
{
	int value;
	Node* next;
};

class LinkedList
{
private:
	
	void deleteNodes(Node* node)
	{
		while (node->next != NULL)
		{
			Node* temp = node;
			node = node->next;
			delete temp;
		}

		delete node;
	}

public:
	
	Node* root;

	LinkedList()
	{
		this->root = NULL;
	}

	// Normally would destroy here, but we're doing funky pointer stuff.
	~LinkedList()
	{
		//deleteNodes(this->root);
	}

	void addNode(int num)
	{
		if (this->root == NULL)
		{
			this->root = new Node();
			this->root->value = num;
			return;
		}

		Node* node = this->root;

		while (node->next != NULL)
		{
			node = node->next;
		}

		Node* newNode = new Node();
		newNode->value = num;
		newNode->next = NULL;
		node->next = newNode;
	}

	void mergeTwoLists(const LinkedList& l1, const LinkedList& l2, LinkedList& merged)
	{
		Node* l1Nodes = l1.root;
		Node* l2Nodes = l2.root;

		while (l1Nodes != NULL && l2Nodes != NULL)
		{
			if (l1Nodes->value == l2Nodes->value)
			{
				merged.addNode(l1Nodes->value);
				merged.addNode(l1Nodes->value);
				l1Nodes = l1Nodes->next;
				l2Nodes = l2Nodes->next;
			}
			else if (l1Nodes->value < l2Nodes->value)
			{
				merged.addNode(l1Nodes->value);
				l1Nodes = l1Nodes->next;
			}
			else if (l1Nodes->value > l2Nodes->value)
			{
				merged.addNode(l2Nodes->value);
				l2Nodes = l2Nodes->next;
			}
		}

		// Get whatever is left over if the lists aren't the same length.
		Node** ptr = NULL;

		if (l1Nodes == NULL)
		{
			ptr = &l2Nodes;
		}
		else if (l2Nodes == NULL)
		{
			ptr = &l1Nodes;
		}

		if (ptr != NULL)
		{
			while (*(ptr) != NULL)
			{
				merged.addNode((*ptr)->value);
				ptr = &(*ptr)->next;
			}
		}
	}

	friend ostream& operator<<(ostream& os, const LinkedList& l)
	{
		Node* curNode = l.root;

		while (curNode != NULL)
		{
			os << curNode->value << endl;
			curNode = curNode->next;
		}

		return os;
	}

	friend istream& operator>>(istream& os, LinkedList& l)
	{
		int temp = -1;
		os >> temp;
		l.addNode(temp);

		return os;
	}
};

#endif
