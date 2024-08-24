#include "stationsmodel.h"

#include <QDebug>
#include <QQmlEngine>

StationsModel::StationsModel(QObject *parent) : QAbstractListModel(parent), m_player(new QMediaPlayer())
{
    const bool updateResult{updateStations()};
    if (!updateResult) {
        qWarning() << "Update stations failed!";
    }
}

QVariant StationsModel::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }

    const Station &station{m_stations.at(static_cast<quint64>(index.row()))};

    switch (role) {
        case StationRoles::NameRole: {
            return QVariant::fromValue(station.name());
        }
        case StationRoles::PictureRole: {
            return QVariant::fromValue(station.pic());
        }
        case StationRoles::UrlRole: {
            return QVariant::fromValue(station.url());
        }
        default: {
            return true;
        }
    }
}

int StationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<qint32>(m_stations.size());
}

QHash<int, QByteArray> StationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StationRoles::NameRole] = "name";
    roles[StationRoles::PictureRole] = "picture";
    roles[StationRoles::UrlRole] = "url";
    return roles;
}

void StationsModel::registerMe()
{
    qmlRegisterType<StationsModel>("Stations", 1, 0, "StationsModel");
}

// Подумать над использованием QMediaPlayList
void StationsModel::setStation(qint32 index)
{
    qDebug() << index;
    if (static_cast<qint32>(m_stations.size()) < index) {
        qWarning() << "Station not added";
        return;
    }
    m_player->setMedia(m_stations.at(static_cast<quint64>(index)).url());
    m_player->play();
    qDebug() << m_player->audioRole();
}

void StationsModel::stop()
{
    m_player->stop();
}

bool StationsModel::updateStations()
{
    bool requestResult{false};
    std::vector<Station> stationResult;
    std::tie(requestResult, stationResult) = m_stationsReader.requestStationsReader();

    if (requestResult) {
        m_stations.swap(stationResult);
        emit dataChanged(createIndex(0, 0), createIndex(static_cast<qint32>(m_stations.size()), 0));
    }
    return requestResult;
}
