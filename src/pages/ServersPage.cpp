#include "pages/ServersPage.h"
#include "data/DataManager.h"
#include "ui_ServersPage.h"
#include <cmath>
#include <qtimer.h>

ServersPage::ServersPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServersPage)
{
    ui->setupUi(this);

    QList<ServerData> servers = DataManager::loadServers();
    for (int i = 0; i < servers.count(); ++i) {
        add(i, new ServerPreview(i, servers.at(i)));
    }

    QTimer *timer = new QTimer(this);
    timer->setInterval(5000);

    connect(timer, &QTimer::timeout, this, [this] {
        for (ServerPreview *preview : m_servers) {
            preview->updateStatus();
        }
    });

    timer->start();
}

ServersPage::~ServersPage()
{
    delete ui;
}

void ServersPage::add()
{
    int idx = m_servers.count();
    ServerPreview *preview = new ServerPreview(idx, this);
    add(idx, preview);
}

void ServersPage::add(const int idx, ServerPreview *preview)
{
    m_servers.insert(idx, preview);

    int row = std::floor(idx / 2.0);
    int col = idx % 2;

    ui->servers->addWidget(preview, row, col);
    ui->servers->setRowStretch(row, 1);
    ui->servers->setColumnStretch(col, 1);

    connect(preview, &ServerPreview::removeRequested, this, [this, preview] {
        int serverNum = m_servers.indexOf(preview);
        m_servers.removeAll(preview);
        ui->servers->removeWidget(preview);
        preview->deleteLater();

        for (ServerPreview *server : std::as_const(m_servers)) {
            int num = m_servers.indexOf(server);

            int row = std::floor( (num) / 2.0);
            int col = num % 2;

            ui->servers->removeWidget(server);
            ui->servers->addWidget(server, row, col);
            ui->servers->setRowStretch(row, 1);
            ui->servers->setColumnStretch(col, 1);
        }
    });

    preview->updateStatus();
}
