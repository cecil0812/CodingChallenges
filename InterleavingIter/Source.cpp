#include <iostream>
#include <vector>
#include "InterleavingIter.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> odds{ 1, 3, 5, 7 };
	vector<int> evens{ 2, 4, 6, 8 };

	vector<int> arr1 = { 1, 2, 3 };
	vector<int> arr2 = { 4, 5 };
	vector<int> arr3 = { 6, 7, 8, 9 };
	
	InterleavingIter<int> it;
	InterleavingIter<int> it2;
	it.AddIter(odds.begin(), odds.end());
	it.AddIter(evens.begin(), evens.end());

	it2.AddIter(arr1.begin(), arr1.end());
	it2.AddIter(arr2.begin(), arr2.end());
	it2.AddIter(arr3.begin(), arr3.end());

	// 1 2 3 4 5 6 7 8
	while (it.hasNext())
	{
		cout << it.next() << endl;
	}

	// 1 4 6 2 5 7 3 8 9
	while (it2.hasNext())
	{
		cout << it2.next() << endl;
	}

	try
	{
		int t = it2.next(); // Throws
	}
	catch (runtime_error ex)
	{
		cout << ex.what() << endl;
	}
	
	return 0;
}
