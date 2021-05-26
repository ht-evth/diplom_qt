#include "NameMetricsTree.h"

// ������������ ������� �������� ������� �����������
NameMetricsTree::NameMetricsTree() : BaseMetricsTree() { }

NameMetricsTree::NameMetricsTree(std::string name) : BaseMetricsTree(name) { }

NameMetricsTree::NameMetricsTree(NameMetricsTree* l, NameMetricsTree* r, NameMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }




// ��������� �������
QList<int> NameMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0 };

	DFS(this, results);

    std::cout << "\n\n��������� ����������: " << results->at(0);
    std::cout << "\n������������ ����������: " << results->at(1);
    std::cout << "\n�������������� ����������: " << results->at(2);
    std::cout << "\n����� ����� ������������� ����������: " << results->at(3);

    return *results;
}

void NameMetricsTree::DFS(BaseMetricsTree* root, QList<int>* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			if (root->n->ident != "{block}" && root->n->ident != "{inside-block}")
			{
                results->replace(0, results->at(0) + 1); // ���-�� ����������

				// ������� ���-�� ������������� ����������
				if (root->n->number_of_uses > 0)
				{
                    results->replace(1, results->at(1) + 1);
                    results->replace(3, results->at(3) + root->n->number_of_uses);
				}
				else
                    results->replace(2, results->at(2) + 1);

                if (root->n->managment)
                    results->replace(4, results->at(4) + 1);


			}

		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
