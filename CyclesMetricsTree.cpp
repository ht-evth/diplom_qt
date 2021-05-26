#include "CyclesMetricsTree.h"

// ������������ ������� �������� ������� �����������
CyclesMetricsTree::CyclesMetricsTree() : BaseMetricsTree() { }

CyclesMetricsTree::CyclesMetricsTree(std::string name) : BaseMetricsTree(name) { }

CyclesMetricsTree::CyclesMetricsTree(CyclesMetricsTree* l, CyclesMetricsTree* r, CyclesMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// ��������� �������
int* CyclesMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\n������: " << results[0];
	std::cout << "\n��������� ������: " << results[1];
	std::cout << "\n����. ������� ����������� ������: " << results[2];
	std::cout << "\n����� ���-�� ���������������� ������: " << results[3];
	std::cout << "\n����� �����: " << results[4];
	std::cout << "\n���������� continue: " << results[5];
	std::cout << "\n���������� break/return: " << results[6];

	return results;
}

void CyclesMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			results[0]++;		// ���-�� ������ ++

			// ���� ���� ���� ���������, ��������������
			if (root->n->is_inside)
				results[1]++;

			// ���� ������� ���� ������� ����������� ������ ����� ������, ������,
			// ��� ����������� �����, ��������� ��������
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[4] += root->n->length;	// ��������� �����

			// ��������� continue
			results[5] += root->n->_continue;

			// ��������� break_return
			results[6] += root->n->break_return;

		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}

}

