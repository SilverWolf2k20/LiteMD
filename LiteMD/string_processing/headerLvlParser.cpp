#include "headerLvlParser.h"
#include <boost/container/string.hpp>
#include "global_definitions.h"
#include "exceptionHandler.h"

//boost::container::string* head_lvl_url_output;
std::string* head_lvl_url_output;

std::string headerLvlParser(std::string& rawInput)
{
	uint32_t* buffer_size = (uint32_t*)malloc(sizeof(uint32_t));
	*buffer_size = rawInput.size();	//������ ���������� � ����������� ��������

	head_lvl_url_output = new std::string;
	//head_lvl_url_output = new boost::container::string;

	int32_t stroke_start = -1;
	int32_t stroke_end = -1;
	uint8_t header_size = 0;

	char* buffer = (char*)calloc(*buffer_size + 1, sizeof(char));
	strcpy(buffer, rawInput.c_str());	//��������, //������ ����� � �������� ��������� ����� � �������� ��� ����

	head_lvl_url_output->assign(buffer);

	for (volatile int32_t _index = *buffer_size; _index >= 0; --_index)
	{
		//���� ������ ������ �������� �� ������� �� ����� ������
		if (buffer[_index] == '\n')
		{
			//����� ��������� ��������� ��������
			for (volatile int32_t _idx = _index; _idx >= 0; --_idx)
			{
				if ((buffer[_idx] != '\r') && (buffer[_idx] != '\n') && (buffer[_idx] != '\0'))
				{
					stroke_end = _idx;
					break;
				}
			}
			//�������� ������ ������ ������
			for (volatile int32_t _idx = stroke_end; _idx >= 0; --_idx)
			{
				if ((buffer[_idx] == '\n') || (_idx == 0))
				{
					//���� ������� ������ ��� ������� ����� �� ���� �� ���������
					(buffer[_idx] == '\n') ? stroke_start = _idx + 1 : stroke_start = 0;
					break;
				}
			}

			//��������� ������ 5 ��������, ���� �������� ������� �� ������� ��� ��� ���� �� �����������
			//���������� �������� �� ������ ���� ��� 0
			for (volatile int32_t _idx = stroke_start; _idx < stroke_start + 5; ++_idx)
			{
				if (buffer[_idx] == '#')
					++header_size;
				else
					break;
			}

			//���� ������� �� ������� �� ��������� ��� ������ �� �������� �������� ���������
			//������ ������ ����������� ��� ������ ����� � ���� ��� ������
			if ((header_size == 0) && (_index > 0))
				_index = stroke_start - 1;
			else
			{	//�������� ��������� �� ������ header_size;
				switch (header_size)
				{
					case 1:
					{
						//������� ���� � �����
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_end + 1, "1");
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_iclosetext);
						//������� ���� � ������
						//head_lvl_url_output->insert(stroke_start, header_lvl_icloselvl);
						head_lvl_url_output->replace(stroke_start, 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_start, "1");
						//head_lvl_url_output->replace(stroke_start, 1, header_lvl_iopenlvl);
						head_lvl_url_output->insert(stroke_start, header_lvl_iopenlvl);
						break;
					}
					case 2:
					{
						//������� ���� � �����
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_end + 1, "2");
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_iclosetext);
						//������� ���� � ������
						//head_lvl_url_output->insert(stroke_start, header_lvl_icloselvl);
						head_lvl_url_output->replace(stroke_start, 2, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_start, "2");
						//head_lvl_url_output->replace(stroke_start, 2, header_lvl_iopenlvl);
						head_lvl_url_output->insert(stroke_start, header_lvl_iopenlvl);
						break;
					}
					case 3:
					{
						//������� ���� � �����
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_end + 1, "3");
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_iclosetext);
						//������� ���� � ������
						//head_lvl_url_output->insert(stroke_start, header_lvl_icloselvl);
						head_lvl_url_output->replace(stroke_start, 3, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_start, "3");
						//head_lvl_url_output->replace(stroke_start, 3, header_lvl_iopenlvl);
						head_lvl_url_output->insert(stroke_start, header_lvl_iopenlvl);
						break;
					}
					case 4:
					{
						//������� ���� � �����
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_end + 1, "4");
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_iclosetext);
						//������� ���� � ������
						//head_lvl_url_output->insert(stroke_start, header_lvl_icloselvl);
						head_lvl_url_output->replace(stroke_start, 4, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_start, "4");
						//head_lvl_url_output->replace(stroke_start, 4, header_lvl_iopenlvl);
						head_lvl_url_output->insert(stroke_start, header_lvl_iopenlvl);
						break;
					}
					case 5:
					{
						//������� ���� � �����
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_end + 1, "5");
						head_lvl_url_output->insert(stroke_end + 1, header_lvl_iclosetext);
						//������� ���� � ������
						//head_lvl_url_output->insert(stroke_start, header_lvl_icloselvl);
						head_lvl_url_output->replace(stroke_start, 5, header_lvl_icloselvl);
						head_lvl_url_output->insert(stroke_start, "5");
						//head_lvl_url_output->replace(stroke_start, 5, header_lvl_iopenlvl);
						head_lvl_url_output->insert(stroke_start, header_lvl_iopenlvl);
						break;
					}
				}
			}
			//����� ��� ������ �� ��������� �������
			header_size = 0;
			//����������� ��������� �� ������� ������ � ������� ��� ������
			_index = stroke_start;
			//����� �������� ��� ��� ����� ������� � ���� ������ �� �������
			stroke_start = -1;
			stroke_end = 1;
		}
	}

	free(buffer_size);
	free(buffer);

	return head_lvl_url_output->c_str();
}
