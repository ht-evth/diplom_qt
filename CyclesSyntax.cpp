#include "CyclesSyntax.h"
#include "CyclesScanner.h"
#include "CyclesMetricsTree.h"
#include <iostream>

CyclesSyntax::CyclesSyntax()
{
	this->scaner = new CyclesScanner();
	this->is_do_while = false;
	
	this->root = new CyclesMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}


CyclesSyntax::CyclesSyntax(std::string text)
{
	this->scaner = new CyclesScanner();
	this->scaner->SetText(text);
	this->is_do_while = false;
	
	this->root = new CyclesMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}

// �������������� ����������
void CyclesSyntax::Prog()
{
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	
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
		
		if (type_lex != TYPE_CLOSED_BRACE)
		{
			if (type_lex != TYPE_OPENED_BRACE)
				scaner->SetUk(uk1);
		}
		else
			return;


		// SE
		if (type_lex == TYPE_FOR || type_lex == TYPE_DO || type_lex == TYPE_WHILE)
		{
			// ��������� �������� �� do while

			if (is_do_while)
			{
				is_do_while = false;
				return;
			}

			scaner->SetUk(uk1);
			E();					// ����� E -> for(c*) | for(c*) { S } | while X | while X{ S } | do S while
		}

		// SX
		else if (type_lex == TYPE_OTHER)
		{
			scaner->SetUk(uk1);
			X();					// ����� X -> Xd | d 
		}

		// SD
		else if (type_lex == TYPE_OPENED_BRACE)
		{
			scaner->SetUk(uk1);
			D();					// ����� D -> { S } 
		}

		// �������� �� ����� �����
		else if (type_lex == TYPE_END)
		{
			//std::cout << "����� �� ����� ������!" << std::endl;
			scaner->SetUk(uk1); // �� ������ ��������
			break;
		}
		else
			type_lex = scaner->Scan(lex);


	}

	root->CalculateMetrics();

}



// E -> for(c*) | for(c*) { S } | while X | while X{ S } | do S while
void CyclesSyntax::E()
{
	// ��������� ����� class
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������

	// ���������� ������� ���� ������ (��� �������� �� �����������)
	BaseMetricsTree* save_parent = this->currentNode;
	std::string name = ""; // ��� ����� ��� �������

	// ���� for
	if (type_lex == TYPE_FOR)
	{
		// ������ � �������
		name = "for" + std::to_string(counter++);

		type_lex = scaner->Scan(lex);
		// ����� for ����������� ������, ����� �� ����� ���... 
		if (*lex == "(")
		{
			while (*lex != ")")
			{
				type_lex = scaner->Scan(lex);
				if (type_lex == TYPE_END)
				{
					std::cout << "��������� ������ ')' ��� ��������� ����� for";
					exit(-1);
				}
			}



			// ����� ����� ���� {
			uk1 = scaner->GetUk();
			type_lex = scaner->Scan(lex);


			// ��� ����� ��� ����������� ������������ �����...
			if (type_lex == TYPE_OPENED_BRACE)
			{
				this->currentNode = new CyclesMetricsTree(name);
				save_parent->AddChieldForThisNode(this->currentNode);

				if (save_parent->Up)
					this->currentNode->n->is_inside = true;

				std::cout << "\n��������� � " << name << " (" << this->currentNode << ")";
				// �����������

				scaner->SetUk(uk1);
				Prog();
			}
			else
			{
				scaner->SetUk(uk1);
				this->currentNode = new CyclesMetricsTree(name);
				save_parent->AddChieldForThisNode(this->currentNode);
				if (save_parent->Up)
					this->currentNode->n->is_inside = true;

			}

		}
	}

	// while
	else if (type_lex == TYPE_WHILE)
	{
		// ������ � �������
		name = "while" + std::to_string(counter++);
		X();

		// ����� ����� ���� {
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		// ��� ����� ��� ����������� ������������ �����...
		if (type_lex == TYPE_OPENED_BRACE)
		{
			// �����������
			
			this->currentNode = new CyclesMetricsTree(name);
			save_parent->AddChieldForThisNode(this->currentNode);

			if (save_parent->Up)
				this->currentNode->n->is_inside = true;

			std::cout << "\n��������� � " << name << " (" << this->currentNode << ")";

			Prog();
		}
		else
		{
			scaner->SetUk(uk1);
			this->currentNode = new CyclesMetricsTree(name);
			save_parent->AddChieldForThisNode(this->currentNode);

			if (save_parent->Up)
				this->currentNode->n->is_inside = true;
		}

	}

	else if (type_lex == TYPE_DO)
	{
		name = "do-while" + std::to_string(counter++);
		this->currentNode = new CyclesMetricsTree(name);
		save_parent->AddChieldForThisNode(this->currentNode);

		if (save_parent->Up)
			this->currentNode->n->is_inside = true;

		std::cout << "\n��������� � " << name << " (" << this->currentNode << ")";

	
		int uk2 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		// ���� �� {
		if (type_lex != TYPE_OPENED_BRACE)
			scaner->Scan(lex);	// ����������� ��������� ����� {

		Prog();


		// ��������� while
		uk2 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
		if (type_lex != TYPE_WHILE)
		{
			std::cout << "��������� �������� while ��� do-while.";
			exit(-1);
		}

	}


	// ��������������� ������� ���� - ����� �� �����������
	std::cout << "\n������� �� " << name << " ������� � (" << save_parent << ")";
	this->currentNode = save_parent;

}


// X -> Xd | d 
void CyclesSyntax::X()
{
	// ��������� ����� ��������

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (*lex == "break" || *lex == "return")
			this->currentNode->n->break_return++;
		else if (*lex == "continue")
			this->currentNode->n->_continue++;
		else if (*lex == ";")
			this->currentNode->n->length++;


	}

	// ����������� ��������� ����� ��������, ��-�� ������� ����� �� �����
	scaner->SetUk(uk1);

}


// D -> { S } 
void CyclesSyntax::D()
{
	// ��������� ����� {

	Prog();

	// ��������� ����� }

}