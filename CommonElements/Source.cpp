#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> findCommonElements(const vector<int>& arr, const vector<int>& arr2);
template <class T>
void printVector(const vector<T>& v);


int main(int argc, char* argv[])
{
	vector<int> arr{ 1, 2, 3, 4, 5, 6, 7 };
	vector<int> arr2{ 1, 3, 5, 7, 9, 10, 11 };

	vector<int> common = findCommonElements(arr, arr2);

	printVector(common);

	return 0;
}

vector<int> findCommonElements(const vector<int>& arr, const vector<int>& arr2)
{
	vector<int> common;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (std::binary_search(arr2.begin(), arr2.end(), arr[i]))
		{
			common.push_back(arr[i]);
		}
	}

	return common;
}

template <class T>
void printVector(const vector<T>& v)
{
	cout << endl << "[";

	for (size_t i = 0; i < v.size(); ++i)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << v[i];
	}

	cout << "]" << endl;
}
