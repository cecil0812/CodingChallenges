#ifndef _InterleavingIter_H
#define _InterleavingIter_H

#include <iostream>
#include <vector>

using std::vector;


#define _INIT_SIZE 5;

template <typename T>
class InterleavingIter
{
private:

	typename typedef std::vector<T>::iterator my_iter_container;

	struct AllIterators
	{
		my_iter_container curIter;
		my_iter_container end;
	};

	AllIterators* iterators;
	int currentSize;
	int currentUsed;
	int index;

	void resize()
	{
		AllIterators* temp = new AllIterators[currentSize];
		
		for (int i = 0; i < currentSize; ++i)
		{
			temp[i] = iterators[i];
		}

		delete[] iterators;

		int oldSize = currentSize;
		currentSize *= 2;
		iterators = new AllIterators[currentSize];

		for (int i = 0; i < oldSize; ++i)
		{
			iterators[i] = temp[i];
		}

		delete[] temp;
	}

	AllIterators* hasNextIter(bool incrementIndex)
	{
		AllIterators* iterToUse = NULL;
		int prevIndex = index;

		do
		{
			if (iterators[index].curIter != iterators[index].end)
			{
				iterToUse = &iterators[index];
			}

			++index;

			if (index >= currentUsed)
			{
				index = 0;
			}
		} while (iterToUse == NULL && index != prevIndex);

		if (!incrementIndex)
		{
			index = prevIndex;
		}

		return iterToUse;
	}

public:

	InterleavingIter()
	{
		currentSize = _INIT_SIZE;
		iterators = new AllIterators[currentSize];
		index = 0;
		currentUsed = 0;
	}

	~InterleavingIter()
	{
		delete [] iterators;
	}

	void AddIter(my_iter_container begin, my_iter_container end)
	{
		if (currentUsed + 1 >= currentSize)
		{
			resize();
		}

		AllIterators temp;
		temp.curIter = begin;
		temp.end = end;

		iterators[currentUsed++] = temp;
	}

	bool hasNext()
	{
		return (hasNextIter(false) != NULL);
	}

	T next()
	{
		AllIterators* iterToUse = hasNextIter(true);

		if (iterToUse == NULL)
		{
			throw(std::runtime_error("InterleavingIter::next() - Out of range error."));
		}

		T temp = *(iterToUse->curIter);
		++iterToUse->curIter;

		if (index >= currentUsed)
		{
			index = 0;
		}
		
		return temp;
	}
};

#endif
