#include <iostream>
#include <vector>

using namespace std;


/*
Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.
*/
int jump(const vector<int>& nums);
int jump(size_t currentIndex, int currentJumpCount, vector<int>& allJumps, const vector<int>& nums);

int main(int argc, char* argv[])
{
	vector<int> nums;
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(4);

	int jumps = jump(nums);

	cout << "[";
	for (size_t i = 0; i < nums.size(); ++i)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << nums[i];
	}
	cout << "]" << endl;

	cout << jumps << endl;

	return 0;
}

int jump(const vector<int>& nums)
{
	vector<int> allJumps;

	jump(0, 0, allJumps, nums);

	int lowest = nums.size();

	for (size_t i = 0; i < allJumps.size(); ++i)
	{
		if (allJumps[i] < lowest)
		{
			lowest = allJumps[i];
		}
	}

	return lowest;
}

int jump(size_t currentIndex, int currentJumpCount, vector<int>& allJumps, const vector<int>& nums)
{
	++currentJumpCount;
	size_t endingPos = nums.size() - 1;
	int jumps = 0;

	int jumper = nums[currentIndex];
	int distance = endingPos - currentIndex;

	//See if we can get to the end immediately.
	if (jumper + currentIndex >= endingPos)
	{
		++jumps;
		return jumps;
	}

	for (size_t i = jumper; i > 0; --i)
	{
		int result = jump(currentIndex + i, currentJumpCount, allJumps, nums);

		if (result != 0)
		{
			currentJumpCount += result;
			allJumps.push_back(currentJumpCount);
			currentJumpCount = 0;
		}
	}

	return 0;
}
