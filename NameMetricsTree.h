#pragma once
#include "BaseMetricsTree.h"

class NameMetricsTree : public BaseMetricsTree
{
private:


public:
	NameMetricsTree();
	NameMetricsTree(std::string name);
	NameMetricsTree(NameMetricsTree* l, NameMetricsTree* r, NameMetricsTree* u, Node* Data);

    QList<int> CalculateMetrics() override;
    void DFS(BaseMetricsTree* root, QList<int>* results) override;	// Обход дерева в глубину
};

