#include "symbolCleaner.h"
#include "regex.h"
#include <map>

std::wstring symbolCleaner(std::wstring& rawInput)
{
	//������� ������, � ������� ����� ������� �����������
	std::wstring buffer = rawInput;

	//������� ������ � ������� ����� �������� ���������
	std::wstring regBuffer(buffer);

	//��������� �����������, ���� ���������� ������ ���������� ����������
	std::wstring symbol;

	//��������� ���������� ��������� ������
	std::wsmatch wstrMatch;

	//��������� �� ������ ������� �� ���������� ������
	uint8_t replaceIndex = 0;

	//��������� �� ���������� ���������
	uint32_t prevIndex = 0;

	//������, �� �������� ����� ����� ���������� ������ �������
	//std::wstring marker(L"\u009C");
	std::wstring marker(L"Z");

	//������ �������� ����������� �����������
	uint32_t symbolDuplicate = 0;

	//������ ������� ���������� ������������
	std::map<int, int> symbolIndexes;

	//0 - ������ �����
	//1 - ������ �������� ��������
	bool firstOrder = 0;

	std::wstring temp;

	//��������� ������
	std::vector<std::wstring> garbage;
	std::vector<std::wstring> xpression;

	//�������� ������ �� "��������" ��������� � �����
	//�������� ��������� - ��������� �������� �������� - ��������� �� �������� �� ������ �����
	//����� - �������� �� ��������� ��������
	for (uint32_t index = 0; index < buffer.size(); ++index)
	{
		//����������� ����������� ��������� ����-�����(��������-�����)
		regBuffer = buffer.substr(index, buffer.size() - index);
		if (std::regex_search(regBuffer, wstrMatch, regexHyperlink))
		{
			if (index == wstrMatch.position() + index)
			{
				index == 0 ? firstOrder = 1 : firstOrder = 0;
				garbage.push_back(buffer.substr(prevIndex, index - prevIndex));
				xpression.push_back(buffer.substr(index, wstrMatch.length()));
				index += wstrMatch.length();
				prevIndex = index;
			}
		}
		if (std::regex_search(regBuffer, wstrMatch, simplifiedRegexHyperlink))
		{
			if (index == wstrMatch.position() + index)
			{
				index == 0 ? firstOrder = 1 : firstOrder = 0;
				garbage.push_back(buffer.substr(prevIndex, index - prevIndex));
				xpression.push_back(buffer.substr(index, wstrMatch.length()));
				index += wstrMatch.length();
				prevIndex = index;
			}
		}
		if (std::regex_search(regBuffer, wstrMatch, advRegexHyperlink))
		{
			if (index == wstrMatch.position() + index)
			{
				index == 0 ? firstOrder = 1 : firstOrder = 0;
				garbage.push_back(buffer.substr(prevIndex, index - prevIndex));
				xpression.push_back(buffer.substr(index, wstrMatch.length()));
				index += wstrMatch.length();
				prevIndex = index;
			}
		}
	}

	for (uint32_t iters = 0; iters < garbage.size(); ++iters)
	{
		//���������� �� ��������� ������� ��������� ������� ���������
		for (uint32_t index = 0; index < garbage.at(iters).size(); ++index)
		{
			//���� ��������� ������ ������� �� ������� � ���������� �������
			if (!symbol.empty())
				if (garbage.at(iters).at(index) == symbol.at(0))
				{
					symbolIndexes.insert(std::map<int, int>::value_type(symbolDuplicate, replaceIndex));
					temp = garbage.at(iters).substr(symbolDuplicate, 1);
					garbage.at(iters).replace(symbolDuplicate, 1, marker);
					symbolDuplicate = index;
				}

			//���� ����� ����������� ����� ������ �� ������� ��� ������� �� ���� ���������
			//� ������� ������ ������� ������ �������
			if (symbolCollection.find(garbage.at(iters).at(index)) <= symbolCollection.size() && !symbol.empty())
				if (garbage.at(iters).at(index) != symbol.at(0))
					symbol.clear();

			//���� ���������� ������ ��� ������� �� ���������� ���
			if (symbolCollection.find(garbage.at(iters).at(index)) <= symbolCollection.size() && symbol.empty())
			{
				replaceIndex = symbolCollection.find(garbage.at(iters).at(index));
				symbol = symbolCollection.at(replaceIndex);
				symbolDuplicate = index;
			}
		}

		//���� ������� ��������� � ������ � �����(����� ����������� ��������
		for (uint32_t index = 0; index < garbage.at(iters).size(); ++index)
		{
			//��� ������ ������� ������ ���������� - ������� � ������� �� �����
			if (symbolClearanceBack.find(garbage.at(iters).at(index)) <= symbolClearanceBack.size())
			{
				symbolIndexes.insert(std::map<int, int>::value_type(index, symbolClearanceBack.find(garbage.at(iters).at(index))));
				garbage.at(iters).replace(index, 1, marker);
				break;
			}
		}

		//���� ������� ��������� � ����� � ������(����� ����������� ��������)
		for (uint32_t index = garbage.at(iters).size() - 1; index > 0; --index)
		{
			//��� ������ ������� ������ ���������� - ������� � ������� �� �����
			if (symbolClearanceFront.find(garbage.at(iters).at(index)) <= symbolClearanceFront.size())
			{
				symbolIndexes.insert(std::map<int, int>::value_type(index, symbolClearanceFront.find(garbage.at(iters).at(index))));
				garbage.at(iters).replace(index, 1, marker);
				break;
			}
		}

		//�������� ������� �� html ��������� ������������
		for (std::map<int, int>::reverse_iterator it = symbolIndexes.rbegin(); it != symbolIndexes.rend(); ++it)
		{
			//�������� ������ ������� �������������� ���������� �����
			switch (it->second)
			{
				case 0:
				{
					garbage.at(iters).replace(it->first, 1, replaceSymbols[it->second]);
					break;
				}
				case 1:
				{
					garbage.at(iters).replace(it->first, 1, replaceSymbols[it->second]);
					break;
				}
			}
		}

		//������ ������� �������, ������ ����� �������� ����� ��������� ���������
		symbolDuplicate = 0;
		symbolIndexes.clear();
		symbol.clear();	//������� ������ ����� �� ���� ������� ������������ � ����� ��������
	}

	//������ ������ �.� ������ ������ � �� ������ �� �����
	buffer.clear();

	if (firstOrder)	//���� ������� � ��� �������� ������� �� ������ ���
	{
		for (uint32_t index = 0; index < xpression.size(); ++index)
		{
			//��������� ������� �������� �������(�� ��� ������) � ����� �����
			buffer += xpression.at(index);
			buffer += garbage.at(index);
		}
		//���� ������� �������������� �����, �� ���� ���������
		if (xpression.size() < garbage.size())
			buffer += garbage.at(garbage.size());
	}
	else //����� ������� ��� �����
	{
		for (uint32_t index = 0; index < garbage.size(); ++index)
		{
			//��� �������� - ������� ����� � ����� ��������
			buffer += garbage.at(index);
			buffer += xpression.at(index);
		}
		//���� ������� �������������� �������, �� ���������, ���������� ��� � �������
		if (garbage.size() < xpression.size())
			buffer += xpression.at(xpression.size());
	}

	//buffer = buffer;

	return buffer;
}
