#include "BaseMetricsTree.h"
#include "string"
#include "list"

// инициализация текущего узла
BaseMetricsTree* BaseMetricsTree::Cur = (BaseMetricsTree*)NULL;

// отладочная печать
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

	// левый потомок
	if (with_value && Left != NULL)
		value = " (" + std::to_string(Left->n->max_deep) + ")";
	else value = "";

	if (Left != NULL) std::cout << Left->n->ident << value;
	else std::cout << " * ";

	std::cout << "\t|\t";

	// правый потомок
	if (with_value && Right != NULL)
		value = " (" + std::to_string(Right->n->max_deep) + ")";
	else 
		value = "";


	if (Right != NULL) std::cout << Right->n->ident << value;
	else std::cout << " * ";

	std::cout << "\n";

	// рекурсивный спуск по дереву

	if (Left != NULL) Left->Print(with_value);
	if (Right != NULL) Right->Print(with_value);

}

// конструктор класса со всеми параметрами
BaseMetricsTree::BaseMetricsTree(BaseMetricsTree* l, BaseMetricsTree* r, BaseMetricsTree* u, Node* Data)
{
	n = new Node();

	// инициализация ссылок и данных
	this->Left = l;
	this->Right = r;
	this->Up = u;
	memcpy(n, Data, sizeof(Node));
}

// конструктор класса для корня дерева
BaseMetricsTree::BaseMetricsTree()
{
	this->n = new Node();
	this->n->ident = "^root";

	// инициализация ссылок
	this->Up = NULL;
	this->Left = NULL;
	this->Right = NULL;
}

// конструктор класса для любого другого узла с указанием идентификатора
BaseMetricsTree::BaseMetricsTree(std::string ident)
{
	this->n = new Node();
	this->n->ident = ident;

	// инициализация ссылок
	this->Up = NULL;
	this->Left = NULL;
	this->Right = NULL;
}

// получить последнего соседа слева для текущего узла
BaseMetricsTree* BaseMetricsTree::GetLastNeighbor()
{
	if (this == NULL)
		return NULL;

	BaseMetricsTree* i = this;

	// поиск "влево" по связям
	while ((i->Left != NULL) )
		i = i->Left;

	// вернуть ссылку на результат
	return i;
}

// задать переданный узел, как дочерний узел справа для текущей вершины
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

// задать переданный узел, как сосед слева для текущей вершины
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

// получить ссылку на родильский узел от текущего
BaseMetricsTree* BaseMetricsTree::GetUp()
{
	return this->Up;
}

// вернуть ссылку на данные в узле
Node* BaseMetricsTree::GetData()
{
	return n;
}

// поиск данных от текущей вершины до корня
BaseMetricsTree* BaseMetricsTree::FindUp(std::string ident)
{
	return FindUp(this, ident);
}

// поиск данных от заданной вершины до корня
BaseMetricsTree* BaseMetricsTree::FindUp(BaseMetricsTree* From, std::string ident)
{
	BaseMetricsTree* i = From;
	// поиск "вверх" по связям
	while ((i != NULL) && (i->n->ident != ident))
		i = i->Up;

	// вернуть ссылку на результат
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