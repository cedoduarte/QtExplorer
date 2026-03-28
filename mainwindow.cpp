#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "preferencesdialog.h"
#include "iconproviderobject.h"

#include <QFileSystemModel>
#include <QMessageBox>

QIcon MainWindow::getIconByDisplayName(const QString &displayName) const
{
    IconProviderObject iconProvider;
    if (displayName.contains(MY_COMPUTER_DISPLAY_NAME, Qt::CaseInsensitive))
    {
        return iconProvider.getIcon(IconProviderObject::MyComputer);
    }
    else if (displayName.contains(DESKTOP_DISPLAY_NAME, Qt::CaseInsensitive))
    {
        return iconProvider.getIcon(IconProviderObject::Desktop);
    }
    return iconProvider.getIcon(IconProviderObject::Folder);
}

std::vector<LocationObject> MainWindow::getLocationList() const
{
    const auto &standardPathList = LocationObject::getStandardPathList();
    const auto &pathNames = LocationObject::getPathNames();

    const qsizetype count = standardPathList.size();
    std::vector<LocationObject> locationList;
    locationList.reserve(count);

    for (qsizetype index = 0; index < count; index++)
    {
        const int id = static_cast<int>(index) + 1;
        const auto &path = standardPathList.at(index);
        const auto &displayName = pathNames.at(index);
        locationList.emplace_back(id, displayName, getIconByDisplayName(displayName), path);
    }

    return locationList;
}

void MainWindow::displayLocationList()
{
    for (const auto &locationObject : m_locationList)
    {
        toListWidgetItem(locationObject);
    }
}

void MainWindow::toListWidgetItem(const LocationObject &locationObject) const
{
    auto *item = new QListWidgetItem(ui->locationListWidget);
    item->setText(locationObject.displayName());
    item->setIcon(locationObject.icon());
    item->setData(Qt::UserRole, locationObject.id());
}

const LocationObject* MainWindow::getLocationById(int id) const
{
    for (const auto &locationObject : m_locationList)
    {
        if (locationObject.id() == id)
        {
            return &locationObject;
        }
    }
    return nullptr;
}

void MainWindow::goPath(const QString &path)
{
    m_fileSystemModel->setRootPath(path);
    ui->explorerListView->setRootIndex(m_fileSystemModel->index(path));
}

void MainWindow::onLocationListWidgetItemClicked(QListWidgetItem *item)
{
    const int locationId = item->data(Qt::UserRole).toInt();
    const auto *locationObject = getLocationById(locationId);
    if (locationObject != nullptr)
    {
        goPath(locationObject->path());
    }
}

QString MainWindow::formattedDataSize(qint64 bytes) const
{
    return QLocale().formattedDataSize(bytes);
}

QTreeWidgetItem* MainWindow::createFileDetailTreeWidgetItem(const QString &text) const
{
    auto *item = new QTreeWidgetItem({ text });
    item->setIcon(0, QIcon(":/icons/text.png"));
    return item;
}

QTreeWidgetItem* MainWindow::createFileInfoTreeWidgetItem(const QModelIndex &index)
{
    const auto &fileInfo = m_fileSystemModel->fileInfo(index);
    auto *fileTopLevelItem = new QTreeWidgetItem;
    fileTopLevelItem->setText(0, fileInfo.fileName());
    fileTopLevelItem->setIcon(0, m_fileSystemModel->fileIcon(index));
    fileTopLevelItem->setData(0, Qt::UserRole, fileInfo.filePath());
    fileTopLevelItem->addChildren({
        createFileDetailTreeWidgetItem(QString("Path: %1").arg(fileInfo.filePath())),
        createFileDetailTreeWidgetItem(QString("Size: %1").arg(formattedDataSize(fileInfo.size()))),
        createFileDetailTreeWidgetItem(QString("Is Executable: %1").arg(fileInfo.isExecutable() ? "Yes" : "No")),
        createFileDetailTreeWidgetItem(QString("Birth Time: %1").arg(fileInfo.birthTime().toString("yyyy-MM-dd hh:mm:ss")))
    });
    return fileTopLevelItem;
}

bool MainWindow::fileDetailItemExists(const QString &path) const
{
    const int count = ui->fileDetailTreeWidget->topLevelItemCount();
    for (int index = 0; index < count; index++)
    {
        const auto iPath = ui->fileDetailTreeWidget->topLevelItem(index)->data(0, Qt::UserRole).toString();
        if (path == iPath)
        {
            return true;
        }
    }
    return false;
}

void MainWindow::onExplorerListViewItemClicked(const QModelIndex &index)
{
    const auto &fileInfo = m_fileSystemModel->fileInfo(index);
    if (fileInfo.isFile() && !fileDetailItemExists(fileInfo.filePath()))
    {
        ui->fileDetailTreeWidget->addTopLevelItem(createFileInfoTreeWidgetItem(index));
    }
    else if (fileInfo.isDir())
    {
        goPath(fileInfo.filePath());
    }
}

void MainWindow::goFirstLocation()
{
    if (ui->locationListWidget->count() > 0)
    {
        onLocationListWidgetItemClicked(ui->locationListWidget->item(0));
    }
}

void MainWindow::initialize()
{
    m_fileSystemModel = new QFileSystemModel(this);
    ui->explorerListView->setModel(m_fileSystemModel);

    m_locationList = getLocationList();
    displayLocationList();

    IconProviderObject iconProvider;
    setWindowIcon(iconProvider.getIcon(IconProviderObject::Folder));

    connectSlots();
    goFirstLocation();
}

void MainWindow::connectSlots()
{
    connect(ui->locationListWidget, &QListWidget::itemClicked, this, &MainWindow::onLocationListWidgetItemClicked);
    connect(ui->explorerListView, &QListView::clicked, this, &MainWindow::onExplorerListViewItemClicked);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "Qt");
}

void MainWindow::on_clearButton_clicked()
{
    ui->fileDetailTreeWidget->clear();
}

bool MainWindow::isTopLevelItem(QTreeWidgetItem *item) const
{
    return item && item->parent() == nullptr;
}

void MainWindow::on_removeButton_clicked()
{
    auto *item = ui->fileDetailTreeWidget->currentItem();
    if (item == nullptr)
    {
        return;
    }
    if (isTopLevelItem(item))
    {
        const int index = ui->fileDetailTreeWidget->indexOfTopLevelItem(item);
        if (index >= 0)
        {
            delete ui->fileDetailTreeWidget->takeTopLevelItem(index);
        }
    }
}