#include "LiteMD.h"
#include <QtWidgets/QApplication>
#include <regex>
#include <string>

int main(int argc, char *argv[])
{
    QApplication mdApp(argc, argv);

	std::string mdInput{ "To be, or not to be, that is the question..." }; // �������� ������
	std::regex rex{ "(\\S+)" }; // ���������� ���������
	std::sregex_iterator beg{ mdInput.cbegin(), mdInput.cend(), rex }; // ��������
	// �� ������ ������������������ ��������� ����������
	std::sregex_iterator end{};  // '�������' ��������

    LiteMD sdiEditor;
	sdiEditor.show();
    return mdApp.exec();
}
