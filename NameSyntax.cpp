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


// синтаксический анализатор
QList<int> NameSyntax::Prog()
{
    QList<int> temp;
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();			// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	
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
			int uk_before_ident = scaner->GetUk();	// сохраним значение указателя до идентифактора
            while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER || *lex == "[" || *lex == "]")
			{
				type_lex = scaner->Scan(lex);
                if (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER || *lex == "[" || *lex == "]")
					uk_before_ident = scaner->GetUk();
			}

			// ожидается идентификатор (SD)
			if (type_lex == TYPE_IDENT)
			{
				// после идентификатора ожидается ветка D
				// восстановим указатель 

				int uk2 = scaner->GetUk();
				scaner->Scan(lex);
				scaner->SetUk(uk2);

				if (*lex != "(")
				{
					scaner->SetUk(uk_before_ident);
					D();	// перейдём к ветке D -> t* id K;
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

		// проверка на конец файла
		else if (type_lex == TYPE_END)
		{
			//std::cout << "Дошли до конца модуля!" << std::endl;
			scaner->SetUk(uk1); // на случай рекурсии
			break;
		}

		

	}

    return this->root->CalculateMetrics();

}



void NameSyntax::E()
{
	// УКАЗАТЕЛЬ УЖЕ ПОСЛЕ {

	// строим дерево с учетом вложенности
	// создаём узел {}

	NameMetricsTree* new_node = new NameMetricsTree("{block}");
	this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

	// создаём ещё один узел {vlozh} для реализации вложенности
	// и переходим в него
	NameMetricsTree* new_vlozh = new NameMetricsTree("{inside-block}");
	this->currentNode->AddChieldForThisNode(new_vlozh);;
	this->currentNode = new_vlozh;

	Prog();

	// вернуться на предыдущий уровень вложенности
	// возвращаемся к узлу {}
	this->currentNode = new_node;
}


void NameSyntax::D()
{
	// указатель уже перед ident 

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	
	// сейчас уже считан ident
	if (type_lex != TYPE_IDENT)
	{
        QMessageBox* pmbx =
                            new QMessageBox("Критическая ошибка!",
                            "Ожидался идентификатор при объявлении переменной.",
                            QMessageBox::Critical,
                            QMessageBox::Ok,
                            0,
                            0);
        pmbx->exec();
        //std::cout << "Ожидался идентификатор при объявлении переменной.";
        exit(-1);
	}

	NameMetricsTree* new_node = new NameMetricsTree(*lex);
	this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

	K();		// ветка K -> , id K | , p id  K | eps

	type_lex = scaner->Scan(lex);
	if (type_lex != TYPE_SEMICOLON)
	{
		if (*lex != ":" && *lex != "in")
		{
            QMessageBox* pmbx =
                                new QMessageBox("Критическая ошибка!",
                                "Ожидалась точка с запятой при объявлении переменных.",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            //std::cout << "Ожидалась точка с запятой при объявлении переменных.";
            exit(-1);
		}
	}

}


void NameSyntax::K()
{

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	scaner->SetUk(uk1);

	if (*lex == ":" || *lex == "in")
		return;

	// ожидается запятая

	while (type_lex != TYPE_SEMICOLON && type_lex != TYPE_END)
	{

		uk1 = scaner->GetUk();		
		type_lex = scaner->Scan(lex);


		if (type_lex == TYPE_COMMA)
		{
			type_lex = scaner->Scan(lex);

			// ожидается идентификатор
			if (type_lex == TYPE_IDENT)
			{
				// новый узел дерева
				NameMetricsTree* new_node = new NameMetricsTree(*lex);
				this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

				continue;
			}

			// ожидается * идентификатор
			else if (type_lex == TYPE_POINTER)
			{
				type_lex = scaner->Scan(lex);
				if (type_lex == TYPE_IDENT)
				{
					// новый узел дерева
					NameMetricsTree* new_node = new NameMetricsTree(*lex);
					this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

					continue;
				}
			}
		}

		// если точка с запятой или конец файла
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

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER || type_lex == TYPE_IDENT || type_lex == TYPE_COMMA || type_lex == TYPE_SEMICOLON)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (type_lex == TYPE_IDENT)
		{
			// дерево ++ счетчик использования для lex
			
			BaseMetricsTree* v = this->currentNode->FindUp(*lex);

			if (v != NULL)
				v->GetData()->number_of_uses++;

		}


	}

	// восстановим указатель перед лексемой, из-за которой вышли из цикла
	scaner->SetUk(uk1);

}

void NameSyntax::V()
{
    //V -> (t * p id B) {

    // указатель до (
    std::string* lex = new std::string();

    int uk1 = scaner->GetUk();
    int type_lex = scaner->Scan(lex);
    type_lex = scaner->Scan(lex);

    while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER || *lex == "[" || *lex == "]")
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

    int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
    int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
    scaner->SetUk(uk1);

    // ожидается запятая

    while (*lex != ")" && type_lex != TYPE_END)
    {

        uk1 = scaner->GetUk();
        type_lex = scaner->Scan(lex);

        if (*lex == ")") break;


        if (type_lex == TYPE_COMMA)
        {
            type_lex = scaner->Scan(lex);

            while (type_lex == TYPE_TYPE || type_lex == TYPE_POINTER || *lex == "[" || *lex == "]")
            {
                type_lex = scaner->Scan(lex);
            }

            // ожидается идентификатор
            if (type_lex == TYPE_IDENT)
            {
                // новый узел дерева
                NameMetricsTree* new_node = new NameMetricsTree(*lex);
                this->currentNode = this->currentNode->AddNeighborForThisNode(new_node);

                continue;
            }


        }

        // если точка с запятой или конец файла
        else if (type_lex == TYPE_END || *lex == ")")
        {
            break;
        }


    }

}

