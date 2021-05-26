#include "BlockMetricsTree.h"

// конструкторы классов вызывают базовый конструктор

BlockMetricsTree::BlockMetricsTree() : BaseMetricsTree() { }

BlockMetricsTree::BlockMetricsTree(std::string name) : BaseMetricsTree(name) { }

BlockMetricsTree::BlockMetricsTree(BlockMetricsTree* l, BlockMetricsTree* r, BlockMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики
int* BlockMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\nБлоков: " << results[0];
	std::cout << "\nВложенных блоков: " << results[1];
	std::cout << "\nМакс. уровень вложенности блоков: " << results[2];
	std::cout << "\nОбщая длина: " << results[3];

	return results;
}


void BlockMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			// просмотреть текущий узел

			results[0]++;		// кол-во блоков ++

			// если этот блок вложенный, инкрементируем
			if (root->n->is_inside)
				results[1]++;

			// если уровень макс уровень вложенности внутри этого блока, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[3] += root->n->length;	// суммируем длины

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
