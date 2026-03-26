#ifndef LOCATIONOBJECT_H
#define LOCATIONOBJECT_H

#include <QIcon>

class QListWidgetItem;

class LocationObject
{
public:
    LocationObject();
    LocationObject(int id, const QString &displayName, const QIcon &icon, const QString &path);

    void setId(int id);
    void setDisplayName(const QString &name);
    void setIcon(const QIcon &icon);
    void setPath(const QString &path);

    int id() const;
    QString displayName() const;
    QIcon icon() const;
    QString path() const;

    static std::vector<QString> getStandardPathList();
    static std::vector<QString> getPathNames();
private:
    int m_id;
    QString m_displayName;
    QIcon m_icon;
    QString m_path;
};

#endif // LOCATIONOBJECT_H
