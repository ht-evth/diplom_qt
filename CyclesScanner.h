#pragma once
#include "BaseScanner.h"
#include <string>


#define TYPE_FOR 1
#define TYPE_DO 2
#define TYPE_WHILE 3
#define TYPE_OPENED_BRACE 4
#define TYPE_CLOSED_BRACE 5
#define TYPE_OTHER 6
#define TYPE_END 1000

class CyclesScanner : public BaseScanner
{

public:
	CyclesScanner();						// конструктор класса
	int Scan(std::string* lex) override;	// метод сканирования для классов
};

