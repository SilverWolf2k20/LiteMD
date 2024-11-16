#include "shieldingParser.h"

std::wstring shieldingParser(std::wstring& rawInput)
{
	//������� ������ � ������� ����� ��������� ���������
	std::wstring buffer = rawInput;

	//������ ������� ����� ����������� ������
	std::wstring replaceSymbol;

	//������-�������� �������������
	std::wstring shieldDetector(L"\\");

	//���� �����������, ������� �������� ������ �������������
	for (uint32_t index = buffer.size() - 1; index > 0; --index)
	{
		if (buffer.empty())
			break;
		//���� ������� �� ������ ������ � �����, ������� ����� �� � ����������
		//����� ���������� ���������� � ������ � ��������� ������� � �����
		if (buffer.at(index) == L'\\')
		{
			replaceSymbol = buffer.at(index + 1);
			replaceSymbol = shieldingSymbols.at(shieldingSymbolsSrc.find(replaceSymbol));
			buffer.replace(index, 2, replaceSymbol);
		}
	}

	//���������� ������ � ������
	return buffer;
}
