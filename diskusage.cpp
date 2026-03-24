#include "diskusage.h"

DiskUsage::DiskUsage()
{
    m_bytesTotal = 0;
    m_bytesAvailable = 0;
    m_usedBytes = 0;
    m_percentage = 0;
}

void DiskUsage::setBytesTotal(qint64 bytes)
{
    m_bytesTotal = bytes;
}

void DiskUsage::setBytesAvailable(qint64 bytes)
{
    m_bytesAvailable = bytes;
}

bool DiskUsage::compute()
{
    if (m_bytesTotal > 0)
    {
        m_usedBytes = qMax<qint64>(0, m_bytesTotal - m_bytesAvailable);
        m_percentage = qRound((double)m_usedBytes / m_bytesTotal * 100.0);
        return true;
    }
    return false;
}

qint64 DiskUsage::bytesTotal() const
{
    return m_bytesTotal;
}

qint64 DiskUsage::bytesAvailable() const
{
    return m_bytesAvailable;
}

qint64 DiskUsage::usedBytes() const
{
    return m_usedBytes;
}

int DiskUsage::percentage() const
{
    return m_percentage;
}

QString DiskUsage::formattedDataSize(qint64 bytes) const
{
    QString totalStr = QLocale().formattedDataSize(bytes);
    return totalStr;
}
