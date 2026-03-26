#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "locationobject.h"

#include <QMainWindow>
#include <vector>

class QFileSystemModel;
class QTreeWidgetItem;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void on_actionClose_triggered();
    void on_actionPreferences_triggered();
    void onLocationListWidgetItemClicked(QListWidgetItem *item);
    void onExplorerListViewItemClicked(const QModelIndex &index);
    void on_actionAbout_Qt_triggered();
    void on_clearButton_clicked();

    void on_removeButton_clicked();

private:
    static QIcon getFolderIcon();

    bool isTopLevelItem(QTreeWidgetItem *item) const;
    void initialize();
    void connectSlots();
    void goFirstLocation();
    QTreeWidgetItem* createFileDetailTreeWidgetItem(const QString &text) const;
    QString formattedDataSize(qint64 bytes) const;
    bool fileDetailItemExists(const QString &path) const;
    QTreeWidgetItem* createFileInfoTreeWidgetItem(const QModelIndex &index);
    void goPath(const QString &path);
    void toListWidgetItem(const LocationObject &locationObject) const;
    void displayLocationList();
    std::vector<LocationObject> getLocationList() const;
    const LocationObject* getLocationById(int id) const;

    Ui::MainWindow *ui;
    std::vector<LocationObject> m_locationList;
    QFileSystemModel *m_fileSystemModel;
};

#endif // MAINWINDOW_H
