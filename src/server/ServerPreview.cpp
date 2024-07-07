#include "server/ServerPreview.h"
#include "data/DataManager.h"
#include "dialogs/ConsoleOutputDialog.h"
#include "dialogs/ServerInfoDialog.h"
#include "ui_ServerPreview.h"

#include <QProcess>

ServerPreview::ServerPreview(int idx, const ServerData &data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerPreview)
    , m_data(data)
    , m_idx(idx)
{
    ui->setupUi(this);

    ui->name->setText(data.name);
}

ServerPreview::ServerPreview(int idx, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerPreview)
    , m_idx(idx)
{
    ui->setupUi(this);

    m_data.port = 22;

    DataManager::addServer(idx, m_data);
}

ServerPreview::~ServerPreview()
{
    delete ui;
}

void ServerPreview::remove()
{
    emit removeRequested();
}

void ServerPreview::updateServer()
{
    QString program = "ssh";
    QStringList arguments;
    arguments << m_data.user + "@" + m_data.host << "-p" << QString::number(m_data.port);
    arguments << m_data.os.upgradeCmd;

    QProcess *process = new QProcess(this);
    ConsoleOutputDialog *dialog = new ConsoleOutputDialog(process, program, arguments, this);
    dialog->show();
}

void ServerPreview::reboot()
{
    QString program = "ssh";
    QStringList arguments;
    arguments << m_data.user + "@" + m_data.host << "-p" << QString::number(m_data.port);
    arguments << m_data.os.rebootCmd;

    QProcess *process = new QProcess(this);
    ConsoleOutputDialog *dialog = new ConsoleOutputDialog(process, program, arguments, this);
    dialog->show();

}

void ServerPreview::modify()
{
    ServerInfoDialog *dialog = new ServerInfoDialog(m_data, this);
    dialog->show();

    connect(dialog, &ServerInfoDialog::ready, this, [this](const ServerData &data) {
        m_data = data;
        ui->name->setText(data.name);

        DataManager::removeServer(m_idx);
        DataManager::addServer(m_idx, data);
    });
}

void ServerPreview::updateStatus()
{
    QString program = "ping";
    QStringList arguments;
    arguments << m_data.host;
    arguments << "-c" << "1";

    QProcess *process = new QProcess(this);
    process->start(program, arguments);

    connect(process, &QProcess::finished, this, [this](int exitCode) {
        bool good = exitCode == 0;
        if (good) {
            ui->online->setIcon(QIcon(":/icons/check"));
            ui->onlineLabel->setText("Online");
        } else {
            ui->online->setIcon(QIcon(":/icons/xmark"));
            ui->onlineLabel->setText("Offline");
        }
    });
}
