#include <iostream>
#include <vector>

using namespace std;


int search(vector<int>& nums, int target);
int findPivot(vector<int> nums);
int binarySearch(vector<int> nums, int target);
void printVector(const vector<int>& nums);

/*
Search an element in a sorted and rotated array
An element in a sorted array can be found in O(log n) time via binary search. 
But suppose we rotate an ascending order sorted array at some pivot unknown to you beforehand. 
So for instance, 1 2 3 4 5 might become 3 4 5 1 2. Devise a way to find an element in the rotated array in O(log n) time.

Input  : arr[] = {5, 6, 7, 8, 9, 10, 1, 2, 3};
key = 3
Output : Found at index 8

Input  : arr[] = {5, 6, 7, 8, 9, 10, 1, 2, 3};
key = 30
Output : Not found

Input : arr[] = {30, 40, 50, 10, 20}
key = 10
Output : Found at index 3
*/
int main(int argc, char* argv[])
{
	vector<int> arr{5, 6, 7, 8, 9, 10, 1, 2, 3 };
	int key = 3;

	printVector(arr);
	cout << "Found (" << key << ") at index " << search(arr, key) << endl;

	key = 8;
	printVector(arr);
	cout << "Found (" << key << ") at index " << search(arr, key) << endl;

	key = 11;
	printVector(arr);
	cout << "Found (" << key << ") at index " << search(arr, key) << endl;


	vector<int> arr2{ 5, 6, 7, 8, 9, 10, 1, 2, 3 };
	key = 30;
	printVector(arr2);
	cout << "Found (" << key << ") at index " << search(arr2, key) << endl;


	vector<int> arr3{ 30, 40, 50, 10, 20 };
	key = 10;
	printVector(arr3);
	cout << "Found (" << key << ") at index " << search(arr3, key) << endl;
	return 0;
}

int search(vector<int>& nums, int target)
{
	int pivot = findPivot(nums);
	
	if (target == nums[pivot])
	{
		return pivot;
	}

	vector<int> low(nums.begin() + pivot, nums.end());
	vector<int> high(nums.begin(), nums.begin() + pivot);

	vector<int>* searchTarget = NULL;
	int toAddIndex = 0;

	if (target < nums[pivot - 1] && target > nums[nums.size() - 1])
	{
		searchTarget = &high;
	}
	else
	{
		searchTarget = &low;
		toAddIndex = pivot;
	}
	
	int index = binarySearch(*searchTarget, target);

	if (index != -1)
	{
		index += toAddIndex;
	}

	return index;
}

int findPivot(vector<int> nums)
{
	if (nums.empty())
	{
		return -1;
	}
	else if (nums.size() == 1)
	{
		return 0;
	}
	else if (nums.size() == 2)
	{
		return -1;
	}

	int pivot = nums.size() / 2;

	if (nums[pivot - 1] < nums[pivot]
		&& nums[pivot + 1] > nums[pivot])
	{
		int index = -1;
		vector<int> low(nums.begin(), nums.begin() + pivot);
		index = findPivot(low);
		
		if (index == -1)
		{
			vector<int> high(nums.begin() + pivot, nums.end());
			index = findPivot(high);

			if (index != -1)
			{
				index += low.size();
			}
		}

		return index;
	}
	
	return pivot;
}

int binarySearch(vector<int> nums, int target)
{
	if (nums.empty())
	{
		return -1;
	}
	else if (nums.size() == 1)
	{
		if (target == nums[0])
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}

	int pivot = nums.size() / 2;

	if (target < nums[pivot])
	{
		int index = -1;
		vector<int> low(nums.begin(), nums.begin() + pivot);
		index = binarySearch(low, target);

		return index;
	}
	else if (target > nums[pivot])
	{
		int index = -1;
		vector<int> high(nums.begin() + pivot, nums.end());
		index = binarySearch(high, target);

		if (index == -1)
		{
			return index;
		}
		
		return index + pivot;
	}
	else if (target == nums[pivot])
	{
		return pivot;
	}

	return -1;
}

void printVector(const vector<int>& nums)
{
	cout << endl << "[";

	for (size_t i = 0; i < nums.size(); ++i)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << nums[i];
	}

	cout << "]" << endl;
}
