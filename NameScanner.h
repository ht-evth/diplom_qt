#pragma once
#include "BaseScanner.h"

/*
Имена:

  лексема                тип      обозначение  в КС-грамматике идентификаторов
ключевое слово описания   1        t
идентификатор             2        id
{                         3         {
}                         4         }
,                         5         ,
;                         6         ;
*		    			  7	    pointer
все остальное             8         d
*/

#define TYPE_TYPE 1
#define TYPE_IDENT 2
#define TYPE_OPENED_BRACE 3
#define TYPE_CLOSED_BRACE 4
#define TYPE_COMMA 5
#define TYPE_SEMICOLON 6
#define TYPE_POINTER 7
#define TYPE_OTHER 8
#define TYPE_END 1000

class NameScanner : public BaseScanner
{
public:
	NameScanner();							// конструктор класса
	int Scan(std::string* lex) override;	// метод сканирования для классов
};

