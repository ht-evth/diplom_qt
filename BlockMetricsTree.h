#pragma once
#include "BaseMetricsTree.h"

class BlockMetricsTree : public BaseMetricsTree
{
public:
	BlockMetricsTree();
	BlockMetricsTree(std::string name);
	BlockMetricsTree(BlockMetricsTree* l, BlockMetricsTree* r, BlockMetricsTree* u, Node* Data);

	int* CalculateMetrics() override;
	void DFS(BaseMetricsTree* root, int* results) override;	// Обход дерева в глубину

};

