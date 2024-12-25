#include "LiteMD.h"
#include "ui_update_event.h"
#include "GuiDownloader.h"
#include "dialogBoxes.h"
#include "exceptionHandler.h"
#include "logger_backend.h"
#include "LastFileManager.h"
#include <QtWidgets>
#include <boost/container/string.hpp>
extern "C"
{
	#include "globalFlags.h"
	#include "global_definitions.h"
}

inline QIcon setAppIcon()
{
	QPixmap appIcon(getAppPath() + "/icon.ico");
	appIcon.setMask(appIcon.createMaskFromColor(QColor(0, 0, 0)));
	return appIcon;
}

// �������������� ������ ��������� ���������.
void LiteMD::initLastFileMenu()
{
	// ��������� ������ ������.
	LastFileManager lastFileManager;
	const std::deque<std::string>& lastFilePaths = lastFileManager.getFiles();

	QIcon ico;

	// ���� ������ ������ ��� ������ ������� ������ - ��������� ������.
	if (lastFilePaths.empty() || lastFilePaths.front().empty())
		return;

	mFile->addSeparator();

	// ���������� ����.
	std::for_each(
		std::begin(lastFilePaths),
		std::end(lastFilePaths),
		[=](std::string lastFilePath) {
			QFileInfo fileInfo(lastFilePath.c_str());					//������, ���������� ���������� � �����(����. anrej0705)
			QAction* openLastfile = new QAction(fileInfo.fileName());	//������ ��������, ������� ����� �������� � ����(����. anrej0705)

			openLastfile->setData(fileInfo.filePath());					//��������� ���� �� ����� � QVariant(����. anrej0705)

			openLastfile->setIcon(setAppIcon());						//����� ������

			recentFiles->addAction(openLastfile);						//��������� �������� � ����

			if (!connect(
				openLastfile,
				&QAction::triggered,
				mde,
				[=] { mde->slotOpen(fileInfo.filePath()); }))
				QErrorMessage::qtHandler();	//��������� ������ �� ������ ������ ���� � ���������
		}
	);
}
//� ���������
void LiteMD::slotAbout()
{
	QMessageBox::about(this, "LiteMD", tr("Ver ") + APP_STAGE + APP_VERSION + (" build ") + QString::number(static_cast<uint32_t>(BUILD_NUMBER))
		+ tr("<BR>By anrej0705<BR>See me at Github:") + "<BR><A HREF=\"github.com/anrej0705\">github.com/anrej0705</A><BR><BR>"
		+ tr("This app is free for use,modify and reupload<BR><BR>LiteMD IS FREE SOFTWARE! IF YOU PAID FOR IT YOU HAVE BEEN SCAMMED!")
		+ "<BR>" + "<BR>| Qt 5.14.2 | C++17 | C11 | Boost 1.84.00 |<BR>" + "<BR>"
		+ tr("Github repo: ") + "<A HREF=\"https://github.com/anrej0705/LiteMD\">https://github.com/anrej0705/LiteMD</A><BR>"
		+ tr("Releases: ") + "<A HREF=\"https://github.com/anrej0705/LiteMD/releases\">https://github.com/anrej0705/LiteMD/releases</A>");
}
//���� �������������� ���������(���������� ����� � �����)
void LiteMD::slotTitleChanged(const QString& title)
{
	//���������� ��� ��������� ��������� ���������
	std::string newTitle/* = defTitle.toStdString()*/;	//���� 0.2.2 ����������� ���������
	fileFullPath = title.toStdString();
	if (title.isEmpty())
		fileFullPath = QString(tr("Untitled")).toStdString();
	//��������� ��������� �� ����������� � ������������� � ����������
	newTitle.append((tr("LiteMD") + APP_STAGE + APP_VERSION + tr(" build ") + QString::number(static_cast<uint32_t>(BUILD_NUMBER))).toStdString() + " [" + fileFullPath.substr(fileFullPath.rfind('/') + 1, fileFullPath.size() - fileFullPath.rfind('/')) + "]");
	//defTitle = QString::fromStdString(newTitle);
	setWindowTitle(QString::fromStdString(newTitle));
}
//����� ���������
void LiteMD::slotTitleReset()
{
	setWindowTitle(defTitle);
}
//���� ������ ��������� �� ������ �����
void LiteMD::slot_mbar_send_string(const QString& str)
{
	statusBar()->showMessage(str, 4000);
}
//���� ��������� ����� �������������� �����
void LiteMD::slotFileEdited()
{
	if (!appTitleUpdated)
	{
		QString title = windowTitle();
		title.insert(0, '*');
		setWindowTitle(title);
		appTitleUpdated = 1;
	}
}
//����������� ������� ��������
void LiteMD::closeEvent(QCloseEvent* ce)
{
	push_log("[QT]������� ������� �������� ����������");
	//���� ���� �������������� �� ���������� ����� �� ���������
	if (fileChangedState)
	{
		if (!confirmSave())
		{
			//���� ������������ �� ������� ��������� �� ������ �����������
			appClose = 1;
			dwModule->close();
			ce->accept();
		}
		else
		{
			//���� ������������ ������� ��������� �� ���������� ����� ����������
			appClose = 1;
			emit saveFile();
			dwModule->close();
			ce->accept();
		}
	}
	//���������� ���� �������� � ��������� ������ ���� �� ������
	appClose = 1;
	dwModule->close();
}

//����� ������ ��������
void LiteMD::httpModuleShow()
{
	//���� �� ��������� ���� �� ��� ��� ���� �� ����������
	if (dynamic_cast<DownloaderGui*>(dwModule))
	{
		dwModule->slotShow();
		return;
	}
	//����� ������� ������ � ����������
	dwModule = new DownloaderGui;
	dwModule->slotShow();
}
LiteMD::~LiteMD()
{
	//0.2.7 ����� ��������� �����
	//free(chosenTheme);
	//deleteOnExit();
}

void LiteMD::slotCheckUpdates()
{
	throw(exceptionHandler(exceptionHandler::WARNING), "patch");	//0.3.7
}

void LiteMD::slotFileClose()
{
	//��������� ���� � ������ �����
	mde->closeFile();
	fileFullPath.clear();

	//���������� ���������
	setWindowTitle(defTitle);
}

//��������� ���� ����� ������ ���������
void LiteMD::slotMdsDown()
{
	if (!managePrior)
	{
		//���������� ���������
		if (mdsArea->verticalScrollBar()->size().height() > mde->verticalScrollBar()->size().height())
		{
			//����������� �������� ������ ���������, ��� ����� ������ ����
			mdsArea->verticalScrollBar()->setValue(mdsArea->verticalScrollBar()->value() + mdsArea->verticalScrollBar()->size().height());
			mde->verticalScrollBar()->setValue(mdsArea->verticalScrollBar()->value() + mdsArea->verticalScrollBar()->size().height());
		}
		else
		{
			//����������� �������� ������ ���������, ��� ����� ������ ����
			mdsArea->verticalScrollBar()->setValue(mde->verticalScrollBar()->value() + mde->verticalScrollBar()->size().height());
			mde->verticalScrollBar()->setValue(mde->verticalScrollBar()->value() + mde->verticalScrollBar()->size().height());
		}
	}
	else
	{

	}
}

//��������� ����� ����� ������ ���������
void LiteMD::slotMdsUp()
{
	float proport;		//���������, �� ������� �������������� ����������� � ����
	float mdeHeight = mde->verticalScrollBar()->value();	//0 - ������� �������� �� 0
	float mdsHeight = mdsArea->verticalScrollBar()->value();
	int mdsRes = 0;
	int mdeRes = 0;
	if (!managePrior)
	{
		//���������� ���������
		if (mdsHeight > mdeHeight)
		{
			proport = mdsHeight / mdeHeight;
			//����������� �������� ������ ���������, ��� ����� ������ ����
			mdsRes = mdsArea->verticalScrollBar()->value() * proport;
			mdsArea->verticalScrollBar()->setValue((mdsArea->verticalScrollBar()->value() * proport) - mdsArea->verticalScrollBar()->size().height());
			mde->verticalScrollBar()->setValue((mdsArea->verticalScrollBar()->value() * proport) - mdsArea->verticalScrollBar()->size().height());
		}
		else if(mdeHeight > mdsHeight)
		{
			proport = mdeHeight / mdsHeight;
			//����������� �������� ������ ���������, ��� ����� ������ ����
			mdsArea->verticalScrollBar()->setValue((mde->verticalScrollBar()->value() * proport) - mde->verticalScrollBar()->size().height());
			mde->verticalScrollBar()->setValue((mde->verticalScrollBar()->value() * proport) - mde->verticalScrollBar()->size().height());
		}
	}
	else
	{

	}
}

void LiteMD::slotSwitchDir()
{
	if (scrollPrior)			//��������� - ��������
	{
		scrollPrior = 0;
		dirSwitch1->setText("<<");
		dirSwitch2->setText("<<");
		for (uint8_t it = 0; it < 12; ++it)
			hintsList[it]->setText("<<");
		return;
	}
	else if (!scrollPrior)
	{
		scrollPrior = 1;		//��������� - �������
		dirSwitch1->setText(">>");
		dirSwitch2->setText(">>");
		for (uint8_t it = 0; it < 12; ++it)
			hintsList[it]->setText(">>");
		return;
	}
}

void LiteMD::slotManageDir()
{
	if (managePrior)			//����� - ����
	{
		managePrior = 0;
		manageDir->setText(tr("manageDirAuto"));
		dirSwitch1->setText("<>");
		dirSwitch2->setText("<>");
		dirSwitch1->setEnabled(0);
		dirSwitch2->setEnabled(0);
		if (mdsArea->size().height() > mde->verticalScrollBar()->size().height())
			scrollPrior = 0;	//���� - ��������� - ��������
		else if (mdsArea->size().height() < mde->verticalScrollBar()->size().height())
			scrollPrior = 1;	//���� - ��������� �������
		return;
	}
	else if (!managePrior)		//����� - ������
	{
		managePrior = 1;
		manageDir->setText(tr("manageDirManual"));
		dirSwitch1->setEnabled(1);
		dirSwitch2->setEnabled(1);
		if (scrollPrior) //����������� ������ �����������
		{
			dirSwitch1->setText(">>");
			dirSwitch2->setText(">>");
			for (uint8_t it = 0; it < 12; ++it)
				hintsList[it]->setText(">>");
		}
		else if (!scrollPrior)
		{
			dirSwitch1->setText("<<");
			dirSwitch2->setText("<<");
			for (uint8_t it = 0; it < 12; ++it)
				hintsList[it]->setText("<<");
		}
		return;
	}
}

void LiteMD::slotSwitchSync()
{
	if (syncCtl)		//����
	{
		syncCtl = 0;
		syncCtlBtn->setText("==");
		return;
	}
	else if (!syncCtl)	//������
	{
		syncCtl = 1;
		syncCtlBtn->setText("=|=");
		return;
	}
}

void LiteMD::slotScrollEvent(int scroll)
{
	if (scrollPrior && !syncCtl)			//��������� - ��������
	{
		mdsArea->verticalScrollBar()->setValue(scroll);
		return;
	}
	else if (!scrollPrior && !syncCtl)		//��������� �������
	{
		mde->verticalScrollBar()->setValue(scroll);
		return;
	}
}
