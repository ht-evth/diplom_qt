#include "BlockScanner.h"
#include <iostream>

BlockScanner::BlockScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {};
}


// определение сканера для блоков
int BlockScanner::Scan(std::string* lex)
{
	lex->clear();	// очистим лексему
	int i = 0;

	SkipSymbols();	// пропускаем пробелы, табы, переносы строк и комментарии

	// если конец модуля
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
        //std::cout << "Конец!" << std::endl;
		return TYPE_END;
	}

	// проверка на спецсимволы
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }

	// что-то другое
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "Что-то другое: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
