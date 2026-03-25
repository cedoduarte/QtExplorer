#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "location_t.h"
#include "diskusage.h"

#include <QMainWindow>
#include <vector>
#include <QFileInfo>
#include <QModelIndex>
#include <QStorageInfo>

#ifdef Q_OS_WIN
#define MY_COMPUTER_DIR ":::{20D04FE0-3AEA-1069-A2D8-08002B30309D}"
#else
#define MY_COMPUTER_DIR QDir::rootPath()
#endif

class QFileSystemModel;
class QProgressBar;
class QListWidgetItem;
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
    void onListViewDoubleClicked(const QModelIndex &index);
    void onLocationItemClicked(QListWidgetItem *locationItem);
    void on_actionClose_triggered();
private:
    Location_t createDirectoryLocation(const QString &displayName, const QString &iconUri, const QString &path) const;
    void showOrHideDiskBar(DiskUsage &diskUsage);
    bool matchesFilePathAt(int topLevelItemIndex, const QString &absoluteFilePath) const;
    void clearStatusBar();
    void refreshDiskBar(const Location_t &selectedLocation);
    QListWidgetItem* createLocationListWidgetItem(int locationIndex);
    AdditionalInfo additionalInfoFromStorageInfo(const QStorageInfo &storage) const;
    void appendDrive(const QStorageInfo &storage);
    void appendLocationInLocationListWidget(int locationIndex);
    void prepareAndShowDiskBar(const DiskUsage &diskUsage);
    QString getDiskBarFormat(const QString &availableStr, const QString &totalStr, int percentage) const;
    void displayOrHideDiskBar(const Location_t &selectedLocation);
    void init();
    void appendNewFileInfoInTreeWidget(const QFileInfo &fileInfo);
    bool fileExistsInTreeWidget(const QString &absoluteFilePath) const;
    void appendDrives();
    void initDiskUsageBar();
    void displayDiskUsage(const Location_t &selectedLocation);
    void initFileModel();
    void connectSlots();
    void populateLocationList();
    void populateLocationListWidget();
    void goPath(const QString &path);

    Ui::MainWindow *ui;
    QProgressBar *m_diskBar;
    QFileSystemModel *m_fileModel;
    std::vector<Location_t> m_locationList;
};

#endif // MAINWINDOW_H
