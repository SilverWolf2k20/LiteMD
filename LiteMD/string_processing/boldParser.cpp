#include "boldParser.h"
#include <boost/container/string.hpp>
#include "exceptionHandler.h"
#include "logger_backend.h"
extern "C"
{
	#include "global_definitions.h"
}

//boost::container::string* head_lvl_url_output;
std::string* bold_output;

std::string boldParser(std::string& rawInput)
{
	//��� ������ --->
	boost::container::string* log_out = new boost::container::string;

	uint32_t* buffer_size = (uint32_t*)malloc(sizeof(uint32_t));
	*buffer_size = rawInput.size();	//������ ���������� � ����������� ��������

	push_log(std::string("[������]������ ����� " + std::to_string(*buffer_size)));

	bold_output = new std::string;
	//italic_output = new boost::container::string;

	int32_t stroke_start = -1;
	int32_t stroke_end = -1;

	uint32_t bolds = 0;
	//������� ���������

	char* buffer = (char*)calloc(*buffer_size + 1, sizeof(char));
	strcpy(buffer, rawInput.c_str());	//��������, //������ ����� � �������� ��������� ����� � �������� ��� ����

	bold_output->assign(buffer);

	//---> � �� ���� ���� ����������� �� ������� � ������, ������ ����������� ������ �� �����

	//��� � � ������� - ���� ����� ��������
	for (volatile int32_t _index = *buffer_size - 1; _index > 0; --_index)
	{
		//��� ��� ���� ������ ����� ������� ������� �� '**' � ������ � �����
		//�� ����� ����� ������ ����� �� ����� ����
		if (buffer[_index] == '*' && buffer[_index - 1] == '*')
		{
			//����� ��������� �� ����� � ������� �� ���������� �������
			stroke_end = _index - 1;

			//������ ����� ������
			for (volatile int32_t _idx = stroke_end; _idx > 0; --_idx)
			{
				if (buffer[_idx] == '*' && buffer[_idx - 1] == '*')
				{
					//���������� ������ ������
					stroke_start = _idx - 1;

					//������� ������� ��������� ������
					++bolds;

					//������ ���
					push_log(std::string("[italicParser]��������� ���� **...** (" + std::to_string(stroke_start) + "-" + std::to_string(stroke_end) + ")"));

					//��������� �������� �� ����
					bold_output->replace(stroke_end, 2, bold_txt_iclose);
					bold_output->replace(stroke_start, 2, bold_txt_iopen);

					//������������ �� ������ ������� ������� ������������
					_index = stroke_start;

					//������ ����� �������� �� ����� ���� ��� ���� �� ���������
					break;
				}
			}
		}
		//����� ���� ������� ���������� ���������
		stroke_start = -1;
		stroke_end = -1;
	}

	//����� ������ ����� �������� �� �����
	free(buffer);
	free(buffer_size);

	return bold_output->c_str();
}
