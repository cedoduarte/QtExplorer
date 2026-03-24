#ifndef GLOBALENUMS_H
#define GLOBALENUMS_H

#include <qnamespace.h>

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

#endif // GLOBALENUMS_H
