#pragma once
#define null -1										// ��� ��������
typedef unsigned char HashIndexType;				// ��� �����

class HashTableRow
{
public:
	int row;										// ����� ������
	int hashKey;									// ���-����
	int key;										// ����
	int collision;									// ���-�� ��������

public:
	HashTableRow();									
	HashTableRow(int row, HashIndexType hashKey, int key, int collision);
	~HashTableRow();

	bool isEmpty();									// ���� �� ������
};

