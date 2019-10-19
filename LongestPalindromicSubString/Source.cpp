/*Input: "babad"
Output : "bab"
Note : "aba" is also a valid answer.
Example 2 :

Input : "cbbd"
Output : "bb"
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string longestPalindrome(const string& s);
string addBoundaries(const string& s);
string removeBoundaries(const string& s);

string longestPalindrome2(const string& s);
int expandAroundCenter(const string& s, int left, int right);


int main(int argc, char* argv[])
{
	string s = "abcdefggfedcbafuckyou";
	//string s = "abacdgfdcaba";
	//string s = "babad";
	string r = longestPalindrome2(s);

	cout << s << endl;
	cout << r << endl;

	return 0;
}

string longestPalindrome(const string& s)
{
	if (s.length() == 0)
	{
		return "";
	}

	string s2 = addBoundaries(s);

	int* p = new int(s2.length());
	
	for (size_t i = 0; i < s2.length(); ++i)
	{
		p[i] = 0;
	}

	int c = 0;
	int r = 0;
	int m = 0;
	int n = 0;

	for (size_t i = 1; i < s2.length(); ++i)
	{
		if (i > r)
		{
			p[i] = 0;
			m = i - 1;
			n = i + 1;
		}
		else
		{
			int i2 = c * 2 - i;

			if (p[i2] < (r - i - 1))
			{
				p[i] = p[i2];
				m = -1; // This signals bypassing the while loop below. 
			}
			else
			{
				p[i] = r - i;
				n = r + 1;
				m = i * 2 - n;
			}
		}

		while (m >= 0 && n < s2.length() && s2[m] == s2[n])
		{
			p[i]++;
			m--;
			n++;
		}

		if ((i + p[i]) > r)
		{
			c = i;
			r = i + p[i];
		}
	}

	int len = 0;
	c = 0;

	for (size_t i = 1; i < s2.length(); ++i)
	{
		if (len < p[i])
		{
			len = p[i];
			c = i;
		}
	}

	string ss = s2.substr(c - len, c + len + 1);
	ss = removeBoundaries(ss);

	return ss;
}

string addBoundaries(const string& s)
{
	ostringstream oss;

	for (size_t i = 0; i < s.length(); ++i)
	{
		oss << "|" << s[i];
	}

	oss << "|";
	return oss.str();
}

string removeBoundaries(const string& s)
{
	ostringstream oss;

	for (size_t i = 0; i < s.length(); ++i)
	{
		if (s[i] != '|')
		{
			oss << s[i];
		}
	}

	return oss.str();
}


string longestPalindrome2(const string& s)
{
	if (s.length() < 1)
	{
		return "";
	}

	int start = 0;
	int end = 0;

	for (int i = 0; i < s.length(); ++i)
	{
		int len1 = expandAroundCenter(s, i, i);
		int len2 = expandAroundCenter(s, i, i + 1);
		int len = (len1 > len2 ? len1 : len2);
		
		if (len > end - start)
		{
			start = i - (len - 1) / 2;
			end = i + len / 2;
		}
	}

	return s.substr(start, end);
}

int expandAroundCenter(const string& s, int left, int right)
{
	int L = left;
	int R = right;

	while (L >= 0 && R < s.length() && s[L] == s[R])
	{
		L--;
		R++;
	}

	return R - L - 1;
}