#ifndef FILETREEWIDGETITEM_H
#define FILETREEWIDGETITEM_H

#include <QList>
#include <QFileInfo>

class QTreeWidgetItem;

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

#endif // FILETREEWIDGETITEM_H
