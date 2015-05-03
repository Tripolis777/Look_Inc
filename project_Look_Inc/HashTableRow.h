#pragma once
#define null -1										// Для удобства
typedef unsigned char HashIndexType;				// Тип ключа

class HashTableRow
{
public:
	int row;										// Номер строки
	int hashKey;									// Хэш-ключ
	int key;										// Ключ
	int collision;									// Кол-во коллизий

public:
	HashTableRow();									
	HashTableRow(int row, HashIndexType hashKey, int key, int collision);
	~HashTableRow();

	bool isEmpty();									// Есть ли данные
};

