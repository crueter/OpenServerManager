#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QJsonObject>
#include <QString>

typedef struct OperatingSystem {
    QString name;
    QString rebootCmd;
    QString upgradeCmd;

    QString toString() const;
    static OperatingSystem fromString(const QString &string);
} OperatingSystem;

extern const OperatingSystem Arch;
extern const OperatingSystem Debian;

typedef struct ServerData {
    QString name;
    QString host;
    QString user;
    uint16_t port;
    OperatingSystem os;

    QJsonObject toJson() const;
    static ServerData fromJson(const QJsonObject &obj);
} ServerData;

#endif // SERVERDATA_H
