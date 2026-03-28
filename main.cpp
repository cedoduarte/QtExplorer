#include "mainwindow.h"

#include <QSettings>
#include <QApplication>

void setApplicationStyle(QApplication *a)
{
    QSettings settings;
    settings.beginGroup("settings");
    a->setStyle(settings.value("style").toString());
    settings.endGroup();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QtExplorer");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("DuarteCorporation");
    a.setOrganizationDomain("www.duartecorporation.com");
    setApplicationStyle(&a);
    MainWindow mainWindow;
    mainWindow.show();
    return QCoreApplication::exec();
}