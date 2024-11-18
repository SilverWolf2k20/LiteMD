#include <boost/container/string.hpp>
#include "urlAdvancedParser.h"
#include "global_definitions.h"

boost::container::string* format_url_output;

std::string advancedUrlParser(std::string& rawInput)
{
	//�������� ��� ������� �������� ����
	uint32_t squ_brackets_entry = 0;
	uint32_t squ_brackets_offset = 0;
	uint32_t brackets_entry = 0;
	uint32_t brackets_offset = 0;

	format_url_output = new boost::container::string;	//�������� ����� ������� ������� STD�����

	uint32_t* buffer_size = (uint32_t*)malloc(sizeof(uint32_t));
	*buffer_size = rawInput.size();	//������ ���������� � ����������� ��������

	char* buffer = (char*)malloc(*buffer_size);
	strcpy(buffer, rawInput.c_str());	//��������, //������ ����� � �������� ��������� ����� � �������� ��� ����

	uint32_t* squ_entry_list;	//'['
	uint32_t* squ_offsets;		//']'
	uint32_t* entry_list;		//'('
	uint32_t* offsets;			//')'

	squ_entry_list = (uint32_t*)malloc(sizeof(uint32_t));
	squ_offsets = (uint32_t*)malloc(sizeof(uint32_t));
	entry_list = (uint32_t*)malloc(sizeof(uint32_t));
	offsets = (uint32_t*)malloc(sizeof(uint32_t));
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^��������� � �����

	//������ ����� ����� ��������� ����, ���� ��� ����� ������� ��� �������� ����
	//� ������� ���, ����� ����� �������� ��������� <url> ��� url - ����� ����� ������
	//������� ����� ������ �� ������ ������� ��� ��� �� �����
	//�������� https://www.markdownguide.org/basic-syntax/#formatting-links

	//���� ��������� �� ����� '<'
	for (volatile uint32_t _index = 0; _index < *buffer_size; ++_index)
	{
		if (buffer[_index] == '[')	//����� �������� ��������� ���������� �� �������
		{
			++squ_brackets_entry;	//realloc ��������� ������ + 1 ����� �� �������� �� �������
			squ_entry_list = (uint32_t*)realloc(squ_entry_list, sizeof(uint32_t) * (squ_brackets_entry + 1));
			squ_entry_list[squ_brackets_entry - 1] = _index + 1;
		}
	}

	//���� �����������, ��� ���� ������� �������� ���, ����� �� �������
	//������ � ������ ����������� �������������� ��������� ������ �������
	//���������� ������� � ������
	squ_entry_list = (uint32_t*)realloc(squ_entry_list, sizeof(uint32_t) * (squ_brackets_entry + 1));
	squ_entry_list[squ_brackets_entry] = *buffer_size + 1;	//������� � ������ ���������� �������

	if (entry_list[0] != 0)	//���� ������ ��������� �� �������� ������� ����� �� �������� 0 ��� ��������
	{
		++squ_brackets_offset;
		squ_offsets = (uint32_t*)realloc(squ_offsets, sizeof(uint32_t) * (squ_brackets_offset + 1) + sizeof(uint32_t));
		squ_offsets[squ_brackets_offset - 1] = 0;
	}

	//���� ����������� ����� ']' �� ������� ���������
	for (volatile uint32_t _entry_idx = 0; _entry_idx < squ_brackets_entry; ++_entry_idx)
	{
		//��������� ��������� ����������� ���������. ��� ��������� � ��������������
		//��������� �� ���� � ��� �� ����, ����� ����� ����������� � ���� ��� ��� ���������
		//����������� ������ '['
		for (uint32_t _index = squ_entry_list[_entry_idx]; _index < squ_entry_list[_entry_idx + 1]; ++_index)
		{
			if (buffer[_index] == ']')
			{
				++squ_brackets_offset;
				squ_offsets = (uint32_t*)realloc(squ_offsets, sizeof(uint32_t) * (squ_brackets_offset + 1));
				squ_offsets[squ_brackets_offset - 1] = _index;
			}
		}
	}

	//�� �� ����
	squ_offsets = (uint32_t*)realloc(squ_offsets, sizeof(uint32_t) * (squ_brackets_offset + 1));
	squ_offsets[squ_brackets_offset] = *buffer_size + 1;	//������� � ������ ���������� �������

	volatile uint32_t _entry_idx = 0;

	if (entry_list[0] != 0)	//������ ���� ��������, ��� ����� ������ � ����������� +1 � ������� �������� �������
		_entry_idx = 1;

	//���� ����������� ����� '(' �� ������� ���������
	for (; _entry_idx < squ_brackets_offset; ++_entry_idx)
	{
		//��������� ��������� ����������� ���������. ��� ��������� � ��������������
		//��������� �� ���� � ��� �� ����, ����� ����� ����������� � ���� ��� ��� ���������
		//����������� ������ ']'
		for (uint32_t _index = squ_offsets[_entry_idx]; _index < squ_offsets[_entry_idx + 1]; ++_index)
		{
			if (buffer[_index] == '(')
			{
				++brackets_entry;
				entry_list = (uint32_t*)realloc(entry_list, sizeof(uint32_t) * (brackets_entry + 1));
				entry_list[brackets_entry - 1] = _index + 1;
			}
		}
	}

	//�� �� ���� ������ � ������ �����
	entry_list = (uint32_t*)realloc(entry_list, sizeof(uint32_t) * (squ_brackets_entry + 1));
	entry_list[squ_brackets_entry] = *buffer_size + 1;	//������� � ������ ���������� �������

	//���� ����������� ����� ')' �� ������� ���������
	for (volatile uint32_t _entry_idx = 0; _entry_idx < squ_brackets_entry; ++_entry_idx)
	{
		//��������� ��������� ����������� ���������. ��� ��������� � ��������������
		//��������� �� ���� � ��� �� ����, ����� ����� ����������� � ���� ��� ��� ���������
		//����������� ������ '('
		for (uint32_t _index = entry_list[_entry_idx]; _index < entry_list[_entry_idx + 1]; ++_index)
		{
			if (buffer[_index] == ')')
			{
				++brackets_offset;
				offsets = (uint32_t*)realloc(offsets, sizeof(uint32_t) * (brackets_offset + 1));
				offsets[brackets_offset - 1] = _index;
			}
		}
	}

	//���� ����������� � ������ ������. ������ �������� '<' � '>' ����������� '<a href="'+�����+'">'+�����+'</a>'

	uint32_t entrys_cnt = 0;
	uint32_t blocks_cnt = 0;

	if (entry_list[entrys_cnt] == 0)	//���� ��� ���������� � ������� ������� �� ��������� ������� � +1 entrys_cnt
	{									//� ��������� ������ �� �����
		//������
		for (volatile uint32_t _part_idx = entrys_cnt; _part_idx < squ_brackets_entry;)
		{
			//������ � ����i
			for (volatile uint32_t _part_idx = 0; _part_idx < squ_brackets_entry; ++_part_idx)
			{
				++entrys_cnt;
				//������� ���� <a href="
				format_url_output->append(simple_url_iopenurl, simple_url_iopenurl_size);
				//������� ������-������
				format_url_output->append(&buffer[entry_list[entrys_cnt - 1]], offsets[entrys_cnt - 1] - entry_list[entrys_cnt - 1]);
				//������� ������������ ������ ">
				format_url_output->append(simple_url_icloseurl, simple_url_icloseurl_size);
				//������� ������������� ������
				format_url_output->append(&buffer[squ_entry_list[entrys_cnt - 1]], squ_offsets[entrys_cnt] - squ_entry_list[entrys_cnt - 1]);
				//������� ������������ ����
				format_url_output->append(simple_url_iclosetext, simple_url_iclosetext_size);
				//������� ������ ����� ������
				format_url_output->append(&buffer[offsets[entrys_cnt - 1]] + 1, squ_entry_list[entrys_cnt] - offsets[entrys_cnt - 1] - 2);
			}
		}
	}
	else
	{

		//����������� ������ �� ����
		format_url_output->append(&buffer[squ_offsets[entrys_cnt]], squ_entry_list[entrys_cnt] - 1);

		//������ � ����i
		for (volatile uint32_t _part_idx = 0; _part_idx < squ_brackets_entry; ++_part_idx)
		{
			++entrys_cnt;
			//������� ���� <a href="
			format_url_output->append(simple_url_iopenurl, simple_url_iopenurl_size);
			//������� ������-������
			format_url_output->append(&buffer[entry_list[entrys_cnt - 1]], offsets[entrys_cnt - 1] - entry_list[entrys_cnt - 1]);
			//������� ������������ ������ ">
			format_url_output->append(simple_url_icloseurl, simple_url_icloseurl_size);
			//������� ������������� ������
			format_url_output->append(&buffer[squ_entry_list[entrys_cnt - 1]], squ_offsets[entrys_cnt] - squ_entry_list[entrys_cnt - 1]);
			//������� ������������ ����
			format_url_output->append(simple_url_iclosetext, simple_url_iclosetext_size);
			//������� ������ ����� ������
			format_url_output->append(&buffer[offsets[entrys_cnt - 1]] + 1, squ_entry_list[entrys_cnt] - offsets[entrys_cnt - 1] - 2);
		}
	}

	//������ ����������
	free(squ_entry_list);
	free(squ_offsets);
	free(entry_list);
	free(offsets);

	return format_url_output->c_str();
}
