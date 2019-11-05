#include <iostream>
#include <vector>
#include <map>

#include "MySet.h"
//#include "MyBalancedTree.h"

using namespace std;

/*
a. intersection of the set
b. integers that appear only in set 1
c. integers that appear only in set 2
*/

vector<int> getIntersection(const vector<int>& s1, const vector<int>& s2);
vector<int> getOnlyInFirst(const vector<int>& s1, const vector<int>& s2);
int binarySearch(const vector<int>& s1, int value, size_t min, size_t max);


int main(int argc, char* argv[])
{
	MySet<int> set1;
	set1.insert(2);
	set1.insert(4);
	set1.insert(6);
	set1.insert(8);

	MySet<int> set2;
	set2.insert(1);
	set2.insert(2);
	set2.insert(3);
	set2.insert(4);

	MySet<int> newSet = set1.getUnion(set2);
	MySet<int> newSet2 = set1.getUnionToSet(set2);

	return 0;
}

vector<int> getIntersection(const vector<int>& s1, const vector<int>& s2)
{
	vector<int> results;

	for (size_t i = 0; i < s1.size(); ++i)
	{
		int index = binarySearch(s2, s1[i], 0, s2.size() - 1);

		if (index != -1)
		{
			results.push_back(s1[i]);
		}
	}

	return results;
}

vector<int> getOnlyInFirst(const vector<int>& s1, const vector<int>& s2)
{
	vector<int> results;

	for (size_t i = 0; i < s1.size(); ++i)
	{
		int index = binarySearch(s2, s1[i], 0, s2.size() - 1);

		if (index == -1)
		{
			results.push_back(s1[i]);
		}
	}

	return results;
}

int binarySearch(const vector<int>& s1, int value, size_t min, size_t max)
{
	size_t middle = ((max - min) / 2) + min;

	if (s1[middle] == value)
	{
		return middle;
	}

	if (min == middle)
	{
		return -1;
	}

	if (s1[middle] > value)
	{
		return binarySearch(s1, value, min, middle);
	}
	else if (s1[middle] < value)
	{
		return binarySearch(s1, value, middle, max);
	}

	return -1;
}