#include <iostream>
#include <vector>

using namespace std;


void mergeSort(vector<int>& data, size_t lower, size_t upper);
void merge(vector<int>& data, size_t lower, size_t middle, size_t upper);
template <class T>
void printVector(const vector<T>& v);


int main(int argc, char* argv[])
{
	vector<int> data{ 38, 27, 43, 3, 9, 82, 10 };

	mergeSort(data, 0, data.size() - 1);

	printVector(data);

	return 0;
}

void mergeSort(vector<int>& data, size_t lower, size_t upper)
{
	if (lower < upper)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int middle = (lower + upper) / 2;

		// Sort first and second halves 
		mergeSort(data, lower, middle);
		mergeSort(data, middle + 1, upper);

		merge(data, lower, middle, upper);
	}
}

void merge(vector<int>& data, size_t lower, size_t middle, size_t upper)
{
	int i, j, k;
	int n1 = middle - lower + 1;
	int n2 = upper - middle;

	/* create temp arrays */
	vector<int> lowerArray;
	vector<int> upperArray;

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
	{
		lowerArray.push_back(data[lower + i]);
	}

	for (j = 0; j < n2; j++)
	{
		upperArray.push_back(data[middle + 1 + j]);
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = lower; // Initial index of merged subarray 

	while (i < n1 && j < n2)
	{
		if (lowerArray[i] <= upperArray[j])
		{
			data[k] = lowerArray[i];
			i++;
		}
		else
		{
			data[k] = upperArray[j];
			j++;
		}

		++k;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		data[k] = lowerArray[i];
		++i;
		++k;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		data[k] = upperArray[j];
		++j;
		++k;
	}
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
