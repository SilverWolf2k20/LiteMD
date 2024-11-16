#include <boost/container/string.hpp>
#include "urlBasicParser.h"
#include "global_definitions.h"

struct entry_pointer_list
{
	uint32_t str_entry_first;
	uint32_t str_entry_second;
	uint32_t buffer_shift;
}entry_ptr;

char* piece;
boost::container::string *output;

std::string basicUrlParser(std::string &rawInput)
{
	uint32_t* entry_list;	//������ � ���������, � ������� ���������� ������������ �������
	uint32_t* entry_offset;	//������ �� ��������� �� ������������ �����
	uint32_t entrys = 0;
	uint32_t offsets = 0;
	
	output = new boost::container::string;

	uint32_t* buffer_size = (uint32_t*)malloc(sizeof(uint32_t));
	*buffer_size = rawInput.size();	//������ ���������� � ����������� ��������

	char* buffer = (char*)malloc(*buffer_size);
	strcpy(buffer, rawInput.c_str());	//��������, //������ ����� � �������� ��������� ����� � �������� ��� ����

	entry_list = (uint32_t*)malloc(sizeof(uint32_t));
	entry_offset = (uint32_t*)malloc(sizeof(uint32_t));

	//������ ����� ����� ��������� ����, ���� ��� ����� ������� ��� �������� ����
	//� ������� ���, ����� ����� �������� ��������� <url> ��� url - ����� ����� ������
	//������� ����� ������ �� ������ ������� ��� ��� �� �����
	//�������� https://www.markdownguide.org/basic-syntax/#urls-and-email-addresses

	//���� ��������� �� ����� '<'
	for (volatile uint32_t _index = 0; _index < *buffer_size; ++_index)
	{
		if (buffer[_index] == '<')	//����� �������� ��������� ���������� �� �������
		{
			++entrys;
			entry_list = (uint32_t*)realloc(entry_list, sizeof(uint32_t) * entrys);
			entry_list[entrys - 1] = _index + 1;
		}
	}

	//���� �����������, ��� ���� ������� �������� ���, ����� �� �������
	//������ � ������ ����������� �������������� ��������� ������ �������
	//���������� ������� � ������
	entry_list = (uint32_t*)realloc(entry_list, sizeof(uint32_t) * entrys+1);
	entry_list[entrys] = *buffer_size + 1;	//������� � ������ ���������� �������

	if (entry_list[0] != 0)	//���� ������ ��������� �� �������� ������� ����� �� �������� 0 ��� ��������
	{
		++offsets;
		entry_offset = (uint32_t*)realloc(entry_offset, sizeof(uint32_t) * offsets);
		entry_offset[offsets - 1] = 0;
	}

	//���� ����������� ����� '>' �� ������� ���������
	for (volatile uint32_t _entry_idx = 0; _entry_idx < entrys; ++_entry_idx)
	{
		//��������� ��������� ����������� ���������. ��� ��������� � ��������������
		//��������� �� ���� � ��� �� ����, ����� ����� ����������� � ���� ��� ��� ���������
		//����������� ������ '<'
		for (uint32_t _index = entry_list[_entry_idx]; _index < entry_list[_entry_idx + 1]; ++_index)
		{
			if (buffer[_index] == '>')
			{
				++offsets;
				entry_offset = (uint32_t*)realloc(entry_offset, sizeof(uint32_t) * offsets);
				entry_offset[offsets - 1] = _index;
			}
		}
	}

	//���� ����������� � ������ ������. ������ �������� '<' � '>' ����������� '<a href="'+�����+'">'+�����+'</a>'

	uint32_t entrys_cnt = 0;
	uint32_t blocks_cnt = 0;

	if (entry_list[entrys_cnt] == 0)	//���� ��� ���������� � ������� ������� �� ��������� ������� � +1 entrys_cnt
	{									//� ��������� ������ �� �����
		//������
		for (volatile uint32_t _part_idx = entrys_cnt; _part_idx < entrys + offsets + 0;)
		{

		}
	}
	else
	{
		uint32_t testpoint1 = 0;
		uint32_t testpoint2 = 0;

		//����������� ������ �� ����
		testpoint1 = entry_offset[entrys_cnt];
		testpoint2 = entry_list[entrys_cnt];
		output->append(&buffer[entry_offset[entrys_cnt]], entry_list[entrys_cnt] - 1);

		//������ � ����i
		for (volatile uint32_t _part_idx = 0; _part_idx < entrys;++_part_idx)
		{
			++entrys_cnt;
			//������� ���� <a href="
			output->append(simple_url_iopenurl, simple_url_iopenurl_size);
			//������� ������-������
			output->append(&buffer[entry_list[entrys_cnt - 1]], entry_offset[entrys_cnt] - entry_list[entrys_cnt - 1]);
			//������� ������������ ������ ">
			output->append(simple_url_icloseurl, simple_url_icloseurl_size);
			//������� ������������� ������
			output->append(&buffer[entry_list[entrys_cnt - 1]], entry_offset[entrys_cnt] - entry_list[entrys_cnt - 1]);
			//������� ������������ ����
			output->append(simple_url_iclosetext, simple_url_iclosetext_size);
			//������� ������ ����� ������
			output->append(&buffer[entry_offset[entrys_cnt]] + 1, entry_list[entrys_cnt] - entry_offset[entrys_cnt] - 2);
		}
	}

	return output->c_str();
}
