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



// синтаксический анализатор
QList<int> ClassSyntax::Prog()
{
    QList<int> temp;
	BaseMetricsTree* save_cur = root->Cur;


	std::string* lex = new std::string();
	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером	

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

		
		// объявление класса начинается начинается с ключевого слова class, но перед ним может быть ряд ключевых слов (public, static, ...)
		// поэтому пропускаем всё до тех пор, пока не встретим ключевое слово class


		// SE
		if (type_lex == TYPE_CLASS)
		{			
			scaner->SetUk(uk1);
			E();					// ветка E -> class c* id c* {S} | class c* id c * id{ S }
		}
		else if (type_lex == TYPE_KEYWORD || type_lex == TYPE_TYPE || type_lex == TYPE_OTHER || type_lex == TYPE_IDENT || type_lex == TYPE_OPENED_BRACE)
		{

			scaner->SetUk(uk1);
			X();					// ветка X -> Xd | d | X id |  id | X c* | X { S }

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

    //std::cout << "\n\n ВЫХОД ИЗ prog (CLASS)\n\n";

    return root->CalculateMetrics();



}



// E -> class c* id c* { S } | class c* id c * id{ S }
void ClassSyntax::E()
{

	// указатель перед class
	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	
	if (type_lex == TYPE_CLASS)
	{
		type_lex = scaner->Scan(lex);

        while (type_lex == TYPE_KEYWORD)
		{
			type_lex = scaner->Scan(lex);

			if (type_lex == TYPE_END)
			{
                //std::cout << "Неожиданный конец файла. Синтаксическая ошибка";
                QMessageBox* pmbx =
                                    new QMessageBox("Критическая ошибка!",
                                    "Неожиданный конец файла. Синтаксическая ошибка",
                                    QMessageBox::Critical,
                                    QMessageBox::Ok,
                                    0,
                                    0);
                pmbx->exec();
                delete pmbx;
                exit(-1);
			}
		}

		// имя объявляемого класса
		if (type_lex == TYPE_IDENT)
		{
			BaseMetricsTree* save_parent = this->currentNode;


			// сохраняем текущий узел в дереве
			//this->currentNode = root->Add(*lex, false);
			this->currentNode = new ClassMetricsTree(*lex);
			save_parent->AddChieldForThisNode(this->currentNode);

			if (save_parent->Up)
				this->currentNode->n->is_inside = true;


            //std::cout << "\nПереходим в " << *lex << " (" << this->currentNode << ")";
			std::string name = *lex;

			type_lex = scaner->Scan(lex);

			// далее пропускаем пока не встретим { или идентификатор, но пропускаются только ключевые слова
			while (type_lex == TYPE_KEYWORD)
			{
				type_lex = scaner->Scan(lex);

				if (type_lex == TYPE_END)
				{

                    QMessageBox* pmbx =
                                        new QMessageBox("Критическая ошибка!",
                                        "Неожиданный конец файла. Синтаксическая ошибка",
                                        QMessageBox::Critical,
                                        QMessageBox::Ok,
                                        0,
                                        0);
                    pmbx->exec();
                    delete pmbx;
                    //std::cout << "Неожиданный конец файла. Синтаксическая ошибка";
                    exit(-1);
				}

			}

			// если наследование
			if (type_lex == TYPE_IDENT)
			{
				this->currentNode->n->has_parent = true;	// отметим, что этот класс - наследник

				// ожидается {
				type_lex = scaner->Scan(lex);

				if (type_lex == TYPE_OPENED_BRACE)
				{
					// дерево вложенность
					Prog();
				}


			}
			else if (type_lex == TYPE_OPENED_BRACE)
			{
				// дерево вложенность
				Prog();
			}

			// восстанавливаем текущий узел
			this->currentNode = save_parent;
            //std::cout << "\nВыходим из " << name << " Возвращаемся в (" << save_parent << ")";
			
		}

	}

}


// X -> Xd | d | X id |  id | X c* | X { S }
void ClassSyntax::X()
{
	// указатель перед лексемой

	std::string* lex = new std::string();

	int uk1 = scaner->GetUk();		// переменная для хранения указателя в тексте программы
	int type_lex = scaner->Scan(lex);	// переменная, хранящая текущий тип данных, считанный лексером
	scaner->SetUk(uk1);

	while (type_lex == TYPE_OTHER || type_lex == TYPE_TYPE || type_lex == TYPE_IDENT || type_lex == TYPE_KEYWORD || type_lex == TYPE_OPENED_BRACE)
	{
		uk1 = scaner->GetUk();
		type_lex = scaner->Scan(lex);

		if (type_lex == TYPE_IDENT && *lex == this->currentNode->n->ident)
		{
			int uk_after_ident = scaner->GetUk();
			type_lex = scaner->Scan(lex);


			// если после идентификатора следует ( - это метод
			if (type_lex == TYPE_OTHER && *lex == "(")
			{
				this->currentNode->n->methods++;

				while (*lex != ")")
				{
					type_lex = scaner->Scan(lex);
					if (type_lex == TYPE_END)
					{
                        QMessageBox* pmbx =
                                            new QMessageBox("Критическая ошибка!",
                                            "Неожиданный конец файла. Вероятно ошибка, при объявлении метода класса. Синтаксическая ошибка",
                                            QMessageBox::Critical,
                                            QMessageBox::Ok,
                                            0,
                                            0);
                        pmbx->exec();
                        delete pmbx;
                        //std::cout << "\nНеожиданный конец файла. Вероятно ошибка, при объявлении метода класса.";
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

			// после типа идёт идентификатор

			if (type_lex == TYPE_IDENT)
			{
				// тут считаем кол - во методов и полей
                int uk_after_ident = scaner->GetUk();
				type_lex = scaner->Scan(lex);

				// если после идентификатора следует ( - это метод
				if (type_lex == TYPE_OTHER && *lex == "(")
					this->currentNode->n->methods++;
				else
					scaner->SetUk(uk_after_ident);

			}


		}

		else if (type_lex == TYPE_OPENED_BRACE)
		{
			// дерево вложенность
			Prog();
		}

		else if (*lex == ";")
			this->currentNode->n->length++;

	}

	// восстановим указатель перед лексемой, из-за которой вышли из цикла

	scaner->SetUk(uk1);

}

