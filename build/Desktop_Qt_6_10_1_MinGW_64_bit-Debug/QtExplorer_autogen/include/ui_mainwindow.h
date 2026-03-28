/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionPreferences;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QListWidget *locationListWidget;
    QListView *explorerListView;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTreeWidget *fileDetailTreeWidget;
    QPushButton *clearButton;
    QPushButton *removeButton;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(993, 600);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionClose->setIcon(icon);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName("actionPreferences");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/preferences.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionPreferences->setIcon(icon1);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName("actionAbout_Qt");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/qt.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAbout_Qt->setIcon(icon2);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        locationListWidget = new QListWidget(splitter);
        locationListWidget->setObjectName("locationListWidget");
        splitter->addWidget(locationListWidget);
        explorerListView = new QListView(splitter);
        explorerListView->setObjectName("explorerListView");
        splitter->addWidget(explorerListView);
        widget = new QWidget(splitter);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        fileDetailTreeWidget = new QTreeWidget(widget);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/details.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Files Details"));
        __qtreewidgetitem->setIcon(0, icon3);
        fileDetailTreeWidget->setHeaderItem(__qtreewidgetitem);
        fileDetailTreeWidget->setObjectName("fileDetailTreeWidget");

        gridLayout->addWidget(fileDetailTreeWidget, 0, 0, 1, 3);

        clearButton = new QPushButton(widget);
        clearButton->setObjectName("clearButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clearButton->setIcon(icon4);

        gridLayout->addWidget(clearButton, 1, 0, 1, 1);

        removeButton = new QPushButton(widget);
        removeButton->setObjectName("removeButton");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/remove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        removeButton->setIcon(icon5);

        gridLayout->addWidget(removeButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        splitter->addWidget(widget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 993, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionClose);
        menuEdit->addAction(actionPreferences);
        menuAbout->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qt Explorer", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionPreferences->setText(QCoreApplication::translate("MainWindow", "Preferences", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
