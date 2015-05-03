#include "stdafx.h"
#include "HashTableRow.h"


HashTableRow::HashTableRow()
{
	this->row = null;
	this->collision = null;
	this->hashKey = null;
	this->key = null; 
}

HashTableRow::HashTableRow(int row, HashIndexType hashKey, int key, int collision)
{
	this->row = row;
	this->hashKey = hashKey;
	this->key = key;
	this->collision = collision;
}

HashTableRow::~HashTableRow()
{
}

bool HashTableRow::isEmpty()
{
	return key == null;					
}