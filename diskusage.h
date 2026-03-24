#ifndef DISKUSAGE_H
#define DISKUSAGE_H

#include <QString>
#include <QLocale>

class DiskUsage
{
public:
    DiskUsage();
    void setBytesTotal(qint64 bytes);
    void setBytesAvailable(qint64 bytes);
    bool compute();
    qint64 bytesTotal() const;
    qint64 bytesAvailable() const;
    qint64 usedBytes() const;
    int percentage() const;
    QString formattedDataSize(qint64 bytes) const;
private:
    qint64 m_bytesTotal;
    qint64 m_bytesAvailable;
    qint64 m_usedBytes;
    int m_percentage;
};

#endif // DISKUSAGE_H
