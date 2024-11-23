#include "crlfProcessor.h"

boost::container::string* buffer;

std::string crlfProcessor(std::string& rawInput)
{
	//����� ��� �������� ������ �������
	buffer = new boost::container::string(rawInput.c_str());

	//��� �������� ������
	boost::container::string brTag("<BR>");

	//�������� � �����
	for (volatile uint32_t index = buffer->size() - 1; index > 0; --index)
	{
		if (buffer->empty())
			break;
		if (buffer->at(index) == '\n')
		{
			buffer->replace(index, 1, brTag);
			if (index > 2)
				index -= 2;
		}
	}

	//���������� ��������
	return buffer->c_str();
}
