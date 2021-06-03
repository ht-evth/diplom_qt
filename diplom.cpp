
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>

#include "ClassSyntax.h"
#include "BlockSyntax.h"
#include "NameSyntax.h"
#include "CyclesSyntax.h"

// считываем файл
std::string ReadFile(std::string filename)
{
	std::string text;

	FILE* in;
	errno_t err = fopen_s(&in, filename.c_str(), "r");

	if (err != 0 || in == NULL)
	{
		std::cout << "Не удалось открыть файл" + filename;
		//RequestFilename();
		return NULL;
		//errno_t err = fopen_s(&in, this->filename.c_str(), "r");
	}

	int i = 0;
	char symbol;
	text.clear();

	// считываем файл посимвольно
	while (!feof(in))
	{
		fscanf_s(in, "%c", &symbol);

		// если не конец файла - вставить символ
		if (!feof(in))
			if (symbol != 'п' && symbol != '»' && symbol != 'ї')
				text.insert(i++, 1, symbol);

	}

	fclose(in);
	return text;

}

int main()
{
	// для печати кириллицы
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	
	std::string text = ReadFile("ClassSyntax.cpp");	// открыть и прочитать текст файла
	std::cout << text << std::endl;					// печать текста файла


	// явно создаются синтаксические анализаторы 

	ClassSyntax a(text);
	BlockSyntax b(text);
	CyclesSyntax c(text);
	NameSyntax d(text);


	// запуск анализатора (перед завершением работы анализатора печатаются метрики)

	std::cout << "\n\n\n-----------Метрики классов--------------" << std::endl;					// печать текста файла
	a.Prog();
	std::cout << "\n\n\n------------Метрики блоков--------------" << std::endl;					// печать текста файла
	b.Prog();
	std::cout << "\n\n\n------------Метрики циклов--------------" << std::endl;					// печать текста файла
	c.Prog();
	std::cout << "\n\n\n--------------Метрики имён--------------" << std::endl;					// печать текста файла
	d.Prog();


	// отладочная печать дерева
	//a.PrintTree(); 
	a.PrintTree(true);
	
}





void RequestFilename()
{
	std::cout << "\nУкажите путь до файла: ";
	std::cin >> this->filename;

	std::ifstream file(this->filename);

	while (file.is_open() != true)
	{
		std::cout << "Не удалось открыть файл" + this->filename;
		std::cout << "\nУкажите путь до файла: ";
		std::cin >> this->filename;

		file.open(this->filename);
	}

	file.close();
}

