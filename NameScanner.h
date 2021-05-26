#pragma once
#include "BaseScanner.h"

/*
�����:

  �������                ���      �����������  � ��-���������� ���������������
�������� ����� ��������   1        t
�������������             2        id
{                         3         {
}                         4         }
,                         5         ,
;                         6         ;
*		    			  7	    pointer
��� ���������             8         d
*/

#define TYPE_TYPE 1
#define TYPE_IDENT 2
#define TYPE_OPENED_BRACE 3
#define TYPE_CLOSED_BRACE 4
#define TYPE_COMMA 5
#define TYPE_SEMICOLON 6
#define TYPE_POINTER 7
#define TYPE_OTHER 8
#define TYPE_END 1000

class NameScanner : public BaseScanner
{
public:
	NameScanner();							// ����������� ������
	int Scan(std::string* lex) override;	// ����� ������������ ��� �������
};

