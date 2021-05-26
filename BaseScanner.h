#pragma once
#include <string>
#include <list>

class BaseScanner 
{
protected:
	std::string text;										// текст программы
	int uk;													// значение указателя в тексте программы
	std::list<std::string> keywords;						// список ключевых слов с их номером
	std::list<std::string> reservedwords;					// список зарезервированных слов

public:
	// методы, которые одинаковы для всех сканнеров:
	void SkipSymbols();							// пропускаем пробелы, табы, переносы строк и комментарии и т.д.
	bool IsReservedWord(std::string lex);		// Проверка на зарезервированное слово ЯП
	void SetUk(int new_uk);						// установить значение указателя в тексте
	int GetUk();								// получить значение указателя в тексте
	void SetText(std::string text);				// установить текст для сканера

	// методы, которые будут переопределены для каждого сканера
    virtual int Scan(std::string* lex) = 0;		// метод сканирования очередной лексемы
};


