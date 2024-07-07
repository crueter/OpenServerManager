#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "ServerData.h"

#include <QDir>

class Exercise;

class DataManager
{
public:
    static void init();

    enum DataError {
        Success,
        Failure,
        NoOp
    };

    static DataError removeServer(const int idx);
    static DataError addServer(const int idx, const ServerData &data);
    static DataError appendServer(const ServerData &data);
    static QList<ServerData> loadServers();

private:
    static QDir dataDir;

    static DataError addJsonObject(QFile &file, const int idx, const QJsonObject &obj);
    static DataError appendJsonObject(QFile &file, const QJsonObject &obj);
};

#endif // DATAMANAGER_H
