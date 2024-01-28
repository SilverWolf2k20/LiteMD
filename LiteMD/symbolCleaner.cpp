#include "symbolCleaner.h"
#include "regex.h"
#include <map>

std::wstring symbolCleaner(std::wstring& rawInput)
{
	//������� ������, � ������� ����� ������� �����������
	std::wstring buffer = rawInput;

	//��������� �����������, ���� ���������� ������ ���������� ����������
	std::wstring symbol;

	//��������� �� ������ ������� �� ���������� ������
	uint8_t replaceIndex = 0;

	//������, �� �������� ����� ����� ���������� ������ �������
	std::wstring marker(L"\u009C");

	//������ �������� ����������� �����������
	uint32_t symbolDuplicate = 0;

	//������ ������� ���������� ������������
	std::map<int, int> symbolIndexes;

	//������� �� �������� ������������
	for (uint32_t index = 0; index < buffer.size(); ++index)
	{
		//���� ��������� ������ ������� �� ������� � ���������� �������
		if(!symbol.empty())
			if (buffer.at(index) == symbol.at(0))
			{
				symbolIndexes.insert(std::map<int, int>::value_type(symbolDuplicate,replaceIndex));
				buffer.replace(symbolDuplicate, 1, marker);
				symbolDuplicate = index;
			}

		//���� ����� ����������� ����� ������ �� ������� ��� ������� �� ���� ���������
		//� ������� ������ ������� ������ �������
		if (symbolCollection.find(buffer.at(index)) <= symbolCollection.size() && !symbol.empty())
			if (buffer.at(index) != symbol.at(0))
				symbol.clear();

		//���� ���������� ������ ��� ������� �� ���������� ���
		if (symbolCollection.find(buffer.at(index)) <= symbolCollection.size() && symbol.empty())
		{
			replaceIndex = symbolCollection.find(buffer.at(index));
			symbol = symbolCollection.at(replaceIndex);
			symbolDuplicate = index;
		}
	}

	//������� �� ����������� ������������
	for (uint32_t index = 0; index < buffer.size(); ++index)
	{
		//��� ������ ������� ������ ���������� - ������� � ������� �� �����
		if (symbolClearance.find(buffer.at(index)) <= symbolClearance.size())
		{
			symbolIndexes.insert(std::map<int, int>::value_type(index, symbolClearance.find(buffer.at(index))));
			buffer.replace(index, 1, marker);
			break;
		}
	}

	//�������� ������ � ������������� �����������
	for (std::map<int, int>::reverse_iterator it = symbolIndexes.rbegin(); it != symbolIndexes.rend(); ++it)
	{
		//�������� ������ ������� �������������� ���������� �����
		switch (it->second)
		{
			case 0:
			{
				buffer.replace(it->first, 1, replaceSymbols[it->second]);
				break;
			}
			case 1:
			{
				buffer.replace(it->first, 1, replaceSymbols[it->second]);
				break;
			}
		}
	}

	return buffer;
}
