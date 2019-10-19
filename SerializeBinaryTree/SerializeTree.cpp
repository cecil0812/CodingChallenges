#include "SerializeTree.h"

SerializeTree::SerializeTree()
{
}

string SerializeTree::Serialize(MyTree& tree)
{
	string sb;
	buildString(tree.root, sb);
	return sb;
}

// Decodes your encoded data to tree.
void SerializeTree::Deserialize(string data, MyTree& tree)
{
	list<string> nodes = split_string(data, spliter);
	tree.root = buildTree(nodes);
}


// Private
void SerializeTree::buildString(Node* node, string& sb)
{
	if (node == NULL)
	{
		sb.append(NN).append(spliter);
	}
	else
	{
		ostringstream oss;
		oss << node->data;
		sb.append(oss.str()).append(spliter);
		buildString(node->left, sb);
		buildString(node->right, sb);
	}
}

Node* SerializeTree::buildTree(list<string>& nodes)
{
	string val;

	if (nodes.size() > 0)
	{
		val = nodes.front();
		nodes.pop_front();
	}

	if (val == NN)
	{
		return NULL;
	}
	else
	{
		Node* node = new Node();
		node->data = atoi(val.c_str());
		node->left = buildTree(nodes);	
		node->right = buildTree(nodes);
		return node;
	}
}

list<string> SerializeTree::split_string(string line, const string delim)
{
	list<string> split;

	if (delim == "")
	{
		for (size_t i = 0; i < line.length(); ++i)
		{
			split.push_back(reinterpret_cast<char*>(line[i]));
		}

		return split;
	}

	size_t pos = 0;

	while ((pos = line.find(delim)) != string::npos)
	{
		string sub = line.substr(0, pos);
		split.push_back(sub);

		line = line.substr(pos + 1, line.length() - pos + 1);
	}

	if (line != "")
	{
		split.push_back(line);
	}

	return split;
}
