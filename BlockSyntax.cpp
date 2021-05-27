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

// синтаксический анализатор
QList<int> BlockSyntax::Prog()
{
    QList<int> temp;
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	
	// проверки, чтобы избежать зацикливания
	if (type_lex != TYPE_CLOSED_BRACE)
	{
		if (type_lex != TYPE_OPENED_BRACE)
			scaner->SetUk(uk1);
	}
	else
        return temp;
	

	while (type_lex != TYPE_END && type_lex != TYPE_CLOSED_BRACE)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
		
		// проверки, чтобы избежать зацикливания
		if (type_lex != TYPE_CLOSED_BRACE)
				scaner->SetUk(uk1);
		else
            return temp;;

		// SE
		if (type_lex == TYPE_OPENED_BRACE)
		{
			// вложенность
			E();					// ветка E -> { S }
		}

		// SX
		else if (TYPE_OTHER)
		{
			scaner->SetUk(uk1);
			X();					// ветка X -> Xd | d 
		}

		// проверка на конец файла
		else if (type_lex == TYPE_END)
		{
			//std::cout << "Дошли до конца модуля!" << std::endl;
			scaner->SetUk(uk1); // восстановим указатель (на случай рекурсии)
			break;
		}
		else
			type_lex = scaner->Scan(lex);

	}

    return this->root->CalculateMetrics();

}



// E -> { S }
void BlockSyntax::E()
{
	// указатель после {

	// сохраняем родительский узел (чтобы выйти из вложенности)
	BaseMetricsTree* save_parent = this->currentNode;

	std::string name = "{" + std::to_string(counter++) + "}";

	this->currentNode = new BlockMetricsTree(name);
	save_parent->AddChieldForThisNode(this->currentNode);

	if (save_parent->Up)
		this->currentNode->n->is_inside = true;


    //std::cout << "\nВошли в блок " << name;

	// вложенность
	Prog();

	// Выход из вложенности
    //std::cout << "\nВышли из блока" << name;
	this->currentNode = save_parent;
}


// X -> Xd | d 
void BlockSyntax::X()
{
	// указатель перед лексемой

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER)
	{
		if (*lex == ";") this->currentNode->n->length++;

		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
	}

	// восстановим указатель перед лексемой, из-за которой вышли из цикла
	scaner->SetUk(uk1);

}
