#include "BlockSyntax.h"
#include "BlockScanner.h"
#include "BlockMetricsTree.h"
#include <iostream>

BlockSyntax::BlockSyntax()
{
	this->scaner = new BlockScanner();
	this->root = new BlockMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}


BlockSyntax::BlockSyntax(std::string text)
{
	this->scaner = new BlockScanner();
	this->scaner->SetText(text);
	this->root = new BlockMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}

// �������������� ����������
void BlockSyntax::Prog()
{
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	
	// ��������, ����� �������� ������������
	if (type_lex != TYPE_CLOSED_BRACE)
	{
		if (type_lex != TYPE_OPENED_BRACE)
			scaner->SetUk(uk1);
	}
	else
		return;
	

	while (type_lex != TYPE_END && type_lex != TYPE_CLOSED_BRACE)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
		
		// ��������, ����� �������� ������������
		if (type_lex != TYPE_CLOSED_BRACE)
				scaner->SetUk(uk1);
		else
			return;

		// SE
		if (type_lex == TYPE_OPENED_BRACE)
		{
			// �����������
			E();					// ����� E -> { S }
		}

		// SX
		else if (TYPE_OTHER)
		{
			scaner->SetUk(uk1);
			X();					// ����� X -> Xd | d 
		}

		// �������� �� ����� �����
		else if (type_lex == TYPE_END)
		{
			//std::cout << "����� �� ����� ������!" << std::endl;
			scaner->SetUk(uk1); // ����������� ��������� (�� ������ ��������)
			break;
		}
		else
			type_lex = scaner->Scan(lex);

	}

	this->root->CalculateMetrics();

}



// E -> { S }
void BlockSyntax::E()
{
	// ��������� ����� {

	// ��������� ������������ ���� (����� ����� �� �����������)
	BaseMetricsTree* save_parent = this->currentNode;

	std::string name = "{" + std::to_string(counter++) + "}";

	this->currentNode = new BlockMetricsTree(name);
	save_parent->AddChieldForThisNode(this->currentNode);

	if (save_parent->Up)
		this->currentNode->n->is_inside = true;


	std::cout << "\n����� � ���� " << name;

	// �����������
	Prog();

	// ����� �� �����������
	std::cout << "\n����� �� �����" << name;
	this->currentNode = save_parent;
}


// X -> Xd | d 
void BlockSyntax::X()
{
	// ��������� ����� ��������

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER)
	{
		if (*lex == ";") this->currentNode->n->length++;

		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
	}

	// ����������� ��������� ����� ��������, ��-�� ������� ����� �� �����
	scaner->SetUk(uk1);

}