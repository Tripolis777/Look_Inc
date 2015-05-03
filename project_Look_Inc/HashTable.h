#pragma once

#include <fstream>  
#include <iostream>
#include <string>

#include "HashTableRow.h"

class HashTable
{
private:
	int K, S;									//K  = 2**8 * (sqrt(5)-1)/2 (золотое сечение). S - число побитового сдвига
	int freeplace;

protected:						

	int size;									// Размер Хэш таблица
	HashTableRow* tableRow;						// Указатель на массив строк
	std::string FILE_NAME = "Hash_Table.txt";	// Переменная хранящая название файла для сохранения данных 

	HashIndexType hashFunction(int key);		// Хэш функция							

public:
	HashTable(int size);						// Конструктор
	~HashTable();								// Деструктор

	bool insertItem(int key);					// Добавление элемента в таблицу
	HashTableRow searchItem(int key);			// Поиск элемента в таблице
	HashTableRow getItem(int row_number);		// Возвращает элемент по номеру строки

	int getSize();								// Возвращает размер таблицы
	bool isCrowded();
	int getFreeValue();

	void loadTable();							// Загрузка таблицы из файла FILE_NAME
	void saveTable();							// Сохраняет таблицу в файл FILE_NAME
};

