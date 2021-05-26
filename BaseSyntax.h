#pragma once
#include "BaseScanner.h"
#include "BaseMetricsTree.h"

class BaseSyntax {
protected:
    BaseScanner* scaner;        // �������
    BaseMetricsTree* root;      // ������
    BaseMetricsTree* currentNode;   // ������� ���� � ������

public:
    virtual void Prog() = 0;    // �������

    void PrintTree(bool with_value = false);
};