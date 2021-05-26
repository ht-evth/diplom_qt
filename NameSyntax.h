#pragma once
#include "BaseSyntax.h"
#include "NameMetricsTree.h"

class NameSyntax : public BaseSyntax
{
private:

	std::list<int> keywords;

public:
	NameSyntax();								// конструктор класса
	NameSyntax(std::string text);				// конструктор с текстом файла

    QList<int> Prog() override;		// аксиома S -> SE | SX | S D |eps

	void E();					// E - > { S }
	void D();					// D -> t* id K;
	void K();					// K -> , id K | , p id  K | eps
	void X();					// X -> Xd | d | X id |  id 


};

