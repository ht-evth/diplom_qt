#include "BaseSyntax.h"
#include <iostream>

void BaseSyntax::PrintTree(bool with_value)
{
	std::cout << std::endl << std::endl << "������:" << std::endl;
	root->Print(with_value);
}