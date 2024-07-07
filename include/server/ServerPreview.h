#ifndef SERVERPREVIEW_H
#define SERVERPREVIEW_H

#include <QWidget>

namespace Ui {
class ServerPreview;
}

class ServerPreview : public QWidget
{
    Q_OBJECT

public:
    explicit ServerPreview(QWidget *parent = nullptr);
    ~ServerPreview();

private:
    Ui::ServerPreview *ui;
};

#endif // SERVERPREVIEW_H
