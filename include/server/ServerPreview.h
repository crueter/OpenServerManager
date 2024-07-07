#ifndef SERVERPREVIEW_H
#define SERVERPREVIEW_H

#include "ServerData.h"
#include <QWidget>

namespace Ui {
class ServerPreview;
}

class ServerPreview : public QWidget
{
    Q_OBJECT

public:
    ServerPreview(int idx, const ServerData &data, QWidget *parent = nullptr);
    explicit ServerPreview(int idx, QWidget *parent = nullptr);
    ~ServerPreview();

public slots:
    void remove();
    void updateServer();
    void reboot();
    void modify();
    void updateStatus();

signals:
    void removeRequested();

private:
    Ui::ServerPreview *ui;

    ServerData m_data;
    int m_idx;

    QString getUser() const;
};

#endif // SERVERPREVIEW_H
