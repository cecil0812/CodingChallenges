#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > combinationSum(const vector<int>& candidates, int target);
void comboSum(const vector<int>& candidates, int sum, vector<vector<int> >& solutions, vector<int>& set, int i);
void printSolutions(const vector<vector<int> >& solutions);

int main(int argc, char* argv[])
{
	vector<int> candidates;
	candidates.push_back(2);
	candidates.push_back(3);
	candidates.push_back(4);
	int target = 5;

	vector<vector<int> > solutions = combinationSum(candidates, target);
	cout << "Target = " << target << endl << "Solutions: " << endl;
	printSolutions(solutions);
	cout << endl;

	solutions.clear();
	candidates.clear();
	candidates.push_back(2);
	candidates.push_back(3);
	candidates.push_back(6);
	candidates.push_back(7);
	target = 7;

	solutions = combinationSum(candidates, target);
	cout << "Target = " << target << endl << "Solutions: " << endl;
	printSolutions(solutions);
	cout << endl;

	
	solutions.clear();
	candidates.clear();
	candidates.push_back(2);
	candidates.push_back(3);
	candidates.push_back(5);
	target = 8;

	solutions = combinationSum(candidates, target);
	cout << "Target = " << target << endl << "Solutions: " << endl;
	printSolutions(solutions);
	cout << endl;

	return 0;
}

vector<vector<int> > combinationSum(const vector<int>& candidates, int target)
{
	vector<vector<int> > solutions;
	vector<int> set;

	comboSum(candidates, target, solutions, set, 0);

	return solutions;
}

void comboSum(const vector<int>& candidates, int sum, vector<vector<int> >& solutions, vector<int>& set, int i)
{
	if (sum < 0)
	{
		return;
	}

	// if we get exact answer 
	if (sum == 0)
	{
		solutions.push_back(set);
		return;
	}

	// Recur for all remaining elements that 
	// have value smaller than sum. 
	while (i < candidates.size() && sum - candidates[i] >= 0)
	{

		// Till every element in the array starting 
		// from i which can contribute to the sum 
		set.push_back(candidates[i]); // add them to list 

		// recur for next numbers 
		comboSum(candidates, sum - candidates[i], solutions, set, i);

		i++;

		// remove number from list (backtracking) 
		set.pop_back();
	}
}

void printSolutions(const vector<vector<int> >& solutions)
{
	for (size_t i = 0; i < solutions.size(); ++i)
	{
		cout << "[";
		for (size_t k = 0; k < solutions[i].size(); ++k)
		{
			if (k != 0)
			{
				cout << ", ";
			}

			cout << solutions[i][k];
		}

		cout << "]" << endl;
	}
}
