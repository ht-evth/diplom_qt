#pragma once
#include "Node.h"
#include <QList>

class BaseMetricsTree
{
public:
	Node* n;					// ������ � ���� ������
	BaseMetricsTree* Up;		// ��������
	BaseMetricsTree* Left;		// ����� �������
	BaseMetricsTree* Right;		// ������ �������

	BaseMetricsTree* GetLastNeighbor();	// �������� ���������� ������ ��� �������� ����
	

public:
	static BaseMetricsTree* Cur;	// ������� ����

	BaseMetricsTree(BaseMetricsTree* l, BaseMetricsTree* r, BaseMetricsTree* u, Node* Data);	// ����������� ������
	BaseMetricsTree(std::string ident);															// ����������� ������
	BaseMetricsTree();																			// ����������� ������

	void Print(bool with_value = false);	// ���������� ������ ������

	void AddChieldForThisNode(BaseMetricsTree* chield);					// ������� ������ ����� ��� �������� ���� ������
	BaseMetricsTree* AddNeighborForThisNode(BaseMetricsTree* neighbor);	// ������� ������� ������ ��� �������� ���� ������

	
	BaseMetricsTree* GetUp();	// ������� ��������� �� �������� �������� ����
	Node* GetData();	// ������� ������ �� ������ � ����
	BaseMetricsTree* FindUp(std::string ident); // ����� ������ �� ������� ������� �� �����	
	BaseMetricsTree* FindUp(BaseMetricsTree* From, std::string ident);	// ����� ������ �� �������� ������� �� �����

    virtual QList<int> CalculateMetrics() = 0;				// ��������� �������
    virtual void DFS(BaseMetricsTree* root, QList<int>* results) = 0;	// ����� ������ � �������
	int CalcHeight(BaseMetricsTree* root);			// �������� ������ ���������
	// int ....		// �������� ����� ���������� ������� � ������

};

