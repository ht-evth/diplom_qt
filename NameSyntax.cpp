#include "NameSyntax.h"
#include "NameScanner.h"
#include "NameMetricsTree.h"
#include <iostream>
#include <QMessageBox>


NameSyntax::NameSyntax()
{
	this->scaner = new NameScanner();
	
	this->root = new NameMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}

NameSyntax::NameSyntax(std::string text)
{
	this->scaner = new NameScanner();
	this->scaner->SetText(text);
	
	this->root = new NameMetricsTree();
	this->root->Cur = root;
	this->currentNode = root;
}


// �������������� ����������
QList<int> NameSyntax::Prog()
{
    QList<int> temp;
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();			// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	
	if (type_lex != TYPE_CLOSED_BRACE)
		scaner->SetUk(uk1);
	else
        return temp;

	while (type_lex != TYPE_END && type_lex != TYPE_CLOSED_BRACE)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (type_lex == TYPE_CLOSED_BRACE)
			break;


		// SD
		if (type_lex == TYPE_TYPE)
		{
			int uk_before_ident = scaner->GetUk();	// �������� �������� ��������� �� �������������
            while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER)
			{
				type_lex = scaner->Scan(lex);
                if (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER)
					uk_before_ident = scaner->GetUk();
			}

			// ��������� ������������� (SD)
			if (type_lex == TYPE_IDENT)
			{
				// ����� �������������� ��������� ����� D
				// ����������� ��������� 

				int uk2 = scaner->GetUk();
				scaner->Scan(lex);
				scaner->SetUk(uk2);

				if (*lex != "(")
				{
					scaner->SetUk(uk_before_ident);
					D();	// ������� � ����� D -> t* id K;
				}
                else
                {
                    V();
                }

			}

		}

		// SE
		else if (type_lex == TYPE_OPENED_BRACE)
		{

			E();

		}

		// SX
		else if (type_lex == TYPE_OTHER || type_lex == TYPE_IDENT)
		{
			scaner->SetUk(uk1);
			X();
		}

		// �������� �� ����� �����
		else if (type_lex == TYPE_END)
		{
			//std::cout << "����� �� ����� ������!" << std::endl;
			scaner->SetUk(uk1); // �� ������ ��������
			break;
		}

		

	}

    return this->root->CalculateMetrics();

}



void NameSyntax::E()
{
	// ��������� ��� ����� {

	// ������ ������ � ������ �����������
	// ������ ���� {}

	NameMetricsTree* new_node = new NameMetricsTree("{block}");
	this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

	// ������ ��� ���� ���� {vlozh} ��� ���������� �����������
	// � ��������� � ����
	NameMetricsTree* new_vlozh = new NameMetricsTree("{inside-block}");
	this->currentNode->AddChieldForThisNode(new_vlozh);;
	this->currentNode = new_vlozh;

	Prog();

	// ��������� �� ���������� ������� �����������
	// ������������ � ���� {}
	this->currentNode = new_node;
}


void NameSyntax::D()
{
	// ��������� ��� ����� ident 

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	
	// ������ ��� ������ ident
	if (type_lex != TYPE_IDENT)
	{
        QMessageBox* pmbx =
                            new QMessageBox("����������� ������!",
                            "�������� ������������� ��� ���������� ����������.",
                            QMessageBox::Critical,
                            QMessageBox::Ok,
                            0,
                            0);
        pmbx->exec();
        //std::cout << "�������� ������������� ��� ���������� ����������.";
        exit(-1);
	}

	NameMetricsTree* new_node = new NameMetricsTree(*lex);
	this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

	K();		// ����� K -> , id K | , p id  K | eps

	type_lex = scaner->Scan(lex);
	if (type_lex != TYPE_SEMICOLON)
	{
		if (*lex != ":" && *lex != "in")
		{
            QMessageBox* pmbx =
                                new QMessageBox("����������� ������!",
                                "��������� ����� � ������� ��� ���������� ����������.",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            //std::cout << "��������� ����� � ������� ��� ���������� ����������.";
            exit(-1);
		}
	}

}


void NameSyntax::K()
{

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	scaner->SetUk(uk1);

	if (*lex == ":" || *lex == "in")
		return;

	// ��������� �������

	while (type_lex != TYPE_SEMICOLON && type_lex != TYPE_END)
	{

		uk1 = scaner->GetUk();		
		type_lex = scaner->Scan(lex);


		if (type_lex == TYPE_COMMA)
		{
			type_lex = scaner->Scan(lex);

			// ��������� �������������
			if (type_lex == TYPE_IDENT)
			{
				// ����� ���� ������
				NameMetricsTree* new_node = new NameMetricsTree(*lex);
				this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

				continue;
			}

			// ��������� * �������������
			else if (type_lex == TYPE_POINTER)
			{
				type_lex = scaner->Scan(lex);
				if (type_lex == TYPE_IDENT)
				{
					// ����� ���� ������
					NameMetricsTree* new_node = new NameMetricsTree(*lex);
					this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

					continue;
				}
			}
		}

		// ���� ����� � ������� ��� ����� �����
		else if (type_lex == TYPE_END || type_lex == TYPE_SEMICOLON)
		{
			scaner->SetUk(uk1);
			break;
		}


	}

}



void NameSyntax::X()
{
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
	int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER || type_lex == TYPE_IDENT || type_lex == TYPE_COMMA || type_lex == TYPE_SEMICOLON)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (type_lex == TYPE_IDENT)
		{
			// ������ ++ ������� ������������� ��� lex
			
			BaseMetricsTree* v = this->currentNode->FindUp(*lex);

			if (v != NULL)
				v->GetData()->number_of_uses++;

		}


	}

	// ����������� ��������� ����� ��������, ��-�� ������� ����� �� �����
	scaner->SetUk(uk1);

}

void NameSyntax::V()
{
    //V -> (t * p id B) {

    // ��������� �� (
    std::string* lex = new std::string();

    int uk1 = scaner->GetUk();
    int type_lex = scaner->Scan(lex);
    type_lex = scaner->Scan(lex);

    while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER)
    {
        type_lex = scaner->Scan(lex);
    }

    if (type_lex == TYPE_IDENT)
    {
        NameMetricsTree* new_node = new NameMetricsTree(*lex);
        this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

        B();
    }

}

void NameSyntax::B()
{

    std::string* lex = new std::string();

    int uk1 = scaner->GetUk();		// ���������� ��� �������� ��������� � ������ ���������
    int type_lex = scaner->Scan(lex);	// ����������, �������� ������� ��� ������, ��������� ��������
    scaner->SetUk(uk1);

    // ��������� �������

    while (*lex != ")" && type_lex != TYPE_END)
    {

        uk1 = scaner->GetUk();
        type_lex = scaner->Scan(lex);

        if (*lex == ")") break;


        if (type_lex == TYPE_COMMA)
        {
            type_lex = scaner->Scan(lex);

            while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER)
            {
                type_lex = scaner->Scan(lex);
            }

            // ��������� �������������
            if (type_lex == TYPE_IDENT)
            {
                // ����� ���� ������
                NameMetricsTree* new_node = new NameMetricsTree(*lex);
                this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

                continue;
            }


        }

        // ���� ����� � ������� ��� ����� �����
        else if (type_lex == TYPE_END || *lex == ")")
        {
            break;
        }


    }

}

