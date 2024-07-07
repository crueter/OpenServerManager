#include "dialogs/ConsoleOutputDialog.h"
#include "ui_ConsoleOutputDialog.h"

#include <QTimer>

ConsoleOutputDialog::ConsoleOutputDialog(QProcess *process, QString program, QStringList arguments, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConsoleOutputDialog)
    , m_process(process)
{
    ui->setupUi(this);

    connect(process, &QProcess::readyRead, this, [this, process] {
        ui->textEdit->append(process->readAll());
    });

    connect(process, &QProcess::finished, this, [this, process](int code, QProcess::ExitStatus) {
        ui->buttonBox->setEnabled(true);
    });
    qDebug() << arguments;

    process->start(program, arguments);
}

ConsoleOutputDialog::~ConsoleOutputDialog()
{
    delete ui;
}

void ConsoleOutputDialog::terminate()
{
    m_process->terminate();
    reject();
}
