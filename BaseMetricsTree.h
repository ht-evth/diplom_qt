#pragma once
#include "Node.h"
#include <QList>

class BaseMetricsTree
{
public:
	Node* n;					// данные в узле дерева
	BaseMetricsTree* Up;		// родитель
	BaseMetricsTree* Left;		// левый потомок
	BaseMetricsTree* Right;		// правый потомок

	BaseMetricsTree* GetLastNeighbor();	// получить последнего соседа для текущего узла
	

public:
	static BaseMetricsTree* Cur;	// текущий узел

	BaseMetricsTree(BaseMetricsTree* l, BaseMetricsTree* r, BaseMetricsTree* u, Node* Data);	// конструктор класса
	BaseMetricsTree(std::string ident);															// конструктор класса
	BaseMetricsTree();																			// конструктор класса

	void Print(bool with_value = false);	// отладочная печать дерева

	void AddChieldForThisNode(BaseMetricsTree* chield);					// создать соседа слева для текущего узла дерева
	BaseMetricsTree* AddNeighborForThisNode(BaseMetricsTree* neighbor);	// создать потомка справа для текущего узла дерева

	
	BaseMetricsTree* GetUp();	// вернуть указатель на родителя текущего узла
	Node* GetData();	// вернуть ссылку на данные в узле
	BaseMetricsTree* FindUp(std::string ident); // поиск данных от текущей вершины до корня	
	BaseMetricsTree* FindUp(BaseMetricsTree* From, std::string ident);	// поиск данных от заданной вершины до корня

    virtual QList<int> CalculateMetrics() = 0;				// вычислить метрики
    virtual void DFS(BaseMetricsTree* root, QList<int>* results) = 0;	// Обход дерева в глубину
	int CalcHeight(BaseMetricsTree* root);			// получить высоту поддерева
	// int ....		// получить общее количество соседей в дереве

};

