#include "BaseScanner.h"
#include <iostream>

// ��������� ������ ��������� ��� ���� ���������

// ���������� �������� ���������
void BaseScanner::SetUk(int new_uk)
{
	this->uk = new_uk;
}

// �������� �������� ���������
int BaseScanner::GetUk()
{
	return this->uk;
}


// ���������� �������, ����, �������� ����� � �����������
void BaseScanner::SkipSymbols()
{

	// ���� ��� �������� ��������, ������� ����������
	while (true)
	{
		// ���������� �������, ��������� � �������� ����� 
        while ((text[uk] == ' ') || (text[uk] == '\n') || (text[uk] == '\r') || (text[uk] == '\t'))
		{
			uk++;
		}

		// ���� ����������� ('/' � '/') ��� ('/' � '*')
		// ��������� ������������ ��� ������������� �����������
		if ((text[uk] == '/' && text[uk + 1] == '/') || (text[uk] == '/' && text[uk + 1] == '*'))
		{
			uk++;

			// ���� ������������ - ���� ����� ������ (�����������)
			if (text[uk] == '/')
			{
				uk++;
				while ((text[uk] != '\n') && (text[uk] != '\0')) uk++;
				continue;
			}

			// ���� �������������, � ����������� ����� ���� ����� �����������
			else if (text[uk] == '*')
			{
				uk++;

				while (true)
				{
					// ���������� �������, ������� ����� ������ �����������
					while ((text[uk] != '*') && (text[uk] != '\0'))
					{
						uk++;
					}

					// ����� �� ����� - ���������� �� ��� ������
					if (text[uk] == '\0')
					{
						uk--;
						break;
					}

					uk++;
					// ���� ����������� �� ������� - ���������� ��� �������
					if (text[uk] != '/')
					{
						uk++;
						continue;
					}

					break;
				}
				uk++;
				continue;
			}

		}
		else if (text[uk] == '#')
		{
			uk++;
			while ((text[uk] != '\n') && (text[uk] != '\0')) uk++;
			continue;
		}

		// ������� �� �����
		break;
	}

}

// �������� �� ����������������� ����� ��
bool BaseScanner::IsReservedWord(std::string lex)
{
	for (std::string word : reservedwords)
	{
		if (word == lex)
			return true;
	}

	return false;
}

// ���������� ����� ��������� ��� ��������
void BaseScanner::SetText(std::string text)
{
	this->text = text;
	this->uk = 0;
}
