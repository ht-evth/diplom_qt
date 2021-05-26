#include "NameMetricsTree.h"

// конструкторы классов вызывают базовый конструктор
NameMetricsTree::NameMetricsTree() : BaseMetricsTree() { }

NameMetricsTree::NameMetricsTree(std::string name) : BaseMetricsTree(name) { }

NameMetricsTree::NameMetricsTree(NameMetricsTree* l, NameMetricsTree* r, NameMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }




// вычислить метрики
int* NameMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\nОбъявлено переменных: " << results[0];
	std::cout << "\nИспользуемых переменных: " << results[1];
	std::cout << "\nНеиспользуемых переменных: " << results[2];
	std::cout << "\nОбщее число использований переменных: " << results[3];
	std::cout << "\nУправляющие переменные: " << results[4];
	//std::cout << "\nОбщая длина: " << results[4];
	//std::cout << "\nОператоров continue: " << results[5];
	//std::cout << "\nОператоров break/return: " << results[6];

	return results;
}

void NameMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			if (root->n->ident != "{block}" && root->n->ident != "{inside-block}")
			{
				results[0]++;		// кол-во переменных

				// считаем кол-во использованых переменных
				if (root->n->number_of_uses > 0)
				{
					results[1]++;
					results[3] += root->n->number_of_uses;
				}
				else
					results[2]++;

				if (root->n->managment)
					results[4]++;


			}

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}


/*
int NameMetricsTree::used = 0;
int NameMetricsTree::unused = 0;

void NameMetricsTree::deep()
{
	deep(this);
}


void NameMetricsTree::deep(BaseMetricsTree* From)
{
	if (From == NULL)
		return;

	if (From->GetData()->ident != "{}" && From->GetData()->ident != "{inside}" && From->GetData()->ident != "root")
	{
		if (From->GetData()->number_of_uses > 0)
			used++;
		else
			unused++;
	}
		

	if (((NameMetricsTree*)From)->Right) deep(((NameMetricsTree*)From)->Right);
	if (((NameMetricsTree*)From)->Left) deep(((NameMetricsTree*)From)->Left);

}
*/