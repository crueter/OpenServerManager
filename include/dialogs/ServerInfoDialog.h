#ifndef SERVERINFODIALOG_H
#define SERVERINFODIALOG_H

#include <QDialog>

#include <ServerData.h>

namespace Ui {
class ServerInfoDialog;
}

class ServerInfoDialog : public QDialog
{
    Q_OBJECT

public:
    ServerInfoDialog(const ServerData &data, QWidget *parent);
    explicit ServerInfoDialog(QWidget *parent = nullptr);
    ~ServerInfoDialog();

public slots:
    void sendInfo();

signals:
    void ready(const ServerData &data);

private:
    Ui::ServerInfoDialog *ui;
};

#endif // SERVERINFODIALOG_H
