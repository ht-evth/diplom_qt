#pragma once
#include "BaseSyntax.h"
#include "ClassScanner.h"
#include "BaseMetricsTree.h"
#include <list>


class ClassSyntax : public BaseSyntax
{
private:

	std::list<int> keywords;

public:
	ClassSyntax();								// конструктор класса
	ClassSyntax(std::string text);				// конструктор с текстом файла

    QList<int> Prog() override;		// аксиома S -> SE | SX | eps

	void E();					// E ->  class c* id c* {S} | class c* id c * id{ S }
	void X();					// X -> Xd | d | X id |  id | X c* | X { S }

}; 
