#include "NameMetricsTree.h"

// конструкторы классов вызывают базовый конструктор
NameMetricsTree::NameMetricsTree() : BaseMetricsTree() { }

NameMetricsTree::NameMetricsTree(std::string name) : BaseMetricsTree(name) { }

NameMetricsTree::NameMetricsTree(NameMetricsTree* l, NameMetricsTree* r, NameMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }




// вычислить метрики
QList<int> NameMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0 };

	DFS(this, results);

    //std::cout << "\n\nОбъявлено переменных: " << results->at(0);
    //std::cout << "\nИспользуемых переменных: " << results->at(1);
    //std::cout << "\nНеиспользуемых переменных: " << results->at(2);
    //std::cout << "\nОбщее число использований переменных: " << results->at(3);

    return *results;
}

void NameMetricsTree::DFS(BaseMetricsTree* root, QList<int>* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			if (root->n->ident != "{block}" && root->n->ident != "{inside-block}")
			{
                results->replace(0, results->at(0) + 1); // кол-во переменных

				// считаем кол-во использованых переменных
				if (root->n->number_of_uses > 0)
				{
                    results->replace(1, results->at(1) + 1);
                    results->replace(3, results->at(3) + root->n->number_of_uses);
				}
				else
                    results->replace(2, results->at(2) + 1);


			}

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
