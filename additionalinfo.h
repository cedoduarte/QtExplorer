#ifndef ADDITIONALINFO_H
#define ADDITIONALINFO_H

#include <QString>

struct AdditionalInfo
{
    QString fileSystem;
    qint64 bytesTotal;
    qint64 bytesAvailable;
};

#endif // ADDITIONALINFO_H
