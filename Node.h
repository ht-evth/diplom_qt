#pragma once
#include <iostream>

struct Node
{
	std::string ident; 			// идентификатор

	// классы / циклы
	bool is_inside = false;		// этот узел вложенный?
	bool has_parent = false;	// этот узел потомок другого класса?
	int max_deep = 0;			// максимальный уровень вложенности
	int length = 0;				// общее количество логических строк

	int amount_chields = 0;		// общее кол-во классов-потомков
	int fields = 0;				// общее количество полей классов
	int methods = 0;			// общее количество методов классов


	int break_return = 0;		// количество операторов break и return в циклах
	int _continue = 0;			// количество операторов continue в циклах

	// для идентификаторов
	int number_of_uses = 0;		// количество использований идентификатора
	bool managment = false;		// количество использований идентификатора
	bool firts_time = false;		// первый раз присвоено значение
	bool second_time = false;		// второй и более раз присвоено значение
};