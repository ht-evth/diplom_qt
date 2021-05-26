#include "BlockMetricsTree.h"

// ������������ ������� �������� ������� �����������

BlockMetricsTree::BlockMetricsTree() : BaseMetricsTree() { }

BlockMetricsTree::BlockMetricsTree(std::string name) : BaseMetricsTree(name) { }

BlockMetricsTree::BlockMetricsTree(BlockMetricsTree* l, BlockMetricsTree* r, BlockMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// ��������� �������
int* BlockMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\n������: " << results[0];
	std::cout << "\n��������� ������: " << results[1];
	std::cout << "\n����. ������� ����������� ������: " << results[2];
	std::cout << "\n����� �����: " << results[3];

	return results;
}


void BlockMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			// ����������� ������� ����

			results[0]++;		// ���-�� ������ ++

			// ���� ���� ���� ���������, ��������������
			if (root->n->is_inside)
				results[1]++;

			// ���� ������� ���� ������� ����������� ������ ����� �����, ������,
			// ��� ����������� �����, ��������� ��������
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[3] += root->n->length;	// ��������� �����

		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
