#include "CyclesMetricsTree.h"

// конструкторы классов вызывают базовый конструктор
CyclesMetricsTree::CyclesMetricsTree() : BaseMetricsTree() { }

CyclesMetricsTree::CyclesMetricsTree(std::string name) : BaseMetricsTree(name) { }

CyclesMetricsTree::CyclesMetricsTree(CyclesMetricsTree* l, CyclesMetricsTree* r, CyclesMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики
QList<int> CyclesMetricsTree::CalculateMetrics()
{
        QList<int>* results = new QList<int>{ 0, 0, 0, 0, 0, 0 };

	DFS(this, results);

    std::cout << "\n\nЦиклов: " << results->at(0);
    std::cout << "\nВложенных циклов: " << results->at(1);
    std::cout << "\nМакс. уровень вложенности циклов: " << results->at(2);
    std::cout << "\nОбщая длина: " << results->at(3);
    std::cout << "\nОператоров continue: " << results->at(4);
    std::cout << "\nОператоров break/return: " << results->at(5);

    return *results;
}

void CyclesMetricsTree::DFS(BaseMetricsTree* root, QList<int>* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
            results->replace(0, results->at(0) + 1); // кол-во циклов ++

			// если этот цикл вложенный, инкрементируем
			if (root->n->is_inside)
                results->replace(1, results->at(1) + 1);

			// если уровень макс уровень вложенности внутри этого класса, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
            if (root->n->max_deep > results->at(2))
                results->replace(2, root->n->max_deep);

            // суммируем длины
            results->replace(3, results->at(3) + root->n->length);

			// суммируем continue
            results->replace(4, results->at(4) + root->n->_continue);

			// суммируем break_return
            results->replace(5, results->at(5) + root->n->break_return);

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}

}

