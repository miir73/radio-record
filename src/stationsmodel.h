#pragma once

#include <QAbstractListModel>
#include <QMediaPlayer>

#include <vector>

#include "station.h"
#include "stationsreader.h"

class StationsModel : public QAbstractListModel {
    Q_OBJECT
public:
    StationsModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index = {}, qint32 role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    QHash<int, QByteArray> roleNames() const override;

    static void registerMe();

    Q_INVOKABLE void setStation(qint32 index);
    Q_INVOKABLE void stop();

private:
    std::vector<Station> m_stations;
    QScopedPointer<QMediaPlayer> m_player;
    StationsReader m_stationsReader;

    enum StationRoles { NameRole = Qt::UserRole + 1, PictureRole, UrlRole };

    bool updateStations();
};
