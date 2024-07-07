#include "dialogs/ServerInfoDialog.h"
#include "ui_ServerInfoDialog.h"

ServerInfoDialog::ServerInfoDialog(const ServerData &data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerInfoDialog)
{
    ui->setupUi(this);

    ui->name->setText(data.name);
    ui->host->setText(data.host);
    ui->user->setText(data.user);
    ui->port->setValue(data.port);
    ui->os->setCurrentText(data.os.toString());
}

ServerInfoDialog::ServerInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerInfoDialog)
{
    ui->setupUi(this);
}

ServerInfoDialog::~ServerInfoDialog()
{
    delete ui;
}

void ServerInfoDialog::sendInfo()
{
    emit ready(
        ServerData{
            ui->name->text(),
            ui->host->text(),
            ui->user->text(),
            static_cast<uint16_t>(ui->port->value()),
            ui->os->currentText()
        });

    accept();
}
