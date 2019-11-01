/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> twoSum(const vector<int>& nums, int target);


int main(int argc, char* argv[])
{
	vector<int> nums = { 2, 7, 11, 15 };
	int target = 17;

	vector<int> result = twoSum(nums, target);

	return 0;
}

vector<int> twoSum(const vector<int>& nums, int target)
{
	vector<int> result;
	map<int, int> complements;
	
	for (size_t i = 0; i < nums.size(); ++i)
	{
		if (complements.find(nums[i]) == complements.end())
		{
			int comp = target - nums[i];
			complements[comp] = i;
		}
		else
		{
			result.push_back(i);
			result.push_back(complements[i]);

			return result;
		}
	}

	return result;
}
