#include "BlockMetricsTree.h"

// ������������ ������� �������� ������� �����������

BlockMetricsTree::BlockMetricsTree() : BaseMetricsTree() { }

BlockMetricsTree::BlockMetricsTree(std::string name) : BaseMetricsTree(name) { }

BlockMetricsTree::BlockMetricsTree(BlockMetricsTree* l, BlockMetricsTree* r, BlockMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// ��������� �������
QList<int> BlockMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0 };


	DFS(this, results);

    std::cout << "\n\n������: " << results->at(0);
    std::cout << "\n��������� ������: " << results->at(1);
    std::cout << "\n����. ������� ����������� ������: " << results->at(2);
    std::cout << "\n����� �����: " << results->at(3);

    return *results;
}


void BlockMetricsTree::DFS(BaseMetricsTree* root,  QList<int>* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			// ����������� ������� ����

            results->replace(0, results->at(0) + 1);		// ���-�� ������ ++

			// ���� ���� ���� ���������, ��������������
			if (root->n->is_inside)
                results->replace(1, results->at(1) + 1);

			// ���� ������� ���� ������� ����������� ������ ����� �����, ������,
			// ��� ����������� �����, ��������� ��������
			root->n->max_deep = CalcHeight(root->Right);
            if (root->n->max_deep > results->at(2))
                results->replace(2, root->n->max_deep);

            results->replace(3, results->at(3) + root->n->length);

		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
