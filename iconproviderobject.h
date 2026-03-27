#ifndef ICONPROVIDEROBJECT_H
#define ICONPROVIDEROBJECT_H

#include <QIcon>
#include <QFileIconProvider>

class IconProviderObject
{
public:
    enum SelectIcon
    {
        MyComputer,
        Desktop,
        Folder
    };

    QIcon getIcon(SelectIcon iconSelected) const;
private:
    static const QFileIconProvider s_provider;
};

#endif // ICONPROVIDEROBJECT_H
