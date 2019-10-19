#include <iostream>
#include <vector>

using namespace std;

void quicksort(vector<int>& data, size_t lower, size_t upper);
size_t partition(vector<int>& data, size_t lower, size_t upper);
template <class T>
void printVector(const vector<T>& v);


int main(int argc, char* argv[])
{
	vector<int> data{ 10, 80, 30, 90, 40, 50, 70 };

	quicksort(data, 0, data.size() - 1);

	printVector(data);

	return 0;
}

void quicksort(vector<int>& data, size_t lower, size_t upper)
{
	if (lower < upper)
	{
		size_t pivot = partition(data, lower, upper);
		quicksort(data, lower, pivot - 1);
		quicksort(data, pivot + 1, upper);
	}
}

size_t partition(vector<int>& data, size_t lower, size_t upper)
{
	int pivotVal = data[upper];

	size_t i = (lower - 1);  // Index of smaller element

	for (size_t j = lower; j <= upper - 1; ++j)
	{
		// If current element is smaller than the pivot
		if (data[j] < pivotVal)
		{
			// increment index of smaller element
			++i;
			int temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}

	int temp = data[i + 1];
	data[i + 1] = data[upper];
	data[upper] = temp;

	return i + 1;
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
