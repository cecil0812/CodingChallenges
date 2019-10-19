#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void readFile(vector<string>&magazine, vector<string>&note);
vector<string> split_string(string line, const string delim);
bool canPrintRansomNote(const vector<string>& magazine, const vector<string>& note);
bool canPrintRansomNote2(vector<string> magazine, const vector<string>& note);
template <class T>
void printVector(const vector<T>& v);


int main(int argc, char* argv[])
{
	//vector<string> magazine{ "give", "me", "one", "grand", "today", "night" };
	//vector<string> note{ "give", "one", "grand", "today" };

	//vector<string> magazine{ "two", "times", "three", "is", "not", "four" };
	//vector<string> note{ "two", "times", "two", "is", "four" };

	//vector<string> magazine{ "ive", "got", "a", "lovely", "bunch", "of", "coconuts" };
	//vector<string> note{ "ive", "got", "some", "coconuts" };

	vector<string> magazine;
	vector<string> note;
	readFile(magazine, note);


	//printVector(magazine);
	//printVector(note);

	cout << "Can Print: " << canPrintRansomNote(magazine, note) << endl;
	//cout << "Can Print2: " << canPrintRansomNote2(magazine, note) << endl;
	return 0;
}

void readFile(vector<string>&magazine, vector<string>&note)
{
	ifstream input("myfile.dat", ios::in);
	string line;

	getline(input, line);
	magazine = split_string(line, " ");

	getline(input, line);
	note = split_string(line, " ");

	input.close();
}

bool canPrintRansomNote(const vector<string>& magazine, const vector<string>& note)
{
	map<string, int> magWords;

	for (size_t i = 0; i < magazine.size(); ++i)
	{
		if (magWords.find(magazine[i]) == magWords.end())
		{
			magWords[magazine[i]] = 1;
		}
		else
		{
			++magWords[magazine[i]];
		}
	}

	for (size_t i = 0; i < note.size(); ++i)
	{
		if (magWords.find(note[i]) == magWords.end())
		{
			return false;
		}
		else
		{
			if (magWords[note[i]] - 1 == 0)
			{
				magWords.erase(note[i]);
			}
			else
			{
				--magWords[note[i]];
			}
		}
	}

	return true;
}

bool canPrintRansomNote2(vector<string> magazine, const vector<string>& note)
{
	for (size_t i = 0; i < note.size(); ++i)
	{
		bool foundWord = false;
		vector<string>::iterator iter = magazine.begin();

		while (!foundWord && iter != magazine.end())
		{
			if (*iter == note[i])
			{
				magazine.erase(iter);
				foundWord = true;
			}
			else
			{
				++iter;
			}
		}

		if (!foundWord)
		{
			return false;
		}		
	}

	return true;
}

vector<string> split_string(string line, const string delim)
{
	vector<string> split;

	if (delim == "")
	{
		for (size_t i = 0; i < line.length(); ++i)
		{
			split.push_back(reinterpret_cast<char*>(line[i]));
		}

		return split;
	}

	size_t pos = 0;

	while ((pos = line.find(delim)) != string::npos)
	{
		string sub = line.substr(0, pos);
		split.push_back(sub);

		line = line.substr(pos + 1, line.length() - pos + 1);
	}

	if (line != "")
	{
		split.push_back(line);
	}

	return split;
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
