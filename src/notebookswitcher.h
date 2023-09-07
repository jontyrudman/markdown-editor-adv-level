#ifndef NOTEBOOKSWITCHER_H
#define NOTEBOOKSWITCHER_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QStringList>

namespace Ui {
class NotebookSwitcher;
}

class NotebookSwitcher : public QDialog
{
    Q_OBJECT

public:
    explicit NotebookSwitcher(QWidget *parent = 0);
    ~NotebookSwitcher();
    void setNotebookList(QStringList &notebooks);
    QString selectedNotebook();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NotebookSwitcher *ui;
    QString notebookName;
};

#endif // NOTEBOOKSWITCHER_H
