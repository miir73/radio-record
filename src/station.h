#pragma once

#include <QString>
#include <QUrl>

class Station {
public:
    Station() = default;
    Station(QString name, QString picture, QUrl url);

    QString name() const { return m_name; }
    QString pic() const { return m_pic; }
    QUrl url() const { return m_url; }

private:
    QString m_name;
    QString m_pic;
    QUrl m_url;
};

//#endif // STATION_H
