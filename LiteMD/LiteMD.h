#pragma once
#include <QtWidgets>
//#include "ui_LiteMD.h"
#include "mdEditor.h"
#include "mdScreen.h"
#include "GuiDownloader.h"
#include "appSettings.h"
#include "frameChangelog.h"
#include "xmlWriter.h"
#include "xmlReader.h"
#include "logger.h"
extern "C"
{
	#include "globalFlags.h"
	#include "global_definitions.h"
}

//Номер билда, пока задаётся вручную
//UPD patch 0.1.9 теперь вынесен в global_definitions.h

class LiteMD : public QMainWindow
{
    Q_OBJECT
	private:
		//Ui::LiteMDClass ui;			//Не используется
		QToolBar* quick_tb;				//Тулбар для кнопок-ярлыков
		QToolBar* serv_tb;				//Тулбар для кнопок помощи, о проге, Bug!
		QMenu* mHelp;					//Меню помощи
		QMenu* mFile;					//Меню файла
		QMenu* mEdit;					//Меню "Правка"
		QMenu* mSettings;				//Меню настроек
		mdEditor* mde;					//Редактор
		mdScreen* mds;					//Рендер текста
		DownloaderGui* dwModule;		//Модуль загрузчика
		QString defTitle;				//Контейнер дефолтного заголовка
		QLabel* workProgressCap;		//Затычка на недоделанные элементы
		appSettings* mdlSet;			//Диалог настроек приложения
		QGroupBox* editorWindow;		//Окно редактора
		QGroupBox* viewerWindow;		//Окно рендера
		currentChangelog* cLog;			//Список изменений
		xmlWriter* xmlW;				//Класс для записи настроек в файл
		xmlReader* xmlR;				//Читалка настроек
		QTimer* showTim;				//Таймер на отображение окна
		logger* logWindow;				//Окно логов которое появляется нажатием на жука

		//Действия всякие, в меню и в док
		QAction* actAbout;				//Пункт меню о программе
		QAction* actOpen;				//Пункт меню открыть
		QAction* actSave;				//Пункт меню сохранить
		QAction* actSaveAs;				//Пункт меню сохранить как
		QAction* actQuit;				//Пункт меню выход
		QAction* actDownloader;			//Кнопка вызова загрузчика
		QAction* actSet;				//Кнопка вызова настроек
		QAction* actNew;				//Кнопка создания нового документа
		QAction* actPlaceUrl;			//Преобразовать в (ссылку)
		QAction* actPlaceAltUrl;		//Преобразовать в [альтернативную](ссылку)
		QAction* actSetTextFormat;		//Выбрать форматирование выделенного текста
		QAction* actHelp;				//Открывает справку
		QAction* actOpenChangelog;		//Открывает список изменений текущей версии
		QAction* actBugReport;			//Кнопка открытия окна логов
	protected:
		bool eventFilter(QObject* pobj, QEvent* event);
		void update_ui();
		void localeDetector(void);
	public:
		void closeEvent(QCloseEvent*);		//Перехватчик закрытия приложения
		LiteMD(QWidget *parent = nullptr);	//Базовый конструкор
		~LiteMD();
	signals:
		void saveFile();		//Сохранение файла
		void switch_lang(int);	//Сигнал смены языка
	private slots:
		void slotAbout();	//Слот для вызова окна о программе
		void httpModuleShow();	//Сигнал для вызова модуля загрузчика
		void slot_mbar_send_string(const QString&);	//Слот для смены заголовка
	public slots:
		void slotTitleChanged(const QString&);	//Слот для изменения заголовка
		void slotFileEdited();	//Слот для установки флага "*"
		void slotTitleReset();	//Слот для сброса заголовка к дефолтному
};
