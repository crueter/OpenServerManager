#include "ServerData.h"

// z

const OperatingSystem Arch{"Arch", "reboot now", "pacman -Syu --noconfirm"};
const OperatingSystem Debian{"Debian", "reboot now", "apt update && apt upgrade -y"};

QJsonObject ServerData::toJson() const
{
    QJsonObject obj;

    obj.insert("name", name);
    obj.insert("host", host);
    obj.insert("user", user);
    obj.insert("port", port);
    obj.insert("os", os.toString());

    return obj;
}

ServerData ServerData::fromJson(const QJsonObject &obj)
{
    ServerData data{};

    data.name = obj.value("name").toString();
    data.host = obj.value("host").toString();
    data.user = obj.value("user").toString();
    data.port = obj.value("port").toInt();
    data.os = OperatingSystem::fromString(obj.value("os").toString());

    return data;
}

QString OperatingSystem::toString() const
{
    return name;
}

OperatingSystem OperatingSystem::fromString(const QString &string)
{
    if (string == "Arch") {
        return Arch;
    } else if (string == "Debian") {
        return Debian;
    } else {
        return OperatingSystem{
            "reboot now",
            "apt update && apt upgrade -y"
        };
    }
}
