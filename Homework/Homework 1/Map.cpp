#include <iostream>
#include "Map.h"

using namespace std;

Map::Map()	// Create an empty map (i.e., one with no key/value pairs)
{
	pair_size = 0;
}

bool Map::empty() const	// Return true if the map is empty, otherwise false.
{
	if (pair_size == 0)
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
	return pair_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
	if (pair_size == DEFAULT_MAX_ITEMS)
	{
		return false;
	}
	for (int i = 0; i < pair_size; i++)
	{
		if (pairs[i].k == key)
		{
			return false;
		}
	}

	pairs[pair_size].k = key;
	pairs[pair_size].v = value;

	pair_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	for (int i = 0; i < pair_size; i++)
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
	for (int i = 0; i < pair_size; i++)
	{
		if (pairs[i].k == key)
		{
			pairs[i].v = value;
			return true;
		}
	}
	if (pair_size == DEFAULT_MAX_ITEMS)
	{
		return false;
	}
	else
	{
		pairs[pair_size].k = key;
		pairs[pair_size].v = value;
		pair_size++;
		return true;
	}
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	for (int i = 0; i < pair_size; i++)
	{
		if (pairs[i].k == key)
		{
			for (int j = 0; j < pair_size - 1; j++)
			{
				pairs[j] = pairs[j + 1];
			}
			pair_size--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	for (int i = 0; i < pair_size; i++)
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
	for (int i = 0; i < pair_size; i++)
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
	for (int j = 0; j < pair_size; j++)
	{
		copy.pairs[j] = pairs[j];
	}

	for (int a = 0; a < pair_size; a++)
	{
		for (int b = a + 1; b < pair_size; b++)
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

	if (i >= 0 && i < pair_size)
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
	other.pair_size = pair_size;
	for (int i = 0; i < pair_size; i++)
	{
		other.pairs[i] = pairs[i];
	}

	pair_size = temp.size();
	for (int i = 0; i < pair_size; i++)
	{
		pairs[i] = temp.pairs[i];
	}
}