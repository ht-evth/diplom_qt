#pragma once
#include "BaseSyntax.h"

class BlockSyntax : public BaseSyntax
{
private:
	int counter = 0;
public:
	BlockSyntax();								// конструктор класса
	BlockSyntax(std::string text);				// конструктор с текстом файла

	void Prog() override;		// аксиома S -> SE | SX | eps

	void E();					// E ->  { S }
	void X();					// X -> Xd | d  

};