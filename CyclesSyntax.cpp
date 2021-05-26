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

// синтаксический анализатор
QList<int> CyclesSyntax::Prog()
{
    QList<int> temp;
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	
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
		
		if (type_lex != TYPE_CLOSED_BRACE)
		{
			if (type_lex != TYPE_OPENED_BRACE)
				scaner->SetUk(uk1);
		}
		else
            return temp;


		// SE
		if (type_lex == TYPE_FOR || type_lex == TYPE_DO || type_lex == TYPE_WHILE)
		{
			// отдельная проверка на do while

			if (is_do_while)
			{
				is_do_while = false;
                return temp;
			}

			scaner->SetUk(uk1);
			E();					// ветка E -> for(c*) | for(c*) { S } | while X | while X{ S } | do S while
		}

		// SX
		else if (type_lex == TYPE_OTHER)
		{
			scaner->SetUk(uk1);
			X();					// ветка X -> Xd | d 
		}

		// SD
		else if (type_lex == TYPE_OPENED_BRACE)
		{
			scaner->SetUk(uk1);
			D();					// ветка D -> { S } 
		}

		// проверка на конец файла
		else if (type_lex == TYPE_END)
		{
			//std::cout << "Дошли до конца модуля!" << std::endl;
			scaner->SetUk(uk1); // на случай рекурсии
			break;
		}
		else
			type_lex = scaner->Scan(lex);


	}

    return root->CalculateMetrics();

}



// E -> for(c*) | for(c*) { S } | while X | while X{ S } | do S while
void CyclesSyntax::E()
{
	// указатель перед class
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером

	// запоминаем текущий узел дерева (для возврата из вложенности)
	BaseMetricsTree* save_parent = this->currentNode;
	std::string name = ""; // имя цикла для отладки

	// цикл for
	if (type_lex == TYPE_FOR)
	{
		// работа с деревом
		name = "for" + std::to_string(counter++);

		type_lex = scaner->Scan(lex);
		// после for открывается скобка, далее не важно что... 
		if (*lex == "(")
		{
			while (*lex != ")")
			{
				type_lex = scaner->Scan(lex);
				if (type_lex == TYPE_END)
				{
					std::cout << "Ожидалась скобка ')' для оператора цикла for";
					exit(-1);
				}
			}



			// далее может быть {
			uk1 = scaner->GetUk();
			type_lex = scaner->Scan(lex);


			// тут можно ещё отслеживать однострочные циклы...
			if (type_lex == TYPE_OPENED_BRACE)
			{
				this->currentNode = new CyclesMetricsTree(name);
				save_parent->AddChieldForThisNode(this->currentNode);

				if (save_parent->Up)
					this->currentNode->n->is_inside = true;

				std::cout << "\nПереходим в " << name << " (" << this->currentNode << ")";
				// вложенность

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
		// работа с деревом
		name = "while" + std::to_string(counter++);
		X();

		// далее может быть {
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		// тут можно ещё отслеживать однострочные циклы...
		if (type_lex == TYPE_OPENED_BRACE)
		{
			// вложенность
			
			this->currentNode = new CyclesMetricsTree(name);
			save_parent->AddChieldForThisNode(this->currentNode);

			if (save_parent->Up)
				this->currentNode->n->is_inside = true;

			std::cout << "\nПереходим в " << name << " (" << this->currentNode << ")";

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

		std::cout << "\nПереходим в " << name << " (" << this->currentNode << ")";

	
		int uk2 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		// если не {
		if (type_lex != TYPE_OPENED_BRACE)
			scaner->Scan(lex);	// восстановим указатель перед {

		Prog();


		// ожидается while
		uk2 = scaner->GetUk();
		type_lex = scaner->Scan(lex);
		if (type_lex != TYPE_WHILE)
		{
			std::cout << "ожидается оператор while для do-while.";
			exit(-1);
		}

	}


	// восстанавливаем текущий узел - выход из вложенности
	std::cout << "\nВыходим из " << name << " возврат в (" << save_parent << ")";
	this->currentNode = save_parent;

}


// X -> Xd | d 
void CyclesSyntax::X()
{
	// указатель перед лексемой

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
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

	// восстановим указатель перед лексемой, из-за которой вышли из цикла
	scaner->SetUk(uk1);

}


// D -> { S } 
void CyclesSyntax::D()
{
	// указатель перед {

	Prog();

	// указатель после }

}
