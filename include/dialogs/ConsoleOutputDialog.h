#ifndef CONSOLEOUTPUTDIALOG_H
#define CONSOLEOUTPUTDIALOG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class ConsoleOutputDialog;
}

class ConsoleOutputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConsoleOutputDialog(QProcess *process, QString program, QStringList arguments, QWidget *parent = nullptr);
    ~ConsoleOutputDialog();

public slots:
    void terminate();

private:
    Ui::ConsoleOutputDialog *ui;

    QProcess *m_process;
};

#endif // CONSOLEOUTPUTDIALOG_H
