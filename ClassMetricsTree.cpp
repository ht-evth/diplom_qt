#include "ClassMetricsTree.h"

// ������������ ������� �������� ������� �����������
ClassMetricsTree::ClassMetricsTree() : BaseMetricsTree() { }

ClassMetricsTree::ClassMetricsTree(std::string name) : BaseMetricsTree(name) { }

ClassMetricsTree::ClassMetricsTree(ClassMetricsTree* l, ClassMetricsTree* r, ClassMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// ��������� ������� (����� �� root)
int* ClassMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\n�������: " << results[0];
	std::cout << "\n��������� �������: " << results[1];
	std::cout << "\n����. ������� ����������� �������: " << results[2];
	std::cout << "\n����� �����: " << results[3];
	std::cout << "\n����� �����: " << results[4];
	std::cout << "\n����� �������: " << results[5];
	std::cout << "\n����� �������-��������: " << results[6];

	return results;
}


void ClassMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			// ����������� ������� ����
			
			results[0]++;		// ���-�� ������� ++

			// ���� ���� ����� ���������, ��������������
			if (root->n->is_inside)
				results[1]++;

			// ���� ������� ���� ������� ����������� ������ ����� ������, ������,
			// ��� ����������� �����, ��������� ��������
			root->n->max_deep = CalcHeight(root->Right);
			if (root->n->max_deep > results[2])
				results[2] = root->n->max_deep;

			results[3] += root->n->length;	// ��������� �����

			// ��������� ���-�� ����� 
			//results[4] += root->n->fields;

			// ��������� ���-�� �������
			results[5] += root->n->methods;

			if (root->n->has_parent)
				results[6]++;
		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}