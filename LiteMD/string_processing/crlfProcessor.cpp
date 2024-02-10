#include "crlfProcessor.h"

std::wstring crlfProcessor(std::wstring& rawInput)
{
	//����� ��� �������� ������ �������
	std::wstring buffer = rawInput;

	//��� �������� ������
	std::wstring brTag(L"<BR>");

	//�������� � �����
	for (uint32_t index = buffer.size() - 1; index > 0; --index)
	{
		if (buffer.at(index) == L'\n')
		{
			buffer.replace(index, 1, brTag);
		}
	}

	//���������� ��������
	return buffer;
}
