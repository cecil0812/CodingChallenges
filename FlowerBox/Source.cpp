#include <iostream>
#include <vector>

using namespace std;


bool canPlant(vector<bool> flowerBox, int number);

template <class T>
void printVector(const vector<T>& v);


int main(int argc, char* argv[])
{
	vector<bool> box{ false, false, false, false, false };
	int num = 3;
	bool res = canPlant(box, num);

	printVector(box);
	cout << "Planting " << num << " flowers = " << (res ? "true" : "false") << endl;


	vector<bool> box2{ false, false, true, false, true };
	num = 3;
	res = canPlant(box2, num);

	printVector(box2);
	cout << "Planting " << num << " flowers = " << (res ? "true" : "false") << endl;


	vector<bool> box3{ true, false, false, false, true };
	num = 1;
	res = canPlant(box3, num);

	printVector(box3);
	cout << "Planting " << num << " flowers = " << (res ? "true" : "false") << endl;

	return 0;
}

bool canPlant(vector<bool> flowerBox, int number)
{
	if (flowerBox.size() < number)
	{
		return false;
	}

	int index = 0;

	while (index < flowerBox.size() && number != 0)
	{
		int prevIndex = index - 1;
		int nextIndex = index + 1;

		if (index == 0)
		{
			prevIndex = index;
		}
		else if (index == flowerBox.size() - 1)
		{
			nextIndex = index;
		}
		
		if (!flowerBox[prevIndex] && !flowerBox[index] && !flowerBox[nextIndex])
		{
			--number;
			flowerBox[index] = true;
		}

		++index;
	}

	return (number == 0 ? true : false);
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
