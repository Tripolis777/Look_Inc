#include "stdafx.h"
#include "HashTable.h"
#include "math.h"


using namespace std;

HashTable::HashTable(int size)
{
	this->size = size; 
	this->freeplace = size;
	tableRow = new HashTableRow[size];					// ���� ������� 
	int a = 4;											// �.�. size = 16 �� � = 4

// �.�. � ��� ������ ������� 10-20 �����, ����� �� ����������� '�', �� ������ 
// ��������� ��� ��������. 
	if (size > 16)										
		a = 5;

// � - �� ��� �� ������������
	K = pow(2.0, 8.0)*(sqrt(5.0) - 1)/2;
	S = 8 - a;

	loadTable(); 
}


HashTable::~HashTable()
{
	delete[] tableRow;									
}

void HashTable::loadTable()								// ��������� ������ �� �������, ���� ���������
{
	std::ifstream ifs;									// ������� ������� ����� 

	ifs.open(FILE_NAME, std::ifstream::in);				// ��������� ����
	int i = 0;											// ��� ���������� ����� ��������� ����� ������.

	while (ifs >> i) {									// ���������, ���� ���� ������� ������
		if (i >= size)									// ���������, �� ��������� �� ����� ������ ������ �������
		{
			AfxMessageBox(L"������������ ������ � �����", MB_OK | MB_ICONERROR, NULL);
			break;										// ���-�� ����� �� ���, ������ ������
		}
		tableRow[i].row = i;
		ifs >> tableRow[i].hashKey;						//��������� ���-����
		ifs >> tableRow[i].key;							// -/- ����
		ifs >> tableRow[i].collision;					// -/- ���-�� ��������
		freeplace--;
	}

	ifs.close();										// ��������� ����
}

HashIndexType HashTable::hashFunction(int key)
{
	return (HashIndexType)(key * K) >> S;				// ��������� ����� ������ �� S + �������� ���� �����
}

bool HashTable::insertItem(int key)
{
	if (isCrowded())
		return false;

	HashIndexType hashKey = hashFunction(key);			// ��� ���-����
	HashIndexType hashSave = hashKey;					// �������� ��� �� ������ ������, ���� � ��� ���� ��������

	while (hashKey < size)								// ���������� �� ����� �������, ���� �����������
	{
		if (tableRow[hashKey].hashKey != null)			// ���� ���� ��� ���� Oops!
		{
			if (hashKey == hashSave)					// ����������� ������� ��������
				tableRow[hashKey].collision++;

			hashKey++;									// �������� ������ ������ � ����� ����
			if (hashKey == size)						// ���� �������, ���� ����� �� ����� 
				hashKey = 0;

			if (hashKey == hashSave)					// ���������� �����, ���� ������� ������ ����� �������
				return false;							// �������, ���� ��������� ����

			continue;
		}
														// ����� �������, �� ����� ��������� �����
		tableRow[hashKey] = HashTableRow(hashKey, hashSave, key, 0); 
		freeplace--;
		return true;
	}
	return false;										// ������, �� ���� �� ����� �� ������, �� ����-��!!!
}

HashTableRow HashTable::searchItem(int key)
{
	HashIndexType hashKey = hashFunction(key);		// ���������� ��� � � ������� insertItem
	HashIndexType hashSave = hashKey;

	while (hashKey < size)
	{
		if (tableRow[hashKey].key == key)			// ���� ����� �����
			return tableRow[hashKey];				// ��� ���� ����� 

		hashKey++;									// �������� ������ ������ � ����� ����
		if (hashKey == size)						// ���� �������, ���� ����� �� ����� 
			hashKey = 0;

		if (hashKey == hashSave)					// ���������� �����, ���� ������� ������ ����� �������
			return HashTableRow();					// �������, ���� ��������� ����

	}
	return HashTableRow();							// ����� �� ������ ������
}

HashTableRow HashTable::getItem(int row_number)		// ��� ������� ����� ������ ����� ������� ��������� ���� �������
{													// �� ��������, �� ����� ���� �� ������
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

void HashTable::saveTable()												/// ��������� ������
{
	std::ofstream ofs;													// ������� �������� �����
	ofs.open(FILE_NAME, std::ofstream::out | std::ofstream::app);		// ��������� ����, ���� �� ������ - �������
													
	for (int i = 0; i < size; i++)										// �������� ��� ���� �������
	{
		
		if (tableRow[i].isEmpty())										// ���������� ������ �������� ��������
			continue;
																		// ����������... 
		ofs << i << " " << tableRow[i].hashKey << " " << tableRow[i].key << " " << tableRow[i].collision;
		ofs << std::endl;												// ��������� "������" �� ����. ������ 
	}
		
	ofs.close();														// ��������� ����
}	