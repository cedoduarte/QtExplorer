#include "iconproviderobject.h"

const QFileIconProvider IconProviderObject::s_provider;

QIcon IconProviderObject::getIcon(SelectIcon iconSelected) const
{
    switch (iconSelected)
    {
        case MyComputer:
        {
            return s_provider.icon(QFileIconProvider::Computer);
        }
        case Desktop:
        {
            return s_provider.icon(QFileIconProvider::Desktop);
        }
        case Folder:
        {
            return s_provider.icon(QFileIconProvider::Folder);
        }
    }
    return QIcon();
}