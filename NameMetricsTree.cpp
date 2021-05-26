#include "NameMetricsTree.h"

// ������������ ������� �������� ������� �����������
NameMetricsTree::NameMetricsTree() : BaseMetricsTree() { }

NameMetricsTree::NameMetricsTree(std::string name) : BaseMetricsTree(name) { }

NameMetricsTree::NameMetricsTree(NameMetricsTree* l, NameMetricsTree* r, NameMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }




// ��������� �������
int* NameMetricsTree::CalculateMetrics()
{
	int results[] = { 0, 0, 0, 0, 0 };

	DFS(this, results);

	std::cout << "\n\n��������� ����������: " << results[0];
	std::cout << "\n������������ ����������: " << results[1];
	std::cout << "\n�������������� ����������: " << results[2];
	std::cout << "\n����� ����� ������������� ����������: " << results[3];
	std::cout << "\n����������� ����������: " << results[4];
	//std::cout << "\n����� �����: " << results[4];
	//std::cout << "\n���������� continue: " << results[5];
	//std::cout << "\n���������� break/return: " << results[6];

	return results;
}

void NameMetricsTree::DFS(BaseMetricsTree* root, int* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			if (root->n->ident != "{block}" && root->n->ident != "{inside-block}")
			{
				results[0]++;		// ���-�� ����������

				// ������� ���-�� ������������� ����������
				if (root->n->number_of_uses > 0)
				{
					results[1]++;
					results[3] += root->n->number_of_uses;
				}
				else
					results[2]++;

				if (root->n->managment)
					results[4]++;


			}

		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}


/*
int NameMetricsTree::used = 0;
int NameMetricsTree::unused = 0;

void NameMetricsTree::deep()
{
	deep(this);
}


void NameMetricsTree::deep(BaseMetricsTree* From)
{
	if (From == NULL)
		return;

	if (From->GetData()->ident != "{}" && From->GetData()->ident != "{inside}" && From->GetData()->ident != "root")
	{
		if (From->GetData()->number_of_uses > 0)
			used++;
		else
			unused++;
	}
		

	if (((NameMetricsTree*)From)->Right) deep(((NameMetricsTree*)From)->Right);
	if (((NameMetricsTree*)From)->Left) deep(((NameMetricsTree*)From)->Left);

}
*/