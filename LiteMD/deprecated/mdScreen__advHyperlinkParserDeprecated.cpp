#include <QtWidgets>
#include "mdScreen.h"
#include "syntax_preprocessor.h"
#include "syntax_postprocessor.h"
#include "symbolCleaner.h"
#include "urlBasicSimplifiedParser.h"
#include "urlBasicParser.h"
#include "urlAdvancedParser.h"
#include <string>
#include <regex>

//��������� ��� �������� ������� html �����������
struct visualTags
{
	std::string tag_href_open = "a href=\"";
	std::string tag_href_close = "\"";
	std::string tag_href_end = "</a>";
	std::string left_angl_bracket_replacer = "&#60";
	std::string right_angl_bracket_replacer = "&#62";
}vType;

void mdScreen::textProcessorDeprecated()
{
	//������������ ����� ��������������
	mdInput = hyperlinkParser(mdInput);

	//������������ � ��������� ������
	//���� ������ � ������� ����������� ���������
	std::wsregex_iterator beg{mdInput.cbegin(),mdInput.cend(),*regexHyperlink};
	std::wsregex_iterator end{};
	std::wstring buffer = QString("NULL").toStdWString();
	std::wstring debugPeek;

	//���������� ��������
	lengShift = 0;
	mdFormatted = QString::fromStdWString(mdInput);

	//��������� ���� � ������ ���������� ���������
	for (std::wsregex_iterator i = beg; i != end;++i)
	{
		//��������� ��� "a href="
		mdFormatted.insert(i->position() + lengShift + 1, QString::fromStdString(vType.tag_href_open));
		debugPeek = mdFormatted.toStdWString();
		//����������� �� ������ ������ ������
		buffer = std::wstring(mdFormatted.toStdWString()).substr(i->position() + lengShift + vType.tag_href_open.size() + 1,i->length()-2);
		//����������� ����������� ���
		mdFormatted.insert(i->position() + buffer.size() + vType.tag_href_open.size() + lengShift + 1, QString::fromStdString(vType.tag_href_close));
		debugPeek = mdFormatted.toStdWString();
		//����������� ������� ������
		mdFormatted.insert(i->position() + buffer.size() + vType.tag_href_open.size() + vType.tag_href_close.size() + lengShift + 2,QString::fromStdWString(buffer));
		debugPeek = mdFormatted.toStdWString();
		//����������� ����������� ���
		mdFormatted.insert(i->position() + buffer.size() + vType.tag_href_open.size() + vType.tag_href_close.size() + buffer.size() + lengShift + 2, QString::fromStdString(vType.tag_href_end));
		debugPeek = mdFormatted.toStdWString();
		//��������� �������� ����������� ��� + ����������� ����� ���� + ����������� ��������� ������������� ������+ ����������� ���
		lengShift += vType.tag_href_open.size() + vType.tag_href_close.size() + buffer.size() + vType.tag_href_end.size();
		debugPeek = mdFormatted.toStdWString();
		//qApp->processEvents();	�������� �����������
	}

	//������� �� ���������� ��������� � ���������� ����� � �����
	processCRLF(mdFormatted);
	lengShift = 0;
	buffer = L"";
	mdInput = mdFormatted.toStdWString();

	//��������� �������������� ������
	int indexIn = 0;
	int index = 0;
	int range = 0;
	int urname_length = 0;
	std::wstring bufferLink=L"";
	std::wstring bufferName=L"";
	//��������� ���� �� ����� �� ����� ������
	for (int i = 0;i < mdInput.size();++i)
	{
		//�������� ��������� �� ���������������� �������� ������
		index = mdInput.find('[', index);
		range = mdInput.find(']', index);
		//���� �������� ����-�� ����� �� ��������� �� ���������
		if (index == -1 || range == -1)
			break;
		//�������� ���������������� �������� � ������
		buffer = mdInput.substr(index, range - index+1);
		bufferName = buffer;
		//�������� ��������� �� ������ � �����
		indexIn = index;
		index = range;
		//�������� ���� ��������� �� ����� �� ����� ������
		if (index!=mdInput.size()-1)
			//���� ������� ����������� ������ �� ���������
			if(mdInput.at(index + 1) == '(')
			{
				//�������� ����� ������ �� ����������� ������
				range = mdInput.find(')', index + 1);
				//���� ����������� ������ ��� �� �������
				if (range == -1)
					break;
				//�������� � ����� ������
				buffer = mdInput.substr(index + 1, range - index);
				bufferLink = buffer;
				buffer = L"";
				//����������� � ������ ������� ������ � ����� ���������������� �������� ������
				buffer.append(bufferLink);
				buffer.append(bufferName);
				//��������� ������ ������
				urname_length = buffer.size();
				//����������� ������ � html ������
				buffer.replace(0, 1, L"<");
				lengShift += 4;
				//��������� ��� a href
				buffer.insert(1, std::wstring(vType.tag_href_open.begin(),vType.tag_href_open.end()));
				buffer.insert(buffer.find(')'), std::wstring(vType.tag_href_close.begin(), vType.tag_href_close.end()));
				//��������� ����������� ���
				buffer.replace(buffer.find(')'), 2, L">");
				buffer.replace(buffer.find(']'), 1, std::wstring(vType.tag_href_end.begin(), vType.tag_href_end.end()));
				//��������� ������
				mdInput.replace(indexIn, urname_length, buffer);
				//��������� � ������ �� �����
				mdFormatted = QString::fromStdWString(mdInput);
			}
	}
}
