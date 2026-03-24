#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filetreewidgetitem.h"
#include "diskusage.h"

#include <QStandardPaths>
#include <QFileSystemModel>
#include <QProgressBar>
#include <QStorageInfo>

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

    FileTreeWidgetItem *topLevelFileItem = new FileTreeWidgetItem(fileInfo);
    ui->treeWidget->addTopLevelItem(topLevelFileItem->topLevelFileItem);
    delete topLevelFileItem;
}

bool MainWindow::fileExistsInTreeWidget(const QString &absoluteFilePath) const
{
    const int count = ui->treeWidget->topLevelItemCount();
    for (int x = 0; x < count; x++)
    {
        QString currentAbsoluteFilePath = ui->treeWidget->topLevelItem(x)->data(0, FilePathRole).value<QString>();
        if (currentAbsoluteFilePath == absoluteFilePath)
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

void MainWindow::displayDiskUsage(const Location_t &selectedLocation)
{
    if (selectedLocation.additionalInfo)
    {
        DiskUsage diskUsage;
        diskUsage.setBytesTotal(selectedLocation.additionalInfo->bytesTotal);
        diskUsage.setBytesAvailable(selectedLocation.additionalInfo->bytesAvailable);
        if (diskUsage.compute())
        {
            QString totalStr = diskUsage.formattedDataSize(diskUsage.bytesTotal());
            QString availableStr = diskUsage.formattedDataSize(diskUsage.bytesAvailable());
            m_diskBar->setValue(diskUsage.percentage());
            m_diskBar->setFormat(QString("%1 free out of %2 (%3%)")
                .arg(availableStr)
                .arg(totalStr)
                .arg(diskUsage.percentage()));
            m_diskBar->show();
        }
        else
        {
            m_diskBar->hide();
        }
    }
}

void MainWindow::onLocationItemClicked(QListWidgetItem *locationItem)
{
    int locationIndex = locationItem->data(LocationRole).value<int>();
    const Location_t &selectedLocation = m_locationList.at(locationIndex);
    if (selectedLocation.locationType == DRIVE)
    {
        displayDiskUsage(selectedLocation);
    }
    else
    {
        ui->statusbar->clearMessage();
        m_diskBar->hide();
    }
    goPath(selectedLocation.path);
}

void MainWindow::connectSlots()
{
    connect(ui->locationListWidget, &QListWidget::itemClicked, this, &MainWindow::onLocationItemClicked);
    connect(ui->explorerListView, &QListView::doubleClicked, this, &MainWindow::onListViewDoubleClicked);
}

void MainWindow::populateLocationListWidget()
{
    const int locationCount = m_locationList.size();
    for (int locationIndex = 0; locationIndex < locationCount; locationIndex++)
    {
        const Location_t &location = m_locationList.at(locationIndex);
        QListWidgetItem *locationItem = new QListWidgetItem;
        locationItem->setText(location.displayText);
        locationItem->setIcon(QIcon(location.iconPath));
        locationItem->setData(LocationRole, locationIndex);
        ui->locationListWidget->addItem(locationItem);
    }
}

void MainWindow::appendDrives()
{
    for (const QStorageInfo &storage : QStorageInfo::mountedVolumes())
    {
        if (!storage.isValid() || !storage.isReady())
        {
            continue;
        }
        QString rootPath = storage.rootPath(); // Ej: "C:/"
        QString name = storage.displayName();
        AdditionalInfo additionalInfo {
            QString::fromLatin1(storage.fileSystemType()),
            storage.bytesTotal(),
            storage.bytesAvailable()
        };
        m_locationList.push_back({ DRIVE, name, ":/icons/drive.png", rootPath, additionalInfo });
    }
}

void MainWindow::populateLocationList()
{
    m_locationList.push_back({ DIRECTORY, "My Computer", ":/icons/computer.png", MY_COMPUTER_DIR });
    m_locationList.push_back({ DIRECTORY, "Home", ":/icons/home.png", QStandardPaths::writableLocation(QStandardPaths::HomeLocation) });
    m_locationList.push_back({ DIRECTORY, "Desktop", ":/icons/desktop.png", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) });
    m_locationList.push_back({ DIRECTORY, "Documents", ":/icons/documents.png", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) });
    m_locationList.push_back({ DIRECTORY, "Downloads", ":/icons/downloads.png", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) });
    m_locationList.push_back({ DIRECTORY, "Music", ":/icons/music.png", QStandardPaths::writableLocation(QStandardPaths::MusicLocation) });
    m_locationList.push_back({ DIRECTORY, "Pictures", ":/icons/pictures.png", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) });
    m_locationList.push_back({ DIRECTORY, "Movies", ":/icons/movies.png", QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) });
    m_locationList.push_back({ DIRECTORY, "Temp", ":/icons/temp.png", QStandardPaths::writableLocation(QStandardPaths::TempLocation) });
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