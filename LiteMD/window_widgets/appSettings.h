#pragma once
#include <QtWidgets>
class appSettings : public QDialog
{
	Q_OBJECT
	private:
		QWidget* basicSettings;	//�������� ���������
		QWidget* parserSettings;	//��������� ��������� ������
		QTabWidget* settingsLister;	//�������� �������
		QLabel* workprogress;	//��������
		QPushButton* btnOk;		//������ �������������
		QPushButton* btnCancel;	//������ ������
		QHBoxLayout* controlBtnLay;	//��������� ���������� ������ �����
		QVBoxLayout* dialogWindow;	//�������� ������ ���������� ���������
		void configureBasicSettingsTab();
	public:
		appSettings(QWidget* aWgt = 0);
};
