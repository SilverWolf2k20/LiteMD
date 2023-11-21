#pragma once
#include <QtWidgets>
#include <qurl.h>
#include <qnetworkaccessmanager.h>
//����� ���������� �� ����
class Downloader : public QObject
{
	Q_OBJECT
	private:
		//�������� ������� �����������
		QNetworkAccessManager* netman;
	public:
		//������� �����������
		Downloader(QObject* dobj = 0);
		//��������� �������
		void download(const QUrl&);
	signals:
		//������ ��������� ��������
		void downloadProgress(qint64, qint64);
		//������ ���������� ��������
		void done(const QUrl&, const QByteArray&);
		//������ ������ �����������
		void error();
	private slots:
		//���� ���������� ��������
		void slotFinished(QNetworkReply*);
};
