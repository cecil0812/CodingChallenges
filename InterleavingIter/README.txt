Interleaving Iterator, supposedly an old Google question.

Basically, write a class that will take in n number of iterators (I used vector<int>::iterator for simplicity).

When calling next(), the iterator should interleave the iterators so that it first gets an element from the first one, then the second one, etc.

Example:

vector<int> odds{ 1, 3, 5, 7 };
vector<int> evens{ 2, 4, 6, 8 };

InterleavingIter<int> it;
it.AddIter(odds.begin(), odds.end());
it.AddIter(evens.begin(), evens.end());


while (it.hasNext())
{
	cout << it.next() << " ";
}

// prints 1 2 3 4 5 6 7 8



Keep in mind the lists don't have to be the same size:

vector<int> arr1 = { 1, 2, 3 };
vector<int> arr2 = { 4, 5 };
vector<int> arr3 = { 6, 7, 8, 9 };
	
InterleavingIter<int> it;
it.AddIter(arr1.begin(), arr1.end());
it.AddIter(arr2.begin(), arr2.end());
it.AddIter(arr3.begin(), arr3.end());

while (it.hasNext())
{
	cout << it.next() << " ";
} // prints 1 4 6 2 5 7 3 8 9

// next() should throw an exception if you call it passed the end of all iterators:
try
{
	it.next();
}
catch (runtime_error ex)
{
	cout << ex.what << endl;
}
