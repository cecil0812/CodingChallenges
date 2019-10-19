#include <iostream>
#include <sstream>

using namespace std;

string addNumbers(string a, string b);
int addZeroDigits(string& result, const string& from, int finishedIndex, int count);
void doRemainingAddition(string& result, const string& from, int startIndex, int rem);


int main(int argc, char* argv[])
{
	/*string a = "3.14";
	string b = ".91";
	string c = addNumbers(a, b); // 4.05

	string a1 = ".91";
	string b1 = "3.14";
	string c1 = addNumbers(a1, b1); // 4.05

	string a2 = "1.91";
	string b2 = "333.1412";
	string c2 = addNumbers(a2, b2); //335.0512

	string a3 = "47426246591237423.3985486002482462467";
	string b3 = "36484591.37353355489069";
	string c3 = addNumbers(a3, b3);
	//47426246627722014.7720821551389362467
	//47426246627722014.6820821551389362467
	//47426246527722014.7720821551389362467

	string c4 = addNumbers(b3, a3);*/


	string a5 = "4742";
	string b5 = "3648.34";
	string c5 = addNumbers(b5, a5);

	/*cout << a << " + " << b << " = " << c << endl;
	cout << a1 << " + " << b1 << " = " << c1 << endl;
	cout << a2 << " + " << b2 << " = " << c2 << endl;
	cout << a3 << " + " << b3 << " = " << c3 << endl;
	cout << b3 << " + " << a3 << " = " << c4 << endl;*/
	cout << a5 << " + " << b5 << " = " << c5 << endl;

	return 0;
}

// 3.14 + .91 = 4.05
string addNumbers(string a, string b)
{
	size_t decimalA = a.find(".");
	size_t decimalB = b.find(".");

	if (decimalA == string::npos)
	{
		decimalA = a.length() - 1;
	}

	if (decimalB == string::npos)
	{
		decimalB = b.length() - 1;
	}

	string result = "";

	size_t startIndexB = b.length() - 1 - decimalB;
	size_t startIndexA = a.length() - 1 - decimalA;
	int aIndex = a.length() - 1;
	int bIndex = b.length() - 1;

	if (startIndexB > startIndexA)
	{
		bIndex = addZeroDigits(result, b, bIndex, startIndexB - startIndexA);

		if (b[bIndex] == '.')
		{
			--bIndex;
		}

		if (startIndexA == 0)
		{
			result.append(".");
		}
	}
	else if (startIndexB < startIndexA)
	{
		aIndex = addZeroDigits(result, a, aIndex, startIndexA - startIndexB);
	}

	int bval = b[bIndex] - '0';

	int rem = 0;

	for (; aIndex >= 0; --aIndex)
	{
		if (a[aIndex] == '.')
		{
			result.append(".");
			continue;
		}

		int aval = a[aIndex] - '0';
		
		int val = aval + bval;
		rem = val / 10;
		val = val % 10;

		ostringstream oss;
		oss << val;
		result.append(oss.str());

		if (bIndex - 1 >= 0)
		{
			char b1 = b[--bIndex];

			if (b1 == '.')
			{
				if (bIndex - 1 >= 0)
				{
					b1 = b[--bIndex];
				}
				else
				{
					break;
				}
			}

			bval = b1 - '0';
			bval += rem;

			// this is only used if we end after this.
			rem = bval / 10;
		}
		else
		{
			break;
		}
	}

	if (aIndex >= 0)
	{
		doRemainingAddition(result, a, aIndex, rem);
	}
	else if (bIndex >= 0)
	{
		int val = bval + rem;
		rem = val / 10;
		val = val % 10;

		ostringstream oss;
		oss << val;
		result.append(oss.str());

		doRemainingAddition(result, b, bIndex, rem);
	}

	std::reverse(result.begin(), result.end());

	return result;
}

int addZeroDigits(string& result, const string& from, int finishedIndex, int count)
{
	while (count > 0)
	{
		ostringstream oss;
		oss << from[finishedIndex];
		result.append(oss.str());
		--finishedIndex;
		--count;
	}

	return finishedIndex;
}

void doRemainingAddition(string& result, const string& from, int startIndex, int rem)
{
	for (int j = startIndex - 1; j >= 0; --j)
	{
		if (from[j] == '.')
		{
			result.append(".");
		}
		else
		{
			int aval2 = from[j] - '0';
			int val = aval2 + rem;
			rem = val / 10;
			val = val % 10;

			ostringstream oss;
			oss << val;
			result.append(oss.str());
		}
	}
}
