#ifndef SERVERSPAGE_H
#define SERVERSPAGE_H

#include "server/ServerPreview.h"
#include <QWidget>

namespace Ui {
class ServersPage;
}

class ServersPage : public QWidget
{
    Q_OBJECT

public:
    explicit ServersPage(QWidget *parent = nullptr);
    ~ServersPage();

public slots:
    void add();
    void add(const int idx, ServerPreview *preview);

private:
    Ui::ServersPage *ui;

    QList<ServerPreview *> m_servers;
};

#endif // SERVERSPAGE_H
