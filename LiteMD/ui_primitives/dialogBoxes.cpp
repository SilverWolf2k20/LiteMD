#include <QtWidgets>
#include "dialogBoxes.h"
#include "LiteMD.h"
//���� ������������� ����������
bool confirmSave()
{
	//������ ���� ������������ ������������� �����
	QMessageBox qmsg(QMessageBox::Warning, QObject::tr("File not saved"), QObject::tr("You dont save changes in file, which is opened currently. Save?"), QMessageBox::Yes | QMessageBox::No);

	//����� �������� ������
	QPixmap appIcon(getAppPath() + "/icon.ico");
	appIcon.setMask(appIcon.createMaskFromColor(QColor(0, 0, 0)));
	qmsg.setWindowIcon(QIcon(appIcon));

	//���������� ������������
	int confirm_status = qmsg.exec();
	//���� ������������ ���������� �� ���������� 1, ����� 0
	if (confirm_status == QMessageBox::Yes)
		return 1;
	else if (confirm_status == QMessageBox::No)
		return 0;
	//���������� 0 ���� ������������ �������
	return 0;
}
