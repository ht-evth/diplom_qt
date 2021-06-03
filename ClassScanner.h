#pragma once
#include "BaseScanner.h"
#include <string>

#define TYPE_KEYWORD 1
#define TYPE_IDENT 2
#define TYPE_CLASS 3
#define TYPE_OPENED_BRACE 4
#define TYPE_CLOSED_BRACE 5
#define TYPE_OTHER 6
#define TYPE_TYPE 7
#define TYPE_END 1000

class ClassScanner : public BaseScanner
{
private:
	std::list<std::string> types;

public:
	ClassScanner();							// конструктор класса
	int Scan(std::string *lex) override;	// метод сканирования для классов
};

