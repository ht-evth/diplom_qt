#pragma once
#include "BaseSyntax.h"
class CyclesSyntax : public BaseSyntax
{
private:
	bool is_do_while;
	int counter = 0;
public:
	CyclesSyntax();								// ����������� ������
	CyclesSyntax(std::string text);				// ����������� � ������� �����

    int* Prog() override;		// ������� S -> SE | SX | eps

	void E();					// E ->  for (c*) | for(c*) { S }	| while X | while X { S }	| do S while
	void X();					// X -> Xd | d  
	void D();					// X -> { S }

};
