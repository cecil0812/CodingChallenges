#pragma once

#include <string>
#include <list>
#include <sstream>
#include "MyTree.h"

using std::string;
using std::ostringstream;


class SerializeTree
{
public:
	SerializeTree();
	string Serialize(MyTree& tree);
	void Deserialize(string data, MyTree& tree);

private:

	string spliter = ",";
	string NN = "X";

	void buildString(Node* node, string& sb);
	Node* buildTree(list<string>& nodes);
	list<string> split_string(string line, const string delim);
};
