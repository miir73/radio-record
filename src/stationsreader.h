#pragma once

#include <QList>

#include "station.h"

class StationsReader {
public:
    std::pair<bool, std::vector<Station>> requestStationsReader();
};
