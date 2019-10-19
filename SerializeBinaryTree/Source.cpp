#include <iostream>
#include <string>
#include "SerializeTree.h"
#include "MyTree.h"

using namespace std;


int main(int argc, char* argv[])
{
	MyTree tree;
	tree.AddNode(1);
	tree.AddNode(2);
	tree.AddNode(3);
	tree.AddNode(4);
	tree.AddNode(5);

	tree.PrintToStream(cout);

	SerializeTree serializer;
	string mystr = serializer.Serialize(tree);

	cout << endl << mystr << endl;

	MyTree newTree;
	serializer.Deserialize(mystr, newTree);

	newTree.PrintToStream(cout);

	return 0;
}
