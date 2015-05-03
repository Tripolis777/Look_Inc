#pragma once

#include <fstream>  
#include <iostream>
#include <string>

#include "HashTableRow.h"

class HashTable
{
private:
	int K, S;									//K  = 2**8 * (sqrt(5)-1)/2 (������� �������). S - ����� ���������� ������
	int freeplace;

protected:						

	int size;									// ������ ��� �������
	HashTableRow* tableRow;						// ��������� �� ������ �����
	std::string FILE_NAME = "Hash_Table.txt";	// ���������� �������� �������� ����� ��� ���������� ������ 

	HashIndexType hashFunction(int key);		// ��� �������							

public:
	HashTable(int size);						// �����������
	~HashTable();								// ����������

	bool insertItem(int key);					// ���������� �������� � �������
	HashTableRow searchItem(int key);			// ����� �������� � �������
	HashTableRow getItem(int row_number);		// ���������� ������� �� ������ ������

	int getSize();								// ���������� ������ �������
	bool isCrowded();
	int getFreeValue();

	void loadTable();							// �������� ������� �� ����� FILE_NAME
	void saveTable();							// ��������� ������� � ���� FILE_NAME
};

