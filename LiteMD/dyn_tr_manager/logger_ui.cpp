#include "logger.h"
#include "global_definitions.h"
#include "ui_update_event.h"
#include "logger_backend.h"
extern "C"
{
	#include "globalFlags.h"
}

bool logger::eventFilter(QObject* pobj, QEvent* p_event)
{
	if (p_event->type() == static_cast<QEvent::Type>(QEvent::User + APP_EVENT_logger_UPDATE_EVENT))
	{
		update_ui();
		return 1;
	}
	return QWidget::eventFilter(pobj, p_event);
}
//���������� ���������� � ������� ���������� ������ ��������� �����������
void logger::update_ui()
{
	push_log("[logger_ui]���������� ����������");

	//������ ������ ��������
	QList<QWidget*> wList = this->findChildren<QWidget*>();

	//������� ����� ������ ������� �� �������
	foreach(QWidget * sWgt, wList)
	{
		sWgt->setStyle(QStyleFactory::create(chosenTheme));
	}

	//���������� ����
	//uiChanged = 0;

	this->setWindowTitle(tr("logTitle"));
	clearLog->setText(tr("clearLog"));
	saveLog->setText(tr("saveLog"));
	frame->setTitle(tr("logHint"));
}
