#pragma once
#include "BaseMetricsTree.h"

class CyclesMetricsTree : public BaseMetricsTree
{
public:
	CyclesMetricsTree();
	CyclesMetricsTree(std::string name);
	CyclesMetricsTree(CyclesMetricsTree* l, CyclesMetricsTree* r, CyclesMetricsTree* u, Node* Data);

	int* CalculateMetrics() override;
	void DFS(BaseMetricsTree* root, int* results) override;	// Обход дерева в глубину
};

