#ifndef _MY_SET_H
#define _MY_SET_H

#include "MyBalancedTree.h"

template <class T>
class MySet
{
private:

	MyBalancedTree<T> data;
	size_t dataSize;

	static bool EqualCmp(MySet<T>& set, T value)
	{
		return set.find(value);
	}

	static bool NotEqualCmp(MySet<T>& set, T value)
	{
		return !set.find(value);
	}

	MySet<T>& getUnionWithPred(MySet<T>& set, bool(*f)(MySet<T>&, T))
	{
		MyBalancedTree<T>::iterator iter = this->data.begin();
		MySet<T>* newSet = new MySet<T>();

		while (iter != this->data.end())
		{
			T value = (*iter).value;

			if (f(set, value))
			{
				newSet->insert(value);
			}

			++iter;
		}

		return *newSet;
	}

public:

	MySet()
	{
		dataSize = 0;
	}
	
	size_t size()
	{
		return dataSize;
	}

	void insert(T value)
	{
		if (data.insert(value))
		{
			++dataSize;
		}
	}

	bool find(T value)
	{
		return this->data.find(value);
	}

	void erase(T value)
	{
		if (data.erase(value))
		{
			--dataSize;
		}
	}

	MySet<T>& getUnion(MySet<T>& set)
	{
		return getUnionWithPred(set, MySet<T>::EqualCmp);
	}

	// Find T that only appears in this set.  If it appears in set, it is excluded
	MySet<T>& getUnionToSet(MySet<T>& set)
	{
		return getUnionWithPred(set, MySet<T>::NotEqualCmp);
	}
};

#endif
