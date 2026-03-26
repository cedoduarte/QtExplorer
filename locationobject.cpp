#include "locationobject.h"

#include <QDir>
#include <QIcon>
#include <QStandardPaths>

#ifdef Q_OS_WIN
#define MY_COMPUTER_DIR ":::{20D04FE0-3AEA-1069-A2D8-08002B30309D}"
#else
#define MY_COMPUTER_DIR QDir::rootPath()
#endif

std::vector<QString> LocationObject::getStandardPathList()
{
    return {
        MY_COMPUTER_DIR,
        QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
        QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        QStandardPaths::writableLocation(QStandardPaths::MoviesLocation),
        QStandardPaths::writableLocation(QStandardPaths::TempLocation)
    };
}

std::vector<QString> LocationObject::getPathNames()
{
    return {
        "My Computer",
        "Home",
        "Desktop",
        "Documents",
        "Downloads",
        "Music",
        "Pictures",
        "Movies",
        "Temp"
    };
}

LocationObject::LocationObject()
    : m_id(-1)
{
}

LocationObject::LocationObject(int id, const QString &displayName, const QIcon &icon, const QString &path)
    : m_id(id)
    , m_displayName(displayName)
    , m_icon(icon)
    , m_path(path)
{
}

void LocationObject::setId(int id)
{
    m_id = id;
}

void LocationObject::setDisplayName(const QString &name)
{
    m_displayName = name;
}

void LocationObject::setIcon(const QIcon &icon)
{
    m_icon = icon;
}

void LocationObject::setPath(const QString &path)
{
    m_path = path;
}

int LocationObject::id() const
{
    return m_id;
}

QString LocationObject::displayName() const
{
    return m_displayName;
}

QIcon LocationObject::icon() const
{
    return m_icon;
}

QString LocationObject::path() const
{
    return m_path;
}