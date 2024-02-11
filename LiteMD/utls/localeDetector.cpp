#include "LiteMD.h"
#include <map>

//����� ������������ ���������� ����� � ��� ����� � ����������
std::map<QString, int> localeMap{
	{"en_US", 0},
	{"ru_RU", 1},
	{"ru_UA", 2}
};

//������� ��������� ���� ������� � ����� ���� ���������� � ������������
void LiteMD::localeDetector(void)
{
	QTranslator lmd_lgn;
	QString localeName = QLocale::system().name();
	if (localeName == "en_US")
		mdlSet->slot_lang_selected(localeMap[localeName]);
	else if (localeName == "ru_RU")
		mdlSet->slot_lang_selected(localeMap[localeName]);
	else if (localeName == "ru_UA")
		mdlSet->slot_lang_selected(localeMap[localeName]);
}
