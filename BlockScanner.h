#pragma once
#include "BaseScanner.h"
#include <string>

#define TYPE_OPENED_BRACE 1
#define TYPE_CLOSED_BRACE 2
#define TYPE_OTHER 3
#define TYPE_END 1000

class BlockScanner : public BaseScanner
{

public:
	BlockScanner();							// конструктор класса
	int Scan(std::string* lex) override;	// метод сканирования для классов
};

