#pragma once
#include <iostream>
#include <stack>
#include <vector>

#ifndef NULL
#define NULL 0
#endif

using std::cout;
using std::endl;
using std::stack;
using std::vector;


struct Node
{
	int value;
	Node* left;
	Node* right;
};

class BinaryTreeMirror
{
private:
	vector<Node*> paths;
	Node* root;

	Node* newNode(int value)
	{
		Node* newNode = new Node();
		newNode->value = value;
		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;
	}

	void addNode(Node* node, int value)
	{
		if (value < node->value)
		{
			if (node->left == NULL)
			{
				Node* nnode = newNode(value);
				node->left = nnode;
			}
			else
			{
				addNode(node->left, value);
			}
		}
		else if (value > node->value)
		{
			if (node->right == NULL)
			{
				Node* nnode = newNode(value);
				node->right = nnode;
			}
			else
			{
				addNode(node->right, value);
			}
		}
	}

	void removeNode(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		if (node->left == NULL && node->right == NULL)
		{
			delete node;
		}
		else
		{
			removeNode(node->left);
			removeNode(node->right);
			delete node;
		}
	}

	void mirror(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		else
		{
			Node* temp;

			mirror(node->left);
			mirror(node->right);

			temp = node->left;
			node->left = node->right;
			node->right = temp;
		}
	}

	void inOrder(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		inOrder(node->left);
		cout << node->value << " ";
		inOrder(node->right);
	}

	void printAllPaths(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		if (node->left == NULL && node->right == NULL)
		{
			for (size_t i = 0; i < this->paths.size(); ++i)
			{
				cout << this->paths[i]->value << ", ";
			}

			cout << node->value << endl;
		}
		else
		{
			this->paths.push_back(node);
			printAllPaths(node->left);
			printAllPaths(node->right);
			this->paths.pop_back();
		}
	}

	/*
	Let T be a rooted tree. The lowest common ancestor between two nodes n1 and n2 is defined as the lowest node in T that has both n1 and n2 as descendants
	(where we allow a node to be a descendant of itself).

	If we are given a BST where every node has parent pointer, then LCA can be easily determined by traversing up using parent pointer and printing the first
	intersecting node.

	We can solve this problem using BST properties. We can recursively traverse the BST from root. The main idea of the solution is, while traversing from top to bottom,
	the first node n we encounter with value between n1 and n2, i.e., n1 < n < n2 or same as one of the n1 or n2, is LCA of n1 and n2 (assuming that n1 < n2).
	So just recursively traverse the BST in, if node’s value is greater than both n1 and n2 then our LCA lies in left side of the node, if it’s is smaller than
	both n1 and n2, then LCA lies on right side. Otherwise root is LCA (assuming that both n1 and n2 are present in BST)
	*/
	int lca(Node* node, int n1, int n2)
	{
		// Node is on the left side
		if (n1 < node->value && n2 < node->value)
		{
			return lca(node->left, n1, n2);
		}
		else if (n1 > node->value && n2 > node->value)
		{
			return lca(node->right, n1, n2);
		}
		else if (node->value >= n1 && node->value <= n2)
		{
			return node->value;
		}

		return -1;
	}

	int getLeafNodeCount(Node* node)
	{
		if (node == NULL)
		{
			return 0;
		}
		else if (node->left == NULL && node->right == NULL)
		{
			return 1;
		}
		
		return getLeafNodeCount(node->left) + getLeafNodeCount(node->right);
	}

public:

	class iterator;
	friend class iterator;

	BinaryTreeMirror()
	{
		root = NULL;
	}

	BinaryTreeMirror(int val)
	{
		root = NULL;
		AddNode(val);
	}

	~BinaryTreeMirror()
	{
		removeNode(root);
		root = NULL;
	}

	void AddNode(int value)
	{
		if (root == NULL)
		{
			root = new Node();
			root->value = value;
			root->left = NULL;
			root->right = NULL;
		}
		else
		{
			addNode(root, value);
		}
	}

	void Clear()
	{
		removeNode(this->root);
		this->root = NULL;
	}

	void InOrder()
	{
		if (this->root == NULL)
		{
			return;
		}

		inOrder(this->root);
	}

	void PrintAllPaths()
	{
		if (this->root == NULL)
		{
			return;
		}

		printAllPaths(this->root);
	}

	void Mirror()
	{
		mirror(this->root);
	}

	int LCA(int n1, int n2)
	{
		if (this->root == NULL)
		{
			return -1;
		}

		if (n1 > n2)
		{
			int temp = n1;
			n1 = n2;
			n2 = temp;
		}

		return lca(this->root, n1, n2);
	}

	int find(int n)
	{
		int distance = 0;
		Node* node = this->root;

		while (node != NULL)
		{
			if (n == node->value)
			{
				break;
			}
			else if (n < node->value)
			{
				node = node->left;
			}
			else if (n > node->value)
			{
				node = node->right;
			}

			++distance;
		}

		distance = (node == NULL ? -1 : distance);
		return distance;
	}

	/*
	 * The LCA of n1 and n2 in T is the shared ancestor of n1 and n2 that is located farthest from the root.Computation of lowest common ancestors may be useful,
	 * for instance, as part of a procedure for determining the distance between pairs of nodes in a tree : the distance from n1 to n2 can be computed as the distance
	 *  from the root to n1, plus the distance from the root to n2, minus twice the distance from the root to their lowest common ancestor. (Source Wiki)
	*/
	int FindNodeDistance(int n1, int n2)
	{
		int dist1 = find(n1);
		int dist2 = find(n2);
		int lc = lca(this->root, n1, n2);
		int lcaDist = find(lc);

		if (dist1 == -1 || dist2 == -1 || lc == -1 || lcaDist == -1)
		{
			return -1;
		}

		return dist1 + dist2 - (2 * lcaDist);
	}

	int GetLeafNodeCount()
	{
		return getLeafNodeCount(this->root);
	}

	void RemoveNode(int n)
	{
		Node* node = this->root;
		Node* prevNode = NULL;

		while (node != NULL && n != node->value)
		{
			if (n < node->value)
			{
				prevNode = node;
				node = node->left;
			}
			else if (n > node->value)
			{
				prevNode = node;
				node = node->right;
			}
		}

		// Didn't find it, just return.
		if (node == NULL)
		{
			return;
		}

		// Found the Node to remove.
		if (node->left == NULL && node->right == NULL)
		{
			if (node == prevNode->left)
			{
				prevNode->left = NULL;
			}
			else if (node == prevNode->right)
			{
				prevNode->right = NULL;
			}
			
			delete node;
			node = NULL;
		}
		else if (node->left != NULL && node->right != NULL)
		{
			Node* min = node;
			Node* ptrNode = node->right;
			Node* minPrevNode = min;

			while (ptrNode != NULL)
			{
				minPrevNode = min;
				min = ptrNode;
				ptrNode = ptrNode->left;
			}

			if (node == prevNode->left)
			{
				prevNode->left = min;
			}
			else if (node == prevNode->right)
			{
				prevNode->right = min;
			}

			min->left = node->left;
			min->right = node->right;

			if (minPrevNode == node)
			{
				min->right = NULL;
			}

			minPrevNode->left = NULL;
			delete node;
			node = NULL;
		}
		else
		{
			Node* nodeToMove = NULL;

			if (node->right != NULL && node->left == NULL)
			{
				nodeToMove = node->right;
			}
			else
			{
				nodeToMove = node->left;
			}
			
			if (node == prevNode->left)
			{
				prevNode->left = nodeToMove;
			}
			else if (node == prevNode->right)
			{
				prevNode->right = nodeToMove;
			}
			
			delete node;
			node = NULL;
		}
	}

	class iterator : public std::iterator<std::random_access_iterator_tag, Node>
	{
	private:

		friend class BinaryTreeMirror;
		BinaryTreeMirror* ptr;
		Node* node;
		stack<Node*> nodes;
		int value;

		iterator(BinaryTreeMirror* btPtr)
		{
			this->node = NULL;
			this->value = -1;
			this->ptr = btPtr;

			if (this->ptr != NULL)
			{
				this->node = this->ptr->root;
				setToLeftMost();
				this->value = this->node->value;
			}
		}

		void setToLeftMost()
		{
			while (this->node->left != NULL)
			{
				this->nodes.push(this->node);
				this->node = this->node->left;
			}
		}

		iterator& operator--()
		{
			return *this;
		}

		iterator operator--(int)
		{
			return *this;
		}

	public:

		iterator& next()
		{
			if (this->node->right != NULL)
			{
				this->node = this->node->right;
				setToLeftMost();
				this->value = this->node->value;
			}
			else if (!this->nodes.empty())
			{
				this->node = this->nodes.top();
				this->nodes.pop();
				this->value = this->node->value;
			}
			else
			{
				this->node = NULL;
				this->value = -1;
				this->ptr = NULL;
			}
			
			return *this;
		}

		int Value()
		{
			return value;
		}

		iterator& operator++()
		{
			next();
			return *this;
		}

		iterator operator++(int)
		{
			iterator temp = *this;
			next();

			return temp;
		}

		bool operator==(const iterator& it2) const
		{
			if (this->ptr == it2.ptr && this->node == it2.node)
			{
				return true;
			}

			return false;
		}

		bool operator!=(const iterator& it2) const
		{
			return !(*this == it2);
		}

		Node operator*() const
		{
			return *this->node;
		}
	};

	iterator begin()
	{
		return iterator(this);
	}

	iterator end()
	{
		return iterator(NULL);
	}
};
