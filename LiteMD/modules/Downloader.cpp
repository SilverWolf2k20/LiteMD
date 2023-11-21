#include <QtWidgets>
#include <qurl.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include "Downloader.h"
//������� �����������, ������� ������ ����������
Downloader::Downloader(QObject* dobj) : QObject(dobj)
{
	//�������������� �������� �����������
	netman = new QNetworkAccessManager(this);
	//��������� ������ ��������� � ����� ��������������� ������ ���������� ��������
	if (!QObject::connect(netman, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*))))
		QErrorMessage::qtHandler();
}
//��������� �������
void Downloader::download(const QUrl& url)
{
	//������� ������ ���������� � �������� ������ �� ������� ����� ������
	QNetworkRequest netreq(url);
	//��������� ������ ������ ���� � ��������� ��� ��������� ��� ��������� ������� ���������
	QNetworkReply* netrep = netman->get(netreq);
	//��������� ������ ��������� �������� ������ ����� �� ���� � ����� ������� ����� ���������� �� ���������� ��������
	if (!QObject::connect(netrep, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64))))
		QErrorMessage::qtHandler();
}
//����, ���������� �� ���������� ��������
void Downloader::slotFinished(QNetworkReply* netrep)
{
	//��������� ������ ������. ���� ���� ������ �� ���������� ������ �� ������
	if (netrep->error() != QNetworkReply::NoError)
		emit error();
	else
		//����� ���������� ������ ���������� ��������
		emit done(netrep->url(), netrep->readAll());
	//���������� ������ �� �������� ������� �� �����������
	netrep->deleteLater();
}
