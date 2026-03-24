#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <optional>

#ifdef Q_OS_WIN
#define MY_COMPUTER_DIR ":::{20D04FE0-3AEA-1069-A2D8-08002B30309D}"
#else
#define MY_COMPUTER_DIR QDir::rootPath()
#endif

class QFileSystemModel;
class QProgressBar;
class QListWidgetItem;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum LocationType
    {
        DIRECTORY,
        DRIVE
    };

    enum LocationRoles
    {
        LocationRole = Qt::UserRole + 1
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

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void onLocationItemClicked(QListWidgetItem *locationItem);
private:
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
