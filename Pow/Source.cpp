#include <iostream>
#include <vector>

using namespace std;

double mypow(double x, int n);
double fast_power(double x, int n);


int main(int argc, char* argv[])
{
	cout << mypow(2.0, 10) << endl;
	cout << mypow(2.1, 3) << endl;
	cout << mypow(2.0, -2) << endl;

	cout << fast_power(2.0, 100) << endl;
	cout << fast_power(2.0, 10) << endl;
	cout << fast_power(2.1, 3) << endl;
	cout << fast_power(2.0, -2) << endl;
	
	return 0;
}

double mypow(double x, int n)
{
	double result = x;

	if (n == 0)
	{
		return 1.0;
	}

	bool isNeg = false;

	if (n < 0)
	{
		n *= -1;
		isNeg = true;
	}

	for (int i = 1; i < n; ++i)
	{
		result *= x;
	}

	if (isNeg)
	{
		result = 1.0 / result;
	}

	return result;
}

double fast_power(double x, int n)
{
	double result = 1;

	bool isNeg = false;

	if (n < 0)
	{
		n *= -1;
		isNeg = true;
	}

	while (n > 0)
	{
		// Can also use (power & 1) to make code even faster
		if (n % 2 == 1)
		{
			result = (result * x);
		}

		x = (x * x);
		n = n / 2; // Can also use power >>= 1; to make code even faster
	}

	if (isNeg)
	{
		result = 1.0 / result;
	}

	return result;
}
