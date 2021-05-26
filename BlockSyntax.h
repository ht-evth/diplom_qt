#pragma once
#include "BaseSyntax.h"

class BlockSyntax : public BaseSyntax
{
private:
	int counter = 0;
public:
	BlockSyntax();								// ����������� ������
	BlockSyntax(std::string text);				// ����������� � ������� �����

    int* Prog() override;		// ������� S -> SE | SX | eps

	void E();					// E ->  { S }
	void X();					// X -> Xd | d  

};
