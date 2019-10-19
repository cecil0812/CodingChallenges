#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<string> allPermutations(const string& s, const string& b);
void createPerms(const string& s, map<string, string>& perms);
template <class T>
void printVector(const vector<T>& v);

/*
Example:
s = abbc
b = babcabbacaabcbabcacbb
Walk through the first s.length() characters of b and see if there is a permutation.
*/
int main(int argc, char* argv[])
{
	string s = "abbc";
	string b = "babcabbacaabcbabcacbb";

	vector<string> combos = allPermutations(s, b);

	cout << "Permutations of '" << s << "' in " << "'" << b << "'" << endl;
	printVector(combos);

	return 0;
}

vector<string> allPermutations(const string& s, const string& b)
{
	vector<string> combos;
	map<string, string> perms;

	createPerms(s, perms);

	for (size_t i = 0; i < b.length() - s.length() + 1; ++i)
	{
		string temp = b.substr(i, s.length());

		if (perms.find(temp) != perms.end())
		{
			combos.push_back(temp);
		}
	}

	return combos;
}

void createPerms(const string& s, map<string, string>& perms)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		char letter = s[i];

		for (size_t j = 0; j < s.length(); ++j)
		{
			string temp(s);
			char tempChar = temp[i];
			temp[i] = temp[j];
			temp[j] = letter;

			perms[temp] = temp;
		}
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
