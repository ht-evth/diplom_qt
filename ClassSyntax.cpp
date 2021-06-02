#include "ClassSyntax.h"
#include "ClassScanner.h"
#include "ClassMetricsTree.h"
#include <iostream>
#include <QMessageBox>

ClassSyntax::ClassSyntax()
{
	this->scaner = new ClassScanner();
	this->root = new ClassMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}


ClassSyntax::ClassSyntax(std::string text)
{
	this->scaner = new ClassScanner();
	this->scaner->SetText(text);
	this->root = new ClassMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}



// �������������� ����������
QList<int> ClassSyntax::Prog()
{
    QList<int> temp;
	BaseMetricsTree* save_cur = root->Cur;


	std::string* lex = new std::string();
	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������	

	if (type_lex != TYPE_CLOSED_BRACE)
		scaner->SetUk(uk1);
	else
        return temp;


	while (type_lex != TYPE_END && type_lex != TYPE_CLOSED_BRACE)
	{ 
		uk1 = scaner->GetUk();			
		type_lex = scaner->Scan(lex);
		if (type_lex != TYPE_CLOSED_BRACE)
			scaner->SetUk(uk1);
		else
            return temp;

		
		// ���������� ������ ���������� ���������� � ��������� ����� class, �� ����� ��� ����� ���� ��� �������� ���� (public, static, ...)
		// ������� ���������� �� �� ��� ���, ���� �� �������� �������� ����� class


		// SE
		if (type_lex == TYPE_CLASS)
		{			
			scaner->SetUk(uk1);
			E();					// ����� E -> class c* id c* {S} | class c* id c * id{ S }
		}
		else if (type_lex == TYPE_KEYWORD || type_lex == TYPE_TYPE || type_lex == TYPE_OTHER || type_lex == TYPE_IDENT || type_lex == TYPE_OPENED_BRACE)
		{

			scaner->SetUk(uk1);
			X();					// ����� X -> Xd | d | X id |  id | X c* | X { S }

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

    //std::cout << "\n\n ����� �� prog (CLASS)\n\n";

    return root->CalculateMetrics();



}



// E -> class c* id c* { S } | class c* id c * id{ S }
void ClassSyntax::E()
{

	// ��������� ����� class
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	
	if (type_lex == TYPE_CLASS)
	{
		type_lex = scaner->Scan(lex);

        while (type_lex == TYPE_KEYWORD)
		{
			type_lex = scaner->Scan(lex);

			if (type_lex == TYPE_END)
			{
                //std::cout << "����������� ����� �����. �������������� ������";
                QMessageBox* pmbx =
                                    new QMessageBox("����������� ������!",
                                    "����������� ����� �����. �������������� ������",
                                    QMessageBox::Critical,
                                    QMessageBox::Ok,
                                    0,
                                    0);
                pmbx->exec();
                delete pmbx;
                exit(-1);
			}
		}

		// ��� ������������ ������
		if (type_lex == TYPE_IDENT)
		{
			BaseMetricsTree* save_parent = this->currentNode;


			// ��������� ������� ���� � ������
			//this->currentNode = root->Add(*lex, false);
			this->currentNode = new ClassMetricsTree(*lex);
			save_parent->AddChieldForThisNode(this->currentNode);

			if (save_parent->Up)
				this->currentNode->n->is_inside = true;


            //std::cout << "\n��������� � " << *lex << " (" << this->currentNode << ")";
			std::string name = *lex;

			type_lex = scaner->Scan(lex);

			// ����� ���������� ���� �� �������� { ��� �������������, �� ������������ ������ �������� �����
			while (type_lex == TYPE_KEYWORD)
			{
				type_lex = scaner->Scan(lex);

				if (type_lex == TYPE_END)
				{

                    QMessageBox* pmbx =
                                        new QMessageBox("����������� ������!",
                                        "����������� ����� �����. �������������� ������",
                                        QMessageBox::Critical,
                                        QMessageBox::Ok,
                                        0,
                                        0);
                    pmbx->exec();
                    delete pmbx;
                    //std::cout << "����������� ����� �����. �������������� ������";
                    exit(-1);
				}

			}

			// ���� ������������
			if (type_lex == TYPE_IDENT)
			{
				this->currentNode->n->has_parent = true;	// �������, ��� ���� ����� - ���������

				// ��������� {
				type_lex = scaner->Scan(lex);

				if (type_lex == TYPE_OPENED_BRACE)
				{
					// ������ �����������
					Prog();
				}


			}
			else if (type_lex == TYPE_OPENED_BRACE)
			{
				// ������ �����������
				Prog();
			}

			// ��������������� ������� ����
			this->currentNode = save_parent;
            //std::cout << "\n������� �� " << name << " ������������ � (" << save_parent << ")";
			
		}

	}

}


// X -> Xd | d | X id |  id | X c* | X { S }
void ClassSyntax::X()
{
	// ��������� ����� ��������

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER || type_lex == TYPE_TYPE || type_lex == TYPE_IDENT || type_lex == TYPE_KEYWORD || type_lex == TYPE_OPENED_BRACE)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (type_lex == TYPE_IDENT && *lex == this->currentNode->n->ident)
		{
			int uk_after_ident = scaner->GetUk();
			type_lex = scaner->Scan(lex);


			// ���� ����� �������������� ������� ( - ��� �����
			if (type_lex == TYPE_OTHER && *lex == "(")
			{
				this->currentNode->n->methods++;

				while (*lex != ")")
				{
					type_lex = scaner->Scan(lex);
					if (type_lex == TYPE_END)
					{
                        QMessageBox* pmbx =
                                            new QMessageBox("����������� ������!",
                                            "����������� ����� �����. �������� ������, ��� ���������� ������ ������. �������������� ������",
                                            QMessageBox::Critical,
                                            QMessageBox::Ok,
                                            0,
                                            0);
                        pmbx->exec();
                        delete pmbx;
                        //std::cout << "\n����������� ����� �����. �������� ������, ��� ���������� ������ ������.";
                        exit(-1);
					}
				}
			}

		}


		else if (type_lex == TYPE_TYPE)
		{
			int uk2 = scaner->GetUk();
            while (type_lex == TYPE_TYPE || (type_lex == TYPE_OTHER && *lex == "*") || *lex == "[" || *lex == "]" )
			{
				uk2 = scaner->GetUk();
				type_lex = scaner->Scan(lex);
			}

			// ����� ���� ��� �������������

			if (type_lex == TYPE_IDENT)
			{
				// ��� ������� ��� - �� ������� � �����
                int uk_after_ident = scaner->GetUk();
				type_lex = scaner->Scan(lex);

				// ���� ����� �������������� ������� ( - ��� �����
				if (type_lex == TYPE_OTHER && *lex == "(")
					this->currentNode->n->methods++;
				else
					scaner->SetUk(uk_after_ident);

			}


		}

		else if (type_lex == TYPE_OPENED_BRACE)
		{
			// ������ �����������
			Prog();
		}

		else if (*lex == ";")
			this->currentNode->n->length++;

	}

	// ����������� ��������� ����� ��������, ��-�� ������� ����� �� �����

	scaner->SetUk(uk1);

}

