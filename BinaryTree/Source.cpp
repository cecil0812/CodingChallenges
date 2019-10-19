#include <iostream>
//#include "BinaryTree.h"
#include "BinaryTreeMirror.h"

using namespace std;


int main(int argc, char* argv[])
{
	BinaryTreeMirror tree;

	/*tree.AddNode(5);
	tree.AddNode(6);
	tree.AddNode(4);
	tree.AddNode(1);
	tree.AddNode(10);
	tree.AddNode(8);*/

	tree.AddNode(20);
	tree.AddNode(8);
	tree.AddNode(22);
	tree.AddNode(4);
	tree.AddNode(12);
	tree.AddNode(10);
	tree.AddNode(14);
	tree.AddNode(13);

	cout << "Leaf nodes: " << tree.GetLeafNodeCount() << endl;

	cout << tree.find(20) << endl;
	cout << tree.find(10) << endl;
	cout << tree.find(2) << endl;
	cout << tree.find(4) << endl;

	cout << endl;

	cout << tree.FindNodeDistance(10, 14) << endl;
	cout << tree.FindNodeDistance(4, 14) << endl;
	cout << tree.FindNodeDistance(4, 22) << endl;
	cout << tree.FindNodeDistance(8, 14) << endl;

	cout << endl;

	for (BinaryTreeMirror::iterator iter = tree.begin(); iter != tree.end(); ++iter)
	{
		cout << "Value = " << (*iter).value << endl;
	}

	cout << endl;

	/* LCA of 10 and 14 is 12
	 * LCA of 14 and 8 is 8
	 * LCA of 10 and 22 is 20
	*/
	cout << "LCA(10, 14) = " << tree.LCA(10, 14) << endl;
	cout << "LCA(14, 8) = " << tree.LCA(14, 8) << endl;
	cout << "LCA(10, 22) = " << tree.LCA(10, 22) << endl;
	cout << "LCA(4, 10) = " << tree.LCA(4, 10) << endl;

	cout << "Paths: " << endl;
	tree.PrintAllPaths();

	//tree.InOrder();

	cout << endl;

	tree.RemoveNode(12);

	for (BinaryTreeMirror::iterator iter = tree.begin(); iter != tree.end(); ++iter)
	{
		cout << "Value = " << (*iter).value << endl;
	}

	tree.Mirror();

	//tree.InOrder();

	cout << endl;

	for (BinaryTreeMirror::iterator iter = tree.begin(); iter != tree.end(); ++iter)
	{
		cout << "Value = " << (*iter).value << endl;
	}

	cout << endl;

	return 0;
}
