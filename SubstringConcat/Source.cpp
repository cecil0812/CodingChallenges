#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findSubstring(string s, vector<string>& words);
void doMatch(const string& s, const string& matcher, vector<int>& results);

/*
You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in 
words exactly once and without any intervening characters.

Input:
s = "barfoothefoobarman",
words = ["foo", "bar"]
Output : [0, 9]
	Explanation : Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
	The output order does not matter, returning[9, 0] is fine too.
*/
int main(int argc, char* argv[])
{
	/*string s = "barfoothefoobarman";
	vector<string> words;
	words.push_back("foo");
	words.push_back("bar");*/

	//string s = "wordgoodgoodgoodbestword";
	string s = "wordgoodbestwordgoodbestword";
	vector<string> words;
	words.push_back("word");
	words.push_back("good");
	words.push_back("best");
	words.push_back("word");

	cout << "s: " << s << endl;
	cout << "words: ";
	cout << "[";

	for (size_t i = 0; i < words.size(); ++i)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << words[i];
	}

	cout << "]" << endl;

	vector<int> res = findSubstring(s, words);

	cout << "[";

	for (size_t i = 0; i < res.size(); ++i)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << res[i];
	}

	cout << "]" << endl;

	return 0;
}

vector<int> findSubstring(string s, vector<string>& words)
{
	vector<int> result;
	string forwards;
	string backwards;

	for (size_t i = 0; i < words.size(); ++i)
	{
		forwards.append(words[i]);
		string temp = words[i];
		temp.append(backwards);
		backwards = temp;
	}

	doMatch(s, forwards, result);
	doMatch(s, backwards, result);

	return result;
}

void doMatch(const string& s, const string& matcher, vector<int>& results)
{
	size_t pos = s.find(matcher, 0);

	while (pos != string::npos)
	{
		results.push_back(pos);
		pos = s.find(matcher, pos + 1);
	}
}
