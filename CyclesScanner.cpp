#include "CyclesScanner.h"
#include <iostream>
#include <QMessageBox>

CyclesScanner::CyclesScanner()
{

	this->uk = 0;
	this->text.clear();
	this->keywords = {};
}


// ����������� ������� ��� ������
int CyclesScanner::Scan(std::string* lex)
{
	lex->clear();	// ������� �������
	int i = 0;

	SkipSymbols();	// ���������� �������, ����, �������� ����� � �����������

	// ���� ����� ������
	if (text[uk] == '\0')
	{
		lex[0] = '\0';
        //std::cout << "�����!" << std::endl;
		return TYPE_END;
	}

	// ����� �������� �� �������������
	else if (((text[uk] >= 'a') && (text[uk] <= 'z')) || ((text[uk] >= 'A') && (text[uk] <= 'Z')) || (text[uk] == '_'))
	{
		lex->insert(i++, 1, text[uk++]);

		// ���������� �������, �������� ��� ���������������
		while (((text[uk] >= '0') && (text[uk] <= '9')) ||
			((text[uk] >= 'a') && (text[uk] <= 'z')) ||
			((text[uk] >= 'A') && (text[uk] <= 'Z')) ||
			(text[uk] == '_'))
			lex->insert(i++, 1, text[uk++]);


		// ����� ����, ��� �������, �������� �� �������� �����
		//std::cout << *lex << std::endl;

		if (*lex == "for")
			return TYPE_FOR;
		
		else if (*lex == "do")
			return TYPE_DO;
		
		else if (*lex == "while")
			return TYPE_WHILE;


		return TYPE_OTHER;
	}

	// �������� �� �����������
	else if (text[uk] == '{') { lex->insert(i++, 1, text[uk++]); return TYPE_OPENED_BRACE; }
	else if (text[uk] == '}') { lex->insert(i++, 1, text[uk++]); return TYPE_CLOSED_BRACE; }
    // ���� ��������� ��������� (����� �� ���������� TYPE_IDENT ����� �������)
    else if (text[uk] == '\'')
    {
        uk++;
        while ((text[uk] != '\'') && (text[uk] != '\0' && (text[uk] != '\n')))
        {
            lex->insert(i++, 1, text[uk++]);
        }


        if (text[uk] == '\0' || text[uk] == '\n')
        {
            //std::cout << "���� ��������� ��������� �������.";
            QMessageBox* pmbx =
                                new QMessageBox("����������� ������!",
                                "���� ��������� ��������� �������. �������������� ������",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            delete pmbx;
            exit(-1);
        }
        uk++;
        return TYPE_OTHER;
    }
    // ���� ��������� ���������� (����� �� ���������� TYPE_IDENT ����� �������)
    else if (text[uk] == '\"')
    {
        uk++;
        while ((text[uk] != '\"') && (text[uk] != '\0') && (text[uk] != '\n'))
        {
            lex->insert(i++, 1, text[uk++]);
        }

        if (text[uk] == '\0' || text[uk] == '\n')
        {
            QMessageBox* pmbx =
                                new QMessageBox("����������� ������!",
                                "���� ��������� ������� �������. �������������� ������",
                                QMessageBox::Critical,
                                QMessageBox::Ok,
                                0,
                                0);
            pmbx->exec();
            delete pmbx;
            //std::cout << "���� ��������� ������� �������.";
            exit(-1);
        }
        uk++;
        return TYPE_OTHER;
    }

	// ���-�� ������
	else
	{
		lex->insert(i++, 1, text[uk++]);
		//std::cout << "���-�� ������: " << *lex << std::endl;
		return TYPE_OTHER;
	}

}
