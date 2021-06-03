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


// определение сканера для классов
int ClassScanner::Scan(std::string *lex)
{
	lex->clear();	// очистим лексему
	int i = 0;		

	SkipSymbols();	// пропускаем пробелы, табы, переносы строк и комментарии

	// если конец модуля
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
		//std::cout << "\nКонец classscanner!" << std::endl;
		return TYPE_END;
	}

	// иначе проверка на идентификатор
	else if (((text[uk] >= 'a') && (text[uk] <= 'z')) || ((text[uk] >= 'A') && (text[uk] <= 'Z')) || (text[uk] == '_'))
	{
		lex->insert(i++, 1, text[uk++]);

		// запоминаем символы, уместные для идентификаторов
		while (((text[uk] >= '0') && (text[uk] <= '9')) ||
			((text[uk] >= 'a') && (text[uk] <= 'z')) ||
			((text[uk] >= 'A') && (text[uk] <= 'Z')) ||
			(text[uk] == '_'))
				lex->insert(i++, 1, text[uk++]);


		// после того, как считали, проверим на ключевое слово
		for (auto word : this->keywords)
		{
			if (word == *lex)
			{
				//std::cout << *lex << std::endl;
				return TYPE_KEYWORD;
			}
		}

		// проверка на тип данных
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

	// проверка на спецсимволы
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

	// что-то другое
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "Что-то другое: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
