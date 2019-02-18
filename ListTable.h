#pragma once
#include <sstream>
#include <iostream>
#include <ostream>
#include "linearList.h"

using namespace std;

template<typename T>
struct chainNode
{
	chainNode(){}

	chainNode(const T& element):m_element(element),m_lpNext(NULL){}

	chainNode(const T& element, chainNode<T>* lpNext) :m_element(element),m_lpNext(lpNext){}
	
	chainNode<T>* m_lpNext;
	T m_element;
};

template<typename T>
class chain : public linearList<T>
{
public:
	chain(int capacity = 10);

	chain(const chain<T>& list);

	~chain();

	bool empty() const { return m_listSize == 0; }

	int size() const { return m_listSize; }

	T& get(int index) const;

	int indexOf(const T& theElement) const;

	void insert(int theIndex, const T& theElement);

	void erase(int theIndex);

	void output(ostream& os) const;

protected:
	void checkIndex(int theIndex) const;
	chainNode<T>* m_lpHead;
	int m_listSize;
};


template<typename T>
chain<T>::chain(int capacity /* = 10 */)
{
	if (capacity < 0)
	{
		ostringstream s;
		s << "capacity" << capacity << "must be > 0" << endl;
		throw s.str();
	}
	m_lpHead = NULL;
	m_listSize = 0;
}


template<typename T>
chain<T>::chain(const chain<T>& list)
{
	m_listSize = list.m_listSize;
	if (m_listSize == 0)
	{
		m_lpHead = NULL;
		return;
	}

	chainNode<T>* sourceNode = list.m_lpHead;
	m_lpHead = new chainNode<T>(sourceNode->m_element);
	sourceNode = sourceNode->m_lpNext;
	chainNode<T>* targetNode = m_lpHead;

	while (sourceNode != NULL)
	{
		targetNode->m_lpNext = new chainNode<T>(sourceNode->m_element);
		targetNode = targetNode->m_lpNext;
		sourceNode = sourceNode->m_lpNext;
	}
	targetNode->m_lpNext = NULL;
}


template<typename T>
chain<T>::~chain()
{
	while (m_lpHead != NULL)
	{
		chainNode<T>* lp = m_lpHead->m_lpNext;
		delete m_lpHead;
		m_lpHead = lp;
	}
}


template<typename T>
void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= m_listSize)
	{
		ostringstream s;
		s << "wrong index" << endl;
		throw s.str();
	}
}


template<typename T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = m_lpHead;
	for (int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->m_lpNext;
	}

	return currentNode->m_element;

}


template<typename T>
int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T>* currentNode = m_lpHead;
	int index = 0;

	while (currentNode != NULL && currentNode->m_element != theElement)
	{
		currentNode = currentNode->m_lpNext;
		index++;
	}

	if (currentNode == NULL)
	{
		return -1;
	}
	else
	{
		return index;
	}
}


template<typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > m_listSize)
	{
		ostringstream s;
		s << "wrong index" << endl;
		throw s.str();
	}

	if (theIndex == 0)
	{
		m_lpHead = new chainNode<T>(theElement, m_lpHead);
	}
	else
	{
		chainNode<T>* p = m_lpHead;
		for (int i = 0; i < theIndex-1; i++)
		{
			p = p->m_lpNext;
		}

		p->m_lpNext = new chainNode<T>(theElement, p->m_lpNext);
	}
	m_listSize++;
}


template<typename T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = m_lpHead;
		m_lpHead = m_lpHead->m_lpNext;
	}
	else
	{
		chainNode<T>* p = m_lpHead;
		for (int i = 0; i < theIndex -1; i++)
		{
			p = p->m_lpNext;
		}
		deleteNode = p->m_lpNext;
		p->m_lpNext = p->m_lpNext->m_lpNext;
	}
	delete deleteNode;
	m_listSize--;
}


template<typename T>
void chain<T>::output(ostream& os) const
{
	for (chainNode<T>* currentNode = m_lpHead; currentNode != NULL; currentNode = currentNode->m_lpNext)
	{
		os << currentNode->m_element << " ";
	}
}


template<typename T>
ostream& operator<<(ostream& out, const chain<T>& list)
{
	list.output(out);
	return out;
}