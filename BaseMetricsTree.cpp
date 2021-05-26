#include "BaseMetricsTree.h"
#include "string"
#include "list"

// ������������� �������� ����
BaseMetricsTree* BaseMetricsTree::Cur = (BaseMetricsTree*)NULL;

// ���������� ������
void BaseMetricsTree::Print(bool with_value)
{
	std::string value = "";
	if (with_value)
		value = " (" + std::to_string(n->max_deep) + ")";



	if (n->ident == "")
		std::cout << " * ";
	else
		std::cout << n->ident << value;

	std::cout << "\t---->\t";

	// ����� �������
	if (with_value && Left != NULL)
		value = " (" + std::to_string(Left->n->max_deep) + ")";
	else value = "";

	if (Left != NULL) std::cout << Left->n->ident << value;
	else std::cout << " * ";

	std::cout << "\t|\t";

	// ������ �������
	if (with_value && Right != NULL)
		value = " (" + std::to_string(Right->n->max_deep) + ")";
	else 
		value = "";


	if (Right != NULL) std::cout << Right->n->ident << value;
	else std::cout << " * ";

	std::cout << "\n";

	// ����������� ����� �� ������

	if (Left != NULL) Left->Print(with_value);
	if (Right != NULL) Right->Print(with_value);

}

// ����������� ������ �� ����� �����������
BaseMetricsTree::BaseMetricsTree(BaseMetricsTree* l, BaseMetricsTree* r, BaseMetricsTree* u, Node* Data)
{
	n = new Node();

	// ������������� ������ � ������
	this->Left = l;
	this->Right = r;
	this->Up = u;
	memcpy(n, Data, sizeof(Node));
}

// ����������� ������ ��� ����� ������
BaseMetricsTree::BaseMetricsTree()
{
	this->n = new Node();
	this->n->ident = "^root";

	// ������������� ������
	this->Up = NULL;
	this->Left = NULL;
	this->Right = NULL;
}

// ����������� ������ ��� ������ ������� ���� � ��������� ��������������
BaseMetricsTree::BaseMetricsTree(std::string ident)
{
	this->n = new Node();
	this->n->ident = ident;

	// ������������� ������
	this->Up = NULL;
	this->Left = NULL;
	this->Right = NULL;
}

// �������� ���������� ������ ����� ��� �������� ����
BaseMetricsTree* BaseMetricsTree::GetLastNeighbor()
{
	if (this == NULL)
		return NULL;

	BaseMetricsTree* i = this;

	// ����� "�����" �� ������
	while ((i->Left != NULL) )
		i = i->Left;

	// ������� ������ �� ���������
	return i;
}

// ������ ���������� ����, ��� �������� ���� ������ ��� ������� �������
void BaseMetricsTree::AddChieldForThisNode(BaseMetricsTree* chield)
{

	if (this->n->ident == "^root")
	{
		auto lastNeighbor = GetLastNeighbor();
		chield->Up = lastNeighbor;
		lastNeighbor->Left = chield;
	}
	else
	{
		auto lastChield = Right->GetLastNeighbor();
		if (lastChield != NULL)
		{
			chield->Up = lastChield;
			lastChield->Left = chield;
		}
		else
		{
			chield->Up = this;
			this->Right = chield;
		}
	}
	
}

// ������ ���������� ����, ��� ����� ����� ��� ������� �������
BaseMetricsTree* BaseMetricsTree::AddNeighborForThisNode(BaseMetricsTree* neighbor)
{
	auto last = GetLastNeighbor();

	if (last != NULL)
	{
		neighbor->Up = last;
		last->Left = neighbor;
	}
	else
	{
		neighbor->Up = this;
		this->Left = neighbor;
	}

	return neighbor;
}

// �������� ������ �� ���������� ���� �� ��������
BaseMetricsTree* BaseMetricsTree::GetUp()
{
	return this->Up;
}

// ������� ������ �� ������ � ����
Node* BaseMetricsTree::GetData()
{
	return n;
}

// ����� ������ �� ������� ������� �� �����
BaseMetricsTree* BaseMetricsTree::FindUp(std::string ident)
{
	return FindUp(this, ident);
}

// ����� ������ �� �������� ������� �� �����
BaseMetricsTree* BaseMetricsTree::FindUp(BaseMetricsTree* From, std::string ident)
{
	BaseMetricsTree* i = From;
	// ����� "�����" �� ������
	while ((i != NULL) && (i->n->ident != ident))
		i = i->Up;

	// ������� ������ �� ���������
	return i;
}


int max(int a, int b)
{
	return ((a) > (b) ? (a) : (b));
}

int BaseMetricsTree::CalcHeight(BaseMetricsTree* root)
{
	if (root == NULL)
		return 0;

	int neighbor = 0;
	int cur = 0;
	cur = CalcHeight(root->Right);

	BaseMetricsTree* temp = root;
	while (temp->Left != NULL)
	{
		neighbor = max(neighbor, temp->CalcHeight(temp->Left->Right));
		temp = temp->Left;
	}
	

	cur = max(cur, neighbor);

	return cur + 1;
}
