#include "regex.h";
#include "urlBasicParser.h"
#include <map>

std::wstring basicUrlParser(std::wstring& rawInput)
{
	//������ ��� ������ � �������
	std::wstring buffer = rawInput;

	//��������� ����������
	std::wstring _garbage;
	std::wstring _xpressions;

	//����� ��� �������� ���������� ������ � ���������
	std::map<int, std::wstring> garbageMap;
	std::map<int, std::wstring> xpressionsMap;

	//������ ��������� � ����� ���������
	int index = 0;
	int range = 0;

	for (std::wsregex_iterator it = std::wsregex_iterator(buffer.cbegin(), buffer.cend(), regexHyperlink); it != std::wsregex_iterator(); ++it)
	{
		range = it->position();
	}

	return buffer;
}
