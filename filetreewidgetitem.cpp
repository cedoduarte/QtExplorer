#include "filetreewidgetitem.h"
#include "diskusage.h"
#include "globalenums.h"

#include <QTreeWidgetItem>

QTreeWidgetItem* FileTreeWidgetItem::createSubitem(const QString &text) const
{
    QTreeWidgetItem *subitem = new QTreeWidgetItem({ text });
    subitem->setIcon(0, QIcon(":/icons/subitem.png"));
    return subitem;
}

QList<QTreeWidgetItem*> FileTreeWidgetItem::children() const
{
    return {
        pathItem,
        birthTimeItem,
        groupItem,
        isExecutableItem,
        isHiddenItem,
        lastModifiedItem,
        lastReadItem,
        ownerItem,
        sizeItem,
        suffixItem
    };
}

FileTreeWidgetItem::FileTreeWidgetItem(const QFileInfo &fileInfo)
{
    QString absoluteFilePath = fileInfo.absoluteFilePath();

    topLevelFileItem = new QTreeWidgetItem({ fileInfo.fileName() });
    topLevelFileItem->setIcon(0, QIcon(":/icons/folder3.png"));
    topLevelFileItem->setData(0, FilePathRole, absoluteFilePath);

    pathItem = createSubitem(QString("Path: %1").arg(absoluteFilePath));
    birthTimeItem = createSubitem(QString("Birth Time: %1").arg(fileInfo.birthTime().toString("yyyy-MM-dd hh:mm:ss")));
    groupItem = createSubitem(QString("Group: %1").arg(fileInfo.group()));
    isExecutableItem = createSubitem(QString("Is Executable: %1").arg(fileInfo.isExecutable() ? "Yes" : "No"));
    isHiddenItem = createSubitem(QString("Is Hidden: %1").arg(fileInfo.isHidden() ? "Yes" : "No"));
    lastModifiedItem = createSubitem(QString("Last Modified: %1").arg(fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss")));
    lastReadItem = createSubitem(QString("Last Read: %1").arg(fileInfo.lastRead().toString("yyyy-MM-dd hh:mm:ss")));
    ownerItem = createSubitem(QString("Owner: %1").arg(fileInfo.owner()));

    DiskUsage diskUsage;
    QString fileSizeString = diskUsage.formattedDataSize(fileInfo.size());
    sizeItem = createSubitem(QString("Size: %1").arg(fileSizeString));
    suffixItem = createSubitem(QString("Suffix: %1").arg(fileInfo.suffix()));

    topLevelFileItem->addChildren(children());
}