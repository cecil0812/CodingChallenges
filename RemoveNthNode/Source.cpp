#include <iostream>

struct Node
{
	Node* next;
	int data;
};

class LinkedList
{
public:

	LinkedList()
	{
		root = NULL;
		end = root;
		size = 0;
	}

	~LinkedList()
	{
		Node* curNode = root;

		while (curNode != NULL)
		{
			Node* temp = curNode;
			curNode = curNode->next;
			delete temp;
		}
	}

	void AddNode(int data)
	{
		if (root == NULL)
		{
			root = new Node();
			root->data = data;
			root->next = end;
			end = root;
		}
		else
		{
			Node* temp = end;
			end = new Node();
			end->next = NULL;
			end->data = data;
			temp->next = end;
		}

		++size;
	}

	// Assume n is always valid
	int RemoveNthFromEnd(int n)
	{
		int num = size - n;
		Node* curNode = root;
		Node* prevNode = NULL;

		// Find the node.
		int currNodeCount = 0;

		while (currNodeCount != num)
		{
			prevNode = curNode;
			curNode = curNode->next;
			++currNodeCount;
		}

		Node* temp = curNode->next;
		prevNode->next = temp;
		int retVal = curNode->data;
		delete curNode;

		return retVal;
	}

private:

	Node* root;
	Node* end;
	size_t size;
};

int main(int argc, char* argv[])
{
	LinkedList list;
	list.AddNode(0);
	list.AddNode(1);
	list.AddNode(2);
	list.AddNode(3);
	list.AddNode(4);

	list.RemoveNthFromEnd(2);

	return 0;
}
