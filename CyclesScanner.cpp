#include "CyclesScanner.h"
#include <iostream>
#include <QMessageBox>

CyclesScanner::CyclesScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {};
}


// определение сканера для циклов
int CyclesScanner::Scan(std::string* lex)
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
		//std::cout << *lex << std::endl;

		if (*lex == "for")
			return TYPE_FOR;
		
		else if (*lex == "do")
			return TYPE_DO;
		
		else if (*lex == "while")
			return TYPE_WHILE;


		return TYPE_OTHER;
	}

	// проверка на спецсимволы
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }
    // если константы строковые (чтобы не возвращало TYPE_IDENT между кавычек)
    else if (text[uk] == '\'')
    {
        uk++;
        while ((text[uk] != '\'') && (text[uk] != '\0' && (text[uk] != '\n')))
        {
            lex->insert(i++, 1, text[uk++]);
        }


        if (text[uk] == '\0' || text[uk] == '\n')
        {
            //std::cout << "Была пропущена одинарная кавычка.";
            QMessageBox* pmbx =
                                new QMessageBox("Критическая ошибка!",
                                "Была пропущена одинарная кавычка. Синтаксическая ошибка",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            delete pmbx;
            exit(-1);
        }
        uk++;
        return TYPE_OTHER;
    }
    // если константы символьные (чтобы не возвращало TYPE_IDENT между кавычек)
    else if (text[uk] == '\"')
    {
        uk++;
        while ((text[uk] != '\"') && (text[uk] != '\0') && (text[uk] != '\n'))
        {
            lex->insert(i++, 1, text[uk++]);
        }

        if (text[uk] == '\0' || text[uk] == '\n')
        {
            QMessageBox* pmbx =
                                new QMessageBox("Критическая ошибка!",
                                "Была пропущена двойная кавычка. Синтаксическая ошибка",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            delete pmbx;
            //std::cout << "Была пропущена двойная кавычка.";
            exit(-1);
        }
        uk++;
        return TYPE_OTHER;
    }

	// что-то другое
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "Что-то другое: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
