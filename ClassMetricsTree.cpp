#include "ClassMetricsTree.h"
#include <QList>

// ������������ ������� �������� ������� �����������
ClassMetricsTree::ClassMetricsTree() : BaseMetricsTree() { }

ClassMetricsTree::ClassMetricsTree(std::string name) : BaseMetricsTree(name) { }

ClassMetricsTree::ClassMetricsTree(ClassMetricsTree* l, ClassMetricsTree* r, ClassMetricsTree* u, Node* Data) : BaseMetricsTree(l, r, u, Data) { }


// ��������� ������� (����� �� root)
QList<int> ClassMetricsTree::CalculateMetrics()
{
    QList<int>* results = new QList<int>{ 0, 0, 0, 0, 0, 0 };

	DFS(this, results);



    std::cout << "\n\n�������: " << results->at(0);
    std::cout << "\n��������� �������: " << results->at(1);
    std::cout << "\n����. ������� ����������� �������: " << results->at(2);
    std::cout << "\n����� �����: " << results->at(3);
    std::cout << "\n����� �������: " << results->at(4);
    std::cout << "\n����� �������-��������: " << results->at(5);

    return *results;
}


void ClassMetricsTree::DFS(BaseMetricsTree* root,  QList<int>* results)
{
	if (root)
	{
		// ���� �� �� � ����� ������
		if (root->Up)
		{
			// ����������� ������� ����
			
            results->replace(0, results->at(0) + 1);

			// ���� ���� ����� ���������, ��������������
			if (root->n->is_inside)
                results->replace(1, results->at(1) + 1);

			// ���� ������� ���� ������� ����������� ������ ����� ������, ������,
			// ��� ����������� �����, ��������� ��������
			root->n->max_deep = CalcHeight(root->Right);
            if (root->n->max_deep > results->at(2))
                results->replace(2, root->n->max_deep);

            results->replace(3, results->at(3) + root->n->length);

			// ��������� ���-�� �������         
             results->replace(4, results->at(4) + root->n->methods);

			if (root->n->has_parent)
                 results->replace(5, results->at(5) + 1);
		}

		// ������� � ��������
		DFS(root->Left, results);
		DFS(root->Right, results);
	}
}
