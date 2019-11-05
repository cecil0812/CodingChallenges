#ifndef _MY_BALANCED_TREE_H
#define _MY_BALANCED_TREE_H

#include <stack>

using std::stack;

#ifndef NULL
#define NULL 0
#endif;

template <class T>
class MyBalancedTree
{
private:

	struct Node
	{
		T value;
		Node* left;
		Node* right;
		int height;
	};

	Node* root;

	Node* createNode(T value)
	{
		Node* n = new Node();
		n->value = value;
		n->left = NULL;
		n->right = NULL;
		n->height = 1;

		return n;
	}

	int height(Node* node)
	{
		if (node == NULL)
		{
			return 0;
		}

		return node->height;
	}

	Node* insertNode(Node* node, T value)
	{
		if (node == NULL)
		{
			return createNode(value);
		}

		if (node->value > value)
		{
			node->left = insertNode(node->left, value);
		}
		else if (node->value < value)
		{
			node->right = insertNode(node->right, value);
		}

		int heightToAdd = 0;

		if (height(node->left) > height(node->right))
		{
			heightToAdd = height(node->left);
		}
		else
		{
			heightToAdd = height(node->right);
		}

		node->height = 1 + heightToAdd;

		int balance = getBalance(node);

		// If this node becomes unbalanced, then  
		// there are 4 cases  
		// Left Left Case  
		if (balance > 1 && value < node->left->value)
		{
			return rightRotate(node);
		}

		// Right Right Case  
		if (balance < -1 && value > node->right->value)
		{
			return leftRotate(node);
		}

		// Left Right Case  
		if (balance > 1 && value > node->left->value)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case  
		if (balance < -1 && value < node->right->value)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	int getBalance(Node* node)
	{
		if (node == NULL)
		{
			return 0;
		}

		return height(node->left) - height(node->right);
	}

	Node* rightRotate(Node* node)
	{
		Node* leftOfNode = node->left;
		Node* treeToRight = leftOfNode->right;

		// Perform rotation  
		leftOfNode->right = node;
		node->left = treeToRight;

		if (this->root == node)
		{
			this->root = leftOfNode;
		}

		// Update heights
		int newHeight = 0;
		if (height(node->left) > height(node->right))
		{
			newHeight = height(node->left);
		}
		else
		{
			newHeight = height(node->right);
		}

		node->height = newHeight + 1;

		newHeight = 0;
		if (height(leftOfNode->left) > height(leftOfNode->right))
		{
			newHeight = height(leftOfNode->left);
		}
		else
		{
			newHeight = height(leftOfNode->right);
		}

		leftOfNode->height = newHeight + 1;

		return leftOfNode;
	}

	// A utility function to left  
	// rotate subtree rooted with x  
	// See the diagram given above.  
	Node *leftRotate(Node* node)
	{
		Node* rightOfNode = node->right;
		Node* otherTree = rightOfNode->left;

		// Perform rotation  
		rightOfNode->left = node;
		node->right = otherTree;

		if (this->root == node)
		{
			this->root = rightOfNode;
		}

		// Update heights
		int newHeight = 0;
		if (height(node->left) > height(node->right))
		{
			newHeight = height(node->left);
		}
		else
		{
			newHeight = height(node->right);
		}

		node->height = newHeight + 1;

		newHeight = 0;
		if (height(rightOfNode->left) > height(rightOfNode->right))
		{
			newHeight = height(rightOfNode->left);
		}
		else
		{
			newHeight = height(rightOfNode->right);
		}

		rightOfNode->height = newHeight + 1;

		return rightOfNode;
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

	Node* findNode(T value)
	{
		Node* node = this->root;

		while (node != NULL)
		{
			if (value == node->value)
			{
				return node;
			}
			else if (value > node->value)
			{
				node = node->right;
			}
			else if (value < node->value)
			{
				node = node->left;
			}
		}

		return NULL;
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

	Node* eraseNode(Node* node, T value)
	{
		if (node == NULL)
		{
			return NULL;
		}

		if (node->value > value)
		{
			node->left = eraseNode(node->left, value);
		}
		else if (node->value < value)
		{
			node->right = eraseNode(node->right, value);
		}
		else if (node->value == value)
		{
			Node* tempNode = node;

			if (node->right == NULL && node->left != NULL)
			{
				node = node->left;
				delete tempNode;
			}
			else if ((node->right != NULL && node->left != NULL)
				|| (node->right != NULL && node->left == NULL))
			{
				node = node->right;
				node->left = tempNode->left;
				delete tempNode;
			}
			else
			{
				// No
				int dummy = 1;
			}
		}

		int heightToAdd = 0;

		if (height(node->left) > height(node->right))
		{
			heightToAdd = height(node->left);
		}
		else
		{
			heightToAdd = height(node->right);
		}

		node->height = 1 + heightToAdd;

		int balance = getBalance(node);

		// If this node becomes unbalanced, then  
		// there are 4 cases  
		// Left Left Case  
		if (balance > 1 && value < node->left->value)
		{
			return rightRotate(node);
		}

		// Right Right Case  
		if (balance < -1 && value > node->right->value)
		{
			return leftRotate(node);
		}

		// Left Right Case  
		if (balance > 1 && value > node->left->value)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case  
		if (balance < -1 && value < node->right->value)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

public:

	class iterator;
	friend class iterator;

	MyBalancedTree()
	{
		root = NULL;
	}

	~MyBalancedTree()
	{
		removeNode(root);
		root = NULL;
	}

	bool insert(T value)
	{
		if (root == NULL)
		{
			root = new Node();
			root->value = value;
			root->right = NULL;
			root->left = NULL;
			root->height = 1;
			return true;
		}
		else
		{
			if (!find(value))
			{
				insertNode(root, value);
				return true;
			}
		}

		return false;
	}

	bool find(T value)
	{
		Node* foundNode = findNode(value);
		
		return (foundNode == NULL) ? false : true;
	}

	bool erase(T value)
	{
		if (find(value))
		{
			eraseNode(this->root, value);
			return true;
		}

		return false;
	}

	void clear()
	{
		removeNode(this->root);
		this->root = NULL;
	}

	void mirror()
	{
		mirror(this->root);
	}

	class iterator : public std::iterator<std::random_access_iterator_tag, Node>
	{
	private:

		friend class MyBalancedTree;
		MyBalancedTree* ptr;
		Node* node;
		stack<Node*> nodes;
		int value;

		iterator(MyBalancedTree* btPtr)
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

#endif
