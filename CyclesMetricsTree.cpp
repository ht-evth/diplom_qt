#include "CyclesMetricsTree.h"

// конструкторы классов вызывают базовый конструктор
CyclesMetricsTree::CyclesMetricsTree() : BaseMetricsTree() { }

CyclesMetricsTree::CyclesMetricsTree(std::string name) : BaseMetricsTree(name) { }

CyclesMetricsTree::CyclesMetricsTree(CyclesMetricsTree* l, CyclesMetricsTree* r, CyclesMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики
int* CyclesMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\nЦиклов: " << results[0];
	std::cout << "\nВложенных циклов: " << results[1];
	std::cout << "\nМакс. уровень вложенности циклов: " << results[2];
	std::cout << "\nОбщее кол-во последовательных циклов: " << results[3];
	std::cout << "\nОбщая длина: " << results[4];
	std::cout << "\nОператоров continue: " << results[5];
	std::cout << "\nОператоров break/return: " << results[6];

	return results;
}

void CyclesMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			results[0]++;		// кол-во циклов ++

			// если этот цикл вложенный, инкрементируем
			if (root->n->is_inside)
				results[1]++;

			// если уровень макс уровень вложенности внутри этого класса, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[4] += root->n->length;	// суммируем длины

			// суммируем continue
			results[5] += root->n->_continue;

			// суммируем break_return
			results[6] += root->n->break_return;

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}

}

