#pragma once
#include <iostream>

struct Node
{
	std::string ident; 			// �������������

	// ������ / �����
	bool is_inside = false;		// ���� ���� ���������?
	bool has_parent = false;	// ���� ���� ������� ������� ������?
	int max_deep = 0;			// ������������ ������� �����������
	int length = 0;				// ����� ���������� ���������� �����

	int amount_chields = 0;		// ����� ���-�� �������-��������
	int fields = 0;				// ����� ���������� ����� �������
	int methods = 0;			// ����� ���������� ������� �������


	int break_return = 0;		// ���������� ���������� break � return � ������
	int _continue = 0;			// ���������� ���������� continue � ������

	// ��� ���������������
	int number_of_uses = 0;		// ���������� ������������� ��������������
};
