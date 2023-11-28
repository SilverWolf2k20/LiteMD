#include <QtWidgets>
#include "dialogBoxes.h"
//���� ������������� ����������
bool confirmSave()
{
	//���������� ������������
	int confirm_status = QMessageBox(QMessageBox::Warning, QObject::tr("File not saved"), QObject::tr("You dont save changes in file, which is opened currently. Save?"), QMessageBox::Yes | QMessageBox::No).exec();
	//���� ������������ ���������� �� ���������� 1, ����� 0
	if (confirm_status == QMessageBox::Yes)
		return 1;
	else if (confirm_status == QMessageBox::No)
		return 0;
	//���������� 0 ���� ������������ �������
	return 0;
}
