#pragma once
#include <QtWidgets>
#include <qurl.h>
#include "Downloader.h"
//����������� �������� ��� ���������� �����������
class DownloaderGui : public QWidget
{
	Q_OBJECT
	private:
		//������ ����������
		Downloader* dw;
		//����� ���������
		QProgressBar* dwPb;
		//���� ����� ������
		QLineEdit* dwEt;
		//������ ������ ��������
		QPushButton* dwPt;
		//����� ��� ������ ����������� ��������
		void showPic(const QString&);
		//������� ������ �������
		QLabel* plbl;
	public:
		//������� �����������
		DownloaderGui(QWidget* dwgt = 0);
		//������� ����������
		~DownloaderGui();
		//������� �������� ����
		void closeEvent(QCloseEvent*);
	private slots:
		//���� ��������� ��������
		void slotGo();
		//���� ����������� ������
		void slotError();
		//���� �������������� ������� ��������� ��������
		void slotDownloadProgress(qint64, qint64);
		//���� ������������ ��� �������� ���������
		void slotDone(const QUrl&, const QByteArray&);
		//����, ������������ ����
		void slotShow();
};
