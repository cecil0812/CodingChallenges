#include <iostream>
#include <string>

using namespace std;

bool isMatch(const string& s, const string& p);

int main(int argc, char* argv[])
{
	// False
	//string s = "aa";
	//string p = "a";

	// True
	//string s = "aa";
	//string p = "*";

	// False
	//string s = "cb";
	//string p = "?";

	// True
	//string s = "adceb";
	//string p = "a*b";

	// False
	//string s = "acdcb";
	//string p = "a*c?b";

	// True
	string s = "abcdefg";
	string p = "a*def?";
	
	cout << s << " is match with " << p << " " << isMatch(s, p) << endl;

	return 0;
}

bool isMatch(const string& s, const string& p)
{
	bool patternMatched = true;
	size_t sindex = 0;
	size_t i = 0;

	while (i < p.length() && sindex < s.length())
	{
		if (p[i] != '?' && p[i] != '*')
		{
			if (p[i] != s[sindex])
			{
				return false;
			}

			++sindex;
			++i;
		}
		else
		{
			if (p[i] == '?')
			{
				++sindex;
				++i;
			}
			else if (p[i] == '*')
			{
				if (i == p.length() - 1)
				{
					// We've nothing else to match and the last thing is a *
					return true;
				}

				if (p[i + 1] == '*') // invalid
				{
					return false;
				}

				char nextChar = p[i + 1];
				i += 2;
				bool usedStarUp = false;
				
				++sindex;
				while (sindex < s.length() && !usedStarUp)
				{
					if (s[sindex] == nextChar)
					{
						usedStarUp = true;
					}

					++sindex;
				}
			}
		}
	}

	if (sindex < s.length() || i < p.length())
	{
		return false;
	}

	return patternMatched;
}
