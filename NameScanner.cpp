#include "NameScanner.h"
#include <iostream>


NameScanner::NameScanner()
{
	this->uk = 0;
	this->text.clear();
	this->keywords = {
		"char", 
		"int", 
		"unsigned", 
		"short",
		"long",
		"float",
		"double",
		"string",
		"bool",
		"boolean",
		"decimal",
		"const",
		"static",
		"extern",
		"internal",
		"byte",
		"final",
		"auto",
		"var",
		"typedef",
	};

	this->reservedwords = {
	"std",
	"if",
	"else",
	"switch",
	"case",
	"default",
	"while",
	"do",
	"bool",
	"break",
	"continue",
	"for",
	"try",
	"catch",
	"finally",
	"throw",
	"throws",
	"private",
	"protected",
	"public",
	"import",
	"package",
	"class",
	"interface",
	"extends",
	"implements",
	"static",
	"final",
	"void",
	"abstract",
	"native",
	"new",
	"return",
	"this",
	"super",
	"synchronized",
	"volatile",
	"const",
	"goto",
	"instanceof",
	"enum",
	"assert",
	"transient",
	"strictfp",
	"as",
	"checked",
	"delegate",
	"event",
	"explicit",
	"false",
	"true",
	"fixed",
	"in",
	"is",
	"lock",
	"namespace",
	"null",
	"NULL",
	"object",
	"operator",
	"out",
	"override",
	"params",
	"ref",
	"sizeof",
	"struct",
	"virtual",
	};


}


// определение сканера дл€ классов
int NameScanner::Scan(std::string* lex)
{
	lex->clear();	// очистим лексему
	int i = 0;

	SkipSymbols();	// пропускаем пробелы, табы, переносы строк и комментарии

	// если конец модул€
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
		//std::cout << " онец сканнер имЄн!" << std::endl;
		return TYPE_END;
	}

	// иначе проверка на идентификатор
	else if (((text[uk] >= 'a') && (text[uk] <= 'z')) || ((text[uk] >= 'A') && (text[uk] <= 'Z')) || (text[uk] == '_'))
	{
		lex->insert(i++, 1, text[uk++]);

		// запоминаем символы, уместные дл€ идентификаторов
		while (((text[uk] >= '0') && (text[uk] <= '9')) ||
			((text[uk] >= 'a') && (text[uk] <= 'z')) ||
			((text[uk] >= 'A') && (text[uk] <= 'Z')) ||
			(text[uk] == '_'))
			lex->insert(i++, 1, text[uk++]);


		// после того, как считали, проверим на ключевое слово
		for (auto word : this->keywords)
		{
			if (word == *lex)
			{
				//std::cout << *lex << std::endl;
				return TYPE_TYPE;
			}
		}

		// зарезервированное слово - это "что-то другое"
		for (auto word : this->reservedwords)
		{
			if (word == *lex)
			{
				//std::cout << *lex << std::endl;
				return TYPE_OTHER;
			}
		}

		//std::cout << *lex << std::endl;
		return TYPE_IDENT;
	}

	// проверка на спецсимволы
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }
	else if (text[uk] == ',') { lex->insert(i++, 1, text[uk++]); return TYPE_COMMA; }
	else if (text[uk] == ';') { lex->insert(i++, 1, text[uk++]); return TYPE_SEMICOLON; }
	else if (text[uk] == '*') { lex->insert(i++, 1, text[uk++]); return TYPE_POINTER; }

	// если константы строковые (чтобы не возвращало TYPE_IDENT между кавычек)
	else if (text[uk] == '\'') 
	{
		uk++;
		while ((text[uk] != '\'') && (text[uk] != '\0' && (text[uk] != '\n')))
		{
			lex->insert(i++, 1, text[uk++]);
		}

		
		if (text[uk] == '\0' || text[uk] == '\n')
		{
			std::cout << "Ѕыла пропущена одинарна€ кавычка.";
			exit(-1);
		}
		uk++;
		return TYPE_OTHER; 
	}
	// если константы символьные (чтобы не возвращало TYPE_IDENT между кавычек)
	else if (text[uk] == '\"') 
	{ 
		uk++;
		while ((text[uk] != '\"') && (text[uk] != '\0') && (text[uk] != '\n'))
		{
			lex->insert(i++, 1, text[uk++]);
		}
		
		if (text[uk] == '\0' || text[uk] == '\n')
		{
			std::cout << "Ѕыла пропущена двойна€ кавычка.";
			exit(-1);
		}
		uk++;
		return TYPE_OTHER;
	}

	// что-то другое
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "„то-то другое: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
