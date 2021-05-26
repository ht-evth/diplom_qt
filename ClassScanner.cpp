#include "ClassScanner.h"
#include <iostream>

ClassScanner::ClassScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {
		"public", 
		"private",
		"protected",
		"abstract",
		"sealed", 
		"static", 
		"extends",
	};

	this->types = {
	"char",
	"int",
	"unsigned",
	"short",
	"long",
	"float",
	"double",
	"string",
	"bool",
	"boolean",
	"decimal",
	"const",
	"static",
	"extern",
	"internal",
	"byte",
	"final",
	"auto",
	"var",
	"typedef",
	"void",
	};
}


// ����������� ������� ��� �������
int ClassScanner::Scan(std::string *lex)
{
	lex->clear();	// ������� �������
	int i = 0;		

	SkipSymbols();	// ���������� �������, ����, �������� ����� � �����������

	// ���� ����� ������
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
		//std::cout << "\n����� classscanner!" << std::endl;
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
		for (auto word : this->keywords)
		{
			if (word == *lex)
			{
				//std::cout << *lex << std::endl;
				return TYPE_KEYWORD;
			}
		}

		// �������� �� ��� ������
		for (auto word : this->types)
		{
			if (word == *lex)
			{
				//std::cout << *lex << std::endl;
				return TYPE_TYPE;
			}
		}

		//std::cout << *lex << std::endl;

		if (*lex == "class")
			return TYPE_CLASS;

		return TYPE_IDENT;
	}

	// �������� �� �����������
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }

	else if (text[uk] == ':') 
	{ 
		lex->insert(i++, 1, text[uk++]);

		if (text[uk] == ':')
		{
			lex->insert(i++, 1, text[uk++]);
			return TYPE_OTHER;
		}
		else
			return TYPE_KEYWORD;
	}

	// ���-�� ������
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "���-�� ������: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
