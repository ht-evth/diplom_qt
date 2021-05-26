#pragma once
#include "BaseScanner.h"
#include "BaseMetricsTree.h"

class BaseSyntax {
protected:
    BaseScanner* scaner;        // сканнер
    BaseMetricsTree* root;      // дерево
    BaseMetricsTree* currentNode;   // текущий узел в дереве

public:
    virtual int* Prog() = 0;    // аксиома

    void PrintTree(bool with_value = false);
};
