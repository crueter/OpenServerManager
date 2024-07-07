#include "ServerPreview.h"
#include "ui_ServerPreview.h"

ServerPreview::ServerPreview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerPreview)
{
    ui->setupUi(this);
}

ServerPreview::~ServerPreview()
{
    delete ui;
}
