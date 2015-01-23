#include <iostream>
#pragma once
#include "SafeArrayOutOfBoundsException.h"

template <class T>
class SafeArray
{
public:
	SafeArray();
	SafeArray(int numElements);
	SafeArray(SafeArray <T>& copy);
	~SafeArray();
	void push_back(const T&);
	void push_back(SafeArray < T >&);
	void insert(int position, const T&) ;
	void insert(int position, const SafeArray < T >& elems); 
	void resize(int newSize);
	T pop_back();
	T remove(int position);
	void removeRange(int startIndex, int endIndex);
	T& at(int pos);
	T& operator[](int pos);
	int size();

private:
	T* p_array;
	int capacity;
	int numElements;

};

template <class T>
SafeArray <T>:: SafeArray()
{
	int initSize = 10;

	//create a new array on the heap
	p_array = new T[10];
	
	//store the size of the underlying array
	capacity = 10;
	numElements = 10;
}

template <class T>
SafeArray <T>:: SafeArray(int newElements)
{
	if(newElements >= 0)
	{
		int initSize = newElements;

		//create a new array on the heap
		p_array = new T[initSize];
	
		//store the size of the underlying array
		capacity = initSize;
		numElements = initSize;
	}
	else
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
}

template <class T>
SafeArray <T>:: SafeArray(SafeArray <T>& copy)
{
	//creates a new array of a new size
	p_array = new T[copy.capacity];
	
	//will copy over the elements to the new array.
	for(int i = 0; i < copy.size(); i++)
	{
		p_array[i] = copy[i];
	}
	//sets the capacity and the size
	capacity = copy.capacity;
	numElements = copy.size();
}

template <class T>
void SafeArray <T>:: removeRange(int startIndex, int endIndex)
{
	//will call the remove function for each index that needs to be removed.
	for(int i = endIndex; i >= startIndex; i--)
	{
		remove(i);
	}
}

template <class T>
int SafeArray <T>:: size()
{
	//returns the numElements
	return numElements;
}
template <class T>
void SafeArray <T>:: resize(int newSize)
{
	if(newSize > 0)
	{
		//creates a new array of a new size
		T* tempArray = new T[newSize];
		capacity = newSize;
		//sets the new array equal to the p_array
		if(newSize > numElements)
		{
			//sets the temp array to the value of the p_array at each position
			for(int i = 0; i < numElements; i++)
			{
				tempArray[i] = p_array[i];
			}
		}
		else
		{
			if(numElements < newSize)
			{
				for(int i = 0; i < numElements; i++)
				{
					tempArray[i] = p_array[i];
				}
			}
			else
			{
				for(int i = 0; i < newSize; i++)
				{
					tempArray[i] = p_array[i];
				}
				//resets the numElements
				numElements = newSize;
			}

		}
		//deletes the old p_array address
		delete [] p_array;
		//makes p_array point to the new tempArray
		p_array = tempArray;
	}
	else
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
}

template <class T>
SafeArray <T>:: ~SafeArray()
{
	//cout << "All heap data was deleted!" << endl;
	delete [] p_array;
}

template <class T>
void SafeArray <T>:: push_back(const T& newElement)
{
	//checks if there is room for another element
	if(numElements == capacity)
	{
		resize(capacity * 2);
		cout << "Resizing array because the capacity was reached." << endl;
	}
	//adds the new element to the array
	p_array[numElements] = newElement;
	numElements++;
}

template <class T>
void SafeArray <T>:: push_back(SafeArray < T >& addedArray)
{
	//calls push back for each position of the array that will be pushed back
	for(int i = 0; i < addedArray.size(); i++)
	{
		push_back(addedArray[i]);
	}
}

template <class T>
void SafeArray <T>:: insert(int position, const T& elem)
{
	
	if(position < 0 || position > numElements)
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
	//pushback the elem
	push_back(elem);
	//will move the elements into the positions that they are needed to be in.
	for(int i = numElements-2; i >= position; i--)
	{
		p_array[i+1] = p_array[i];
	}
	//sets the position of the inserted element
	p_array[position] = elem;
}
template <class T>
void SafeArray <T>:: insert(int position, const SafeArray < T >& elems)
{
	//calls insert to insert each individual element in the array
	for(int i = 0; i < elems.size(); i++)
	{
		insert(position, elems[i]);
		position++;
	}
}

template <class T>
T SafeArray <T>:: pop_back()
{
	if(numElements > 0)
	{
		//checks if the capacity can be decreased
		if(numElements <= capacity/2)
		{
			resize(capacity/2);
			cout << "Resizing because the number of elements is now less then half of the capacity." << endl;
		}

		//decreases the number of elements in the array
		numElements--;
		//returns the element that was popped back
		return p_array[numElements];
	}
	else
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
}

template <class T>
T SafeArray <T>:: remove(int position)
{
	//checks if it is a valid position to be removed
	if(position >= 0 && position < numElements)
	{
		//holds the element that is going to be removed from the array.
		T holder = p_array[position];
		//moves the elements to fill the removed spot
		for(int i = position; i < (size() - 1); i++)
		{
			p_array[i] = p_array[i+1];
		}
		//changes the number of elements in the array
		numElements--;
		//checks if the array needs to be resized
		if(numElements < capacity/2)
		{
			resize(capacity/2);
		}
		return holder;
	}
	else
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
}

template <class T>
T& SafeArray <T>:: at(int pos)
{
	//will return the element at the pos if it is within the arrays bounds
	if(pos >= 0 && pos < numElements)
	{
		return p_array[pos];
	}
	else
	{
		SafeArrayOutOfBoundsException ex;
		throw ex;
	}
}

template <class T>
T& SafeArray <T>:: operator[](int pos)
{
	return at(pos);
}