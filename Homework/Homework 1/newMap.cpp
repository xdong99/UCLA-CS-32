#include <iostream>
#include "newMap.h"

using namespace std;

Map::Map()	// Create an empty map (i.e., one with no key/value pairs)
{
	pairs = new mapPair[DEFAULT_MAX_ITEMS];
	pair_size = DEFAULT_MAX_ITEMS;
	used = 0;
}

Map::Map(int newSize)
{
	pair_size = newSize;
	pairs = new mapPair[pair_size];
	used = 0;
}

Map::~Map()
{
	delete[]pairs;
}

Map::Map(const Map& src)
{
	pair_size = src.pair_size;
	pairs = new mapPair[pair_size];
	used = src.used;
	for (int i = 0; i < pair_size; i++)
	{
		pairs[i] = src.pairs[i];
	}
}

Map& Map::operator=(const Map& src)
{
	delete[]pairs;

	pair_size = src.pair_size;
	pairs = new mapPair[pair_size];
	used = src.used;
	for (int i = 0; i < pair_size; i++)
	{
		pairs[i] = src.pairs[i];
	}
	return (*this);
}

bool Map::empty() const	// Return true if the map is empty, otherwise false.
{
	if (used == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Map::size() const	// Return the number of key/value pairs in the map.
{
	return used;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
	if (used == pair_size)
	{
		return false;
	}
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			return false;
		}
	}
	pairs[used].k = key;
	pairs[used].v = value;
	used++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			pairs[i].v = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			pairs[i].v = value;
			return true;
		}
	}
	if (used == pair_size)
	{
		return false;
	}
	else
	{
		pairs[used].k = key;
		pairs[used].v = value;
		used++;
		return true;
	}
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			for (int j = 0; j < used - 1; j++)
			{
				pairs[j] = pairs[j + 1];
			}
			used--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	for (int i = 0; i < used; i++)
	{
		if (pairs[i].k == key)
		{
			value = pairs[i].v;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.
{
	Map copy;
	for (int j = 0; j < used; j++)
	{
		copy.pairs[j] = pairs[j];
	}

	for (int a = 0; a < used; a++)
	{
		for (int b = a + 1; b < used; b++)
		{
			Map temp;
			if (copy.pairs[b].k < copy.pairs[a].k)
			{
				temp.pairs[a] = copy.pairs[a];
				copy.pairs[a] = copy.pairs[b];
				copy.pairs[b] = temp.pairs[a];
			}
		}
	}

	if (i >= 0 && i < used)
	{
		key = copy.pairs[i].k;
		value = copy.pairs[i].v;
		return true;
	}
	return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
	Map temp = other;
	other = *this;
	*this = temp;
}