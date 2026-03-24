#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <optional>
#include <QFileInfo>
#include <QModelIndex>

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

enum LocationType
{
    DIRECTORY,
    DRIVE
};

enum LocationRoles
{
    LocationRole = Qt::UserRole + 1
};

enum FileTreeRoles
{
    FilePathRole = Qt::UserRole + 1
};

struct AdditionalInfo
{
    QString fileSystem;
    qint64 bytesTotal;
    qint64 bytesAvailable;
};

struct Location
{
    LocationType locationType;
    QString displayText;
    QString iconPath;
    QString path;
    std::optional<AdditionalInfo> additionalInfo;
};

struct FileTreeWidgetItem
{
    QTreeWidgetItem *topLevelFileItem;
    QTreeWidgetItem *pathItem;
    QTreeWidgetItem *birthTimeItem;
    QTreeWidgetItem *groupItem;
    QTreeWidgetItem *isExecutableItem;
    QTreeWidgetItem *isHiddenItem;
    QTreeWidgetItem *lastModifiedItem;
    QTreeWidgetItem *lastReadItem;
    QTreeWidgetItem *ownerItem;
    QTreeWidgetItem *sizeItem;
    QTreeWidgetItem *suffixItem;

    FileTreeWidgetItem(const QFileInfo &fileInfo);
    QTreeWidgetItem* createSubitem(const QString &text) const;
    QList<QTreeWidgetItem*> children() const;
};

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
    void init();
    void appendNewFileInfoInTreeWidget(const QFileInfo &fileInfo);
    bool fileExistsInTreeWidget(const QString &absoluteFilePath) const;
    void appendDrives();
    void initDiskUsageBar();
    void displayDiskUsage(const Location &selectedLocation);
    void initFileModel();
    void connectSlots();
    void populateLocationList();
    void populateLocationListWidget();
    void goPath(const QString &path);

    Ui::MainWindow *ui;
    QProgressBar *m_diskBar;
    QFileSystemModel *m_fileModel;
    std::vector<Location> m_locationList;
};

#endif // MAINWINDOW_H
