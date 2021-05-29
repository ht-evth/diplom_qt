#pragma once
#include "BaseSyntax.h"
#include "NameMetricsTree.h"

class NameSyntax : public BaseSyntax
{
private:

	std::list<int> keywords;

public:
	NameSyntax();								// ����������� ������
	NameSyntax(std::string text);				// ����������� � ������� �����

    QList<int> Prog() override;		// ������� S -> SE | SX | S D |eps

	void E();					// E - > { S }
	void D();					// D -> t* id K;
	void K();					// K -> , id K | , p id  K | eps
	void X();					// X -> Xd | d | X id |  id 
    void V();
    void B();


};

