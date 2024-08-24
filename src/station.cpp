#include "station.h"

Station::Station(QString name, QString picture, QUrl url) :
    m_name{std::move(name)}, m_pic{std::move(picture)}, m_url{std::move(url)}
{
}
