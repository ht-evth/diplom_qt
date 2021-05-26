#pragma once
#include "BaseMetricsTree.h"
#include <list>


class ClassMetricsTree : public BaseMetricsTree
{

public:
	ClassMetricsTree();
	ClassMetricsTree(std::string name);
	ClassMetricsTree(ClassMetricsTree* l, ClassMetricsTree* r, ClassMetricsTree* u, Node* Data);

	int* CalculateMetrics() override;
	
	void DFS(BaseMetricsTree* root, int* results) override;	// Обход дерева в глубину
};

