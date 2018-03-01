#ifndef NOTEBOOKSWITCHER_H
#define NOTEBOOKSWITCHER_H

#include <QDialog>

namespace Ui {
class NotebookSwitcher;
}

class NotebookSwitcher : public QDialog
{
    Q_OBJECT

public:
    explicit NotebookSwitcher(QWidget *parent = 0);
    ~NotebookSwitcher();

private:
    Ui::NotebookSwitcher *ui;
};

#endif // NOTEBOOKSWITCHER_H
