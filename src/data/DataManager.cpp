#include "data/DataManager.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonArray>

#include <QMessageBox>
#include <QDirIterator>
#include <QJsonDocument>

QDir DataManager::dataDir{};

void DataManager::init()
{
    dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    dataDir.mkpath(".");
}

DataManager::DataError DataManager::removeServer(const int idx)
{
    QFile file(dataDir.absoluteFilePath("servers.json"));
    if (!file.open(QIODevice::ReadOnly)) {
        return NoOp;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    array.removeAt(idx);

    QByteArray toWrite = QJsonDocument(array).toJson();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save server data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    file.write(toWrite);

    file.close();

    return Success;
}

DataManager::DataError DataManager::addServer(const int idx, const ServerData &data)
{
    QFile file(dataDir.absoluteFilePath("servers.json"));

    return addJsonObject(file, idx, data.toJson());
}

DataManager::DataError DataManager::appendServer(const ServerData &data)
{
    QFile file(dataDir.absoluteFilePath("servers.json"));

    return appendJsonObject(file, data.toJson());

}

QList<ServerData> DataManager::loadServers()
{
    QList<ServerData> data{};

    QFile f(dataDir.absoluteFilePath("servers.json"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return data;
    }

    QByteArray contents = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(contents);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        data.append(ServerData::fromJson(obj));
    }

    f.close();

    return data;
}

DataManager::DataError DataManager::addJsonObject(QFile &file, const int idx, const QJsonObject &obj)
{
    QJsonArray array;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        array = doc.array();

        file.close();
    }

    array.insert(idx, obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to write some data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;
}

DataManager::DataError DataManager::appendJsonObject(QFile &file, const QJsonObject &obj)
{
    QJsonArray array;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        array = doc.array();

        file.close();
    }

    array.append(obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to write some data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;

}
