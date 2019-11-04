/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
*/
#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;

Node* mergeTwoListsNodeWise(Node* l1, Node* l2);
void cleanup(Node* node);

int main(int argc, char* argv[])
{
	ofstream file("somefile.txt");
	file << "Do stuff";


	LinkedList l1;
	l1.addNode(1);
	l1.addNode(2);
	l1.addNode(4);

	LinkedList l2;
	l2.addNode(1);
	l2.addNode(3);
	l2.addNode(4);
	l2.addNode(5);

	LinkedList l3;

	l1.mergeTwoLists(l1, l2, l3);

	cout << l3 << endl;

	cout << endl;

	LinkedList l5;
	cin >> l5;
	cin >> l5;
	cin >> l5;

	LinkedList l4;
	l4.root = mergeTwoListsNodeWise(l1.root, l2.root);
	cout << l4;

	// We have to manually clean up because our destructor won't work anymore.
	cleanup(l1.root);
	cleanup(l3.root);
	cleanup(l5.root);
	
	// This list is (mostly) destroyed above.
	// Deleting this list, results in the destruction of list4.
	// I should note: I would normally not choose to create a new list in this manner since in C++, RAII.
	// Resource Allocation Is Initalization => Use classes and destructors.
	// This is why the Node* root member would normally be private in the LinkedList class.
	// That said, there are use cases for the above and also, it's good pointer practice to do it pointer-wise.
	// I would just really expect RAII in an actual production evironment unless there were memory constraints.
	// (Note: See LinkedList::~LinkedList())
	delete l2.root;

	return 0;
}

void cleanup(Node* node)
{
	Node* temp = node;

	while (temp != NULL)
	{
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}

Node* mergeTwoListsNodeWise(Node* l1, Node* l2)
{
	Node* merged = NULL;

	if (l1 == NULL && l2 == NULL)
	{
		return NULL;
	}

	if (l1->value < l2->value)
	{
		merged = l1;
		l1 = l1->next;
	}
	else
	{
		merged = l2;
		l2 = l2->next;
	}

	Node* root = merged;

	while (l1 != NULL && l2 != NULL)
	{
		if (l1->value < l2->value)
		{
			merged->next = l1;
			l1 = l1->next;
		}
		else
		{
			merged->next = l2;
			l2 = l2->next;
		}

		merged = merged->next;
	}

	// Get whatever is left over if the lists aren't the same length.
	if (l1 == NULL)
	{
		merged->next = l2;
	}
	else
	{
		merged->next = l1;
	}

	return root;
}
