#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filetreewidgetitem.h"

#include <QStandardPaths>
#include <QFileSystemModel>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    initFileModel();
    initDiskUsageBar();
    populateLocationList();
    populateLocationListWidget();
    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onListViewDoubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = m_fileModel->fileInfo(index);
    if (fileInfo.isDir())
    {
        goPath(fileInfo.absoluteFilePath());
    }
    else
    {
        appendNewFileInfoInTreeWidget(fileInfo);
    }
}

void MainWindow::appendNewFileInfoInTreeWidget(const QFileInfo &fileInfo)
{
    QString absoluteFilePath = fileInfo.absoluteFilePath();
    if (fileExistsInTreeWidget(absoluteFilePath))
    {
        return;
    }
    FileTreeWidgetItem topLevelFileItem(fileInfo);
    ui->treeWidget->addTopLevelItem(topLevelFileItem.topLevelFileItem);
}

bool MainWindow::matchesFilePathAt(int topLevelItemIndex, const QString &absoluteFilePath) const
{
    QString currentAbsoluteFilePath =
        ui->treeWidget->topLevelItem(topLevelItemIndex)->data(0, FilePathRole).value<QString>();
    return currentAbsoluteFilePath == absoluteFilePath;
}

bool MainWindow::fileExistsInTreeWidget(const QString &absoluteFilePath) const
{
    const int count = ui->treeWidget->topLevelItemCount();
    for (int topLevelItemIndex = 0; topLevelItemIndex < count; topLevelItemIndex++)
    {
        if (matchesFilePathAt(topLevelItemIndex, absoluteFilePath))
        {
            return true;
        }
    }
    return false;
}

void MainWindow::initDiskUsageBar()
{
    m_diskBar = new QProgressBar(this);
    ui->statusbar->insertWidget(0, m_diskBar);
    m_diskBar->hide();
}

void MainWindow::initFileModel()
{
    m_fileModel = new QFileSystemModel(this);
    ui->explorerListView->setModel(m_fileModel);    
    QString path = MY_COMPUTER_DIR;
    m_fileModel->setRootPath(path);
    ui->explorerListView->setRootIndex(m_fileModel->index(path));
}

QString MainWindow::getDiskBarFormat(const QString &availableStr, const QString &totalStr, int percentage) const
{
    return QString("%1 free out of %2 (%3%)")
        .arg(availableStr)
        .arg(totalStr)
        .arg(percentage);
}

void MainWindow::prepareAndShowDiskBar(const DiskUsage &diskUsage)
{
    QString totalStr = diskUsage.formattedDataSize(diskUsage.bytesTotal());
    QString availableStr = diskUsage.formattedDataSize(diskUsage.bytesAvailable());
    m_diskBar->setValue(diskUsage.percentage());
    m_diskBar->setFormat(getDiskBarFormat(availableStr, totalStr, diskUsage.percentage()));
    m_diskBar->show();
}

void MainWindow::showOrHideDiskBar(DiskUsage &diskUsage)
{
    if (diskUsage.compute())
    {
        prepareAndShowDiskBar(diskUsage);
    }
    else
    {
        m_diskBar->hide();
    }
}

void MainWindow::displayOrHideDiskBar(const Location_t &selectedLocation)
{
    DiskUsage diskUsage;
    diskUsage.setBytesTotal(selectedLocation.additionalInfo->bytesTotal);
    diskUsage.setBytesAvailable(selectedLocation.additionalInfo->bytesAvailable);
    showOrHideDiskBar(diskUsage);
}

void MainWindow::displayDiskUsage(const Location_t &selectedLocation)
{
    if (selectedLocation.additionalInfo)
    {
        displayOrHideDiskBar(selectedLocation);
    }
}

void MainWindow::clearStatusBar()
{
    ui->statusbar->clearMessage();
    m_diskBar->hide();
}

void MainWindow::refreshDiskBar(const Location_t &selectedLocation)
{
    if (selectedLocation.locationType == DRIVE)
    {
        displayDiskUsage(selectedLocation);
    }
    else
    {
        clearStatusBar();
    }
}

void MainWindow::onLocationItemClicked(QListWidgetItem *locationItem)
{
    const int locationIndex = locationItem->data(LocationRole).value<int>();
    const Location_t &selectedLocation = m_locationList.at(locationIndex);
    refreshDiskBar(selectedLocation);
    goPath(selectedLocation.path);
}

void MainWindow::connectSlots()
{
    connect(ui->locationListWidget, &QListWidget::itemClicked, this, &MainWindow::onLocationItemClicked);
    connect(ui->explorerListView, &QListView::doubleClicked, this, &MainWindow::onListViewDoubleClicked);
}

QListWidgetItem* MainWindow::createLocationListWidgetItem(int locationIndex)
{
    const Location_t &location = m_locationList.at(locationIndex);
    QListWidgetItem *locationItem = new QListWidgetItem;
    locationItem->setText(location.displayText);
    locationItem->setIcon(QIcon(location.iconPath));
    locationItem->setData(LocationRole, locationIndex);
    return locationItem;
}

void MainWindow::appendLocationInLocationListWidget(int locationIndex)
{
    ui->locationListWidget->addItem(createLocationListWidgetItem(locationIndex));
}

void MainWindow::populateLocationListWidget()
{
    const int locationCount = m_locationList.size();
    for (int locationIndex = 0; locationIndex < locationCount; locationIndex++)
    {
        appendLocationInLocationListWidget(locationIndex);
    }
}

AdditionalInfo MainWindow::additionalInfoFromStorageInfo(const QStorageInfo &storage) const
{
    return {
        QString::fromLatin1(storage.fileSystemType()),
        storage.bytesTotal(),
        storage.bytesAvailable()
    };
}

void MainWindow::appendDrive(const QStorageInfo &storage)
{
    QString rootPath = storage.rootPath(); // Ej: "C:/"
    QString name = storage.displayName();
    m_locationList.push_back({
        DRIVE,
        name,
        ":/icons/drive.png",
        rootPath,
        additionalInfoFromStorageInfo(storage)
    });
}

void MainWindow::appendDrives()
{
    for (const QStorageInfo &storage : QStorageInfo::mountedVolumes())
    {
        if (!storage.isValid() || !storage.isReady())
        {
            continue;
        }
        appendDrive(storage);
    }
}

Location_t MainWindow::createDirectoryLocation(const QString &displayName, const QString &iconUri, const QString &path) const
{
    return {
        DIRECTORY,
        displayName,
        iconUri,
        path
    };
}

void MainWindow::populateLocationList()
{
    m_locationList.push_back(createDirectoryLocation("My Computer", ":/icons/computer.png", MY_COMPUTER_DIR));
    m_locationList.push_back(createDirectoryLocation("Home", ":/icons/home.png", QStandardPaths::writableLocation(QStandardPaths::HomeLocation)));
    m_locationList.push_back(createDirectoryLocation("Desktop", ":/icons/desktop.png", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)));
    m_locationList.push_back(createDirectoryLocation("Documents", ":/icons/documents.png", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)));
    m_locationList.push_back(createDirectoryLocation("Downloads", ":/icons/downloads.png", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)));
    m_locationList.push_back(createDirectoryLocation("Music", ":/icons/music.png", QStandardPaths::writableLocation(QStandardPaths::MusicLocation)));
    m_locationList.push_back(createDirectoryLocation("Pictures", ":/icons/pictures.png", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)));
    m_locationList.push_back(createDirectoryLocation("Movies", ":/icons/movies.png", QStandardPaths::writableLocation(QStandardPaths::MoviesLocation)));
    m_locationList.push_back(createDirectoryLocation("Temp", ":/icons/temp.png", QStandardPaths::writableLocation(QStandardPaths::TempLocation)));
    appendDrives();
}

void MainWindow::goPath(const QString &path)
{
    m_fileModel->setRootPath(path);
    ui->explorerListView->setRootIndex(m_fileModel->index(path));
}

void MainWindow::on_actionClose_triggered()
{
    close();
}