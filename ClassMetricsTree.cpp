#include "ClassMetricsTree.h"
#include <QList>

// конструкторы классов вызывают базовый конструктор
ClassMetricsTree::ClassMetricsTree() : BaseMetricsTree() { }

ClassMetricsTree::ClassMetricsTree(std::string name) : BaseMetricsTree(name) { }

ClassMetricsTree::ClassMetricsTree(ClassMetricsTree* l, ClassMetricsTree* r, ClassMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// вычислить метрики (вызрв из root)
QList<int> ClassMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0, 0, 0 };

	DFS(this, results);



    //std::cout << "\n\nКлассов: " << results->at(0);
    //std::cout << "\nВложенных классов: " << results->at(1);
    //std::cout << "\nМакс. уровень вложенности классов: " << results->at(2);
    //std::cout << "\nОбщая длина: " << results->at(3);
    //std::cout << "\nВсего методов: " << results->at(4);
    //std::cout << "\nВсего классов-потомков: " << results->at(5);

    return *results;
}


void ClassMetricsTree::DFS(BaseMetricsTree* root,  QList<int>* results)
{
	if (root)
	{
		// если мы не в корне дерева
		if (root->Up)
		{
			// просмотреть текущий узел
			
            results->replace(0, results->at(0) + 1);

			// если этот класс вложенный, инкрементируем
			if (root->n->is_inside)
                results->replace(1, results->at(1) + 1);

			// если уровень макс уровень вложенности внутри этого класса, больше,
			// чем запомненный ранее, обновляем значение
			root->n->max_deep = CalcHeight(root->Right);
            if (root->n->max_deep > results->at(2))
                results->replace(2, root->n->max_deep);

            results->replace(3, results->at(3) + root->n->length);

			// суммируем кол-во методов         
             results->replace(4, results->at(4) + root->n->methods);

			if (root->n->has_parent)
                 results->replace(5, results->at(5) + 1);
		}

		// перейти к потомкам
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
