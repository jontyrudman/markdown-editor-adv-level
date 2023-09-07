#include "notebookswitcher.h"
#include "ui_notebookswitcher.h"

NotebookSwitcher::NotebookSwitcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotebookSwitcher)
{
    ui->setupUi(this);
}

NotebookSwitcher::~NotebookSwitcher()
{
    delete ui;
}

void NotebookSwitcher::setNotebookList(QStringList &notebooks)
{
    // Adds each QString in notebooks list as an item in listNotebooksView
    for (int i = 0; i < notebooks.size(); i++) {
        QString cur = notebooks.at(i).toLocal8Bit().constData();
        new QListWidgetItem(cur, ui->listNotebooksView);
    }
}

QString NotebookSwitcher::selectedNotebook()
{
    return notebookName;
}

void NotebookSwitcher::on_buttonBox_accepted()
{
    // If an item has been selected, set notebookName to its QString
    if (!ui->listNotebooksView->selectedItems().isEmpty())
        notebookName = ui->listNotebooksView->selectedItems().first()->text();
}
