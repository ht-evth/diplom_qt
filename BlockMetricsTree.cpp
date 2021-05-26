#include "BlockMetricsTree.h"

// конструкторы классов вызывают базовый конструктор

BlockMetricsTree::BlockMetricsTree() : BaseMetricsTree() { }

BlockMetricsTree::BlockMetricsTree(std::string name) : BaseMetricsTree(name) { }

BlockMetricsTree::BlockMetricsTree(BlockMetricsTree* l, BlockMetricsTree* r, BlockMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики
QList<int> BlockMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0 };


	DFS(this, results);

    std::cout << "\n\nБлоков: " << results->at(0);
    std::cout << "\nВложенных блоков: " << results->at(1);
    std::cout << "\nМакс. уровень вложенности блоков: " << results->at(2);
    std::cout << "\nОбщая длина: " << results->at(3);

    return *results;
}


void BlockMetricsTree::DFS(BaseMetricsTree* root,  QList<int>* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			// просмотреть текущий узел

            results->replace(0, results->at(0) + 1);		// кол-во блоков ++

			// если этот блок вложенный, инкрементируем
			if (root->n->is_inside)
                results->replace(1, results->at(1) + 1);

			// если уровень макс уровень вложенности внутри этого блока, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
            if (root->n->max_deep > results->at(2))
                results->replace(2, root->n->max_deep);

            results->replace(3, results->at(3) + root->n->length);

		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
