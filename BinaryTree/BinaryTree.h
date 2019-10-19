#pragma once

#include <stack>

#ifndef NULL
#define NULL 0
#endif

using std::stack;


struct Node
{
	int value;
	Node* left;
	Node* right;
};

class BinaryTree
{
private:
	Node* root;

	static bool LessThanTreeCmp(int v1, int v2)
	{
		if (v1 > v2)
		{
			return true;
		}

		return false;
	}

	static bool GreaterThanTreeCmp(int v1, int v2)
	{
		if (v1 < v2)
		{
			return true;
		}

		return false;
	}

	void addNode(Node* node, int value, bool(*f)(int, int))
	{
		//if (value < node->value)
		if (f(node->value, value))
		{
			if (node->left == NULL)
			{
				Node* newNode = new Node();
				newNode->value = value;
				newNode->left = NULL;
				newNode->right = NULL;
				node->left = newNode;
			}
			else
			{
				addNode(node->left, value, f);
			}
		}
		//else if (value > node->value)
		else
		{
			if (node->right == NULL)
			{
				Node* newNode = new Node();
				newNode->value = value;
				newNode->left = NULL;
				newNode->right = NULL;
				node->right = newNode;
			}
			else
			{
				addNode(node->right, value, f);
			}
		}
		/*else if (value == node->value)
		{
			// Some shit
		}*/
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

public:

	class iterator;
	friend class iterator;

	BinaryTree()
	{
		root = NULL;
	}

	BinaryTree(int val)
	{
		root = NULL;
		AddNode(val);
	}

	~BinaryTree()
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
			addNode(root, value, BinaryTree::LessThanTreeCmp);
		}
	}

	void Clear()
	{
		removeNode(this->root);
		this->root = NULL;
	}

	class iterator : public std::iterator<std::random_access_iterator_tag, Node>
	{
	private:

		friend class BinaryTree;
		BinaryTree* ptr;
		Node* node;
		stack<Node*> nodes;
		int value;

		iterator(BinaryTree* btPtr)
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
			if (!this->nodes.empty())
			{
				this->node = this->nodes.top();
				this->nodes.pop();
				this->value = this->node->value;
			}
			else if (this->node->right != NULL)
			{
				this->node = this->node->right;
				setToLeftMost();
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

	class order_iterator : public std::iterator<std::random_access_iterator_tag, Node>
	{
	private:

		friend class BinaryTree;
		BinaryTree* ptr;
		Node* node;
		stack<Node*> nodes;
		int value;

		order_iterator(BinaryTree* btPtr)
		{
			this->node = NULL;
			this->value = -1;
			this->ptr = btPtr;

			if (this->ptr != NULL)
			{
				this->node = this->ptr->root;
				this->value = this->node->value;
				this->nodes.push(this->ptr->root);
			}
		}

		order_iterator& operator--()
		{
			return *this;
		}

		order_iterator operator--(int)
		{
			return *this;
		}

	public:

		order_iterator& next()
		{
			if (this->node->left != NULL)
			{
				this->node = this->node->left;
				this->value = this->node->value;
				this->nodes.push(this->node);
			}
			else if (this->node->right != NULL)
			{
				this->nodes.pop();
				this->node = this->node->right;
				this->value = this->node->value;
				this->nodes.push(this->node);
			}
			else if (!this->nodes.empty())
			{
				while (this->node->right == NULL && !this->nodes.empty())
				{
					this->node = this->nodes.top();
					this->nodes.pop();
				}

				if (this->node->right == NULL && this->nodes.empty())
				{
					this->node = NULL;
					this->value = -1;
					this->ptr = NULL;
				}
				else
				{
					this->node = this->node->right;
					this->value = this->node->value;
					this->nodes.push(this->node);
				}
			}

			return *this;
		}

		int Value()
		{
			return value;
		}

		order_iterator& operator++()
		{
			next();
			return *this;
		}

		order_iterator operator++(int)
		{
			order_iterator temp = *this;
			next();

			return temp;
		}

		bool operator==(const order_iterator& it2) const
		{
			if (this->ptr == it2.ptr && this->node == it2.node)
			{
				return true;
			}

			return false;
		}

		bool operator!=(const order_iterator& it2) const
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

	order_iterator order_begin()
	{
		return order_iterator(this);
	}

	order_iterator order_end()
	{
		return order_iterator(NULL);
	}

	void CreateMirror(BinaryTree& tree)
	{
		if (this->root == NULL)
		{
			return;
		}

		tree.Clear();
		tree.AddNode(this->root->value);
		order_iterator iter = this->order_begin();
		++iter;

		for (; iter != this->order_end(); ++iter)
		{
			tree.addNode(tree.root, (*iter).value, BinaryTree::GreaterThanTreeCmp);
		}
	}
};
