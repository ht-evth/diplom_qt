#include "BlockScanner.h"
#include <iostream>

BlockScanner::BlockScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {};
}


// ����������� ������� ��� ������
int BlockScanner::Scan(std::string* lex)
{
	lex->clear();	// ������� �������
	int i = 0;

	SkipSymbols();	// ���������� �������, ����, �������� ����� � �����������

	// ���� ����� ������
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
		std::cout << "�����!" << std::endl;
		return TYPE_END;
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
