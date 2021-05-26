#include "ClassMetricsTree.h"

// конструкторы классов вызывают базовый конструктор
ClassMetricsTree::ClassMetricsTree() : BaseMetricsTree() { }

ClassMetricsTree::ClassMetricsTree(std::string name) : BaseMetricsTree(name) { }

ClassMetricsTree::ClassMetricsTree(ClassMetricsTree* l, ClassMetricsTree* r, ClassMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики (вызрв из root)
int* ClassMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\nКлассов: " << results[0];
	std::cout << "\nВложенных классов: " << results[1];
	std::cout << "\nМакс. уровень вложенности классов: " << results[2];
	std::cout << "\nОбщая длина: " << results[3];
	std::cout << "\nВсего полей: " << results[4];
	std::cout << "\nВсего методов: " << results[5];
	std::cout << "\nВсего классов-потомков: " << results[6];

	return results;
}


void ClassMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			// просмотреть текущий узел
			
			results[0]++;		// кол-во классов ++

			// если этот класс вложенный, инкрементируем
			if (root->n->is_inside)
				results[1]++;

			// если уровень макс уровень вложенности внутри этого класса, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[3] += root->n->length;	// суммируем длины

			// суммируем кол-во полей 
			//results[4] += root->n->fields;

			// суммируем кол-во методов
			results[5] += root->n->methods;

			if (root->n->has_parent)
				results[6]++;
		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}