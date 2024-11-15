#include "regex.h"
#include "urlAdvancedParser.h"

std::wstring advancedUrlParser(std::wstring& rawInput)
{
	//������ ��� ������ � �������
	std::wstring buffer = rawInput;

	//��������� ������
	std::vector<std::wstring> garbage;
	std::vector<std::wstring> xpression;

	//0 - ������ �����
	//1 - ������ �������� ��������
	bool firstOrder = 0;

	//��������� �� �������� ������
	uint32_t linkIndex = 0;

	//��������� �� ������ ��������� ������
	uint32_t nameIndex = 0;

	//��������� ����� ��� ���������
	std::wstring _xpression;

	//������ ��������� � ����� ���������
	uint32_t prevIndex = 0;
	uint32_t index = 0;
	uint32_t range = 0;

	//�������������� �������� �� ����� � ��������� ���������� ���������
	//71 ������� ����������!!
	for (std::wsregex_iterator it = std::wsregex_iterator(buffer.cbegin(), buffer.cend(), advRegexHyperlink); it != std::wsregex_iterator(); ++it)
	{
		prevIndex = index + range;										//���������� ���������� ���������
		index = it->position();											//�������� ������ ���������
		range = it->length();											//�������� ����� ���������� ���������
		index == 0 ? firstOrder = 1 : firstOrder = 0;					//���������� ������� ���������� �����������
		garbage.push_back(buffer.substr(prevIndex, index - prevIndex));	//���������� �����(��� �� �� �������)
		xpression.push_back(buffer.substr(index, range));				//���������� ��������� ������� ����� ������������
	}

	//���� ����� ���������� ������������ ��������� ������� ����� �� ��������� ��� ����
	if (index + range < buffer.size())
		garbage.push_back(buffer.substr(index + range, buffer.size() - (index + range)));

	//������������ ��������� ��������� ������� �� � HTML ������
	for (uint16_t iter = 0; iter < xpression.size(); ++iter)
	{
		linkIndex = xpression.at(iter).find(L"(");																//������� ������� ������ ������
		nameIndex = xpression.at(iter).find(L"[");
		_xpression = advUrlWrap.at(0);																			//��������� ����������� ���
		_xpression.append(xpression.at(iter).substr(linkIndex + 1, xpression.at(iter).size() - linkIndex - 2));	//��������� � ��� ������ ������������� �� ����. ��������
		_xpression.append(advUrlWrap.at(1));																	//��������� ������������ ������������ ����
		_xpression.append(xpression.at(iter).substr(nameIndex + 1, linkIndex - nameIndex - 2));					//��������� ������������ ����� ������
		_xpression.append(advUrlWrap.at(2));																	//��������� ����������� ���
		xpression.at(iter) = _xpression;																		//�������� �������� ������������ �������
	}

	//�������������� ����� � ������
	buffer.clear();

	//��������� ���� - ������ ������
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
			if (index < xpression.size())
				buffer += xpression.at(index);
		}
	}

	return buffer;
}
