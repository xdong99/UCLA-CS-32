#include <iostream>
#include "Map.h"

using namespace std;

Map::Map()
{
	head = nullptr;
	tail = nullptr;
	nItems = 0;
}

Map::~Map()
{
	if (nItems > 0)
	{
		Node* ptr = head;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
			delete ptr->previous;
		}
		delete ptr;

		head = nullptr;
		tail = nullptr;
		nItems = 0;
	}
}

Map::Map(const Map& other) //the copy constructor
{
	nItems = other.nItems;
	
	if (other.nItems == 0) { // if other is empty, set this to empty and return
		head = nullptr;
		tail = nullptr;
		return;
	}

	// creating new linked list
	head = new Node;
	head->previous = nullptr;

	Node* ptr = head;

	// copies all but the last node, dynamically allocating new nodes along the way
	for (Node* cPtr = other.head; cPtr->next != nullptr; cPtr = cPtr ->next) 
	{
		Node* newNode = new Node;

		ptr->k = cPtr->k;
		ptr->v = cPtr->v;
		ptr->next = newNode;
		newNode->previous = ptr;

		ptr = newNode;
	}

	//copies data to last node and sets next to nullptr
	ptr->k = other.tail->k;
	ptr->v = other.tail->v;
	ptr->next = nullptr;

	//sets tail pointer
	tail = ptr;
}

Map& Map::operator=(const Map& rhs)
{
	if (this != &rhs)
	{
		Map temp(rhs);
		swap(temp);
	}
	return *this;
}

bool Map::empty() const
{
	return (head == nullptr);
}

int Map::size() const
{
	return nItems;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (nItems == 0)
	{
		head = new Node;
		tail = head;

		head->k = key;
		head->v = value;
		head->next = nullptr;
		head->previous = nullptr;
	}
	else
	{
		 Node* ptr = head;
		 if (ptr->k == key)
			 return false;
		 while (ptr->next != nullptr) 
		 {
			 ptr = ptr->next;  // traverse to the last node in the doubly-linked list
			 if (ptr->k == key)
				 return false;
		 }

		 ptr->next = new Node;
		 ptr->next->k = key;
		 ptr->next->v = value;
		 ptr->next->next = nullptr;
		 ptr->next->previous = ptr;
		 tail = ptr->next;
	}
	nItems++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	if (nItems == 0)
	{
		return false;
	}
	else
	{
		Node* ptr = head;
		if (ptr->k == key)
		{
			ptr->v = value;
			return true;
		}

		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
			if (ptr->k == key)
			{
				ptr->v = value;
				return true;
			}
		}
		return false;
	}
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (!insert(key, value))
	{
		update(key, value);
	}
	return true;
}

bool Map::erase(const KeyType& key) 
{
	if (nItems == 0)
		return false;
	else 
	{
		Node* ptr = head;
		if (head->k == key) 
		{ // erase the first node
			if (ptr->next != nullptr) { // the "Map" has more than one node
				head = ptr->next;
				ptr->next->previous = nullptr;
				delete ptr;
				nItems--;
				return true;
			}
			else 
			{ // the "Map" has only one node
				head = nullptr;
				tail = nullptr;
				delete ptr;
				nItems--;
				return true;
			}
		}

		while (ptr->next != nullptr) 
		{ // traverse to every node
			ptr = ptr->next;

			if (ptr->k == key) 
			{
				if (ptr->next != nullptr) 
				{ // the node to erase is not the last node
					ptr->previous->next = ptr->next;
					ptr->next->previous = ptr->previous;
					delete ptr;
					nItems--;
					return true;
				}
				else 
				{ // the node to erase is the last node
					ptr->previous->next = nullptr;
					tail = ptr->previous;
					delete ptr;
					nItems--;
					return true;
				}
			}
		}
		return false;
	}
}

bool Map::contains(const KeyType& key) const
{
	if (nItems == 0)
	{
		return false;
	}
	else
	{
		Node* ptr = head;
		if (ptr->k == key)
		{
			return true;
		}

		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
			if (ptr->k == key)
			{
				return true;
			}
		}
		return false;
	}
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (nItems == 0)
	{
		return false;
	}
	else
	{
		Node* ptr = head;
		if (ptr->k == key)
		{
			value = ptr->v;
			return true;
		}

		while (ptr->next != nullptr)
		{
			ptr = ptr->next;

			if (ptr->k == key)
			{
				value = ptr->v;
				return true;
			}
		}
		return false;
	}
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (!(i >= 0 && i < nItems))
	{
		return false;
	}

	else
	{
		if (nItems == 0)
		{
			return false;
		}
		else if (head->next == nullptr)
		{
			key = head->k;
			value = head->v;
			return true;
		}
		else
		{

			Node* p = new Node();
			Node* q = new Node();
			KeyType tempK;
			ValueType tempV;
			for (p = head; p->next != nullptr; p = p->next)
			{
				for (q = p->next; q != nullptr; q = q->next)
				{
					if (q->k < p->k)
					{
						tempK = q->k;
						q->k = p->k;
						p->k = tempK;

						tempV = q->v;
						q->v = p->v;
						p->v = tempV;
						
					}
				}
			}
		}
		
		int count = 0;
		Node* ptr2 = head;
		if (i == count)
		{
			key = ptr2->k;
			value = ptr2->v;
			return true;
		}

		while (ptr2->next != nullptr)
		{
			ptr2 = ptr2->next;
			count++;

			if (i == count)
			{
				key = ptr2->k;
				value = ptr2->v;
				return true;
			}
		}
		return false;
	}
}

void Map::swap(Map& other) 
{
	Node* tempHead; // swap the "head" pointer
	tempHead = other.head;
	other.head = head;
	head = tempHead;

	Node* tempTail; // swap the "tail" pointer
	tempTail = other.tail;
	other.tail = tail;
	tail = tempTail;

	int tempNItems; // swap "nItems"
	tempNItems = other.nItems;
	other.nItems = nItems;
	nItems = tempNItems;
}

bool merge(const Map& m1, const Map& m2, Map& result) 
{
	Map combinedMap = *new Map; // create a new "Map" to store result, to avoid aliasing

	bool hasConflict = false;
	for (int i = 0; i < m1.size(); i++) 
	{
		KeyType key;
		ValueType value;
		m1.get(i, key, value);

		if (m2.contains(key)) 
		{
			ValueType value2;
			m2.get(key, value2);
			if (value != value2) 
			{
				hasConflict = true;
			}
			else
			{
				combinedMap.insertOrUpdate(key, value);
			}
		}
		else
		{
			combinedMap.insertOrUpdate(key, value);
		}
	}

	for (int i = 0; i < m2.size(); i++) 
	{
		KeyType key;
		ValueType value;
		m2.get(i, key, value);

		if (!m1.contains(key))
			combinedMap.insertOrUpdate(key, value);
	}

	result = combinedMap;

	if (hasConflict)
		return false;
	else
		return true;
}

void reassign(const Map& m, Map& result)
{
	Map reassignedMap = *new Map;

	if (m.size() == 1)
	{
		reassignedMap = m;
	}
	else
	{
		KeyType key1;
		ValueType value1;
		m.get(0, key1, value1);

		for (int i = 0; i < m.size() - 1; i = i + 2)
		{
			KeyType key2;
			ValueType value2;
			KeyType key3;
			ValueType value3;
			m.get(i, key2, value2);
			m.get(i + 1, key3, value3);
			
			ValueType temp;
			temp = value2;
			value2 = value3;
			value3 = temp;

			reassignedMap.insert(key2, value2);
			reassignedMap.insert(key3, value3);
		}
		KeyType key4;
		ValueType value4;

		m.get(m.size() - 1, key4, value4);
		value4 = value1;

		reassignedMap.insert(key4, value4);

	}
	result = reassignedMap;
}