#include "gitlogin.h"
#include "ui_gitlogin.h"

GitLogin::GitLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitLogin)
{
    ui->setupUi(this);
}

GitLogin::~GitLogin()
{
    delete ui;
}
