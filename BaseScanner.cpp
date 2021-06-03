#include "BaseScanner.h"
#include <iostream>

// следующие методы одинаковы для всех сканнеров

// установить значение указателя
void BaseScanner::SetUk(int new_uk)
{
	this->uk = new_uk;
}

// получить значение указателя
int BaseScanner::GetUk()
{
	return this->uk;
}


// пропускаем пробелы, табы, переносы строк и комментарии
void BaseScanner::SkipSymbols()
{

	// цикл для проверки символов, которые игнорируем
	while (true)
	{
		// пропускаем пробелы, табуляции и переносы строк 
        while ((text[uk] == ' ') || (text[uk] == '\n') || (text[uk] == '\r') || (text[uk] == '\t'))
		{
			uk++;
		}

		// если встретились ('/' и '/') или ('/' и '*')
		// проверяем однострочный или многострочный комментарий
		if ((text[uk] == '/' && text[uk + 1] == '/') || (text[uk] == '/' && text[uk + 1] == '*'))
		{
			uk++;

			// если однострочный - ищем конец строки (комментария)
			if (text[uk] == '/')
			{
				uk++;
				while ((text[uk] != '\n') && (text[uk] != '\0')) uk++;
				continue;
			}

			// если многострочный, в бесконечном цикле ищем конец комментария
			else if (text[uk] == '*')
			{
				uk++;

				while (true)
				{
					// пропускаем символы, которые лежат внутри комментария
					while ((text[uk] != '*') && (text[uk] != '\0'))
					{
						uk++;
					}

					// дошли до конца - коментарий не был закрыт
					if (text[uk] == '\0')
					{
						uk--;
						break;
					}

					uk++;
					// если комментарий не окончен - пропускаем все символы
					if (text[uk] != '/')
					{
						uk++;
						continue;
					}

					break;
				}
				uk++;
				continue;
			}

		}
		else if (text[uk] == '#')
		{
			uk++;
			while ((text[uk] != '\n') && (text[uk] != '\0')) uk++;
			continue;
		}

		// выходим из цикла
		break;
	}

}

// Проверка на зарезервированное слово ЯП
bool BaseScanner::IsReservedWord(std::string lex)
{
	for (std::string word : reservedwords)
	{
		if (word == lex)
			return true;
	}

	return false;
}

// установить текст программы для сканнера
void BaseScanner::SetText(std::string text)
{
	this->text = text;
	this->uk = 0;
}
