#include "GuiDownloader.h"
#include "global_definitions.h"
#include "logger_backend.h"
extern "C"
{
	#include "globalFlags.h"
}

bool DownloaderGui::eventFilter(QObject* pobj, QEvent* p_event)
{
	if (p_event->type() == static_cast<QEvent::Type>(QEvent::User + APP_EVENT_GuiDownloader_UPDATE_EVENT))
	{
		update_ui();
		return 1;
	}
	return QWidget::eventFilter(pobj, p_event);
}

void DownloaderGui::update_ui()
{
	push_log("[GuiDownloader_ui]���������� ����������");

	//������ ������ ��������
	QList<QWidget*> wList = this->findChildren<QWidget*>();

	//������� ����� ������ ������� �� �������
	foreach(QWidget * sWgt, wList)
	{
		sWgt->setStyle(QStyleFactory::create(chosenTheme));
	}

	//���������� ����
	//uiChanged = 0;

	setWindowTitle(tr("HTTP Download module GUI(Deprecated)"));
	dwPt->setText(tr("&Go"));
	plbl->setWindowTitle(tr("View"));
}
