#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include "ui_Monitor.h"
#include "ui_Control.h"
#include "qcustomplot.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QDockWidget>


class Ui_MainWidget
{
	friend class MainWidget;
private:

    Monitor *monitor;
    Control *control;

    QFrame *frame;
    QDockWidget *dockMonitor;
    QDockWidget *dockControl;
    QWidget *widgetMonitor;
    QWidget *centralWidget;

    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionPreferences;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionAboutBioreactor;

    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuOptions;
    QMenu *menuAbout;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    QGridLayout *layout;
    QGridLayout *layoutCentralWidget;
    QGridLayout *layoutFrame;
    QCustomPlot *chartMain;

public:

    void setup(QMainWindow *MainWidget)
    {
        if(MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));

        MainWidget->resize(1126,466);
        MainWidget->setMinimumSize(QSize(1000,0));

        setupActions(MainWidget);
        setupMenus(MainWidget);
        setupToolBars(MainWidget);
        setAllText(MainWidget);

//		Monitor
        dockMonitor = new QDockWidget(MainWidget);
        dockMonitor->setObjectName(QStringLiteral("dockMonitor"));
        monitor = new Monitor();
        monitor->setup();
        dockMonitor->setWidget(monitor);
        MainWidget->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockMonitor);

//      Control
        dockControl = new QDockWidget(MainWidget);
        dockControl->setObjectName(QStringLiteral("dockControl"));
		dockControl->setMinimumSize(230,250);
        control = new Control();
        control->setup();
        dockControl->setWidget(control);
        MainWidget->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockControl);
//		control.setup(MainWidget);


//		Chart
        centralWidget = new QWidget(MainWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);

        layoutCentralWidget = new QGridLayout(centralWidget);
        layoutCentralWidget->setSpacing(6);
        layoutCentralWidget->setContentsMargins(11,11,11,11);
        layoutCentralWidget->setObjectName(QStringLiteral("layoutCentralWidget"));
        layoutCentralWidget->addWidget(frame,0,0,1,1);

        chartMain = new QCustomPlot(frame);
        chartMain->setObjectName(QStringLiteral("chartMain"));

        layoutFrame = new QGridLayout(frame);
        layoutFrame->setSpacing(6);
        layoutFrame->setContentsMargins(11,11,11,11);
        layoutFrame->setObjectName(QStringLiteral("layoutFrame"));
        layoutFrame->addWidget(chartMain,0,0,1,1);

        MainWidget->setCentralWidget(centralWidget);

    }

    void setupActions(QMainWindow *MainWidget)
    {
        actionNew = new QAction(MainWidget);
        actionSave = new QAction(MainWidget);
        actionSave_As = new QAction(MainWidget);
        actionClose = new QAction(MainWidget);
        actionExit = new QAction(MainWidget);
        actionPreferences = new QAction(MainWidget);
        actionConnect = new QAction(MainWidget);
        actionDisconnect = new QAction(MainWidget);
        actionAboutBioreactor = new QAction(MainWidget);

        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionAboutBioreactor->setObjectName(QStringLiteral("actionAboutBioreactor"));

        QIcon icon;
        icon.addFile(QStringLiteral(":/new/Resource/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);

        QIcon icon1;
        icon1.addFile(QStringLiteral("images/connect.png"), QSize(), QIcon::Normal, QIcon::On);
        actionConnect->setIcon(icon1);

        QIcon icon2;
        icon2.addFile(QStringLiteral("images/disconnect.png"), QSize(), QIcon::Normal, QIcon::On);
        actionDisconnect->setIcon(icon2);
    }

    void setupMenus(QMainWindow *MainWidget)
    {
        menuBar = new QMenuBar(MainWidget);
        menuBar->setGeometry(QRect(0, 0, 1126, 19));
        menuFile = new QMenu(menuBar);
        menuEdit = new QMenu(menuBar);
        menuOptions = new QMenu(menuBar);
        menuAbout = new QMenu(menuBar);

        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuAbout->setObjectName(QStringLiteral("menuAbout"));

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionConnect);
        menuOptions->addAction(actionDisconnect);
        menuEdit->addAction(actionPreferences);
        menuAbout->addAction(actionAboutBioreactor);
        MainWidget->setMenuBar(menuBar);


    }

    void setupToolBars(QMainWindow *MainWidget)
    {
        statusBar = new QStatusBar(MainWidget);
        mainToolBar = new QToolBar(MainWidget);

        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));

        MainWidget->setStatusBar(statusBar);
        MainWidget->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
    }

    void setAllText(QMainWindow *MainWidget)
    {
        MainWidget->setWindowTitle("Bioreactor 1000");
        actionNew->setText("New");
        actionSave->setText("Save");
        actionSave_As->setText("Save As");
        actionClose->setText("Close");
        actionExit->setText("Exit");
        actionPreferences->setText("Preferences");
        actionConnect->setText("Connect");
        actionDisconnect->setText("Disconnect");
        actionAboutBioreactor->setText("About Bioreactor");
        menuFile->setTitle("File");
        menuEdit->setTitle("Edit");
        menuOptions->setTitle("Options");
        menuAbout->setTitle("About");
    }

};

namespace Ui
{
	class MainWidget : public Ui_MainWidget {};
}

#endif
