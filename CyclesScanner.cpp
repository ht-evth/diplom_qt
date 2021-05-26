#include "CyclesScanner.h"
#include <iostream>

CyclesScanner::CyclesScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {};
}


// ����������� ������� ��� ������
int CyclesScanner::Scan(std::string* lex)
{
	lex->clear();	// ������� �������
	int i = 0;

	SkipSymbols();	// ���������� �������, ����, �������� ����� � �����������

	// ���� ����� ������
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
        //std::cout << "�����!" << std::endl;
		return TYPE_END;
	}

	// ����� �������� �� �������������
	else if (((text[uk] >= 'a') && (text[uk] <= 'z')) || ((text[uk] >= 'A') && (text[uk] <= 'Z')) || (text[uk] == '_'))
	{
		lex->insert(i++, 1, text[uk++]);

		// ���������� �������, �������� ��� ���������������
		while (((text[uk] >= '0') && (text[uk] <= '9')) ||
			((text[uk] >= 'a') && (text[uk] <= 'z')) ||
			((text[uk] >= 'A') && (text[uk] <= 'Z')) ||
			(text[uk] == '_'))
			lex->insert(i++, 1, text[uk++]);


		// ����� ����, ��� �������, �������� �� �������� �����
		//std::cout << *lex << std::endl;

		if (*lex == "for")
			return TYPE_FOR;
		
		else if (*lex == "do")
			return TYPE_DO;
		
		else if (*lex == "while")
			return TYPE_WHILE;


		return TYPE_OTHER;
	}

	// �������� �� �����������
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }

	// ���-�� ������
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "���-�� ������: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
