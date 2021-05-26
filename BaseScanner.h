#pragma once
#include <string>
#include <list>

class BaseScanner 
{
protected:
	std::string text;										// ����� ���������
	int uk;													// �������� ��������� � ������ ���������
	std::list<std::string> keywords;						// ������ �������� ���� � �� �������
	std::list<std::string> reservedwords;					// ������ ����������������� ����

public:
	// ������, ������� ��������� ��� ���� ���������:
	void SkipSymbols();							// ���������� �������, ����, �������� ����� � ����������� � �.�.
	bool IsReservedWord(std::string lex);		// �������� �� ����������������� ����� ��
	void SetUk(int new_uk);						// ���������� �������� ��������� � ������
	int GetUk();								// �������� �������� ��������� � ������
	void SetText(std::string text);				// ���������� ����� ��� �������

	// ������, ������� ����� �������������� ��� ������� �������
    virtual int Scan(std::string* lex) = 0;		// ����� ������������ ��������� �������
};


