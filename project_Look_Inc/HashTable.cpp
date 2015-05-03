#include "stdafx.h"
#include "HashTable.h"
#include "math.h"


using namespace std;

HashTable::HashTable(int size)
{
	this->size = size; 
	this->freeplace = size;
	tableRow = new HashTableRow[size];					// Наша таблица 
	int a = 4;											// Т.к. size = 16 то а = 4

// Т.к. у нас размер таблицы 10-20 строк, чтобы не высчитывать 'а', мы просто 
// проверяем его условием. 
	if (size > 16)										
		a = 5;

// К - мы так же высчитаываем
	K = pow(2.0, 8.0)*(sqrt(5.0) - 1)/2;
	S = 8 - a;

	loadTable(); 
}


HashTable::~HashTable()
{
	delete[] tableRow;									
}

void HashTable::loadTable()								// Загружаем данные из таблицы, если сохраняли
{
	std::ifstream ifs;									// Создаем входной поток 

	ifs.open(FILE_NAME, std::ifstream::in);				// Открываем файл
	int i = 0;											// Эта переменная будет считывать номер строки.

	while (ifs >> i) {									// Повторяем, пока есть входные данные
		if (i >= size)									// Проверяем, не превышает ли номер строки размер таблицы
		{
			AfxMessageBox(L"Неккоректные данные в файле", MB_OK | MB_ICONERROR, NULL);
			break;										// Что-то пошло не так, уходим отсюда
		}
		tableRow[i].row = i;
		ifs >> tableRow[i].hashKey;						//Считываем Хэш-ключ
		ifs >> tableRow[i].key;							// -/- ключ
		ifs >> tableRow[i].collision;					// -/- кол-во коллизий
		freeplace--;
	}

	ifs.close();										// Закрываем файл
}

HashIndexType HashTable::hashFunction(int key)
{
	return (HashIndexType)(key * K) >> S;				// Побитовый сдвиг вправо на S + обрезаем нули слева
}

bool HashTable::insertItem(int key)
{
	if (isCrowded())
		return false;

	HashIndexType hashKey = hashFunction(key);			// Наш хэш-ключ
	HashIndexType hashSave = hashKey;					// Сохраним его на всякий случай, если у нас есть коллизии

	while (hashKey < size)								// Пробежимся по всему массиву, если потребуется
	{
		if (tableRow[hashKey].hashKey != null)			// Если ключ уже есть Oops!
		{
			if (hashKey == hashSave)					// Увеличиваем счетчик коллизии
				tableRow[hashKey].collision++;

			hashKey++;									// Начинаем искать дальше с шагом один
			if (hashKey == size)						// Идем сначала, если дошли до конца 
				hashKey = 0;

			if (hashKey == hashSave)					// Прекращаем поиск, если сделали полный обход массива
				return false;							// Неудача, нету свободных мест

			continue;
		}
														// Какое счастье, мы нашли свободное место
		tableRow[hashKey] = HashTableRow(hashKey, hashSave, key, 0); 
		freeplace--;
		return true;
	}
	return false;										// Вообще, до сюда мы дойти не должны, но мало-ли!!!
}

HashTableRow HashTable::searchItem(int key)
{
	HashIndexType hashKey = hashFunction(key);		// Аналогично что и к функции insertItem
	HashIndexType hashSave = hashKey;

	while (hashKey < size)
	{
		if (tableRow[hashKey].key == key)			// Если ключи равны
			return tableRow[hashKey];				// Нас ждет успех 

		hashKey++;									// Начинаем искать дальше с шагом один
		if (hashKey == size)						// Идем сначала, если дошли до конца 
			hashKey = 0;

		if (hashKey == hashSave)					// Прекращаем поиск, если сделали полный обход массива
			return HashTableRow();					// Неудача, нету свободных мест

	}
	return HashTableRow();							// Опять же всякое бывает
}

HashTableRow HashTable::getItem(int row_number)		// Эта функция нужна только чтобы красиво построить нашу таблицу
{													// по хорошему, ее здесь быть не должно
	return tableRow[row_number];
}

int HashTable::getSize()
{
	return size;
}

bool HashTable::isCrowded()
{
	return freeplace <= 0;
}

int HashTable::getFreeValue()
{
	return freeplace;
}

void HashTable::saveTable()												/// Сохраняем данные
{
	std::ofstream ofs;													// Создаем выходной поток
	ofs.open(FILE_NAME, std::ofstream::out | std::ofstream::app);		// Открываем файл, если не создан - создаем
													
	for (int i = 0; i < size; i++)										// Проходим всю нашу таблицу
	{
		
		if (tableRow[i].isEmpty())										// Записываем только непустые элементы
			continue;
																		// Записываем... 
		ofs << i << " " << tableRow[i].hashKey << " " << tableRow[i].key << " " << tableRow[i].collision;
		ofs << std::endl;												// Переносим "курсор" на след. строку 
	}
		
	ofs.close();														// Закрываем файл
}	