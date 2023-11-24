#include <QtWidgets>
#include <qurl.h>
#include "Downloader.h"
#include "GuiDownloader.h"
//������� �����������
DownloaderGui::DownloaderGui(QWidget* dwgt) : QWidget(dwgt)
{
	//������������� ��������� ���� ������
	setWindowTitle(tr("HTTP Download module GUI(Deprecated)"));
	//�������������� ������� ����������
	dw = new Downloader(this);
	//�������������� ����������� ��������
	dwPb = new QProgressBar;
	dwEt = new QLineEdit;
	dwPt = new QPushButton("&Go");
	//������� ������ � ���������� ������-������(12.11.2023 �� ��������)
	QString strDownloadLink = "http://i122.fastpic.org/thumb/2023/1120/b5/_e3bc95b508c698aeaa35e205a2b8abb5.jpeg";
	//�������� ������ � ���� �����
	dwEt->setText(strDownloadLink);
	//��������� ������ ������ �� ������ ���������� ��������
	if (!connect(dwPt, SIGNAL(clicked()), SLOT(slotGo())))
		QErrorMessage::qtHandler();
	//��������� ������ ��������� �������� �� ������ ������������ �������� ��������
	if (!connect(dw, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(slotDownloadProgress(qint64, qint64))))
		QErrorMessage::qtHandler();
	//��������� ������ ���������� �� ������
	if (!connect(dw, SIGNAL(done(const QUrl&, const QByteArray&)), this, SLOT(slotDone(const QUrl&, const QByteArray&))))
		QErrorMessage::qtHandler();
	//�������������� ����� ��� ���������� ��������
	QGridLayout* gLay = new QGridLayout;
	//��������� �������
	gLay->addWidget(dwEt, 0, 0);
	gLay->addWidget(dwPt, 0, 1);
	gLay->addWidget(dwPb, 1, 0, 1, 1);
	//������������� ��� ����
	setLayout(gLay);
}
//������� ����������
DownloaderGui::~DownloaderGui()
{}
//���� ���������� ��������
void DownloaderGui::slotGo()
{
	//�������� ����� ������ �������� � �������� ������ �� ���� �����
	dw->download(QUrl(dwEt->text()));
}
//���� ����������� ������� ��������� ��������
void DownloaderGui::slotDownloadProgress(qint64 nRecs, qint64 nTotal)
{
	//���� n ������ 0 ������ � ��� ������
	if (nTotal <= 0)
	{
		//�������� ���� ������ � ���������� ��������
		slotError();
		return;
	}
	//����� ���������� �������� � ���������
	dwPb->setValue(100 * nRecs / nTotal);
}
//���� ����������� ������ � ���������� ��������
void DownloaderGui::slotDone(const QUrl& url, const QByteArray& ba)
{
	//������� ��������� ����� �����, �������������� ������� �� ���� ������ �������
	QString strFileName = url.path().section('/', -1);
	//������� ������ �����
	QFile file(url.path().section('/', -1));
	//���� ������ �������� � ������ �� ���������
	if (file.open(QIODevice::WriteOnly))
	{
		//���������� ���������� ������ � ����
		file.write(ba);
		//��������� ����
		file.close();
		//���� ����� ���� ���� ����� ���������� jpg ��� png �� ������ ��� ��������
		if(strFileName.endsWith(".jpg") || strFileName.endsWith(".png") || strFileName.endsWith(".jpeg"))
			//���������� ��������
			showPic(strFileName);
	}
}
//����� ��������� �� ����� ��������
void DownloaderGui::showPic(const QString& strFileName)
{
	//������� ������ ��������
	QPixmap pix(strFileName);
	//����������� ��� �������� ������ � 2 ���� �� ����� ��������. ���������� ����� ����������� � ������������� �����.������
	pix = pix.scaled(pix.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	//������� ������ �������
	QLabel* plbl = new QLabel;
	//�������� ��������
	plbl->setPixmap(pix);
	//������������ ��������� �������
	plbl->setFixedSize(pix.size());
	//������������� ��������� ����
	plbl->setWindowTitle(tr("View"));
	//���������� �� �����
	plbl->show();
}
//���� ����������� ������
void DownloaderGui::slotError()
{
	//�������� ��������� � ������� ������ ��� ��������� ��� ��������
	QMessageBox::critical(0, tr("Error"), tr("An error while download is occured"));
}
void DownloaderGui::slotShow()
{
	this->move(190, 80);
	this->resize(800, 80);
	this->show();
	QMessageBox::information(0, tr("And he won't live long..."), tr("This module was added experimentally. In the future it will undergo changes or disappear"));
}
