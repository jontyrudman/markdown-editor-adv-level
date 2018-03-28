#ifndef GITLOGIN_H
#define GITLOGIN_H

#include <QDialog>

namespace Ui {
class GitLogin;
}

class GitLogin : public QDialog
{
    Q_OBJECT

public:
    explicit GitLogin(QWidget *parent = 0);
    ~GitLogin();

private:
    Ui::GitLogin *ui;
};

#endif // GITLOGIN_H
